#include <iostream>
#include <fstream>
#include <string>

#include "Decompressor.hpp"
#include "Dictionary.hpp"

#define CODE_WIDTH 12

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

  int* codes = convert_to_codes(buffer, length);
  delete[] buffer;

  int num_codes = (length / 3) * 2;
  decompress(codes, num_codes);

  // testing
  if (length % 3 != 0)
    num_codes++;
  for (int i=0; i<num_codes; i++) {
    cout << codes[i] << " ";
  }
  cout << endl;
  // end

  delete[] codes;
  return 0;
}

int* convert_to_codes(char* input, int length)
{
  int num_codes = (length / 3) * 2;
  if (length % 3 != 0)
    num_codes++;

  int* codes = new int[num_codes];
  int cur_pos = 0;

  for (int i=0; i<length; i+=3)
  {
    int c1 = (int) input[i];
    char c2 = input[i+1];

    // If there is only one code left, it will be a padded 16-bit number
    if (num_codes - cur_pos == 1)
    {
      codes[cur_pos] = (c1 << 8) | (int) c2;
      return codes;
    }

    int c3 = (int) input[i+2];

    int lower = c2 & 0x0F;
    int upper = (c2 << 4) & 0x00000F00;

    codes[cur_pos] = (c1 << 4) | lower;
    codes[cur_pos+1] = c3 | upper;
    cur_pos += 2;
  }

  return codes;
}

string& decompress(int* codes, int num_codes)
{
  Dictionary* dict = new Dictionary();



  string* str = new string;
  //string& str2 = *str;
  return *str;
}
