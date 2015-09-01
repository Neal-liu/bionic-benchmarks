#!/bin/bash

adb push ~/android/out/target/product/manta/system/bin/bionic-benchmarks32 /data/local
adb shell stop
#adb shell /data/local/bionic-benchmarks32 malloc_test3
adb shell /data/local/bionic-benchmarks32 malloc_single --plot 
adb pull /data/local/benchlog benchlog
if [ -s benchlog ]; then
	./benchplot.py benchlog
	display benchlog.png
fi
adb shell start

