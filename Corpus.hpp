#ifndef CORPUS_HPP
#define CORPUS_HPP

#include "functions.hpp"

class Corpus {

public:
  Corpus(std::string selector);
  std::vector<std::pair<DFA<int>, std::string>> getDFAs() { return c; }
  bool isEmpty() { return !c.size(); }
  void add(std::pair<DFA<int>, std::string> dfa) { c.push_back(dfa); }

private:
  std::vector<std::pair<DFA<int>, std::string>> c;
};

#endif
