#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <map>

using namespace std;

class Dictionary {

private:
  string** dict;
  int next_index;

  void free_strings(void);

public:
  Dictionary();
  ~Dictionary();
  //Dictionary(const &Dictionary);
  //Dictionary& operator=(const &Dictionary);
  void init_ascii_chars(void);
  string* get(int index);
  void put(string str);

};

#endif
