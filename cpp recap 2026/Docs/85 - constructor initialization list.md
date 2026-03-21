# 85 - Constructor Initialization List in C++

## What is a Constructor Initialization List?
An initialization list is a way to initialize member variables before the constructor body executes. It appears after the constructor parameter list, preceded by a colon, with members initialized using parentheses or braces.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int id;
    string name;
    double gpa;
    const int year;
    static int studentCount;
    
public:
    // Constructor with initialization list
    Student(int i, string n, double g, int y) 
        : id(i), name(n), gpa(g), year(y) {
        studentCount++;
        cout << "Student created: " << name << " (ID: " << id << ")" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", GPA: " << gpa << ", Year: " << year << endl;
    }
    
    static int getCount() { return studentCount; }
};

int Student::studentCount = 0;

int main() {
    Student s1(101, "John", 3.5, 2024);
    Student s2(102, "Alice", 3.8, 2024);
    
    s1.display();
    s2.display();
    cout << "Total students: " << Student::getCount() << endl;
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### student.h
```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
private:
    int id;
    string name;
    double gpa;
    const int year;
    static int studentCount;
    
public:
    Student(int i, string n, double g, int y);
    void display() const;
    static int getCount();
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

int Student::studentCount = 0;

Student::Student(int i, string n, double g, int y) 
    : id(i), name(n), gpa(g), year(y) {
    studentCount++;
    cout << "Student created: " << name << " (ID: " << id << ")" << endl;
}

void Student::display() const {
    cout << "ID: " << id << ", Name: " << name 
         << ", GPA: " << gpa << ", Year: " << year << endl;
}

int Student::getCount() { return studentCount; }
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student s1(101, "John", 3.5, 2024);
    Student s2(102, "Alice", 3.8, 2024);
    
    s1.display();
    s2.display();
    cout << "Total: " << Student::getCount() << endl;
    
    return 0;
}
```

## Why Use Initialization Lists?

### 1. Initializing const Members
```cpp
#include <iostream>
using namespace std;

class Circle {
private:
    const double PI;
    double radius;
    
public:
    // Must use initialization list for const members
    Circle(double r) : PI(3.14159), radius(r) {
        // PI = 3.14;  // Error! Can't assign to const
    }
    
    double area() const { return PI * radius * radius; }
};

int main() {
    Circle c(5.0);
    cout << "Area: " << c.area() << endl;
    return 0;
}
```

### 2. Initializing Reference Members
```cpp
#include <iostream>
#include <string>
using namespace std;

class Logger {
public:
    void log(const string& msg) {
        cout << "[LOG] " << msg << endl;
    }
};

class Processor {
private:
    Logger& logger;  // Reference member
    string& data;    // Reference member
    
public:
    // Must use initialization list for references
    Processor(Logger& l, string& d) : logger(l), data(d) {}
    
    void process() {
        logger.log("Processing: " + data);
        data = data + "_processed";
    }
};

int main() {
    Logger logger;
    string text = "Hello";
    Processor proc(logger, text);
    
    proc.process();
    cout << "Result: " << text << endl;
    
    return 0;
}
```

### 3. Efficiency (Avoids Default Construction)
```cpp
#include <iostream>
#include <string>
using namespace std;

class Name {
private:
    string firstName;
    string lastName;
    
public:
    // Without initialization list - default construct then assign
    Name(string first, string last) {
        firstName = first;   // Default construct, then assign
        lastName = last;     // Default construct, then assign
        cout << "Name created with assignment" << endl;
    }
};

class EfficientName {
private:
    string firstName;
    string lastName;
    
public:
    // With initialization list - direct construction
    EfficientName(string first, string last) 
        : firstName(first), lastName(last) {
        cout << "Name created with initialization list" << endl;
    }
};

int main() {
    Name n1("John", "Doe");
    EfficientName n2("Jane", "Smith");
    
    return 0;
}
```

### 4. Initializing Base Class
```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    
public:
    Person(string n, int a) : name(n), age(a) {
        cout << "Person constructor: " << name << endl;
    }
};

class Student : public Person {
private:
    int rollNumber;
    
public:
    // Must initialize base class in initialization list
    Student(string n, int a, int roll) 
        : Person(n, a), rollNumber(roll) {
        cout << "Student constructor: " << name << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age 
             << ", Roll: " << rollNumber << endl;
    }
};

int main() {
    Student s("John", 20, 101);
    s.display();
    
    return 0;
}
```

## Order of Initialization

```cpp
#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "A constructed" << endl; }
};

class B {
public:
    B() { cout << "B constructed" << endl; }
};

class C {
private:
    B b;
    A a;
    
public:
    // Order in initialization list doesn't matter!
    // Members are initialized in declaration order
    C() : a(), b() {
        cout << "C constructed" << endl;
    }
};

int main() {
    C c;  // Output: B constructed, A constructed, C constructed
          // Because b declared before a in class
    return 0;
}
```

## Practical Examples

### Example 1: Employee Class with Complex Initialization

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Employee {
private:
    const int id;
    string name;
    double salary;
    time_t hireDate;
    static int nextId;
    
    // Private helper
    time_t getCurrentTime() {
        return time(nullptr);
    }
    
public:
    // Constructor with initialization list
    Employee(string n, double s) 
        : id(nextId++), name(n), salary(s), hireDate(getCurrentTime()) {
        cout << "Employee created: " << name << " (ID: " << id << ")" << endl;
    }
    
    // Constructor with name only (default salary)
    Employee(string n) 
        : id(nextId++), name(n), salary(30000.0), hireDate(getCurrentTime()) {
        cout << "Employee created: " << name << " (ID: " << id << ", default salary)" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Salary: $" << salary << endl;
        cout << "Hire Date: " << ctime(&hireDate);
    }
};

int Employee::nextId = 1000;

int main() {
    Employee e1("John Doe", 50000);
    Employee e2("Jane Smith", 60000);
    Employee e3("Bob Johnson");  // Default salary
    
    cout << "\n--- Employee Details ---" << endl;
    e1.display();
    cout << endl;
    e2.display();
    cout << endl;
    e3.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**employee.h**
```cpp
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <ctime>
using namespace std;

class Employee {
private:
    const int id;
    string name;
    double salary;
    time_t hireDate;
    static int nextId;
    
    time_t getCurrentTime();
    
public:
    Employee(string n, double s);
    Employee(string n);
    void display() const;
};

#endif
```

**employee.cpp**
```cpp
#include "employee.h"
#include <iostream>
#include <ctime>
using namespace std;

int Employee::nextId = 1000;

time_t Employee::getCurrentTime() {
    return time(nullptr);
}

Employee::Employee(string n, double s) 
    : id(nextId++), name(n), salary(s), hireDate(getCurrentTime()) {
    cout << "Employee created: " << name << " (ID: " << id << ")" << endl;
}

Employee::Employee(string n) 
    : id(nextId++), name(n), salary(30000.0), hireDate(getCurrentTime()) {
    cout << "Employee created: " << name << " (ID: " << id << ", default salary)" << endl;
}

void Employee::display() const {
    cout << "ID: " << id << ", Name: " << name 
         << ", Salary: $" << salary << endl;
    cout << "Hire Date: " << ctime(&hireDate);
}
```

**main.cpp**
```cpp
#include <iostream>
#include "employee.h"
using namespace std;

int main() {
    Employee e1("John Doe", 50000);
    Employee e2("Jane Smith");
    
    e1.display();
    cout << endl;
    e2.display();
    
    return 0;
}
```

### Example 2: Matrix Class with Efficient Initialization

#### Type 1: Single File
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    vector<vector<int>> data;
    
public:
    // Constructor with initialization list
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {
        cout << "Matrix " << rows << "x" << cols << " created" << endl;
    }
    
    // Constructor with initial value
    Matrix(int r, int c, int val) : rows(r), cols(c), data(r, vector<int>(c, val)) {
        cout << "Matrix " << rows << "x" << cols << " filled with " << val << endl;
    }
    
    // Constructor from initializer list (C++11)
    Matrix(initializer_list<initializer_list<int>> list) 
        : rows(list.size()), cols(list.begin()->size()) {
        
        data.resize(rows, vector<int>(cols));
        int i = 0;
        for (auto row : list) {
            int j = 0;
            for (int val : row) {
                data[i][j++] = val;
            }
            i++;
        }
        cout << "Matrix initialized from list" << endl;
    }
    
    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    Matrix m1(3, 4);                    // Zero matrix
    Matrix m2(2, 3, 5);                 // Matrix filled with 5
    Matrix m3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};  // Initializer list
    
    cout << "\nm1 (3x4):" << endl;
    m1.display();
    
    cout << "\nm2 (2x3, filled with 5):" << endl;
    m2.display();
    
    cout << "\nm3 (3x3):" << endl;
    m3.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**matrix.h**
```cpp
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    vector<vector<int>> data;
    
public:
    Matrix(int r, int c);
    Matrix(int r, int c, int val);
    Matrix(initializer_list<initializer_list<int>> list);
    void display() const;
};

#endif
```

**matrix.cpp**
```cpp
#include "matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {
    cout << "Matrix " << rows << "x" << cols << " created" << endl;
}

Matrix::Matrix(int r, int c, int val) : rows(r), cols(c), data(r, vector<int>(c, val)) {
    cout << "Matrix " << rows << "x" << cols << " filled with " << val << endl;
}

Matrix::Matrix(initializer_list<initializer_list<int>> list) 
    : rows(list.size()), cols(list.begin()->size()) {
    
    data.resize(rows, vector<int>(cols));
    int i = 0;
    for (auto row : list) {
        int j = 0;
        for (int val : row) {
            data[i][j++] = val;
        }
        i++;
    }
    cout << "Matrix initialized from list" << endl;
}

void Matrix::display() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
}
```

**main.cpp**
```cpp
#include <iostream>
#include "matrix.h"
using namespace std;

int main() {
    Matrix m1(2, 3);
    Matrix m2(2, 2, 7);
    Matrix m3 = {{1, 2}, {3, 4}};
    
    m1.display();
    cout << endl;
    m2.display();
    cout << endl;
    m3.display();
    
    return 0;
}
```

### Example 3: Date Class with Validation

#### Type 1: Single File
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
    
    bool isValid() const {
        if (year < 1900 || year > 2100) return false;
        if (month < 1 || month > 12) return false;
        
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 
                             31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear()) daysInMonth[1] = 29;
        
        return day >= 1 && day <= daysInMonth[month - 1];
    }
    
    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    
public:
    // Constructor with validation in initialization
    Date(int d, int m, int y) : day(d), month(m), year(y) {
        if (!isValid()) {
            cout << "Invalid date! Setting to 1/1/2000" << endl;
            day = 1;
            month = 1;
            year = 2000;
        }
    }
    
    // Constructor from day of year
    Date(int dayOfYear, int y) : year(y), month(1), day(1) {
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 
                             31, 31, 30, 31, 30, 31};
        if (isLeapYear()) daysInMonth[1] = 29;
        
        int remaining = dayOfYear;
        for (int m = 0; m < 12; m++) {
            if (remaining <= daysInMonth[m]) {
                month = m + 1;
                day = remaining;
                break;
            }
            remaining -= daysInMonth[m];
        }
    }
    
    void display() const {
        cout << setfill('0') << setw(2) << day << "/"
             << setw(2) << month << "/" << year;
    }
};

int main() {
    Date d1(15, 3, 2024);
    Date d2(32, 13, 2025);  // Invalid - will be corrected
    Date d3(100, 2024);      // 100th day of 2024
    
    cout << "d1: "; d1.display(); cout << endl;
    cout << "d2: "; d2.display(); cout << endl;
    cout << "d3: "; d3.display(); cout << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**date.h**
```cpp
#ifndef DATE_H
#define DATE_H

class Date {
private:
    int day;
    int month;
    int year;
    
    bool isValid() const;
    bool isLeapYear() const;
    
public:
    Date(int d, int m, int y);
    Date(int dayOfYear, int y);
    void display() const;
};

#endif
```

**date.cpp**
```cpp
#include "date.h"
#include <iostream>
#include <iomanip>
using namespace std;

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!isValid()) {
        cout << "Invalid date! Setting to 1/1/2000" << endl;
        day = 1;
        month = 1;
        year = 2000;
    }
}

Date::Date(int dayOfYear, int y) : year(y), month(1), day(1) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 
                         31, 31, 30, 31, 30, 31};
    if (isLeapYear()) daysInMonth[1] = 29;
    
    int remaining = dayOfYear;
    for (int m = 0; m < 12; m++) {
        if (remaining <= daysInMonth[m]) {
            month = m + 1;
            day = remaining;
            break;
        }
        remaining -= daysInMonth[m];
    }
}

bool Date::isValid() const {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 
                         31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear()) daysInMonth[1] = 29;
    
    return day >= 1 && day <= daysInMonth[month - 1];
}

bool Date::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void Date::display() const {
    cout << setfill('0') << setw(2) << day << "/"
         << setw(2) << month << "/" << year;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "date.h"
using namespace std;

int main() {
    Date d1(15, 3, 2024);
    Date d2(100, 2024);
    
    cout << "d1: "; d1.display(); cout << endl;
    cout << "d2: "; d2.display(); cout << endl;
    
    return 0;
}
```

## Initialization List vs Constructor Body

```cpp
#include <iostream>
#include <string>
using namespace std;

class Demo {
private:
    const int id;
    string name;
    static int counter;
    
public:
    // Using initialization list - efficient
    Demo(string n) : id(++counter), name(n) {
        // Already initialized
    }
    
    // Not possible to do this with assignment:
    // Demo(string n) {
    //     id = ++counter;  // Error! const can't be assigned
    //     name = n;        // Works but less efficient
    // }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
    }
};

int Demo::counter = 0;

int main() {
    Demo d1("First");
    Demo d2("Second");
    
    d1.display();
    d2.display();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting colon | Syntax error | Add `:` before initialization list |
| Order mismatch | Depends on declaration order | Follow declaration order |
| Not initializing const/reference | Compilation error | Always initialize in list |
| Using parentheses for all types | Most vexing parse | Use braces for clarity |
| Duplicate initialization | Wasted work | Use initialization list, not body |

## Summary

- **Initialization list** initializes members before constructor body
- Required for **const members** and **reference members**
- More **efficient** than assigning in constructor body
- Used to call **base class constructors**
- Members initialized in **declaration order**, not list order
- Preferred way to initialize members in modern C++
- Allows **direct construction** instead of default then assign

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class MyClass {
private:
    const int id;
    string name;
    double value;
    static int counter;
    
public:
    MyClass(string n, double v) : id(++counter), name(n), value(v) {
        cout << "Created: " << name << " (ID: " << id << ")" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Value: " << value << endl;
    }
};

int MyClass::counter = 0;

int main() {
    MyClass obj1("First", 10.5);
    MyClass obj2("Second", 20.7);
    
    obj1.display();
    obj2.display();
    
    return 0;
}
```

### Type 2: Multiple Files

**myclass.h**
```cpp
#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>
using namespace std;

class MyClass {
private:
    const int id;
    string name;
    double value;
    static int counter;
    
public:
    MyClass(string n, double v);
    void display() const;
};

#endif
```

**myclass.cpp**
```cpp
#include "myclass.h"
#include <iostream>
using namespace std;

int MyClass::counter = 0;

MyClass::MyClass(string n, double v) : id(++counter), name(n), value(v) {
    cout << "Created: " << name << " (ID: " << id << ")" << endl;
}

void MyClass::display() const {
    cout << "ID: " << id << ", Name: " << name << ", Value: " << value << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "myclass.h"
using namespace std;

int main() {
    MyClass obj1("First", 10.5);
    MyClass obj2("Second", 20.7);
    
    obj1.display();
    obj2.display();
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*