# 97 - Hierarchical Inheritance in C++

## What is Hierarchical Inheritance?
Hierarchical inheritance is a type of inheritance where multiple derived classes inherit from a single base class. This creates a tree-like structure where the base class provides common functionality, and each derived class adds its own specific features.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
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
    
    virtual ~Shape() {
        cout << "Shape destroyed: " << color << endl;
    }
};

// Derived class 1
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(string c, double r) : Shape(c), radius(r) {
        cout << "Circle created: radius=" << radius << endl;
    }
    
    void calculateArea() override {
        area = 3.14159 * radius * radius;
    }
    
    void display() const override {
        cout << "Circle (r=" << radius << ") - ";
        Shape::display();
    }
    
    double getRadius() const { return radius; }
    
    ~Circle() {
        cout << "Circle destroyed: radius=" << radius << endl;
    }
};

// Derived class 2
class Rectangle : public Shape {
private:
    double length;
    double width;
    
public:
    Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {
        cout << "Rectangle created: " << length << "x" << width << endl;
    }
    
    void calculateArea() override {
        area = length * width;
    }
    
    void display() const override {
        cout << "Rectangle (" << length << "x" << width << ") - ";
        Shape::display();
    }
    
    double getLength() const { return length; }
    double getWidth() const { return width; }
    
    ~Rectangle() {
        cout << "Rectangle destroyed: " << length << "x" << width << endl;
    }
};

// Derived class 3
class Triangle : public Shape {
private:
    double base;
    double height;
    
public:
    Triangle(string c, double b, double h) : Shape(c), base(b), height(h) {
        cout << "Triangle created: base=" << base << ", height=" << height << endl;
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
    // Creating objects of different derived classes
    Circle circle("Red", 5.0);
    Rectangle rect("Blue", 4.0, 3.0);
    Triangle tri("Green", 6.0, 4.0);
    
    // Calculate areas
    circle.calculateArea();
    rect.calculateArea();
    tri.calculateArea();
    
    cout << "\n=== Shape Details ===" << endl;
    circle.display();
    rect.display();
    tri.display();
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### shape.h
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
    virtual ~Shape();
};

#endif
```

### shape.cpp
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

Shape::~Shape() {
    cout << "Shape destroyed: " << color << endl;
}
```

### circle.h
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
    void display() const override;
    double getRadius() const;
    ~Circle();
};

#endif
```

### circle.cpp
```cpp
#include "circle.h"
#include <iostream>
using namespace std;

Circle::Circle(string c, double r) : Shape(c), radius(r) {
    cout << "Circle created: radius=" << radius << endl;
}

void Circle::calculateArea() {
    area = 3.14159 * radius * radius;
}

void Circle::display() const {
    cout << "Circle (r=" << radius << ") - ";
    Shape::display();
}

double Circle::getRadius() const { return radius; }

Circle::~Circle() {
    cout << "Circle destroyed: radius=" << radius << endl;
}
```

### rectangle.h
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
    void display() const override;
    double getLength() const;
    double getWidth() const;
    ~Rectangle();
};

#endif
```

### rectangle.cpp
```cpp
#include "rectangle.h"
#include <iostream>
using namespace std;

Rectangle::Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {
    cout << "Rectangle created: " << length << "x" << width << endl;
}

void Rectangle::calculateArea() {
    area = length * width;
}

void Rectangle::display() const {
    cout << "Rectangle (" << length << "x" << width << ") - ";
    Shape::display();
}

double Rectangle::getLength() const { return length; }
double Rectangle::getWidth() const { return width; }

Rectangle::~Rectangle() {
    cout << "Rectangle destroyed: " << length << "x" << width << endl;
}
```

### triangle.h
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

### triangle.cpp
```cpp
#include "triangle.h"
#include <iostream>
using namespace std;

Triangle::Triangle(string c, double b, double h) : Shape(c), base(b), height(h) {
    cout << "Triangle created: base=" << base << ", height=" << height << endl;
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

### main.cpp
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
    
    circle.calculateArea();
    rect.calculateArea();
    tri.calculateArea();
    
    circle.display();
    rect.display();
    tri.display();
    
    return 0;
}
```

## Constructor and Destructor Order

```cpp
#include <iostream>
#include <string>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructor" << endl; }
    ~Base() { cout << "Base destructor" << endl; }
};

class Derived1 : public Base {
public:
    Derived1() { cout << "Derived1 constructor" << endl; }
    ~Derived1() { cout << "Derived1 destructor" << endl; }
};

class Derived2 : public Base {
public:
    Derived2() { cout << "Derived2 constructor" << endl; }
    ~Derived2() { cout << "Derived2 destructor" << endl; }
};

int main() {
    cout << "Creating Derived1:" << endl;
    Derived1 d1;
    
    cout << "\nCreating Derived2:" << endl;
    Derived2 d2;
    
    return 0;
}
```

## Practical Examples

### Example 1: Employee Management System

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class
class Employee {
protected:
    int id;
    string name;
    double baseSalary;
    static int nextId;
    
public:
    Employee(string n, double salary) : name(n), baseSalary(salary) {
        id = nextId++;
        cout << "Employee created: " << name << " (ID: " << id << ")" << endl;
    }
    
    virtual double calculateSalary() const {
        return baseSalary;
    }
    
    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Salary: $" << calculateSalary() << endl;
    }
    
    string getName() const { return name; }
    int getId() const { return id; }
    
    virtual ~Employee() {
        cout << "Employee destroyed: " << name << endl;
    }
};

int Employee::nextId = 1000;

// Derived class 1: Developer
class Developer : public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, double salary, string lang, int projects) 
        : Employee(n, salary), programmingLanguage(lang), projectsCompleted(projects) {
        cout << "Developer created: " << lang << " specialist" << endl;
    }
    
    double calculateSalary() const override {
        return baseSalary + (projectsCompleted * 1000);
    }
    
    void display() const override {
        Employee::display();
        cout << "  Language: " << programmingLanguage 
             << ", Projects: " << projectsCompleted << endl;
    }
    
    void writeCode() {
        cout << name << " is writing " << programmingLanguage << " code" << endl;
    }
    
    ~Developer() {
        cout << "Developer destroyed: " << name << endl;
    }
};

// Derived class 2: Manager
class Manager : public Employee {
private:
    int teamSize;
    vector<string> teamMembers;
    
public:
    Manager(string n, double salary, int size) 
        : Employee(n, salary), teamSize(size) {
        cout << "Manager created: Team size=" << teamSize << endl;
    }
    
    void addTeamMember(string member) {
        teamMembers.push_back(member);
    }
    
    double calculateSalary() const override {
        return baseSalary + (teamSize * 500);
    }
    
    void display() const override {
        Employee::display();
        cout << "  Team Size: " << teamSize << endl;
        cout << "  Team Members: ";
        for (const auto& m : teamMembers) {
            cout << m << " ";
        }
        cout << endl;
    }
    
    void conductMeeting() {
        cout << name << " is conducting team meeting" << endl;
    }
    
    ~Manager() {
        cout << "Manager destroyed: " << name << endl;
    }
};

// Derived class 3: Intern
class Intern : public Employee {
private:
    string university;
    int durationMonths;
    
public:
    Intern(string n, double salary, string uni, int duration) 
        : Employee(n, salary), university(uni), durationMonths(duration) {
        cout << "Intern created from: " << university << endl;
    }
    
    double calculateSalary() const override {
        return baseSalary * 0.5; // Interns get half salary
    }
    
    void display() const override {
        Employee::display();
        cout << "  University: " << university 
             << ", Duration: " << durationMonths << " months" << endl;
    }
    
    void learn() {
        cout << name << " is learning from mentors" << endl;
    }
    
    ~Intern() {
        cout << "Intern destroyed: " << name << endl;
    }
};

int main() {
    cout << "=== Creating Employees ===" << endl;
    
    Developer dev("Alice Johnson", 60000, "C++", 8);
    Manager mgr("Bob Smith", 80000, 5);
    Intern intern("Carol White", 30000, "MIT", 6);
    
    mgr.addTeamMember("Alice");
    mgr.addTeamMember("David");
    
    cout << "\n=== Employee Details ===" << endl;
    dev.display();
    mgr.display();
    intern.display();
    
    cout << "\n=== Employee Actions ===" << endl;
    dev.writeCode();
    mgr.conductMeeting();
    intern.learn();
    
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
    static int nextId;
    
public:
    Employee(string n, double salary);
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

Employee::Employee(string n, double salary) : name(n), baseSalary(salary) {
    id = nextId++;
    cout << "Employee created: " << name << " (ID: " << id << ")" << endl;
}

double Employee::calculateSalary() const {
    return baseSalary;
}

void Employee::display() const {
    cout << "ID: " << id << ", Name: " << name 
         << ", Salary: $" << calculateSalary() << endl;
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
    Developer(string n, double salary, string lang, int projects);
    double calculateSalary() const override;
    void display() const override;
    void writeCode();
    ~Developer();
};

#endif
```

**developer.cpp**
```cpp
#include "developer.h"
#include <iostream>
using namespace std;

Developer::Developer(string n, double salary, string lang, int projects) 
    : Employee(n, salary), programmingLanguage(lang), projectsCompleted(projects) {
    cout << "Developer created: " << lang << " specialist" << endl;
}

double Developer::calculateSalary() const {
    return baseSalary + (projectsCompleted * 1000);
}

void Developer::display() const {
    Employee::display();
    cout << "  Language: " << programmingLanguage 
         << ", Projects: " << projectsCompleted << endl;
}

void Developer::writeCode() {
    cout << name << " is writing " << programmingLanguage << " code" << endl;
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
    Manager(string n, double salary, int size);
    void addTeamMember(string member);
    double calculateSalary() const override;
    void display() const override;
    void conductMeeting();
    ~Manager();
};

#endif
```

**manager.cpp**
```cpp
#include "manager.h"
#include <iostream>
using namespace std;

Manager::Manager(string n, double salary, int size) 
    : Employee(n, salary), teamSize(size) {
    cout << "Manager created: Team size=" << teamSize << endl;
}

void Manager::addTeamMember(string member) {
    teamMembers.push_back(member);
}

double Manager::calculateSalary() const {
    return baseSalary + (teamSize * 500);
}

void Manager::display() const {
    Employee::display();
    cout << "  Team Size: " << teamSize << endl;
    cout << "  Team Members: ";
    for (const auto& m : teamMembers) {
        cout << m << " ";
    }
    cout << endl;
}

void Manager::conductMeeting() {
    cout << name << " is conducting team meeting" << endl;
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
    Intern(string n, double salary, string uni, int duration);
    double calculateSalary() const override;
    void display() const override;
    void learn();
    ~Intern();
};

#endif
```

**intern.cpp**
```cpp
#include "intern.h"
#include <iostream>
using namespace std;

Intern::Intern(string n, double salary, string uni, int duration) 
    : Employee(n, salary), university(uni), durationMonths(duration) {
    cout << "Intern created from: " << university << endl;
}

double Intern::calculateSalary() const {
    return baseSalary * 0.5;
}

void Intern::display() const {
    Employee::display();
    cout << "  University: " << university 
         << ", Duration: " << durationMonths << " months" << endl;
}

void Intern::learn() {
    cout << name << " is learning from mentors" << endl;
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
    Developer dev("Alice", 60000, "C++", 8);
    Manager mgr("Bob", 80000, 5);
    Intern intern("Carol", 30000, "MIT", 6);
    
    mgr.addTeamMember("Alice");
    
    dev.display();
    mgr.display();
    intern.display();
    
    dev.writeCode();
    mgr.conductMeeting();
    intern.learn();
    
    return 0;
}
```

### Example 2: Vehicle Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class
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

// Derived class 1: Car
class Car : public Vehicle {
private:
    int doors;
    string transmission;
    
public:
    Car(string mk, string md, int y, int d, string trans) 
        : Vehicle(mk, md, y), doors(d), transmission(trans) {
        cout << "Car created: " << doors << "-door, " << transmission << endl;
    }
    
    void start() override {
        cout << make << " " << model << " car starting with key" << endl;
    }
    
    void honk() {
        cout << make << " " << model << " honks: Beep Beep!" << endl;
    }
    
    void display() const override {
        Vehicle::display();
        cout << "Doors: " << doors << ", Transmission: " << transmission << endl;
    }
    
    ~Car() {
        cout << "Car destroyed: " << make << " " << model << endl;
    }
};

// Derived class 2: Motorcycle
class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    int engineCC;
    
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
        cout << "Engine: " << engineCC << "cc, Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
    }
    
    ~Motorcycle() {
        cout << "Motorcycle destroyed: " << make << " " << model << endl;
    }
};

// Derived class 3: Truck
class Truck : public Vehicle {
private:
    double cargoCapacity;
    int axles;
    
public:
    Truck(string mk, string md, int y, double capacity, int ax) 
        : Vehicle(mk, md, y), cargoCapacity(capacity), axles(ax) {
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
    
    void display() const override {
        Vehicle::display();
        cout << "Capacity: " << cargoCapacity << " tons, Axles: " << axles << endl;
    }
    
    ~Truck() {
        cout << "Truck destroyed: " << make << " " << model << endl;
    }
};

int main() {
    cout << "=== Creating Vehicles ===" << endl;
    
    Car car("Toyota", "Camry", 2022, 4, "Automatic");
    Motorcycle bike("Harley", "Sportster", 2023, 1200, false);
    Truck truck("Ford", "F-150", 2021, 3.5, 2);
    
    cout << "\n=== Vehicle Actions ===" << endl;
    car.start();
    car.drive(100);
    car.honk();
    
    bike.start();
    bike.wheelie();
    
    truck.start();
    truck.loadCargo(2.0);
    
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
    
public:
    Car(string mk, string md, int y, int d, string trans);
    void start() override;
    void honk();
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

Car::Car(string mk, string md, int y, int d, string trans) 
    : Vehicle(mk, md, y), doors(d), transmission(trans) {
    cout << "Car created: " << doors << "-door, " << transmission << endl;
}

void Car::start() {
    cout << make << " " << model << " car starting with key" << endl;
}

void Car::honk() {
    cout << make << " " << model << " honks: Beep Beep!" << endl;
}

void Car::display() const {
    Vehicle::display();
    cout << "Doors: " << doors << ", Transmission: " << transmission << endl;
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
    bool hasSidecar;
    int engineCC;
    
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
    cout << "Engine: " << engineCC << "cc, Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
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
    
public:
    Truck(string mk, string md, int y, double capacity, int ax);
    void start() override;
    void loadCargo(double weight);
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

Truck::Truck(string mk, string md, int y, double capacity, int ax) 
    : Vehicle(mk, md, y), cargoCapacity(capacity), axles(ax) {
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

void Truck::display() const {
    Vehicle::display();
    cout << "Capacity: " << cargoCapacity << " tons, Axles: " << axles << endl;
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
    Car car("Toyota", "Camry", 2022, 4, "Automatic");
    Motorcycle bike("Harley", "Sportster", 2023, 1200, false);
    Truck truck("Ford", "F-150", 2021, 3.5, 2);
    
    car.start();
    bike.start();
    truck.start();
    
    car.display();
    bike.display();
    truck.display();
    
    return 0;
}
```

### Example 3: Animal Classification

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class
class Animal {
protected:
    string name;
    int age;
    string habitat;
    
public:
    Animal(string n, int a, string h) : name(n), age(a), habitat(h) {
        cout << "Animal created: " << name << endl;
    }
    
    virtual void makeSound() const = 0;
    
    virtual void move() const {
        cout << name << " is moving" << endl;
    }
    
    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << ", Habitat: " << habitat << endl;
    }
    
    virtual ~Animal() {
        cout << "Animal destroyed: " << name << endl;
    }
};

// Derived class 1: Mammal
class Mammal : public Animal {
protected:
    string furColor;
    bool hasTail;
    
public:
    Mammal(string n, int a, string h, string fur, bool tail) 
        : Animal(n, a, h), furColor(fur), hasTail(tail) {
        cout << "Mammal created: " << fur << " fur" << endl;
    }
    
    void feedMilk() {
        cout << name << " is feeding milk to young" << endl;
    }
    
    void display() const override {
        Animal::display();
        cout << "Fur: " << furColor << ", Tail: " << (hasTail ? "Yes" : "No") << endl;
    }
    
    ~Mammal() {
        cout << "Mammal destroyed: " << name << endl;
    }
};

// Derived class 2: Bird
class Bird : public Animal {
protected:
    double wingspan;
    bool canFly;
    
public:
    Bird(string n, int a, string h, double wings, bool fly) 
        : Animal(n, a, h), wingspan(wings), canFly(fly) {
        cout << "Bird created: wingspan=" << wings << "m" << endl;
    }
    
    void fly() {
        if (canFly) {
            cout << name << " is flying with " << wingspan << "m wingspan" << endl;
        } else {
            cout << name << " cannot fly" << endl;
        }
    }
    
    void display() const override {
        Animal::display();
        cout << "Wingspan: " << wingspan << "m, Can Fly: " << (canFly ? "Yes" : "No") << endl;
    }
    
    ~Bird() {
        cout << "Bird destroyed: " << name << endl;
    }
};

// Derived class 3: Fish
class Fish : public Animal {
protected:
    string waterType;  // Freshwater or Saltwater
    bool hasScales;
    
public:
    Fish(string n, int a, string h, string water, bool scales) 
        : Animal(n, a, h), waterType(water), hasScales(scales) {
        cout << "Fish created: " << water << " fish" << endl;
    }
    
    void swim() {
        cout << name << " is swimming in " << waterType << " water" << endl;
    }
    
    void display() const override {
        Animal::display();
        cout << "Water: " << waterType << ", Scales: " << (hasScales ? "Yes" : "No") << endl;
    }
    
    ~Fish() {
        cout << "Fish destroyed: " << name << endl;
    }
};

// Specific mammals
class Dog : public Mammal {
private:
    string breed;
    
public:
    Dog(string n, int a, string h, string fur, bool tail, string b) 
        : Mammal(n, a, h, fur, tail), breed(b) {
        cout << "Dog created: " << breed << endl;
    }
    
    void makeSound() const override {
        cout << name << " says: Woof! Woof!" << endl;
    }
    
    void fetch() {
        cout << name << " is fetching the ball" << endl;
    }
    
    void display() const override {
        Mammal::display();
        cout << "Breed: " << breed << endl;
    }
    
    ~Dog() {
        cout << "Dog destroyed: " << name << endl;
    }
};

class Cat : public Mammal {
public:
    Cat(string n, int a, string h, string fur, bool tail) 
        : Mammal(n, a, h, fur, tail) {
        cout << "Cat created" << endl;
    }
    
    void makeSound() const override {
        cout << name << " says: Meow! Meow!" << endl;
    }
    
    void climb() {
        cout << name << " is climbing" << endl;
    }
    
    ~Cat() {
        cout << "Cat destroyed: " << name << endl;
    }
};

// Specific birds
class Eagle : public Bird {
public:
    Eagle(string n, int a, string h, double wings) 
        : Bird(n, a, h, wings, true) {
        cout << "Eagle created" << endl;
    }
    
    void makeSound() const override {
        cout << name << " screeches: Kree! Kree!" << endl;
    }
    
    void hunt() {
        cout << name << " is hunting with sharp eyes" << endl;
    }
    
    ~Eagle() {
        cout << "Eagle destroyed: " << name << endl;
    }
};

class Penguin : public Bird {
public:
    Penguin(string n, int a, string h, double wings) 
        : Bird(n, a, h, wings, false) {
        cout << "Penguin created" << endl;
    }
    
    void makeSound() const override {
        cout << name << " honks: HONK! HONK!" << endl;
    }
    
    void swim() {
        cout << name << " is swimming like a fish" << endl;
    }
    
    ~Penguin() {
        cout << "Penguin destroyed: " << name << endl;
    }
};

int main() {
    cout << "=== Creating Animals ===" << endl;
    
    Dog dog("Buddy", 3, "Domestic", "Golden", true, "Golden Retriever");
    Cat cat("Whiskers", 2, "Domestic", "White", true);
    Eagle eagle("Sky", 5, "Mountains", 2.5);
    Penguin penguin("Pingu", 4, "Antarctic", 0.5);
    
    cout << "\n=== Animal Sounds ===" << endl;
    dog.makeSound();
    cat.makeSound();
    eagle.makeSound();
    penguin.makeSound();
    
    cout << "\n=== Animal Actions ===" << endl;
    dog.fetch();
    cat.climb();
    eagle.hunt();
    penguin.swim();
    penguin.fly();  // Can't fly - will show message
    
    cout << "\n=== Animal Details ===" << endl;
    dog.display();
    cat.display();
    eagle.display();
    penguin.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**animal.h**
```cpp
#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    string habitat;
    
public:
    Animal(string n, int a, string h);
    virtual void makeSound() const = 0;
    virtual void move() const;
    virtual void display() const;
    virtual ~Animal();
};

#endif
```

**animal.cpp**
```cpp
#include "animal.h"
#include <iostream>
using namespace std;

Animal::Animal(string n, int a, string h) : name(n), age(a), habitat(h) {
    cout << "Animal created: " << name << endl;
}

void Animal::move() const {
    cout << name << " is moving" << endl;
}

void Animal::display() const {
    cout << "Name: " << name << ", Age: " << age << ", Habitat: " << habitat << endl;
}

Animal::~Animal() {
    cout << "Animal destroyed: " << name << endl;
}
```

**mammal.h**
```cpp
#ifndef MAMMAL_H
#define MAMMAL_H

#include "animal.h"
#include <string>
using namespace std;

class Mammal : public Animal {
protected:
    string furColor;
    bool hasTail;
    
public:
    Mammal(string n, int a, string h, string fur, bool tail);
    void feedMilk();
    void display() const override;
    ~Mammal();
};

#endif
```

**mammal.cpp**
```cpp
#include "mammal.h"
#include <iostream>
using namespace std;

Mammal::Mammal(string n, int a, string h, string fur, bool tail) 
    : Animal(n, a, h), furColor(fur), hasTail(tail) {
    cout << "Mammal created: " << fur << " fur" << endl;
}

void Mammal::feedMilk() {
    cout << name << " is feeding milk to young" << endl;
}

void Mammal::display() const {
    Animal::display();
    cout << "Fur: " << furColor << ", Tail: " << (hasTail ? "Yes" : "No") << endl;
}

Mammal::~Mammal() {
    cout << "Mammal destroyed: " << name << endl;
}
```

**bird.h**
```cpp
#ifndef BIRD_H
#define BIRD_H

#include "animal.h"
#include <string>
using namespace std;

class Bird : public Animal {
protected:
    double wingspan;
    bool canFly;
    
public:
    Bird(string n, int a, string h, double wings, bool fly);
    void fly();
    void display() const override;
    ~Bird();
};

#endif
```

**bird.cpp**
```cpp
#include "bird.h"
#include <iostream>
using namespace std;

Bird::Bird(string n, int a, string h, double wings, bool fly) 
    : Animal(n, a, h), wingspan(wings), canFly(fly) {
    cout << "Bird created: wingspan=" << wings << "m" << endl;
}

void Bird::fly() {
    if (canFly) {
        cout << name << " is flying with " << wingspan << "m wingspan" << endl;
    } else {
        cout << name << " cannot fly" << endl;
    }
}

void Bird::display() const {
    Animal::display();
    cout << "Wingspan: " << wingspan << "m, Can Fly: " << (canFly ? "Yes" : "No") << endl;
}

Bird::~Bird() {
    cout << "Bird destroyed: " << name << endl;
}
```

**fish.h**
```cpp
#ifndef FISH_H
#define FISH_H

#include "animal.h"
#include <string>
using namespace std;

class Fish : public Animal {
protected:
    string waterType;
    bool hasScales;
    
public:
    Fish(string n, int a, string h, string water, bool scales);
    void swim();
    void display() const override;
    ~Fish();
};

#endif
```

**fish.cpp**
```cpp
#include "fish.h"
#include <iostream>
using namespace std;

Fish::Fish(string n, int a, string h, string water, bool scales) 
    : Animal(n, a, h), waterType(water), hasScales(scales) {
    cout << "Fish created: " << water << " fish" << endl;
}

void Fish::swim() {
    cout << name << " is swimming in " << waterType << " water" << endl;
}

void Fish::display() const {
    Animal::display();
    cout << "Water: " << waterType << ", Scales: " << (hasScales ? "Yes" : "No") << endl;
}

Fish::~Fish() {
    cout << "Fish destroyed: " << name << endl;
}
```

**dog.h**
```cpp
#ifndef DOG_H
#define DOG_H

#include "mammal.h"
#include <string>
using namespace std;

class Dog : public Mammal {
private:
    string breed;
    
public:
    Dog(string n, int a, string h, string fur, bool tail, string b);
    void makeSound() const override;
    void fetch();
    void display() const override;
    ~Dog();
};

#endif
```

**dog.cpp**
```cpp
#include "dog.h"
#include <iostream>
using namespace std;

Dog::Dog(string n, int a, string h, string fur, bool tail, string b) 
    : Mammal(n, a, h, fur, tail), breed(b) {
    cout << "Dog created: " << breed << endl;
}

void Dog::makeSound() const {
    cout << name << " says: Woof! Woof!" << endl;
}

void Dog::fetch() {
    cout << name << " is fetching the ball" << endl;
}

void Dog::display() const {
    Mammal::display();
    cout << "Breed: " << breed << endl;
}

Dog::~Dog() {
    cout << "Dog destroyed: " << name << endl;
}
```

**cat.h**
```cpp
#ifndef CAT_H
#define CAT_H

#include "mammal.h"
#include <string>
using namespace std;

class Cat : public Mammal {
public:
    Cat(string n, int a, string h, string fur, bool tail);
    void makeSound() const override;
    void climb();
    ~Cat();
};

#endif
```

**cat.cpp**
```cpp
#include "cat.h"
#include <iostream>
using namespace std;

Cat::Cat(string n, int a, string h, string fur, bool tail) 
    : Mammal(n, a, h, fur, tail) {
    cout << "Cat created" << endl;
}

void Cat::makeSound() const {
    cout << name << " says: Meow! Meow!" << endl;
}

void Cat::climb() {
    cout << name << " is climbing" << endl;
}

Cat::~Cat() {
    cout << "Cat destroyed: " << name << endl;
}
```

**eagle.h**
```cpp
#ifndef EAGLE_H
#define EAGLE_H

#include "bird.h"
#include <string>
using namespace std;

class Eagle : public Bird {
public:
    Eagle(string n, int a, string h, double wings);
    void makeSound() const override;
    void hunt();
    ~Eagle();
};

#endif
```

**eagle.cpp**
```cpp
#include "eagle.h"
#include <iostream>
using namespace std;

Eagle::Eagle(string n, int a, string h, double wings) 
    : Bird(n, a, h, wings, true) {
    cout << "Eagle created" << endl;
}

void Eagle::makeSound() const {
    cout << name << " screeches: Kree! Kree!" << endl;
}

void Eagle::hunt() {
    cout << name << " is hunting with sharp eyes" << endl;
}

Eagle::~Eagle() {
    cout << "Eagle destroyed: " << name << endl;
}
```

**penguin.h**
```cpp
#ifndef PENGUIN_H
#define PENGUIN_H

#include "bird.h"
#include <string>
using namespace std;

class Penguin : public Bird {
public:
    Penguin(string n, int a, string h, double wings);
    void makeSound() const override;
    void swim();
    ~Penguin();
};

#endif
```

**penguin.cpp**
```cpp
#include "penguin.h"
#include <iostream>
using namespace std;

Penguin::Penguin(string n, int a, string h, double wings) 
    : Bird(n, a, h, wings, false) {
    cout << "Penguin created" << endl;
}

void Penguin::makeSound() const {
    cout << name << " honks: HONK! HONK!" << endl;
}

void Penguin::swim() {
    cout << name << " is swimming like a fish" << endl;
}

Penguin::~Penguin() {
    cout << "Penguin destroyed: " << name << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "dog.h"
#include "cat.h"
#include "eagle.h"
#include "penguin.h"
using namespace std;

int main() {
    Dog dog("Buddy", 3, "Domestic", "Golden", true, "Golden Retriever");
    Cat cat("Whiskers", 2, "Domestic", "White", true);
    Eagle eagle("Sky", 5, "Mountains", 2.5);
    Penguin penguin("Pingu", 4, "Antarctic", 0.5);
    
    dog.makeSound();
    cat.makeSound();
    eagle.makeSound();
    penguin.makeSound();
    
    dog.fetch();
    cat.climb();
    eagle.hunt();
    penguin.swim();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting virtual destructor | Memory leak | Make base destructor virtual |
| Not overriding pure virtual functions | Cannot instantiate derived class | Provide implementation |
| Object slicing | Loss of derived data | Use pointers/references |
| Duplicate code in derived classes | Maintenance nightmare | Move common code to base class |
| Deep inheritance chains | Complexity | Keep hierarchy shallow |

## Summary

- **Hierarchical inheritance** creates a tree structure from one base class
- Multiple derived classes share **common functionality** from base
- Each derived class can add **unique features**
- **Constructor order**: Base then Derived
- **Destructor order**: Derived then Base
- **Virtual functions** enable polymorphic behavior
- **Pure virtual functions** create abstract base classes

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
    
    virtual void show() {
        cout << "Base: " << value << endl;
    }
    
    virtual ~Base() {}
};

class Derived1 : public Base {
private:
    int extra1;
    
public:
    Derived1(int v, int e) : Base(v), extra1(e) {
        cout << "Derived1 constructor" << endl;
    }
    
    void show() override {
        Base::show();
        cout << "Derived1 extra: " << extra1 << endl;
    }
};

class Derived2 : public Base {
private:
    int extra2;
    
public:
    Derived2(int v, int e) : Base(v), extra2(e) {
        cout << "Derived2 constructor" << endl;
    }
    
    void show() override {
        Base::show();
        cout << "Derived2 extra: " << extra2 << endl;
    }
};

int main() {
    Derived1 d1(10, 20);
    Derived2 d2(30, 40);
    
    d1.show();
    d2.show();
    
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
    virtual void show();
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

void Base::show() {
    cout << "Base: " << value << endl;
}

Base::~Base() {}
```

**derived1.h**
```cpp
#ifndef DERIVED1_H
#define DERIVED1_H

#include "base.h"

class Derived1 : public Base {
private:
    int extra1;
    
public:
    Derived1(int v, int e);
    void show() override;
};

#endif
```

**derived1.cpp**
```cpp
#include "derived1.h"
#include <iostream>
using namespace std;

Derived1::Derived1(int v, int e) : Base(v), extra1(e) {
    cout << "Derived1 constructor" << endl;
}

void Derived1::show() {
    Base::show();
    cout << "Derived1 extra: " << extra1 << endl;
}
```

**derived2.h**
```cpp
#ifndef DERIVED2_H
#define DERIVED2_H

#include "base.h"

class Derived2 : public Base {
private:
    int extra2;
    
public:
    Derived2(int v, int e);
    void show() override;
};

#endif
```

**derived2.cpp**
```cpp
#include "derived2.h"
#include <iostream>
using namespace std;

Derived2::Derived2(int v, int e) : Base(v), extra2(e) {
    cout << "Derived2 constructor" << endl;
}

void Derived2::show() {
    Base::show();
    cout << "Derived2 extra: " << extra2 << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "derived1.h"
#include "derived2.h"
using namespace std;

int main() {
    Derived1 d1(10, 20);
    Derived2 d2(30, 40);
    
    d1.show();
    d2.show();
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*