/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fstream>
#include <memory>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include "audio_utils/sndfile.h"
#include <android-base/scopeguard.h>

#define MAX_BUFFER_SIZE 0x00005000
#define MAX_FRAME_READ_COUNT 100
#define MAX_FRAME_COUNT 1000

#ifdef SNDFILE_FUZZER_HOST
// the path is located in shared memory, so it can accelerate fuzzing on host
// however, the path is not supported on device
#define TEMP_DATA_PATH "/dev/shm/sndfile_fuzzer.tmp"
#else
#define TEMP_DATA_PATH "/data/local/tmp/sndfile_fuzzer.tmp"
#endif

// create a unique path so that the fuzzer can be run parallelly
std::string getUniquePath() {
  pid_t pid = getpid();
  std::string unique_path = TEMP_DATA_PATH + std::to_string(pid);
  return unique_path;
}

int parseValue(const uint8_t *src, int index, void *dst, size_t size) {
  memcpy(dst, &src[index], size);
  return size;
}

size_t getSizeByType(uint32_t input_format) {
  switch (input_format) {
  case 0: return sizeof(short);
  case 1: return sizeof(int);
  case 2: return sizeof(float);
  default: return sizeof(short);
  }
}

sf_count_t sfReadfWithType(uint32_t input_format, SNDFILE *handle,
                           const void *ptr, sf_count_t desired) {
  switch (input_format) {
  case 0: return sf_readf_short(handle, (short *)ptr, desired);
  case 1: return sf_readf_int(handle, (int *)ptr, desired);
  case 2: return sf_readf_float(handle, (float *)ptr, desired);
  default: return 0;
  }
}

// the corpus of this fuzzer is generated by :
// printf "\x01\x00\x00\x00\x01\x00\x00\x00" | \
// cat - 2020_06_10_15_56_20.wav > merged_corpus
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *bytes, size_t size) {
  uint32_t desired_frame_count = 1;
  uint32_t input_format = 0;

  size_t metadata_size = sizeof(desired_frame_count) + sizeof(input_format);
  if (size < metadata_size) {
    return 0;
  }

  int idx = 0;
  idx +=
      parseValue(bytes, idx, &desired_frame_count, sizeof(desired_frame_count));
  idx += parseValue(bytes, idx, &input_format, sizeof(input_format));

  desired_frame_count %= MAX_FRAME_READ_COUNT;
  input_format %= 3;

  // write bytes to a file
  std::string path = getUniquePath();
  std::ofstream file;
  file.open(path.c_str(), std::ios::trunc | std::ios::binary | std::ios::out);
  if (!file.is_open()) {
    return 0;
  }

  file.write((char *)(bytes + idx), size - idx);
  file.close();
  // ensure file is unlinked after use
  auto scope_guard =
      android::base::make_scope_guard([path] { remove(path.c_str()); });

  SF_INFO info;
  // when format is set to zero, all other field are filled in by the lib
  info.format = 0;
  std::unique_ptr<SNDFILE, decltype(&sf_close)> handle(
      sf_open(path.c_str(), SFM_READ, &info), &sf_close);

  if (handle == nullptr) {
    return 0;
  }

  // sndfile support three different data types to read regardless the original
  // data type in file. the library handles the data conversion. The size of
  // input is parsed from file; malloc buffer by the size is risky, but it
  // cannot be fuzzed at this level. Here, we only ensure the read APIs does not
  // write memory outside the buffer.
  size_t input_size =
      getSizeByType(input_format) * desired_frame_count * info.channels;

  if (input_size > MAX_BUFFER_SIZE) {
    return 0;
  }

  void *dst_buffer = malloc(input_size);
  if (dst_buffer == nullptr) {
    return 0;
  }

  sf_count_t read_frame_count = 0;
  sf_count_t frame_count = 0;
  do {
    read_frame_count = sfReadfWithType(input_format, handle.get(), dst_buffer,
                                       desired_frame_count);
    frame_count += read_frame_count;
  } while (read_frame_count > 0 && frame_count < MAX_FRAME_COUNT);
  free(dst_buffer);

  return 0;
}