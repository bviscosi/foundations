#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "DFA.hpp"
#include "NFA.hpp"
#include "alphabet.hpp"
#include <cmath>
#include <iostream>
#include <optional>
#include <utility>
#define SEPARATOR "-------------------------------------------\n"

// to print pairs more easily
inline std::ostream &operator<<(std::ostream &out,
                                const std::pair<int, int> &pair) {
  out << pair.first << "_" << pair.second;
  return out;
}
// Task 3
string inline lexi(alphabet a, int n) {
  string s(a);
  int layer = 0;
  int y = 0;
  int partition;
  if (n == 0) {
    std::cout << "\u03B5";
  } else if (n <= a.size()) {
    s.add(a.a[n - 1]);
  } else {

    int i = 1;
    while (i <= n) {
      n -= pow(a.size(), layer);
      i *= a.size();
      layer++;
    }
    partition = pow(a.size(), layer);
    int x = partition;
    for (int j = 0; j < layer; j++) {
      partition /= a.size();
      x = partition;
      y = 0;
      while (x <= n) {
        x += partition;
        y++;
      }
      s.add(a.a[y]);
      if (y) {
        n -= (partition * y);
      }
    }
  }
  return s;
}
// Task 7
DFA<int> inline givenChar(character in) {
  std::vector<character> chars;
  chars.push_back(in);
  alphabet alpha(chars);
  DFA<int> givenChar([](int qi) { return qi == 0 || qi == 1 || qi == 2; },
                     alpha, 0,
                     [in](int qi, character c) {
                       switch (qi) {
                       case (0):
                         return c == in ? 1 : 2;
                       case (1):
                         return 2;
                       default:
                         return 2;
                       }
                     },
                     [](int qi) { return qi == 1; });
  return givenChar;
}
// Task 10
template <class State> inline bool accepts(DFA<State> dfa, string w) {
  bool accepted = dfa.accepts(w);
  std::cout << w;
  if (w.isEmpty()) {
    std::cout << "     ";
  } else {
    for (int i = 0; i < 6 - w.size(); i++) {
      std::cout << " ";
    }
  }
  std::cout << "---   ";
  if (accepted)
    std::cout << "Accepted";
  else
    std::cout << "Rejected";
  std::cout << " : ";
  for (auto i : trace(dfa, w)) {
    std::cout << " -> " << i;
  }
  std::cout << "\n";
  return accepted;
}
// TASK 11
template <class State>
inline std::vector<State> trace(DFA<State> dfa, string w) {
  dfa.accepts(w);
  return dfa.getVisited();
}
// TASK 12
template <class State> inline std::optional<string> example(DFA<State> dfa) {
  std::optional<string> x = dfa.example();
  return x;
}
// TASK 13
template <class State> inline DFA<State> complement(DFA<State> dfa) {
  auto F = dfa.getF();
  DFA<State> cdfa(dfa.getQ(), dfa.getE(), dfa.getq0(), dfa.getd(),
                  [F](State qi) { return !F(qi); });
  return cdfa;
}
// TASK 14
template <class T1, class T2>
inline DFA<std::pair<T1, T2>> _union(DFA<T1> dfa1, DFA<T2> dfa2) {
  DFA<std::pair<T1, T2>> udfa(
      [dfa1, dfa2](std::pair<T1, T2> qi) {
        return dfa1.Q(qi.first) || dfa2.Q(qi.second);
      },
      dfa1.getE(), std::pair<T1, T2>(dfa1.q0, dfa2.q0),
      [dfa1, dfa2](std::pair<T1, T2> qi, character c) {
        return std::pair<T1, T2>(dfa1.d(qi.first, c), dfa2.d(qi.second, c));
      },
      [dfa1, dfa2](std::pair<T1, T2> qi) {
        return dfa1.F(qi.first) || dfa2.F(qi.second);
      });
  return udfa;
}
// TASK 16
template <class T1, class T2>
inline DFA<std::pair<T1, T2>> intersect(DFA<T1> dfa1, DFA<T2> dfa2) {
  DFA<std::pair<T1, T2>> idfa(
      [dfa1, dfa2](std::pair<T1, T2> qi) {
        return dfa1.Q(qi.first) || dfa2.Q(qi.second);
      },
      dfa1.getE(), std::pair<T1, T2>(dfa1.q0, dfa2.q0),
      [dfa1, dfa2](std::pair<T1, T2> qi, character c) {
        return std::pair<T1, T2>(dfa1.d(qi.first, c), dfa2.d(qi.second, c));
      },
      [dfa1, dfa2](std::pair<T1, T2> qi) {
        return dfa1.F(qi.first) && dfa2.F(qi.second);
      });
  return idfa;
}
// TASK 18
template <class State> inline bool subset(DFA<State> x, DFA<State> y) {
  return !example(intersect(complement(y), x)).has_value();
}
// TASK 20
template <class State> inline bool equals(DFA<State> x, DFA<State> y) {
  return subset(x, y) && subset(y, x);
}
// TASK 24
template <class State> inline NFA<State> DFAtoNFA(DFA<State> dfa) {
  NFA<State> nfa(
      dfa.Q, dfa.E, dfa.q0,
      [dfa](int qi, character c) {
        State s = dfa.d(qi, c);
        std::vector<State> states = {s};
        return states;
      },
      dfa.F);
  return nfa;
}
// TASK 26
template <class State>
inline bool oracle(NFA<State> nfa,
                   std::vector<std::pair<State, string>> trace) {
  if (!trace.size())
    return true;
  for (int i = 0; i < trace.size() - 1; i++) {
    std::vector<State> states =
        nfa.d(trace[i].first, trace[i].second.pop_front());
    if (std::find(states.begin(), states.end(), trace[i + 1].first) ==
        states.end()) {
      std::cout << " : INVALID\n";
      return false;
    }
  }
  std::cout << " : VALID - ";
  nfa.F(trace[trace.size() - 1].first) ? std::cout << "(ACCEPTED)\n"
                                       : std::cout << "(REJECTED)\n";

  return true;
}

// TASK 32
template <class State> inline bool backtrack(NFA<State> nfa, string w) {
  bool accepted = nfa.accepts(w);
  std::cout << w;
  if (w.isEmpty()) {
    std::cout << "     ";
  } else {
    for (int i = 0; i < 6 - w.size(); i++) {
      std::cout << " ";
    }
  }
  std::cout << "---   ";
  if (accepted)
    std::cout << "Accepted";
  else
    std::cout << "Rejected";

  std::cout << "\n";
  return accepted;
}

// TASK 30
template <class State>
inline TraceTree<State> explore(NFA<State> nfa, string w) {
  TraceTree tt = TraceTree<State>(nfa, w, nfa.q0);
  tt.print();
  return tt;
}

enum side { START, LEFT, RIGHT };

// TASK 33
template <class T1, class T2>
NFA<std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>>
union_nfa(NFA<T1> nfa1, NFA<T2> nfa2) {

  std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>> start = {
      START, {std::nullopt, std::nullopt}};

  NFA<std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>> unfa(
      // Q
      [nfa1, nfa2,
       start](std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>
                  state) {
        if (state == start) {
          return true;
        } else if (state.first == LEFT && state.second.first != std::nullopt) {
          return nfa1.Q(state.second.first.value());
        } else if (state.first == RIGHT &&
                   state.second.second != std::nullopt) {
          return nfa2.Q(state.second.second.value());
        }
        return false;
      },
      // E
      nfa1.E,
      // q0
      {START, {std::nullopt, std::nullopt}},
      // delta
      [nfa1, nfa2, start](
          std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>> state,
          character next) {
        std::vector<
            std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>>
            v;
        if (state == start && next == -1) {
          v.push_back({1, {nfa1.q0, std::nullopt}});
          v.push_back({2, {std::nullopt, nfa2.q0}});
        } else if (state.first == LEFT && state.second.first != std::nullopt) {
          std::vector<T1> vTemp = nfa1.d(state.second.first.value(), next);
          for (auto i = vTemp.begin(); i != vTemp.end(); i++) {
            v.push_back({LEFT, {*i, std::nullopt}});
          }
        } else if (state.first == RIGHT &&
                   state.second.second != std::nullopt) {
          std::vector<T2> vTemp = nfa2.d(state.second.second.value(), next);
          for (auto i = vTemp.begin(); i != vTemp.end(); i++) {
            v.push_back({RIGHT, {std::nullopt, *i}});
          }
        }
        return v;
      },
      // F
      [nfa1,
       nfa2](std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>
                 state) {
        if (state.first == LEFT && state.second.first != std::nullopt) {
          return nfa1.F(state.second.first.value());
        } else if (state.first == RIGHT &&
                   state.second.second != std::nullopt) {
          return nfa2.F(state.second.second.value());
        }
        return false;
      });
  return unfa;
}

// TASK 34
template <class T1, class T2>
NFA<std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>>
cat(NFA<T1> nfa1, NFA<T2> nfa2) {

  std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>> start = {
      START, {std::nullopt, std::nullopt}};

  NFA<std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>> cnfa(
      // Q
      [nfa1, nfa2,
       start](std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>
                  state) {
        if (state == start)
          return true;
        if (state.first == LEFT && state.second.first != std::nullopt) {
          return nfa1.Q(state.second.first.value());
        }
        if (state.first == RIGHT && state.second.second != std::nullopt) {
          return nfa2.Q(state.second.second.value());
        }
        return false;
      },
      // E
      nfa1.E,
      // q0
      {START, {std::nullopt, std::nullopt}},
      // delta
      [nfa1, nfa2, start](
          std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>> state,
          character next) {
        std::vector<
            std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>>
            v;
        if (state == start && next == -1) {
          v.push_back({LEFT, {nfa1.q0, std::nullopt}});
          v.push_back({RIGHT, {std::nullopt, nfa2.q0}});
        } else if (state.first == LEFT && state.second.first != std::nullopt) {
          std::vector<T1> vTemp = nfa1.d(state.second.first.value(), next);
          for (auto i = vTemp.begin(); i != vTemp.end(); i++) {
            v.push_back({LEFT, {*i, std::nullopt}});
          }
          if (nfa1.F(state.second.first.value()) && next == -1)
            v.push_back({RIGHT, {std::nullopt, nfa2.q0}});
        } else if (state.first == RIGHT &&
                   state.second.second != std::nullopt) {
          std::vector<T2> vTemp = nfa2.d(state.second.second.value(), next);
          for (auto i = vTemp.begin(); i != vTemp.end(); i++) {
            v.push_back({RIGHT, {std::nullopt, *i}});
          }
          if (nfa2.F(state.second.second.value()) && next == -1)
            v.push_back({LEFT, {nfa1.q0, std::nullopt}});
        }
        return v;
      },
      // F
      [nfa1,
       nfa2](std::pair<int, std::pair<std::optional<T1>, std::optional<T2>>>
                 state) {
        if (state.first == LEFT && state.second.first != std::nullopt) {
          return nfa1.F(state.second.first.value());
        }
        if (state.first == RIGHT && state.second.second != std::nullopt) {
          return nfa2.F(state.second.second.value());
        }
        return false;
      }

  );

  return cnfa;
}

// Task 36

template <class State> NFA<State> kleene(NFA<State> nfa) {

  NFA<State> knfa([nfa](int qi) { return qi == START ? true : nfa.Q(qi); },
                  nfa.E, nfa.q0,
                  [nfa](int qi, character c) {
                    std::vector<State> v;
                    for (auto i : nfa.d(qi, c)) {
                      v.push_back(i);
                      if (nfa.F(i))
                        v.push_back(START);
                    }
                    return v;
                  },
                  [nfa](int qi) { return qi == START; });

  return knfa;
}

// Task 38
template <class State> DFA<std::vector<State>> NFAtoDFA(NFA<State> nfa) {

  std::vector<State> q0;
  q0.push_back(nfa.q0);
  DFA<std::vector<State>> dfa =

      DFA<std::vector<State>>(
          [nfa](std::vector<State> qi) {
            for (auto q : qi) {
              if (!nfa.Q(q))
                return false;
            }
            return true;
          },
          nfa.E, q0,

          [nfa](std::vector<State> qi, character c) {
            std::vector<State> states;
            for (auto deadend : E(qi, nfa)) {
              for (auto q : nfa.d(deadend, c)) {
                if (std::find(states.begin(), states.end(), q) == states.end())
                  states.push_back(q);
              }
            }
            return states;
          },
          [nfa](std::vector<State> qi) {
            for (auto q : qi) {
              if (nfa.F(q))
                return true;
            }
            return false;
          });

  return dfa;
}

template <class State>
std::vector<State> E(std::vector<State> states, NFA<State> nfa) {
  std::vector<State> deadends;
  for (auto qi : states) {
    std::vector<State> qe = nfa.d(qi, nfa.epsilon);
    if (!qe.empty()) {
      deadends.push_back(qi);
      for (auto qn : qe) {
        if (qn != qi) {
          std::vector<State> helper = E(std::vector<State>{qn}, nfa);
          deadends.insert(deadends.end(), helper.begin(), helper.end());
        }
      }
    } else {
      deadends.push_back(qi);
    }
  }
  return deadends;
}

// Task 45
// string generate(Regex){}

#endif
