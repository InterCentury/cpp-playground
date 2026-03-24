# 98 - Hybrid Inheritance in C++

## What is Hybrid Inheritance?
Hybrid inheritance is a combination of two or more types of inheritance (single, multiple, multilevel, hierarchical) within a single class hierarchy. It creates complex relationships that often lead to the diamond problem, which requires virtual inheritance to resolve.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Person {
protected:
    string name;
    int age;
    
public:
    Person(string n, int a) : name(n), age(a) {
        cout << "Person constructor: " << name << endl;
    }
    
    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    virtual ~Person() {
        cout << "Person destructor: " << name << endl;
    }
};

// Interface 1
class Employee {
protected:
    int employeeId;
    double salary;
    static int nextId;
    
public:
    Employee(double sal) : salary(sal) {
        employeeId = nextId++;
        cout << "Employee constructor: ID=" << employeeId << endl;
    }
    
    virtual double calculateBonus() const {
        return salary * 0.1;
    }
    
    virtual void display() const {
        cout << "Employee ID: " << employeeId << ", Salary: $" << salary << endl;
    }
    
    virtual ~Employee() {
        cout << "Employee destructor: ID=" << employeeId << endl;
    }
};

int Employee::nextId = 1000;

// Interface 2
class Student {
protected:
    int studentId;
    double gpa;
    static int nextStudentId;
    
public:
    Student(double g) : gpa(g) {
        studentId = nextStudentId++;
        cout << "Student constructor: ID=" << studentId << endl;
    }
    
    virtual void display() const {
        cout << "Student ID: " << studentId << ", GPA: " << gpa << endl;
    }
    
    virtual ~Student() {
        cout << "Student destructor: ID=" << studentId << endl;
    }
};

int Student::nextStudentId = 5000;

// Hybrid class: Combining Person, Employee, and Student
// This creates a diamond pattern
class WorkingStudent : public Person, public Employee, public Student {
private:
    string company;
    string university;
    
public:
    WorkingStudent(string n, int a, double sal, double g, string comp, string uni)
        : Person(n, a), Employee(sal), Student(g), company(comp), university(uni) {
        cout << "WorkingStudent constructor: " << name << " works at " << company 
             << " and studies at " << university << endl;
    }
    
    void display() const override {
        Person::display();
        Employee::display();
        Student::display();
        cout << "Company: " << company << ", University: " << university << endl;
    }
    
    double calculateBonus() const override {
        return Employee::calculateBonus() + (gpa * 500);
    }
    
    ~WorkingStudent() {
        cout << "WorkingStudent destructor: " << name << endl;
    }
};

int main() {
    WorkingStudent ws("Alice Johnson", 25, 60000, 3.8, "Tech Corp", "State University");
    
    cout << "\n=== Working Student Details ===" << endl;
    ws.display();
    cout << "Bonus: $" << ws.calculateBonus() << endl;
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### person.h
```cpp
#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    
public:
    Person(string n, int a);
    virtual void display() const;
    virtual ~Person();
};

#endif
```

### person.cpp
```cpp
#include "person.h"
#include <iostream>
using namespace std;

Person::Person(string n, int a) : name(n), age(a) {
    cout << "Person constructor: " << name << endl;
}

void Person::display() const {
    cout << "Name: " << name << ", Age: " << age << endl;
}

Person::~Person() {
    cout << "Person destructor: " << name << endl;
}
```

### employee.h
```cpp
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
protected:
    int employeeId;
    double salary;
    static int nextId;
    
public:
    Employee(double sal);
    virtual double calculateBonus() const;
    virtual void display() const;
    virtual ~Employee();
};

#endif
```

### employee.cpp
```cpp
#include "employee.h"
#include <iostream>
using namespace std;

int Employee::nextId = 1000;

Employee::Employee(double sal) : salary(sal) {
    employeeId = nextId++;
    cout << "Employee constructor: ID=" << employeeId << endl;
}

double Employee::calculateBonus() const {
    return salary * 0.1;
}

void Employee::display() const {
    cout << "Employee ID: " << employeeId << ", Salary: $" << salary << endl;
}

Employee::~Employee() {
    cout << "Employee destructor: ID=" << employeeId << endl;
}
```

### student.h
```cpp
#ifndef STUDENT_H
#define STUDENT_H

class Student {
protected:
    int studentId;
    double gpa;
    static int nextStudentId;
    
public:
    Student(double g);
    virtual void display() const;
    virtual ~Student();
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

int Student::nextStudentId = 5000;

Student::Student(double g) : gpa(g) {
    studentId = nextStudentId++;
    cout << "Student constructor: ID=" << studentId << endl;
}

void Student::display() const {
    cout << "Student ID: " << studentId << ", GPA: " << gpa << endl;
}

Student::~Student() {
    cout << "Student destructor: ID=" << studentId << endl;
}
```

### workingstudent.h
```cpp
#ifndef WORKINGSTUDENT_H
#define WORKINGSTUDENT_H

#include "person.h"
#include "employee.h"
#include "student.h"
#include <string>
using namespace std;

class WorkingStudent : public Person, public Employee, public Student {
private:
    string company;
    string university;
    
public:
    WorkingStudent(string n, int a, double sal, double g, string comp, string uni);
    void display() const override;
    double calculateBonus() const override;
    ~WorkingStudent();
};

#endif
```

### workingstudent.cpp
```cpp
#include "workingstudent.h"
#include <iostream>
using namespace std;

WorkingStudent::WorkingStudent(string n, int a, double sal, double g, string comp, string uni)
    : Person(n, a), Employee(sal), Student(g), company(comp), university(uni) {
    cout << "WorkingStudent constructor: " << name << " works at " << company 
         << " and studies at " << university << endl;
}

void WorkingStudent::display() const {
    Person::display();
    Employee::display();
    Student::display();
    cout << "Company: " << company << ", University: " << university << endl;
}

double WorkingStudent::calculateBonus() const {
    return Employee::calculateBonus() + (gpa * 500);
}

WorkingStudent::~WorkingStudent() {
    cout << "WorkingStudent destructor: " << name << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "workingstudent.h"
using namespace std;

int main() {
    WorkingStudent ws("Alice", 25, 60000, 3.8, "Tech Corp", "University");
    
    ws.display();
    cout << "Bonus: $" << ws.calculateBonus() << endl;
    
    return 0;
}
```

## Diamond Problem and Virtual Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Animal {
protected:
    string name;
    
public:
    Animal(string n) : name(n) {
        cout << "Animal constructor: " << name << endl;
    }
    
    void eat() {
        cout << name << " is eating" << endl;
    }
    
    virtual ~Animal() {
        cout << "Animal destructor: " << name << endl;
    }
};

// Without virtual inheritance - causes diamond problem
class Mammal : public Animal {
public:
    Mammal(string n) : Animal(n) {
        cout << "Mammal constructor" << endl;
    }
    
    void feedMilk() {
        cout << name << " is feeding milk" << endl;
    }
};

class Winged : public Animal {
public:
    Winged(string n) : Animal(n) {
        cout << "Winged constructor" << endl;
    }
    
    void fly() {
        cout << name << " is flying" << endl;
    }
};

// Problem: Bat inherits two copies of Animal
class Bat : public Mammal, public Winged {
public:
    Bat(string n) : Mammal(n), Winged(n) {
        cout << "Bat constructor" << endl;
    }
    // Bat has two Animal subobjects - ambiguous!
};

int main() {
    // This would cause compilation error
    // Bat bat("Bruce");
    // bat.eat();  // Error! Which Animal?
    
    return 0;
}
```

### Solution with Virtual Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class with virtual inheritance
class Animal {
protected:
    string name;
    
public:
    Animal(string n) : name(n) {
        cout << "Animal constructor: " << name << endl;
    }
    
    void eat() {
        cout << name << " is eating" << endl;
    }
    
    string getName() const { return name; }
    
    virtual ~Animal() {
        cout << "Animal destructor: " << name << endl;
    }
};

// Virtual inheritance - only one Animal subobject
class Mammal : virtual public Animal {
public:
    Mammal(string n) : Animal(n) {
        cout << "Mammal constructor" << endl;
    }
    
    void feedMilk() {
        cout << name << " is feeding milk" << endl;
    }
};

class Winged : virtual public Animal {
public:
    Winged(string n) : Animal(n) {
        cout << "Winged constructor" << endl;
    }
    
    void fly() {
        cout << name << " is flying" << endl;
    }
};

// Bat now has only one Animal subobject
class Bat : public Mammal, public Winged {
public:
    Bat(string n) : Animal(n), Mammal(n), Winged(n) {
        cout << "Bat constructor" << endl;
    }
    
    void display() {
        cout << "Bat: " << getName() << endl;
    }
};

int main() {
    Bat bat("Bruce");
    bat.eat();        // Now works fine
    bat.feedMilk();
    bat.fly();
    bat.display();
    
    return 0;
}
```

## Practical Examples

### Example 1: University System with Hybrid Inheritance

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class
class Person {
protected:
    string name;
    int age;
    string email;
    
public:
    Person(string n, int a, string e) : name(n), age(a), email(e) {
        cout << "Person created: " << name << endl;
    }
    
    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
        cout << "Email: " << email << endl;
    }
    
    virtual ~Person() {
        cout << "Person destroyed: " << name << endl;
    }
};

// Employee hierarchy (Single inheritance)
class Employee : virtual public Person {
protected:
    int employeeId;
    double salary;
    string department;
    static int nextEmpId;
    
public:
    Employee(string n, int a, string e, double sal, string dept) 
        : Person(n, a, e), salary(sal), department(dept) {
        employeeId = nextEmpId++;
        cout << "Employee created: ID=" << employeeId << endl;
    }
    
    virtual double calculateSalary() const {
        return salary;
    }
    
    void display() const override {
        Person::display();
        cout << "Employee ID: " << employeeId << ", Dept: " << department << endl;
        cout << "Salary: $" << salary << endl;
    }
    
    ~Employee() {
        cout << "Employee destroyed: ID=" << employeeId << endl;
    }
};

int Employee::nextEmpId = 1000;

// Student hierarchy (Single inheritance)
class Student : virtual public Person {
protected:
    int studentId;
    double gpa;
    string major;
    static int nextStdId;
    
public:
    Student(string n, int a, string e, double g, string m) 
        : Person(n, a, e), gpa(g), major(m) {
        studentId = nextStdId++;
        cout << "Student created: ID=" << studentId << endl;
    }
    
    virtual void display() const override {
        Person::display();
        cout << "Student ID: " << studentId << ", Major: " << major << endl;
        cout << "GPA: " << gpa << endl;
    }
    
    ~Student() {
        cout << "Student destroyed: ID=" << studentId << endl;
    }
};

int Student::nextStdId = 5000;

// TeachingAssistant - Hybrid (Multiple + Hierarchical)
class TeachingAssistant : public Employee, public Student {
private:
    vector<string> courses;
    int hoursPerWeek;
    
public:
    TeachingAssistant(string n, int a, string e, double sal, string dept, 
                      double g, string m, int hours) 
        : Person(n, a, e), Employee(n, a, e, sal, dept), Student(n, a, e, g, m),
          hoursPerWeek(hours) {
        cout << "Teaching Assistant created: " << name << endl;
    }
    
    void addCourse(string course) {
        courses.push_back(course);
    }
    
    double calculateSalary() const override {
        return Employee::calculateSalary() + (hoursPerWeek * 25);
    }
    
    void display() const override {
        Person::display();
        cout << "Employee ID: " << employeeId << ", Student ID: " << studentId << endl;
        cout << "Department: " << department << ", Major: " << major << endl;
        cout << "Salary: $" << calculateSalary() << ", GPA: " << gpa << endl;
        cout << "Hours/Week: " << hoursPerWeek << endl;
        cout << "Teaching Courses: ";
        for (const auto& c : courses) cout << c << " ";
        cout << endl;
    }
    
    ~TeachingAssistant() {
        cout << "Teaching Assistant destroyed: " << name << endl;
    }
};

// ResearchAssistant - Another hybrid
class ResearchAssistant : public Employee, public Student {
private:
    string researchTopic;
    vector<string> publications;
    
public:
    ResearchAssistant(string n, int a, string e, double sal, string dept,
                      double g, string m, string topic) 
        : Person(n, a, e), Employee(n, a, e, sal, dept), Student(n, a, e, g, m),
          researchTopic(topic) {
        cout << "Research Assistant created: " << name << endl;
    }
    
    void addPublication(string pub) {
        publications.push_back(pub);
    }
    
    double calculateSalary() const override {
        return Employee::calculateSalary() + (publications.size() * 1000);
    }
    
    void display() const override {
        Person::display();
        cout << "Employee ID: " << employeeId << ", Student ID: " << studentId << endl;
        cout << "Department: " << department << ", Major: " << major << endl;
        cout << "Salary: $" << calculateSalary() << ", GPA: " << gpa << endl;
        cout << "Research Topic: " << researchTopic << endl;
        cout << "Publications: ";
        for (const auto& p : publications) cout << p << " ";
        cout << endl;
    }
    
    ~ResearchAssistant() {
        cout << "Research Assistant destroyed: " << name << endl;
    }
};

// Professor - Multiple inheritance (Employee + additional roles)
class Professor : public Employee {
private:
    string title;
    vector<string> researchAreas;
    
public:
    Professor(string n, int a, string e, double sal, string dept, string t) 
        : Person(n, a, e), Employee(n, a, e, sal, dept), title(t) {
        cout << "Professor created: " << name << " (" << title << ")" << endl;
    }
    
    void addResearchArea(string area) {
        researchAreas.push_back(area);
    }
    
    double calculateSalary() const override {
        return Employee::calculateSalary() + (researchAreas.size() * 2000);
    }
    
    void display() const override {
        Person::display();
        cout << "Employee ID: " << employeeId << ", Title: " << title << endl;
        cout << "Department: " << department << endl;
        cout << "Salary: $" << calculateSalary() << endl;
        cout << "Research Areas: ";
        for (const auto& a : researchAreas) cout << a << " ";
        cout << endl;
    }
    
    ~Professor() {
        cout << "Professor destroyed: " << name << endl;
    }
};

int main() {
    cout << "=== Creating University Staff ===" << endl;
    
    TeachingAssistant ta("Alice Johnson", 25, "alice@uni.edu", 40000, "CS", 
                         3.8, "Computer Science", 20);
    ta.addCourse("Data Structures");
    ta.addCourse("Algorithms");
    
    ResearchAssistant ra("Bob Smith", 28, "bob@uni.edu", 45000, "Physics",
                         3.9, "Physics", "Quantum Computing");
    ra.addPublication("Quantum Algorithms Paper");
    ra.addPublication("Quantum Error Correction");
    
    Professor prof("Dr. Carol White", 45, "carol@uni.edu", 120000, "Mathematics", 
                   "Full Professor");
    prof.addResearchArea("Algebraic Geometry");
    prof.addResearchArea("Number Theory");
    
    cout << "\n=== Teaching Assistant Details ===" << endl;
    ta.display();
    
    cout << "\n=== Research Assistant Details ===" << endl;
    ra.display();
    
    cout << "\n=== Professor Details ===" << endl;
    prof.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**person.h**
```cpp
#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    string email;
    
public:
    Person(string n, int a, string e);
    virtual void display() const;
    virtual ~Person();
};

#endif
```

**person.cpp**
```cpp
#include "person.h"
#include <iostream>
using namespace std;

Person::Person(string n, int a, string e) : name(n), age(a), email(e) {
    cout << "Person created: " << name << endl;
}

void Person::display() const {
    cout << "Name: " << name << ", Age: " << age << endl;
    cout << "Email: " << email << endl;
}

Person::~Person() {
    cout << "Person destroyed: " << name << endl;
}
```

**employee.h**
```cpp
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "person.h"
#include <string>
using namespace std;

class Employee : virtual public Person {
protected:
    int employeeId;
    double salary;
    string department;
    static int nextEmpId;
    
public:
    Employee(string n, int a, string e, double sal, string dept);
    virtual double calculateSalary() const;
    void display() const override;
    ~Employee();
};

#endif
```

**employee.cpp**
```cpp
#include "employee.h"
#include <iostream>
using namespace std;

int Employee::nextEmpId = 1000;

Employee::Employee(string n, int a, string e, double sal, string dept) 
    : Person(n, a, e), salary(sal), department(dept) {
    employeeId = nextEmpId++;
    cout << "Employee created: ID=" << employeeId << endl;
}

double Employee::calculateSalary() const {
    return salary;
}

void Employee::display() const {
    Person::display();
    cout << "Employee ID: " << employeeId << ", Dept: " << department << endl;
    cout << "Salary: $" << salary << endl;
}

Employee::~Employee() {
    cout << "Employee destroyed: ID=" << employeeId << endl;
}
```

**student.h**
```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include <string>
using namespace std;

class Student : virtual public Person {
protected:
    int studentId;
    double gpa;
    string major;
    static int nextStdId;
    
public:
    Student(string n, int a, string e, double g, string m);
    void display() const override;
    ~Student();
};

#endif
```

**student.cpp**
```cpp
#include "student.h"
#include <iostream>
using namespace std;

int Student::nextStdId = 5000;

Student::Student(string n, int a, string e, double g, string m) 
    : Person(n, a, e), gpa(g), major(m) {
    studentId = nextStdId++;
    cout << "Student created: ID=" << studentId << endl;
}

void Student::display() const {
    Person::display();
    cout << "Student ID: " << studentId << ", Major: " << major << endl;
    cout << "GPA: " << gpa << endl;
}

Student::~Student() {
    cout << "Student destroyed: ID=" << studentId << endl;
}
```

**teachingassistant.h**
```cpp
#ifndef TEACHINGASSISTANT_H
#define TEACHINGASSISTANT_H

#include "employee.h"
#include "student.h"
#include <vector>
#include <string>
using namespace std;

class TeachingAssistant : public Employee, public Student {
private:
    vector<string> courses;
    int hoursPerWeek;
    
public:
    TeachingAssistant(string n, int a, string e, double sal, string dept, 
                      double g, string m, int hours);
    void addCourse(string course);
    double calculateSalary() const override;
    void display() const override;
    ~TeachingAssistant();
};

#endif
```

**teachingassistant.cpp**
```cpp
#include "teachingassistant.h"
#include <iostream>
using namespace std;

TeachingAssistant::TeachingAssistant(string n, int a, string e, double sal, string dept, 
                                      double g, string m, int hours) 
    : Person(n, a, e), Employee(n, a, e, sal, dept), Student(n, a, e, g, m),
      hoursPerWeek(hours) {
    cout << "Teaching Assistant created: " << name << endl;
}

void TeachingAssistant::addCourse(string course) {
    courses.push_back(course);
}

double TeachingAssistant::calculateSalary() const {
    return Employee::calculateSalary() + (hoursPerWeek * 25);
}

void TeachingAssistant::display() const {
    Person::display();
    cout << "Employee ID: " << employeeId << ", Student ID: " << studentId << endl;
    cout << "Department: " << department << ", Major: " << major << endl;
    cout << "Salary: $" << calculateSalary() << ", GPA: " << gpa << endl;
    cout << "Hours/Week: " << hoursPerWeek << endl;
    cout << "Courses: ";
    for (const auto& c : courses) cout << c << " ";
    cout << endl;
}

TeachingAssistant::~TeachingAssistant() {
    cout << "Teaching Assistant destroyed: " << name << endl;
}
```

**researchassistant.h**
```cpp
#ifndef RESEARCHASSISTANT_H
#define RESEARCHASSISTANT_H

#include "employee.h"
#include "student.h"
#include <vector>
#include <string>
using namespace std;

class ResearchAssistant : public Employee, public Student {
private:
    string researchTopic;
    vector<string> publications;
    
public:
    ResearchAssistant(string n, int a, string e, double sal, string dept,
                      double g, string m, string topic);
    void addPublication(string pub);
    double calculateSalary() const override;
    void display() const override;
    ~ResearchAssistant();
};

#endif
```

**researchassistant.cpp**
```cpp
#include "researchassistant.h"
#include <iostream>
using namespace std;

ResearchAssistant::ResearchAssistant(string n, int a, string e, double sal, string dept,
                                      double g, string m, string topic) 
    : Person(n, a, e), Employee(n, a, e, sal, dept), Student(n, a, e, g, m),
      researchTopic(topic) {
    cout << "Research Assistant created: " << name << endl;
}

void ResearchAssistant::addPublication(string pub) {
    publications.push_back(pub);
}

double ResearchAssistant::calculateSalary() const {
    return Employee::calculateSalary() + (publications.size() * 1000);
}

void ResearchAssistant::display() const {
    Person::display();
    cout << "Employee ID: " << employeeId << ", Student ID: " << studentId << endl;
    cout << "Department: " << department << ", Major: " << major << endl;
    cout << "Salary: $" << calculateSalary() << ", GPA: " << gpa << endl;
    cout << "Research Topic: " << researchTopic << endl;
    cout << "Publications: ";
    for (const auto& p : publications) cout << p << " ";
    cout << endl;
}

ResearchAssistant::~ResearchAssistant() {
    cout << "Research Assistant destroyed: " << name << endl;
}
```

**professor.h**
```cpp
#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "employee.h"
#include <vector>
#include <string>
using namespace std;

class Professor : public Employee {
private:
    string title;
    vector<string> researchAreas;
    
public:
    Professor(string n, int a, string e, double sal, string dept, string t);
    void addResearchArea(string area);
    double calculateSalary() const override;
    void display() const override;
    ~Professor();
};

#endif
```

**professor.cpp**
```cpp
#include "professor.h"
#include <iostream>
using namespace std;

Professor::Professor(string n, int a, string e, double sal, string dept, string t) 
    : Person(n, a, e), Employee(n, a, e, sal, dept), title(t) {
    cout << "Professor created: " << name << " (" << title << ")" << endl;
}

void Professor::addResearchArea(string area) {
    researchAreas.push_back(area);
}

double Professor::calculateSalary() const {
    return Employee::calculateSalary() + (researchAreas.size() * 2000);
}

void Professor::display() const {
    Person::display();
    cout << "Employee ID: " << employeeId << ", Title: " << title << endl;
    cout << "Department: " << department << endl;
    cout << "Salary: $" << calculateSalary() << endl;
    cout << "Research Areas: ";
    for (const auto& a : researchAreas) cout << a << " ";
    cout << endl;
}

Professor::~Professor() {
    cout << "Professor destroyed: " << name << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "teachingassistant.h"
#include "researchassistant.h"
#include "professor.h"
using namespace std;

int main() {
    TeachingAssistant ta("Alice", 25, "alice@uni.edu", 40000, "CS", 3.8, "CS", 20);
    ResearchAssistant ra("Bob", 28, "bob@uni.edu", 45000, "Physics", 3.9, "Physics", "Quantum");
    Professor prof("Dr. Carol", 45, "carol@uni.edu", 120000, "Math", "Full Professor");
    
    ta.addCourse("Data Structures");
    ra.addPublication("Quantum Paper");
    prof.addResearchArea("Algebra");
    
    ta.display();
    ra.display();
    prof.display();
    
    return 0;
}
```

### Example 2: Smart Home System with Hybrid Inheritance

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base device class
class Device {
protected:
    string deviceId;
    string name;
    bool isOn;
    static int nextId;
    
public:
    Device(string n) : name(n), isOn(false) {
        deviceId = "DEV" + to_string(nextId++);
        cout << "Device created: " << name << " (" << deviceId << ")" << endl;
    }
    
    virtual void turnOn() {
        isOn = true;
        cout << name << " turned ON" << endl;
    }
    
    virtual void turnOff() {
        isOn = false;
        cout << name << " turned OFF" << endl;
    }
    
    virtual void display() const {
        cout << "Device: " << name << " (" << deviceId << ")" << endl;
        cout << "Status: " << (isOn ? "ON" : "OFF") << endl;
    }
    
    virtual ~Device() {
        cout << "Device destroyed: " << name << endl;
    }
};

int Device::nextId = 1;

// Connectable interface
class Connectable {
protected:
    string ipAddress;
    bool connected;
    
public:
    Connectable() : ipAddress("0.0.0.0"), connected(false) {}
    
    virtual void connect(const string& ip) {
        ipAddress = ip;
        connected = true;
        cout << "Connected to network at " << ipAddress << endl;
    }
    
    virtual void disconnect() {
        connected = false;
        cout << "Disconnected from network" << endl;
    }
    
    virtual void sendData(const string& data) {
        if (connected) {
            cout << "Sending data: " << data << endl;
        }
    }
    
    virtual ~Connectable() {}
};

// SmartDevice - Hybrid (Device + Connectable)
class SmartDevice : virtual public Device, virtual public Connectable {
protected:
    string firmwareVersion;
    
public:
    SmartDevice(string n, string fw) : Device(n), firmwareVersion(fw) {
        cout << "SmartDevice created: FW v" << firmwareVersion << endl;
    }
    
    void updateFirmware(string version) {
        firmwareVersion = version;
        cout << name << " firmware updated to v" << version << endl;
    }
    
    void display() const override {
        Device::display();
        cout << "Firmware: v" << firmwareVersion << endl;
        cout << "Network: " << (connected ? "Connected" : "Disconnected") 
             << " (" << ipAddress << ")" << endl;
    }
    
    ~SmartDevice() {
        cout << "SmartDevice destroyed: " << name << endl;
    }
};

// SmartLight - Multilevel + Multiple
class SmartLight : public SmartDevice {
private:
    int brightness;
    string color;
    
public:
    SmartLight(string n, string fw, string col) 
        : Device(n), SmartDevice(n, fw), color(col), brightness(100) {
        cout << "SmartLight created: " << color << " light" << endl;
    }
    
    void setBrightness(int level) {
        brightness = min(100, max(0, level));
        cout << name << " brightness set to " << brightness << "%" << endl;
    }
    
    void setColor(string col) {
        color = col;
        cout << name << " color set to " << color << endl;
    }
    
    void display() const override {
        SmartDevice::display();
        cout << "Brightness: " << brightness << "%, Color: " << color << endl;
    }
    
    ~SmartLight() {
        cout << "SmartLight destroyed: " << name << endl;
    }
};

// SmartPlug - Another SmartDevice
class SmartPlug : public SmartDevice {
private:
    double powerConsumption;
    bool applianceOn;
    
public:
    SmartPlug(string n, string fw) 
        : Device(n), SmartDevice(n, fw), powerConsumption(0), applianceOn(false) {
        cout << "SmartPlug created" << endl;
    }
    
    void toggleAppliance() {
        applianceOn = !applianceOn;
        cout << name << " appliance " << (applianceOn ? "ON" : "OFF") << endl;
    }
    
    void recordPower(double watts) {
        powerConsumption = watts;
        cout << "Power consumption: " << powerConsumption << "W" << endl;
    }
    
    void display() const override {
        SmartDevice::display();
        cout << "Appliance: " << (applianceOn ? "ON" : "OFF") << endl;
        cout << "Power: " << powerConsumption << "W" << endl;
    }
    
    ~SmartPlug() {
        cout << "SmartPlug destroyed: " << name << endl;
    }
};

// SecurityCamera - Hybrid with additional features
class SecurityCamera : public SmartDevice {
private:
    bool recording;
    string resolution;
    vector<string> motionEvents;
    
public:
    SecurityCamera(string n, string fw, string res) 
        : Device(n), SmartDevice(n, fw), resolution(res), recording(false) {
        cout << "SecurityCamera created: " << resolution << " resolution" << endl;
    }
    
    void startRecording() {
        recording = true;
        cout << name << " started recording" << endl;
    }
    
    void stopRecording() {
        recording = false;
        cout << name << " stopped recording" << endl;
    }
    
    void detectMotion() {
        cout << name << " detected motion!" << endl;
        motionEvents.push_back("Motion at " + to_string(time(nullptr)));
    }
    
    void display() const override {
        SmartDevice::display();
        cout << "Resolution: " << resolution << endl;
        cout << "Recording: " << (recording ? "Yes" : "No") << endl;
        cout << "Motion events: " << motionEvents.size() << endl;
    }
    
    ~SecurityCamera() {
        cout << "SecurityCamera destroyed: " << name << endl;
    }
};

// SmartHomeHub - Multiple inheritance from different branches
class SmartHomeHub : public Device, public Connectable {
private:
    vector<SmartDevice*> devices;
    string hubName;
    
public:
    SmartHomeHub(string n, string hub) : Device(n), hubName(hub) {
        cout << "SmartHomeHub created: " << hubName << endl;
    }
    
    void addDevice(SmartDevice* device) {
        devices.push_back(device);
        cout << "Added " << device->name << " to hub" << endl;
    }
    
    void controlAll(const string& command) {
        cout << "Hub " << hubName << " sending command: " << command << endl;
        for (auto device : devices) {
            if (command == "ON") device->turnOn();
            else if (command == "OFF") device->turnOff();
        }
    }
    
    void display() const override {
        Device::display();
        cout << "Hub Name: " << hubName << endl;
        cout << "Network: " << (connected ? "Connected" : "Disconnected") << endl;
        cout << "Devices: " << devices.size() << " devices" << endl;
    }
    
    ~SmartHomeHub() {
        cout << "SmartHomeHub destroyed: " << hubName << endl;
    }
};

int main() {
    cout << "=== Creating Smart Home System ===" << endl;
    
    SmartLight light("Living Room Light", "1.0", "White");
    SmartPlug plug("Coffee Maker Plug", "1.2");
    SecurityCamera camera("Front Door Camera", "2.0", "1080p");
    SmartHomeHub hub("Main Hub", "Home Assistant");
    
    light.connect("192.168.1.10");
    plug.connect("192.168.1.11");
    camera.connect("192.168.1.12");
    hub.connect("192.168.1.1");
    
    hub.addDevice(&light);
    hub.addDevice(&plug);
    hub.addDevice(&camera);
    
    cout << "\n=== Device Operations ===" << endl;
    light.turnOn();
    light.setBrightness(75);
    light.setColor("Warm White");
    
    plug.toggleAppliance();
    plug.recordPower(1500);
    
    camera.startRecording();
    camera.detectMotion();
    
    hub.controlAll("OFF");
    
    cout << "\n=== Device Status ===" << endl;
    light.display();
    plug.display();
    camera.display();
    hub.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**device.h**
```cpp
#ifndef DEVICE_H
#define DEVICE_H

#include <string>
using namespace std;

class Device {
protected:
    string deviceId;
    string name;
    bool isOn;
    static int nextId;
    
public:
    Device(string n);
    virtual void turnOn();
    virtual void turnOff();
    virtual void display() const;
    virtual ~Device();
};

#endif
```

**device.cpp**
```cpp
#include "device.h"
#include <iostream>
using namespace std;

int Device::nextId = 1;

Device::Device(string n) : name(n), isOn(false) {
    deviceId = "DEV" + to_string(nextId++);
    cout << "Device created: " << name << " (" << deviceId << ")" << endl;
}

void Device::turnOn() {
    isOn = true;
    cout << name << " turned ON" << endl;
}

void Device::turnOff() {
    isOn = false;
    cout << name << " turned OFF" << endl;
}

void Device::display() const {
    cout << "Device: " << name << " (" << deviceId << ")" << endl;
    cout << "Status: " << (isOn ? "ON" : "OFF") << endl;
}

Device::~Device() {
    cout << "Device destroyed: " << name << endl;
}
```

**connectable.h**
```cpp
#ifndef CONNECTABLE_H
#define CONNECTABLE_H

#include <string>
using namespace std;

class Connectable {
protected:
    string ipAddress;
    bool connected;
    
public:
    Connectable();
    virtual void connect(const string& ip);
    virtual void disconnect();
    virtual void sendData(const string& data);
    virtual ~Connectable();
};

#endif
```

**connectable.cpp**
```cpp
#include "connectable.h"
#include <iostream>
using namespace std;

Connectable::Connectable() : ipAddress("0.0.0.0"), connected(false) {}

void Connectable::connect(const string& ip) {
    ipAddress = ip;
    connected = true;
    cout << "Connected to network at " << ipAddress << endl;
}

void Connectable::disconnect() {
    connected = false;
    cout << "Disconnected from network" << endl;
}

void Connectable::sendData(const string& data) {
    if (connected) {
        cout << "Sending data: " << data << endl;
    }
}

Connectable::~Connectable() {}
```

**smartdevice.h**
```cpp
#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include "device.h"
#include "connectable.h"
#include <string>
using namespace std;

class SmartDevice : virtual public Device, virtual public Connectable {
protected:
    string firmwareVersion;
    
public:
    SmartDevice(string n, string fw);
    void updateFirmware(string version);
    void display() const override;
    ~SmartDevice();
};

#endif
```

**smartdevice.cpp**
```cpp
#include "smartdevice.h"
#include <iostream>
using namespace std;

SmartDevice::SmartDevice(string n, string fw) : Device(n), firmwareVersion(fw) {
    cout << "SmartDevice created: FW v" << firmwareVersion << endl;
}

void SmartDevice::updateFirmware(string version) {
    firmwareVersion = version;
    cout << name << " firmware updated to v" << version << endl;
}

void SmartDevice::display() const {
    Device::display();
    cout << "Firmware: v" << firmwareVersion << endl;
    cout << "Network: " << (connected ? "Connected" : "Disconnected") 
         << " (" << ipAddress << ")" << endl;
}

SmartDevice::~SmartDevice() {
    cout << "SmartDevice destroyed: " << name << endl;
}
```

**smartlight.h**
```cpp
#ifndef SMARTLIGHT_H
#define SMARTLIGHT_H

#include "smartdevice.h"
#include <string>
using namespace std;

class SmartLight : public SmartDevice {
private:
    int brightness;
    string color;
    
public:
    SmartLight(string n, string fw, string col);
    void setBrightness(int level);
    void setColor(string col);
    void display() const override;
    ~SmartLight();
};

#endif
```

**smartlight.cpp**
```cpp
#include "smartlight.h"
#include <iostream>
#include <algorithm>
using namespace std;

SmartLight::SmartLight(string n, string fw, string col) 
    : Device(n), SmartDevice(n, fw), color(col), brightness(100) {
    cout << "SmartLight created: " << color << " light" << endl;
}

void SmartLight::setBrightness(int level) {
    brightness = min(100, max(0, level));
    cout << name << " brightness set to " << brightness << "%" << endl;
}

void SmartLight::setColor(string col) {
    color = col;
    cout << name << " color set to " << color << endl;
}

void SmartLight::display() const {
    SmartDevice::display();
    cout << "Brightness: " << brightness << "%, Color: " << color << endl;
}

SmartLight::~SmartLight() {
    cout << "SmartLight destroyed: " << name << endl;
}
```

**smartplug.h**
```cpp
#ifndef SMARTPLUG_H
#define SMARTPLUG_H

#include "smartdevice.h"

class SmartPlug : public SmartDevice {
private:
    double powerConsumption;
    bool applianceOn;
    
public:
    SmartPlug(string n, string fw);
    void toggleAppliance();
    void recordPower(double watts);
    void display() const override;
    ~SmartPlug();
};

#endif
```

**smartplug.cpp**
```cpp
#include "smartplug.h"
#include <iostream>
using namespace std;

SmartPlug::SmartPlug(string n, string fw) 
    : Device(n), SmartDevice(n, fw), powerConsumption(0), applianceOn(false) {
    cout << "SmartPlug created" << endl;
}

void SmartPlug::toggleAppliance() {
    applianceOn = !applianceOn;
    cout << name << " appliance " << (applianceOn ? "ON" : "OFF") << endl;
}

void SmartPlug::recordPower(double watts) {
    powerConsumption = watts;
    cout << "Power consumption: " << powerConsumption << "W" << endl;
}

void SmartPlug::display() const {
    SmartDevice::display();
    cout << "Appliance: " << (applianceOn ? "ON" : "OFF") << endl;
    cout << "Power: " << powerConsumption << "W" << endl;
}

SmartPlug::~SmartPlug() {
    cout << "SmartPlug destroyed: " << name << endl;
}
```

**securitycamera.h**
```cpp
#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "smartdevice.h"
#include <vector>
#include <string>
using namespace std;

class SecurityCamera : public SmartDevice {
private:
    bool recording;
    string resolution;
    vector<string> motionEvents;
    
public:
    SecurityCamera(string n, string fw, string res);
    void startRecording();
    void stopRecording();
    void detectMotion();
    void display() const override;
    ~SecurityCamera();
};

#endif
```

**securitycamera.cpp**
```cpp
#include "securitycamera.h"
#include <iostream>
#include <ctime>
using namespace std;

SecurityCamera::SecurityCamera(string n, string fw, string res) 
    : Device(n), SmartDevice(n, fw), resolution(res), recording(false) {
    cout << "SecurityCamera created: " << resolution << " resolution" << endl;
}

void SecurityCamera::startRecording() {
    recording = true;
    cout << name << " started recording" << endl;
}

void SecurityCamera::stopRecording() {
    recording = false;
    cout << name << " stopped recording" << endl;
}

void SecurityCamera::detectMotion() {
    cout << name << " detected motion!" << endl;
    motionEvents.push_back("Motion at " + to_string(time(nullptr)));
}

void SecurityCamera::display() const {
    SmartDevice::display();
    cout << "Resolution: " << resolution << endl;
    cout << "Recording: " << (recording ? "Yes" : "No") << endl;
    cout << "Motion events: " << motionEvents.size() << endl;
}

SecurityCamera::~SecurityCamera() {
    cout << "SecurityCamera destroyed: " << name << endl;
}
```

**smarthomehub.h**
```cpp
#ifndef SMARTHOMEHUB_H
#define SMARTHOMEHUB_H

#include "device.h"
#include "connectable.h"
#include "smartdevice.h"
#include <vector>
#include <string>
using namespace std;

class SmartHomeHub : public Device, public Connectable {
private:
    vector<SmartDevice*> devices;
    string hubName;
    
public:
    SmartHomeHub(string n, string hub);
    void addDevice(SmartDevice* device);
    void controlAll(const string& command);
    void display() const override;
    ~SmartHomeHub();
};

#endif
```

**smarthomehub.cpp**
```cpp
#include "smarthomehub.h"
#include <iostream>
using namespace std;

SmartHomeHub::SmartHomeHub(string n, string hub) : Device(n), hubName(hub) {
    cout << "SmartHomeHub created: " << hubName << endl;
}

void SmartHomeHub::addDevice(SmartDevice* device) {
    devices.push_back(device);
    cout << "Added " << device->name << " to hub" << endl;
}

void SmartHomeHub::controlAll(const string& command) {
    cout << "Hub " << hubName << " sending command: " << command << endl;
    for (auto device : devices) {
        if (command == "ON") device->turnOn();
        else if (command == "OFF") device->turnOff();
    }
}

void SmartHomeHub::display() const {
    Device::display();
    cout << "Hub Name: " << hubName << endl;
    cout << "Network: " << (connected ? "Connected" : "Disconnected") << endl;
    cout << "Devices: " << devices.size() << " devices" << endl;
}

SmartHomeHub::~SmartHomeHub() {
    cout << "SmartHomeHub destroyed: " << hubName << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "smartlight.h"
#include "smartplug.h"
#include "securitycamera.h"
#include "smarthomehub.h"
using namespace std;

int main() {
    SmartLight light("Living Room", "1.0", "White");
    SmartPlug plug("Coffee Maker", "1.2");
    SecurityCamera camera("Front Door", "2.0", "1080p");
    SmartHomeHub hub("Main Hub", "Home Assistant");
    
    light.connect("192.168.1.10");
    plug.connect("192.168.1.11");
    hub.connect("192.168.1.1");
    
    hub.addDevice(&light);
    hub.addDevice(&plug);
    
    light.turnOn();
    light.setBrightness(75);
    plug.toggleAppliance();
    hub.controlAll("OFF");
    
    light.display();
    plug.display();
    hub.display();
    
    return 0;
}
```

## Virtual Inheritance Rules

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructor" << endl; }
    virtual ~Base() {}
};

class Derived1 : virtual public Base {
public:
    Derived1() { cout << "Derived1 constructor" << endl; }
};

class Derived2 : virtual public Base {
public:
    Derived2() { cout << "Derived2 constructor" << endl; }
};

class MostDerived : public Derived1, public Derived2 {
public:
    MostDerived() { cout << "MostDerived constructor" << endl; }
};

int main() {
    MostDerived md;
    // Output:
    // Base constructor (only once!)
    // Derived1 constructor
    // Derived2 constructor
    // MostDerived constructor
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Diamond problem without virtual | Multiple base copies | Use virtual inheritance |
| Constructor initialization order | Wrong initialization | Virtual base first, then in order |
| Object slicing | Loss of derived data | Use pointers/references |
| Forgetting virtual destructor | Memory leak | Make base destructors virtual |
| Ambiguous member access | Compilation error | Use scope resolution or override |

## Summary

- **Hybrid inheritance** combines multiple inheritance types
- **Virtual inheritance** solves diamond problem
- **Constructor order**: Virtual base classes first, then non-virtual in declaration order
- **Destructor order**: Reverse of constructor order
- Used in complex hierarchies where classes have multiple roles
- Common in **design patterns** and **framework design**

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class Base1 {
public:
    Base1() { cout << "Base1" << endl; }
    virtual void show() { cout << "Base1 show" << endl; }
    virtual ~Base1() {}
};

class Base2 {
public:
    Base2() { cout << "Base2" << endl; }
    virtual void show() { cout << "Base2 show" << endl; }
    virtual ~Base2() {}
};

class Derived : public Base1, public Base2 {
public:
    Derived() { cout << "Derived" << endl; }
    void show() override {
        Base1::show();
        Base2::show();
        cout << "Derived show" << endl;
    }
};

int main() {
    Derived d;
    d.show();
    return 0;
}
```

### Type 2: Multiple Files

**base1.h**
```cpp
#ifndef BASE1_H
#define BASE1_H

class Base1 {
public:
    Base1();
    virtual void show();
    virtual ~Base1();
};

#endif
```

**base1.cpp**
```cpp
#include "base1.h"
#include <iostream>
using namespace std;

Base1::Base1() { cout << "Base1" << endl; }
void Base1::show() { cout << "Base1 show" << endl; }
Base1::~Base1() {}
```

**base2.h**
```cpp
#ifndef BASE2_H
#define BASE2_H

class Base2 {
public:
    Base2();
    virtual void show();
    virtual ~Base2();
};

#endif
```

**base2.cpp**
```cpp
#include "base2.h"
#include <iostream>
using namespace std;

Base2::Base2() { cout << "Base2" << endl; }
void Base2::show() { cout << "Base2 show" << endl; }
Base2::~Base2() {}
```

**derived.h**
```cpp
#ifndef DERIVED_H
#define DERIVED_H

#include "base1.h"
#include "base2.h"

class Derived : public Base1, public Base2 {
public:
    Derived();
    void show() override;
};

#endif
```

**derived.cpp**
```cpp
#include "derived.h"
#include <iostream>
using namespace std;

Derived::Derived() { cout << "Derived" << endl; }

void Derived::show() {
    Base1::show();
    Base2::show();
    cout << "Derived show" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "derived.h"
using namespace std;

int main() {
    Derived d;
    d.show();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*