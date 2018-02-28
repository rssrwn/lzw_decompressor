#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert> // remove

#include "decompressor.hpp"

#define CODE_WIDTH 12
#define BITS_PER_BYTE 8 // remove

using namespace std;

static void convert_to_codes(string str, int* codes);

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

  stringstream content;
  content << file.rdbuf();
  file.close();

  assert((content.str().length() * BITS_PER_BYTE) % CODE_WIDTH == 0); // remove

  int arr_len = (content.str().length() / 3) * 2;
  int codes[arr_len];
  convert_to_codes(content.str(), codes);

  for (int i=0; i<arr_len; i++) {
    cout << codes[i] << " ";
  }
  cout << endl;

  return 0;
}

static void convert_to_codes(string str, int* codes)
{
  int cur_pos = 0;
  for (int i=0; i<str.length(); i+=3)
  {
    int c1 = (int) str.at(i);
    char c2 = str.at(i+1);
    int c3 = (int) str.at(i+2);

    int lower = c2 & 0x0F;
    int upper = (c2 << 4) & 0x00000F00;

    codes[cur_pos] = (c1 << 4) | lower;
    codes[cur_pos+1] = c3 | upper;
    cur_pos += 2;
  }
}
