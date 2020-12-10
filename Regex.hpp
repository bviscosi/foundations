#ifndef REGEX_HPP
#define REGEX_HPP

#include "character.hpp"
#include "string.hpp"
#include <iostream>

class Regex {
public:
  Regex(){};
  Regex(Regex *next) : next(next){};
  Regex *next;
  virtual void print() {
    if (next != NULL)
      next->print();
  };
};

class RE_Empty : public Regex {
public:
  void print() override { std::cout << "\u00D8"; }
};

class RE_Epsilon : public Regex {
public:
  void print() override { std::cout << "\u03B5"; }
};

class RE_Char : public Regex {
public:
  RE_Char(character c) : c(c){};
  character c;
  void print() override { std::cout << c; }
};

class RE_Union : public Regex {
public:
  RE_Union(Regex *lhs, Regex *rhs) : lhs(lhs), rhs(rhs){};
  Regex *lhs;
  Regex *rhs;

  void print() override {
    lhs->print();
    std::cout << 'U';
    rhs->print();
  }
};

class RE_Star : public Regex {
public:
  RE_Star(Regex arg) : arg(arg){};
  Regex arg;
  void print() override {
    arg.print();
    std::cout << '*';
  }
};

class RE_Circ : public Regex {
public:
  RE_Circ(Regex lhs, Regex rhs) : lhs(lhs), rhs(rhs){};
  Regex lhs;
  Regex rhs;
  void print() override {
    lhs.print();
    std::cout << "\u25CB";
    rhs.print();
  }
};

#endif
