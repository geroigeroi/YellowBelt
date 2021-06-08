//
//  main.cpp
//  test_equation
//
//  Created by Andre on 12/7/20.
//

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cassert>

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

int LinealEquation(double b, double c) {
    if (b == 0) {  // 0x = -c  — корней нет
        return 0;
    }
    if (c == 0) {  // bx = 0  — один корень (x = 0)
        return 1;
    }
    return 1;  // Линейное уравнение имеет один действительный корень
}

int QuadraticEquation(double a, double b, double c) {
    double D = b * b - 4 * a * c;
    if (D > 0) {
        return 2;
    } else if (D == 0) {
        return 1;
    } else {  // D < 0
        return 0;
    }
}

int GetDistinctRealRootCount(double a, double b, double c) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
    if (a == 0) {  // Линейное уравнение
        return LinealEquation(b, c);
    } else {  // Квадратное уравнение
        return QuadraticEquation(a, b, c);
    }
}

void TestLineal() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "1 = 0 ==> корней нет");
    AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "1x = 0 ==> один корень");
}
void TestQuadratic() {
    AssertEqual(GetDistinctRealRootCount(1, 1, 0), 2, "ax^2 + bx = 0 ==> два корня");
    AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "ax^2 = 0  ==> один корень");
    AssertEqual(GetDistinctRealRootCount(1, 1, 1), 0, "ax^2 + bx + c = 0  ==> 0 корней");
}

int main() {
    std::cout << QuadraticEquation(1, 1, 1);
    TestRunner runner;
    runner.RunTest(TestLineal, "TestLineal");
    runner.RunTest(TestQuadratic, "TestQuadratic");
  // добавьте сюда свои тесты
  return 0;
}
