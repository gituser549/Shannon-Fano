
#ifndef ERRORS_HPP
#define ERRORS_HPP

#include "String.hpp"



// The error when program can't open the file
extern const String ERROR_CANT_OPEN_FILE;

// The error when filename length is incorrect
extern const String ERROR_FILENAME_LENGTH;

// The error when length of file is incorrect
extern const String ERROR_FILE_LENGTH;

// The error when given file has incorrect extension
extern const String ERROR_FILE_EXT;

// The error when too much console parameters were given
extern const String ERROR_TOO_MUCH_CONS_PARAM;

// The error when too few console parameters were given
extern const String ERROR_TOO_FEW_CONS_PARAM;

// The error when programmer destroyed program logic
extern const String ERROR_INCORRECT_USAGE_CONS_PARAM_EXC;

// The error when incorrect size was give to create a HashTable
extern const char* ERROR_BAD_SIZE;

// The error when fullness factor of HashTable has become too large
extern const char* ERROR_FULLNESS_FACTOR;

// The error when there is a try to do sth with empty HashTable
extern const char* ERROR_EMPTY_TABLE;

// The error when smb is trying to use nullptr as key or value in HashTable
extern const char* ERROR_STRING_MUST_BE_STRING;

// The error when programmer destroyed the logic of program
extern const char* ERROR_TABLE_OVERFLOW;

// The error when given element hasn't been found
extern const char* ERROR_INCORRECT_KEY;

// The error with incorrect symbol index
extern const char* ERROR_INCORRECT_INDEX;

// The error with incorrect capacity
extern const char* ERROR_INCORRECT_CAPACITY;

// The error when nullptr given instead of C-string
extern const char* ERROR_NULLPTR_INSTEAD_OF_STRING;



#endif
