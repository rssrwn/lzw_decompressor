#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert> // remove

#include "decompressor.hpp"

#define CODE_WIDTH 12
#define BITS_PER_BYTE 8 // remove

using namespace std;

void print_string(string input); // remove

int main(int argc, char **argv)
{
  if (argc < 2) {
    cerr << "No filename given" << endl;
    exit(EXIT_FAILURE);
  }

  ifstream file(argv[1]);
  if (!file) {
    cerr << "Unknown filename" << endl;
    exit(EXIT_FAILURE);
  }

  stringstream content;
  content << file.rdbuf();
  assert((content.str().length() * BITS_PER_BYTE) % CODE_WIDTH == 0); // remove

  //cout << content.str().length() << endl;
  //print_string(content.str());
  file.close();

  return 0;
}

void print_string(string input)
{
  for (int i=0; i<input.length(); i++)
  {
    cout << input.at(i) << endl;
  }
}
