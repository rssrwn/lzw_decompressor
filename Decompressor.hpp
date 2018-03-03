#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <string>

typedef unsigned short int uint16_t;

using namespace std;

int* convert_to_codes(char* input, int length);


string& decompress(int* codes, int num_codes);

#endif
