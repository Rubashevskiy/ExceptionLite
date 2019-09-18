#include <iostream>
#include "../src/ExceptionLite/exceptionlite.h"

void thirdFunction() {
  throw ERROR("Test throw!!!");
}

void secondFunction() {
  thirdFunction();
}

void firstFunction() {
  secondFunction();
}

void test() {
  firstFunction();
}

int main(int argc, char *argv[]) {
  try {
    std::cout << "Test LiteException" << std::endl;
    test();
  }
  catch(ExceptionLite &e)
  {
    std::cerr << "Error Message: "  << e.what() << std::endl;
    std::cerr << "Error Function: "  << e.function() << std::endl;
    std::cerr << "Error line: " << e.line() << std::endl;
    std::cerr << "Error file: " << e.file() << std::endl;
    std::cerr << "Error trace: "  << std::endl << e.trace() << std::endl;
  }
  return 0;
}
