#ifndef CORPUS_HPP
#define CORPUS_HPP

#include "functions.hpp"

class Corpus {

public:
  Corpus(std::string selector);
  std::vector<std::pair<DFA<int>, std::string>> getDFAs() { return dfas; }
  bool isEmpty() { return !dfas.size() && !nfas.size(); }
  void add(std::pair<DFA<int>, std::string> dfa) { dfas.push_back(dfa); }
  void add(std::pair<NFA<int>, std::string> dfa) { nfas.push_back(dfa); }
  std::vector<std::pair<DFA<int>, std::string>> dfas;
  std::vector<std::pair<NFA<int>, std::string>> nfas;
  std::vector<std::vector<std::vector<std::pair<int, string>>>> traces;
  std::vector<std::vector<std::pair<int, string>>> n1_traces;
  std::vector<std::vector<std::pair<int, string>>> n2_traces;
  std::vector<std::vector<std::pair<int, string>>> n3_traces;
  std::vector<std::vector<std::pair<int, string>>> n4_traces;
  std::vector<std::vector<TraceTree<int>>> n1_tt;
  std::vector<std::vector<TraceTree<int>>> n2_tt;
  std::vector<std::vector<TraceTree<int>>> n3_tt;
  std::vector<std::vector<TraceTree<int>>> n4_tt;
};

#endif
