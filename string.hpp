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
  bool isLetters = false;

  string(alphabet alphabet) : a(alphabet){};
  string(alphabet alphabet, std::vector<character> s) : a(alphabet), chars(s){};
  string(alphabet alphabet, std::string w, bool ls) : a(alphabet) {
    for (auto c : w)
      chars.push_back(character(c, ls));
  }
  void add(character c) { chars.push_back(c); }
  void add(string w) {
    for (auto c : w.chars)
      chars.push_back(c);
  }
  void add(std::string w) {
    for (auto c : w)
      chars.push_back(character(c));
  }
  void push_front(character c) { chars.insert(chars.begin(), c); }
    
  character pop_front() {
    character c = chars[0];
    chars.erase(chars.begin());
    return c;
  }

  int size() { return int(chars.size()); }
  bool isEmpty() { return !(chars.size()); }
  friend std::ostream &operator<<(std::ostream &out, const string &s);
};

#endif
