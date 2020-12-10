#ifndef NFA_HPP
#define NFA_HPP

#include "alphabet.hpp"
#include "character.hpp"
#include "string.hpp"
#include <functional>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

template <class State> class NFA {
public:
  NFA(std::function<bool(State)> Q, alphabet E, State q0,
      std::function<std::vector<State>(State, character)> d,
      std::function<bool(State)> F)
      : Q(Q), E(E), q0(q0), d(d), F(F){};
  ;

  bool accepts(string w) {
    std::vector<std::pair<State, string>> visited;
    std::vector<std::pair<State, string>> pending = {std::make_pair(q0, w)};

    while (!pending.empty()) {
      auto qi = pending[0];
      // pop off qi from pending
      auto position = std::find(pending.begin(), pending.end(), qi);
      pending.erase(position);

      // if w is empty/epsilon -> accepted ? return true : add all epsilon
      // transitions
      if (qi.second.isEmpty()) {
        if (F(qi.first))
          return true;
        for (auto qj : d(qi.first, epsilon)) {
          if (std::find(pending.begin(), pending.end(),
                        std::make_pair(qj, qi.second)) == pending.end()) {
            auto qk = std::make_pair(qj, qi.second);
            pending.push_back(qk);
            visited.push_back(qk);
          }
        }
      } else {
        for (auto qj : d(qi.first, epsilon)) {
          if (std::find(pending.begin(), pending.end(),
                        std::make_pair(qj, qi.second)) == pending.end()) {
            auto qk = std::make_pair(qj, qi.second);
            pending.push_back(qk);
            visited.push_back(qk);
          }
        }
        character c = qi.second.pop_front();
        for (auto qj : d(qi.first, c)) {
          if (std::find(pending.begin(), pending.end(),
                        std::make_pair(qj, qi.second)) == pending.end()) {
            pending.push_back(std::make_pair(qj, qi.second));
            visited.push_back(std::make_pair(qj, qi.second));
          }
        }
      }
    }
    return false;
  }
  alphabet getE() { return E; }

  std::function<bool(State)> Q;
  alphabet E;
  character epsilon = character(-1);
  State q0;
  std::function<std::vector<State>(State, character)> d;
  std::function<bool(State)> F;
};

// TASK 28
template <class State> class TraceTree {
public:
  State q;
  bool accepted;
  string w;
  std::vector<TraceTree<State>> branches;
  character epsilon = character(-1);
  character c = character(-1);

  TraceTree(NFA<State> nfa, string w, State qi) : q(qi), w(w) {

    std::vector<State> states = nfa.d(q, epsilon);
    if (w.isEmpty() &&
        (states.size() == 0 || (states.size() == 1 && states[0] == q))) {
      accepted = nfa.F(q);
    } else {
      w.isEmpty() ? c = epsilon : c = w.pop_front();
      for (auto qj : nfa.d(q, c))
        branches.push_back(TraceTree<State>(nfa, w, qj));
    }
  }

  void print() {
    std::cout << " -> ";
    std::cout << "[" << q << "]";
    if (branches.size() != 0) {
      w.isEmpty() ? std::cout << "\u03B5" : std::cout << w.chars[0];
      for (int i = 0; i < branches.size(); i++) {
        if (i > 0) {
          for (int j = 0; j < branches.size(); j++) {
            std::cout << "        ";
          }
        }
        branches[i].print();
      }
    } else {
      std::cout << " : ";
      accepted ? std::cout << "\u2713\n" : std::cout << "x\n";
    }
  }
};
#endif
