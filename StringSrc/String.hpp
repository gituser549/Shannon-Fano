

#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>



class String {
private:
  char* str_;
  int capacity_;
  int size_;

public:
  String();
  String(const char* str);
  String(const String& str);
  String(String&& str) noexcept;
  ~String();
  void swap(String& str) noexcept;
  String& operator=(const String& str);
  String& operator=(String&& str) noexcept;
  bool operator==(const String& str) const;
  bool operator!=(const String& str) const;
  bool operator!() const;
  char& operator[](const int index);
  const char& operator[](const int index) const;
  String& operator+=(const char& value);
  String operator+(const char& value);
  String& operator+=(const String& str);
  String operator+(const String& str) const;
  const char* getCStr() const;
  friend std::ostream& operator<<(std::ostream& out, const String& str);
  friend std::istream& operator>>(std::istream& in, String& str);
  int length() const;
  String substr(int fir, int num) const;
  void reserve(int capacity);
};

int getLen(const char* str);

#endif
