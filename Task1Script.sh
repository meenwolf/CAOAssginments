# a script that runs the function we wrote for task 1 for the desired number of strings, and string length, with seed 2
#!/bin/sh
cc -o Task1FromScript Task1Bitstring.c 
for n in 64 89 256; do
    for l in 10 100; do
        ./Task1FromScript $n $l 2;
        done
done
