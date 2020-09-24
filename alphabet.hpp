#ifndef ALPHABET_HPP
#define ALPHABET_HPP

#include "character.hpp"
#include <iostream>
#include <vector>

class alphabet {

public:
  std::vector<character> a;

  alphabet(std::vector<character> chars) : a(chars){};
  alphabet();
  int size() { return a.size(); }
  void push_back(character c);
};

#endif
