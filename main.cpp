#include "Corpus.hpp"
#include "functions.hpp"
#include "tests.hpp"

bool runTests(Corpus corpus);

int main(void) {
  Corpus corpus("default");
  runTests(corpus);
  return 0;
}

bool runTests(Corpus corpus) {
  std::vector<std::pair<DFA<int>, std::string>> c = corpus.getDFAs();
  // alphabet letters("abcdefghijklmnopqrstuvwxyz", true);
  std::cout << SEPARATOR;
  // testLexi(letters);
  // testCorpus(c);
  testExample(c);
  testComplement(c);
  testUnion(c);
  testIntersect(c);
  testSubset(c);
  std::cout << SEPARATOR;
  return true;
}
