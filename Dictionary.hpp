#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <map>

using namespace std;

class Dictionary {

private:
  map<string, int>* dict;
  int curr_index;

public:
  Dictionary();
  ~Dictionary();
  //Dictionary(const &Dictionary);
  //Dictionary& operator=(const &Dictionary);
  void init_ascii_chars(void);
  bool contains(string str);
  int get(string str);
  void put(string str);

};

#endif
