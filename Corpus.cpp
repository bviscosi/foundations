#include "Corpus.hpp"

Corpus::Corpus(std::string selector) {
  if (selector == "default") {
    character c0(0), c1(1), c2(2), b('b', 1), e('e', 1), n('n', 1);

    alphabet binary(std::vector<character>{c0, c1, c2});
    alphabet three(std::vector<character>{c0, c1, c2});
    alphabet ben(std::vector<character>{b, e, n});

    // TASK 5
    DFA<int> denyAll([](int qi) { return qi; }, binary, 0,
                     [](int qi, character c) { return 0; },
                     [](int qi) { return 0; });
    // TASK 6
    DFA<int> emptyString([](int qi) { return qi; }, binary, 1,
                         [](int qi, character c) { return 0; },
                         [](int qi) { return qi; });
    // TASK 7
    DFA<int> onlyChar = givenChar(c1);
    // Task 8
    DFA<int> evenLength([](int qi) { return qi; }, binary, 0,
                        [](int qi, character c) { return !qi; },
                        [](int qi) { return !qi; });

    DFA<int> evenBinary([](int qi) { return qi == 0 || qi == 1; }, binary, 0,
                        [](int qi, character c) { return !(c == 0); },
                        [](int qi) { return qi == 0; });

    DFA<int> oddBinary([](int qi) { return qi == 0 || qi == 1; }, binary, 0,
                       [](int qi, character c) { return !(c == 0); },
                       [](int qi) { return qi == 1; });

    DFA<int> notZero([](int qi) { return qi == 0 || qi == 1; }, binary, 0,
                     [](int qi, character c) { return !(c == 0) || qi != 0; },
                     [](int qi) { return qi == 1; });

    DFA<int> me([](int qi) { return qi == 0 || qi == 1 || qi == 2 || qi == 3; },
                ben, 0,
                [](int qi, character c) {
                  switch (qi) {
                  case (0):
                    return c == (int)'b' ? 1 : 0;
                  case (1):
                    return c == (int)'e' ? 2 : 0;
                  case (2):
                    return c == (int)'n' ? 3 : 0;
                  case (3):
                    return 3;
                  default:
                    return 4;
                  }
                },
                [](int qi) { return qi == 3; });

    c = {std::pair(denyAll, "DENYALL"),
         std::pair(emptyString, "EMPTYSTRING"),
         std::pair(onlyChar, "ONLYCHAR"),
         std::pair(evenLength, "EVENLENGTH"),
         std::pair(evenBinary, "EVENBINARY"),
         std::pair(oddBinary, "ODDBINARY"),
         std::pair(me, "ME"),
         std::pair(notZero, "NOTZERO")};
  }
}
