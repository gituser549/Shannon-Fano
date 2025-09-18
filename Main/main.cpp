#include <iostream>

#include "Coder.hpp"
#include "CodingProcessException.hpp"
#include "Constants.hpp"
#include "DeCoder.hpp"
#include "String.hpp"



int main(int argc, char* argv[]) {
  bool result = true;

  try {

    if (argc != AMOUNT_EXPECTED_ARGS) {
      throw ConsoleParametersException(argc);
    }

    String srcFileName = argv[1], binFileName = argv[2],
           decodeFileName = argv[3], rulesFileName = argv[4];

    Coder testCoder(srcFileName, binFileName, rulesFileName);
    testCoder();

    DeCoder testDeCoder(rulesFileName, binFileName, decodeFileName);
    testDeCoder();

    long long srcFileSize = getFileSize(srcFileName);
    long long binFileSize = getFileSize(binFileName);
    long long rulesFileSize = getFileSize(rulesFileName);

    std::cout << "Efficiency without rules file: "
              << 1 - static_cast<double>(binFileSize) / srcFileSize << "\n";
    std::cout << "Efficiency with rules file: "
              << 1 -
            static_cast<double>(binFileSize + rulesFileSize) / srcFileSize
              << "\n";
    std::cout << "Influence of rules file: "
              << static_cast<double>(rulesFileSize) / srcFileSize << "\n";
    std::cout << "Are source and decoded files equal: " << std::boolalpha
              << checkIdentity(srcFileName, decodeFileName) << "\n";

  } catch (const ConsoleParametersException& error) {
    std::cerr << error.what() << "\n";
    result = false;
  } catch (const CodingProcessException& error) {
    std::cerr << error.what() << "\n";
    result = false;
  } catch (const std::exception& error) {
    std::cerr << error.what() << "\n";
    result = false;
  }

  return (result) ? EXIT_SUCCESS : EXIT_FAILURE;
}
