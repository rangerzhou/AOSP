/*
 * Copyright (C) 2004-2010 NXP Software
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef _LVREV_TABLES_H_
#define _LVREV_TABLES_H_

/****************************************************************************************/
/*                                                                                      */
/*  Includes                                                                            */
/*                                                                                      */
/****************************************************************************************/
#include "LVREV_Private.h"

/****************************************************************************************/
/*                                                                                      */
/*  Definitions                                                                         */
/*                                                                                      */
/****************************************************************************************/

extern const LVM_UINT32 LVM_FsTable[];
extern LVM_UINT32 LVM_GetFsFromTable(LVM_Fs_en FsIndex);

extern const LVM_FLOAT LVREV_GainPolyTable[24][5];
extern const LVM_INT16 LVREV_MAX_T_DELAY[];
extern const LVM_INT16 LVREV_MAX_AP_DELAY[];

#endif /** _LVREV_TABLES_H_ **/

/* End of file */
