//
//  main.cpp
//  refactoring
//
//  Created by Andre on 24/12/20.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human(const string& t = "human", const string& n = "humanName") : Type_(t), Name_(n) {}
    virtual void TypeAndName(const string& Type_, const string& Name_) const {
        cout << Type_ << " " << Name_;
    }
    virtual void Walk(const string& destination) const {
        TypeAndName(Type_, Name_);
        cout << " walks to: " << destination << endl;
    }
public:
    const string Type_;
    const string Name_;
};

class Student : public Human {
public:
    Student(const string& name, const string& favouriteSong) : Human("Student", name) {
        name_ = name;
        favouriteSong_ = favouriteSong;
    }
    void Learn() const {
        TypeAndName(Type_, Name_);
        cout << " learns" << endl;
    }
    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }
    void SingSong() const {
        TypeAndName(Type_, Name_);
        cout << " sings a song: " << favouriteSong_ << endl;
    }
private:
    string name_;
    string favouriteSong_;
};

class Teacher : public Human {
public:
    Teacher(const string& name, const string& subject) : Human("Teacher", name) {
        name_ = name;
        subject_ = subject;
    }
    void Teach() const {
        TypeAndName(Type_, Name_);
        cout << " teaches: " << subject_ << endl;
    }
private:
    string subject_;
    string name_;
};

class Policeman : public Human {
public:
    Policeman(const string& name) : Human("Policeman", name) {
        name_ = name;
    }
    void Check(const Human& h) const {
        TypeAndName(Type_, Name_);
        cout << " checks " << h.Type_ << ". " <<  h.Type_ << "'s name is: " << h.Name_ << endl;
    }
private:
    string name_;
};

void VisitPlaces(const Human& h, const vector<string>& places) {
    for (auto p : places) {
        h.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    vector<string> dest = {"Moscow", "London"};
    VisitPlaces(t, dest);
    p.Check(s);
    VisitPlaces(s, dest);
    
    return 0;
}
