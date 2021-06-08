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

void TestIsPalindrom() {
        AssertEqual(IsPalindrom(""),true, "empty");
        AssertEqual(IsPalindrom(" "),true, "double empty");
        AssertEqual(IsPalindrom(" - - "),true, " - - ");
        AssertEqual(IsPalindrom("s"),true, "s");
        AssertEqual(IsPalindrom("ccbbaamomaabbcc"),true, "ccbbaamomaabbcc");
        AssertEqual(IsPalindrom("ccbbaaMoMaabbcc"),true, "ccbbaaMoMaabbcc");
        AssertEqual(IsPalindrom("mOm"),true, "mOm");
        AssertEqual(IsPalindrom("level"),true, "level");
        AssertEqual(IsPalindrom("ccbbaawasitacaroracatisawaabbcc"),true, "ccbbaawasitacaroracatisawaabbcc");
        AssertEqual(IsPalindrom("madam"),true, "madam");
        AssertEqual(IsPalindrom("ccbbaamadamaabbcc"),true, "ccbbaamadamaabbcc");
        AssertEqual(IsPalindrom("ma d am"),true, "ma d am");
        AssertEqual(IsPalindrom("maasdsaam"),true, "maasdsaam");
        AssertEqual(IsPalindrom("asa"),true, "asa");
        AssertEqual(IsPalindrom("moM"),false, "moM");
        AssertEqual(IsPalindrom("ccbbaamoMaabbcc"),false, "ccbbaamoMaabbcc");
        AssertEqual(IsPalindrom("ccbbaamOmaabbcc"),true), "ccbbaamOmaabbcc";
        AssertEqual(IsPalindrom("ma dam"),false, "ma dam");
        AssertEqual(IsPalindrom(" ccbbaaasaaabbcc"),false, " ccbbaaasaaabbcc");
        AssertEqual(IsPalindrom("sa"),false, "sa");
        AssertEqual(IsPalindrom("as"),false, "as");
        AssertEqual(IsPalindrom("s "),false, "s ");
        AssertEqual(IsPalindrom("ccbbaaasaaabbcc "),false, "ccbbaaasaaabbcc ");
        AssertEqual(IsPalindrom(" s"),false, " s");
        AssertEqual(IsPalindrom("wasitacaroracatisaw"), true);
        AssertEqual(IsPalindrom("able was I ere I saw elba"), true);
        AssertEqual(IsPalindrom(" baoab "), true);
        AssertEqual(IsPalindrom(" ba o ab "), true);
        AssertEqual(IsPalindrom(" a b b a "), true);
        AssertEqual(IsPalindrom("  a  "), true);
        AssertEqual(IsPalindrom("Aba"), false);
        AssertEqual(IsPalindrom("777778"), false);
        AssertEqual(IsPalindrom("aaa"), true);
        AssertEqual(IsPalindrom("Aa"), false);
        AssertEqual(IsPalindrom(" "), true);
        AssertEqual(IsPalindrom("777777"), false);
        Assert(!IsPalindrom(" ABCCBA"), " ABCCBA");
  Assert(!IsPalindrom("ABCCBA "), "ABCCBA ");
  Assert(!IsPalindrom("ABCCB A"), "ABCCB A");
  Assert(!IsPalindrom("A BCCBA"), "A BCCBA");
  Assert(!IsPalindrom("AB CCBA"), "AB CCBA");
  Assert(!IsPalindrom("ABCC BA"), "ABCC BA");
  Assert(!IsPalindrom("AB CCBA"), "AB CCBA");
  Assert(!IsPalindrom("ABCcBA"), "ABCcBA");
  Assert(!IsPalindrom("ABC CbA"), "ABC CbA");
  Assert(!IsPalindrom("ABC cbA"), "ABC cbA");
  Assert(!IsPalindrom("wasitacaRoracatisaw"), "wasitacaRoracatisaw");
  Assert(!IsPalindrom("wasitacAroracatisaw"), "wasitacAroracatisaw");
  Assert(!IsPalindrom("wasitaCaroracatisaw"), "wasitaCaroracatisaw");
  Assert(!IsPalindrom("wasitAcaroracatisaw"), "wasitAcaroracatisaw");
  Assert(!IsPalindrom("wasiTacaroracatisaw"), "wasiTacaroracatisaw");
  Assert(!IsPalindrom("wasItacaroracatisaw"), "wasItacaroracatisaw");
  Assert(!IsPalindrom("waSitacaroracatisaw"), "waSitacaroracatisaw");
  Assert(!IsPalindrom("wAsitacaroracatisaw"), "wAsitacaroracatisaw");
  Assert(!IsPalindrom("wasitacaRracatisaw"), "wasitacaRoracatisaw");
  Assert(!IsPalindrom("wasitacArracatisaw"), "wasitacAroracatisaw");
  Assert(!IsPalindrom("wasitaCarracatisaw"), "wasitaCaroracatisaw");
  Assert(!IsPalindrom("wasitAcarracatisaw"), "wasitAcaroracatisaw");
  Assert(!IsPalindrom("wasiTacarracatisaw"), "wasiTacaroracatisaw");
  Assert(!IsPalindrom("wasItacarracatisaw"), "wasItacaroracatisaw");
  Assert(!IsPalindrom("waSitacarracatisaw"), "waSitacaroracatisaw");
  Assert(!IsPalindrom("wAsitacarracatisaw"), "wAsitacaroracatisaw");
  Assert(!IsPalindrom("ZBCDmadamDCBA"), "ABCDmadamDCBA");
  Assert(!IsPalindrom("ABCDmadamDCBZ"), "ABCDmadamDCBZ");
  Assert(IsPalindrom("madam"), "madam");
  Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
  Assert(IsPalindrom("a a"), "a a");
  Assert(IsPalindrom("a"), "TestSingle");
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
    runner.TestRunner(TestIsPalindrom, "TestIsPalindrom");
  return 0;
}
