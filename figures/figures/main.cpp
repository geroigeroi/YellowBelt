//
//  main.cpp
//  figures
//
//  Created by Andre on 24/12/20.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cmath>

using namespace std;

class Figure {
public:
    virtual string Name() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
};

class Triangle : public Figure {
public:
    Triangle(int sideA, int sideB, int sideC) {
        sideA_ = sideA;
        sideB_ = sideB;
        sideC_ = sideC;
    }
    string Name() override {
        return name;
    }
    double Perimeter() override {
        return sideA_ + sideB_ + sideC_;
    }
    double Area() override {
        double p = (double)(sideA_ + sideB_ + sideC_) / 2;
        return sqrt(p * (p - sideA_) * (p - sideB_) * (p - sideC_));
    }
private:
    const string name = "TRIANGLE";
    int sideA_, sideB_, sideC_;
};

class Rect : public Figure {
public:
    Rect(int length, int width) {
        length_ = length;
        width_ = width;
    }
    string Name() override {
        return name;
    }
    double Perimeter() override {
        return 2 * (length_ + width_);
    }
    double Area() override {
        return length_ * width_;
    }
private:
    const string name = "RECT";
    int length_, width_;
};

class Circle : public Figure {
public:
    Circle(int radius) {
        radius_ = radius;
    }
    string Name() override {
        return name;
    }
    double Perimeter() override {
        return 6.28 * radius_;
    }
    double Area() override {
        return 3.14 * radius_ * radius_;
    }
private:
    const string name = "CIRCLE";
    int radius_;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string nameFigure;
    is >> nameFigure;
    if (nameFigure == "CIRCLE") {
        int radius;
        is >> radius;
        shared_ptr<Figure> c;
        c = make_shared<Circle>(radius);
        return c;
        
    } else if (nameFigure == "RECT") {
        int length, width;
        is >> length >> width;
        shared_ptr<Figure> r;
        r = make_shared<Rect>(length, width);
        return r;
        
    } else {  // == "TRIANGE"
        int sideA, sideB, sideC;
        is >> sideA >> sideB >> sideC;
        shared_ptr<Figure> t;
        t = make_shared<Triangle>(sideA, sideB, sideC);
        return t;
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
      for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
          is >> ws;
          figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
          for (const auto& current_figure : figures) {
            cout << fixed << setprecision(3)
                 << current_figure->Name() << " "
                 << current_figure->Perimeter() << " "
                 << current_figure->Area() << endl;
          }
        }
      }
      return 0;
}
