
#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>

#include "Constants.hpp"
#include "String.hpp"



class HashTable {

private:
  struct Record {
    String key_;
    char value_;
    bool occupied_;
    bool deleted_;
    Record();
    Record(const String& key, const char& value);
    Record(const Record&) = delete;
    Record(Record&&) = delete;
    Record& operator=(const Record&) = delete;
    Record& operator=(Record&&) = delete;
  };

  int size_;
  int number_;
  Record* table_;

  int getHash(const String& key) const;
  bool insert(const Record& data);
  bool remove(const int removeInd);
  int searchInTableFunc(const String& key) const;

public:
  HashTable(int size = DEFAULT_TABLE_SIZE);
  HashTable(const HashTable&) = delete;
  HashTable(HashTable&&) = delete;
  HashTable& operator=(const HashTable&&) = delete;
  HashTable& operator=(HashTable&&) = delete;
  ~HashTable();
  bool insert(const String& key, const char& value);
  bool remove(const String& key);
  bool searchInTable(const String& key) const;
  bool isEmpty() const;
  friend std::ostream& operator<<(std::ostream& out, const HashTable& table);
  friend std::ostream& operator<<(std::ostream& out, const Record& record);
  char& operator[](const String& key);
  const char& operator[](const String& key) const;
  void eraseElements();
};

#endif
