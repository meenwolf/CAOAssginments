#include "RandomBitsGenFast.h" //We can not include a C file, but we can include so called header files, which
// can be seen a C programm without a main, so just function declarations.
// I don't have to include libraries that I included in the RandomBitsGenFast.h file.



int main() {
    srand(time(NULL));

    int L = 123;
    BitString b = alloc_bit_string(L);
    print_bitstring(b);
}
