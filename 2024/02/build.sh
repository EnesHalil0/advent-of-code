#!/bin/sh

gcc main.c -o main && ./main $1

rm main
