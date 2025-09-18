
#include "Coder.hpp"
#include "CodingProcessException.hpp"
#include "Constants.hpp"
#include "Errors.hpp"
#include <fstream>



Coder::Coder(const String& inFileName, const String& binFileName,
             const String& rulesFileName)
  : inputFileName_(inFileName),
    binFileName_(binFileName),
    rulesFileName_(rulesFileName),
    prefix_{0},
    symbCounter_(0) {
  TextFileNameValidator(String(inputFileName_));
  BinFileNameValidator(String(binFileName_));
  TextFileNameValidator(String(rulesFileName_));
}



int Coder::getLetsAndSort() {
  std::ifstream inputFileThread(inputFileName_.getCStr());

  if (!inputFileThread.is_open()) {
    throw FileOpenningException(inputFileName_);
  }

  int numEls = 0;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    letsByAmounts_[i] = Symbol(i, 0);
  }

  int symb = inputFileThread.get();

  while (symb != EOF) {
    if (symb >= 0 && symb <= 255) {
      if (letsByAmounts_[symb].amount_ == 0) {
        numEls++;
      }
      letsByAmounts_[symb].amount_++;
    }
    symb = inputFileThread.get();
  }

  inputFileThread.close();

  for (int i = 1; i < ALPHABET_SIZE; i++) {
    for (int j = i;
         j > 0 && letsByAmounts_[j].amount_ > letsByAmounts_[j - 1].amount_;
         j--) {
      Symbol temp(letsByAmounts_[j - 1]);
      letsByAmounts_[j - 1] = letsByAmounts_[j];
      letsByAmounts_[j] = temp;
    }
  }

  return numEls;
}



void Coder::getPrefixes(const int& begin, const int& end) {
  for (int i = begin; i <= end; i++) {
    prefix_[i] = 0;
  }

  prefix_[begin] = letsByAmounts_[begin].amount_;

  for (int i = begin + 1; i <= end; i++) {
    prefix_[i] = prefix_[i - 1] + letsByAmounts_[i].amount_;
  }
}



void Coder::getCodes(const int& begin, const int& end, const String& code) {
  if (end > begin) {
    getPrefixes(begin, end);
    int bestPos = begin;
    int bestDelta = std::abs(prefix_[end] - 2 * prefix_[begin]);
    for (int i = begin + 1; i < end; i++) {
      if (std::abs(prefix_[end] - 2 * prefix_[i]) < bestDelta) {
        bestDelta = std::abs(prefix_[end] - 2 * prefix_[i]);
        bestPos = i;
      }
    }
    getCodes(begin, bestPos, code + "0");
    getCodes(bestPos + 1, end, code + "1");
  } else if (begin == end) {
    letsByAmounts_[begin].code_ = (code.length()) ? code : "1";
  }
}



void Coder::codeText() {
  int size = getLetsAndSort();

  if (size == 0) {
    throw FileLengthException(inputFileName_);
  }

  getCodes(0, size - 1);

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    letToCode_[i] = String();
  }

  symbCounter_ = 0;
  for (int i = 0; i < size; i++) {
        letToCode_[letsByAmounts_[i].letter_] = letsByAmounts_[i].code_;
        symbCounter_ += letsByAmounts_[i].amount_;
  }
  
  std::ifstream inputFileThread(inputFileName_.getCStr());
  if (!inputFileThread.is_open()) {
    throw FileOpenningException(inputFileName_);
  }

  std::ofstream binFileThread(binFileName_.getCStr(),
                              std::ios::out | std::ios::binary |
                                  std::ios::trunc);
  if (!binFileThread.is_open()) {
    throw FileOpenningException(binFileName_);
  }

  unsigned char byte = 0;
  int bitCount = 0;
  int symb = inputFileThread.get();

  while (symb != EOF) {
    // Get code of current symbol
    const String& code = letToCode_[symb];
    for (int i = 0; i < code.length(); i++) {
      // Get digit on i position in code
      char bitChar = code[i];

      // We move current byte left by one bit
      byte <<= 1;

      if (bitChar == '1') {
        // We compare the lowest (nearly appeared after previous action) with 1 (00000001) and get next bit in code
        byte |= 1;
      }

      bitCount++;

      // If full byte was collected, write it to binary file
      if (bitCount == BITS_PER_BYTE) {
        binFileThread.write(reinterpret_cast<const char*>(&byte), 1);
        // Refresh byte and bit counter variables to get the next byte
        byte = 0;
        bitCount = 0;
      }
    }
    // Get next byte
    symb = inputFileThread.get();
  }

  // If we have non-written bits, we need to write them to file in correct form
  if (bitCount > 0) {
    // We move current byte (with bitCount real bits) left by some bits to get correct byte
    byte <<= (BITS_PER_BYTE - bitCount);
    binFileThread.write(reinterpret_cast<const char*>(&byte), 1);
  }

  inputFileThread.close();
  binFileThread.close();
}



void Coder::exportRules() {
  std::ofstream rulesFileThread(rulesFileName_.getCStr(),
                                std::ios::out | std::ios::trunc);
  if (!rulesFileThread.is_open()) {
    throw FileOpenningException(rulesFileName_);
  }

  rulesFileThread << symbCounter_ << "\n";

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (letToCode_[i] != String()) {
      rulesFileThread << letToCode_[i] << " " << static_cast<char>(i) << "\n";
    }
  }
}



void Coder::operator()() {
  codeText();
  exportRules();
}



long long getFileSize(const String& fileName) {
  if (fileName.length() <= LENGTH_OF_EXT_IN_FILENAME) {
    throw FileNameLengthException(fileName);
  }

  std::ifstream fileThreadToCheck(fileName.getCStr(),
                                  std::ios::binary | std::ios::ate);

  if (!fileThreadToCheck.is_open()) {
    throw FileOpenningException(fileName);
  }

  long long result = static_cast<long long>(fileThreadToCheck.tellg());
  fileThreadToCheck.close();
  return result;
}
