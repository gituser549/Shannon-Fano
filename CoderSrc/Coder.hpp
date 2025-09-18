
#ifndef CODER_HPP
#define CODER_HPP

#include "Constants.hpp"

#include "String.hpp"
#include "Symbol.hpp"



class Coder {
private:
  String inputFileName_;
  String binFileName_;
  String rulesFileName_;
  int prefix_[ALPHABET_SIZE];
  Symbol letsByAmounts_[ALPHABET_SIZE];
  String letToCode_[ALPHABET_SIZE];
  int symbCounter_;

  int getLetsAndSort();
  void getPrefixes(const int& begin, const int& end);
  void getCodes(const int& begin, const int& end,
                const String& code = String());
  void codeText();
  void exportRules();

public:
  Coder(const String& inFileName, const String& binFileName,
        const String& rulesFileName);
  Coder(const Coder&) = delete;
  Coder& operator=(const Coder&) = delete;
  Coder(Coder&&) = delete;
  Coder& operator=(Coder&&) = delete;
  void operator()();
};



long long getFileSize(const String& fileName);

#endif
