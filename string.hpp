#ifndef STRING_HPP
#define STRING_HPP

#include "alphabet.hpp"
#include "character.hpp"
#include <iostream>
#include <vector>

class string {

public:
  alphabet a;
  std::vector<character> chars;

  string(alphabet alphabet, std::vector<character> s) : a(alphabet), chars(s){};
  string(alphabet alphabet) : a(alphabet){};

  void add(character c) { chars.push_back(c); }
  int size() { return chars.size(); }
  bool isEmpty() { return (size() == 0); }
  friend std::ostream &operator<<(std::ostream &out, const string &s);
};

#endif
