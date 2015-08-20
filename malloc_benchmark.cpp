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
#define N_ELEMENTS 10

#define AT_COMMON_SIZES \
	Arg(512)->Arg(1*KB)->Arg(2*KB)->Arg(4*KB)->Arg(8*KB)->Arg(16*KB)->Arg(32*KB)->Arg(64*KB)->Arg(128*KB)->Arg(256*KB)->Arg(512*KB)-> \
	Arg(1*MB)->Arg(2*MB)->Arg(4*MB)->Arg(8*MB)->Arg(16*MB)->Arg(32*MB)->Arg(64*MB)->Arg(128*MB)->Arg(256*MB)

#define AT_CONTINUOUS_SIZES \
	Arg(512)->Arg(1*KB)->Arg(2*KB)->Arg(4*KB)->Arg(8*KB)->Arg(16*KB)->Arg(32*KB)->Arg(64*KB)->Arg(128*KB)->Arg(256*KB)->Arg(512*KB)-> \
	Arg(1*MB)->Arg(2*MB)->Arg(4*MB)->Arg(8*MB)->Arg(16*MB)->Arg(32*MB)->Arg(64*MB)->Arg(128*MB)

//static unsigned size = 512;

static void BM_malloc_test(int iters, int chunk_size) {
	unsigned request_size = chunk_size;

//	StartBenchmarkTiming();

    for (int i = 0; i < iters; i++) {
		StartBenchmarkTiming();

        void * buf;
        buf = malloc(request_size);
        free(buf);

		StopBenchmarkTimingWithStd();
    }
//	StopBenchmarkTimingWithStd();
//	StopBenchmarkTiming();
}
BENCHMARK(BM_malloc_test)->AT_COMMON_SIZES;

static void BM_malloc_test2(int iters, int chunk_size) {
	unsigned request_size = chunk_size;


    for (int i = 0; i < iters; i++) {
		StartBenchmarkTiming();

        void * buf;
        buf = malloc(request_size);
        buf = realloc(buf, request_size*2);
        free(buf);
		
		StopBenchmarkTimingWithStd();
    }
	
//	StopBenchmarkTimingWithStd();
//	StopBenchmarkTiming();
}
BENCHMARK(BM_malloc_test2)->AT_COMMON_SIZES;


static void BM_malloc_test3(int iters, int chunk_size) {
	int request_size = chunk_size;
	int *buf = new int[N_ELEMENTS];

	for(int i = 0 ; i < iters ; i ++) {

		StartBenchmarkTiming();
		for (int j = 0 ; j < N_ELEMENTS ; j++)
			buf[j] = (int)malloc(request_size);

		for (int k = 0 ; k < N_ELEMENTS ; k++)
			free((void *)buf[k]);	

		StopBenchmarkTimingWithArg(N_ELEMENTS);
	}
//	StopBenchmarkTimingWithArg(N_ELEMENTS);
//	StopBenchmarkTiming();

}
BENCHMARK(BM_malloc_test3)->AT_CONTINUOUS_SIZES;


