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

void testAll(){
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

AssertEqual(IsPalindrom(""),true);
AssertEqual(IsPalindrom(" "),true);
AssertEqual(IsPalindrom(" - - "),true);
AssertEqual(IsPalindrom("s"),true);
AssertEqual(IsPalindrom("mom"),true);
AssertEqual(IsPalindrom("MoM"),true);
AssertEqual(IsPalindrom("mOm"),true);
AssertEqual(IsPalindrom("level"),true);
AssertEqual(IsPalindrom("wasitacaroracatisawwasitacaroracatisaw"),true);
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
}

int main() {
  TestRunner runner;
  // добавьте сюда свои тесты
  runner.RunTest(testAll, "testAll");
  return 0;
}
