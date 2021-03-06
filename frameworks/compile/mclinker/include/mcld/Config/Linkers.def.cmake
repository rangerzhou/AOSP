//===- llvm/Config/Linkers.def - MCLinkers ----------------------*- C++ -*-===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file enumerates all of the linkers supported by this build of MCLinker.
// Clients of this file should define the MCLD_LINKER macro to be a function-like
// macro with a single parameter (the name of the target whose exe/dso can be
// generated); including this file will then enumerate all of the targets with
// linkers.
//
// The set of targets supported by MCLD is generated at configuration
// time, at which point this header is generated. Do not modify this
// header directly.
//
//===----------------------------------------------------------------------===//

#ifndef MCLD_LINKER
#  error Please define the macro MCLD_LINKER(TargetName)
#endif

${MCLD_ENUM_LINKERS}

#undef MCLD_LINKER
