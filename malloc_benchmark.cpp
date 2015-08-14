/*
 * Copyright (C) 2013 The Android Open Source Project
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
#include <fenv.h>
#include <malloc.h>

#define KB 1024
#define MB 1024*KB

#define AT_COMMON_SIZES \
	Arg(512)->Arg(1*KB)->Arg(2*KB)->Arg(4*KB)->Arg(8*KB)->Arg(16*KB)->Arg(32*KB)->Arg(64*KB)->Arg(128*KB)->Arg(256*KB)->Arg(512*KB)-> \
	Arg(1*MB)->Arg(2*MB)->Arg(4*MB)->Arg(8*MB)->Arg(16*MB)->Arg(32*MB)->Arg(64*MB)->Arg(128*MB)->Arg(256*MB)->Arg(512*MB)


//static unsigned size = 512;

static void BM_malloc_test(int iters, int chunk_size) {
	unsigned request_size = chunk_size;

	StartBenchmarkTiming();

    for (int i = 0; i < iters; i++) {
        void * buf;
        buf = malloc(request_size);
        free(buf);
    }

	StopBenchmarkTiming();
}
BENCHMARK(BM_malloc_test)->AT_COMMON_SIZES;

static void BM_malloc_test2(int iters, int chunk_size) {
	unsigned request_size = chunk_size;

	StartBenchmarkTiming();

    for (int i = 0; i < iters; i++) {
        void * buf;
        buf = malloc(request_size);
        buf = realloc(buf, request_size*2);
        free(buf);
    }

	StopBenchmarkTiming();
}
BENCHMARK(BM_malloc_test2)->AT_COMMON_SIZES;

/*
static void BM_malloc_test3(int iters, int chunk_size) {
	unsigned request_size = chunk_size;

	StartBenchmarkTiming();

	for (int j = 0; j < iters; j++) {
		void * buf;
		buf = malloc(request_size);
		//			buf = realloc(buf, request_size*i*2);
		free(buf);
	}

	StopBenchmarkTiming();

}
BENCHMARK(BM_malloc_test3)->AT_COMMON_SIZES;
*/
