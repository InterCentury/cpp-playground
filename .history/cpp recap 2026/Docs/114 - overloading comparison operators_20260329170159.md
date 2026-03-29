# 114 - Overloading Comparison Operators in C++

## What are Comparison Operators?
Comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`) are used to compare two objects. Overloading them allows user-defined types to be compared naturally, enabling sorting, ordering, and equality checks.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int id;
    double gpa;
    
public:
    Student(string n = "", int i = 0, double g = 0.0) 
        : name(n), id(i), gpa(g) {}
    
    // Equality operators
    bool operator==(const Student& other) const {
        return id == other.id;
    }
    
    bool operator!=(const Student& other) const {
        return !(*this == other);
    }
    
    // Relational operators (by GPA)
    bool operator<(const Student& other) const {
        return gpa < other.gpa;
    }
    
    bool operator>(const Student& other) const {
        return other < *this;
    }
    
    bool operator<=(const Student& other) const {
        return !(other < *this);
    }
    
    bool operator>=(const Student& other) const {
        return !(*this < other);
    }
    
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << s.name << " (ID:" << s.id << ", GPA:" << s.gpa << ")";
        return os;
    }
};

int main() {
    Student s1("John", 101, 3.5);
    Student s2("Alice", 102, 3.8);
    Student s3("Bob", 101, 3.2);
    
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    
    cout << "\nEquality:" << endl;
    cout << "s1 == s2: " << (s1 == s2 ? "Yes" : "No") << endl;
    cout << "s1 == s3: " << (s1 == s3 ? "Yes" : "No") << endl;
    
    cout << "\nOrdering by GPA:" << endl;
    cout << "s1 < s2: " << (s1 < s2 ? "Yes" : "No") << endl;
    cout << "s1 > s3: " << (s1 > s3 ? "Yes" : "No") << endl;
    
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
    int id;
    double gpa;
    
public:
    Student(string n = "", int i = 0, double g = 0.0);
    
    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator<=(const Student& other) const;
    bool operator>=(const Student& other) const;
    
    friend ostream& operator<<(ostream& os, const Student& s);
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student(string n, int i, double g) : name(n), id(i), gpa(g) {}

bool Student::operator==(const Student& other) const {
    return id == other.id;
}

bool Student::operator!=(const Student& other) const {
    return !(*this == other);
}

bool Student::operator<(const Student& other) const {
    return gpa < other.gpa;
}

bool Student::operator>(const Student& other) const {
    return other < *this;
}

bool Student::operator<=(const Student& other) const {
    return !(other < *this);
}

bool Student::operator>=(const Student& other) const {
    return !(*this < other);
}

ostream& operator<<(ostream& os, const Student& s) {
    os << s.name << " (ID:" << s.id << ", GPA:" << s.gpa << ")";
    return os;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student s1("John", 101, 3.5);
    Student s2("Alice", 102, 3.8);
    
    cout << (s1 == s2 ? "Equal" : "Not equal") << endl;
    cout << (s1 < s2 ? "s1 has lower GPA" : "s2 has lower GPA") << endl;
    
    return 0;
}
```

## Implementing All Operators from One Function

```cpp
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

class Person {
private:
    string firstName;
    string lastName;
    int age;
    
public:
    Person(string f, string l, int a) : firstName(f), lastName(l), age(a) {}
    
    // Single comparison function
    int compare(const Person& other) const {
        if (lastName != other.lastName) 
            return lastName < other.lastName ? -1 : 1;
        if (firstName != other.firstName) 
            return firstName < other.firstName ? -1 : 1;
        if (age != other.age) 
            return age < other.age ? -1 : 1;
        return 0;
    }
    
    // All operators using compare()
    bool operator==(const Person& other) const { return compare(other) == 0; }
    bool operator!=(const Person& other) const { return compare(other) != 0; }
    bool operator<(const Person& other) const { return compare(other) < 0; }
    bool operator>(const Person& other) const { return compare(other) > 0; }
    bool operator<=(const Person& other) const { return compare(other) <= 0; }
    bool operator>=(const Person& other) const { return compare(other) >= 0; }
    
    friend ostream& operator<<(ostream& os, const Person& p) {
        os << p.lastName << ", " << p.firstName << " (" << p.age << ")";
        return os;
    }
};

int main() {
    Person p1("John", "Doe", 30);
    Person p2("Jane", "Doe", 28);
    Person p3("John", "Doe", 30);
    
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p3 = " << p3 << endl;
    
    cout << "\np1 == p3: " << (p1 == p3 ? "Yes" : "No") << endl;
    cout << "p1 != p2: " << (p1 != p2 ? "Yes" : "No") << endl;
    cout << "p2 < p1: " << (p2 < p1 ? "Yes" : "No") << endl;
    
    return 0;
}
```

## Using std::tie for Multi-Field Comparison

```cpp
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    
public:
    Product(int i, string n, double p) : id(i), name(n), price(p) {}
    
    // Using std::tie for lexicographic comparison
    auto tied() const {
        return tie(price, name, id);  // Compare by price first
    }
    
    bool operator==(const Product& other) const {
        return tied() == other.tied();
    }
    
    bool operator<(const Product& other) const {
        return tied() < other.tied();
    }
    
    bool operator>(const Product& other) const {
        return other < *this;
    }
    
    bool operator<=(const Product& other) const {
        return !(other < *this);
    }
    
    bool operator>=(const Product& other) const {
        return !(*this < other);
    }
    
    friend ostream& operator<<(ostream& os, const Product& p) {
        os << p.id << ": " << p.name << " ($" << p.price << ")";
        return os;
    }
};

int main() {
    Product p1(101, "Laptop", 999.99);
    Product p2(102, "Mouse", 29.99);
    Product p3(103, "Keyboard", 79.99);
    Product p4(104, "Laptop", 999.99);
    
    cout << "Products by price:" << endl;
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3 << endl;
    
    cout << "\np1 == p4: " << (p1 == p4 ? "Yes" : "No") << endl;
    cout << "p2 < p3: " << (p2 < p3 ? "Yes" : "No") << endl;
    cout << "p1 > p2: " << (p1 > p2 ? "Yes" : "No") << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Point Class with Distance Comparison

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    double distanceFromOrigin() const {
        return sqrt(x*x + y*y);
    }
    
    // Compare by distance from origin
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Point& other) const {
        return distanceFromOrigin() < other.distanceFromOrigin();
    }
    
    bool operator>(const Point& other) const {
        return other < *this;
    }
    
    bool operator<=(const Point& other) const {
        return !(other < *this);
    }
    
    bool operator>=(const Point& other) const {
        return !(*this < other);
    }
    
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int main() {
    Point p1(3, 4);    // distance = 5
    Point p2(0, 5);    // distance = 5
    Point p3(1, 1);    // distance = 1.414
    Point p4(3, 4);    // same as p1
    
    cout << "p1 = " << p1 << " (dist: " << p1.distanceFromOrigin() << ")" << endl;
    cout << "p2 = " << p2 << " (dist: " << p2.distanceFromOrigin() << ")" << endl;
    cout << "p3 = " << p3 << " (dist: " << p3.distanceFromOrigin() << ")" << endl;
    
    cout << "\np1 == p4: " << (p1 == p4 ? "Yes" : "No") << endl;
    cout << "p1 == p2: " << (p1 == p2 ? "Yes" : "No") << endl;
    cout << "p3 < p1: " << (p3 < p1 ? "Yes" : "No") << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**point.h**
```cpp
#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0);
    
    double distanceFromOrigin() const;
    
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    bool operator<(const Point& other) const;
    bool operator>(const Point& other) const;
    bool operator<=(const Point& other) const;
    bool operator>=(const Point& other) const;
    
    friend ostream& operator<<(ostream& os, const Point& p);
};

#endif
```

**point.cpp**
```cpp
#include "point.h"
#include <iostream>
#include <cmath>
using namespace std;

Point::Point(double x, double y) : x(x), y(y) {}

double Point::distanceFromOrigin() const {
    return sqrt(x*x + y*y);
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

bool Point::operator<(const Point& other) const {
    return distanceFromOrigin() < other.distanceFromOrigin();
}

bool Point::operator>(const Point& other) const {
    return other < *this;
}

bool Point::operator<=(const Point& other) const {
    return !(other < *this);
}

bool Point::operator>=(const Point& other) const {
    return !(*this < other);
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "point.h"
using namespace std;

int main() {
    Point p1(3, 4);
    Point p2(1, 1);
    
    cout << (p1 == p2 ? "Equal" : "Not equal") << endl;
    cout << (p2 < p1 ? "p2 is closer to origin" : "p1 is closer to origin") << endl;
    
    return 0;
}
```

### Example 2: Date Class with Chronological Order

#### Type 1: Single File
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

class Date {
private:
    int day, month, year;
    
    int toDays() const {
        return year * 365 + month * 30 + day;  // Simplified
    }
    
public:
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}
    
    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
    
    bool operator!=(const Date& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    bool operator>(const Date& other) const {
        return other < *this;
    }
    
    bool operator<=(const Date& other) const {
        return !(other < *this);
    }
    
    bool operator>=(const Date& other) const {
        return !(*this < other);
    }
    
    friend ostream& operator<<(ostream& os, const Date& d) {
        os << setfill('0') << setw(2) << d.day << "/"
           << setw(2) << d.month << "/" << d.year;
        return os;
    }
};

int main() {
    Date d1(15, 3, 2024);
    Date d2(20, 3, 2024);
    Date d3(15, 3, 2024);
    Date d4(1, 1, 2023);
    
    cout << "d1 = " << d1 << endl;
    cout << "d2 = " << d2 << endl;
    cout << "d3 = " << d3 << endl;
    cout << "d4 = " << d4 << endl;
    
    cout << "\nd1 == d3: " << (d1 == d3 ? "Yes" : "No") << endl;
    cout << "d1 < d2: " << (d1 < d2 ? "Yes" : "No") << endl;
    cout << "d4 < d1: " << (d4 < d1 ? "Yes" : "No") << endl;
    
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
    int day, month, year;
    
public:
    Date(int d = 1, int m = 1, int y = 2000);
    
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    
    friend ostream& operator<<(ostream& os, const Date& d);
};

#endif
```

**date.cpp**
```cpp
#include "date.h"
#include <iostream>
#include <iomanip>
using namespace std;

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date& other) const {
    return other < *this;
}

bool Date::operator<=(const Date& other) const {
    return !(other < *this);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
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
    Date d1(15, 3, 2024);
    Date d2(20, 3, 2024);
    
    cout << (d1 < d2 ? "d1 is earlier" : "d2 is earlier") << endl;
    
    return 0;
}
```

### Example 3: String Class with Lexicographic Comparison

#### Type 1: Single File
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private:
    char* data;
    int length;
    
public:
    MyString(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
    
    ~MyString() {
        delete[] data;
    }
    
    // Comparison operators using strcmp
    bool operator==(const MyString& other) const {
        return strcmp(data, other.data) == 0;
    }
    
    bool operator!=(const MyString& other) const {
        return strcmp(data, other.data) != 0;
    }
    
    bool operator<(const MyString& other) const {
        return strcmp(data, other.data) < 0;
    }
    
    bool operator>(const MyString& other) const {
        return strcmp(data, other.data) > 0;
    }
    
    bool operator<=(const MyString& other) const {
        return strcmp(data, other.data) <= 0;
    }
    
    bool operator>=(const MyString& other) const {
        return strcmp(data, other.data) >= 0;
    }
    
    friend ostream& operator<<(ostream& os, const MyString& s) {
        os << s.data;
        return os;
    }
};

int main() {
    MyString s1("apple");
    MyString s2("banana");
    MyString s3("apple");
    
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    
    cout << "\ns1 == s3: " << (s1 == s3 ? "Yes" : "No") << endl;
    cout << "s1 != s2: " << (s1 != s2 ? "Yes" : "No") << endl;
    cout << "s1 < s2: " << (s1 < s2 ? "Yes" : "No") << endl;
    cout << "s2 > s1: " << (s2 > s1 ? "Yes" : "No") << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**mystring.h**
```cpp
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using namespace std;

class MyString {
private:
    char* data;
    int length;
    
public:
    MyString(const char* str = "");
    ~MyString();
    
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator>(const MyString& other) const;
    bool operator<=(const MyString& other) const;
    bool operator>=(const MyString& other) const;
    
    friend ostream& operator<<(ostream& os, const MyString& s);
};

#endif
```

**mystring.cpp**
```cpp
#include "mystring.h"
#include <cstring>
#include <iostream>
using namespace std;

MyString::MyString(const char* str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
}

MyString::~MyString() {
    delete[] data;
}

bool MyString::operator==(const MyString& other) const {
    return strcmp(data, other.data) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return strcmp(data, other.data) != 0;
}

bool MyString::operator<(const MyString& other) const {
    return strcmp(data, other.data) < 0;
}

bool MyString::operator>(const MyString& other) const {
    return strcmp(data, other.data) > 0;
}

bool MyString::operator<=(const MyString& other) const {
    return strcmp(data, other.data) <= 0;
}

bool MyString::operator>=(const MyString& other) const {
    return strcmp(data, other.data) >= 0;
}

ostream& operator<<(ostream& os, const MyString& s) {
    os << s.data;
    return os;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "mystring.h"
using namespace std;

int main() {
    MyString s1("apple");
    MyString s2("banana");
    
    cout << (s1 < s2 ? "apple comes before banana" : "banana comes before apple") << endl;
    
    return 0;
}
```

## Comparison Operator Patterns

### Pattern 1: Single Compare Function
```cpp
class MyClass {
public:
    int compare(const MyClass& other) const {
        if (field1 != other.field1) return field1 - other.field1;
        if (field2 != other.field2) return field2 - other.field2;
        return field3 - other.field3;
    }
    
    bool operator==(const MyClass& other) const { return compare(other) == 0; }
    bool operator!=(const MyClass& other) const { return compare(other) != 0; }
    bool operator<(const MyClass& other) const { return compare(other) < 0; }
    bool operator>(const MyClass& other) const { return compare(other) > 0; }
    bool operator<=(const MyClass& other) const { return compare(other) <= 0; }
    bool operator>=(const MyClass& other) const { return compare(other) >= 0; }
};
```

### Pattern 2: std::tie for Simple Classes
```cpp
class MyClass {
    auto tied() const { return std::tie(field1, field2, field3); }
    
    bool operator==(const MyClass& other) const { return tied() == other.tied(); }
    bool operator<(const MyClass& other) const { return tied() < other.tied(); }
    // ... other operators using tied()
};
```

### Pattern 3: Implement Only < and ==, Derive Others
```cpp
class MyClass {
    bool operator==(const MyClass& other) const { /* ... */ }
    bool operator<(const MyClass& other) const { /* ... */ }
    
    bool operator!=(const MyClass& other) const { return !(*this == other); }
    bool operator>(const MyClass& other) const { return other < *this; }
    bool operator<=(const MyClass& other) const { return !(other < *this); }
    bool operator>=(const MyClass& other) const { return !(*this < other); }
};
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Inconsistent logic | Contradictory results | Ensure operators are consistent |
| Missing const | Can't compare const objects | Add const to all comparison operators |
| Not implementing all operators | Incomplete functionality | Implement full set or derive from < and == |
| Using wrong comparison order | Unexpected sorting | Define clear ordering criteria |
| Ignoring tie-breaking | Ambiguous ordering | Compare all relevant fields |

## Summary

- **Comparison operators** enable natural object comparison
- **Implement == and <** first, derive others from them
- **Use std::tie** for simple multi-field comparisons
- **const correctness** is essential for all comparison operators
- **Consistency** required: if a < b then !(b < a) and !(a == b)
- **Transitivity**: if a < b and b < c then a < c
- **Return bool** for all comparison operators

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <tuple>
using namespace std;

class MyClass {
private:
    int a, b;
    string c;
    
public:
    MyClass(int a = 0, int b = 0, string c = "") : a(a), b(b), c(c) {}
    
    auto tied() const { return tie(a, b, c); }
    
    bool operator==(const MyClass& other) const { return tied() == other.tied(); }
    bool operator!=(const MyClass& other) const { return tied() != other.tied(); }
    bool operator<(const MyClass& other) const { return tied() < other.tied(); }
    bool operator>(const MyClass& other) const { return other < *this; }
    bool operator<=(const MyClass& other) const { return !(other < *this); }
    bool operator>=(const MyClass& other) const { return !(*this < other); }
    
    friend ostream& operator<<(ostream& os, const MyClass& obj) {
        os << "(" << obj.a << ", " << obj.b << ", " << obj.c << ")";
        return os;
    }
};

int main() {
    MyClass obj1(1, 2, "a"), obj2(1, 2, "a"), obj3(2, 1, "b");
    cout << (obj1 == obj2 ? "Equal" : "Not equal") << endl;
    cout << (obj1 < obj3 ? "obj1 < obj3" : "obj3 < obj1") << endl;
    return 0;
}
```

### Type 2: Multiple Files

**myclass.h**
```cpp
#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>
#include <string>
#include <tuple>
using namespace std;

class MyClass {
private:
    int a, b;
    string c;
    
public:
    MyClass(int a = 0, int b = 0, string c = "");
    
    auto tied() const { return tie(a, b, c); }
    
    bool operator==(const MyClass& other) const;
    bool operator!=(const MyClass& other) const;
    bool operator<(const MyClass& other) const;
    bool operator>(const MyClass& other) const;
    bool operator<=(const MyClass& other) const;
    bool operator>=(const MyClass& other) const;
    
    friend ostream& operator<<(ostream& os, const MyClass& obj);
};

#endif
```

**myclass.cpp**
```cpp
#include "myclass.h"
#include <iostream>
using namespace std;

MyClass::MyClass(int a, int b, string c) : a(a), b(b), c(c) {}

bool MyClass::operator==(const MyClass& other) const { return tied() == other.tied(); }
bool MyClass::operator!=(const MyClass& other) const { return tied() != other.tied(); }
bool MyClass::operator<(const MyClass& other) const { return tied() < other.tied(); }
bool MyClass::operator>(const MyClass& other) const { return other < *this; }
bool MyClass::operator<=(const MyClass& other) const { return !(other < *this); }
bool MyClass::operator>=(const MyClass& other) const { return !(*this < other); }

ostream& operator<<(ostream& os, const MyClass& obj) {
    os << "(" << obj.a << ", " << obj.b << ", " << obj.c << ")";
    return os;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "myclass.h"
using namespace std;

int main() {
    MyClass obj1(1, 2, "a");
    MyClass obj2(1, 2, "a");
    
    cout << (obj1 == obj2 ? "Equal" : "Not equal") << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*