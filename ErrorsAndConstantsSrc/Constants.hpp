
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "String.hpp"



// The size of alphabet
static const int ALPHABET_SIZE = 256;

// The amount of bits in one byte
extern const int BITS_PER_BYTE;

// The fullness factor of HashTable
extern const double HASH_TABLE_FULLNESS_FACTOR;

// The number of console arguments needed
extern const int AMOUNT_EXPECTED_ARGS;

// The length of extension in file name
extern const int LENGTH_OF_EXT_IN_FILENAME;

// The standard decoder table size
extern const int DECODER_TABLE_SIZE;

// The default size of HashTable
extern const int DEFAULT_TABLE_SIZE;

// The default amount of fnv offset basis for hash function FNV-1a
extern const unsigned long long FNV_OFFSET_BASIS;

// The default amount of fnv prime number for hash function FNV-1a
extern const unsigned long long FNV_PRIME;

// The text file extension
extern const String TEXT_FILE_EXTENSION;

// The binary file extension
extern const String BIN_FILE_EXTENSION;

// The basic capacity of String
extern const int STRING_BASIC_CAPACITY;


#endif
