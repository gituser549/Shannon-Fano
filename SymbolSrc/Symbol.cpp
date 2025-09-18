
#include "Symbol.hpp"



Symbol::Symbol() : letter_('\0'), code_(String()), amount_(0) {};



Symbol::Symbol(unsigned char letter, int amount)
  : letter_(letter), code_(String()), amount_(amount) {};



Symbol::Symbol(unsigned char letter, String code, int amount)
  : letter_(letter), code_(code), amount_(amount) {};



Symbol::Symbol(const Symbol& symbol)
  : letter_(symbol.letter_), code_(symbol.code_), amount_(symbol.amount_) {};
