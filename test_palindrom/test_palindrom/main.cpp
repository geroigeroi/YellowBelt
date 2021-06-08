//
//  main.cpp
//  test_palindrom
//
//  Created by Andre on 12/8/20.
//

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
    int sz;                         // Размер строки
    int mdl;                        // Значение середины строки
    sz = (int)str.size();
    mdl = sz / 2;
        for (int i = 0; i < mdl; ++i){
            if (str[i] == str[sz - 1]) {
                --sz;
            } else {
                return false;
            }
        }
    return true;
}


void TestCorrectPalindrom() {
    AssertEqual(IsPalindrom("wasitacaroracatisaw"), true);
}

void TestEmpty() {
    AssertEqual(IsPalindrom(""), true);
}

void TestOneChar() {
    AssertEqual(IsPalindrom("a"), true);
}

void TestWhitespace() {
    AssertEqual(IsPalindrom("able was I ere I saw elba"), true);
}

void TestFirstAndLastWhitespaces() {
    AssertEqual(IsPalindrom(" baoab "), true);
}

void TestFirstAndLastWhitespacesAndOneInside() {
    AssertEqual(IsPalindrom(" ba o ab "), true);
}

void TestOneCharOneWhitespace() {
    AssertEqual(IsPalindrom(" a b b a "), true);
}

void TestMoreThatOneWhitespace() {
    AssertEqual(IsPalindrom("  a  "), true);
}

void TestCase() {
    AssertEqual(IsPalindrom("Aba"), false);
}

void TestDigits() {
    AssertEqual(IsPalindrom("777778"), false);
}

void TestEqualChars() {
    AssertEqual(IsPalindrom("aaa"), true);
}
void TestCase2() {
    AssertEqual(IsPalindrom("Aa"), false);
}

void TestDoubleWhitespace() {
    AssertEqual(IsPalindrom(" "), true);
}

void TestSevens() {
    AssertEqual(IsPalindrom("777777"), false);
}

void TestWithComma() {
    AssertEqual(IsPalindrom(" , "), true);
}

void TestCyrillic() {
    AssertEqual(IsPalindrom("А РОЗА УПАЛА НА ЛАПУ АЗОРА"), true);
}

void TestAll() {
    AssertEqual(IsPalindrom(""),true);
    AssertEqual(IsPalindrom(" "),true);
    AssertEqual(IsPalindrom(" - - "),true);
    AssertEqual(IsPalindrom("s"),true);
    AssertEqual(IsPalindrom("mom"),true);
    AssertEqual(IsPalindrom("MoM"),true);
    AssertEqual(IsPalindrom("mOm"),true);
    AssertEqual(IsPalindrom("level"),true);
    AssertEqual(IsPalindrom("wasitacaroracatisaw"),true);
    AssertEqual(IsPalindrom("madam"),true);
    AssertEqual(IsPalindrom("ma d am"),true);
    AssertEqual(IsPalindrom("maasdsaam"),true);
    AssertEqual(IsPalindrom("asa"),true);
    AssertEqual(IsPalindrom("moM"),false);
    AssertEqual(IsPalindrom("ma dam"),false);
    AssertEqual(IsPalindrom(" asa"),false);
    AssertEqual(IsPalindrom("sa"),false);
    AssertEqual(IsPalindrom("as"),false);
    AssertEqual(IsPalindrom("s "),false);
    AssertEqual(IsPalindrom(" s"),false);
    Assert(IsPalindrom(""), "Is  palindrome");
    Assert(IsPalindrom(" "), "Is  palindrome");
    Assert(IsPalindrom("lool"), "Is  palindrome");
    Assert(IsPalindrom("o"), "Is  palindrome");
    Assert(IsPalindrom("1"), "Is  palindrome");
    Assert(!IsPalindrom("madaM"), "Not a palindrome");
    Assert(!IsPalindrom("leveL"), "Not a palindrome");
    Assert(!IsPalindrom("Level"), "Not a palindrome");
    Assert(!IsPalindrom("level "), "Not a palindrome");
    Assert(!IsPalindrom(" llevell"), "Not a palindrome");
    Assert(IsPalindrom("top pot"), " is palindrome");
    Assert(IsPalindrom("l e v e l"), "Is palindrome");
    Assert(IsPalindrom("l  e  v  e  l"), "Is palindrome");
    Assert(!IsPalindrom(" lev e  l   "), "Is not palindrome");
    Assert(!IsPalindrom("mada m"), "Is not palindrome");
    Assert(!IsPalindrom("   madam  "), "Is not palindrome");
    Assert(IsPalindrom("MADAM"), "Is  palindrome");
    Assert(IsPalindrom("o lol o"), "Is  palindrome");
    Assert(!IsPalindrom(" madam"), "Is not palindrome");
    Assert(!IsPalindrom(" madrydam"), "Is not palindrome");
    Assert(IsPalindrom("wasitacaroracatisaw"), "Is  palindrome");
    Assert(IsPalindrom("   tutneotmfmtoentut   "), "Is  palindrome");
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
    runner.RunTest(TestCorrectPalindrom, "CorrectPalindrom");
    runner.RunTest(TestEmpty, "TestEmpty");
    runner.RunTest(TestOneChar, "TestOneChar");
    runner.RunTest(TestWhitespace, "TestWhitespace");
    runner.RunTest(TestFirstAndLastWhitespaces, "TestFirstAndLastWhitespaces");
    runner.RunTest(TestFirstAndLastWhitespacesAndOneInside, "TestFirstAndLastWhitespacesAndOneInside");
    runner.RunTest(TestOneCharOneWhitespace, "TestOneCharOneWhitespace");
    runner.RunTest(TestMoreThatOneWhitespace, "TestMoreThatOneWhitespace");
    runner.RunTest(TestCase, "TestCase");
    runner.RunTest(TestDigits, "TestDigits");
    runner.RunTest(TestEqualChars, "TestEqualChars");
    runner.RunTest(TestCase2, "TestCase2");
    runner.RunTest(TestDoubleWhitespace, "TestDoubleWhitespace");
    runner.RunTest(TestSevens, "TestSevens");
    runner.RunTest(TestWithComma, "TestWithComma");
    runner.RunTest(TestAll, "TestAll");
    runner.RunTest(TestCyrillic, "TestCyrillic");
  return 0;
}
