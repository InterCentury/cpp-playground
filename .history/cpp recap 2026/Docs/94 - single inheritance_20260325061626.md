# 94 - Single Inheritance in C++

## What is Single Inheritance?
Single inheritance is a type of inheritance where a derived class inherits from exactly one base class. The derived class acquires all the members (variables and functions) of the base class, allowing code reuse and establishing an "is-a" relationship.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class (Parent)
class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {
        cout << "Animal constructor called for " << name << endl;
    }
    
    void eat() {
        cout << name << " is eating" << endl;
    }
    
    void sleep() {
        cout << name << " is sleeping" << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    virtual ~Animal() {
        cout << "Animal destructor called for " << name << endl;
    }
};

// Derived class (Child) - inherits from Animal
class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(string n, int a, string b) : Animal(n, a), breed(b) {
        cout << "Dog constructor called for " << name << endl;
    }
    
    void bark() {
        cout << name << " says: Woof! Woof!" << endl;
    }
    
    void fetch() {
        cout << name << " is fetching the ball" << endl;
    }
    
    void display() const {
        Animal::display();
        cout << "Breed: " << breed << endl;
    }
    
    ~Dog() {
        cout << "Dog destructor called for " << name << endl;
    }
};

int main() {
    Dog dog("Buddy", 3, "Golden Retriever");
    
    dog.display();
    dog.eat();      // Inherited from Animal
    dog.sleep();    // Inherited from Animal
    dog.bark();     // Dog's own method
    dog.fetch();    // Dog's own method
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### animal.h
```cpp
#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a);
    void eat();
    void sleep();
    void display() const;
    virtual ~Animal();
};

#endif
```

### animal.cpp
```cpp
#include "animal.h"
#include <iostream>
using namespace std;

Animal::Animal(string n, int a) : name(n), age(a) {
    cout << "Animal constructor called for " << name << endl;
}

void Animal::eat() {
    cout << name << " is eating" << endl;
}

void Animal::sleep() {
    cout << name << " is sleeping" << endl;
}

void Animal::display() const {
    cout << "Name: " << name << ", Age: " << age << endl;
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
    
public:
    Dog(string n, int a, string b);
    void bark();
    void fetch();
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

Dog::Dog(string n, int a, string b) : Animal(n, a), breed(b) {
    cout << "Dog constructor called for " << name << endl;
}

void Dog::bark() {
    cout << name << " says: Woof! Woof!" << endl;
}

void Dog::fetch() {
    cout << name << " is fetching the ball" << endl;
}

void Dog::display() const {
    Animal::display();
    cout << "Breed: " << breed << endl;
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
    Dog dog("Buddy", 3, "Golden Retriever");
    dog.display();
    dog.eat();
    dog.bark();
    
    return 0;
}
```

## Access Specifiers in Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

class Base {
private:
    int privateVar = 1;
protected:
    int protectedVar = 2;
public:
    int publicVar = 3;
    
    void showBase() {
        cout << "Private: " << privateVar << endl;
        cout << "Protected: " << protectedVar << endl;
        cout << "Public: " << publicVar << endl;
    }
};

class Derived : public Base {
public:
    void showDerived() {
        // cout << privateVar;  // Error! Private not accessible
        cout << "Protected: " << protectedVar << endl;  // Accessible
        cout << "Public: " << publicVar << endl;        // Accessible
    }
};

int main() {
    Base b;
    Derived d;
    
    // b.privateVar;   // Error! Private
    // b.protectedVar; // Error! Protected
    b.publicVar = 10;   // OK
    
    d.showDerived();
    
    return 0;
}
```

## Types of Inheritance

### 1. Public Inheritance (Most Common)
```cpp
class Base { };
class Derived : public Base { };
// Public members of Base remain public in Derived
// Protected members remain protected
// Private members remain inaccessible
```

### 2. Protected Inheritance
```cpp
class Base { };
class Derived : protected Base { };
// Public and protected members of Base become protected in Derived
```

### 3. Private Inheritance
```cpp
class Base { };
class Derived : private Base { };
// Public and protected members of Base become private in Derived
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

class Derived : public Base {
public:
    Derived() { cout << "Derived constructor" << endl; }
    ~Derived() { cout << "Derived destructor" << endl; }
};

int main() {
    cout << "Creating Derived object:" << endl;
    Derived d;
    cout << "\nDestroying Derived object:" << endl;
    // Destructor called in reverse order
    
    return 0;
}
```
Output:
```
Creating Derived object:
Base constructor
Derived constructor

Destroying Derived object:
Derived destructor
Base destructor
```

## Practical Examples

### Example 1: Employee Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

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
    
    virtual ~Employee() {
        cout << "Employee destroyed: " << name << endl;
    }
};

int Employee::nextId = 1000;

class Manager : public Employee {
private:
    double bonus;
    int teamSize;
    
public:
    Manager(string n, double salary, double b, int size) 
        : Employee(n, salary), bonus(b), teamSize(size) {
        cout << "Manager created: " << name << " (Team: " << teamSize << ")" << endl;
    }
    
    double calculateSalary() const override {
        return baseSalary + bonus;
    }
    
    void display() const override {
        Employee::display();
        cout << "  Bonus: $" << bonus << ", Team Size: " << teamSize << endl;
    }
    
    ~Manager() {
        cout << "Manager destroyed: " << name << endl;
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, double salary, string lang, int projects) 
        : Employee(n, salary), programmingLanguage(lang), projectsCompleted(projects) {
        cout << "Developer created: " << name << " (" << lang << ")" << endl;
    }
    
    double calculateSalary() const override {
        return baseSalary + (projectsCompleted * 1000);
    }
    
    void display() const override {
        Employee::display();
        cout << "  Language: " << programmingLanguage 
             << ", Projects: " << projectsCompleted << endl;
    }
    
    ~Developer() {
        cout << "Developer destroyed: " << name << endl;
    }
};

int main() {
    Manager mgr("Alice Johnson", 80000, 15000, 5);
    Developer dev1("Bob Smith", 60000, "C++", 8);
    Developer dev2("Carol White", 65000, "Python", 6);
    
    cout << "\n--- Employee Details ---" << endl;
    mgr.display();
    dev1.display();
    dev2.display();
    
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

Employee::~Employee() {
    cout << "Employee destroyed: " << name << endl;
}
```

**manager.h**
```cpp
#ifndef MANAGER_H
#define MANAGER_H

#include "employee.h"

class Manager : public Employee {
private:
    double bonus;
    int teamSize;
    
public:
    Manager(string n, double salary, double b, int size);
    double calculateSalary() const override;
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

Manager::Manager(string n, double salary, double b, int size) 
    : Employee(n, salary), bonus(b), teamSize(size) {
    cout << "Manager created: " << name << " (Team: " << teamSize << ")" << endl;
}

double Manager::calculateSalary() const override {
    return baseSalary + bonus;
}

void Manager::display() const override {
    Employee::display();
    cout << "  Bonus: $" << bonus << ", Team Size: " << teamSize << endl;
}

Manager::~Manager() {
    cout << "Manager destroyed: " << name << endl;
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
    cout << "Developer created: " << name << " (" << lang << ")" << endl;
}

double Developer::calculateSalary() const override {
    return baseSalary + (projectsCompleted * 1000);
}

void Developer::display() const override {
    Employee::display();
    cout << "  Language: " << programmingLanguage 
         << ", Projects: " << projectsCompleted << endl;
}

Developer::~Developer() {
    cout << "Developer destroyed: " << name << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "manager.h"
#include "developer.h"
using namespace std;

int main() {
    Manager mgr("Alice", 80000, 15000, 5);
    Developer dev("Bob", 60000, "C++", 8);
    
    mgr.display();
    dev.display();
    
    return 0;
}
```

### Example 2: Shape Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Shape {
protected:
    string color;
    
public:
    Shape(string c) : color(c) {
        cout << "Shape created: " << color << endl;
    }
    
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    
    string getColor() const { return color; }
    
    virtual void display() const {
        cout << "Shape color: " << color << endl;
    }
    
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
    }
    
    double area() const override {
        return M_PI * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * M_PI * radius;
    }
    
    void display() const override {
        Shape::display();
        cout << "Circle: radius=" << radius 
             << ", area=" << area() 
             << ", perimeter=" << perimeter() << endl;
    }
    
    ~Circle() {
        cout << "Circle destroyed: radius=" << radius << endl;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;
    
public:
    Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {
        cout << "Rectangle created: " << length << "x" << width << endl;
    }
    
    double area() const override {
        return length * width;
    }
    
    double perimeter() const override {
        return 2 * (length + width);
    }
    
    void display() const override {
        Shape::display();
        cout << "Rectangle: " << length << "x" << width 
             << ", area=" << area() 
             << ", perimeter=" << perimeter() << endl;
    }
    
    ~Rectangle() {
        cout << "Rectangle destroyed: " << length << "x" << width << endl;
    }
};

int main() {
    Circle circle("Red", 5.0);
    Rectangle rect("Blue", 4.0, 3.0);
    
    cout << "\n--- Shape Details ---" << endl;
    circle.display();
    rect.display();
    
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
    
public:
    Shape(string c);
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    string getColor() const;
    virtual void display() const;
    virtual ~Shape();
};

#endif
```

**shape.cpp**
```cpp
#include "shape.h"
#include <iostream>
using namespace std;

Shape::Shape(string c) : color(c) {
    cout << "Shape created: " << color << endl;
}

string Shape::getColor() const { return color; }

void Shape::display() const {
    cout << "Shape color: " << color << endl;
}

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
    double area() const override;
    double perimeter() const override;
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
}

double Circle::area() const {
    return M_PI * radius * radius;
}

double Circle::perimeter() const {
    return 2 * M_PI * radius;
}

void Circle::display() const {
    Shape::display();
    cout << "Circle: radius=" << radius << endl;
}

Circle::~Circle() {
    cout << "Circle destroyed: radius=" << radius << endl;
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
    double area() const override;
    double perimeter() const override;
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
}

double Rectangle::area() const {
    return length * width;
}

double Rectangle::perimeter() const {
    return 2 * (length + width);
}

void Rectangle::display() const {
    Shape::display();
    cout << "Rectangle: " << length << "x" << width << endl;
}

Rectangle::~Rectangle() {
    cout << "Rectangle destroyed: " << length << "x" << width << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "circle.h"
#include "rectangle.h"
using namespace std;

int main() {
    Circle circle("Red", 5.0);
    Rectangle rect("Blue", 4.0, 3.0);
    
    circle.display();
    rect.display();
    
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
    
public:
    Vehicle(string mk, string md, int y) : make(mk), model(md), year(y) {
        cout << "Vehicle created: " << make << " " << model << endl;
    }
    
    virtual void start() {
        cout << make << " " << model << " is starting" << endl;
    }
    
    virtual void stop() {
        cout << make << " " << model << " is stopping" << endl;
    }
    
    virtual void display() const {
        cout << year << " " << make << " " << model << endl;
    }
    
    virtual ~Vehicle() {
        cout << "Vehicle destroyed: " << make << " " << model << endl;
    }
};

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
        cout << make << " " << model << " car is starting with key" << endl;
    }
    
    void honk() {
        cout << make << " " << model << " honks: Beep Beep!" << endl;
    }
    
    void display() const override {
        Vehicle::display();
        cout << "  Doors: " << doors << ", Transmission: " << transmission << endl;
    }
    
    ~Car() {
        cout << "Car destroyed: " << make << " " << model << endl;
    }
};

class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    
public:
    Motorcycle(string mk, string md, int y, bool sidecar) 
        : Vehicle(mk, md, y), hasSidecar(sidecar) {
        cout << "Motorcycle created: " << (hasSidecar ? "with" : "without") << " sidecar" << endl;
    }
    
    void start() override {
        cout << make << " " << model << " motorcycle is kick-starting" << endl;
    }
    
    void wheelie() {
        cout << make << " " << model << " is doing a wheelie!" << endl;
    }
    
    void display() const override {
        Vehicle::display();
        cout << "  Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
    }
    
    ~Motorcycle() {
        cout << "Motorcycle destroyed: " << make << " " << model << endl;
    }
};

int main() {
    Car car("Toyota", "Camry", 2022, 4, "Automatic");
    Motorcycle bike("Harley-Davidson", "Sportster", 2023, false);
    
    cout << "\n--- Vehicle Details ---" << endl;
    car.display();
    bike.display();
    
    cout << "\n--- Vehicle Actions ---" << endl;
    car.start();
    car.honk();
    bike.start();
    bike.wheelie();
    
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
    
public:
    Vehicle(string mk, string md, int y);
    virtual void start();
    virtual void stop();
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

Vehicle::Vehicle(string mk, string md, int y) : make(mk), model(md), year(y) {
    cout << "Vehicle created: " << make << " " << model << endl;
}

void Vehicle::start() {
    cout << make << " " << model << " is starting" << endl;
}

void Vehicle::stop() {
    cout << make << " " << model << " is stopping" << endl;
}

void Vehicle::display() const {
    cout << year << " " << make << " " << model << endl;
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

void Car::start() override {
    cout << make << " " << model << " car is starting with key" << endl;
}

void Car::honk() {
    cout << make << " " << model << " honks: Beep Beep!" << endl;
}

void Car::display() const override {
    Vehicle::display();
    cout << "  Doors: " << doors << ", Transmission: " << transmission << endl;
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

class Motorcycle : public Vehicle {
private:
    bool hasSidecar;
    
public:
    Motorcycle(string mk, string md, int y, bool sidecar);
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

Motorcycle::Motorcycle(string mk, string md, int y, bool sidecar) 
    : Vehicle(mk, md, y), hasSidecar(sidecar) {
    cout << "Motorcycle created: " << (hasSidecar ? "with" : "without") << " sidecar" << endl;
}

void Motorcycle::start() override {
    cout << make << " " << model << " motorcycle is kick-starting" << endl;
}

void Motorcycle::wheelie() {
    cout << make << " " << model << " is doing a wheelie!" << endl;
}

void Motorcycle::display() const override {
    Vehicle::display();
    cout << "  Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
}

Motorcycle::~Motorcycle() {
    cout << "Motorcycle destroyed: " << make << " " << model << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "car.h"
#include "motorcycle.h"
using namespace std;

int main() {
    Car car("Toyota", "Camry", 2022, 4, "Automatic");
    Motorcycle bike("Harley", "Sportster", 2023, false);
    
    car.display();
    bike.display();
    
    car.start();
    bike.start();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting virtual destructor | Memory leak | Make base destructor virtual |
| Not calling base constructor | Base not initialized | Use initialization list |
| Incorrect access specifier | Unexpected member visibility | Choose public/protected/private appropriately |
| Object slicing | Loss of derived data | Use pointers/references |
| Hiding base class methods | Unexpected behavior | Use `using` or override |

## Summary

- **Single inheritance** - derived class inherits from one base class
- **Public inheritance** - "is-a" relationship
- **Protected/private inheritance** - "implemented-in-terms-of"
- **Constructor order** - base first, then derived
- **Destructor order** - derived first, then base
- **Virtual functions** enable polymorphic behavior
- **Virtual destructor** ensures proper cleanup

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