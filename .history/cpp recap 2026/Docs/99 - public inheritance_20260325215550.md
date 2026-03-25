# 99 - Public Inheritance in C++

## What is Public Inheritance?
Public inheritance is the most commonly used form of inheritance in C++. It establishes an "is-a" relationship between the derived class and the base class. All public members of the base class become public in the derived class, and protected members remain protected.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Animal {
private:
    string id;           // Private - not accessible in derived class
protected:
    string name;         // Protected - accessible in derived class
    int age;             // Protected - accessible in derived class
public:
    string species;      // Public - accessible everywhere
    
    Animal(string n, int a, string s) : name(n), age(a), species(s) {
        id = "ANM" + to_string(rand());
        cout << "Animal constructor called for " << name << endl;
    }
    
    void eat() {
        cout << name << " is eating" << endl;
    }
    
    void sleep() {
        cout << name << " is sleeping" << endl;
    }
    
    virtual void makeSound() const {
        cout << name << " makes a sound" << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Species: " << species << endl;
    }
    
    virtual ~Animal() {
        cout << "Animal destructor called for " << name << endl;
    }
};

// Derived class with public inheritance
class Dog : public Animal {
private:
    string breed;
    string favoriteToy;
    
public:
    Dog(string n, int a, string b, string toy) 
        : Animal(n, a, "Canine"), breed(b), favoriteToy(toy) {
        cout << "Dog constructor called for " << name << endl;
    }
    
    // Override base class virtual function
    void makeSound() const override {
        cout << name << " says: Woof! Woof!" << endl;
    }
    
    // Dog-specific methods
    void bark() {
        cout << name << " barks loudly!" << endl;
    }
    
    void fetch() {
        cout << name << " fetches the " << favoriteToy << endl;
    }
    
    void wagTail() {
        cout << name << " wags tail happily" << endl;
    }
    
    void display() const {
        Animal::display();
        cout << "Breed: " << breed << ", Favorite Toy: " << favoriteToy << endl;
    }
    
    ~Dog() {
        cout << "Dog destructor called for " << name << endl;
    }
};

int main() {
    Dog dog("Buddy", 3, "Golden Retriever", "ball");
    
    cout << "\n=== Accessing Members ===" << endl;
    // Public members of Animal accessible
    dog.species = "Canine";
    cout << "Species: " << dog.species << endl;
    
    // Protected members not accessible from outside
    // dog.name = "Max";  // Error! name is protected
    
    cout << "\n=== Calling Methods ===" << endl;
    dog.eat();           // Inherited from Animal
    dog.sleep();         // Inherited from Animal
    dog.makeSound();     // Overridden in Dog
    dog.bark();          // Dog's own method
    dog.fetch();         // Dog's own method
    dog.wagTail();       // Dog's own method
    
    cout << "\n=== Display Info ===" << endl;
    dog.display();
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### animal.h
```cpp
#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <cstdlib>
using namespace std;

class Animal {
private:
    string id;
protected:
    string name;
    int age;
public:
    string species;
    
    Animal(string n, int a, string s);
    void eat();
    void sleep();
    virtual void makeSound() const;
    void display() const;
    virtual ~Animal();
};

#endif
```

### animal.cpp
```cpp
#include "animal.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Animal::Animal(string n, int a, string s) : name(n), age(a), species(s) {
    id = "ANM" + to_string(rand());
    cout << "Animal constructor called for " << name << endl;
}

void Animal::eat() {
    cout << name << " is eating" << endl;
}

void Animal::sleep() {
    cout << name << " is sleeping" << endl;
}

void Animal::makeSound() const {
    cout << name << " makes a sound" << endl;
}

void Animal::display() const {
    cout << "Name: " << name << ", Age: " << age << ", Species: " << species << endl;
}

Animal::~Animal() {
    cout << "Animal destructor called for " << name << endl;
}
```

### dog.h
```cpp
#ifndef DOG_H
#define DOG_H

#include "animal.h"
#include <string>
using namespace std;

class Dog : public Animal {
private:
    string breed;
    string favoriteToy;
    
public:
    Dog(string n, int a, string b, string toy);
    void makeSound() const override;
    void bark();
    void fetch();
    void wagTail();
    void display() const;
    ~Dog();
};

#endif
```

### dog.cpp
```cpp
#include "dog.h"
#include <iostream>
using namespace std;

Dog::Dog(string n, int a, string b, string toy) 
    : Animal(n, a, "Canine"), breed(b), favoriteToy(toy) {
    cout << "Dog constructor called for " << name << endl;
}

void Dog::makeSound() const {
    cout << name << " says: Woof! Woof!" << endl;
}

void Dog::bark() {
    cout << name << " barks loudly!" << endl;
}

void Dog::fetch() {
    cout << name << " fetches the " << favoriteToy << endl;
}

void Dog::wagTail() {
    cout << name << " wags tail happily" << endl;
}

void Dog::display() const {
    Animal::display();
    cout << "Breed: " << breed << ", Favorite Toy: " << favoriteToy << endl;
}

Dog::~Dog() {
    cout << "Dog destructor called for " << name << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "dog.h"
using namespace std;

int main() {
    Dog dog("Buddy", 3, "Golden Retriever", "ball");
    
    dog.eat();
    dog.makeSound();
    dog.bark();
    dog.fetch();
    dog.display();
    
    return 0;
}
```

## Public Inheritance Access Specifiers

```cpp
#include <iostream>
using namespace std;

class Base {
private:
    int privateVar = 1;
protected:
    int protectedVar = 2;
public:
    int publicVar = 3;
    
    void showBase() {
        cout << "Base: private=" << privateVar 
             << ", protected=" << protectedVar 
             << ", public=" << publicVar << endl;
    }
};

class Derived : public Base {
public:
    void showDerived() {
        // cout << privateVar;  // Error! Private not accessible
        cout << "Derived: protected=" << protectedVar << endl;  // Accessible
        cout << "Derived: public=" << publicVar << endl;        // Accessible
    }
};

int main() {
    Base b;
    Derived d;
    
    // b.privateVar;   // Error! Private
    // b.protectedVar; // Error! Protected
    b.publicVar = 10;   // OK
    
    d.showDerived();
    d.publicVar = 20;    // OK - public member
    
    return 0;
}
```

## Practical Examples

### Example 1: Shape Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Shape {
protected:
    string color;
    double area;
    
public:
    Shape(string c) : color(c), area(0) {
        cout << "Shape created: " << color << endl;
    }
    
    virtual void calculateArea() = 0;
    
    virtual void display() const {
        cout << "Color: " << color << ", Area: " << area << endl;
    }
    
    string getColor() const { return color; }
    double getArea() const { return area; }
    
    virtual ~Shape() {
        cout << "Shape destroyed: " << color << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(string c, double r) : Shape(c), radius(r) {
        cout << "Circle created: radius=" << radius << endl;
        calculateArea();
    }
    
    void calculateArea() override {
        area = M_PI * radius * radius;
    }
    
    double getRadius() const { return radius; }
    
    void display() const override {
        cout << "Circle (r=" << radius << ") - ";
        Shape::display();
    }
    
    ~Circle() {
        cout << "Circle destroyed" << endl;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;
    
public:
    Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {
        cout << "Rectangle created: " << length << "x" << width << endl;
        calculateArea();
    }
    
    void calculateArea() override {
        area = length * width;
    }
    
    double getLength() const { return length; }
    double getWidth() const { return width; }
    
    void display() const override {
        cout << "Rectangle (" << length << "x" << width << ") - ";
        Shape::display();
    }
    
    ~Rectangle() {
        cout << "Rectangle destroyed" << endl;
    }
};

class Triangle : public Shape {
private:
    double base;
    double height;
    
public:
    Triangle(string c, double b, double h) : Shape(c), base(b), height(h) {
        cout << "Triangle created: base=" << base << ", height=" << height << endl;
        calculateArea();
    }
    
    void calculateArea() override {
        area = 0.5 * base * height;
    }
    
    void display() const override {
        cout << "Triangle (b=" << base << ", h=" << height << ") - ";
        Shape::display();
    }
    
    ~Triangle() {
        cout << "Triangle destroyed" << endl;
    }
};

int main() {
    Circle circle("Red", 5.0);
    Rectangle rect("Blue", 4.0, 3.0);
    Triangle tri("Green", 6.0, 4.0);
    
    cout << "\n=== Shape Details ===" << endl;
    circle.display();
    rect.display();
    tri.display();
    
    // Using base class pointers (polymorphism)
    Shape* shapes[3] = {&circle, &rect, &tri};
    
    cout << "\n=== Polymorphic Behavior ===" << endl;
    for (int i = 0; i < 3; i++) {
        shapes[i]->display();
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**shape.h**
```cpp
#ifndef SHAPE_H
#define SHAPE_H

#include <string>
using namespace std;

class Shape {
protected:
    string color;
    double area;
    
public:
    Shape(string c);
    virtual void calculateArea() = 0;
    virtual void display() const;
    string getColor() const;
    double getArea() const;
    virtual ~Shape();
};

#endif
```

**shape.cpp**
```cpp
#include "shape.h"
#include <iostream>
using namespace std;

Shape::Shape(string c) : color(c), area(0) {
    cout << "Shape created: " << color << endl;
}

void Shape::display() const {
    cout << "Color: " << color << ", Area: " << area << endl;
}

string Shape::getColor() const { return color; }
double Shape::getArea() const { return area; }

Shape::~Shape() {
    cout << "Shape destroyed: " << color << endl;
}
```

**circle.h**
```cpp
#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(string c, double r);
    void calculateArea() override;
    double getRadius() const;
    void display() const override;
    ~Circle();
};

#endif
```

**circle.cpp**
```cpp
#include "circle.h"
#include <iostream>
#include <cmath>
using namespace std;

Circle::Circle(string c, double r) : Shape(c), radius(r) {
    cout << "Circle created: radius=" << radius << endl;
    calculateArea();
}

void Circle::calculateArea() {
    area = M_PI * radius * radius;
}

double Circle::getRadius() const { return radius; }

void Circle::display() const {
    cout << "Circle (r=" << radius << ") - ";
    Shape::display();
}

Circle::~Circle() {
    cout << "Circle destroyed" << endl;
}
```

**rectangle.h**
```cpp
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
private:
    double length;
    double width;
    
public:
    Rectangle(string c, double l, double w);
    void calculateArea() override;
    double getLength() const;
    double getWidth() const;
    void display() const override;
    ~Rectangle();
};

#endif
```

**rectangle.cpp**
```cpp
#include "rectangle.h"
#include <iostream>
using namespace std;

Rectangle::Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {
    cout << "Rectangle created: " << length << "x" << width << endl;
    calculateArea();
}

void Rectangle::calculateArea() {
    area = length * width;
}

double Rectangle::getLength() const { return length; }
double Rectangle::getWidth() const { return width; }

void Rectangle::display() const {
    cout << "Rectangle (" << length << "x" << width << ") - ";
    Shape::display();
}

Rectangle::~Rectangle() {
    cout << "Rectangle destroyed" << endl;
}
```

**triangle.h**
```cpp
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape {
private:
    double base;
    double height;
    
public:
    Triangle(string c, double b, double h);
    void calculateArea() override;
    void display() const override;
    ~Triangle();
};

#endif
```

**triangle.cpp**
```cpp
#include "triangle.h"
#include <iostream>
using namespace std;

Triangle::Triangle(string c, double b, double h) : Shape(c), base(b), height(h) {
    cout << "Triangle created: base=" << base << ", height=" << height << endl;
    calculateArea();
}

void Triangle::calculateArea() {
    area = 0.5 * base * height;
}

void Triangle::display() const {
    cout << "Triangle (b=" << base << ", h=" << height << ") - ";
    Shape::display();
}

Triangle::~Triangle() {
    cout << "Triangle destroyed" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
using namespace std;

int main() {
    Circle circle("Red", 5.0);
    Rectangle rect("Blue", 4.0, 3.0);
    Triangle tri("Green", 6.0, 4.0);
    
    circle.display();
    rect.display();
    tri.display();
    
    return 0;
}
```

### Example 2: Employee Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Employee {
protected:
    int id;
    string name;
    double baseSalary;
    string department;
    static int nextId;
    
public:
    Employee(string n, double salary, string dept) 
        : name(n), baseSalary(salary), department(dept) {
        id = nextId++;
        cout << "Employee created: " << name << " (ID: " << id << ")" << endl;
    }
    
    virtual double calculateSalary() const {
        return baseSalary;
    }
    
    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "Base Salary: $" << baseSalary << endl;
        cout << "Total Salary: $" << calculateSalary() << endl;
    }
    
    string getName() const { return name; }
    int getId() const { return id; }
    
    virtual ~Employee() {
        cout << "Employee destroyed: " << name << endl;
    }
};

int Employee::nextId = 1000;

class Developer : public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, double salary, string dept, string lang, int projects) 
        : Employee(n, salary, dept), programmingLanguage(lang), projectsCompleted(projects) {
        cout << "Developer created: " << lang << " specialist" << endl;
    }
    
    double calculateSalary() const override {
        return baseSalary + (projectsCompleted * 1000);
    }
    
    void writeCode() {
        cout << name << " is writing " << programmingLanguage << " code" << endl;
    }
    
    void debug() {
        cout << name << " is debugging" << endl;
    }
    
    void display() const override {
        Employee::display();
        cout << "Language: " << programmingLanguage << endl;
        cout << "Projects Completed: " << projectsCompleted << endl;
    }
    
    ~Developer() {
        cout << "Developer destroyed: " << name << endl;
    }
};

class Manager : public Employee {
private:
    int teamSize;
    vector<string> teamMembers;
    
public:
    Manager(string n, double salary, string dept, int size) 
        : Employee(n, salary, dept), teamSize(size) {
        cout << "Manager created: Team size=" << teamSize << endl;
    }
    
    void addTeamMember(string member) {
        teamMembers.push_back(member);
    }
    
    double calculateSalary() const override {
        return baseSalary + (teamSize * 500);
    }
    
    void conductMeeting() {
        cout << name << " is conducting team meeting" << endl;
    }
    
    void reviewCode() {
        cout << name << " is reviewing code" << endl;
    }
    
    void display() const override {
        Employee::display();
        cout << "Team Size: " << teamSize << endl;
        cout << "Team Members: ";
        for (const auto& m : teamMembers) {
            cout << m << " ";
        }
        cout << endl;
    }
    
    ~Manager() {
        cout << "Manager destroyed: " << name << endl;
    }
};

class Intern : public Employee {
private:
    string university;
    int durationMonths;
    
public:
    Intern(string n, double salary, string dept, string uni, int duration) 
        : Employee(n, salary, dept), university(uni), durationMonths(duration) {
        cout << "Intern created from: " << university << endl;
    }
    
    double calculateSalary() const override {
        return baseSalary * 0.5;
    }
    
    void learn() {
        cout << name << " is learning from mentors" << endl;
    }
    
    void attendTraining() {
        cout << name << " is attending training session" << endl;
    }
    
    void display() const override {
        Employee::display();
        cout << "University: " << university << endl;
        cout << "Duration: " << durationMonths << " months" << endl;
    }
    
    ~Intern() {
        cout << "Intern destroyed: " << name << endl;
    }
};

int main() {
    Developer dev("Alice Johnson", 60000, "Engineering", "C++", 8);
    Manager mgr("Bob Smith", 80000, "Engineering", 5);
    Intern intern("Carol White", 30000, "Engineering", "MIT", 6);
    
    mgr.addTeamMember("Alice");
    mgr.addTeamMember("David");
    
    cout << "\n=== Developer Details ===" << endl;
    dev.display();
    dev.writeCode();
    dev.debug();
    
    cout << "\n=== Manager Details ===" << endl;
    mgr.display();
    mgr.conductMeeting();
    mgr.reviewCode();
    
    cout << "\n=== Intern Details ===" << endl;
    intern.display();
    intern.learn();
    intern.attendTraining();
    
    return 0;
}
```

#### Type 2: Multiple Files

**employee.h**
```cpp
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using namespace std;

class Employee {
protected:
    int id;
    string name;
    double baseSalary;
    string department;
    static int nextId;
    
public:
    Employee(string n, double salary, string dept);
    virtual double calculateSalary() const;
    virtual void display() const;
    string getName() const;
    int getId() const;
    virtual ~Employee();
};

#endif
```

**employee.cpp**
```cpp
#include "employee.h"
#include <iostream>
using namespace std;

int Employee::nextId = 1000;

Employee::Employee(string n, double salary, string dept) 
    : name(n), baseSalary(salary), department(dept) {
    id = nextId++;
    cout << "Employee created: " << name << " (ID: " << id << ")" << endl;
}

double Employee::calculateSalary() const {
    return baseSalary;
}

void Employee::display() const {
    cout << "ID: " << id << ", Name: " << name << endl;
    cout << "Department: " << department << endl;
    cout << "Base Salary: $" << baseSalary << endl;
    cout << "Total Salary: $" << calculateSalary() << endl;
}

string Employee::getName() const { return name; }
int Employee::getId() const { return id; }

Employee::~Employee() {
    cout << "Employee destroyed: " << name << endl;
}
```

**developer.h**
```cpp
#ifndef DEVELOPER_H
#define DEVELOPER_H

#include "employee.h"
#include <string>
using namespace std;

class Developer : public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, double salary, string dept, string lang, int projects);
    double calculateSalary() const override;
    void writeCode();
    void debug();
    void display() const override;
    ~Developer();
};

#endif
```

**developer.cpp**
```cpp
#include "developer.h"
#include <iostream>
using namespace std;

Developer::Developer(string n, double salary, string dept, string lang, int projects) 
    : Employee(n, salary, dept), programmingLanguage(lang), projectsCompleted(projects) {
    cout << "Developer created: " << lang << " specialist" << endl;
}

double Developer::calculateSalary() const {
    return baseSalary + (projectsCompleted * 1000);
}

void Developer::writeCode() {
    cout << name << " is writing " << programmingLanguage << " code" << endl;
}

void Developer::debug() {
    cout << name << " is debugging" << endl;
}

void Developer::display() const {
    Employee::display();
    cout << "Language: " << programmingLanguage << endl;
    cout << "Projects Completed: " << projectsCompleted << endl;
}

Developer::~Developer() {
    cout << "Developer destroyed: " << name << endl;
}
```

**manager.h**
```cpp
#ifndef MANAGER_H
#define MANAGER_H

#include "employee.h"
#include <vector>
#include <string>
using namespace std;

class Manager : public Employee {
private:
    int teamSize;
    vector<string> teamMembers;
    
public:
    Manager(string n, double salary, string dept, int size);
    void addTeamMember(string member);
    double calculateSalary() const override;
    void conductMeeting();
    void reviewCode();
    void display() const override;
    ~Manager();
};

#endif
```

**manager.cpp**
```cpp
#include "manager.h"
#include <iostream>
using namespace std;

Manager::Manager(string n, double salary, string dept, int size) 
    : Employee(n, salary, dept), teamSize(size) {
    cout << "Manager created: Team size=" << teamSize << endl;
}

void Manager::addTeamMember(string member) {
    teamMembers.push_back(member);
}

double Manager::calculateSalary() const {
    return baseSalary + (teamSize * 500);
}

void Manager::conductMeeting() {
    cout << name << " is conducting team meeting" << endl;
}

void Manager::reviewCode() {
    cout << name << " is reviewing code" << endl;
}

void Manager::display() const {
    Employee::display();
    cout << "Team Size: " << teamSize << endl;
    cout << "Team Members: ";
    for (const auto& m : teamMembers) {
        cout << m << " ";
    }
    cout << endl;
}

Manager::~Manager() {
    cout << "Manager destroyed: " << name << endl;
}
```

**intern.h**
```cpp
#ifndef INTERN_H
#define INTERN_H

#include "employee.h"
#include <string>
using namespace std;

class Intern : public Employee {
private:
    string university;
    int durationMonths;
    
public:
    Intern(string n, double salary, string dept, string uni, int duration);
    double calculateSalary() const override;
    void learn();
    void attendTraining();
    void display() const override;
    ~Intern();
};

#endif
```

**intern.cpp**
```cpp
#include "intern.h"
#include <iostream>
using namespace std;

Intern::Intern(string n, double salary, string dept, string uni, int duration) 
    : Employee(n, salary, dept), university(uni), durationMonths(duration) {
    cout << "Intern created from: " << university << endl;
}

double Intern::calculateSalary() const {
    return baseSalary * 0.5;
}

void Intern::learn() {
    cout << name << " is learning from mentors" << endl;
}

void Intern::attendTraining() {
    cout << name << " is attending training session" << endl;
}

void Intern::display() const {
    Employee::display();
    cout << "University: " << university << endl;
    cout << "Duration: " << durationMonths << " months" << endl;
}

Intern::~Intern() {
    cout << "Intern destroyed: " << name << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "developer.h"
#include "manager.h"
#include "intern.h"
using namespace std;

int main() {
    Developer dev("Alice", 60000, "Engineering", "C++", 8);
    Manager mgr("Bob", 80000, "Engineering", 5);
    Intern intern("Carol", 30000, "Engineering", "MIT", 6);
    
    dev.display();
    mgr.display();
    intern.display();
    
    return 0;
}
```

### Example 3: Vehicle Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;
    double mileage;
    
public:
    Vehicle(string mk, string md, int y) : make(mk), model(md), year(y), mileage(0) {
        cout << "Vehicle created: " << make << " " << model << endl;
    }
    
    virtual void start() {
        cout << make << " " << model << " starting" << endl;
    }
    
    virtual void drive(double distance) {
        mileage += distance;
        cout << "Driven " << distance << " km. Total mileage: " << mileage << endl;
    }
    
    virtual void display() const {
        cout << year << " " << make << " " << model << endl;
        cout << "Mileage: " << mileage << " km" << endl;
    }
    
    virtual ~Vehicle() {
        cout << "Vehicle destroyed: " << make << " " << model << endl;
    }
};

class Car : public Vehicle {
private:
    int doors;
    string transmission;
    bool hasSunroof;
    
public:
    Car(string mk, string md, int y, int d, string trans, bool sunroof) 
        : Vehicle(mk, md, y), doors(d), transmission(trans), hasSunroof(sunroof) {
        cout << "Car created: " << doors << "-door, " << transmission << endl;
    }
    
    void start() override {
        cout << make << " " << model << " car starting with key" << endl;
    }
    
    void honk() {
        cout << make << " " << model << " honks: Beep Beep!" << endl;
    }
    
    void openSunroof() {
        if (hasSunroof) {
            cout << "Opening sunroof" << endl;
        } else {
            cout << "No sunroof available" << endl;
        }
    }
    
    void display() const override {
        Vehicle::display();
        cout << "Doors: " << doors << ", Transmission: " << transmission << endl;
        cout << "Sunroof: " << (hasSunroof ? "Yes" : "No") << endl;
    }
    
    ~Car() {
        cout << "Car destroyed: " << make << " " << model << endl;
    }
};

class Motorcycle : public Vehicle {
private:
    int engineCC;
    bool hasSidecar;
    
public:
    Motorcycle(string mk, string md, int y, int cc, bool sidecar) 
        : Vehicle(mk, md, y), engineCC(cc), hasSidecar(sidecar) {
        cout << "Motorcycle created: " << cc << "cc" << endl;
    }
    
    void start() override {
        cout << make << " " << model << " motorcycle kick-starting" << endl;
    }
    
    void wheelie() {
        cout << make << " " << model << " doing a wheelie!" << endl;
    }
    
    void display() const override {
        Vehicle::display();
        cout << "Engine: " << engineCC << "cc" << endl;
        cout << "Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
    }
    
    ~Motorcycle() {
        cout << "Motorcycle destroyed: " << make << " " << model << endl;
    }
};

class Truck : public Vehicle {
private:
    double cargoCapacity;
    int axles;
    bool hasTrailer;
    
public:
    Truck(string mk, string md, int y, double capacity, int ax, bool trailer) 
        : Vehicle(mk, md, y), cargoCapacity(capacity), axles(ax), hasTrailer(trailer) {
        cout << "Truck created: " << capacity << " tons capacity" << endl;
    }
    
    void start() override {
        cout << make << " " << model << " truck starting with heavy engine" << endl;
    }
    
    void loadCargo(double weight) {
        cout << "Loading " << weight << " tons into " << make << " " << model << endl;
        if (weight > cargoCapacity) {
            cout << "Warning: Exceeds capacity!" << endl;
        }
    }
    
    void attachTrailer() {
        if (hasTrailer) {
            cout << "Attaching trailer" << endl;
        } else {
            cout << "Trailer not available" << endl;
        }
    }
    
    void display() const override {
        Vehicle::display();
        cout << "Capacity: " << cargoCapacity << " tons, Axles: " << axles << endl;
        cout << "Trailer: " << (hasTrailer ? "Yes" : "No") << endl;
    }
    
    ~Truck() {
        cout << "Truck destroyed: " << make << " " << model << endl;
    }
};

int main() {
    Car car("Toyota", "Camry", 2022, 4, "Automatic", true);
    Motorcycle bike("Harley", "Sportster", 2023, 1200, false);
    Truck truck("Ford", "F-150", 2021, 3.5, 2, true);
    
    cout << "\n=== Vehicle Actions ===" << endl;
    car.start();
    car.drive(100);
    car.honk();
    car.openSunroof();
    
    bike.start();
    bike.wheelie();
    
    truck.start();
    truck.loadCargo(2.0);
    truck.attachTrailer();
    
    cout << "\n=== Vehicle Details ===" << endl;
    car.display();
    bike.display();
    truck.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**vehicle.h**
```cpp
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;
    double mileage;
    
public:
    Vehicle(string mk, string md, int y);
    virtual void start();
    virtual void drive(double distance);
    virtual void display() const;
    virtual ~Vehicle();
};

#endif
```

**vehicle.cpp**
```cpp
#include "vehicle.h"
#include <iostream>
using namespace std;

Vehicle::Vehicle(string mk, string md, int y) : make(mk), model(md), year(y), mileage(0) {
    cout << "Vehicle created: " << make << " " << model << endl;
}

void Vehicle::start() {
    cout << make << " " << model << " starting" << endl;
}

void Vehicle::drive(double distance) {
    mileage += distance;
    cout << "Driven " << distance << " km. Total mileage: " << mileage << endl;
}

void Vehicle::display() const {
    cout << year << " " << make << " " << model << endl;
    cout << "Mileage: " << mileage << " km" << endl;
}

Vehicle::~Vehicle() {
    cout << "Vehicle destroyed: " << make << " " << model << endl;
}
```

**car.h**
```cpp
#ifndef CAR_H
#define CAR_H

#include "vehicle.h"
#include <string>
using namespace std;

class Car : public Vehicle {
private:
    int doors;
    string transmission;
    bool hasSunroof;
    
public:
    Car(string mk, string md, int y, int d, string trans, bool sunroof);
    void start() override;
    void honk();
    void openSunroof();
    void display() const override;
    ~Car();
};

#endif
```

**car.cpp**
```cpp
#include "car.h"
#include <iostream>
using namespace std;

Car::Car(string mk, string md, int y, int d, string trans, bool sunroof) 
    : Vehicle(mk, md, y), doors(d), transmission(trans), hasSunroof(sunroof) {
    cout << "Car created: " << doors << "-door, " << transmission << endl;
}

void Car::start() {
    cout << make << " " << model << " car starting with key" << endl;
}

void Car::honk() {
    cout << make << " " << model << " honks: Beep Beep!" << endl;
}

void Car::openSunroof() {
    if (hasSunroof) {
        cout << "Opening sunroof" << endl;
    } else {
        cout << "No sunroof available" << endl;
    }
}

void Car::display() const {
    Vehicle::display();
    cout << "Doors: " << doors << ", Transmission: " << transmission << endl;
    cout << "Sunroof: " << (hasSunroof ? "Yes" : "No") << endl;
}

Car::~Car() {
    cout << "Car destroyed: " << make << " " << model << endl;
}
```

**motorcycle.h**
```cpp
#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "vehicle.h"
#include <string>
using namespace std;

class Motorcycle : public Vehicle {
private:
    int engineCC;
    bool hasSidecar;
    
public:
    Motorcycle(string mk, string md, int y, int cc, bool sidecar);
    void start() override;
    void wheelie();
    void display() const override;
    ~Motorcycle();
};

#endif
```

**motorcycle.cpp**
```cpp
#include "motorcycle.h"
#include <iostream>
using namespace std;

Motorcycle::Motorcycle(string mk, string md, int y, int cc, bool sidecar) 
    : Vehicle(mk, md, y), engineCC(cc), hasSidecar(sidecar) {
    cout << "Motorcycle created: " << cc << "cc" << endl;
}

void Motorcycle::start() {
    cout << make << " " << model << " motorcycle kick-starting" << endl;
}

void Motorcycle::wheelie() {
    cout << make << " " << model << " doing a wheelie!" << endl;
}

void Motorcycle::display() const {
    Vehicle::display();
    cout << "Engine: " << engineCC << "cc" << endl;
    cout << "Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
}

Motorcycle::~Motorcycle() {
    cout << "Motorcycle destroyed: " << make << " " << model << endl;
}
```

**truck.h**
```cpp
#ifndef TRUCK_H
#define TRUCK_H

#include "vehicle.h"
#include <string>
using namespace std;

class Truck : public Vehicle {
private:
    double cargoCapacity;
    int axles;
    bool hasTrailer;
    
public:
    Truck(string mk, string md, int y, double capacity, int ax, bool trailer);
    void start() override;
    void loadCargo(double weight);
    void attachTrailer();
    void display() const override;
    ~Truck();
};

#endif
```

**truck.cpp**
```cpp
#include "truck.h"
#include <iostream>
using namespace std;

Truck::Truck(string mk, string md, int y, double capacity, int ax, bool trailer) 
    : Vehicle(mk, md, y), cargoCapacity(capacity), axles(ax), hasTrailer(trailer) {
    cout << "Truck created: " << capacity << " tons capacity" << endl;
}

void Truck::start() {
    cout << make << " " << model << " truck starting with heavy engine" << endl;
}

void Truck::loadCargo(double weight) {
    cout << "Loading " << weight << " tons into " << make << " " << model << endl;
    if (weight > cargoCapacity) {
        cout << "Warning: Exceeds capacity!" << endl;
    }
}

void Truck::attachTrailer() {
    if (hasTrailer) {
        cout << "Attaching trailer" << endl;
    } else {
        cout << "Trailer not available" << endl;
    }
}

void Truck::display() const {
    Vehicle::display();
    cout << "Capacity: " << cargoCapacity << " tons, Axles: " << axles << endl;
    cout << "Trailer: " << (hasTrailer ? "Yes" : "No") << endl;
}

Truck::~Truck() {
    cout << "Truck destroyed: " << make << " " << model << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "car.h"
#include "motorcycle.h"
#include "truck.h"
using namespace std;

int main() {
    Car car("Toyota", "Camry", 2022, 4, "Automatic", true);
    Motorcycle bike("Harley", "Sportster", 2023, 1200, false);
    Truck truck("Ford", "F-150", 2021, 3.5, 2, true);
    
    car.start();
    bike.start();
    truck.start();
    
    car.display();
    bike.display();
    truck.display();
    
    return 0;
}
```

## Public Inheritance Rules

```cpp
#include <iostream>
using namespace std;

class Base {
private:
    int privateVar = 1;
protected:
    int protectedVar = 2;
public:
    int publicVar = 3;
    
    void show() {
        cout << "Base: private=" << privateVar 
             << ", protected=" << protectedVar 
             << ", public=" << publicVar << endl;
    }
};

class Derived : public Base {
public:
    void access() {
        // cout << privateVar;  // Error! Private not accessible
        cout << "protectedVar: " << protectedVar << endl;  // Accessible
        cout << "publicVar: " << publicVar << endl;        // Accessible
    }
    
    void modify() {
        protectedVar = 20;
        publicVar = 30;
    }
};

int main() {
    Base b;
    Derived d;
    
    b.publicVar = 10;    // OK
    // b.protectedVar = 20; // Error!
    
    d.publicVar = 40;    // OK
    // d.protectedVar = 50; // Error!
    
    d.access();
    d.modify();
    d.access();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting virtual destructor | Memory leak | Make base destructor virtual |
| Not using override keyword | Hiding instead of overriding | Use `override` keyword |
| Slicing | Loss of derived data | Use pointers/references |
| Accessing protected members outside | Compilation error | Use public interface |
| Calling base function incorrectly | Wrong behavior | Use scope resolution `Base::` |

## Summary

- **Public inheritance** establishes "is-a" relationship
- Public members of base become **public** in derived
- Protected members of base become **protected** in derived
- Private members of base are **not accessible**
- **Virtual functions** enable polymorphic behavior
- **Virtual destructor** ensures proper cleanup
- Use **override** keyword for clarity
- Base class pointers can point to derived objects

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    int value;
    
public:
    Base(int v) : value(v) {
        cout << "Base constructor" << endl;
    }
    
    virtual void display() const {
        cout << "Base value: " << value << endl;
    }
    
    virtual ~Base() {
        cout << "Base destructor" << endl;
    }
};

class Derived : public Base {
private:
    int extra;
    
public:
    Derived(int v, int e) : Base(v), extra(e) {
        cout << "Derived constructor" << endl;
    }
    
    void display() const override {
        Base::display();
        cout << "Derived extra: " << extra << endl;
    }
    
    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};

int main() {
    Derived d(10, 20);
    d.display();
    
    Base* ptr = &d;
    ptr->display();
    
    return 0;
}
```

### Type 2: Multiple Files

**base.h**
```cpp
#ifndef BASE_H
#define BASE_H

class Base {
protected:
    int value;
    
public:
    Base(int v);
    virtual void display() const;
    virtual ~Base();
};

#endif
```

**base.cpp**
```cpp
#include "base.h"
#include <iostream>
using namespace std;

Base::Base(int v) : value(v) {
    cout << "Base constructor" << endl;
}

void Base::display() const {
    cout << "Base value: " << value << endl;
}

Base::~Base() {
    cout << "Base destructor" << endl;
}
```

**derived.h**
```cpp
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"

class Derived : public Base {
private:
    int extra;
    
public:
    Derived(int v, int e);
    void display() const override;
    ~Derived();
};

#endif
```

**derived.cpp**
```cpp
#include "derived.h"
#include <iostream>
using namespace std;

Derived::Derived(int v, int e) : Base(v), extra(e) {
    cout << "Derived constructor" << endl;
}

void Derived::display() const {
    Base::display();
    cout << "Derived extra: " << extra << endl;
}

Derived::~Derived() {
    cout << "Derived destructor" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "derived.h"
using namespace std;

int main() {
    Derived d(10, 20);
    d.display();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*