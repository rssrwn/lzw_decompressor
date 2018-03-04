#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <map>

using namespace std;

// A int -> string mapping used for decompressing an lzw-compressed file
class Dictionary {

private:
  string* dict;
  int next_index;

public:

  Dictionary();
  ~Dictionary();

  // Add all 8-bits (ascii) characters to the dictionary
  void init_ascii_chars(void);

  // Get the string at a given index
  string* get(int index);

  // Add the given string to the dictionary at next_index
  void put(string str);

};

#endif
