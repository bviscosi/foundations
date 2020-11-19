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

  bool accepts(string w) {
    visited.clear();
    auto qi = q0;
    for (character c : w.chars) {
      visited.push_back(qi);
      qi = d(qi, c);
    }
    return F(qi);
  }

  std::optional<string> example() {
    visited.clear();
    string str(E);
    return hasPath(q0, str);
  }

  std::optional<string> hasPath(State qi, string w) {
    if (F(qi)) {
      return w;
    }
    for (auto c : E.a) {
      if (std::find(visited.begin(), visited.end(), d(qi, c)) ==
          visited.end()) {
        visited.push_back(d(qi, c));
        auto output = hasPath(d(qi, c), w);
        if (output.has_value()) {
          w.add(output.value());
          w.push_front(c);
          return w;
        }
      }
    }
    return std::nullopt;
  }

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
