
#include <fstream>

#include "CodingProcessException.hpp"
#include "Constants.hpp"
#include "DeCoder.hpp"
#include "Errors.hpp"



DeCoder::DeCoder(const String& rulesFileName, const String& binFileName,
                 const String& decodeFileName)
  : rulesFileName_(rulesFileName),
    binFileName_(binFileName),
    decodeFileName_(decodeFileName),
    codeToLet_(DECODER_TABLE_SIZE),
    symbCounter_(0) {
  TextFileNameValidator(String(rulesFileName_));
  BinFileNameValidator(String(binFileName_));
  TextFileNameValidator(String(decodeFileName_));
}



void DeCoder::getRules() {
  std::ifstream rulesFileThread(rulesFileName_.getCStr());
  if (!rulesFileThread.is_open()) {
    throw FileOpenningException(rulesFileName_);
  }

  codeToLet_.eraseElements();

  symbCounter_ = 0;

  // Get number of symbol in source file
  rulesFileThread >> symbCounter_;

  // Ignore '\n'
  rulesFileThread.ignore();

  String code;

  // Get first symbol from thread
  int symb = rulesFileThread.get();

  // Cycle condition guarantees that last gotten symbol is correct
  while (symb != EOF) {
    // Return last symbol to thread because it is correct
    rulesFileThread.putback(symb);
    // Get code from thread
    rulesFileThread >> code;
    // Ignore space - separator
    rulesFileThread.ignore();
    // Get coded symbol (byte)
    symb = rulesFileThread.get();
    // Fill decode table
    codeToLet_[code] = symb;
    // Ignore space ('\n' symbol)
    rulesFileThread.ignore();
    // Get next symbol to check whether the thread is in correct state
    symb = rulesFileThread.get();
  }

  rulesFileThread.close();
}



void DeCoder::decodeText() {
  std::ifstream binFileThread(binFileName_.getCStr(),
                              std::ios::in | std::ios::binary);
  if (!binFileThread.is_open()) {
    throw FileOpenningException(binFileName_);
  }
  std::ofstream decodeFileThread(decodeFileName_.getCStr(),
                                 std::ios::out | std::ios::trunc);
  if (!decodeFileThread.is_open()) {
    throw FileOpenningException(decodeFileName_);
  }

  String code = String();
  unsigned char byte = 0;
  int byteAsInt = binFileThread.get();

  while (byteAsInt != EOF && symbCounter_ > 0) {
    byte = static_cast<unsigned char>(byteAsInt);
    // Parsing every gotten byte digit by digit
    for (int i = 7; i >= 0 && symbCounter_ > 0; --i) {
      // To get needed bit move current byte right by i positions, and needed bit appear as the lowest bit
      // Use the bitwise operator AND with 1 (00000001) to get exactly the lowest bit
      int bit = (byte >> i) & 1;
      if (bit) {
        code += "1";
      } else {
        code += "0";
      }
      // If code that was gotten on current step is in decode table, put needed symbol to decoded file
      if (codeToLet_.searchInTable(code)) {
        decodeFileThread.put(codeToLet_[code]);
        // Reduce symbols counter because one symbol has been decoded
        // To refresh the current code chain assign empty string to code variable
        code = String();
        symbCounter_--;
      }
    }
    // Read next byte
    byteAsInt = binFileThread.get();
  }

  binFileThread.close();
  decodeFileThread.close();
}



void DeCoder::operator()() {
  getRules();
  decodeText();
}



bool checkIdentity(const String& firstFileName, const String& secondFileName) {
  TextFileNameValidator(String(firstFileName));
  TextFileNameValidator(String(secondFileName));

  std::ifstream firstFileThread(firstFileName.getCStr(),
                                std::ios::in | std::ios::binary);
  std::ifstream secondFileThread(secondFileName.getCStr(),
                                 std::ios::in | std::ios::binary);

  if (!firstFileThread.is_open() || !secondFileThread.is_open()) {
    throw FileOpenningException(!firstFileThread.is_open() ? firstFileName
                                                           : secondFileName);
  }

  bool result = true;

  char symbFirThread = firstFileThread.get(),
       symbSecThread = secondFileThread.get();
  while (result && (symbFirThread != EOF || symbSecThread != EOF)) {
    if (symbFirThread != symbSecThread) {
      result = false;
    }
    symbFirThread = firstFileThread.get();
    symbSecThread = secondFileThread.get();
  }

  if (symbFirThread != symbSecThread) {
    result = false;
  }

  return result;
}
