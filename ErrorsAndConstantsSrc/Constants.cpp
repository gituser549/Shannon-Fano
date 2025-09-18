
#include "Constants.hpp"

// The text file extension
const String TEXT_FILE_EXTENSION = ".txt";

// The binary file extension
const String BIN_FILE_EXTENSION = ".bin";

// The amount of bits in one byte
const int BITS_PER_BYTE = 8;

// The fullness factor of HashTable
const double HASH_TABLE_FULLNESS_FACTOR = 0.7;

// The number of console arguments needed
const int AMOUNT_EXPECTED_ARGS = 5;

// The length of extension in file name
const int LENGTH_OF_EXT_IN_FILENAME = 4;

// The standard decoder table size
const int DECODER_TABLE_SIZE = 512;

// The default size of HashTable
const int DEFAULT_TABLE_SIZE = 20;

// The default amount of fnv offset basis for hash function FNV-1a
const unsigned long long FNV_OFFSET_BASIS = 1469598103934665603ULL;

// The default amount of fnv prime number for hash function FNV-1a
const unsigned long long FNV_PRIME = 1099511628211ULL;

// The basic capacity of String
const int STRING_BASIC_CAPACITY = 30;
