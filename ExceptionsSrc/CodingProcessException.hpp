

#ifndef CODING_PROCESS_EXCEPTION_HPP
#define CODING_PROCESS_EXCEPTION_HPP

#include "String.hpp"



class CodingProcessException {
protected:
  String fileName_;

public:
  CodingProcessException(const String& fileName);
  virtual const String what() const = 0;
  virtual ~CodingProcessException() = default;
};



class FileNameLengthException : public CodingProcessException {
public:
  using CodingProcessException::CodingProcessException;
  const String what() const;
};



class FileLengthException : public CodingProcessException {
public:
  using CodingProcessException::CodingProcessException;
  const String what() const;
};



class FileExtensionException : public CodingProcessException {
public:
  using CodingProcessException::CodingProcessException;
  const String what() const;
};



class FileOpenningException : public CodingProcessException {
public:
  using CodingProcessException::CodingProcessException;
  const String what() const;
};



class ConsoleParametersException {
private:
  int amountConsoleParameters_;

public:
  ConsoleParametersException(int numConsoleParam);
  const String what() const;
};



class TextFileNameValidator {
private:
  String textFileName_;

public:
  TextFileNameValidator(const String& textFileName);
  void operator()() const;
};



class BinFileNameValidator {
private:
  String binFileName_;

public:
  BinFileNameValidator(const String& binFileName);
  void operator()() const;
};

#endif
