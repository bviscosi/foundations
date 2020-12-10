#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>

class character {

public:
  character(){};
  character(int character) : val(character){};
  character(int character, bool l) : val(character), isLetter(l){};
  friend std::ostream &operator<<(std::ostream &out, const character &c) {
    if (c == -1) {
      out << "\u03B5";
      return out;
    }
    c.isLetter ? out << static_cast<char>(c.val) : out << c.val;
    return out;
  }
  friend bool operator==(character c1, character c2) {
    return c1.val == c2.val;
  }
  friend bool operator==(character c1, char c2) { return c1.val == (int)c2; }

private:
  int val;
  bool isLetter = false;
};

#endif
