#include "Dictionary.hpp"

#define MAX_CHARS 255
#define MAX_DICT_SIZE 4096

using namespace std;

Dictionary::Dictionary()
{
  dict = new string*[MAX_DICT_SIZE];
  next_index = 0;
}

Dictionary::~Dictionary()
{
  free_strings();
  delete[] dict;
}

void Dictionary::init_ascii_chars(void)
{
  for (int i=0; i<=MAX_CHARS; i++)
  {
    string str(1, (char) i);
    this->put(str);
  }
}

string* Dictionary::get(int index)
{
  if (index >= next_index)
    return nullptr;

  return dict[index];
}

void Dictionary::put(string str)
{
  // If the dictionary is bigger than 2^12, reset it
  if (next_index >= MAX_DICT_SIZE)
  {
    free_strings();
    init_ascii_chars();
  }

  string* copy = new string(str);
  dict[next_index] = copy;
  next_index++;
}

void Dictionary::free_strings(void)
{
  for (int i=0; i<next_index; i++)
    delete dict[i];
}
