#include "DFA.hpp"

bool DFA::accepts(string w) {
  int qi = q0;
  for (character c : w.chars) {
    visitedStates.push_back(qi);
    qi = d(qi, c);
  }
  return F(qi);
}

void DFA::trace() {
  std::cout << "\u03B5";
  for (auto i : visitedStates) {
    std::cout << " -> " << i;
  }
  std::cout << '\n';
}
