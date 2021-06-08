//
//  main.cpp
//  test_rational
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



void TestConstructorByDefault() {
    Rational rationalByDefault;
    AssertEqual(rationalByDefault.Numerator(), 0);
    AssertEqual(rationalByDefault.Denominator(), 1);
}

void TestReduction() {
    Rational rationalAllPositive(4, 6);
    AssertEqual(rationalAllPositive.Numerator(), 2);
    AssertEqual(rationalAllPositive.Denominator(), 3);
}

void TestPositiveNegative() {
    Rational rationalNegativeDenominator(4, -7);
    AssertEqual(rationalNegativeDenominator.Numerator(), -4);
    AssertEqual(rationalNegativeDenominator.Denominator(), 7);
    Rational rationalBothNegative(-5, -8);
    AssertEqual(rationalBothNegative.Numerator(), 5);
    AssertEqual(rationalBothNegative.Denominator(), 8);
}

void TestReductionWithPosNeg() {
    Rational rationalNegativeDenominator(6, -12);
    AssertEqual(rationalNegativeDenominator.Numerator(), -1);
    AssertEqual(rationalNegativeDenominator.Denominator(), 2);
    Rational rationalBothNegative(-3, -9);
    AssertEqual(rationalBothNegative.Numerator(), 1);
    AssertEqual(rationalBothNegative.Denominator(), 3);
}
void TestNumeratorIsZero() {
    Rational rationalNumeratorIsZero(0, 4);
    AssertEqual(rationalNumeratorIsZero.Denominator(), 1);
}


int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestConstructorByDefault, "TestConstructorByDefault");
    runner.RunTest(TestReduction, "TestReduction");
    runner.RunTest(TestPositiveNegative, "TestPositiveNegative");
    runner.RunTest(TestReductionWithPosNeg, "TestReductionWithPosNeg");
    runner.RunTest(TestNumeratorIsZero, "TestNumeratorIsZero");
    return 0;
}
