#ifndef TESTS_HPP
#define TESTS_HPP

#include "functions.hpp"

template <class State> inline void test(DFA<State> dfa) {
  alphabet E = dfa.getE();
  for (int i = 13; i < 40; i++) {
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

// Task 21
template <class State>
inline bool testEquals(std::vector<std::pair<DFA<State>, std::string>> corpus) {
  bool passed = false;
  std::cout << "EQUALS TESTS\n" << SEPARATOR;
  for (int i = 0; i < corpus.size() - 4; i++) {
    std::cout << corpus[i].second << " == " << corpus[i].second << " : ";
    equals(corpus[i].first, corpus[i].first) ? std::cout << "TRUE\n"
                                             : std::cout << "FALSE\n";
    std::cout << corpus[i].second << " == " << corpus[i + 1].second << " : ";
    equals(corpus[i].first, corpus[i + 1].first) ? std::cout << "TRUE\n"
                                                 : std::cout << "FALSE\n";
  }
  std::cout << "EVENBINARY == ODDBINARY\' : ";
  equals(corpus[4].first, complement(corpus[5].first)) ? std::cout << "TRUE\n"
                                                       : std::cout << "FALSE\n";

  std::cout << "EMPTYSTRING == EMPTYSTRING ∪ DENYALL : ";
  equals(_union(corpus[1].first, corpus[1].first),
         _union(corpus[1].first, corpus[0].first))
      ? std::cout << "TRUE\n"
      : std::cout << "FALSE\n";

  std::cout << "DENYALL\' == EVENBINARY ∪ NOTZERO : ";
  equals(complement(_union(corpus[0].first, corpus[0].first)),
         _union(corpus[4].first, corpus[7].first))
      ? std::cout << "TRUE\n"
      : std::cout << "FALSE\n";

  character c99(99), c('c', 1);

  std::cout << "ONLYCHAR(c) == ONLYCHAR(99)) : ";
  equals(givenChar(c), givenChar(c99)) ? std::cout << "TRUE\n"
                                       : std::cout << "FALSE\n";
  std::cout << SEPARATOR;

  return passed;
}

inline bool testOracle(Corpus corpus) {
  std::cout << SEPARATOR << "ORACLE TESTS\n" << SEPARATOR;
  for (int i = 0; i < corpus.nfas.size(); i++) {
    std::cout << corpus.nfas[i].second << '\n';
    for (int j = 0; j < corpus.traces[i].size(); j++) {
      for (auto e : corpus.traces[i][j]) {
        std::cout << " -> " << '[' << e.first << ']' << e.second;
      }
      oracle(corpus.nfas[i].first, corpus.traces[i][j]);
    }
    std::cout << SEPARATOR;
  }
  return true;
}

// Task 22
inline bool verifyWithEquals() {
  std::cout << "VERIFY WITH EQUALS\n" << SEPARATOR;

  character c0(0), c1(1);
  alphabet binary(std::vector<character>{c0, c1});

  DFA<int> denyAll([](int qi) { return qi; }, binary, 0,
                   [](int qi, character c) { return 0; },
                   [](int qi) { return 0; });
  DFA<int> acceptAll([](int qi) { return qi; }, binary, 1,
                     [](int qi, character c) { return 1; },
                     [](int qi) { return 1; });
  DFA<int> evenBinary([](int qi) { return qi == 0 || qi == 1; }, binary, 0,
                      [](int qi, character c) { return !(c == 0); },
                      [](int qi) { return qi == 0; });
  DFA<int> oddBinary([](int qi) { return qi == 0 || qi == 1; }, binary, 0,
                     [](int qi, character c) { return !(c == 0); },
                     [](int qi) { return qi == 1; });

  std::cout << "ODDBINARY' == EVENBINARY : ";
  equals(complement(oddBinary), evenBinary) ? std::cout << "Passed\n"
                                            : std::cout << "Failed\n";
  std::cout << "ODDBINARY ∪ EVENBINARY' == ACCEPTALL : ";
  equals(_union(oddBinary, evenBinary), _union(acceptAll, acceptAll))
      ? std::cout << "Passed\n"
      : std::cout << "Failed\n";
  std::cout << "ODDBINARY ∩ EVENBINARY' == DENYALL : ";
  equals(intersect(oddBinary, evenBinary), _union(denyAll, denyAll))
      ? std::cout << "Passed\n"
      : std::cout << "Failed\n";
  return true;
}

// Task 35
template <class State>
inline bool testCat(std::vector<std::pair<NFA<State>, std::string>> corpus) {
  return true;
}

// Task 37
template <class State>
inline bool testKleene(std::vector<std::pair<NFA<State>, std::string>> corpus) {

  character epsilon(-1), c0(0), c1(1), c2(2), a('a', 1), b('b', 1), e('e', 1),
      n('n', 1);
  alphabet binary(std::vector<character>{c0, c1});

  if (!(kleene(corpus[0].first)
            .accepts(string(binary, std::vector<character>{c1, c0, c1}))))
    return false;
  if (!(kleene(corpus[0].first)
            .accepts(string(binary, std::vector<character>{c1, c0, c1, c1}))))
    return false;
  if (!(kleene(corpus[0].first)
            .accepts(string(binary, std::vector<character>{c1, c1, c1, c1}))))
    return false;

  if (!(kleene(corpus[1].first)
            .accepts(string(binary, std::vector<character>{c1, c0, c0}))))
    return false;
  if (!(kleene(corpus[1].first)
            .accepts(string(binary,
                            std::vector<character>{c1, c0, c0, c1, c0, c0}))))
    return false;
  if (!(kleene(corpus[1].first)
            .accepts(string(binary,
                            std::vector<character>{c1, c0, c1, c1, c0, c1}))))
    return false;

  std::cout << "Kleene Tests : PASSED" << std::endl;

  return true;
}

// Task 39
template <class State>
inline bool testNFAToDFA(std::vector<std::pair<NFA<State>, std::string>> nfas) {

  auto uNFA = union_nfa(nfas[0].first, nfas[1].first);
  auto cNFA = cat(nfas[0].first, nfas[1].first);
  auto kNFA = kleene(nfas[0].first);

  character epsilon(-1), c0(0), c1(1), c2(2), a('a', 1), b('b', 1), e('e', 1),
      n('n', 1);
  alphabet binary(std::vector<character>{c0, c1});

  auto w = string(binary, std::vector<character>{c1, c0, c1});
  auto w1 = string(binary, std::vector<character>{c1, c0, c1, c1, c0, c1});
  auto w2 = string(binary,
                   std::vector<character>{c1, c0, c1, c1, c0, c1, c1, c0, c1});

  if (!(uNFA.accepts(w) == NFAtoDFA(uNFA).accepts(w)))
    return false;
  if (!(cNFA.accepts(w1) == NFAtoDFA(cNFA).accepts(w1)))
    return false;
  if (!(kNFA.accepts(w2) == NFAtoDFA(kNFA).accepts(w2)))
    return false;

  std::cout << "NFAtoDFA Tests : PASSED" << std::endl;

  return true;
}

// Task 40
template <class State>
inline bool
testNFAToDFAManually(std::vector<std::pair<NFA<State>, std::string>> corpus) {

  //    dfa1, dfa2, dfa3;

  character epsilon(-1), c0(0), c1(1), c2(2), a('a', 1), b('b', 1), e('e', 1),
      n('n', 1);

  alphabet binary(std::vector<character>{c0, c1});

  DFA<std::vector<int>> denyAllDFA(
      [](std::vector<int> qi) { return true; }, binary, std::vector<int>{0},
      [](std::vector<int> qi, character c) { return std::vector<int>{0}; },
      [](std::vector<int> qi) { return 0; });

  NFA<int> denyAllNFA([](int qi) { return qi; }, binary, 0,
                      [](int qi, character c) { return std::vector<int>{0}; },
                      [](int qi) { return 0; });

  DFA<std::vector<int>> emptyStringDFA(
      [](std::vector<int> qi) { return true; }, binary, std::vector<int>{1},
      [](std::vector<int> qi, character c) { return std::vector<int>{0}; },
      [](std::vector<int> qi) { return qi == std::vector<int>{1}; });

  NFA<int> emptyStringNFA(
      [](int qi) { return qi; }, binary, 1,
      [](int qi, character c) { return std::vector<int>{0}; },
      [](int qi) { return qi; });

  if (!(equals(denyAllDFA, NFAtoDFA(denyAllNFA))))
    return false;
  if (!(equals(emptyStringDFA, NFAtoDFA(emptyStringNFA))))
    return false;

  std::cout << "Manual NFAtoDFA Tests : PASSED" << std::endl;

  return true;
}

bool testTraceTree(Corpus corpus) {
  character epsilon(-1), c0(0), c1(1), c2(2), a('a', 1), b('b', 1), e('e', 1),
      n('n', 1);
  alphabet binary(std::vector<character>{c0, c1}),
      three(std::vector<character>{c0, c1, c2}),
      ben(std::vector<character>{b, e, n}), ab(std::vector<character>{a, b}),
      unary(std::vector<character>{c0});
  string s(binary, std::vector<character>{c0, c1, c0, c1, c0, c0});

  std::vector<string> strings = {
      string(binary, std::vector<character>{c0}),
      string(binary, std::vector<character>{c0, c1}),
      string(binary, std::vector<character>{c0, c1, c0}),
      string(binary, std::vector<character>{c0, c1, c0, c1}),
      string(binary, std::vector<character>{c0}),
      string(binary, std::vector<character>{c0, c1}),
      string(binary, std::vector<character>{c0, c1, c0}),
      string(binary, std::vector<character>{c0, c1, c0, c1}),
      string(binary, std::vector<character>{epsilon}),
      string(binary, std::vector<character>{epsilon, c0}),
      string(binary, std::vector<character>{epsilon, c0, c0}),
      string(binary, std::vector<character>{epsilon, c0, c0, c0}),

      string(ab, std::vector<character>{b}),
      string(ab, std::vector<character>{b, a}),
      string(ab, std::vector<character>{b, b, a}),
      string(ab, std::vector<character>{b, a, b, a, epsilon})};

  std::cout << "TRACE TREES\n" << SEPARATOR;

  for (int i = 0; i < corpus.nfas.size(); i++) {
    std::cout << corpus.nfas[i].second << '\n';
    for (int j = i * 4; j < i * 4 + 4; j++) {
      explore(corpus.nfas[i].first, strings[j]);
      std::cout << std::endl;
    }
    std::cout << SEPARATOR;
  }

  return true;
}

#endif
