# 107 - Pure Virtual Functions in C++

## What are Pure Virtual Functions?
A pure virtual function is a virtual function that has no implementation in the base class and must be overridden in derived classes. It makes the base class abstract, meaning you cannot create objects of that class.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Abstract base class with pure virtual functions
class Shape {
public:
    // Pure virtual functions - no implementation
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    
    // Regular virtual function - has implementation
    virtual void info() const {
        cout << "This is a shape" << endl;
    }
    
    // Virtual destructor
    virtual ~Shape() {
        cout << "Shape destroyed" << endl;
    }
};

// Concrete derived class - must implement all pure virtual functions
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    // Implement pure virtual functions
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
    
    ~Circle() {
        cout << "Circle destroyed" << endl;
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
    
    ~Rectangle() {
        cout << "Rectangle destroyed" << endl;
    }
};

int main() {
    // Shape s;  // Error! Cannot instantiate abstract class
    
    Shape* shapes[2];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 3.0);
    
    for (int i = 0; i < 2; i++) {
        shapes[i]->info();
        shapes[i]->draw();
        cout << endl;
        delete shapes[i];
    }
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### shape.h
```cpp
#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    virtual void info() const;
    virtual ~Shape();
};

#endif
```

### shape.cpp
```cpp
#include "shape.h"
#include <iostream>
using namespace std;

void Shape::info() const {
    cout << "This is a shape" << endl;
}

Shape::~Shape() {
    cout << "Shape destroyed" << endl;
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
    Circle(double r);
    double area() const override;
    double perimeter() const override;
    void draw() const override;
    ~Circle();
};

#endif
```

### circle.cpp
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

Circle::~Circle() {
    cout << "Circle destroyed" << endl;
}
```

### rectangle.h
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
    ~Rectangle();
};

#endif
```

### rectangle.cpp
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

Rectangle::~Rectangle() {
    cout << "Rectangle destroyed" << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "circle.h"
#include "rectangle.h"
using namespace std;

int main() {
    Shape* shapes[2];
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 3.0);
    
    for (int i = 0; i < 2; i++) {
        shapes[i]->draw();
        delete shapes[i];
    }
    
    return 0;
}
```

## Abstract Classes as Interfaces

```cpp
#include <iostream>
#include <string>
using namespace std;

// Interface 1 - Drawable
class Drawable {
public:
    virtual void draw() const = 0;
    virtual ~Drawable() {}
};

// Interface 2 - Serializable
class Serializable {
public:
    virtual void serialize() const = 0;
    virtual void deserialize(const string& data) = 0;
    virtual ~Serializable() {}
};

// Interface 3 - Printable
class Printable {
public:
    virtual void print() const = 0;
    virtual ~Printable() {}
};

// Concrete class implementing multiple interfaces
class Document : public Drawable, public Serializable, public Printable {
private:
    string title;
    string content;
    
public:
    Document(string t, string c) : title(t), content(c) {}
    
    void draw() const override {
        cout << "Drawing document: " << title << endl;
    }
    
    void serialize() const override {
        cout << "<document><title>" << title << "</title>" << endl;
        cout << "<content>" << content << "</content></document>" << endl;
    }
    
    void deserialize(const string& data) override {
        cout << "Deserializing: " << data << endl;
    }
    
    void print() const override {
        cout << "=== " << title << " ===" << endl;
        cout << content << endl;
        cout << "===============" << endl;
    }
};

int main() {
    Document doc("My Document", "This is the content");
    
    doc.draw();
    cout << endl;
    doc.print();
    cout << endl;
    doc.serialize();
    
    return 0;
}
```

## Pure Virtual Destructor

```cpp
#include <iostream>
using namespace std;

class AbstractBase {
public:
    // Pure virtual destructor - must have implementation
    virtual ~AbstractBase() = 0;
};

// Pure virtual destructor must be defined
AbstractBase::~AbstractBase() {
    cout << "AbstractBase destructor" << endl;
}

class Derived : public AbstractBase {
public:
    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};

int main() {
    AbstractBase* ptr = new Derived();
    delete ptr;  // Calls Derived destructor, then AbstractBase destructor
    
    return 0;
}
```

## Practical Examples

### Example 1: Employee Hierarchy with Pure Virtual Functions

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract base class
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
    
    // Pure virtual functions
    virtual double calculateSalary() const = 0;
    virtual void work() const = 0;
    virtual string getRole() const = 0;
    
    // Non-pure virtual function
    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
        cout << "Base Salary: $" << baseSalary << endl;
        cout << "Role: " << getRole() << endl;
        cout << "Total Salary: $" << calculateSalary() << endl;
    }
    
    virtual ~Employee() {
        cout << "Employee destroyed: " << name << endl;
    }
};

int Employee::nextId = 1000;

class Developer : public Employee {
private:
    string language;
    int projectsCompleted;
    
public:
    Developer(string n, double salary, string lang, int projects)
        : Employee(n, salary), language(lang), projectsCompleted(projects) {
        cout << "Developer created: " << language << " specialist" << endl;
    }
    
    double calculateSalary() const override {
        return baseSalary + (projectsCompleted * 1000);
    }
    
    void work() const override {
        cout << name << " is writing " << language << " code" << endl;
    }
    
    string getRole() const override {
        return "Software Developer";
    }
    
    void display() const override {
        Employee::display();
        cout << "Language: " << language << endl;
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
    Manager(string n, double salary, int size) : Employee(n, salary), teamSize(size) {
        cout << "Manager created: Team size=" << teamSize << endl;
    }
    
    void addTeamMember(string member) {
        teamMembers.push_back(member);
    }
    
    double calculateSalary() const override {
        return baseSalary + (teamSize * 500);
    }
    
    void work() const override {
        cout << name << " is conducting meetings and reviewing code" << endl;
    }
    
    string getRole() const override {
        return "Team Manager";
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
    int duration;
    
public:
    Intern(string n, double salary, string uni, int dur)
        : Employee(n, salary), university(uni), duration(dur) {
        cout << "Intern created from: " << university << endl;
    }
    
    double calculateSalary() const override {
        return baseSalary * 0.5;
    }
    
    void work() const override {
        cout << name << " is learning from mentors" << endl;
    }
    
    string getRole() const override {
        return "Intern";
    }
    
    void display() const override {
        Employee::display();
        cout << "University: " << university << endl;
        cout << "Duration: " << duration << " months" << endl;
    }
    
    ~Intern() {
        cout << "Intern destroyed: " << name << endl;
    }
};

int main() {
    vector<Employee*> employees;
    
    employees.push_back(new Developer("Alice", 60000, "C++", 8));
    employees.push_back(new Manager("Bob", 80000, 5));
    employees.push_back(new Intern("Carol", 30000, "MIT", 6));
    
    dynamic_cast<Manager*>(employees[1])->addTeamMember("Alice");
    dynamic_cast<Manager*>(employees[1])->addTeamMember("David");
    
    cout << "\n=== Employee Details ===" << endl;
    for (auto emp : employees) {
        emp->display();
        cout << endl;
    }
    
    cout << "=== Work Activities ===" << endl;
    for (auto emp : employees) {
        emp->work();
    }
    
    for (auto emp : employees) {
        delete emp;
    }
    
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
    virtual double calculateSalary() const = 0;
    virtual void work() const = 0;
    virtual string getRole() const = 0;
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

void Employee::display() const {
    cout << "ID: " << id << ", Name: " << name << endl;
    cout << "Base Salary: $" << baseSalary << endl;
    cout << "Role: " << getRole() << endl;
    cout << "Total Salary: $" << calculateSalary() << endl;
}

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
    string language;
    int projectsCompleted;
    
public:
    Developer(string n, double salary, string lang, int projects);
    double calculateSalary() const override;
    void work() const override;
    string getRole() const override;
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
    : Employee(n, salary), language(lang), projectsCompleted(projects) {
    cout << "Developer created: " << language << " specialist" << endl;
}

double Developer::calculateSalary() const {
    return baseSalary + (projectsCompleted * 1000);
}

void Developer::work() const {
    cout << name << " is writing " << language << " code" << endl;
}

string Developer::getRole() const {
    return "Software Developer";
}

void Developer::display() const {
    Employee::display();
    cout << "Language: " << language << endl;
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
    Manager(string n, double salary, int size);
    void addTeamMember(string member);
    double calculateSalary() const override;
    void work() const override;
    string getRole() const override;
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

Manager::Manager(string n, double salary, int size) : Employee(n, salary), teamSize(size) {
    cout << "Manager created: Team size=" << teamSize << endl;
}

void Manager::addTeamMember(string member) {
    teamMembers.push_back(member);
}

double Manager::calculateSalary() const {
    return baseSalary + (teamSize * 500);
}

void Manager::work() const {
    cout << name << " is conducting meetings and reviewing code" << endl;
}

string Manager::getRole() const {
    return "Team Manager";
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
    int duration;
    
public:
    Intern(string n, double salary, string uni, int dur);
    double calculateSalary() const override;
    void work() const override;
    string getRole() const override;
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

Intern::Intern(string n, double salary, string uni, int dur)
    : Employee(n, salary), university(uni), duration(dur) {
    cout << "Intern created from: " << university << endl;
}

double Intern::calculateSalary() const {
    return baseSalary * 0.5;
}

void Intern::work() const {
    cout << name << " is learning from mentors" << endl;
}

string Intern::getRole() const {
    return "Intern";
}

void Intern::display() const {
    Employee::display();
    cout << "University: " << university << endl;
    cout << "Duration: " << duration << " months" << endl;
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
    
    return 0;
}
```

### Example 2: Animal Hierarchy with Pure Virtual Functions

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {}
    
    // Pure virtual functions
    virtual void makeSound() const = 0;
    virtual void move() const = 0;
    virtual string getHabitat() const = 0;
    virtual string getDiet() const = 0;
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
        cout << "Habitat: " << getHabitat() << endl;
        cout << "Diet: " << getDiet() << endl;
    }
    
    virtual ~Animal() {}
};

class Lion : public Animal {
public:
    Lion(string n, int a) : Animal(n, a) {}
    
    void makeSound() const override {
        cout << name << " roars: ROOOAR!" << endl;
    }
    
    void move() const override {
        cout << name << " stalks silently through the savanna" << endl;
    }
    
    string getHabitat() const override {
        return "Savanna";
    }
    
    string getDiet() const override {
        return "Carnivore (zebras, wildebeest)";
    }
};

class Eagle : public Animal {
public:
    Eagle(string n, int a) : Animal(n, a) {}
    
    void makeSound() const override {
        cout << name << " screeches: KREE KREE!" << endl;
    }
    
    void move() const override {
        cout << name << " soars high in the sky" << endl;
    }
    
    string getHabitat() const override {
        return "Mountains and cliffs";
    }
    
    string getDiet() const override {
        return "Carnivore (fish, small mammals)";
    }
};

class Elephant : public Animal {
public:
    Elephant(string n, int a) : Animal(n, a) {}
    
    void makeSound() const override {
        cout << name << " trumpets: BRRRROOOO!" << endl;
    }
    
    void move() const override {
        cout << name << " walks slowly through the forest" << endl;
    }
    
    string getHabitat() const override {
        return "Forest and grassland";
    }
    
    string getDiet() const override {
        return "Herbivore (leaves, bark, fruits)";
    }
};

int main() {
    vector<Animal*> animals;
    animals.push_back(new Lion("Simba", 5));
    animals.push_back(new Eagle("Sky", 3));
    animals.push_back(new Elephant("Dumbo", 10));
    
    cout << "=== Animal Sounds ===" << endl;
    for (auto animal : animals) {
        animal->makeSound();
    }
    
    cout << "\n=== Animal Movements ===" << endl;
    for (auto animal : animals) {
        animal->move();
    }
    
    cout << "\n=== Animal Details ===" << endl;
    for (auto animal : animals) {
        animal->display();
        cout << endl;
    }
    
    for (auto animal : animals) {
        delete animal;
    }
    
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
    
public:
    Animal(string n, int a);
    virtual void makeSound() const = 0;
    virtual void move() const = 0;
    virtual string getHabitat() const = 0;
    virtual string getDiet() const = 0;
    void display() const;
    virtual ~Animal();
};

#endif
```

**animal.cpp**
```cpp
#include "animal.h"
#include <iostream>
using namespace std;

Animal::Animal(string n, int a) : name(n), age(a) {}

void Animal::display() const {
    cout << "Name: " << name << ", Age: " << age << endl;
    cout << "Habitat: " << getHabitat() << endl;
    cout << "Diet: " << getDiet() << endl;
}

Animal::~Animal() {}
```

**lion.h**
```cpp
#ifndef LION_H
#define LION_H

#include "animal.h"

class Lion : public Animal {
public:
    Lion(string n, int a);
    void makeSound() const override;
    void move() const override;
    string getHabitat() const override;
    string getDiet() const override;
};

#endif
```

**lion.cpp**
```cpp
#include "lion.h"
#include <iostream>
using namespace std;

Lion::Lion(string n, int a) : Animal(n, a) {}

void Lion::makeSound() const {
    cout << name << " roars: ROOOAR!" << endl;
}

void Lion::move() const {
    cout << name << " stalks silently" << endl;
}

string Lion::getHabitat() const {
    return "Savanna";
}

string Lion::getDiet() const {
    return "Carnivore";
}
```

**eagle.h**
```cpp
#ifndef EAGLE_H
#define EAGLE_H

#include "animal.h"

class Eagle : public Animal {
public:
    Eagle(string n, int a);
    void makeSound() const override;
    void move() const override;
    string getHabitat() const override;
    string getDiet() const override;
};

#endif
```

**eagle.cpp**
```cpp
#include "eagle.h"
#include <iostream>
using namespace std;

Eagle::Eagle(string n, int a) : Animal(n, a) {}

void Eagle::makeSound() const {
    cout << name << " screeches: KREE KREE!" << endl;
}

void Eagle::move() const {
    cout << name << " soars high in the sky" << endl;
}

string Eagle::getHabitat() const {
    return "Mountains";
}

string Eagle::getDiet() const {
    return "Carnivore";
}
```

**elephant.h**
```cpp
#ifndef ELEPHANT_H
#define ELEPHANT_H

#include "animal.h"

class Elephant : public Animal {
public:
    Elephant(string n, int a);
    void makeSound() const override;
    void move() const override;
    string getHabitat() const override;
    string getDiet() const override;
};

#endif
```

**elephant.cpp**
```cpp
#include "elephant.h"
#include <iostream>
using namespace std;

Elephant::Elephant(string n, int a) : Animal(n, a) {}

void Elephant::makeSound() const {
    cout << name << " trumpets: BRRRROOOO!" << endl;
}

void Elephant::move() const {
    cout << name << " walks slowly" << endl;
}

string Elephant::getHabitat() const {
    return "Forest";
}

string Elephant::getDiet() const {
    return "Herbivore";
}
```

**main.cpp**
```cpp
#include <iostream>
#include "lion.h"
#include "eagle.h"
#include "elephant.h"
using namespace std;

int main() {
    Lion lion("Simba", 5);
    Eagle eagle("Sky", 3);
    Elephant elephant("Dumbo", 10);
    
    lion.makeSound();
    eagle.makeSound();
    elephant.makeSound();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting implementation in derived class | Derived class remains abstract | Implement all pure virtual functions |
| Instantiating abstract class | Compilation error | Use derived classes |
| Missing pure virtual destructor implementation | Linker error | Provide definition for pure virtual destructor |
| Not using override | Hidden functions | Use override keyword |
| Incomplete interface | Missing required functions | Ensure all pure virtual functions are implemented |

## Summary

- **Pure virtual functions** make classes abstract
- Syntax: `virtual returnType functionName() = 0;`
- **Abstract classes** cannot be instantiated
- Derived classes must implement all pure virtual functions
- Can provide implementation for pure virtual functions (but still abstract)
- **Pure virtual destructor** must be defined
- Useful for creating **interfaces** and **abstract base classes**

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class AbstractClass {
public:
    virtual void pureVirtual() = 0;
    virtual ~AbstractClass() {}
};

class ConcreteClass : public AbstractClass {
public:
    void pureVirtual() override {
        cout << "Implementation" << endl;
    }
};

int main() {
    // AbstractClass obj;  // Error!
    ConcreteClass obj;
    obj.pureVirtual();
    
    AbstractClass* ptr = new ConcreteClass();
    ptr->pureVirtual();
    delete ptr;
    
    return 0;
}
```

### Type 2: Multiple Files

**abstract.h**
```cpp
#ifndef ABSTRACT_H
#define ABSTRACT_H

class AbstractClass {
public:
    virtual void pureVirtual() = 0;
    virtual ~AbstractClass();
};

#endif
```

**abstract.cpp**
```cpp
#include "abstract.h"

AbstractClass::~AbstractClass() {}
```

**concrete.h**
```cpp
#ifndef CONCRETE_H
#define CONCRETE_H

#include "abstract.h"

class ConcreteClass : public AbstractClass {
public:
    void pureVirtual() override;
};

#endif
```

**concrete.cpp**
```cpp
#include "concrete.h"
#include <iostream>
using namespace std;

void ConcreteClass::pureVirtual() {
    cout << "Implementation" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "concrete.h"
using namespace std;

int main() {
    ConcreteClass obj;
    obj.pureVirtual();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*