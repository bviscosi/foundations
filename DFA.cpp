#include "DFA.hpp"

template <> std::optional<string> DFA<int>::example() {
  visited.clear();
  string str(E);
  return hasPath(q0, str);
}

template <> std::optional<string> DFA<std::pair<int, int>>::example() {
  visited.clear();
  string str(E);
  return hasPath(q0, str);
}

template <class State>
std::optional<string> DFA<State>::hasPath(State qi, string w) {
  if (F(qi)) {
    return w;
  }
  for (auto c : E.a) {
    if (std::find(visited.begin(), visited.end(), d(qi, c)) == visited.end()) {
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

template <> bool DFA<int>::accepts(string w) {
  visited.clear();
  auto qi = q0;
  for (character c : w.chars) {
    visited.push_back(qi);
    qi = d(qi, c);
  }
  return F(qi);
}

template <> bool DFA<std::pair<int, int>>::accepts(string w) {
  visited.clear();
  auto qi = q0;
  for (character c : w.chars) {
    visited.push_back(qi);
    qi = d(qi, c);
  }
  return F(qi);
}
