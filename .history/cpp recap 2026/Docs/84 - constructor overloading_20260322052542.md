# 84 - Constructor Overloading in C++

## What is Constructor Overloading?
Constructor overloading allows a class to have multiple constructors with different parameter lists. This provides flexibility in how objects can be created and initialized.

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
    
public:
    // Constructor 1: No parameters (default)
    Student() {
        id = 0;
        name = "Unknown";
        gpa = 0.0;
        cout << "Default constructor called" << endl;
    }
    
    // Constructor 2: Only ID
    Student(int i) {
        id = i;
        name = "Unknown";
        gpa = 0.0;
        cout << "Constructor with ID called" << endl;
    }
    
    // Constructor 3: ID and name
    Student(int i, string n) {
        id = i;
        name = n;
        gpa = 0.0;
        cout << "Constructor with ID and name called" << endl;
    }
    
    // Constructor 4: All parameters
    Student(int i, string n, double g) {
        id = i;
        name = n;
        gpa = g;
        cout << "Constructor with all parameters called" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", GPA: " << gpa << endl;
    }
};

int main() {
    Student s1;                    // Default constructor
    Student s2(101);               // Constructor with ID
    Student s3(102, "John");       // Constructor with ID and name
    Student s4(103, "Alice", 3.8); // Constructor with all parameters
    
    cout << "\n--- Student Details ---" << endl;
    s1.display();
    s2.display();
    s3.display();
    s4.display();
    
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
    
public:
    Student();
    Student(int i);
    Student(int i, string n);
    Student(int i, string n, double g);
    void display() const;
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student() {
    id = 0;
    name = "Unknown";
    gpa = 0.0;
    cout << "Default constructor called" << endl;
}

Student::Student(int i) {
    id = i;
    name = "Unknown";
    gpa = 0.0;
    cout << "Constructor with ID called" << endl;
}

Student::Student(int i, string n) {
    id = i;
    name = n;
    gpa = 0.0;
    cout << "Constructor with ID and name called" << endl;
}

Student::Student(int i, string n, double g) {
    id = i;
    name = n;
    gpa = g;
    cout << "Constructor with all parameters called" << endl;
}

void Student::display() const {
    cout << "ID: " << id << ", Name: " << name << ", GPA: " << gpa << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student s1;
    Student s2(101);
    Student s3(102, "John");
    Student s4(103, "Alice", 3.8);
    
    s1.display();
    s2.display();
    s3.display();
    s4.display();
    
    return 0;
}
```

## Different Ways to Overload Constructors

```cpp
#include <iostream>
#include <string>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
    
public:
    // 1. Default constructor
    Rectangle() : length(1.0), width(1.0) {
        cout << "Default rectangle created" << endl;
    }
    
    // 2. Constructor with one parameter (square)
    Rectangle(double side) : length(side), width(side) {
        cout << "Square created: " << side << "x" << side << endl;
    }
    
    // 3. Constructor with two parameters
    Rectangle(double l, double w) : length(l), width(w) {
        cout << "Rectangle created: " << length << "x" << width << endl;
    }
    
    // 4. Constructor with string parameter (for parsing)
    Rectangle(string dimensions) {
        size_t comma = dimensions.find(',');
        length = stod(dimensions.substr(0, comma));
        width = stod(dimensions.substr(comma + 1));
        cout << "Rectangle parsed: " << length << "x" << width << endl;
    }
    
    double area() const { return length * width; }
    double perimeter() const { return 2 * (length + width); }
    
    void display() const {
        cout << "Length: " << length << ", Width: " << width 
             << ", Area: " << area() << endl;
    }
};

int main() {
    Rectangle r1;                    // Default
    Rectangle r2(5.0);               // Square
    Rectangle r3(4.0, 6.0);          // Rectangle
    Rectangle r4("3.5,7.5");         // String parsing
    
    cout << "\n--- Rectangles ---" << endl;
    r1.display();
    r2.display();
    r3.display();
    r4.display();
    
    return 0;
}
```

## Constructor Overloading with Default Arguments

```cpp
#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    int quantity;
    
public:
    // Using default arguments instead of multiple overloads
    Product(int i = 0, string n = "Unknown", double p = 0.0, int q = 0) 
        : id(i), name(n), price(p), quantity(q) {
        cout << "Product created: " << name << " (ID: " << id << ")" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Price: $" << price << ", Qty: " << quantity << endl;
    }
};

int main() {
    Product p1;                      // All defaults
    Product p2(101);                 // ID provided
    Product p3(102, "Laptop");       // ID and name
    Product p4(103, "Mouse", 29.99); // ID, name, price
    Product p5(104, "Keyboard", 79.99, 10); // All provided
    
    p1.display();
    p2.display();
    p3.display();
    p4.display();
    p5.display();
    
    return 0;
}
```

## Constructor Overloading vs Default Arguments

```cpp
#include <iostream>
#include <string>
using namespace std;

// Approach 1: Multiple overloaded constructors
class EmployeeOverload {
private:
    int id;
    string name;
    double salary;
    
public:
    EmployeeOverload() : id(0), name("Unknown"), salary(0) {
        cout << "Default constructor" << endl;
    }
    
    EmployeeOverload(int i) : id(i), name("Unknown"), salary(0) {
        cout << "Constructor with ID" << endl;
    }
    
    EmployeeOverload(int i, string n) : id(i), name(n), salary(0) {
        cout << "Constructor with ID and name" << endl;
    }
    
    EmployeeOverload(int i, string n, double s) : id(i), name(n), salary(s) {
        cout << "Constructor with all parameters" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Salary: $" << salary << endl;
    }
};

// Approach 2: Single constructor with default arguments
class EmployeeDefault {
private:
    int id;
    string name;
    double salary;
    
public:
    EmployeeDefault(int i = 0, string n = "Unknown", double s = 0) 
        : id(i), name(n), salary(s) {
        cout << "Single constructor with defaults" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Salary: $" << salary << endl;
    }
};

int main() {
    cout << "=== Overloaded Constructors ===" << endl;
    EmployeeOverload e1;
    EmployeeOverload e2(101);
    EmployeeOverload e3(102, "John");
    EmployeeOverload e4(103, "Alice", 50000);
    
    cout << "\n=== Single Constructor with Defaults ===" << endl;
    EmployeeDefault d1;
    EmployeeDefault d2(201);
    EmployeeDefault d3(202, "Bob");
    EmployeeDefault d4(203, "Carol", 60000);
    
    return 0;
}
```

## Practical Examples

### Example 1: Point Class with Multiple Constructors

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double x, y;
    
public:
    // Default constructor - origin
    Point() : x(0), y(0) {
        cout << "Point at origin" << endl;
    }
    
    // Constructor with single value (both coordinates same)
    Point(double val) : x(val), y(val) {
        cout << "Point at (" << x << ", " << y << ")" << endl;
    }
    
    // Constructor with two values
    Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {
        cout << "Point at (" << x << ", " << y << ")" << endl;
    }
    
    // Copy constructor
    Point(const Point& other) : x(other.x), y(other.y) {
        cout << "Copy of point at (" << x << ", " << y << ")" << endl;
    }
    
    double distanceFromOrigin() const {
        return sqrt(x*x + y*y);
    }
    
    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx*dx + dy*dy);
    }
    
    void display() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Point p1;           // Origin
    Point p2(5);        // (5,5)
    Point p3(3, 4);     // (3,4)
    Point p4(p3);       // Copy of p3
    
    cout << "\n--- Points ---" << endl;
    cout << "p1: "; p1.display();
    cout << "p2: "; p2.display();
    cout << "p3: "; p3.display();
    cout << "p4: "; p4.display();
    
    cout << "\nDistance from origin: " << p3.distanceFromOrigin() << endl;
    cout << "Distance between p2 and p3: " << p2.distanceTo(p3) << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**point.h**
```cpp
#ifndef POINT_H
#define POINT_H

class Point {
private:
    double x, y;
    
public:
    Point();
    Point(double val);
    Point(double xCoord, double yCoord);
    Point(const Point& other);
    double distanceFromOrigin() const;
    double distanceTo(const Point& other) const;
    void display() const;
};

#endif
```

**point.cpp**
```cpp
#include "point.h"
#include <iostream>
#include <cmath>
using namespace std;

Point::Point() : x(0), y(0) {
    cout << "Point at origin" << endl;
}

Point::Point(double val) : x(val), y(val) {
    cout << "Point at (" << x << ", " << y << ")" << endl;
}

Point::Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {
    cout << "Point at (" << x << ", " << y << ")" << endl;
}

Point::Point(const Point& other) : x(other.x), y(other.y) {
    cout << "Copy of point at (" << x << ", " << y << ")" << endl;
}

double Point::distanceFromOrigin() const {
    return sqrt(x*x + y*y);
}

double Point::distanceTo(const Point& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt(dx*dx + dy*dy);
}

void Point::display() const {
    cout << "(" << x << ", " << y << ")" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "point.h"
using namespace std;

int main() {
    Point p1;
    Point p2(5);
    Point p3(3, 4);
    Point p4(p3);
    
    p1.display();
    p2.display();
    p3.display();
    p4.display();
    
    return 0;
}
```

### Example 2: Date Class with Multiple Constructors

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
    // Constructor 1: Default - today's date
    Date() {
        time_t now = time(0);
        tm* local = localtime(&now);
        day = local->tm_mday;
        month = local->tm_mon + 1;
        year = local->tm_year + 1900;
        cout << "Date set to today" << endl;
    }
    
    // Constructor 2: Day, month, year
    Date(int d, int m, int y) : day(d), month(m), year(y) {
        if (!isValid()) {
            cout << "Invalid date! Setting to 1/1/2000" << endl;
            day = 1;
            month = 1;
            year = 2000;
        }
        cout << "Date created: " << *this << endl;
    }
    
    // Constructor 3: Month and year (first day of month)
    Date(int m, int y) : day(1), month(m), year(y) {
        if (!isValid()) {
            cout << "Invalid date! Setting to 1/1/2000" << endl;
            day = 1;
            month = 1;
            year = 2000;
        }
        cout << "First day of month: " << *this << endl;
    }
    
    // Constructor 4: String format "DD/MM/YYYY"
    Date(string dateStr) {
        sscanf(dateStr.c_str(), "%d/%d/%d", &day, &month, &year);
        if (!isValid()) {
            cout << "Invalid date! Setting to 1/1/2000" << endl;
            day = 1;
            month = 1;
            year = 2000;
        }
        cout << "Date parsed: " << *this << endl;
    }
    
    friend ostream& operator<<(ostream& os, const Date& d) {
        os << setfill('0') << setw(2) << d.day << "/"
           << setw(2) << d.month << "/" << d.year;
        return os;
    }
};

int main() {
    Date d1;                      // Today
    Date d2(15, 3, 2024);         // Specific date
    Date d3(5, 2024);             // First day of May 2024
    Date d4("25/12/2024");        // String format
    
    cout << "\n--- Dates ---" << endl;
    cout << "d1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    cout << "d3: " << d3 << endl;
    cout << "d4: " << d4 << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**date.h**
```cpp
#ifndef DATE_H
#define DATE_H

#include <string>
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
    Date();
    Date(int d, int m, int y);
    Date(int m, int y);
    Date(string dateStr);
    friend ostream& operator<<(ostream& os, const Date& d);
};

#endif
```

**date.cpp**
```cpp
#include "date.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdio>
using namespace std;

Date::Date() {
    time_t now = time(0);
    tm* local = localtime(&now);
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;
    cout << "Date set to today" << endl;
}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!isValid()) {
        cout << "Invalid date! Setting to 1/1/2000" << endl;
        day = 1;
        month = 1;
        year = 2000;
    }
    cout << "Date created: " << *this << endl;
}

Date::Date(int m, int y) : day(1), month(m), year(y) {
    if (!isValid()) {
        cout << "Invalid date! Setting to 1/1/2000" << endl;
        day = 1;
        month = 1;
        year = 2000;
    }
    cout << "First day of month: " << *this << endl;
}

Date::Date(string dateStr) {
    sscanf(dateStr.c_str(), "%d/%d/%d", &day, &month, &year);
    if (!isValid()) {
        cout << "Invalid date! Setting to 1/1/2000" << endl;
        day = 1;
        month = 1;
        year = 2000;
    }
    cout << "Date parsed: " << *this << endl;
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

ostream& operator<<(ostream& os, const Date& d) {
    os << setfill('0') << setw(2) << d.day << "/"
       << setw(2) << d.month << "/" << d.year;
    return os;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "date.h"
using namespace std;

int main() {
    Date d1;
    Date d2(15, 3, 2024);
    Date d3(5, 2024);
    Date d4("25/12/2024");
    
    cout << "\nd1: " << d1 << endl;
    cout << "d2: " << d2 << endl;
    cout << "d3: " << d3 << endl;
    cout << "d4: " << d4 << endl;
    
    return 0;
}
```

### Example 3: Vector3D Class with Multiple Constructors

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Vector3D {
private:
    double x, y, z;
    
public:
    // Default constructor - zero vector
    Vector3D() : x(0), y(0), z(0) {
        cout << "Zero vector created" << endl;
    }
    
    // Constructor with single value (all components same)
    Vector3D(double val) : x(val), y(val), z(val) {
        cout << "Vector with equal components: (" << x << ", " << y << ", " << z << ")" << endl;
    }
    
    // Constructor with three values
    Vector3D(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {
        cout << "Vector created: (" << x << ", " << y << ", " << z << ")" << endl;
    }
    
    // Constructor from another vector (copy)
    Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z) {
        cout << "Vector copied: (" << x << ", " << y << ", " << z << ")" << endl;
    }
    
    double magnitude() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    Vector3D normalize() const {
        double mag = magnitude();
        if (mag > 0) {
            return Vector3D(x/mag, y/mag, z/mag);
        }
        return Vector3D(0, 0, 0);
    }
    
    Vector3D add(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    
    double dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    Vector3D cross(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    void display() const {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }
};

int main() {
    Vector3D v1;                    // Zero vector
    Vector3D v2(5);                 // (5,5,5)
    Vector3D v3(1, 2, 3);           // (1,2,3)
    Vector3D v4(v3);                // Copy of v3
    
    cout << "\n--- Vectors ---" << endl;
    cout << "v1: "; v1.display();
    cout << "v2: "; v2.display();
    cout << "v3: "; v3.display();
    cout << "v4: "; v4.display();
    
    cout << "\nMagnitude of v3: " << v3.magnitude() << endl;
    cout << "Normalized v3: "; v3.normalize().display();
    
    Vector3D sum = v2.add(v3);
    cout << "v2 + v3: "; sum.display();
    
    cout << "Dot product v2 · v3: " << v2.dot(v3) << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**vector3d.h**
```cpp
#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D {
private:
    double x, y, z;
    
public:
    Vector3D();
    Vector3D(double val);
    Vector3D(double xVal, double yVal, double zVal);
    Vector3D(const Vector3D& other);
    double magnitude() const;
    Vector3D normalize() const;
    Vector3D add(const Vector3D& other) const;
    double dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;
    void display() const;
};

#endif
```

**vector3d.cpp**
```cpp
#include "vector3d.h"
#include <iostream>
#include <cmath>
using namespace std;

Vector3D::Vector3D() : x(0), y(0), z(0) {
    cout << "Zero vector created" << endl;
}

Vector3D::Vector3D(double val) : x(val), y(val), z(val) {
    cout << "Vector with equal components: (" << x << ", " << y << ", " << z << ")" << endl;
}

Vector3D::Vector3D(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {
    cout << "Vector created: (" << x << ", " << y << ", " << z << ")" << endl;
}

Vector3D::Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z) {
    cout << "Vector copied: (" << x << ", " << y << ", " << z << ")" << endl;
}

double Vector3D::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::normalize() const {
    double mag = magnitude();
    if (mag > 0) {
        return Vector3D(x/mag, y/mag, z/mag);
    }
    return Vector3D(0, 0, 0);
}

Vector3D Vector3D::add(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

double Vector3D::dot(const Vector3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D& other) const {
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

void Vector3D::display() const {
    cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "vector3d.h"
using namespace std;

int main() {
    Vector3D v1;
    Vector3D v2(5);
    Vector3D v3(1, 2, 3);
    Vector3D v4(v3);
    
    v1.display();
    v2.display();
    v3.display();
    v4.display();
    
    Vector3D sum = v2.add(v3);
    cout << "Sum: "; sum.display();
    
    return 0;
}
```

## Constructor Overloading Rules

```cpp
#include <iostream>
#include <string>
using namespace std;

class Example {
public:
    // Overloading based on number of parameters
    Example() { cout << "Default" << endl; }
    Example(int a) { cout << "One int: " << a << endl; }
    Example(int a, int b) { cout << "Two ints: " << a << ", " << b << endl; }
    
    // Overloading based on parameter types
    Example(double d) { cout << "Double: " << d << endl; }
    Example(string s) { cout << "String: " << s << endl; }
    Example(int a, double d) { cout << "Int and double: " << a << ", " << d << endl; }
    
    // Overloading based on parameter order
    Example(double d, int a) { cout << "Double and int: " << d << ", " << a << endl; }
};

int main() {
    Example e1;                    // Default
    Example e2(10);                // One int
    Example e3(10, 20);            // Two ints
    Example e4(3.14);              // Double
    Example e5("Hello");           // String
    Example e6(42, 3.14);          // Int and double
    Example e7(3.14, 42);          // Double and int
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Ambiguous overloads | Compiler can't choose | Ensure unique parameter lists |
| Overloading only by return type | Not allowed | Different parameters |
| Confusing with default arguments | Ambiguity | Avoid mixing with default arguments |
| Not initializing all members | Garbage values | Initialize all members |
| Missing constructor for needed cases | Objects can't be created | Provide required constructors |

## Summary

- **Constructor overloading** allows multiple ways to create objects
- Overloaded constructors differ by **number**, **type**, or **order** of parameters
- **Default arguments** can reduce the number of overloads needed
- Compiler chooses the **best match** based on arguments
- **Ambiguity** occurs when multiple constructors match
- Provides **flexibility** and **convenience** for object creation
- Essential for classes with **different initialization scenarios**

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class MyClass {
private:
    int id;
    string name;
    double value;
    
public:
    MyClass() : id(0), name("Default"), value(0) {
        cout << "Default constructor" << endl;
    }
    
    MyClass(int i) : id(i), name("Default"), value(0) {
        cout << "Constructor with ID: " << id << endl;
    }
    
    MyClass(int i, string n) : id(i), name(n), value(0) {
        cout << "Constructor with ID and name: " << id << ", " << name << endl;
    }
    
    MyClass(int i, string n, double v) : id(i), name(n), value(v) {
        cout << "Constructor with all parameters" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Value: " << value << endl;
    }
};

int main() {
    MyClass obj1;
    MyClass obj2(101);
    MyClass obj3(102, "Test");
    MyClass obj4(103, "Demo", 42.5);
    
    obj1.display();
    obj2.display();
    obj3.display();
    obj4.display();
    
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
    int id;
    string name;
    double value;
    
public:
    MyClass();
    MyClass(int i);
    MyClass(int i, string n);
    MyClass(int i, string n, double v);
    void display() const;
};

#endif
```

**myclass.cpp**
```cpp
#include "myclass.h"
#include <iostream>
using namespace std;

MyClass::MyClass() : id(0), name("Default"), value(0) {
    cout << "Default constructor" << endl;
}

MyClass::MyClass(int i) : id(i), name("Default"), value(0) {
    cout << "Constructor with ID: " << id << endl;
}

MyClass::MyClass(int i, string n) : id(i), name(n), value(0) {
    cout << "Constructor with ID and name: " << id << ", " << name << endl;
}

MyClass::MyClass(int i, string n, double v) : id(i), name(n), value(v) {
    cout << "Constructor with all parameters" << endl;
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
    MyClass obj1;
    MyClass obj2(101);
    MyClass obj3(102, "Test");
    MyClass obj4(103, "Demo", 42.5);
    
    obj1.display();
    obj2.display();
    obj3.display();
    obj4.display();
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*