#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <string>

typedef unsigned short int uint16_t;

using namespace std;

// Converts a list of bytes to a list of 12-bit codes (padded to 16-bits)
uint16_t* convert_to_codes(char* input, int length);

// lzw decompression algorithm that returns the string respresentation
// of the given codes
string* decompress(uint16_t* codes, int num_codes);

#endif
