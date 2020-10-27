#include "string.hpp"

std::ostream &operator<<(std::ostream &out, const string &s) {
  for (auto i : s.chars)
    out << i;
  return out;
}
