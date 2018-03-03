#include "Dictionary.hpp"

#define MAX_CHARS 255
#define MAX_DICT_SIZE 4096

using namespace std;

Dictionary::Dictionary()
{
  dict = new map<string, int>;
  curr_index = 0;
}

Dictionary::~Dictionary()
{
  delete dict;
}

void Dictionary::init_ascii_chars(void)
{
  for (int i=0; i<=MAX_CHARS; i++)
  {
    string str(1, (char) i);
    dict->insert( pair<string, int>(str, i) );
  }
}

bool Dictionary::contains(string str)
{
  if (dict->find(str) == dict->end())
    return false;

  return true;
}

int Dictionary::get(string str)
{
  map<string, int>::iterator iter = dict->find(str);
  if (iter == dict->end())
    return -1;

  return iter->second;
}

void Dictionary::put(string str)
{
  // If the dictionary is bigger than 2^12, reset it
  if (curr_index >= (MAX_DICT_SIZE-1))
  {
    dict->clear();
    this->init_ascii_chars();
    curr_index = 0;
  }

  pair<string, int> p(str, curr_index);
  dict->insert(p);
  curr_index++;
}
