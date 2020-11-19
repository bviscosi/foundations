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
  std::vector<std::pair<DFA<int>, std::string>> dfas = corpus.getDFAs();
  alphabet letters("abcdefghijklmnopqrstuvwxyz", true);
  std::cout << SEPARATOR;
  // testLexi(letters);
  // testDFAs(dfas);
  // testExample(dfas);
  // testComplement(dfas);
  // testUnion(dfas);
  // testIntersect(dfas);
  // testSubset(dfas);
  testEquals(dfas);
  verifyWithEquals();
  testOracle(corpus);
  testTraceTree(corpus);
    return true;
}
