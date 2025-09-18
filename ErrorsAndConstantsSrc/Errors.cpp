
#include "Errors.hpp"



// The error when program can't open the file
const String ERROR_CANT_OPEN_FILE = "ERROR: can't open : ";

// The error when filename length is incorrect
const String ERROR_FILENAME_LENGTH =
    "ERROR: inccorect filename because of its length given : ";

// The error when length of file is incorrect
const String ERROR_FILE_LENGTH = "ERROR: you've given an empty file : ";

// The error when given file has incorrect extension
const String ERROR_FILE_EXT = "ERROR: error with extension : ";

// The error when too much console parameters were given
const String ERROR_TOO_MUCH_CONS_PARAM =
    "ERROR: you've given too much console params, their amount must be 4";

// The error when too few console parameters were given
const String ERROR_TOO_FEW_CONS_PARAM =
    "ERROR: you've given too few console params, their amount must be 4";

// The error when programmer destroyed program logic
const String ERROR_INCORRECT_USAGE_CONS_PARAM_EXC =
    "ERROR: you've destroyed program logic";

// The error when incorrect size was give to create a HashTable
const char* ERROR_BAD_SIZE = "ERROR: size must be >= 1";

// The error when fullness factor of HashTable has become too large
const char* ERROR_FULLNESS_FACTOR = "ERROR: fullness factor >= 0.7";

// The error when there is a try to do sth with empty HashTable
const char* ERROR_EMPTY_TABLE = "ERROR: empty table";

// The error when smb is trying to use nullptr as key or value in HashTable
const char* ERROR_STRING_MUST_BE_STRING =
    "ERROR: key and value cant be nullptrs";

// The error when programmer destroyed the logic of program
const char* ERROR_TABLE_OVERFLOW =
    "ERROR: you changed code and ruined fullness factor rule";

// The error when given element hasn't been found
const char* ERROR_INCORRECT_KEY = "ERROR: no value in table with such key";

// The error with incorrect symbol index
const char* ERROR_INCORRECT_INDEX = "ERROR: incorrect index given";

// The error with incorrect capacity
const char* ERROR_INCORRECT_CAPACITY =
    "ERROR: you can't reduce the capacity of string";

// The error when nullptr given instead of C-string
const char* ERROR_NULLPTR_INSTEAD_OF_STRING = "ERROR: nullptr isn't a C-string";
