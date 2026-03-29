# 113 - Overloading Stream Operators (<<, >>) in C++

## What are Stream Operators?
The stream insertion operator (`<<`) and stream extraction operator (`>>`) are used for input and output operations. Overloading them allows user-defined types to be read from and written to streams (like `cout` and `cin`) in a natural way.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    double gpa;
    
public:
    Student(string n = "", int a = 0, double g = 0.0) 
        : name(n), age(a), gpa(g) {}
    
    // Getter methods for validation
    string getName() const { return name; }
    int getAge() const { return age; }
    double getGpa() const { return gpa; }
    
    // Friend functions for stream operators
    friend ostream& operator<<(ostream& os, const Student& s);
    friend istream& operator>>(istream& is, Student& s);
};

// Output stream operator
ostream& operator<<(ostream& os, const Student& s) {
    os << "Student: " << s.name << ", Age: " << s.age << ", GPA: " << s.gpa;
    return os;
}

// Input stream operator
istream& operator>>(istream& is, Student& s) {
    cout << "Enter name: ";
    is >> s.name;
    cout << "Enter age: ";
    is >> s.age;
    cout << "Enter GPA: ";
    is >> s.gpa;
    return is;
}

int main() {
    Student s1("John", 20, 3.5);
    Student s2;
    
    // Output using overloaded <<
    cout << "Student 1: " << s1 << endl;
    
    // Input using overloaded >>
    cout << "\nEnter student details:" << endl;
    cin >> s2;
    
    // Output the entered student
    cout << "\nStudent 2: " << s2 << endl;
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### student.h
```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    double gpa;
    
public:
    Student(string n = "", int a = 0, double g = 0.0);
    string getName() const;
    int getAge() const;
    double getGpa() const;
    
    friend ostream& operator<<(ostream& os, const Student& s);
    friend istream& operator>>(istream& is, Student& s);
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student(string n, int a, double g) : name(n), age(a), gpa(g) {}

string Student::getName() const { return name; }
int Student::getAge() const { return age; }
double Student::getGpa() const { return gpa; }

ostream& operator<<(ostream& os, const Student& s) {
    os << "Student: " << s.name << ", Age: " << s.age << ", GPA: " << s.gpa;
    return os;
}

istream& operator>>(istream& is, Student& s) {
    cout << "Enter name: ";
    is >> s.name;
    cout << "Enter age: ";
    is >> s.age;
    cout << "Enter GPA: ";
    is >> s.gpa;
    return is;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student s1("John", 20, 3.5);
    Student s2;
    
    cout << s1 << endl;
    cin >> s2;
    cout << s2 << endl;
    
    return 0;
}
```

## Key Principles of Stream Operator Overloading

### 1. Must be Friend Functions (Usually)
```cpp
class MyClass {
    // Must be friend to access private members
    friend ostream& operator<<(ostream& os, const MyClass& obj);
    friend istream& operator>>(istream& is, MyClass& obj);
};
```

### 2. Return Reference to Stream for Chaining
```cpp
ostream& operator<<(ostream& os, const MyClass& obj) {
    os << obj.data;
    return os;  // Allows cout << a << b << c;
}
```

### 3. Formatting and Error Handling
```cpp
istream& operator>>(istream& is, MyClass& obj) {
    is >> obj.data;
    if (is.fail()) {
        // Handle error
        obj.data = defaultValue;
    }
    return is;
}
```

## Practical Examples

### Example 1: Complex Number with Formatted Output

#### Type 1: Single File
```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);
};

ostream& operator<<(ostream& os, const Complex& c) {
    os << fixed << setprecision(2);
    os << c.real;
    if (c.imag >= 0) os << "+";
    os << c.imag << "i";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    cout << "Enter real part: ";
    is >> c.real;
    cout << "Enter imaginary part: ";
    is >> c.imag;
    return is;
}

int main() {
    Complex c1(3.14159, 2.71828);
    Complex c2;
    
    cout << "c1 = " << c1 << endl;
    cout << "\nEnter a complex number:" << endl;
    cin >> c2;
    cout << "You entered: " << c2 << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**complex.h**
```cpp
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0);
    
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);
};

#endif
```

**complex.cpp**
```cpp
#include "complex.h"
#include <iostream>
#include <iomanip>
using namespace std;

Complex::Complex(double r, double i) : real(r), imag(i) {}

ostream& operator<<(ostream& os, const Complex& c) {
    os << fixed << setprecision(2);
    os << c.real;
    if (c.imag >= 0) os << "+";
    os << c.imag << "i";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    cout << "Enter real: ";
    is >> c.real;
    cout << "Enter imag: ";
    is >> c.imag;
    return is;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "complex.h"
using namespace std;

int main() {
    Complex c1(3.14, 2.71);
    Complex c2;
    
    cout << c1 << endl;
    cin >> c2;
    cout << c2 << endl;
    
    return 0;
}
```

### Example 2: Point Class with Multiple Formats

#### Type 1: Single File
```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    // Multiple output formats
    friend ostream& operator<<(ostream& os, const Point& p);
    friend istream& operator>>(istream& is, Point& p);
    
    // Custom format methods
    string toJson() const {
        return "{\"x\":" + to_string(x) + ",\"y\":" + to_string(y) + "}";
    }
    
    string toCsv() const {
        return to_string(x) + "," + to_string(y);
    }
};

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << fixed << setprecision(2) << p.x << ", " << p.y << ")";
    return os;
}

istream& operator>>(istream& is, Point& p) {
    char dummy;
    is >> dummy >> p.x >> dummy >> p.y >> dummy;
    return is;
}

int main() {
    Point p1(3.5, 2.5);
    Point p2;
    
    cout << "p1 = " << p1 << endl;
    cout << "JSON: " << p1.toJson() << endl;
    cout << "CSV: " << p1.toCsv() << endl;
    
    cout << "\nEnter point in format (x, y): ";
    cin >> p2;
    cout << "You entered: " << p2 << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**point.h**
```cpp
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
using namespace std;

class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0);
    
    friend ostream& operator<<(ostream& os, const Point& p);
    friend istream& operator>>(istream& is, Point& p);
    
    string toJson() const;
    string toCsv() const;
};

#endif
```

**point.cpp**
```cpp
#include "point.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

Point::Point(double x, double y) : x(x), y(y) {}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << fixed << setprecision(2) << p.x << ", " << p.y << ")";
    return os;
}

istream& operator>>(istream& is, Point& p) {
    char dummy;
    is >> dummy >> p.x >> dummy >> p.y >> dummy;
    return is;
}

string Point::toJson() const {
    return "{\"x\":" + to_string(x) + ",\"y\":" + to_string(y) + "}";
}

string Point::toCsv() const {
    return to_string(x) + "," + to_string(y);
}
```

**main.cpp**
```cpp
#include <iostream>
#include "point.h"
using namespace std;

int main() {
    Point p1(3.5, 2.5);
    Point p2;
    
    cout << p1 << endl;
    cout << p1.toJson() << endl;
    
    cout << "Enter point (x, y): ";
    cin >> p2;
    cout << p2 << endl;
    
    return 0;
}
```

### Example 3: Vector3D with Formatted Output

#### Type 1: Single File
```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Vector3D {
private:
    double x, y, z;
    
public:
    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    friend ostream& operator<<(ostream& os, const Vector3D& v);
    friend istream& operator>>(istream& is, Vector3D& v);
    
    // Additional formatting methods
    void setPrecision(int p) {
        cout << fixed << setprecision(p);
    }
    
    string toTuple() const {
        return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
    }
    
    double magnitude() const {
        return sqrt(x*x + y*y + z*z);
    }
};

ostream& operator<<(ostream& os, const Vector3D& v) {
    os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
    return os;
}

istream& operator>>(istream& is, Vector3D& v) {
    char c;
    is >> c >> v.x >> c >> v.y >> c >> v.z >> c;
    return is;
}

int main() {
    Vector3D v1(1.5, 2.5, 3.5);
    Vector3D v2;
    
    cout << fixed << setprecision(1);
    cout << "v1 = " << v1 << endl;
    cout << "Magnitude: " << v1.magnitude() << endl;
    cout << "Tuple: " << v1.toTuple() << endl;
    
    cout << "\nEnter vector [x, y, z]: ";
    cin >> v2;
    cout << "You entered: " << v2 << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**vector3d.h**
```cpp
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <string>
using namespace std;

class Vector3D {
private:
    double x, y, z;
    
public:
    Vector3D(double x = 0, double y = 0, double z = 0);
    
    friend ostream& operator<<(ostream& os, const Vector3D& v);
    friend istream& operator>>(istream& is, Vector3D& v);
    
    string toTuple() const;
    double magnitude() const;
};

#endif
```

**vector3d.cpp**
```cpp
#include "vector3d.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

ostream& operator<<(ostream& os, const Vector3D& v) {
    os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
    return os;
}

istream& operator>>(istream& is, Vector3D& v) {
    char c;
    is >> c >> v.x >> c >> v.y >> c >> v.z >> c;
    return is;
}

string Vector3D::toTuple() const {
    return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
}

double Vector3D::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}
```

**main.cpp**
```cpp
#include <iostream>
#include "vector3d.h"
using namespace std;

int main() {
    Vector3D v1(1.5, 2.5, 3.5);
    Vector3D v2;
    
    cout << v1 << endl;
    cout << "Enter vector [x, y, z]: ";
    cin >> v2;
    cout << v2 << endl;
    
    return 0;
}
```

### Example 4: Date Class with Validation

#### Type 1: Single File
```cpp
#include <iostream>
#include <iomanip>
#include <ctime>
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
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {
        if (!isValid()) {
            day = 1;
            month = 1;
            year = 2000;
        }
    }
    
    friend ostream& operator<<(ostream& os, const Date& d);
    friend istream& operator>>(istream& is, Date& d);
};

ostream& operator<<(ostream& os, const Date& d) {
    os << setfill('0') << setw(2) << d.day << "/"
       << setw(2) << d.month << "/" << d.year;
    return os;
}

istream& operator>>(istream& is, Date& d) {
    char slash;
    is >> d.day >> slash >> d.month >> slash >> d.year;
    if (!d.isValid()) {
        d = Date();  // Reset to default
        is.setstate(ios::failbit);
    }
    return is;
}

int main() {
    Date d1(15, 3, 2024);
    Date d2;
    
    cout << "Date 1: " << d1 << endl;
    
    cout << "Enter date (dd/mm/yyyy): ";
    cin >> d2;
    
    if (cin.fail()) {
        cout << "Invalid date entered!" << endl;
        cin.clear();
    } else {
        cout << "Date 2: " << d2 << endl;
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**date.h**
```cpp
#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
    
    bool isValid() const;
    bool isLeapYear() const;
    
public:
    Date(int d = 1, int m = 1, int y = 2000);
    
    friend ostream& operator<<(ostream& os, const Date& d);
    friend istream& operator>>(istream& is, Date& d);
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
        day = 1;
        month = 1;
        year = 2000;
    }
}

bool Date::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::isValid() const {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 
                         31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear()) daysInMonth[1] = 29;
    
    return day >= 1 && day <= daysInMonth[month - 1];
}

ostream& operator<<(ostream& os, const Date& d) {
    os << setfill('0') << setw(2) << d.day << "/"
       << setw(2) << d.month << "/" << d.year;
    return os;
}

istream& operator>>(istream& is, Date& d) {
    char slash;
    is >> d.day >> slash >> d.month >> slash >> d.year;
    if (!d.isValid()) {
        d = Date();
        is.setstate(ios::failbit);
    }
    return is;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "date.h"
using namespace std;

int main() {
    Date d1(15, 3, 2024);
    Date d2;
    
    cout << d1 << endl;
    cout << "Enter date (dd/mm/yyyy): ";
    cin >> d2;
    cout << d2 << endl;
    
    return 0;
}
```

### Example 5: Employee Class with File I/O

#### Type 1: Single File
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Employee {
private:
    int id;
    string name;
    double salary;
    
public:
    Employee(int i = 0, string n = "", double s = 0.0) : id(i), name(n), salary(s) {}
    
    friend ostream& operator<<(ostream& os, const Employee& e);
    friend istream& operator>>(istream& is, Employee& e);
    
    // File I/O operators
    friend ofstream& operator<<(ofstream& ofs, const Employee& e);
    friend ifstream& operator>>(ifstream& ifs, Employee& e);
};

// Console output
ostream& operator<<(ostream& os, const Employee& e) {
    os << "ID: " << e.id << ", Name: " << e.name << ", Salary: $" << e.salary;
    return os;
}

// Console input
istream& operator>>(istream& is, Employee& e) {
    cout << "Enter ID: ";
    is >> e.id;
    cout << "Enter Name: ";
    is >> e.name;
    cout << "Enter Salary: ";
    is >> e.salary;
    return is;
}

// File output
ofstream& operator<<(ofstream& ofs, const Employee& e) {
    ofs << e.id << "\n" << e.name << "\n" << e.salary << "\n";
    return ofs;
}

// File input
ifstream& operator>>(ifstream& ifs, Employee& e) {
    ifs >> e.id;
    ifs.ignore();
    getline(ifs, e.name);
    ifs >> e.salary;
    return ifs;
}

int main() {
    // Console I/O
    Employee emp1(101, "John Doe", 50000);
    Employee emp2;
    
    cout << "Employee 1: " << emp1 << endl;
    
    cout << "\nEnter employee details:" << endl;
    cin >> emp2;
    cout << "Employee 2: " << emp2 << endl;
    
    // File I/O
    ofstream outFile("employees.txt");
    outFile << emp1 << emp2;
    outFile.close();
    
    ifstream inFile("employees.txt");
    vector<Employee> employees;
    Employee temp;
    
    while (inFile >> temp) {
        employees.push_back(temp);
    }
    inFile.close();
    
    cout << "\nEmployees read from file:" << endl;
    for (const auto& e : employees) {
        cout << e << endl;
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**employee.h**
```cpp
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Employee {
private:
    int id;
    string name;
    double salary;
    
public:
    Employee(int i = 0, string n = "", double s = 0.0);
    
    friend ostream& operator<<(ostream& os, const Employee& e);
    friend istream& operator>>(istream& is, Employee& e);
    friend ofstream& operator<<(ofstream& ofs, const Employee& e);
    friend ifstream& operator>>(ifstream& ifs, Employee& e);
};

#endif
```

**employee.cpp**
```cpp
#include "employee.h"
#include <iostream>
#include <fstream>
using namespace std;

Employee::Employee(int i, string n, double s) : id(i), name(n), salary(s) {}

ostream& operator<<(ostream& os, const Employee& e) {
    os << "ID: " << e.id << ", Name: " << e.name << ", Salary: $" << e.salary;
    return os;
}

istream& operator>>(istream& is, Employee& e) {
    cout << "Enter ID: ";
    is >> e.id;
    cout << "Enter Name: ";
    is >> e.name;
    cout << "Enter Salary: ";
    is >> e.salary;
    return is;
}

ofstream& operator<<(ofstream& ofs, const Employee& e) {
    ofs << e.id << "\n" << e.name << "\n" << e.salary << "\n";
    return ofs;
}

ifstream& operator>>(ifstream& ifs, Employee& e) {
    ifs >> e.id;
    ifs.ignore();
    getline(ifs, e.name);
    ifs >> e.salary;
    return ifs;
}
```

**main.cpp**
```cpp
#include <iostream>
#include <fstream>
#include "employee.h"
using namespace std;

int main() {
    Employee emp1(101, "John", 50000);
    Employee emp2;
    
    cout << emp1 << endl;
    
    ofstream out("employees.txt");
    out << emp1;
    out.close();
    
    ifstream in("employees.txt");
    in >> emp2;
    in.close();
    
    cout << "From file: " << emp2 << endl;
    
    return 0;
}
```

## Stream Operator Rules

| Rule | Description |
|------|-------------|
| Must be friend | Usually needs access to private members |
| Return reference | Return `ostream&` or `istream&` for chaining |
| Format properly | Handle spacing, precision, and formatting |
| Error handling | Check `is.fail()` and handle invalid input |
| Consistent formatting | Maintain predictable output format |

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Not returning stream reference | Cannot chain operators | Return `os` or `is` |
| Making them member functions | Left operand must be stream | Use friend functions |
| Ignoring formatting flags | Inconsistent output | Respect `setw`, `setprecision`, etc. |
| No error handling | Invalid input crashes | Check `is.fail()` |
| Forgetting whitespace | Input parsing issues | Use `ws` or proper delimiters |

## Summary

- **Stream operators** must be overloaded as **friend functions**
- **Return reference** to stream for chaining (`cout << a << b`)
- **Output operator** (`<<`) should be `const` (doesn't modify object)
- **Input operator** (`>>`) modifies object, so not const
- **Formatting** should respect manipulators like `setw`, `setprecision`
- **Error handling** important for input validation
- Can be used for **file I/O** with `ifstream`/`ofstream`

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class MyClass {
private:
    int data;
    
public:
    MyClass(int d = 0) : data(d) {}
    
    friend ostream& operator<<(ostream& os, const MyClass& obj) {
        os << obj.data;
        return os;
    }
    
    friend istream& operator>>(istream& is, MyClass& obj) {
        is >> obj.data;
        return is;
    }
};

int main() {
    MyClass a(42), b;
    cout << "a = " << a << endl;
    cout << "Enter value: ";
    cin >> b;
    cout << "b = " << b << endl;
    return 0;
}
```

### Type 2: Multiple Files

**myclass.h**
```cpp
#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>
using namespace std;

class MyClass {
private:
    int data;
    
public:
    MyClass(int d = 0);
    
    friend ostream& operator<<(ostream& os, const MyClass& obj);
    friend istream& operator>>(istream& is, MyClass& obj);
};

#endif
```

**myclass.cpp**
```cpp
#include "myclass.h"
using namespace std;

MyClass::MyClass(int d) : data(d) {}

ostream& operator<<(ostream& os, const MyClass& obj) {
    os << obj.data;
    return os;
}

istream& operator>>(istream& is, MyClass& obj) {
    is >> obj.data;
    return is;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "myclass.h"
using namespace std;

int main() {
    MyClass obj(42);
    cout << obj << endl;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*