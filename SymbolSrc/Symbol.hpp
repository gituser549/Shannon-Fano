
#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include "String.hpp"



struct Symbol {
  unsigned char letter_;
  String code_;
  int amount_;
  Symbol();
  Symbol(unsigned char letter, int amount);
  Symbol(unsigned char letter, String code, int amount);
  Symbol(const Symbol& symbol);
};

#endif
