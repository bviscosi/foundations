#include "Corpus.hpp"

Corpus::Corpus(std::string selector) {
  if (selector == "default") {
    character epsilon(-1), c0(0), c1(1), c2(2), a('a', 1), b('b', 1), e('e', 1),
        n('n', 1);

    alphabet binary(std::vector<character>{c0, c1});
    alphabet three(std::vector<character>{c0, c1, c2});
    alphabet ben(std::vector<character>{b, e, n});
    alphabet ab(std::vector<character>{a, b});
    alphabet unary(std::vector<character>{c0});

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

    dfas = {std::pair(denyAll, "DENYALL"),
            std::pair(emptyString, "EMPTYSTRING"),
            std::pair(onlyChar, "ONLYCHAR"),
            std::pair(evenLength, "EVENLENGTH"),
            std::pair(evenBinary, "EVENBINARY"),
            std::pair(oddBinary, "ODDBINARY"),
            std::pair(me, "ME"),
            std::pair(notZero, "NOTZERO")};

    NFA<int> n1([](int qi) { return qi == 1 || qi == 2 || qi == 3 || qi == 4; },
                binary, 1,
                [](int qi, character c) {
                  switch (qi) {
                  case (1):
                    if (c == 0)
                      return std::vector<int>{1};
                    else if (c == 1)
                      return std::vector<int>{1, 2};
                    else
                      return std::vector<int>{};
                  case (2):
                    if (c == 0 || c == -1)
                      return std::vector<int>{3};
                    else
                      return std::vector<int>{};
                  case (3):
                    if (c == 1)
                      return std::vector<int>{4};
                    else
                      return std::vector<int>{};
                  case (4):
                    return std::vector<int>{4};
                  default:
                    return std::vector<int>{};
                  }
                },
                [](int qi) { return qi == 4; });

    NFA<int> n2([](int qi) { return qi == 1 || qi == 2 || qi == 3 || qi == 4; },
                binary, 1,
                [](int qi, character c) {
                  switch (qi) {
                  case (1):
                    if (c == 0)
                      return std::vector<int>{1};
                    else if (c == 1)
                      return std::vector<int>{1, 2};
                    else
                      return std::vector<int>{};
                  case (2):
                    if (c == 0 || c == 1)
                      return std::vector<int>{3};
                    else
                      return std::vector<int>{};
                  case (3):
                    if (c == 0 || c == 1)
                      return std::vector<int>{4};
                    else
                      return std::vector<int>{};
                  case (4):
                    return std::vector<int>{4};
                  default:
                    return std::vector<int>{};
                  }
                },
                [](int qi) { return qi == 4; });

    NFA<int> n3(
        [](int qi) {
          return qi == 1 || qi == 2 || qi == 3 || qi == 4 || qi == 5 || qi == 6;
        },
        unary, 1,
        [](int qi, character c) {
          switch (qi) {
          case (1):
            if (c == -1)
              return std::vector<int>{2, 3};
            else
              return std::vector<int>{};
          case (2):
            if (c == 0)
              return std::vector<int>{4};
            else
              return std::vector<int>{};
          case (3):
            if (c == 0)
              return std::vector<int>{5};
            else
              return std::vector<int>{};
          case (4):
            if (c == 0)
              return std::vector<int>{2};
            else
              return std::vector<int>{};
          case (5):
            if (c == 0)
              return std::vector<int>{6};
            else
              return std::vector<int>{};
          case (6):
            if (c == 0)
              return std::vector<int>{3};
            else
              return std::vector<int>{};
          default:
            return std::vector<int>{};
          }
        },
        [](int qi) { return (qi == 2 || qi == 3); });

    NFA<int> n4([](int qi) { return qi == 1 || qi == 2 || qi == 3; }, ab, 1,
                [](int qi, character c) {
                  switch (qi) {
                  case (1):
                    if (c == -1)
                      return std::vector<int>{3};
                    if (c == 'b')
                      return std::vector<int>{2};
                    else
                      return std::vector<int>{};
                  case (2):
                    if (c == 'b')
                      return std::vector<int>{3};
                    else if (c == 'a')
                      return std::vector<int>{2, 3};
                    else
                      return std::vector<int>{};
                  case (3):
                    if (c == 'a')
                      return std::vector<int>{1};
                    else
                      return std::vector<int>{};
                  default:
                    return std::vector<int>{};
                  }
                },
                [](int qi) { return qi == 1; });

    nfas = {std::pair(n1, "N1"), std::pair(n2, "N2"), std::pair(n3, "N3"),
            std::pair(n4, "N4")};

    n1_traces = {

        {std::pair(1, string(binary, std::vector<character>{c0})),
         std::pair(1, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1})),
         std::pair(1, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1})),
         std::pair(2, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1, c0, c1})),
         std::pair(2, string(binary, std::vector<character>{c0, c1})),
         std::pair(3, string(binary, std::vector<character>{c1})),
         std::pair(4, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1, c0, c1})),
         std::pair(1, string(binary, std::vector<character>{c0, c1})),
         std::pair(1, string(binary, std::vector<character>{c1})),
         std::pair(1, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1, epsilon, c1})),
         std::pair(2, string(binary, std::vector<character>{epsilon, c1})),
         std::pair(3, string(binary, std::vector<character>{c1})),
         std::pair(4, string(binary))}

    };

    n2_traces = {
        {std::pair(1, string(binary, std::vector<character>{c0})),
         std::pair(1, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1})),
         std::pair(1, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1})),
         std::pair(2, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1, c1, c1})),
         std::pair(2, string(binary, std::vector<character>{c1, c1})),
         std::pair(3, string(binary, std::vector<character>{c1})),
         std::pair(4, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1, c1, c1})),
         std::pair(1, string(binary, std::vector<character>{c1, c1})),
         std::pair(1, string(binary, std::vector<character>{c1})),
         std::pair(1, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{c1, c0, c0})),
         std::pair(2, string(binary, std::vector<character>{c0, c0})),
         std::pair(3, string(binary, std::vector<character>{c0})),
         std::pair(4, string(binary))}

    };

    n3_traces = {

        {std::pair(1, string(binary, std::vector<character>{epsilon})),
         std::pair(2, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{epsilon})),
         std::pair(3, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{epsilon, c0, c0})),
         std::pair(2, string(binary, std::vector<character>{c0, c0})),
         std::pair(4, string(binary, std::vector<character>{c0})),
         std::pair(2, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{epsilon, c0, c0})),
         std::pair(3, string(binary, std::vector<character>{c0, c0})),
         std::pair(5, string(binary, std::vector<character>{c0})),
         std::pair(6, string(binary))},

        {std::pair(1,
                   string(binary, std::vector<character>{epsilon, c0, c0, c0})),
         std::pair(2, string(binary, std::vector<character>{c0, c0, c0})),
         std::pair(4, string(binary, std::vector<character>{c0, c0})),
         std::pair(2, string(binary, std::vector<character>{c0})),
         std::pair(4, string(binary))},

        {std::pair(1,
                   string(binary, std::vector<character>{epsilon, c0, c0, c0})),
         std::pair(3, string(binary, std::vector<character>{c0, c0, c0})),
         std::pair(5, string(binary, std::vector<character>{c0, c0})),
         std::pair(6, string(binary, std::vector<character>{c0})),
         std::pair(3, string(binary))}

    };

    n4_traces = {

        {std::pair(1, string(binary, std::vector<character>{epsilon})),
         std::pair(3, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{b})),
         std::pair(2, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{epsilon, a})),
         std::pair(3, string(binary, std::vector<character>{a})),
         std::pair(1, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{b, a})),
         std::pair(2, string(binary, std::vector<character>{a})),
         std::pair(3, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{b, a})),
         std::pair(2, string(binary, std::vector<character>{a})),
         std::pair(2, string(binary))},

        {std::pair(1, string(binary, std::vector<character>{b, a, a})),
         std::pair(2, string(binary, std::vector<character>{a, a})),
         std::pair(3, string(binary, std::vector<character>{a})),
         std::pair(1, string(binary))}

    };

    traces.push_back(n1_traces);
    traces.push_back(n2_traces);
    traces.push_back(n3_traces);
    traces.push_back(n4_traces);
  }
}
