#!/bin/bash

adb push ~/android/out/target/product/manta/system/bin/bionic-benchmarks32 /data/local
adb shell /data/local/bionic-benchmarks32 malloc --plot 
adb pull /data/local/benchlog
if [ -s benchlog ]; then
	./benchplot.py benchlog
	display benchlog.png
fi
