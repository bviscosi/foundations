#ifndef TESTS_HPP
#define TESTS_HPP

#include "functions.hpp"

template <class State> inline void test(DFA<State> dfa) {
  alphabet E = dfa.getE();
  for (int i = 0; i < 12; i++) {
    accepts(dfa, lexi(E, i));
  }
  std::cout << SEPARATOR;
}

inline bool testLexi(alphabet E) {
  std::cout << SEPARATOR << "FIRST 32 NTH STRINGS \n" << SEPARATOR;
  for (int i = 0; i < 32; i++)
    std::cout << lexi(E, i) << std::endl;
  return true;
}

template <class State>
inline bool testCorpus(std::vector<std::pair<DFA<State>, std::string>> corpus) {
  std::cout << SEPARATOR;
  for (auto i : corpus) {
    std::cout << (i.second) << '\n' << SEPARATOR;
    test(i.first);
  }
  return true;
}

template <class State>
inline bool
testExample(std::vector<std::pair<DFA<State>, std::string>> corpus) {
  std::cout << "EXAMPLE STRING TESTS\n" << SEPARATOR;
  std::optional<string> x;
  for (auto i : corpus) {
    x = example(i.first);
    std::cout << i.second;
    for (auto j = i.second.size(); j < 12; j++)
      std::cout << " ";
    std::cout << ": ";
    if (x.has_value())
      x.value().isEmpty() ? std::cout << "\u03B5\n"
                          : std::cout << x.value() << "\n";
    else
      std::cout << "DNE\n";
  }
  std::cout << '\n' << SEPARATOR;
  return true;
}

template <class State>
inline bool
testComplement(std::vector<std::pair<DFA<State>, std::string>> corpus) {
  for (auto i : corpus) {
    std::cout << (i.second) << "\'\n" << SEPARATOR;
    test(complement(i.first));
  }
  return true;
}

template <class State>
inline bool
testIntersect(std::vector<std::pair<DFA<State>, std::string>> corpus) {
  for (int i = 0; i < corpus.size() - 1; i++) {
    std::cout << corpus[i].second << " ∩ " << corpus[i + 1].second << '\n'
              << SEPARATOR;
    auto x = intersect(corpus[i].first, corpus[i + 1].first);
    test(x);
  }
  return true;
}

template <class State>
inline bool testUnion(std::vector<std::pair<DFA<State>, std::string>> corpus) {
  for (int i = 0; i < corpus.size() - 1; i++) {
    std::cout << corpus[i].second << " ∪ " << corpus[i + 1].second << '\n'
              << SEPARATOR;
    auto u = _union(corpus[i].first, corpus[i + 1].first);
    test(u);
  }
  return true;
}

template <class State>
inline bool testSubset(std::vector<std::pair<DFA<State>, std::string>> corpus) {
  std::cout << "SUBSET TESTS\n" << SEPARATOR;
  for (int i = 0; i < corpus.size() - 1; i++) {
    std::cout << corpus[i].second << " ⊆ " << corpus[i + 1].second;
    for (int j = corpus[i].second.size() + corpus[i + 1].second.size(); j < 23;
         j++)
      std::cout << " ";
    subset(corpus[i].first, corpus[i + 1].first) ? std::cout << ": TRUE\n"
                                                 : std::cout << ": FALSE\n";
  }
  return true;
}

#endif
