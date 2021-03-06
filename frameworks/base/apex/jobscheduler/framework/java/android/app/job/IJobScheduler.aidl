/**
 * Copyright (C) 2014 The Android Open Source Project
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

package android.app.job;

import android.app.job.JobInfo;
import android.app.job.JobSnapshot;
import android.app.job.JobWorkItem;
import android.content.pm.ParceledListSlice;

 /**
  * IPC interface that supports the app-facing {@link #JobScheduler} api.
  * {@hide}
  */
interface IJobScheduler {
    int schedule(in JobInfo job);
    int enqueue(in JobInfo job, in JobWorkItem work);
    int scheduleAsPackage(in JobInfo job, String packageName, int userId, String tag);
    void cancel(int jobId);
    void cancelAll();
    ParceledListSlice getAllPendingJobs();
    JobInfo getPendingJob(int jobId);
    List<JobInfo> getStartedJobs();
    ParceledListSlice getAllJobSnapshots();
}
