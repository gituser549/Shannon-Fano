
#include <iostream>

#include "Errors.hpp"
#include "HashTable.hpp"



HashTable::Record::Record()
  : key_(String()), value_('\0'), occupied_(false), deleted_(false) {};



HashTable::Record::Record(const String& key, const char& value)
  : occupied_(true), deleted_(false) {
  if (key.length() == 0) {
    throw std::logic_error(ERROR_STRING_MUST_BE_STRING);
  }
  key_ = key;
  value_ = value;
}



HashTable::HashTable(int size) : number_(0) {
  if (size < 1) {
    throw std::underflow_error(ERROR_BAD_SIZE);
  } else {
    size_ = size;
    table_ = new Record[size];
  }
}



HashTable::~HashTable() {
  delete[] table_;
}



int HashTable::getHash(const String& key) const {
  if (key.length() == 0) {
    throw std::logic_error(ERROR_STRING_MUST_BE_STRING);
  }

  unsigned long long hashSum = FNV_OFFSET_BASIS;
  for (int i = 0; i < key.length(); i++) {
    hashSum ^= key[i];
    hashSum *= FNV_PRIME;
  }
  return static_cast<int>(hashSum % size_);
}



int HashTable::searchInTableFunc(const String& key) const {
  if (key.length() == 0) {
    throw std::logic_error(ERROR_STRING_MUST_BE_STRING);
  }
  bool end = false;
  bool error = false;
  bool* checkedEls = new bool[size_];
  int numChecked = 0;

  for (int i = 0; i < size_; i++) {
    checkedEls[i] = false;
  }

  int hash = getHash(key);
  int curIndex = hash;
  int lastToInsert = -1;

  for (int i = 0; !end; i++) {
    curIndex = (hash + i * i) % size_;
    if (table_[curIndex].occupied_ && (key == table_[curIndex].key_)) {
      end = true;
    } else if ((!table_[curIndex].occupied_ && !table_[curIndex].deleted_) ||
               numChecked == number_) {
      end = true;
      error = true;
    } else if (!checkedEls[curIndex]) {
      checkedEls[curIndex] = true;
      numChecked++;
    }

    if (!table_[curIndex].occupied_) {
      lastToInsert = curIndex;
    }
  }

  delete[] checkedEls;

  if (error && lastToInsert == -1) {
    throw std::overflow_error(ERROR_TABLE_OVERFLOW);
  }

  return (error ? lastToInsert : curIndex);
}



bool HashTable::searchInTable(const String& key) const {
  return table_[searchInTableFunc(key)].key_ == key;
}



bool HashTable::insert(const Record& data) {
  if ((static_cast<double>(number_) / size_) >= ALPHABET_SIZE) {
    throw std::overflow_error(ERROR_FULLNESS_FACTOR);
  } else if (data.key_.length() == 0) {
    throw std::logic_error(ERROR_STRING_MUST_BE_STRING);
  }

  int insIndex = searchInTableFunc(data.key_);
  bool inserted = false;

  if (!table_[insIndex].occupied_) {
    table_[insIndex].key_ = data.key_;
    table_[insIndex].value_ = data.value_;
    table_[insIndex].occupied_ = true;
    table_[insIndex].deleted_ = false;
    number_++;
    inserted = true;
  }

  return inserted;
}



bool HashTable::insert(const String& key, const char& value) {
  if ((static_cast<double>(number_) / size_) >= ALPHABET_SIZE) {
    throw std::overflow_error(ERROR_FULLNESS_FACTOR);
  } else if (key.length() == 0) {
    throw std::logic_error(ERROR_STRING_MUST_BE_STRING);
  }
  return insert(HashTable::Record(key, value));
}



bool HashTable::remove(const int removeIndex) {
  bool deleted = false;

  if (table_[removeIndex].occupied_) {
    table_[removeIndex].key_ = String();
    table_[removeIndex].value_ = '\0';
    table_[removeIndex].occupied_ = false;
    table_[removeIndex].deleted_ = true;
    number_--;
    deleted = true;
  }

  return deleted;
}



bool HashTable::remove(const String& key) {
  if (isEmpty()) {
    throw std::logic_error(ERROR_EMPTY_TABLE);
  }
  return remove(searchInTableFunc(key));
}



std::ostream& operator<<(std::ostream& out, const HashTable& table) {
  if (table.isEmpty()) {
    throw std::length_error(ERROR_EMPTY_TABLE);
  }

  for (int i = 0; i < table.size_; i++) {
    if (table.table_[i].occupied_) {
      out << table.table_[i] << "\n";
    }
  }
  return out;
}



char& HashTable::operator[](const String& key) {
  if (key.length() == 0) {
    throw std::logic_error(ERROR_STRING_MUST_BE_STRING);
  }
  int searchRes = searchInTableFunc(key);
  double fullnessFactor = static_cast<double>(number_) / size_;
  if (table_[searchRes].key_ != key && fullnessFactor < ALPHABET_SIZE) {
    table_[searchRes].key_ = key;
    table_[searchRes].value_ = '\0';
    table_[searchRes].occupied_ = true;
    table_[searchRes].deleted_ = false;
    number_++;
  } else if (!table_[searchRes].occupied_ &&
             fullnessFactor >= HASH_TABLE_FULLNESS_FACTOR) {
    throw std::overflow_error(ERROR_FULLNESS_FACTOR);
  }
  return table_[searchRes].value_;
}



const char& HashTable::operator[](const String& key) const {
  if (key.length() == 0) {
    throw std::logic_error(ERROR_STRING_MUST_BE_STRING);
  }
  int searchRes = searchInTableFunc(key);
  if (table_[searchRes].key_ != key) {
    throw std::logic_error(ERROR_INCORRECT_KEY);
  }
  return table_[searchRes].value_;
}



bool HashTable::isEmpty() const {
  return number_ == 0;
}



void HashTable::eraseElements() {
  for (int i = 0; number_ && i < size_; i++) {
    if (table_[i].occupied_) {
      table_[i].key_ = String();
      table_[i].value_ = '\0';
      table_[i].occupied_ = false;
      table_[i].deleted_ = true;
      number_--;
    }
  }
}



std::ostream& operator<<(std::ostream& out, const HashTable::Record& record) {
  out << "[" << record.key_ << "] : " << record.value_;
  return out;
}
