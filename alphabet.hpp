#ifndef ALPHABET_HPP
#define ALPHABET_HPP

#include "character.hpp"
#include <iostream>
#include <vector>

class alphabet {

public:
  alphabet(std::vector<character> chars) : a(chars){};
  alphabet(std::string w, bool letters) {
    for (auto i : w)
      a.push_back(character(i, letters));
  }
  std::vector<character> a;
  int size() { return int(a.size()); }
  void push_back(character c);
};

#endif
