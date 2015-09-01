/*
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

#include "benchmark.h"

#include <sys/syscall.h>
#include <unistd.h>

static void BM_unistd_getpid(int iters) {
//  StartBenchmarkTiming();

  for (int i = 0; i < iters; ++i) {
  	StartBenchmarkTiming();

    getpid();

  	StopBenchmarkTimingWithStd();
  }

//  StopBenchmarkTiming();
}
BENCHMARK(BM_unistd_getpid);

static void BM_unistd_getpid_syscall(int iters) {
//  StartBenchmarkTiming();

  for (int i = 0; i < iters; ++i) {
  	StartBenchmarkTiming();

    syscall(__NR_getpid);

  	StopBenchmarkTimingWithStd();
  }

//  StopBenchmarkTiming();
}
BENCHMARK(BM_unistd_getpid_syscall);

// Stop GCC optimizing out our pure function.
/* Must not be static! */ pid_t (*gettid_fp)() = gettid;

static void BM_unistd_gettid(int iters) {
//  StartBenchmarkTiming();

  for (int i = 0; i < iters; ++i) {
  	StartBenchmarkTiming();

    gettid_fp();

  	StopBenchmarkTimingWithStd();
  }

//  StopBenchmarkTiming();
}
BENCHMARK(BM_unistd_gettid);

static void BM_unistd_gettid_syscall(int iters) {
//  StartBenchmarkTiming();

  for (int i = 0; i < iters; ++i) {
  	StartBenchmarkTiming();

    syscall(__NR_gettid);

  	StopBenchmarkTimingWithStd();
  }

//  StopBenchmarkTiming();
}
BENCHMARK(BM_unistd_gettid_syscall);
