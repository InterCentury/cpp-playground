# 106 - Function Overriding in C++

## What is Function Overriding?
Function overriding is a feature that allows a derived class to provide a specific implementation of a function that is already defined in its base class. It enables runtime polymorphism when used with virtual functions.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
    string name;
    
public:
    Animal(string n) : name(n) {}
    
    // Virtual function - can be overridden
    virtual void makeSound() const {
        cout << name << " makes a sound" << endl;
    }
    
    virtual void move() const {
        cout << name << " moves" << endl;
    }
    
    // Non-virtual function - cannot be overridden (can be hidden)
    void eat() const {
        cout << name << " eats" << endl;
    }
    
    virtual ~Animal() {
        cout << "Animal destructor: " << name << endl;
    }
};

class Dog : public Animal {
public:
    Dog(string n) : Animal(n) {}
    
    // Override virtual function
    void makeSound() const override {
        cout << name << " says: Woof! Woof!" << endl;
    }
    
    // Override another virtual function
    void move() const override {
        cout << name << " runs on four legs" << endl;
    }
    
    // This hides the base class function (not overriding)
    void eat() const {
        cout << name << " eats dog food" << endl;
    }
    
    ~Dog() {
        cout << "Dog destructor: " << name << endl;
    }
};

class Cat : public Animal {
public:
    Cat(string n) : Animal(n) {}
    
    void makeSound() const override {
        cout << name << " says: Meow! Meow!" << endl;
    }
    
    void move() const override {
        cout << name << " walks silently" << endl;
    }
    
    ~Cat() {
        cout << "Cat destructor: " << name << endl;
    }
};

int main() {
    // Base class pointers to derived objects
    Animal* animals[2];
    animals[0] = new Dog("Buddy");
    animals[1] = new Cat("Whiskers");
    
    cout << "=== Polymorphic Behavior ===" << endl;
    for (int i = 0; i < 2; i++) {
        animals[i]->makeSound();  // Calls overridden version
        animals[i]->move();       // Calls overridden version
        animals[i]->eat();        // Calls base class version (non-virtual)
        cout << endl;
    }
    
    // Cleanup
    for (int i = 0; i < 2; i++) {
        delete animals[i];
    }
    
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
    
public:
    Animal(string n);
    virtual void makeSound() const;
    virtual void move() const;
    void eat() const;
    virtual ~Animal();
};

#endif
```

### animal.cpp
```cpp
#include "animal.h"
#include <iostream>
using namespace std;

Animal::Animal(string n) : name(n) {}

void Animal::makeSound() const {
    cout << name << " makes a sound" << endl;
}

void Animal::move() const {
    cout << name << " moves" << endl;
}

void Animal::eat() const {
    cout << name << " eats" << endl;
}

Animal::~Animal() {
    cout << "Animal destructor: " << name << endl;
}
```

### dog.h
```cpp
#ifndef DOG_H
#define DOG_H

#include "animal.h"

class Dog : public Animal {
public:
    Dog(string n);
    void makeSound() const override;
    void move() const override;
    void eat() const;
    ~Dog();
};

#endif
```

### dog.cpp
```cpp
#include "dog.h"
#include <iostream>
using namespace std;

Dog::Dog(string n) : Animal(n) {}

void Dog::makeSound() const {
    cout << name << " says: Woof! Woof!" << endl;
}

void Dog::move() const {
    cout << name << " runs on four legs" << endl;
}

void Dog::eat() const {
    cout << name << " eats dog food" << endl;
}

Dog::~Dog() {
    cout << "Dog destructor: " << name << endl;
}
```

### cat.h
```cpp
#ifndef CAT_H
#define CAT_H

#include "animal.h"

class Cat : public Animal {
public:
    Cat(string n);
    void makeSound() const override;
    void move() const override;
    ~Cat();
};

#endif
```

### cat.cpp
```cpp
#include "cat.h"
#include <iostream>
using namespace std;

Cat::Cat(string n) : Animal(n) {}

void Cat::makeSound() const {
    cout << name << " says: Meow! Meow!" << endl;
}

void Cat::move() const {
    cout << name << " walks silently" << endl;
}

Cat::~Cat() {
    cout << "Cat destructor: " << name << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "dog.h"
#include "cat.h"
using namespace std;

int main() {
    Animal* animals[2];
    animals[0] = new Dog("Buddy");
    animals[1] = new Cat("Whiskers");
    
    animals[0]->makeSound();
    animals[1]->makeSound();
    
    delete animals[0];
    delete animals[1];
    
    return 0;
}
```

## Overriding vs Hiding

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void func1() {
        cout << "Base::func1()" << endl;
    }
    
    virtual void func2(int x) {
        cout << "Base::func2(int): " << x << endl;
    }
    
    void func3() {
        cout << "Base::func3()" << endl;
    }
};

class Derived : public Base {
public:
    // Overriding - same signature
    void func1() override {
        cout << "Derived::func1()" << endl;
    }
    
    // Hiding - different signature (not overriding)
    void func2(double x) {
        cout << "Derived::func2(double): " << x << endl;
    }
    
    // Hiding - non-virtual function
    void func3() {
        cout << "Derived::func3()" << endl;
    }
};

int main() {
    Derived d;
    Base* ptr = &d;
    
    cout << "=== Through Base Pointer ===" << endl;
    ptr->func1();      // Derived::func1 (overridden)
    ptr->func2(10);    // Base::func2(int) (not overridden)
    ptr->func3();      // Base::func3() (non-virtual)
    
    cout << "\n=== Through Derived Object ===" << endl;
    d.func1();         // Derived::func1
    d.func2(3.14);     // Derived::func2(double)
    d.func3();         // Derived::func3
    
    return 0;
}
```

## Override Specifier (C++11)

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void func1() {
        cout << "Base::func1" << endl;
    }
    
    virtual void func2() {
        cout << "Base::func2" << endl;
    }
    
    virtual void func3() const {
        cout << "Base::func3 const" << endl;
    }
};

class Derived : public Base {
public:
    // Correct override
    void func1() override {
        cout << "Derived::func1" << endl;
    }
    
    // This will cause compilation error - wrong signature
    // void func2(int x) override { }  // Error! No matching base function
    
    // This will cause compilation error - missing const
    // void func3() override { }  // Error! const mismatch
    
    void func3() const override {
        cout << "Derived::func3 const" << endl;
    }
};

int main() {
    Derived d;
    Base* ptr = &d;
    
    ptr->func1();  // Derived::func1
    ptr->func3();  // Derived::func3 const
    
    return 0;
}
```

## Covariant Return Types

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual Base* clone() const {
        cout << "Base::clone" << endl;
        return new Base(*this);
    }
    
    virtual ~Base() {}
};

class Derived : public Base {
public:
    // Covariant return type - returns Derived* instead of Base*
    Derived* clone() const override {
        cout << "Derived::clone" << endl;
        return new Derived(*this);
    }
};

int main() {
    Base* b1 = new Derived();
    Base* b2 = b1->clone();  // Calls Derived::clone, returns Derived*
    
    delete b1;
    delete b2;
    
    return 0;
}
```

## Practical Examples

### Example 1: Shape Hierarchy with Overriding

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    virtual void scale(double factor) = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() const override {
        return M_PI * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * M_PI * radius;
    }
    
    void draw() const override {
        cout << "○ Circle (r=" << radius << ")" << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
    
    void scale(double factor) override {
        radius *= factor;
        cout << "Circle scaled by " << factor << ", new radius: " << radius << endl;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        cout << "□ Rectangle (" << width << " x " << height << ")" << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
    
    void scale(double factor) override {
        width *= factor;
        height *= factor;
        cout << "Rectangle scaled by " << factor << ", new dimensions: " 
             << width << " x " << height << endl;
    }
};

class Triangle : public Shape {
private:
    double a, b, c;
    
public:
    Triangle(double side1, double side2, double side3) : a(side1), b(side2), c(side3) {}
    
    double area() const override {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    
    double perimeter() const override {
        return a + b + c;
    }
    
    void draw() const override {
        cout << "▲ Triangle (" << a << ", " << b << ", " << c << ")" << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
    
    void scale(double factor) override {
        a *= factor;
        b *= factor;
        c *= factor;
        cout << "Triangle scaled by " << factor << ", new sides: " 
             << a << ", " << b << ", " << c << endl;
    }
};

int main() {
    Shape* shapes[3];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 3.0);
    shapes[2] = new Triangle(3.0, 4.0, 5.0);
    
    cout << "=== Original Shapes ===" << endl;
    for (int i = 0; i < 3; i++) {
        shapes[i]->draw();
        cout << endl;
    }
    
    cout << "=== Scaling Shapes ===" << endl;
    for (int i = 0; i < 3; i++) {
        shapes[i]->scale(2.0);
        cout << endl;
    }
    
    cout << "=== After Scaling ===" << endl;
    for (int i = 0; i < 3; i++) {
        shapes[i]->draw();
        cout << endl;
        delete shapes[i];
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**shape.h**
```cpp
#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    virtual void scale(double factor) = 0;
    virtual ~Shape() {}
};

#endif
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
    Circle(double r);
    double area() const override;
    double perimeter() const override;
    void draw() const override;
    void scale(double factor) override;
};

#endif
```

**circle.cpp**
```cpp
#include "circle.h"
#include <iostream>
#include <cmath>
using namespace std;

Circle::Circle(double r) : radius(r) {}

double Circle::area() const {
    return M_PI * radius * radius;
}

double Circle::perimeter() const {
    return 2 * M_PI * radius;
}

void Circle::draw() const {
    cout << "○ Circle (r=" << radius << ")" << endl;
    cout << "  Area: " << area() << endl;
    cout << "  Perimeter: " << perimeter() << endl;
}

void Circle::scale(double factor) {
    radius *= factor;
    cout << "Circle scaled to radius: " << radius << endl;
}
```

**rectangle.h**
```cpp
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(double w, double h);
    double area() const override;
    double perimeter() const override;
    void draw() const override;
    void scale(double factor) override;
};

#endif
```

**rectangle.cpp**
```cpp
#include "rectangle.h"
#include <iostream>
using namespace std;

Rectangle::Rectangle(double w, double h) : width(w), height(h) {}

double Rectangle::area() const {
    return width * height;
}

double Rectangle::perimeter() const {
    return 2 * (width + height);
}

void Rectangle::draw() const {
    cout << "□ Rectangle (" << width << " x " << height << ")" << endl;
    cout << "  Area: " << area() << endl;
    cout << "  Perimeter: " << perimeter() << endl;
}

void Rectangle::scale(double factor) {
    width *= factor;
    height *= factor;
    cout << "Rectangle scaled to: " << width << " x " << height << endl;
}
```

**triangle.h**
```cpp
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape {
private:
    double a, b, c;
    
public:
    Triangle(double side1, double side2, double side3);
    double area() const override;
    double perimeter() const override;
    void draw() const override;
    void scale(double factor) override;
};

#endif
```

**triangle.cpp**
```cpp
#include "triangle.h"
#include <iostream>
#include <cmath>
using namespace std;

Triangle::Triangle(double side1, double side2, double side3) : a(side1), b(side2), c(side3) {}

double Triangle::area() const {
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::perimeter() const {
    return a + b + c;
}

void Triangle::draw() const {
    cout << "▲ Triangle (" << a << ", " << b << ", " << c << ")" << endl;
    cout << "  Area: " << area() << endl;
    cout << "  Perimeter: " << perimeter() << endl;
}

void Triangle::scale(double factor) {
    a *= factor;
    b *= factor;
    c *= factor;
    cout << "Triangle scaled to sides: " << a << ", " << b << ", " << c << endl;
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
    Shape* shapes[3];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 3.0);
    shapes[2] = new Triangle(3.0, 4.0, 5.0);
    
    for (int i = 0; i < 3; i++) {
        shapes[i]->draw();
        cout << endl;
        delete shapes[i];
    }
    
    return 0;
}
```

### Example 2: Vehicle Hierarchy with Overriding

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
    double speed;
    
public:
    Vehicle(string mk, string md, int y) : make(mk), model(md), year(y), speed(0) {}
    
    virtual void start() {
        cout << make << " " << model << " engine starting" << endl;
    }
    
    virtual void accelerate(double amount) {
        speed += amount;
        cout << make << " " << model << " accelerating to " << speed << " km/h" << endl;
    }
    
    virtual void brake(double amount) {
        speed -= amount;
        if (speed < 0) speed = 0;
        cout << make << " " << model << " braking to " << speed << " km/h" << endl;
    }
    
    virtual void display() const {
        cout << year << " " << make << " " << model << " at " << speed << " km/h" << endl;
    }
    
    virtual ~Vehicle() {
        cout << make << " " << model << " destroyed" << endl;
    }
};

class Car : public Vehicle {
private:
    int doors;
    string transmission;
    
public:
    Car(string mk, string md, int y, int d, string trans) 
        : Vehicle(mk, md, y), doors(d), transmission(trans) {}
    
    void start() override {
        cout << make << " " << model << " car starting with key" << endl;
    }
    
    void accelerate(double amount) override {
        speed += amount * 1.5;  // Cars accelerate faster
        cout << make << " " << model << " car accelerates to " << speed << " km/h" << endl;
    }
    
    void display() const override {
        Vehicle::display();
        cout << "  " << doors << "-door, " << transmission << " transmission" << endl;
    }
};

class Motorcycle : public Vehicle {
private:
    int engineCC;
    bool hasSidecar;
    
public:
    Motorcycle(string mk, string md, int y, int cc, bool sidecar) 
        : Vehicle(mk, md, y), engineCC(cc), hasSidecar(sidecar) {}
    
    void start() override {
        cout << make << " " << model << " motorcycle kick-starting" << endl;
    }
    
    void accelerate(double amount) override {
        speed += amount * 2.0;  // Motorcycles accelerate faster
        cout << make << " " << model << " motorcycle accelerates to " << speed << " km/h" << endl;
    }
    
    void wheelie() {
        cout << make << " " << model << " doing a wheelie!" << endl;
    }
    
    void display() const override {
        Vehicle::display();
        cout << "  " << engineCC << "cc, Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
    }
};

class Truck : public Vehicle {
private:
    double cargoCapacity;
    double load;
    
public:
    Truck(string mk, string md, int y, double capacity) 
        : Vehicle(mk, md, y), cargoCapacity(capacity), load(0) {}
    
    void start() override {
        cout << make << " " << model << " truck starting with heavy engine" << endl;
    }
    
    void accelerate(double amount) override {
        double effectiveAccel = amount * (1 - (load / cargoCapacity));
        speed += effectiveAccel;
        cout << make << " " << model << " truck accelerates slowly to " << speed << " km/h" << endl;
    }
    
    void loadCargo(double weight) {
        if (weight <= cargoCapacity - load) {
            load += weight;
            cout << "Loaded " << weight << " tons. Total load: " << load << "/" << cargoCapacity << endl;
        } else {
            cout << "Cannot load " << weight << " tons - exceeds capacity!" << endl;
        }
    }
    
    void display() const override {
        Vehicle::display();
        cout << "  Load: " << load << "/" << cargoCapacity << " tons" << endl;
    }
};

int main() {
    Vehicle* vehicles[3];
    vehicles[0] = new Car("Toyota", "Camry", 2022, 4, "Automatic");
    vehicles[1] = new Motorcycle("Harley", "Sportster", 2023, 1200, false);
    vehicles[2] = new Truck("Ford", "F-150", 2021, 3.5);
    
    cout << "=== Starting Vehicles ===" << endl;
    for (int i = 0; i < 3; i++) {
        vehicles[i]->start();
    }
    
    cout << "\n=== Accelerating ===" << endl;
    for (int i = 0; i < 3; i++) {
        vehicles[i]->accelerate(20);
    }
    
    cout << "\n=== Vehicle Status ===" << endl;
    for (int i = 0; i < 3; i++) {
        vehicles[i]->display();
        cout << endl;
    }
    
    // Truck-specific operation
    Truck* truck = dynamic_cast<Truck*>(vehicles[2]);
    if (truck) {
        truck->loadCargo(2.0);
        truck->display();
    }
    
    for (int i = 0; i < 3; i++) {
        delete vehicles[i];
    }
    
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
    double speed;
    
public:
    Vehicle(string mk, string md, int y);
    virtual void start();
    virtual void accelerate(double amount);
    virtual void brake(double amount);
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

Vehicle::Vehicle(string mk, string md, int y) : make(mk), model(md), year(y), speed(0) {}

void Vehicle::start() {
    cout << make << " " << model << " engine starting" << endl;
}

void Vehicle::accelerate(double amount) {
    speed += amount;
    cout << make << " " << model << " accelerating to " << speed << " km/h" << endl;
}

void Vehicle::brake(double amount) {
    speed -= amount;
    if (speed < 0) speed = 0;
    cout << make << " " << model << " braking to " << speed << " km/h" << endl;
}

void Vehicle::display() const {
    cout << year << " " << make << " " << model << " at " << speed << " km/h" << endl;
}

Vehicle::~Vehicle() {
    cout << make << " " << model << " destroyed" << endl;
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
    void accelerate(double amount) override;
    void display() const override;
};

#endif
```

**car.cpp**
```cpp
#include "car.h"
#include <iostream>
using namespace std;

Car::Car(string mk, string md, int y, int d, string trans) 
    : Vehicle(mk, md, y), doors(d), transmission(trans) {}

void Car::start() {
    cout << make << " " << model << " car starting with key" << endl;
}

void Car::accelerate(double amount) {
    speed += amount * 1.5;
    cout << make << " " << model << " car accelerates to " << speed << " km/h" << endl;
}

void Car::display() const {
    Vehicle::display();
    cout << "  " << doors << "-door, " << transmission << " transmission" << endl;
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
    void accelerate(double amount) override;
    void wheelie();
    void display() const override;
};

#endif
```

**motorcycle.cpp**
```cpp
#include "motorcycle.h"
#include <iostream>
using namespace std;

Motorcycle::Motorcycle(string mk, string md, int y, int cc, bool sidecar) 
    : Vehicle(mk, md, y), engineCC(cc), hasSidecar(sidecar) {}

void Motorcycle::start() {
    cout << make << " " << model << " motorcycle kick-starting" << endl;
}

void Motorcycle::accelerate(double amount) {
    speed += amount * 2.0;
    cout << make << " " << model << " motorcycle accelerates to " << speed << " km/h" << endl;
}

void Motorcycle::wheelie() {
    cout << make << " " << model << " doing a wheelie!" << endl;
}

void Motorcycle::display() const {
    Vehicle::display();
    cout << "  " << engineCC << "cc, Sidecar: " << (hasSidecar ? "Yes" : "No") << endl;
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
    double load;
    
public:
    Truck(string mk, string md, int y, double capacity);
    void start() override;
    void accelerate(double amount) override;
    void loadCargo(double weight);
    void display() const override;
};

#endif
```

**truck.cpp**
```cpp
#include "truck.h"
#include <iostream>
using namespace std;

Truck::Truck(string mk, string md, int y, double capacity) 
    : Vehicle(mk, md, y), cargoCapacity(capacity), load(0) {}

void Truck::start() {
    cout << make << " " << model << " truck starting with heavy engine" << endl;
}

void Truck::accelerate(double amount) {
    double effectiveAccel = amount * (1 - (load / cargoCapacity));
    speed += effectiveAccel;
    cout << make << " " << model << " truck accelerates to " << speed << " km/h" << endl;
}

void Truck::loadCargo(double weight) {
    if (weight <= cargoCapacity - load) {
        load += weight;
        cout << "Loaded " << weight << " tons. Total: " << load << "/" << cargoCapacity << endl;
    } else {
        cout << "Cannot load - exceeds capacity!" << endl;
    }
}

void Truck::display() const {
    Vehicle::display();
    cout << "  Load: " << load << "/" << cargoCapacity << " tons" << endl;
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
    Truck truck("Ford", "F-150", 2021, 3.5);
    
    car.start();
    bike.start();
    truck.start();
    
    car.accelerate(30);
    bike.accelerate(30);
    truck.accelerate(30);
    
    car.display();
    bike.display();
    truck.display();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting virtual keyword | No overriding, just hiding | Use virtual in base class |
| Signature mismatch | Creates new function, doesn't override | Use override keyword to catch errors |
| Forgetting const | Different signature | Match const qualifiers |
| Slicing | Loss of derived data | Use pointers/references |
| Calling overridden function from constructor | Calls base version | Avoid virtual calls in constructor/destructor |

## Summary

- **Function overriding** provides specific implementation in derived class
- **virtual** keyword enables overriding
- **override** specifier ensures correct overriding (C++11)
- **Virtual destructor** is essential for proper cleanup
- **Signature must match** exactly for overriding
- **Covariant return types** allow returning derived class pointers
- **Hiding** occurs when signature differs or function is non-virtual

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() const {
        cout << "Base class" << endl;
    }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void show() const override {
        cout << "Derived class" << endl;
    }
};

int main() {
    Base* ptr = new Derived();
    ptr->show();
    delete ptr;
    return 0;
}
```

### Type 2: Multiple Files

**base.h**
```cpp
#ifndef BASE_H
#define BASE_H

class Base {
public:
    virtual void show() const;
    virtual ~Base();
};

#endif
```

**base.cpp**
```cpp
#include "base.h"
#include <iostream>
using namespace std;

void Base::show() const {
    cout << "Base class" << endl;
}

Base::~Base() {}
```

**derived.h**
```cpp
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"

class Derived : public Base {
public:
    void show() const override;
};

#endif
```

**derived.cpp**
```cpp
#include "derived.h"
#include <iostream>
using namespace std;

void Derived::show() const {
    cout << "Derived class" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "derived.h"
using namespace std;

int main() {
    Base* ptr = new Derived();
    ptr->show();
    delete ptr;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*