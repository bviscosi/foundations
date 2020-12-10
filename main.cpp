#include "Corpus.hpp"
#include "Regex.hpp"
#include "functions.hpp"
#include "tests.hpp"

bool runTests(Corpus corpus);

int main(void) {
  Corpus corpus("default");
  character epsilon(-1), c0(0), c1(1), c2(2), a('a', 1), b('b', 1), e('e', 1),
      n('n', 1);

  alphabet binary(std::vector<character>{c0, c1});
  auto nfas = corpus.getNFAs();

  testNFAToDFA(nfas);
  testNFAToDFAManually(nfas);
  testKleene(nfas);

  Regex regex1 = Regex(new RE_Union(new RE_Char(c0), new RE_Char(c1)));
  regex1.print();

  std::cout << '\n';

  Regex regex2 = Regex(new RE_Union(new RE_Epsilon(), new RE_Char(c1)));
  regex2.print();

  std::cout << '\n';

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
  //  testEquals(dfas);
  //  verifyWithEquals();
  //  testOracle(corpus);
  //  testTraceTree(corpus);
  return true;
}
