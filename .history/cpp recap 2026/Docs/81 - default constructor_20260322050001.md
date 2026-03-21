# 81 - Default Constructor in C++

## What is a Default Constructor?
A default constructor is a constructor that can be called with no arguments. It initializes objects when no initial values are provided. If no constructor is defined, the compiler provides an implicit default constructor.

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
    // Default constructor
    Student() {
        name = "Unknown";
        age = 0;
        gpa = 0.0;
        cout << "Default constructor called" << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << ", GPA: " << gpa << endl;
    }
};

int main() {
    Student s1;           // Default constructor called
    Student s2;           // Default constructor called again
    
    s1.display();
    s2.display();
    
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
    string name;
    int age;
    double gpa;
    
public:
    Student();  // Default constructor declaration
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
    name = "Unknown";
    age = 0;
    gpa = 0.0;
    cout << "Default constructor called" << endl;
}

void Student::display() const {
    cout << "Name: " << name << ", Age: " << age << ", GPA: " << gpa << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student s1, s2;
    s1.display();
    s2.display();
    return 0;
}
```

## Types of Default Constructors

### 1. Implicit Default Constructor (Compiler-generated)

```cpp
#include <iostream>
#include <string>
using namespace std;

class Simple {
    // No constructor defined - compiler provides implicit default
public:
    int x;
    string name;
    
    void display() {
        cout << "x: " << x << ", name: " << name << endl;
    }
};

int main() {
    Simple obj;
    // x is uninitialized (garbage), name is empty string
    obj.display();
    
    return 0;
}
```

### 2. User-Defined Default Constructor

```cpp
#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int id;
    string name;
    double salary;
    
public:
    // User-defined default constructor
    Employee() {
        id = 0;
        name = "New Employee";
        salary = 30000.0;
        cout << "Employee created with default values" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Salary: $" << salary << endl;
    }
};

int main() {
    Employee emp1, emp2;
    emp1.display();
    emp2.display();
    
    return 0;
}
```

### 3. Default Constructor with Default Arguments

```cpp
#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    
public:
    // Constructor with all default arguments acts as default constructor
    Product(int i = 0, string n = "Unknown", double p = 0.0) 
        : id(i), name(n), price(p) {
        cout << "Parameterized/Default constructor called" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Price: $" << price << endl;
    }
};

int main() {
    Product p1;                // Uses all defaults
    Product p2(101);           // Uses defaults for name and price
    Product p3(102, "Laptop"); // Uses default for price
    Product p4(103, "Mouse", 29.99); // No defaults
    
    p1.display();
    p2.display();
    p3.display();
    p4.display();
    
    return 0;
}
```

### 4. Defaulted Constructor (C++11)

```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    int pages;
    double price;
    
public:
    // Force compiler to generate default constructor
    Book() = default;
    
    Book(string t, int p, double pr) : title(t), pages(p), price(pr) {}
    
    void display() const {
        cout << title << ", " << pages << " pages, $" << price << endl;
    }
};

int main() {
    Book b1;                    // Uses defaulted constructor
    Book b2("C++", 500, 49.99); // Uses parameterized
    
    b1.display();  // Default values (empty string, 0, 0)
    b2.display();
    
    return 0;
}
```

### 5. Deleted Default Constructor (C++11)

```cpp
#include <iostream>
#include <string>
using namespace std;

class NoDefault {
private:
    int id;
    
public:
    NoDefault(int i) : id(i) {}
    
    // Delete default constructor - cannot create without arguments
    NoDefault() = delete;
    
    void display() const {
        cout << "ID: " << id << endl;
    }
};

int main() {
    // NoDefault obj;  // Error! Default constructor is deleted
    
    NoDefault obj(42);  // OK - parameterized constructor
    obj.display();
    
    return 0;
}
```

## Practical Examples

### Example 1: Bank Account with Default Values

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;
    static int nextAccountNumber;
    
    string generateAccountNumber() {
        return "ACC" + to_string(nextAccountNumber++);
    }
    
public:
    // Default constructor
    BankAccount() {
        accountNumber = generateAccountNumber();
        accountHolder = "New Customer";
        balance = 0.0;
        cout << "Default account created: " << accountNumber << endl;
    }
    
    // Parameterized constructor
    BankAccount(string holder, double initialDeposit) {
        accountNumber = generateAccountNumber();
        accountHolder = holder;
        balance = initialDeposit;
        cout << "Account created for " << holder << ": " << accountNumber << endl;
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        }
    }
    
    void display() const {
        cout << "Account: " << accountNumber << endl;
        cout << "Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }
};

int BankAccount::nextAccountNumber = 1000;

int main() {
    BankAccount defaultAcc;              // Default constructor
    BankAccount johnsAcc("John Doe", 1000);  // Parameterized constructor
    
    cout << "\nDefault Account:" << endl;
    defaultAcc.display();
    
    cout << "\nJohn's Account:" << endl;
    johnsAcc.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**bankaccount.h**
```cpp
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;
    static int nextAccountNumber;
    
    string generateAccountNumber();
    
public:
    BankAccount();
    BankAccount(string holder, double initialDeposit);
    void deposit(double amount);
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

BankAccount::BankAccount() {
    accountNumber = generateAccountNumber();
    accountHolder = "New Customer";
    balance = 0.0;
    cout << "Default account created: " << accountNumber << endl;
}

BankAccount::BankAccount(string holder, double initialDeposit) {
    accountNumber = generateAccountNumber();
    accountHolder = holder;
    balance = initialDeposit;
    cout << "Account created for " << holder << ": " << accountNumber << endl;
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "Deposited: $" << amount << endl;
    }
}

void BankAccount::display() const {
    cout << "Account: " << accountNumber << endl;
    cout << "Holder: " << accountHolder << endl;
    cout << "Balance: $" << balance << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "bankaccount.h"
using namespace std;

int main() {
    BankAccount defaultAcc;
    BankAccount johnsAcc("John Doe", 1000);
    
    cout << "\nDefault Account:" << endl;
    defaultAcc.display();
    
    cout << "\nJohn's Account:" << endl;
    johnsAcc.display();
    
    return 0;
}
```

### Example 2: Date Class with Default to Today

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
    
public:
    // Default constructor - sets to current date
    Date() {
        time_t now = time(0);
        tm* local = localtime(&now);
        day = local->tm_mday;
        month = local->tm_mon + 1;
        year = local->tm_year + 1900;
        cout << "Default date set to today" << endl;
    }
    
    // Parameterized constructor
    Date(int d, int m, int y) : day(d), month(m), year(y) {
        if (!isValid()) {
            cout << "Invalid date, setting to default" << endl;
            *this = Date();  // Call default constructor
        }
    }
    
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
    
    void display() const {
        cout << setfill('0') 
             << setw(2) << day << "/"
             << setw(2) << month << "/"
             << year;
    }
};

int main() {
    Date defaultDate;           // Today's date
    Date customDate(15, 3, 2024);
    Date invalidDate(32, 13, 2025);  // Invalid - will use default
    
    cout << "Default: "; defaultDate.display(); cout << endl;
    cout << "Custom: "; customDate.display(); cout << endl;
    cout << "Invalid (corrected): "; invalidDate.display(); cout << endl;
    
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
    Date();
    Date(int d, int m, int y);
    void display() const;
};

#endif
```

**date.cpp**
```cpp
#include "date.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

Date::Date() {
    time_t now = time(0);
    tm* local = localtime(&now);
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;
    cout << "Default date set to today" << endl;
}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!isValid()) {
        cout << "Invalid date, setting to default" << endl;
        *this = Date();
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
    cout << setfill('0') 
         << setw(2) << day << "/"
         << setw(2) << month << "/"
         << year;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "date.h"
using namespace std;

int main() {
    Date defaultDate;
    Date customDate(15, 3, 2024);
    Date invalidDate(32, 13, 2025);
    
    cout << "Default: "; defaultDate.display(); cout << endl;
    cout << "Custom: "; customDate.display(); cout << endl;
    cout << "Invalid (corrected): "; invalidDate.display(); cout << endl;
    
    return 0;
}
```

### Example 3: Array Class with Default Size

#### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class IntArray {
private:
    int* data;
    int size;
    
public:
    // Default constructor
    IntArray() {
        size = 10;  // Default size
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
        cout << "Default array created (size " << size << ")" << endl;
    }
    
    // Parameterized constructor
    IntArray(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
        cout << "Array created (size " << size << ")" << endl;
    }
    
    // Copy constructor
    IntArray(const IntArray& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Copy constructor called" << endl;
    }
    
    int& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        static int dummy = -1;
        return dummy;
    }
    
    int getSize() const { return size; }
    
    void display() const {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    
    ~IntArray() {
        delete[] data;
        cout << "Array destroyed" << endl;
    }
};

int main() {
    IntArray arr1;        // Default constructor (size 10)
    IntArray arr2(5);     // Parameterized constructor
    IntArray arr3 = arr2; // Copy constructor
    
    cout << "arr1 (size " << arr1.getSize() << "): ";
    arr1.display();
    
    cout << "arr2 (size " << arr2.getSize() << "): ";
    arr2.display();
    
    cout << "arr3 (size " << arr3.getSize() << "): ";
    arr3.display();
    
    arr1[0] = 100;
    arr2[0] = 200;
    
    cout << "\nAfter modifications:" << endl;
    arr1.display();
    arr2.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**intarray.h**
```cpp
#ifndef INTARRAY_H
#define INTARRAY_H

class IntArray {
private:
    int* data;
    int size;
    
public:
    IntArray();
    IntArray(int s);
    IntArray(const IntArray& other);
    int& operator[](int index);
    int getSize() const;
    void display() const;
    ~IntArray();
};

#endif
```

**intarray.cpp**
```cpp
#include "intarray.h"
#include <iostream>
using namespace std;

IntArray::IntArray() {
    size = 10;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
    cout << "Default array created (size " << size << ")" << endl;
}

IntArray::IntArray(int s) : size(s) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
    cout << "Array created (size " << size << ")" << endl;
}

IntArray::IntArray(const IntArray& other) : size(other.size) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
    cout << "Copy constructor called" << endl;
}

int& IntArray::operator[](int index) {
    if (index >= 0 && index < size) {
        return data[index];
    }
    static int dummy = -1;
    return dummy;
}

int IntArray::getSize() const { return size; }

void IntArray::display() const {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

IntArray::~IntArray() {
    delete[] data;
    cout << "Array destroyed" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "intarray.h"
using namespace std;

int main() {
    IntArray arr1;
    IntArray arr2(5);
    
    cout << "arr1: "; arr1.display();
    cout << "arr2: "; arr2.display();
    
    arr1[0] = 100;
    arr2[0] = 200;
    
    cout << "\nAfter modifications:" << endl;
    arr1.display();
    arr2.display();
    
    return 0;
}
```

## When Default Constructors Are Called

```cpp
#include <iostream>
using namespace std;

class Demo {
public:
    Demo() { cout << "Default constructor" << endl; }
    Demo(int x) { cout << "Parameterized: " << x << endl; }
};

int main() {
    Demo d1;           // Default constructor
    Demo d2();         // This is a function declaration! Not an object!
    Demo d3{};         // Default constructor (C++11)
    Demo d4 = Demo();  // Default constructor
    
    Demo d5(10);       // Parameterized constructor
    Demo d6 = 20;      // Parameterized constructor
    
    Demo arr[3];       // Default constructor called 3 times
    
    Demo* ptr = new Demo;  // Default constructor
    delete ptr;
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| `Demo d();` | Function declaration, not object | `Demo d;` or `Demo d{}` |
| Forgetting to initialize members | Garbage values | Initialize in constructor |
| Relying on implicit default with pointers | Dangling pointers | Initialize to nullptr |
| Deleting default constructor but trying to use | Compilation error | Don't delete if needed |
| Not handling dynamic memory | Memory leaks | Implement properly |

## Summary

- **Default constructor** can be called with no arguments
- **Implicit default** provided by compiler if no constructor defined
- **User-defined default** explicitly defined by programmer
- **Defaulted constructor** (`= default`) uses compiler-generated version
- **Deleted constructor** (`= delete`) prevents default construction
- **Default arguments** can make parameterized constructor act as default
- Used for **initializing** objects with default values
- Called when creating **arrays of objects**
- Called when using **new without arguments**

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
    static int counter;
    
public:
    // Default constructor
    MyClass() {
        id = ++counter;
        name = "Default";
        cout << "Default constructor: " << name << " (ID: " << id << ")" << endl;
    }
    
    // Parameterized constructor
    MyClass(string n) : name(n) {
        id = ++counter;
        cout << "Parameterized: " << name << " (ID: " << id << ")" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
    }
};

int MyClass::counter = 0;

int main() {
    MyClass obj1;              // Default
    MyClass obj2("Custom");    // Parameterized
    MyClass obj3;              // Default
    MyClass arr[2];            // Default twice
    
    obj1.display();
    obj2.display();
    obj3.display();
    
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
    static int counter;
    
public:
    MyClass();
    MyClass(string n);
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

MyClass::MyClass() {
    id = ++counter;
    name = "Default";
    cout << "Default constructor: " << name << " (ID: " << id << ")" << endl;
}

MyClass::MyClass(string n) : name(n) {
    id = ++counter;
    cout << "Parameterized: " << name << " (ID: " << id << ")" << endl;
}

void MyClass::display() const {
    cout << "ID: " << id << ", Name: " << name << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "myclass.h"
using namespace std;

int main() {
    MyClass obj1;
    MyClass obj2("Custom");
    obj1.display();
    obj2.display();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*