
#include <iostream>
#include <utility>

#include "Constants.hpp"
#include "Errors.hpp"
#include "String.hpp"



String::String() : capacity_(STRING_BASIC_CAPACITY), size_(0) {
  str_ = new char[capacity_ + 1];
  str_[0] = '\0';
}



String::String(const char* str) : size_(getLen(str)) {
  capacity_ =
      (size_ * 2 > STRING_BASIC_CAPACITY) ? size_ * 2 : STRING_BASIC_CAPACITY;
  str_ = new char[capacity_ + 1];
  for (int i = 0; i < size_; i++) {
    str_[i] = str[i];
  }
  str_[size_] = '\0';
}



String::String(const String& str) {
  size_ = str.size_;
  capacity_ =
      (size_ * 2 > STRING_BASIC_CAPACITY) ? size_ * 2 : STRING_BASIC_CAPACITY;
  str_ = new char[capacity_ + 1];
  for (int i = 0; i < size_; i++) {
    str_[i] = str.str_[i];
  }
  str_[size_] = '\0';
}



void String::swap(String& str) noexcept {
  std::swap(str_, str.str_);
  std::swap(size_, str.size_);
  std::swap(capacity_, str.capacity_);
}



String::~String() {
  delete[] str_;
}



String::String(String&& str) noexcept
  : str_(str.str_), size_(str.size_), capacity_(str.capacity_) {
  str.str_ = nullptr;
  str.size_ = 0;
  str.capacity_ = 0;
}



String& String::operator=(const String& str) {
  if (this != &str) {
    String temp(str);
    swap(temp);
  }
  return *this;
}



String& String::operator=(String&& str) noexcept {
  if (this != &str) {
    swap(str);
  }
  return *this;
}



bool String::operator==(const String& str) const {
  if (size_ != str.size_) {
    return false;
  } else {
    for (int i = 0; i < size_; i++) {
      if (str_[i] != str.str_[i]) {
        return false;
      }
    }
  }
  return true;
}



bool String::operator!=(const String& str) const {
  return !(*this == str);
}



bool String::operator!() const {
  return size_ == 0;
}



char& String::operator[](const int index) {
  if (index >= size_ || index < 0) {
    throw std::logic_error(ERROR_INCORRECT_INDEX);
  }
  return str_[index];
}



const char& String::operator[](const int index) const {
  if (index >= size_ || index < 0) {
    throw std::logic_error(ERROR_INCORRECT_INDEX);
  }
  return str_[index];
}



void String::reserve(int capacity) {
  if (capacity_ >= capacity) {
    throw std::logic_error(ERROR_INCORRECT_CAPACITY);
  }
  capacity_ = capacity;
  char* newStr = new char[capacity + 1];
  for (int i = 0; i < size_; i++) {
    newStr[i] = str_[i];
  }
  newStr[size_] = '\0';
  delete[] str_;
  str_ = newStr;
}



String& String::operator+=(const char& symb) {
  if ((size_ + 1) > capacity_) {
    reserve(capacity_ * 2);
  }
  str_[size_] = symb;
  str_[size_ + 1] = '\0';
  size_++;
  return *this;
}



String String::operator+(const char& symb) {
  String temp(*this);
  temp += symb;
  return temp;
}



String& String::operator+=(const String& str) {
  if ((size_ + str.size_) > capacity_) {
    reserve((size_ + str.size_) * 2);
  }
  for (int i = 0; i < str.size_; i++) {
    str_[size_ + i] = str.str_[i];
  }
  str_[size_ + str.size_] = '\0';
  size_ += str.size_;
  return *this;
}



String String::operator+(const String& str) const {
  String temp(*this);
  temp += str;
  return temp;
}



std::ostream& operator<<(std::ostream& out, const String& str) {
  for (int i = 0; i < str.size_; i++) {
    out << str[i];
  }
  return out;
}



std::istream& operator>>(std::istream& in, String& str) {
  str = String();
  int symb = in.get();
  while (symb != ' ' && symb != '\n' && symb != '\t' && symb != '\r' &&
         symb != EOF) {
    str += static_cast<char>(symb);
    symb = in.get();
  }
  if (symb != EOF) {
    in.putback(symb);
  }
  return in;
}



int String::length() const {
  return size_;
}



const char* String::getCStr() const {
  return str_;
}



String String::substr(int fir, int num) const {
  if (fir < 0 || (fir + num - 1) >= length()) {
    throw std::logic_error(ERROR_INCORRECT_INDEX);
  }

  String newStr;
  for (int i = fir; i < (fir + num); i++) {
    newStr += (*this)[i];
  }

  return newStr;
}



int getLen(const char* str) {
  if (str == nullptr) {
    throw std::logic_error(ERROR_NULLPTR_INSTEAD_OF_STRING);
  }
  int counter = 0;
  while (*str++) {
    counter++;
  }
  return counter;
}
