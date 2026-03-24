# 90 - const Member Functions in C++

## What are const Member Functions?
A const member function is a function that promises not to modify any member variables of the class. It can be called on const objects and provides read-only access to the object's data.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    double gpa;
    mutable int accessCount;  // mutable allows modification even in const functions
    
public:
    Student(string n, int roll, double g) 
        : name(n), rollNumber(roll), gpa(g), accessCount(0) {}
    
    // const member functions - promise not to modify object
    string getName() const { 
        accessCount++;  // OK - mutable member can be modified
        return name; 
    }
    
    int getRollNumber() const { 
        accessCount++;
        return rollNumber; 
    }
    
    double getGpa() const { 
        accessCount++;
        return gpa; 
    }
    
    int getAccessCount() const { return accessCount; }
    
    // Non-const member function - can modify
    void setGpa(double g) { 
        gpa = g; 
        cout << "GPA updated to: " << gpa << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Roll: " << rollNumber 
             << ", GPA: " << gpa << endl;
    }
};

int main() {
    // Const object - can only call const member functions
    const Student s1("John", 101, 3.5);
    
    cout << "Const object access:" << endl;
    cout << "Name: " << s1.getName() << endl;
    cout << "Roll: " << s1.getRollNumber() << endl;
    cout << "GPA: " << s1.getGpa() << endl;
    // s1.setGpa(3.8);  // Error! Cannot call non-const on const object
    
    // Non-const object - can call both const and non-const
    Student s2("Alice", 102, 3.8);
    s2.setGpa(3.9);  // OK
    s2.display();     // OK
    
    cout << "\nAccess count for s1: " << s1.getAccessCount() << endl;
    
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
    int rollNumber;
    double gpa;
    mutable int accessCount;
    
public:
    Student(string n, int roll, double g);
    string getName() const;
    int getRollNumber() const;
    double getGpa() const;
    int getAccessCount() const;
    void setGpa(double g);
    void display() const;
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student(string n, int roll, double g) 
    : name(n), rollNumber(roll), gpa(g), accessCount(0) {}

string Student::getName() const { 
    accessCount++;
    return name; 
}

int Student::getRollNumber() const { 
    accessCount++;
    return rollNumber; 
}

double Student::getGpa() const { 
    accessCount++;
    return gpa; 
}

int Student::getAccessCount() const { return accessCount; }

void Student::setGpa(double g) { 
    gpa = g; 
    cout << "GPA updated to: " << gpa << endl;
}

void Student::display() const {
    cout << "Name: " << name << ", Roll: " << rollNumber 
         << ", GPA: " << gpa << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    const Student s1("John", 101, 3.5);
    cout << "Name: " << s1.getName() << endl;
    
    Student s2("Alice", 102, 3.8);
    s2.setGpa(3.9);
    s2.display();
    
    return 0;
}
```

## Why Use const Member Functions?

### 1. Read-Only Access Guarantee
```cpp
class DataProcessor {
private:
    int* data;
    int size;
    
public:
    // Const function - promises not to modify
    int getSize() const { return size; }
    
    // Non-const function - may modify
    void setSize(int s) { size = s; }
    
    // Const function with pointer - can't modify pointer data
    int getElement(int index) const {
        // data[index] = 10;  // Error! Can't modify in const function
        return data[index];    // OK - reading is fine
    }
};
```

### 2. Working with Const Objects
```cpp
void printStudent(const Student& s) {
    // Can only call const member functions
    cout << s.getName() << endl;
    cout << s.getRollNumber() << endl;
    // s.setGpa(4.0);  // Error! Can't call non-const on const reference
}
```

### 3. Function Overloading Based on const
```cpp
class Array {
private:
    int data[10];
    
public:
    // For const objects - returns const reference
    const int& operator[](int index) const {
        return data[index];
    }
    
    // For non-const objects - returns reference (allows modification)
    int& operator[](int index) {
        return data[index];
    }
};

int main() {
    Array arr;
    const Array& constArr = arr;
    
    arr[0] = 10;        // OK - calls non-const version
    // constArr[0] = 20;  // Error - calls const version (read-only)
    int val = constArr[0];  // OK - reading
    
    return 0;
}
```

## const and Pointers in Member Functions

```cpp
class Buffer {
private:
    int* data;
    int size;
    
public:
    Buffer(int s) : size(s), data(new int[s]) {}
    
    // Const function - cannot modify pointer, but can modify what it points to?
    void modifyValue(int index, int value) const {
        // data = new int[20];  // Error! Can't modify pointer
        data[index] = value;     // OK! Can modify what pointer points to
        // This is a common pitfall!
    }
    
    // To prevent modifying pointed data, use const pointer
    void safeModify(int index, int value) const {
        // data[index] = value;  // Would be error if data was const int*
    }
    
    ~Buffer() { delete[] data; }
};
```

## The mutable Keyword

```cpp
class Logger {
private:
    string name;
    mutable int logCount;  // Can be modified in const functions
    
public:
    Logger(string n) : name(n), logCount(0) {}
    
    void log(const string& message) const {
        logCount++;  // OK - mutable allows modification
        cout << "[" << name << "] " << message << endl;
    }
    
    int getLogCount() const { return logCount; }
};

int main() {
    const Logger logger("System");
    logger.log("Starting up");
    logger.log("Processing data");
    logger.log("Shutting down");
    
    cout << "Log count: " << logger.getLogCount() << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Rectangle Class with const Correctness

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
    mutable int areaCalculations;
    
public:
    Rectangle(double l, double w) : length(l), width(w), areaCalculations(0) {}
    
    // Const member functions - read-only
    double getLength() const { return length; }
    double getWidth() const { return width; }
    
    double getArea() const { 
        areaCalculations++;  // mutable - OK
        return length * width; 
    }
    
    double getPerimeter() const { 
        return 2 * (length + width); 
    }
    
    double getDiagonal() const { 
        return sqrt(length * length + width * width); 
    }
    
    bool isSquare() const { 
        return length == width; 
    }
    
    int getAreaCalculations() const { return areaCalculations; }
    
    // Non-const member functions - can modify
    void setLength(double l) { 
        if (l > 0) length = l; 
    }
    
    void setWidth(double w) { 
        if (w > 0) width = w; 
    }
    
    void scale(double factor) {
        if (factor > 0) {
            length *= factor;
            width *= factor;
        }
    }
    
    void display() const {
        cout << "Rectangle: " << length << " x " << width << endl;
        cout << "Area: " << getArea() << ", Perimeter: " << getPerimeter() << endl;
        cout << "Diagonal: " << getDiagonal() << ", Square: " << (isSquare() ? "Yes" : "No") << endl;
    }
};

void printRectangleInfo(const Rectangle& r) {
    // Can only call const functions
    cout << "Rectangle info (const reference):" << endl;
    cout << "  Length: " << r.getLength() << endl;
    cout << "  Width: " << r.getWidth() << endl;
    cout << "  Area: " << r.getArea() << endl;
}

int main() {
    Rectangle rect(5.0, 3.0);
    rect.display();
    
    rect.setLength(6.0);
    rect.scale(2);
    cout << "\nAfter modifications:" << endl;
    rect.display();
    
    printRectangleInfo(rect);
    
    cout << "\nArea calculations performed: " << rect.getAreaCalculations() << endl;
    
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
    mutable int areaCalculations;
    
public:
    Rectangle(double l, double w);
    double getLength() const;
    double getWidth() const;
    double getArea() const;
    double getPerimeter() const;
    double getDiagonal() const;
    bool isSquare() const;
    int getAreaCalculations() const;
    void setLength(double l);
    void setWidth(double w);
    void scale(double factor);
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

Rectangle::Rectangle(double l, double w) : length(l), width(w), areaCalculations(0) {}

double Rectangle::getLength() const { return length; }
double Rectangle::getWidth() const { return width; }

double Rectangle::getArea() const { 
    areaCalculations++;
    return length * width; 
}

double Rectangle::getPerimeter() const { 
    return 2 * (length + width); 
}

double Rectangle::getDiagonal() const { 
    return sqrt(length * length + width * width); 
}

bool Rectangle::isSquare() const { 
    return length == width; 
}

int Rectangle::getAreaCalculations() const { return areaCalculations; }

void Rectangle::setLength(double l) { 
    if (l > 0) length = l; 
}

void Rectangle::setWidth(double w) { 
    if (w > 0) width = w; 
}

void Rectangle::scale(double factor) {
    if (factor > 0) {
        length *= factor;
        width *= factor;
    }
}

void Rectangle::display() const {
    cout << "Rectangle: " << length << " x " << width << endl;
    cout << "Area: " << getArea() << ", Perimeter: " << getPerimeter() << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "rectangle.h"
using namespace std;

int main() {
    Rectangle rect(5.0, 3.0);
    rect.display();
    rect.setLength(6.0);
    rect.display();
    cout << "Area calculations: " << rect.getAreaCalculations() << endl;
    return 0;
}
```

### Example 2: String Class with const Correctness

#### Type 1: Single File
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private:
    char* data;
    int length;
    mutable int accessCount;
    
public:
    MyString(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        accessCount = 0;
    }
    
    // Const member functions - read-only access
    int getLength() const { return length; }
    
    char charAt(int index) const {
        accessCount++;
        if (index >= 0 && index < length) {
            return data[index];
        }
        return '\0';
    }
    
    const char* c_str() const { return data; }
    
    int getAccessCount() const { return accessCount; }
    
    // Overloaded operator[] based on const
    char& operator[](int index) {
        if (index >= 0 && index < length) {
            return data[index];
        }
        static char dummy = '\0';
        return dummy;
    }
    
    const char& operator[](int index) const {
        if (index >= 0 && index < length) {
            return data[index];
        }
        static char dummy = '\0';
        return dummy;
    }
    
    // Non-const member functions - can modify
    void setChar(int index, char ch) {
        if (index >= 0 && index < length) {
            data[index] = ch;
        }
    }
    
    void append(const char* str) {
        int newLen = length + strlen(str);
        char* newData = new char[newLen + 1];
        strcpy(newData, data);
        strcat(newData, str);
        delete[] data;
        data = newData;
        length = newLen;
    }
    
    void display() const {
        cout << data << " (length: " << length << ")" << endl;
    }
    
    ~MyString() {
        delete[] data;
    }
};

int main() {
    MyString s1("Hello");
    MyString s2("World");
    
    cout << "s1: ";
    s1.display();
    
    // Non-const operations
    s1[0] = 'J';
    s1.append(" C++");
    
    cout << "After modifications: ";
    s1.display();
    
    // Const access
    const MyString& constRef = s1;
    cout << "First char via const reference: " << constRef.charAt(0) << endl;
    cout << "C-string: " << constRef.c_str() << endl;
    
    cout << "Access count: " << constRef.getAccessCount() << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**mystring.h**
```cpp
#ifndef MYSTRING_H
#define MYSTRING_H

class MyString {
private:
    char* data;
    int length;
    mutable int accessCount;
    
public:
    MyString(const char* str = "");
    ~MyString();
    
    int getLength() const;
    char charAt(int index) const;
    const char* c_str() const;
    int getAccessCount() const;
    
    char& operator[](int index);
    const char& operator[](int index) const;
    
    void setChar(int index, char ch);
    void append(const char* str);
    void display() const;
};

#endif
```

**mystring.cpp**
```cpp
#include "mystring.h"
#include <iostream>
#include <cstring>
using namespace std;

MyString::MyString(const char* str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
    accessCount = 0;
}

MyString::~MyString() {
    delete[] data;
}

int MyString::getLength() const { return length; }

char MyString::charAt(int index) const {
    accessCount++;
    if (index >= 0 && index < length) {
        return data[index];
    }
    return '\0';
}

const char* MyString::c_str() const { return data; }
int MyString::getAccessCount() const { return accessCount; }

char& MyString::operator[](int index) {
    if (index >= 0 && index < length) {
        return data[index];
    }
    static char dummy = '\0';
    return dummy;
}

const char& MyString::operator[](int index) const {
    if (index >= 0 && index < length) {
        return data[index];
    }
    static char dummy = '\0';
    return dummy;
}

void MyString::setChar(int index, char ch) {
    if (index >= 0 && index < length) {
        data[index] = ch;
    }
}

void MyString::append(const char* str) {
    int newLen = length + strlen(str);
    char* newData = new char[newLen + 1];
    strcpy(newData, data);
    strcat(newData, str);
    delete[] data;
    data = newData;
    length = newLen;
}

void MyString::display() const {
    cout << data << " (length: " << length << ")" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "mystring.h"
using namespace std;

int main() {
    MyString s("Hello");
    s.display();
    s.append(" World");
    s.display();
    cout << "First char: " << s.charAt(0) << endl;
    return 0;
}
```

### Example 3: Bank Account with const Correctness

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
    string pin;
    time_t lastAccess;
    mutable int statementCount;
    
    bool authenticate(const string& inputPin) const {
        return pin == inputPin;
    }
    
public:
    BankAccount(string number, string holder, double initial, string p)
        : accountNumber(number), accountHolder(holder), balance(initial), 
          pin(p), statementCount(0) {
        lastAccess = time(nullptr);
    }
    
    // Const member functions - read-only with authentication
    double getBalance(const string& inputPin) const {
        if (authenticate(inputPin)) {
            return balance;
        }
        return -1;
    }
    
    string getAccountNumber() const {
        if (accountNumber.length() > 8) {
            return "****" + accountNumber.substr(accountNumber.length() - 4);
        }
        return "****";
    }
    
    string getAccountHolder() const { return accountHolder; }
    
    string getLastAccess() const {
        return ctime(&lastAccess);
    }
    
    void printStatement() const {
        statementCount++;
        cout << "\n=== Account Statement ===" << endl;
        cout << "Account: " << getAccountNumber() << endl;
        cout << "Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Last Access: " << getLastAccess();
        cout << "Statement #: " << statementCount << endl;
    }
    
    int getStatementCount() const { return statementCount; }
    
    // Non-const member functions - can modify
    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            lastAccess = time(nullptr);
            return true;
        }
        return false;
    }
    
    bool withdraw(double amount, const string& inputPin) {
        if (authenticate(inputPin) && amount > 0 && amount <= balance) {
            balance -= amount;
            lastAccess = time(nullptr);
            return true;
        }
        return false;
    }
    
    void changePin(const string& oldPin, const string& newPin) {
        if (authenticate(oldPin) && newPin.length() >= 4) {
            pin = newPin;
            lastAccess = time(nullptr);
            cout << "PIN changed successfully" << endl;
        }
    }
};

int main() {
    BankAccount acc("1234567890", "John Doe", 1000.00, "1234");
    
    // Const operations
    acc.printStatement();
    cout << "Account holder: " << acc.getAccountHolder() << endl;
    cout << "Masked account: " << acc.getAccountNumber() << endl;
    
    // Non-const operations
    acc.deposit(500);
    acc.withdraw(200, "1234");
    
    // Another const operation
    acc.printStatement();
    
    cout << "Total statements: " << acc.getStatementCount() << endl;
    
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
    string pin;
    time_t lastAccess;
    mutable int statementCount;
    
    bool authenticate(const string& inputPin) const;
    
public:
    BankAccount(string number, string holder, double initial, string p);
    double getBalance(const string& inputPin) const;
    string getAccountNumber() const;
    string getAccountHolder() const;
    string getLastAccess() const;
    void printStatement() const;
    int getStatementCount() const;
    bool deposit(double amount);
    bool withdraw(double amount, const string& inputPin);
    void changePin(const string& oldPin, const string& newPin);
};

#endif
```

**bankaccount.cpp**
```cpp
#include "bankaccount.h"
#include <iostream>
#include <ctime>
using namespace std;

BankAccount::BankAccount(string number, string holder, double initial, string p)
    : accountNumber(number), accountHolder(holder), balance(initial), 
      pin(p), statementCount(0) {
    lastAccess = time(nullptr);
}

bool BankAccount::authenticate(const string& inputPin) const {
    return pin == inputPin;
}

double BankAccount::getBalance(const string& inputPin) const {
    if (authenticate(inputPin)) {
        return balance;
    }
    return -1;
}

string BankAccount::getAccountNumber() const {
    if (accountNumber.length() > 8) {
        return "****" + accountNumber.substr(accountNumber.length() - 4);
    }
    return "****";
}

string BankAccount::getAccountHolder() const { return accountHolder; }

string BankAccount::getLastAccess() const {
    return ctime(&lastAccess);
}

void BankAccount::printStatement() const {
    statementCount++;
    cout << "\n=== Account Statement ===" << endl;
    cout << "Account: " << getAccountNumber() << endl;
    cout << "Holder: " << accountHolder << endl;
    cout << "Balance: $" << balance << endl;
    cout << "Last Access: " << getLastAccess();
    cout << "Statement #: " << statementCount << endl;
}

int BankAccount::getStatementCount() const { return statementCount; }

bool BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        lastAccess = time(nullptr);
        return true;
    }
    return false;
}

bool BankAccount::withdraw(double amount, const string& inputPin) {
    if (authenticate(inputPin) && amount > 0 && amount <= balance) {
        balance -= amount;
        lastAccess = time(nullptr);
        return true;
    }
    return false;
}

void BankAccount::changePin(const string& oldPin, const string& newPin) {
    if (authenticate(oldPin) && newPin.length() >= 4) {
        pin = newPin;
        lastAccess = time(nullptr);
        cout << "PIN changed successfully" << endl;
    }
}
```

**main.cpp**
```cpp
#include <iostream>
#include "bankaccount.h"
using namespace std;

int main() {
    BankAccount acc("1234567890", "John Doe", 1000.00, "1234");
    acc.printStatement();
    acc.deposit(500);
    acc.printStatement();
    return 0;
}
```

## const Member Function Rules

```cpp
class Example {
private:
    int value;
    int* ptr;
    mutable int counter;
    
public:
    // Can read members
    int getValue() const { return value; }           // OK
    
    // Can modify mutable members
    void incrementCounter() const { counter++; }     // OK
    
    // Can modify what pointer points to (pitfall!)
    void modifyPointer() const { 
        *ptr = 10;  // OK! Pointer is const, but pointed data is not
    }
    
    // Cannot reassign pointer
    // void reassignPointer() const { ptr = new int; }  // Error!
    
    // Cannot modify non-mutable members
    // void setValue(int v) const { value = v; }       // Error!
    
    // Can call other const functions
    int getDouble() const { return getValue() * 2; }  // OK
    
    // Cannot call non-const functions
    // void bad() const { setValue(10); }              // Error!
};
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Missing const on getters | Can't call on const objects | Add const to all read-only functions |
| Modifying members in const | Compilation error | Use mutable for counters/caches |
| Assuming pointer data is const | Accidental modification | Use const pointer to const data |
| Forgetting const overload | Const objects use wrong version | Provide both const and non-const |
| Const-casting | Undefined behavior | Never use const_cast to modify |

## Summary

- **const member functions** promise not to modify object state
- Called on **const objects** and **const references**
- Enable **const correctness** throughout code
- **mutable** allows modification even in const functions
- **Overload** functions based on const for read/write access
- Getters should be **const**
- Setters and modifiers should be **non-const**
- Improves **code safety** and **readability**

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class MyClass {
private:
    int data;
    mutable int accessCount;
    
public:
    MyClass(int d) : data(d), accessCount(0) {}
    
    // Const member functions - read-only
    int getData() const { 
        accessCount++;
        return data; 
    }
    
    int getAccessCount() const { return accessCount; }
    
    // Non-const member functions - can modify
    void setData(int d) { 
        data = d; 
        accessCount++;
    }
    
    void display() const {
        cout << "Data: " << data << ", Accesses: " << accessCount << endl;
    }
};

int main() {
    const MyClass constObj(100);
    MyClass nonConstObj(200);
    
    cout << "Const object: " << constObj.getData() << endl;
    nonConstObj.setData(300);
    nonConstObj.display();
    
    return 0;
}
```

### Type 2: Multiple Files

**myclass.h**
```cpp
#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass {
private:
    int data;
    mutable int accessCount;
    
public:
    MyClass(int d);
    int getData() const;
    int getAccessCount() const;
    void setData(int d);
    void display() const;
};

#endif
```

**myclass.cpp**
```cpp
#include "myclass.h"
#include <iostream>
using namespace std;

MyClass::MyClass(int d) : data(d), accessCount(0) {}

int MyClass::getData() const { 
    accessCount++;
    return data; 
}

int MyClass::getAccessCount() const { return accessCount; }

void MyClass::setData(int d) { 
    data = d; 
    accessCount++;
}

void MyClass::display() const {
    cout << "Data: " << data << ", Accesses: " << accessCount << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "myclass.h"
using namespace std;

int main() {
    MyClass obj(100);
    obj.setData(200);
    obj.display();
    cout << "Data: " << obj.getData() << endl;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*