#ifndef DFA_HPP
#define DFA_HPP

#include "alphabet.hpp"
#include "character.hpp"
#include "string.hpp"
#include <functional>
#include <iostream>
#include <vector>

class DFA {
public:
  DFA(std::function<bool(int)> Q, alphabet E, int q0,
      std::function<int(int, character)> d, std::function<bool(int)> F)
      : Q(Q), E(E), q0(q0), d(d), F(F){};

  bool accepts(string w);
  alphabet getAlpha() { return E; }
  void trace();

private:
  std::function<bool(int)> Q;
  alphabet E;
  int q0;
  std::function<int(int, character)> d;
  std::function<bool(int)> F;
  std::vector<int> visitedStates;
};

#endif
