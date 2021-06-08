//
//  main.cpp
//  test_person
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

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно
  
  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }
  return name;
}

class Person {
public:
  // Вы можете вставлять сюда различные реализации класса,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  void ChangeFirstName(int year, const string& first_name) {
      first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
      last_names[year] = last_name;
  }
  string GetFullName(int year) {
      // получаем имя и фамилию по состоянию на год year
      const string first_name = FindNameByYear(first_names, year);
      const string last_name = FindNameByYear(last_names, year);
      
      // если и имя, и фамилия неизвестны
      if (first_name.empty() && last_name.empty()) {
          return "Incognito";
          
          // если неизвестно только имя
      } else if (first_name.empty()) {
          return last_name + " with unknown first name";
          
          // если неизвестна только фамилия
      } else if (last_name.empty()) {
          return first_name + " with unknown last name";
          
          // если известны и имя, и фамилия
      } else {
          return first_name + " " + last_name;
      }
  }
private:
    map<int, string> first_names;
    map<int, string> last_names;
};

void TestChangeFirstname () {
    {
        std::map<int, std::string> mapAdded;
        mapAdded[1900] = "Ivan";
        Person objAdded;
        objAdded.ChangeFirstName(1900, "Ivan");
        AssertEqual(objAdded, mapAdded);
    }
}

int main() {
    TestRunner runner;
    Person odjAdded;
    runner.RunTest(TestChangeFirstname, "TestChangeFirstname");
  // добавьте сюда свои тесты
  return 0;
}
