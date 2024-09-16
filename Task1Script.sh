#!/bin/sh
cc -o Task1FromScript Task1ToCallFromScript.c 
for n in 64 89 256; do
    for l in 10 100; do
        ./Task1FromScript $n $l 2;
        done
done
