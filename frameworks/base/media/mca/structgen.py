#!/usr/bin/env python

#
# Copyright (C) 2011 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

import os
import sys

hFileTemplate = """/**
 * This file is auto-generated by platform/system/media/mca/structgen.py! Do NOT modify!
 **/

#ifndef %s
#define %s

%s

#endif // %s
"""

jniFileTemplate = """/**
 * This file is auto-generated by platform/system/media/mca/structgen.py! Do NOT modify!
 **/

#include <stdint.h>
#include "native/%s.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "jni.h"

// Helper functions ////////////////////////////////////////////////////////////////////////////////
%s* Get%sAtIndex(JNIEnv* env, jobject buffer, int index) {
  jclass base_class = (*env)->FindClass(env, "android/filterfw/core/NativeBuffer");
  jfieldID ptr_field = (*env)->GetFieldID(env, base_class, "mDataPointer", "J");
  uintptr_t data_ptr = (*env)->GetLongField(env, buffer, ptr_field);
  %s* array = (%s*)data_ptr;
  (*env)->DeleteLocalRef(env, base_class);
  return &array[index];
}

// Declarations ////////////////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL
Java_%s_getElementSize(JNIEnv* env, jobject thiz);

%s

#ifdef __cplusplus
}
#endif

// Implementation //////////////////////////////////////////////////////////////////////////////////
jint Java_%s_getElementSize(JNIEnv* env, jobject thiz) {
  return sizeof(%s);
}

%s
"""

javaFileTemplate = """/**
 * This file is auto-generated by platform/system/media/mca/structgen.py! Do NOT modify!
 **/

package %s;

import android.filterfw.core.NativeBuffer;

%s
"""


def ToJavaName(cname, start_upper_at = 1):
  lower = cname.split("_")
  upper = [c.title() for c in lower]
  return "".join(lower[:start_upper_at] + upper[start_upper_at:])

def ToJNIPackage(package, jclassname):
  return "%s_%s" % (package.replace(".", "_"), jclassname)

def ToMacroDefName(cname, pname):
  return "%s_%s" % (pname.replace(".", "_").upper(), cname.upper())

class ParseError:
  def __init__(self, lineno, message):
    self.lineno = lineno
    self.message = message

  def __str__(self):
    return "On line %d: %s" % (self.lineno, self.message)

class FieldType_BasePOD:
  def __init__(self, name, structname, jclassname, package, javatype, ctype, jtype, defval):
    self.name = name
    self.structname = structname
    self.jclassname = jclassname
    self.package = package
    self.javatype = javatype
    self.ctype = ctype
    self.jtype = jtype
    self.defval = defval

  def cString(self):
    return "  %s %s;" % (self.ctype, self.name)

  def javaGetter(self):
    return "    public %s get%s(int index) {\n"\
           "        assertReadable();\n"\
           "        return nativeGet%s(index);\n"\
           "    }" % (self.javatype, ToJavaName(self.name, 0), ToJavaName(self.name, 0))

  def javaSetter(self):
    return "    public void set%s(int index, %s value) {\n"\
           "        assertWritable();\n"\
           "        nativeSet%s(index, value);\n"\
           "    }" % (ToJavaName(self.name, 0), self.javatype, ToJavaName(self.name, 0))

  def javaNativeGetter(self):
    return "    private native %s nativeGet%s(int index);"\
           % (self.javatype, ToJavaName(self.name, 0))

  def javaNativeSetter(self):
    return "    private native boolean nativeSet%s(int index, %s value);"\
           % (ToJavaName(self.name, 0), self.javatype)

  def jniGetterDefString(self):
    return "JNIEXPORT %s JNICALL\n" \
           "Java_%s_nativeGet%s(JNIEnv* env, jobject thiz, jint index);" \
           % (self.jtype, ToJNIPackage(self.package, self.jclassname), ToJavaName(self.name, 0))

  def jniGetterImplString(self):
    return \
      "%s Java_%s_nativeGet%s(JNIEnv* env, jobject thiz, jint index) {\n"\
      "  %s* instance = Get%sAtIndex(env, thiz, index);\n"\
      "  return instance ? instance->%s : %s;\n"\
      "}\n" % (self.jtype, ToJNIPackage(self.package, self.jclassname), ToJavaName(self.name, 0),\
               self.structname, self.structname, self.name, self.defval)

  def jniSetterDefString(self):
    return "JNIEXPORT jboolean JNICALL\n" \
           "Java_%s_nativeSet%s(JNIEnv* env, jobject thiz, jint index, %s value);" \
           % (ToJNIPackage(self.package, self.jclassname), ToJavaName(self.name, 0), self.jtype)

  def jniSetterImplString(self):
    return \
      "jboolean Java_%s_nativeSet%s(JNIEnv* env, jobject thiz, jint index, %s value) {\n"\
      "  %s* instance = Get%sAtIndex(env, thiz, index);\n"\
      "  if (instance) {\n"\
      "    instance->%s = value;\n"\
      "    return JNI_TRUE;\n"\
      "  }\n"\
      "  return JNI_FALSE;\n"\
      "}\n" % (ToJNIPackage(self.package, self.jclassname), ToJavaName(self.name, 0),\
               self.jtype, self.structname, self.structname, self.name)

class FieldType_Float(FieldType_BasePOD):
  def __init__(self, name, structname, jclassname, package):
    FieldType_BasePOD.__init__(self, name, structname, jclassname, package, "float", "float", "jfloat", "0.0")

class FieldType_Int(FieldType_BasePOD):
  def __init__(self, name, structname, jclassname, package):
    FieldType_BasePOD.__init__(self, name, structname, jclassname, package, "int", "int", "jint", "0")

class FieldType_Long(FieldType_BasePOD):
  def __init__(self, name, structname, jclassname, package):
    FieldType_BasePOD.__init__(self, name, structname, jclassname, package, "long", "long long", "jlong", "0")

class StructSpec:

  def parseTextFile(self, filepath):
    # Init
    self.name = None
    self.package = None
    self.fields = []
    self.structname = None
    self.jclassname = None
    self.libname = None

    # Open the file
    txtfile = open(filepath)

    # Parse it line by line
    lineno = 0
    for line in txtfile:
      # Split line into components
      linecomps = line.split()
      if len(linecomps) == 0:
        continue

      # Execute command
      cmd = linecomps[0]
      if cmd == "@name":
        self.commandArgAssert(linecomps, 1, lineno)
        self.name = linecomps[1]
        if not self.structname:
          self.structname = self.name
        if not self.jclassname:
          self.jclassname = self.name
      elif cmd == "@package":
        self.commandArgAssert(linecomps, 1, lineno)
        self.package = linecomps[1]
      elif cmd == "@libname":
        self.commandArgAssert(linecomps, 1, lineno)
        self.libname = linecomps[1]
      elif cmd == "@structname":
        self.commandArgAssert(linecomps, 1, lineno)
        self.structname = linecomps[1]
      elif cmd == "@javaclassname":
        self.commandArgAssert(linecomps, 1, lineno)
        self.jclassname = linecomps[1]
      elif cmd == "@field":
        self.commandArgAssert(linecomps, 2, lineno)
        typestr = linecomps[1]
        if typestr == "int":
          fieldtype = FieldType_Int(linecomps[2], self.structname, self.jclassname, self.package)
        elif typestr == "long":
          fieldtype = FieldType_Long(linecomps[2], self.structname, self.jclassname, self.package)
        elif typestr == "float":
          fieldtype = FieldType_Float(linecomps[2], self.structname, self.jclassname, self.package)
        else:
          raise ParseError(lineno, "Unknown field type '%s'!" % typestr)
        self.fields.append(fieldtype)
      else:
        raise ParseError(lineno, "Unknown command: '%s'!" % cmd)

      lineno = lineno + 1

    # Make sure we have all required info
    if not self.name:
      raise ParseError(lineno, "Required field '@name' missing!")
    elif not self.package:
      raise ParseError(lineno, "Required field '@package' missing!")
    elif not self.libname:
      raise ParseError(lineno, "Required field '@libname' missing!")

    # Normalize values
    if self.libname[:3] == "lib":
      self.libname = self.libname[3:]

  def commandArgAssert(self, linecomps, expectedcount, lineno):
    foundcount = len(linecomps) - 1
    if foundcount < expectedcount:
      raise ParseError(lineno, "Not enough arguments specifed for command '%s'! Expected %d, " \
                       "but got only %d!" % (linecomps[0], expectedcount, foundcount))
    elif foundcount > expectedcount + 1:
      raise ParseError(lineno, "Too many arguments specifed for command '%s'! Expected %d, " \
                       "but got %d!" % (linecomps[0], expectedcount, foundcount))


  def cStructString(self):
    cfields = [f.cString() for f in self.fields]
    return "typedef struct Struct%s {\n%s\n} %s;\n" % (self.structname,\
                                                       "\n".join(cfields),\
                                                       self.structname)

  def javaClassString(self):
    jgetters = [f.javaGetter() for f in self.fields]
    jsetters = [f.javaSetter() for f in self.fields]
    jnativesetters = [f.javaNativeSetter() for f in self.fields]
    jnativegetters = [f.javaNativeGetter() for f in self.fields]
    return "public class %s extends NativeBuffer {\n\n"\
           "    public %s() {\n"\
           "        super();\n"\
           "    }\n"\
           "\n"\
           "    public %s(int count) {\n"\
           "        super(count);\n"\
           "    }\n"\
           "\n"\
           "    public native int getElementSize();\n"\
           "\n"\
           "%s\n\n"\
           "%s\n\n"\
           "%s\n\n"\
           "%s\n\n"\
           "    static {\n"\
           "        System.loadLibrary(\"%s\");\n"\
           "    }\n"\
           "\n"\
           "};\n" % (self.jclassname,\
                     self.jclassname,\
                     self.jclassname,\
                     "\n\n".join(jgetters),\
                     "\n\n".join(jsetters),\
                     "\n\n".join(jnativegetters),\
                     "\n\n".join(jnativesetters),\
                     self.libname)

  def jniDeclString(self):
    jnigetters = [f.jniGetterDefString() for f in self.fields]
    jnisetters = [f.jniSetterDefString() for f in self.fields]
    return "\n\n".join(jnigetters + jnisetters)

  def jniImplString(self):
    jnigetters = [f.jniGetterImplString() for f in self.fields]
    jnisetters = [f.jniSetterImplString() for f in self.fields]
    return "\n\n".join(jnigetters + jnisetters)

  def hFileString(self):
    defname = ToMacroDefName(self.structname, self.package)
    return hFileTemplate % (defname, defname, self.cStructString(), defname)

  def javaFileString(self):
    return javaFileTemplate % (self.package, self.javaClassString())

  def jniFileString(self):
    return jniFileTemplate % (self.structname.lower(),\
                              self.structname,\
                              self.structname,\
                              self.structname,\
                              self.structname,\
                              ToJNIPackage(self.package, self.jclassname),\
                              self.jniDeclString(),\
                              ToJNIPackage(self.package, self.jclassname),\
                              self.structname,
                              self.jniImplString())

def main(argv):
  if len(argv) != 2:
    print("Usage: %s <file.struct>" % argv[0])
    return -1

  filepath = argv[1]

  structspec = StructSpec()
  structspec.parseTextFile(filepath)

  hfilename = "%s.h" % structspec.structname.lower()
  javafilename = "%s.java" % structspec.jclassname
  jnifilename = "jni_%s.c" % structspec.structname.lower()

  javapackagepath = structspec.package.replace('.','/')

  rootdir = os.path.dirname(filepath)
  hfilepath = "%s/../native/%s" % (rootdir, hfilename)
  javafilepath = "%s/../java/%s/%s" % (rootdir, javapackagepath, javafilename)
  jnifilepath = "%s/../jni/%s" % (rootdir, jnifilename)

  hfile = open(hfilepath, 'w')
  hfile.write(structspec.hFileString())
  hfile.close()

  javafile = open(javafilepath, 'w')
  javafile.write(structspec.javaFileString())
  javafile.close()

  jnifile = open(jnifilepath, 'w')
  jnifile.write(structspec.jniFileString())
  jnifile.close()


if __name__ == "__main__":
  sys.exit(main(sys.argv))
