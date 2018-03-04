#include <iostream>
#include <fstream>
#include <string>

#include "Decompressor.hpp"
#include "Dictionary.hpp"

#define CODE_WIDTH 12
#define SMALLEST_BYTE 0x00FF
#define UPPER_NIBBLE 0x00F0
#define LOWER_NIBBLE 0x000F

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cerr << "No filename given" << endl;
    exit(EXIT_FAILURE);
  }

  ifstream file(argv[1]);
  if (!file)
  {
    cerr << "Unknown filename" << endl;
    exit(EXIT_FAILURE);
  }

  // Get length of file
  file.seekg(0, file.end);
  int length = file.tellg();
  file.seekg(0, file.beg);

  char* buffer = new char[length];
  file.read(buffer, length);
  file.close();

  uint16_t* codes = convert_to_codes(buffer, length);
  delete[] buffer;

  int num_codes = (length / 3) * 2;
  string str = decompress(codes, num_codes);
  cout << str << endl;

  //delete[] codes;
  return 0;
}

uint16_t* convert_to_codes(char* input, int length)
{
  int num_codes = (length / 3) * 2;
  if (length % 3 != 0)
    num_codes++;

  uint16_t* codes = new uint16_t[num_codes];
  int cur_pos = 0;

  for (int i=0; i<length; i+=3)
  {
    uint16_t c1 = input[i];
    uint16_t c2 = input[i+1];

    uint16_t mask_c1 = c1 & SMALLEST_BYTE;

    // If there is only one code left, it will be a padded 16-bit number
    if (num_codes - cur_pos == 1)
    {
      uint16_t mask_c2 = c2 & SMALLEST_BYTE;
      codes[cur_pos] = (mask_c1 << 8) | mask_c2;
      return codes;
    }

    uint16_t c3 = input[i+2];

    uint16_t mask_c3 = c3 & SMALLEST_BYTE;
    uint16_t lower = c2 & LOWER_NIBBLE;
    uint16_t upper = (c2 & UPPER_NIBBLE) >> 4;

    codes[cur_pos] = (mask_c1 << 4) | upper;
    codes[cur_pos+1] = mask_c3 | (lower << 8);
    cur_pos += 2;
  }

  return codes;
}

string& decompress(uint16_t* codes, int num_codes)
{
  string result;
  Dictionary* dict = new Dictionary();
  dict->init_ascii_chars();

  for (int i=0; i<num_codes; i++)
  {
    string curr_str = *dict->get(codes[i]);
    string* next_str_ptr = dict->get(codes[i+1]);

    result += curr_str;
    string new_str(curr_str);

    if (next_str_ptr == nullptr)
      new_str.push_back(curr_str.at(0));

    else
      new_str.push_back(next_str_ptr->at(0));

    dict->put(new_str);
  }
  delete dict;

  return result;
}
