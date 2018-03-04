#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <string>

typedef unsigned short int uint16_t;

using namespace std;

uint16_t* convert_to_codes(char* input, int length);


string& decompress(uint16_t* codes, int num_codes);

#endif
