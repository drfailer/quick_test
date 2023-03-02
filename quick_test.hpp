#ifndef __TEST__
#define __TEST__
#include <iostream>
#include <string>
#define BEGIN_TEST_GRP(TEST_NAME) QuickTest::beginTestGrp(TEST_NAME, __LINE__)
#define END_TEST_GRP() QuickTest::endTestGrp()
#define FAILED QuickTest::hasFailures()
#define ASSERT(EXPR) QuickTest::assert(EXPR, __LINE__, #EXPR)
#define ASSERT_EQL(LEFT, RIGHT) QuickTest::assert_eql(LEFT, RIGHT, __LINE__)
#define BEGIN_TEST_FUNCTION(NAME)                                              \
  void NAME() {                                                                \
    QuickTest::initTestFunction(#NAME);
#define END_TEST_FUNCTION()                                                    \
  QuickTest::endTestFunction();                                                     \
  }
#define CALL(FN_NAME) FN_NAME();

class QuickTest {
private:
  static std::string currentFunName;
  static std::string currentGrpName;
  static int         nbTestFun;
  static int         nbTestGrp;
  static int         nbFailGrp;
  static int         nbFailFun;

public:
  static void initTestFunction(std::string name) {
    currentFunName = name;
    nbFailFun = 0;
    nbTestFun = 0;
    std::cout << "TEST_FUNCTION " << name << " ";
    for (int i = 0; i < 64 - name.size(); ++i) {
      std::cout << "-";
    }
    std::cout << std::endl;
  }

  static void endTestFunction() {
    QuickTest::functionLine();
    QuickTest::report(currentFunName, nbTestFun, nbFailFun);
    QuickTest::functionLine();
    currentFunName = "";
  }

  static void beginTestGrp(std::string grpName, int line) {
    currentGrpName = grpName;
    nbTestGrp = 0;
    nbFailGrp = 0;
    nbTestGrp = 0;
    nbTestFun++;
    std::cout << "..........GRP: " << grpName << std::endl;
  }

  static void endTestGrp() {
    if (nbFailGrp > 0) {
      nbFailFun++;
    }
    std::cout << "..........";
    QuickTest::report(currentGrpName, nbTestGrp, nbFailGrp);
    currentGrpName = "";
  }

  static void assert(bool result, int line, std::string expr) {
    if (!result) {
      std::cout << "\033[0;31m";
      std::cout << line << " - ERROR: " << expr << std::endl;
      std::cout << "\033[0m"; // back to normal
    }
    updateCounters(result);
  }

  // note: this one is a problem
  // 1. you can have an error on type difference
  // 2. won't compile if operator<< is undefined for T
  template <typename T> static void assert_eql(T left, T right, int line) {
    bool result = left == right;

    if (!result) {
      std::cout << "\033[0;31m";
      std::cout << line << " - ERROR: " << left << " == " << right << std::endl;
      std::cout << "\033[0m"; // back to normal
    }
    updateCounters(result);
  }

  static bool hasFailures() { return nbFailGrp > 0; }

  QuickTest() = default;
  ~QuickTest() = default;

private:
  static void functionLine() {
    for (int i = 0; i < 79 - currentFunName.size(); ++i) {
      std::cout << "-";
    }
    std::cout << " " << currentFunName << std::endl;
  }

  static void report(std::string name, int nbTest, int nbFail) {
    std::cout << "result: " << name << std::endl;
    std::cout << "\t";
    if (nbTest > nbFail)
      std::cout << "\033[0;32m";
    std::cout << nbTest - nbFail << " passed\033[0m / ";
    if (nbFailGrp > 0)
      std::cout << "\033[0;31m";
    std::cout << nbFail << " failed\033[0m"
              << " (" << nbTest << ")" << std::endl;
  }

  static void updateCounters(bool result) {
    if (currentFunName == "") {   // not in a function
      if (currentGrpName != "") { // in a group
        if (!result)
          nbFailGrp++;
        nbTestGrp++;
      }
    } else {                      // in a function
      if (currentGrpName != "") { // in a group
        if (!result)
          nbFailGrp++;
        nbTestGrp++;
      } else { // not in a group
        if (!result)
          nbFailFun++;
        nbTestFun++;
      }
    }
  }
};

#endif
