#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>

class character {

public:
  character(int character) { val = character; }
  friend std::ostream &operator<<(std::ostream &out, const character &c) {
    out << c.val;
    return out;
  }
  friend bool operator==(character c1, character c2) {
    return c1.val == c2.val;
  }
  friend bool operator==(character c1, char c2) { return c1.val == c2; }

private:
  int val;
};

#endif
