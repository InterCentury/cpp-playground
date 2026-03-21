# 82 - Parameterized Constructor in C++

## What is a Parameterized Constructor?
A parameterized constructor is a constructor that takes one or more arguments. It allows initializing objects with specific values at the time of creation, rather than using default values.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    double marks;
    
public:
    // Parameterized constructor
    Student(int r, string n, double m) {
        rollNumber = r;
        name = n;
        marks = m;
        cout << "Parameterized constructor called for " << name << endl;
    }
    
    void display() const {
        cout << "Roll: " << rollNumber << ", Name: " << name 
             << ", Marks: " << marks << endl;
    }
};

int main() {
    // Creating objects with parameterized constructor
    Student s1(101, "John", 85.5);
    Student s2(102, "Alice", 92.0);
    Student s3(103, "Bob", 78.5);
    
    s1.display();
    s2.display();
    s3.display();
    
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
    int rollNumber;
    string name;
    double marks;
    
public:
    Student(int r, string n, double m);
    void display() const;
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student(int r, string n, double m) {
    rollNumber = r;
    name = n;
    marks = m;
    cout << "Parameterized constructor called for " << name << endl;
}

void Student::display() const {
    cout << "Roll: " << rollNumber << ", Name: " << name 
         << ", Marks: " << marks << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student s1(101, "John", 85.5);
    Student s2(102, "Alice", 92.0);
    
    s1.display();
    s2.display();
    
    return 0;
}
```

## Different Ways to Call Parameterized Constructor

```cpp
#include <iostream>
#include <string>
using namespace std;

class Point {
private:
    int x, y;
    
public:
    // Parameterized constructor
    Point(int xCoord, int yCoord) : x(xCoord), y(yCoord) {
        cout << "Point created at (" << x << ", " << y << ")" << endl;
    }
    
    void display() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    // Different ways to call parameterized constructor
    
    // 1. Direct initialization
    Point p1(10, 20);
    
    // 2. Assignment syntax
    Point p2 = Point(30, 40);
    
    // 3. Uniform initialization (C++11)
    Point p3{50, 60};
    
    // 4. Dynamic allocation
    Point* p4 = new Point(70, 80);
    
    p1.display();
    p2.display();
    p3.display();
    p4->display();
    
    delete p4;
    
    return 0;
}
```

## Constructor Initialization List

```cpp
#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int id;
    string name;
    double salary;
    const int departmentCode;  // const member must use initialization list
    
public:
    // Using initialization list (more efficient)
    Employee(int i, string n, double s, int dept) 
        : id(i), name(n), salary(s), departmentCode(dept) {
        cout << "Employee " << name << " created" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Salary: $" << salary 
             << ", Dept Code: " << departmentCode << endl;
    }
};

int main() {
    Employee e1(1001, "John Doe", 50000, 101);
    Employee e2(1002, "Jane Smith", 60000, 102);
    
    e1.display();
    e2.display();
    
    return 0;
}
```

## Parameterized Constructor with Default Arguments

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
    // Constructor with default arguments
    Product(int i, string n = "Unknown", double p = 0.0, int q = 0) 
        : id(i), name(n), price(p), quantity(q) {
        cout << "Product created: " << name << " (ID: " << id << ")" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Price: $" << price << ", Qty: " << quantity << endl;
    }
};

int main() {
    Product p1(101);                          // Uses defaults for name, price, qty
    Product p2(102, "Laptop");                // Uses defaults for price, qty
    Product p3(103, "Mouse", 29.99);          // Uses default for qty
    Product p4(104, "Keyboard", 79.99, 10);   // No defaults
    
    p1.display();
    p2.display();
    p3.display();
    p4.display();
    
    return 0;
}
```

## Practical Examples

### Example 1: Bank Account with Parameterized Constructor

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;
    time_t creationDate;
    static int nextAccountNumber;
    
    string generateAccountNumber() {
        return "ACC" + to_string(nextAccountNumber++);
    }
    
public:
    // Parameterized constructor
    BankAccount(string holder, double initialDeposit = 0.0) {
        accountNumber = generateAccountNumber();
        accountHolder = holder;
        balance = initialDeposit;
        creationDate = time(nullptr);
        cout << "Account created for " << holder << endl;
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        }
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
            return true;
        }
        cout << "Insufficient funds!" << endl;
        return false;
    }
    
    void display() const {
        cout << "Account: " << accountNumber << endl;
        cout << "Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Created: " << ctime(&creationDate);
    }
};

int BankAccount::nextAccountNumber = 1000;

int main() {
    BankAccount acc1("John Doe", 1000);
    BankAccount acc2("Jane Smith", 500);
    BankAccount acc3("Bob Johnson");  // Uses default 0 balance
    
    acc1.deposit(500);
    acc1.withdraw(200);
    
    cout << "\nAccount 1 Details:" << endl;
    acc1.display();
    
    cout << "\nAccount 2 Details:" << endl;
    acc2.display();
    
    cout << "\nAccount 3 Details:" << endl;
    acc3.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**bankaccount.h**
```cpp
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <ctime>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;
    time_t creationDate;
    static int nextAccountNumber;
    
    string generateAccountNumber();
    
public:
    BankAccount(string holder, double initialDeposit = 0.0);
    void deposit(double amount);
    bool withdraw(double amount);
    void display() const;
};

#endif
```

**bankaccount.cpp**
```cpp
#include "bankaccount.h"
#include <iostream>
using namespace std;

int BankAccount::nextAccountNumber = 1000;

string BankAccount::generateAccountNumber() {
    return "ACC" + to_string(nextAccountNumber++);
}

BankAccount::BankAccount(string holder, double initialDeposit) {
    accountNumber = generateAccountNumber();
    accountHolder = holder;
    balance = initialDeposit;
    creationDate = time(nullptr);
    cout << "Account created for " << holder << endl;
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "Deposited: $" << amount << endl;
    }
}

bool BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        cout << "Withdrawn: $" << amount << endl;
        return true;
    }
    cout << "Insufficient funds!" << endl;
    return false;
}

void BankAccount::display() const {
    cout << "Account: " << accountNumber << endl;
    cout << "Holder: " << accountHolder << endl;
    cout << "Balance: $" << balance << endl;
    cout << "Created: " << ctime(&creationDate);
}
```

**main.cpp**
```cpp
#include <iostream>
#include "bankaccount.h"
using namespace std;

int main() {
    BankAccount acc1("John Doe", 1000);
    BankAccount acc2("Jane Smith", 500);
    
    acc1.deposit(500);
    acc1.withdraw(200);
    
    cout << "\nAccount 1 Details:" << endl;
    acc1.display();
    
    cout << "\nAccount 2 Details:" << endl;
    acc2.display();
    
    return 0;
}
```

### Example 2: Rectangle Class with Validation

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
    
public:
    // Parameterized constructor with validation
    Rectangle(double l, double w) {
        if (l > 0 && w > 0) {
            length = l;
            width = w;
        } else {
            cout << "Invalid dimensions! Setting to default (1,1)" << endl;
            length = 1;
            width = 1;
        }
        cout << "Rectangle created: " << length << " x " << width << endl;
    }
    
    double area() const {
        return length * width;
    }
    
    double perimeter() const {
        return 2 * (length + width);
    }
    
    double diagonal() const {
        return sqrt(length * length + width * width);
    }
    
    bool isSquare() const {
        return length == width;
    }
    
    void display() const {
        cout << "Rectangle: " << length << " x " << width << endl;
        cout << "Area: " << area() << ", Perimeter: " << perimeter() << endl;
        cout << "Diagonal: " << diagonal() << ", Square: " 
             << (isSquare() ? "Yes" : "No") << endl;
    }
};

int main() {
    Rectangle rect1(5.0, 3.0);
    Rectangle rect2(4.0, 4.0);
    Rectangle rect3(-2.0, 5.0);  // Invalid - will be corrected
    
    cout << "\nRectangle 1:" << endl;
    rect1.display();
    
    cout << "\nRectangle 2:" << endl;
    rect2.display();
    
    cout << "\nRectangle 3:" << endl;
    rect3.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**rectangle.h**
```cpp
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
    double length;
    double width;
    
public:
    Rectangle(double l, double w);
    double area() const;
    double perimeter() const;
    double diagonal() const;
    bool isSquare() const;
    void display() const;
};

#endif
```

**rectangle.cpp**
```cpp
#include "rectangle.h"
#include <iostream>
#include <cmath>
using namespace std;

Rectangle::Rectangle(double l, double w) {
    if (l > 0 && w > 0) {
        length = l;
        width = w;
    } else {
        cout << "Invalid dimensions! Setting to default (1,1)" << endl;
        length = 1;
        width = 1;
    }
    cout << "Rectangle created: " << length << " x " << width << endl;
}

double Rectangle::area() const {
    return length * width;
}

double Rectangle::perimeter() const {
    return 2 * (length + width);
}

double Rectangle::diagonal() const {
    return sqrt(length * length + width * width);
}

bool Rectangle::isSquare() const {
    return length == width;
}

void Rectangle::display() const {
    cout << "Rectangle: " << length << " x " << width << endl;
    cout << "Area: " << area() << ", Perimeter: " << perimeter() << endl;
    cout << "Diagonal: " << diagonal() << ", Square: " 
         << (isSquare() ? "Yes" : "No") << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "rectangle.h"
using namespace std;

int main() {
    Rectangle rect1(5.0, 3.0);
    Rectangle rect2(4.0, 4.0);
    
    rect1.display();
    cout << endl;
    rect2.display();
    
    return 0;
}
```

### Example 3: Time Class with Parameterized Constructor

#### Type 1: Single File
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;
    
    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours >= 24) {
            hours %= 24;
        }
    }
    
public:
    // Parameterized constructor with validation
    Time(int h = 0, int m = 0, int s = 0) {
        hours = (h >= 0 && h < 24) ? h : 0;
        minutes = (m >= 0 && m < 60) ? m : 0;
        seconds = (s >= 0 && s < 60) ? s : 0;
        normalize();
        cout << "Time created: " << *this << endl;
    }
    
    Time add(const Time& other) const {
        return Time(hours + other.hours, 
                    minutes + other.minutes, 
                    seconds + other.seconds);
    }
    
    int difference(const Time& other) const {
        int total1 = hours * 3600 + minutes * 60 + seconds;
        int total2 = other.hours * 3600 + other.minutes * 60 + other.seconds;
        return abs(total1 - total2);
    }
    
    friend ostream& operator<<(ostream& os, const Time& t) {
        os << setfill('0') << setw(2) << t.hours << ":"
           << setw(2) << t.minutes << ":"
           << setw(2) << t.seconds;
        return os;
    }
};

int main() {
    Time t1(2, 30, 45);
    Time t2(1, 45, 30);
    Time t3(25, 70, 90);  // Invalid - will be normalized
    
    cout << "\nTime 1: " << t1 << endl;
    cout << "Time 2: " << t2 << endl;
    cout << "Time 3 (normalized): " << t3 << endl;
    
    Time sum = t1.add(t2);
    cout << "\nSum: " << t1 << " + " << t2 << " = " << sum << endl;
    
    cout << "Difference: " << t1.difference(t2) << " seconds" << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**time.h**
```cpp
#ifndef TIME_H
#define TIME_H

#include <iostream>
using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;
    
    void normalize();
    
public:
    Time(int h = 0, int m = 0, int s = 0);
    Time add(const Time& other) const;
    int difference(const Time& other) const;
    friend ostream& operator<<(ostream& os, const Time& t);
};

#endif
```

**time.cpp**
```cpp
#include "time.h"
#include <iomanip>
#include <cmath>
using namespace std;

void Time::normalize() {
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds %= 60;
    }
    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    }
    if (hours >= 24) {
        hours %= 24;
    }
}

Time::Time(int h, int m, int s) {
    hours = (h >= 0 && h < 24) ? h : 0;
    minutes = (m >= 0 && m < 60) ? m : 0;
    seconds = (s >= 0 && s < 60) ? s : 0;
    normalize();
}

Time Time::add(const Time& other) const {
    return Time(hours + other.hours, 
                minutes + other.minutes, 
                seconds + other.seconds);
}

int Time::difference(const Time& other) const {
    int total1 = hours * 3600 + minutes * 60 + seconds;
    int total2 = other.hours * 3600 + other.minutes * 60 + other.seconds;
    return abs(total1 - total2);
}

ostream& operator<<(ostream& os, const Time& t) {
    os << setfill('0') << setw(2) << t.hours << ":"
       << setw(2) << t.minutes << ":"
       << setw(2) << t.seconds;
    return os;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "time.h"
using namespace std;

int main() {
    Time t1(2, 30, 45);
    Time t2(1, 45, 30);
    
    cout << "Time 1: " << t1 << endl;
    cout << "Time 2: " << t2 << endl;
    
    Time sum = t1.add(t2);
    cout << "Sum: " << sum << endl;
    
    return 0;
}
```

## Constructor Overloading with Parameterized Constructors

```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int pages;
    double price;
    
public:
    // Multiple parameterized constructors (overloading)
    Book(string t) : title(t), author("Unknown"), pages(0), price(0.0) {
        cout << "Book: " << title << " (minimal info)" << endl;
    }
    
    Book(string t, string a) : title(t), author(a), pages(0), price(0.0) {
        cout << "Book: " << title << " by " << author << endl;
    }
    
    Book(string t, string a, int p) : title(t), author(a), pages(p), price(0.0) {
        cout << "Book: " << title << " by " << author << ", " << pages << " pages" << endl;
    }
    
    Book(string t, string a, int p, double pr) 
        : title(t), author(a), pages(p), price(pr) {
        cout << "Book: " << title << " by " << author << ", " 
             << pages << " pages, $" << price << endl;
    }
    
    void display() const {
        cout << "Title: " << title << ", Author: " << author 
             << ", Pages: " << pages << ", Price: $" << price << endl;
    }
};

int main() {
    Book b1("C++ Programming");
    Book b2("Python Basics", "John Doe");
    Book b3("Data Structures", "Jane Smith", 500);
    Book b4("Algorithms", "Bob Johnson", 800, 79.99);
    
    cout << "\n--- Book Details ---" << endl;
    b1.display();
    b2.display();
    b3.display();
    b4.display();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting to initialize members | Garbage values | Use initialization list or assign in body |
| No default constructor when needed | Compilation error when creating arrays | Provide default or use parameterized with defaults |
| Constructor name mismatch | Not a constructor | Use class name exactly |
| Returning value from constructor | Not possible | Constructors don't return values |
| Using parameter names that shadow members | Confusion | Use `this->` or initialization list |

## Summary

- **Parameterized constructor** accepts arguments for initialization
- Can be **overloaded** with different parameter lists
- Use **initialization list** for efficiency and const members
- **Default arguments** can make parameterized act as default
- Called automatically when creating objects with arguments
- Essential for **dependency injection** and **custom initialization**
- Can perform **validation** before assigning values
- Prevents **uninitialized** objects

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
    // Parameterized constructor with initialization list
    MyClass(int i, string n, double v) : id(i), name(n), value(v) {
        cout << "Object created: " << name << " (ID: " << id << ")" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Value: " << value << endl;
    }
};

int main() {
    MyClass obj1(101, "First", 42.5);
    MyClass obj2(102, "Second", 99.9);
    
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
    int id;
    string name;
    double value;
    
public:
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

MyClass::MyClass(int i, string n, double v) : id(i), name(n), value(v) {
    cout << "Object created: " << name << " (ID: " << id << ")" << endl;
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
    MyClass obj1(101, "First", 42.5);
    MyClass obj2(102, "Second", 99.9);
    
    obj1.display();
    obj2.display();
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*