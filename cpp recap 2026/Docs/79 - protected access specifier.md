# 79 - Protected Access Specifier in C++

## What is Protected Access Specifier?
The `protected` access specifier allows members to be accessed within the class itself and by derived (child) classes, but not from outside the class hierarchy. It's a middle ground between `private` and `public`.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
    // Protected members - accessible in derived classes
    string name;
    int age;
    string sound;
    
    // Protected helper
    void makeSound() const {
        cout << name << " makes: " << sound << endl;
    }
    
public:
    Animal(string n, int a, string s) : name(n), age(a), sound(s) {}
    
    void display() const {
        cout << "Animal: " << name << ", Age: " << age << endl;
    }
};

class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(string n, int a, string b) : Animal(n, a, "Woof!"), breed(b) {}
    
    void bark() {
        // Can access protected members from base class
        cout << name << " (" << breed << ") says: " << sound << endl;
        makeSound();  // Calling protected function
    }
    
    void display() const {
        Animal::display();
        cout << "Breed: " << breed << endl;
    }
};

class Cat : public Animal {
public:
    Cat(string n, int a) : Animal(n, a, "Meow!") {}
    
    void meow() {
        cout << name << " says: " << sound << endl;
    }
};

int main() {
    Dog dog("Buddy", 3, "Golden Retriever");
    Cat cat("Whiskers", 2);
    
    dog.bark();
    cat.meow();
    
    // Cannot access protected members from outside
    // dog.name = "Max";     // Error! name is protected
    // dog.sound = "Bark";   // Error! sound is protected
    
    dog.display();
    cat.display();
    
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
    string sound;
    
    void makeSound() const;
    
public:
    Animal(string n, int a, string s);
    void display() const;
};

#endif
```

### animal.cpp
```cpp
#include "animal.h"
#include <iostream>
using namespace std;

Animal::Animal(string n, int a, string s) : name(n), age(a), sound(s) {}

void Animal::makeSound() const {
    cout << name << " makes: " << sound << endl;
}

void Animal::display() const {
    cout << "Animal: " << name << ", Age: " << age << endl;
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
    void display() const;
};

#endif
```

### dog.cpp
```cpp
#include "dog.h"
#include <iostream>
using namespace std;

Dog::Dog(string n, int a, string b) : Animal(n, a, "Woof!"), breed(b) {}

void Dog::bark() {
    cout << name << " (" << breed << ") says: " << sound << endl;
    makeSound();  // Protected function accessible
}

void Dog::display() const {
    Animal::display();
    cout << "Breed: " << breed << endl;
}
```

### cat.h
```cpp
#ifndef CAT_H
#define CAT_H

#include "animal.h"
#include <string>
using namespace std;

class Cat : public Animal {
public:
    Cat(string n, int a);
    void meow();
};

#endif
```

### cat.cpp
```cpp
#include "cat.h"
#include <iostream>
using namespace std;

Cat::Cat(string n, int a) : Animal(n, a, "Meow!") {}

void Cat::meow() {
    cout << name << " says: " << sound << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "dog.h"
#include "cat.h"
using namespace std;

int main() {
    Dog dog("Buddy", 3, "Golden Retriever");
    Cat cat("Whiskers", 2);
    
    dog.bark();
    cat.meow();
    dog.display();
    cat.display();
    
    return 0;
}
```

## Protected vs Private vs Public Comparison

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
    
    void showAccess() {
        cout << "Inside Base class:" << endl;
        cout << "  privateVar: " << privateVar << endl;    // ✅ Accessible
        cout << "  protectedVar: " << protectedVar << endl; // ✅ Accessible
        cout << "  publicVar: " << publicVar << endl;       // ✅ Accessible
    }
};

class Derived : public Base {
public:
    void showAccess() {
        cout << "Inside Derived class:" << endl;
        // cout << "  privateVar: " << privateVar << endl;  // ❌ Not accessible
        cout << "  protectedVar: " << protectedVar << endl; // ✅ Accessible
        cout << "  publicVar: " << publicVar << endl;       // ✅ Accessible
    }
};

int main() {
    Base b;
    Derived d;
    
    cout << "From outside:" << endl;
    // cout << b.privateVar;   // ❌ Not accessible
    // cout << b.protectedVar; // ❌ Not accessible
    cout << "  publicVar: " << b.publicVar << endl; // ✅ Accessible
    
    cout << endl;
    b.showAccess();
    cout << endl;
    d.showAccess();
    
    return 0;
}
```

## Inheritance Types with Protected Members

### Public Inheritance
```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    int protectedData = 10;
};

// Public inheritance - protected members stay protected
class DerivedPublic : public Base {
public:
    void show() {
        cout << "DerivedPublic: protectedData = " << protectedData << endl;
    }
};

int main() {
    DerivedPublic d;
    d.show();
    // d.protectedData = 20;  // ❌ Error! Still protected
    return 0;
}
```

### Protected Inheritance
```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    int protectedData = 10;
public:
    int publicData = 20;
};

// Protected inheritance - public becomes protected
class DerivedProtected : protected Base {
public:
    void show() {
        cout << "DerivedProtected:" << endl;
        cout << "  protectedData = " << protectedData << endl;  // ✅ Accessible
        cout << "  publicData = " << publicData << endl;        // ✅ Accessible (now protected)
    }
};

class GrandChild : public DerivedProtected {
public:
    void show() {
        // Can access both because they are protected in DerivedProtected
        cout << "GrandChild:" << endl;
        cout << "  protectedData = " << protectedData << endl;
        cout << "  publicData = " << publicData << endl;
    }
};

int main() {
    DerivedProtected d;
    d.show();
    // d.publicData = 30;  // ❌ Error! Now protected
    
    GrandChild g;
    g.show();
    
    return 0;
}
```

### Private Inheritance
```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    int protectedData = 10;
public:
    int publicData = 20;
};

// Private inheritance - all become private
class DerivedPrivate : private Base {
public:
    void show() {
        cout << "DerivedPrivate:" << endl;
        cout << "  protectedData = " << protectedData << endl;  // ✅ Accessible
        cout << "  publicData = " << publicData << endl;        // ✅ Accessible (now private)
    }
};

// GrandChild cannot access Base members because they are private in DerivedPrivate
class GrandChild : public DerivedPrivate {
public:
    void show() {
        // Cannot access protectedData or publicData here
        // cout << protectedData;  // ❌ Not accessible
        cout << "GrandChild: Cannot access Base members" << endl;
    }
};

int main() {
    DerivedPrivate d;
    d.show();
    // d.publicData = 30;  // ❌ Error! Now private
    
    GrandChild g;
    g.show();
    
    return 0;
}
```

## Practical Examples

### Example 1: Shape Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Shape {
protected:
    string color;
    double area;
    
    // Protected method - can be used by derived classes
    virtual void calculateArea() = 0;
    
public:
    Shape(string c) : color(c), area(0) {}
    
    void setColor(string c) { color = c; }
    string getColor() const { return color; }
    double getArea() const { return area; }
    
    virtual void display() const {
        cout << "Color: " << color << ", Area: " << area << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    
protected:
    void calculateArea() override {
        area = 3.14159 * radius * radius;
    }
    
public:
    Circle(string c, double r) : Shape(c), radius(r) {
        calculateArea();
    }
    
    void setRadius(double r) {
        radius = r;
        calculateArea();
    }
    
    void display() const override {
        cout << "Circle - Radius: " << radius << ", ";
        Shape::display();
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;
    
protected:
    void calculateArea() override {
        area = length * width;
    }
    
public:
    Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {
        calculateArea();
    }
    
    void setDimensions(double l, double w) {
        length = l;
        width = w;
        calculateArea();
    }
    
    void display() const override {
        cout << "Rectangle - " << length << "x" << width << ", ";
        Shape::display();
    }
};

int main() {
    Circle circle("Red", 5.0);
    Rectangle rect("Blue", 4.0, 3.0);
    
    circle.display();
    rect.display();
    
    circle.setRadius(3.0);
    rect.setDimensions(5.0, 5.0);
    
    cout << "\nAfter modification:" << endl;
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
    double area;
    virtual void calculateArea() = 0;
    
public:
    Shape(string c);
    void setColor(string c);
    string getColor() const;
    double getArea() const;
    virtual void display() const;
    virtual ~Shape() {}
};

#endif
```

**shape.cpp**
```cpp
#include "shape.h"
#include <iostream>
using namespace std;

Shape::Shape(string c) : color(c), area(0) {}

void Shape::setColor(string c) { color = c; }
string Shape::getColor() const { return color; }
double Shape::getArea() const { return area; }

void Shape::display() const {
    cout << "Color: " << color << ", Area: " << area << endl;
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
    
protected:
    void calculateArea() override;
    
public:
    Circle(string c, double r);
    void setRadius(double r);
    void display() const override;
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
    calculateArea();
}

void Circle::calculateArea() {
    area = 3.14159 * radius * radius;
}

void Circle::setRadius(double r) {
    radius = r;
    calculateArea();
}

void Circle::display() const {
    cout << "Circle - Radius: " << radius << ", ";
    Shape::display();
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
    
protected:
    void calculateArea() override;
    
public:
    Rectangle(string c, double l, double w);
    void setDimensions(double l, double w);
    void display() const override;
};

#endif
```

**rectangle.cpp**
```cpp
#include "rectangle.h"
#include <iostream>
using namespace std;

Rectangle::Rectangle(string c, double l, double w) : Shape(c), length(l), width(w) {
    calculateArea();
}

void Rectangle::calculateArea() {
    area = length * width;
}

void Rectangle::setDimensions(double l, double w) {
    length = l;
    width = w;
    calculateArea();
}

void Rectangle::display() const {
    cout << "Rectangle - " << length << "x" << width << ", ";
    Shape::display();
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

### Example 2: Employee Hierarchy

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
    
    // Protected helper
    void generateId() {
        id = nextId++;
    }
    
public:
    Employee(string n, double salary) : name(n), baseSalary(salary) {
        generateId();
    }
    
    int getId() const { return id; }
    string getName() const { return name; }
    virtual double calculateSalary() const {
        return baseSalary;
    }
    
    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Salary: $" << calculateSalary() << endl;
    }
    
    virtual ~Employee() {}
};

int Employee::nextId = 1000;

class Manager : public Employee {
private:
    double bonus;
    int teamSize;
    
public:
    Manager(string n, double salary, double b, int size) 
        : Employee(n, salary), bonus(b), teamSize(size) {}
    
    double calculateSalary() const override {
        return baseSalary + bonus;
    }
    
    void display() const override {
        Employee::display();
        cout << "  Bonus: $" << bonus << ", Team Size: " << teamSize << endl;
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, double salary, string lang, int projects) 
        : Employee(n, salary), programmingLanguage(lang), projectsCompleted(projects) {}
    
    double calculateSalary() const override {
        return baseSalary + (projectsCompleted * 1000);
    }
    
    void display() const override {
        Employee::display();
        cout << "  Language: " << programmingLanguage 
             << ", Projects: " << projectsCompleted << endl;
    }
};

int main() {
    Manager mgr("Alice", 80000, 15000, 5);
    Developer dev("Bob", 60000, "C++", 8);
    
    mgr.display();
    dev.display();
    
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
    
    void generateId();
    
public:
    Employee(string n, double salary);
    int getId() const;
    string getName() const;
    virtual double calculateSalary() const;
    virtual void display() const;
    virtual ~Employee() {}
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
    generateId();
}

void Employee::generateId() {
    id = nextId++;
}

int Employee::getId() const { return id; }
string Employee::getName() const { return name; }

double Employee::calculateSalary() const {
    return baseSalary;
}

void Employee::display() const {
    cout << "ID: " << id << ", Name: " << name 
         << ", Salary: $" << calculateSalary() << endl;
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
};

#endif
```

**manager.cpp**
```cpp
#include "manager.h"
#include <iostream>
using namespace std;

Manager::Manager(string n, double salary, double b, int size) 
    : Employee(n, salary), bonus(b), teamSize(size) {}

double Manager::calculateSalary() const {
    return baseSalary + bonus;
}

void Manager::display() const {
    Employee::display();
    cout << "  Bonus: $" << bonus << ", Team Size: " << teamSize << endl;
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
};

#endif
```

**developer.cpp**
```cpp
#include "developer.h"
#include <iostream>
using namespace std;

Developer::Developer(string n, double salary, string lang, int projects) 
    : Employee(n, salary), programmingLanguage(lang), projectsCompleted(projects) {}

double Developer::calculateSalary() const {
    return baseSalary + (projectsCompleted * 1000);
}

void Developer::display() const {
    Employee::display();
    cout << "  Language: " << programmingLanguage 
         << ", Projects: " << projectsCompleted << endl;
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

## Access Summary Table

| Access Level | Same Class | Derived Class | Outside |
|--------------|------------|---------------|---------|
| Private | ✅ Yes | ❌ No | ❌ No |
| Protected | ✅ Yes | ✅ Yes | ❌ No |
| Public | ✅ Yes | ✅ Yes | ✅ Yes |

## Inheritance Impact on Protected Members

| Inheritance Type | Base Public | Base Protected | Base Private |
|------------------|-------------|----------------|--------------|
| Public | Public | Protected | Private |
| Protected | Protected | Protected | Private |
| Private | Private | Private | Private |

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Using protected when private suffices | Exposes more than needed | Use private unless derived classes need access |
| Making data protected instead of private | Breaks encapsulation | Use private with protected getters/setters |
| Forgetting to specify inheritance type | Defaults to private | Always specify `public`, `protected`, or `private` |
| Accessing protected members from outside | Compilation error | Use public interface or friend |
| Overriding protected virtual functions incorrectly | Slicing or wrong behavior | Use correct override keyword |

## Summary

- **Protected** members accessible in class and derived classes
- **Protected** provides encapsulation while enabling inheritance
- Use **protected** for base class members that derived classes need
- Use **private** for implementation details
- Use **public** for interface methods
- Inheritance type affects how protected members propagate
- **Protected virtual functions** enable customization in derived classes
- **Protected data** should be used sparingly (prefer protected methods)

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class Base {
protected:
    int protectedData;
    
public:
    Base(int val) : protectedData(val) {}
    virtual void display() const {
        cout << "Protected Data: " << protectedData << endl;
    }
};

class Derived : public Base {
private:
    string name;
    
public:
    Derived(int val, string n) : Base(val), name(n) {}
    
    void modifyData(int newVal) {
        protectedData = newVal;  // Accessing protected member
    }
    
    void display() const override {
        cout << name << ": ";
        Base::display();
    }
};

int main() {
    Derived d(10, "Test");
    d.display();
    d.modifyData(20);
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
    int protectedData;
    
public:
    Base(int val);
    virtual void display() const;
    virtual ~Base() {}
};

#endif
```

**base.cpp**
```cpp
#include "base.h"
#include <iostream>
using namespace std;

Base::Base(int val) : protectedData(val) {}

void Base::display() const {
    cout << "Protected Data: " << protectedData << endl;
}
```

**derived.h**
```cpp
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"
#include <string>
using namespace std;

class Derived : public Base {
private:
    string name;
    
public:
    Derived(int val, string n);
    void modifyData(int newVal);
    void display() const override;
};

#endif
```

**derived.cpp**
```cpp
#include "derived.h"
#include <iostream>
using namespace std;

Derived::Derived(int val, string n) : Base(val), name(n) {}

void Derived::modifyData(int newVal) {
    protectedData = newVal;
}

void Derived::display() const {
    cout << name << ": ";
    Base::display();
}
```

**main.cpp**
```cpp
#include <iostream>
#include "derived.h"
using namespace std;

int main() {
    Derived d(10, "Test");
    d.display();
    d.modifyData(20);
    d.display();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*