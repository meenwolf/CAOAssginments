/* Write a C/C++ program that calculates the hamming distance between pairs of N binary
strings of length L. For simplicity, you should generate the strings randomly.
Your program should read three integer numbers from the command line: the number of
strings (N), the string length (L), and a seed for the random number generator (s). Your
program should first dynamically allocate memory, and randomly generate N strings.
Thereafter, the hamming distance for all possible pairs of the N strings should be calculated.
Your program should print the checksum (accumulation of all hamming distances) and the
average of all hamming distances and exit. Write a script that compiles your program and
calls it for L = 64, 89, and 256, and N = 100 and 1000.
The aim of this task is to understand the underlying computations.
Important:
- A “binary string” refers to the concept of an array of bits; it does not necessarily imply
that one should use actual strings to represent the data.
- Consider an efficient way to generate strings, keeping in mind that all data in a system
is represented as arrays of bits.
- Consider an efficient way to calculate and count the differences between the binary
strings. */