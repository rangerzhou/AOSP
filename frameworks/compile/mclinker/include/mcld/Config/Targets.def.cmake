/*===- llvm/Config/Targets.def - MCLD Target Architectures ------*- C++ -*-===*\
|*                                                                            *|
|*                     The MCLinker Project                                   *|
|*                                                                            *|
|* This file is distributed under the University of Illinois Open Source      *|
|* License. See LICENSE.TXT for details.                                      *|
|*                                                                            *|
|*===----------------------------------------------------------------------===*|
|*                                                                            *|
|* This file enumerates all of the target architectures supported by          *|
|* this build of MCLD. Clients of this file should define the                 *|
|* MCLD_TARGET macro to be a function-like macro with a single                *|
|* parameter (the name of the target); including this file will then          *|
|* enumerate all of the targets.                                              *|
|*                                                                            *|
|* The set of targets supported by MCLD is generated at configuration         *|
|* time, at which point this header is generated. Do not modify this          *|
|* header directly.                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifndef MCLD_TARGET
#  error Please define the macro MCLD_TARGET(TargetName)
#endif

${MCLD_ENUM_TARGETS}

#undef MCLD_TARGET
