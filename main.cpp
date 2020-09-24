#include "DFA.hpp"
#include "alphabet.hpp"
#include <cmath>
#include <optional>

DFA givenChar(character c);
string lexi(alphabet a, int n);
bool accepts(DFA dfa, string w);
void test(DFA dfa);

int main(void) {

  character c0(0);
  character c1(1);

  std::vector<character> bits;
  bits.push_back(c0);
  bits.push_back(c1);
  alphabet binary(bits);

  // accepts no strings - TASK 5
  DFA denyAll([](int qi) { return qi; }, binary, 0,
              [](int qi, character c) { return 0; }, [](int qi) { return 0; });

  // accepts only the empty string - TASK 6
  DFA emptyString([](int qi) { return qi; }, binary, 1,
                  [](int qi, character c) { return 0; },
                  [](int qi) { return qi; });

  // accepts only given char - TASK 7
  DFA onlyChar = givenChar(c1);

  // accepts only strings of even length
  DFA evenLength([](int qi) { return qi; }, binary, 0,
                 [](int qi, character c) { return !qi; },
                 [](int qi) { return !qi; });

  // accepts only even binary numbers
  DFA evenBinary([](int qi) { return qi == 0 || qi == 1; }, binary, 0,
                 [](int qi, character c) { return !(c == 0); },
                 [](int qi) { return qi == 0; });

  // accepts only odd binary numbers
  DFA oddBinary([](int qi) { return qi == 0 || qi == 1; }, binary, 0,
                [](int qi, character c) { return !(c == 0); },
                [](int qi) { return qi == 1; });

  // accepts only non-zero numbers
  DFA notZero([](int qi) { return qi == 0 || qi == 1; }, binary, 0,
              [](int qi, character c) { return !(c == 0) || qi != 0; },
              [](int qi) { return qi == 1; });

  std::cout << "\n-------------------------------------------\n" << std::endl;
  std::cout << "NOT ZERO\n";
  test(notZero);
  std::cout << "ODD BINARY\n";
  test(oddBinary);
  std::cout << "EVEN BINARY\n";
  test(evenBinary);
  std::cout << "EVEN LENGTH\n";
  test(evenLength);
  std::cout << "ONLY GIVEN CHAR (TESING USING 1)\n";
  test(onlyChar);
  std::cout << "REJECT ALL\n";
  test(denyAll);
  std::cout << "ONLY EMPTY STRING\n";
  test(emptyString);
  std::cout << "FIRST 32 NTH STRINGS \n";
  std::cout << "\n-------------------------------------------\n" << std::endl;
  for (int i = 0; i < 32; i++)
    std::cout << lexi(binary, i) << std::endl;

  return 0;
}

DFA givenChar(character in) {

  std::vector<character> chars;
  character zero(0);
  chars.push_back(in);
  chars.push_back(zero);
  alphabet alpha(chars);

  DFA givenChar([](int qi) { return qi == 0 || qi == 1 || qi == 2; }, alpha, 0,
                [in](int qi, character c) {
                  switch (qi) {
                  case (0):
                    return c == in ? 1 : 2;
                  case (1):
                    return 2;
                  default:
                    return 2;
                  }
                },
                [](int qi) { return qi == 1; });
  return givenChar;
}

string lexi(alphabet a, int n) {

  string s(a);
  int layer = 0;
  int y = 0;
  int partition;
  if (n == 0) {
    std::cout << "\u03B5";
  } else if (n <= a.size()) {
    s.add(a.a[n - 1]);
  } else {

    int i = 1;
    while (i <= n) {
      n -= pow(a.size(), layer);
      i *= a.size();
      layer++;
    }

    partition = pow(a.size(), layer);

    int x = partition;
    for (int j = 0; j < layer; j++) {
      partition /= a.size();
      x = partition;
      y = 0;
      while (x <= n) {
        x += partition;
        n -= partition;
        y++;
      }
      s.add(a.a[y]);
    }
  }

  return s;
}

bool accepts(DFA dfa, string w) {
  bool accepted = dfa.accepts(w);
  std::cout << w << "   ---   ";
  if (accepted)
    std::cout << "Accepted";
  else
    std::cout << "Rejected";
  std::cout << " : ";
  dfa.trace();
  return accepted;
}

void test(DFA dfa) {
  std::cout << "\n-------------------------------------------\n" << std::endl;
  alphabet E = dfa.getAlpha();
  for (int i = 0; i < 12; i++) {
    accepts(dfa, lexi(E, i));
  }
  std::cout << "\n-------------------------------------------\n" << std::endl;
}
