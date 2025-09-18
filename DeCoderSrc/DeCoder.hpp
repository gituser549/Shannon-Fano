
#ifndef DECODER_HPP
#define DECODER_HPP

#include "HashTable.hpp"
#include "String.hpp"



class DeCoder {
private:
  String rulesFileName_;
  String binFileName_;
  String decodeFileName_;
  HashTable codeToLet_;
  int symbCounter_;

  void getRules();
  void decodeText();

public:
  DeCoder(const String& rulesFileName, const String& binFileName,
          const String& decodeFileName);
  DeCoder(const DeCoder&) = delete;
  DeCoder& operator=(const DeCoder&) = delete;
  DeCoder(DeCoder&&) = delete;
  DeCoder& operator=(DeCoder&&) = delete;
  void operator()();
};



bool checkIdentity(const String& firstFileName, const String& secondFileName);

#endif
