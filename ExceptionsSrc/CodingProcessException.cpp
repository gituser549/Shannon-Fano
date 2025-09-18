
#include <fstream>

#include "CodingProcessException.hpp"
#include "Constants.hpp"
#include "Errors.hpp"



CodingProcessException::CodingProcessException(const String& fileName)
  : fileName_(fileName) {};



const String FileNameLengthException::what() const {
  return ERROR_FILENAME_LENGTH + fileName_;
}



const String FileLengthException::what() const {
  return ERROR_FILE_LENGTH + fileName_;
}



const String FileExtensionException::what() const {
  return ERROR_FILE_EXT + fileName_;
}



const String FileOpenningException::what() const {
  return ERROR_CANT_OPEN_FILE + fileName_;
}



ConsoleParametersException::ConsoleParametersException(int numConsoleParam)
  : amountConsoleParameters_(numConsoleParam) {};



const String ConsoleParametersException::what() const {
  if (amountConsoleParameters_ < AMOUNT_EXPECTED_ARGS) {
    return ERROR_TOO_FEW_CONS_PARAM;
  } else if (amountConsoleParameters_ > AMOUNT_EXPECTED_ARGS) {
    return ERROR_TOO_MUCH_CONS_PARAM;
  } else {
    return ERROR_INCORRECT_USAGE_CONS_PARAM_EXC;
  }
}



TextFileNameValidator::TextFileNameValidator(const String& textFileName)
  : textFileName_(textFileName) {
  operator()();
}



void TextFileNameValidator::operator()() const {
  if (textFileName_.length() <= LENGTH_OF_EXT_IN_FILENAME) {
    throw FileNameLengthException(textFileName_);
  } else if (textFileName_.substr(
                 textFileName_.length() - LENGTH_OF_EXT_IN_FILENAME,
                 LENGTH_OF_EXT_IN_FILENAME) != TEXT_FILE_EXTENSION) {
    throw FileExtensionException(textFileName_);
  }
}



BinFileNameValidator::BinFileNameValidator(const String& binFileName)
  : binFileName_(binFileName) {
  operator()();
}



void BinFileNameValidator::operator()() const {
  if (binFileName_.length() <= LENGTH_OF_EXT_IN_FILENAME) {
    throw FileNameLengthException(binFileName_);
  } else if (binFileName_.substr(
                 binFileName_.length() - LENGTH_OF_EXT_IN_FILENAME,
                 LENGTH_OF_EXT_IN_FILENAME) != BIN_FILE_EXTENSION) {
    throw FileExtensionException(binFileName_);
  }
}
