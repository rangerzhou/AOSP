// GENERATED FILE - DO NOT EDIT.
// Generated by gen_builtin_symbols.py using data from builtin_variables.json and
// builtin_function_declarations.txt.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ParseContext_ESSL_autogen.h:
//   Helpers for built-in related checks.

#ifndef COMPILER_TRANSLATOR_PARSECONTEXT_AUTOGEN_H_
#define COMPILER_TRANSLATOR_PARSECONTEXT_AUTOGEN_H_

namespace sh
{

namespace BuiltInGroup
{

bool isTextureOffsetNoBias(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3094 && id <= 3163;
}
bool isTextureOffsetBias(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3164 && id <= 3183;
}
bool isTextureGatherOffsetsComp(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3221 && id <= 3233;
}
bool isTextureGatherOffsetsNoComp(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3234 && id <= 3249;
}
bool isTextureGatherOffsets(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3221 && id <= 3249;
}
bool isTextureGatherOffsetComp(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3250 && id <= 3255;
}
bool isTextureGatherOffsetNoComp(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3256 && id <= 3263;
}
bool isTextureGatherOffset(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3250 && id <= 3263;
}
bool isTextureGather(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3197 && id <= 3263;
}
bool isAtomicMemory(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3280 && id <= 3297;
}
bool isImageLoad(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3328 && id <= 3342;
}
bool isImageStore(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3343 && id <= 3357;
}
bool isImage(const TFunction *func)
{
    int id = func->uniqueId().get();
    return id >= 3298 && id <= 3357;
}

}  // namespace BuiltInGroup

}  // namespace sh

#endif  // COMPILER_TRANSLATOR_PARSECONTEXT_AUTOGEN_H_