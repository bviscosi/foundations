#ifndef DFA_HPP
#define DFA_HPP

#include "alphabet.hpp"
#include "character.hpp"
#include "string.hpp"
#include <functional>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

template <class State> class DFA {
public:
  DFA(std::function<bool(State)> Q, alphabet E, State q0,
      std::function<State(State, character)> d, std::function<bool(State)> F)
      : Q(Q), E(E), q0(q0), d(d), F(F){};

  bool accepts(string w);
  std::optional<string> example();
  std::optional<string> hasPath(State qi, string w);

  std::vector<State> getVisited() { return visited; }
  std::function<bool(State)> getQ() { return Q; }
  alphabet getE() { return E; }
  State getq0() { return q0; }
  std::function<State(State, character)> getd() { return d; }
  std::function<bool(State)> getF() { return F; }

  std::vector<State> visited;
  std::function<bool(State)> Q;
  alphabet E;
  State q0;
  std::function<State(State, character)> d;
  std::function<bool(State)> F;
};

#endif
