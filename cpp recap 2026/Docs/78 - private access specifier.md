# 78 - Private Access Specifier in C++

## What is Private Access Specifier?
The `private` access specifier restricts access to class members so they can only be accessed within the class itself. Private members are hidden from outside the class, providing encapsulation and data hiding.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    // Private members - cannot be accessed directly from outside
    string accountNumber;
    double balance;
    string pin;
    int failedAttempts;
    
    // Private helper function
    bool verifyPin(string inputPin) {
        return pin == inputPin;
    }
    
public:
    // Constructor
    BankAccount(string accNum, double initialBalance, string userPin) {
        accountNumber = accNum;
        balance = initialBalance;
        pin = userPin;
        failedAttempts = 0;
    }
    
    // Public interface
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
            cout << "New balance: $" << balance << endl;
        }
    }
    
    bool withdraw(double amount, string inputPin) {
        if (!verifyPin(inputPin)) {
            failedAttempts++;
            cout << "Wrong PIN! Attempts: " << failedAttempts << endl;
            return false;
        }
        
        if (amount <= 0 || amount > balance) {
            cout << "Invalid amount or insufficient funds!" << endl;
            return false;
        }
        
        balance -= amount;
        cout << "Withdrawn: $" << amount << endl;
        cout << "New balance: $" << balance << endl;
        failedAttempts = 0;
        return true;
    }
    
    double getBalance(string inputPin) {
        if (verifyPin(inputPin)) {
            return balance;
        }
        cout << "Wrong PIN!" << endl;
        return -1;
    }
    
    string getAccountNumber() const {
        return accountNumber;
    }
};

int main() {
    // Creating account
    BankAccount acc("ACC12345", 1000.00, "1234");
    
    cout << "Account: " << acc.getAccountNumber() << endl;
    
    // Cannot access private members directly
    // acc.balance = 5000;     // Error! balance is private
    // acc.verifyPin("1234");  // Error! verifyPin is private
    
    // Using public interface
    acc.deposit(500);
    acc.withdraw(200, "1234");
    
    double balance = acc.getBalance("1234");
    cout << "Balance from getter: $" << balance << endl;
    
    // Wrong PIN attempt
    acc.withdraw(100, "9999");
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### bankaccount.h
```cpp
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
using namespace std;

class BankAccount {
private:
    // Private members
    string accountNumber;
    double balance;
    string pin;
    int failedAttempts;
    
    // Private helper function
    bool verifyPin(string inputPin);
    
public:
    // Constructor
    BankAccount(string accNum, double initialBalance, string userPin);
    
    // Public interface
    void deposit(double amount);
    bool withdraw(double amount, string inputPin);
    double getBalance(string inputPin);
    string getAccountNumber() const;
};

#endif
```

### bankaccount.cpp
```cpp
#include "bankaccount.h"
#include <iostream>
using namespace std;

BankAccount::BankAccount(string accNum, double initialBalance, string userPin) {
    accountNumber = accNum;
    balance = initialBalance;
    pin = userPin;
    failedAttempts = 0;
}

bool BankAccount::verifyPin(string inputPin) {
    return pin == inputPin;
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "Deposited: $" << amount << endl;
        cout << "New balance: $" << balance << endl;
    }
}

bool BankAccount::withdraw(double amount, string inputPin) {
    if (!verifyPin(inputPin)) {
        failedAttempts++;
        cout << "Wrong PIN! Attempts: " << failedAttempts << endl;
        return false;
    }
    
    if (amount <= 0 || amount > balance) {
        cout << "Invalid amount or insufficient funds!" << endl;
        return false;
    }
    
    balance -= amount;
    cout << "Withdrawn: $" << amount << endl;
    cout << "New balance: $" << balance << endl;
    failedAttempts = 0;
    return true;
}

double BankAccount::getBalance(string inputPin) {
    if (verifyPin(inputPin)) {
        return balance;
    }
    cout << "Wrong PIN!" << endl;
    return -1;
}

string BankAccount::getAccountNumber() const {
    return accountNumber;
}
```

### main.cpp
```cpp
#include <iostream>
#include "bankaccount.h"
using namespace std;

int main() {
    BankAccount acc("ACC12345", 1000.00, "1234");
    
    cout << "Account: " << acc.getAccountNumber() << endl;
    
    acc.deposit(500);
    acc.withdraw(200, "1234");
    
    double balance = acc.getBalance("1234");
    cout << "Balance: $" << balance << endl;
    
    return 0;
}
```

## Private vs Public Comparison

```cpp
#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    // Private - hidden from outside
    string ssn;           // Social Security Number
    double salary;
    int employeeId;
    static int nextId;
    
    // Private helper
    void generateId() {
        employeeId = nextId++;
    }
    
public:
    // Public - accessible interface
    string name;
    string department;
    
    Employee(string n, string dept, string ssnNumber, double initialSalary) {
        name = n;
        department = dept;
        ssn = ssnNumber;
        salary = initialSalary;
        generateId();
    }
    
    void setSalary(double newSalary) {
        if (newSalary >= 0) {
            salary = newSalary;
        }
    }
    
    double getSalary() const {
        return salary;
    }
    
    string getSSN() const {
        // Only show last 4 digits
        return "XXX-XX-" + ssn.substr(ssn.length() - 4);
    }
    
    int getId() const {
        return employeeId;
    }
    
    void display() const {
        cout << "ID: " << employeeId << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "SSN: " << getSSN() << endl;
        cout << "Salary: $" << salary << endl;
    }
};

int Employee::nextId = 1000;

int main() {
    Employee emp("John Doe", "Engineering", "123-45-6789", 75000);
    
    // Public members accessible
    cout << "Name: " << emp.name << endl;
    cout << "Department: " << emp.department << endl;
    
    // Private members NOT accessible
    // emp.salary = 80000;    // Error!
    // emp.ssn = "111-22-3333"; // Error!
    // emp.employeeId = 999;   // Error!
    
    // Access through public methods
    emp.setSalary(85000);
    cout << "Salary: $" << emp.getSalary() << endl;
    cout << "SSN: " << emp.getSSN() << endl;
    cout << "ID: " << emp.getId() << endl;
    
    emp.display();
    
    return 0;
}
```

## Practical Examples

### Example 1: Student Class with Private Data

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    vector<double> grades;
    double average;
    
    // Private helper - automatically updates average
    void calculateAverage() {
        if (grades.empty()) {
            average = 0;
            return;
        }
        double sum = 0;
        for (double g : grades) {
            sum += g;
        }
        average = sum / grades.size();
    }
    
public:
    // Constructor
    Student(string n, int roll) : name(n), rollNumber(roll), average(0) {}
    
    // Public interface
    void addGrade(double grade) {
        if (grade >= 0 && grade <= 100) {
            grades.push_back(grade);
            calculateAverage();
        }
    }
    
    string getName() const { return name; }
    int getRollNumber() const { return rollNumber; }
    double getAverage() const { return average; }
    
    void display() const {
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Grades: ";
        for (double g : grades) cout << g << " ";
        cout << endl;
        cout << "Average: " << average << endl;
    }
};

int main() {
    Student s("Alice", 101);
    
    s.addGrade(85.5);
    s.addGrade(92.0);
    s.addGrade(78.5);
    
    s.display();
    
    // Cannot access private members
    // s.grades.push_back(95);  // Error!
    // s.average = 90;          // Error!
    
    return 0;
}
```

#### Type 2: Multiple Files

**student.h**
```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    vector<double> grades;
    double average;
    
    void calculateAverage();
    
public:
    Student(string n, int roll);
    void addGrade(double grade);
    string getName() const;
    int getRollNumber() const;
    double getAverage() const;
    void display() const;
};

#endif
```

**student.cpp**
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student(string n, int roll) : name(n), rollNumber(roll), average(0) {}

void Student::calculateAverage() {
    if (grades.empty()) {
        average = 0;
        return;
    }
    double sum = 0;
    for (double g : grades) {
        sum += g;
    }
    average = sum / grades.size();
}

void Student::addGrade(double grade) {
    if (grade >= 0 && grade <= 100) {
        grades.push_back(grade);
        calculateAverage();
    }
}

string Student::getName() const { return name; }
int Student::getRollNumber() const { return rollNumber; }
double Student::getAverage() const { return average; }

void Student::display() const {
    cout << "Name: " << name << endl;
    cout << "Roll Number: " << rollNumber << endl;
    cout << "Grades: ";
    for (double g : grades) cout << g << " ";
    cout << endl;
    cout << "Average: " << average << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student s("Alice", 101);
    s.addGrade(85.5);
    s.addGrade(92.0);
    s.addGrade(78.5);
    s.display();
    return 0;
}
```

### Example 2: Time Class with Validation

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
    
    // Private helper - ensures valid time
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
        if (hours < 0) hours = 0;
        if (minutes < 0) minutes = 0;
        if (seconds < 0) seconds = 0;
    }
    
public:
    // Constructor with validation
    Time(int h = 0, int m = 0, int s = 0) {
        hours = (h >= 0 && h < 24) ? h : 0;
        minutes = (m >= 0 && m < 60) ? m : 0;
        seconds = (s >= 0 && s < 60) ? s : 0;
        normalize();
    }
    
    // Setters with validation
    void setHours(int h) {
        if (h >= 0 && h < 24) hours = h;
    }
    
    void setMinutes(int m) {
        if (m >= 0 && m < 60) minutes = m;
    }
    
    void setSeconds(int s) {
        if (s >= 0 && s < 60) seconds = s;
    }
    
    // Getters
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }
    
    // Operations
    void addSeconds(int s) {
        seconds += s;
        normalize();
    }
    
    void addMinutes(int m) {
        minutes += m;
        normalize();
    }
    
    void addHours(int h) {
        hours += h;
        normalize();
    }
    
    void display() const {
        cout << setfill('0') 
             << setw(2) << hours << ":"
             << setw(2) << minutes << ":"
             << setw(2) << seconds << endl;
    }
};

int main() {
    Time t1(2, 30, 45);
    Time t2(25, 70, 90);  // Invalid - will be normalized
    
    cout << "t1: "; t1.display();
    cout << "t2 (normalized): "; t2.display();
    
    t1.addSeconds(45);
    cout << "t1 + 45s: "; t1.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**time.h**
```cpp
#ifndef TIME_H
#define TIME_H

class Time {
private:
    int hours;
    int minutes;
    int seconds;
    
    void normalize();
    
public:
    Time(int h = 0, int m = 0, int s = 0);
    void setHours(int h);
    void setMinutes(int m);
    void setSeconds(int s);
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    void addSeconds(int s);
    void addMinutes(int m);
    void addHours(int h);
    void display() const;
};

#endif
```

**time.cpp**
```cpp
#include "time.h"
#include <iostream>
#include <iomanip>
using namespace std;

Time::Time(int h, int m, int s) {
    hours = (h >= 0 && h < 24) ? h : 0;
    minutes = (m >= 0 && m < 60) ? m : 0;
    seconds = (s >= 0 && s < 60) ? s : 0;
    normalize();
}

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
    if (hours < 0) hours = 0;
    if (minutes < 0) minutes = 0;
    if (seconds < 0) seconds = 0;
}

void Time::setHours(int h) {
    if (h >= 0 && h < 24) hours = h;
}

void Time::setMinutes(int m) {
    if (m >= 0 && m < 60) minutes = m;
}

void Time::setSeconds(int s) {
    if (s >= 0 && s < 60) seconds = s;
}

int Time::getHours() const { return hours; }
int Time::getMinutes() const { return minutes; }
int Time::getSeconds() const { return seconds; }

void Time::addSeconds(int s) {
    seconds += s;
    normalize();
}

void Time::addMinutes(int m) {
    minutes += m;
    normalize();
}

void Time::addHours(int h) {
    hours += h;
    normalize();
}

void Time::display() const {
    cout << setfill('0') 
         << setw(2) << hours << ":"
         << setw(2) << minutes << ":"
         << setw(2) << seconds << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "time.h"
using namespace std;

int main() {
    Time t1(2, 30, 45);
    t1.display();
    t1.addSeconds(45);
    t1.display();
    return 0;
}
```

### Example 3: Counter with Private Static Member

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class Counter {
private:
    int id;
    static int nextId;
    string name;
    static int totalObjects;
    
    // Private constructor - can only be created through factory
    Counter(string n) : name(n) {
        id = nextId++;
        totalObjects++;
    }
    
public:
    // Factory method - controls object creation
    static Counter create(string name) {
        if (name.empty()) {
            cout << "Invalid name!" << endl;
            return Counter("Default");
        }
        return Counter(name);
    }
    
    // Static getters
    static int getTotalObjects() { return totalObjects; }
    static int getNextId() { return nextId; }
    
    // Instance getters
    int getId() const { return id; }
    string getName() const { return name; }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
    }
};

int Counter::nextId = 1;
int Counter::totalObjects = 0;

int main() {
    Counter c1 = Counter::create("First");
    Counter c2 = Counter::create("Second");
    Counter c3 = Counter::create("Third");
    
    c1.display();
    c2.display();
    c3.display();
    
    cout << "Total objects: " << Counter::getTotalObjects() << endl;
    cout << "Next ID: " << Counter::getNextId() << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**counter.h**
```cpp
#ifndef COUNTER_H
#define COUNTER_H

#include <string>
using namespace std;

class Counter {
private:
    int id;
    static int nextId;
    string name;
    static int totalObjects;
    
    Counter(string n);
    
public:
    static Counter create(string name);
    static int getTotalObjects();
    static int getNextId();
    int getId() const;
    string getName() const;
    void display() const;
};

#endif
```

**counter.cpp**
```cpp
#include "counter.h"
#include <iostream>
using namespace std;

int Counter::nextId = 1;
int Counter::totalObjects = 0;

Counter::Counter(string n) : name(n) {
    id = nextId++;
    totalObjects++;
}

Counter Counter::create(string name) {
    if (name.empty()) {
        cout << "Invalid name!" << endl;
        return Counter("Default");
    }
    return Counter(name);
}

int Counter::getTotalObjects() { return totalObjects; }
int Counter::getNextId() { return nextId; }
int Counter::getId() const { return id; }
string Counter::getName() const { return name; }

void Counter::display() const {
    cout << "ID: " << id << ", Name: " << name << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "counter.h"
using namespace std;

int main() {
    Counter c1 = Counter::create("First");
    Counter c2 = Counter::create("Second");
    
    c1.display();
    c2.display();
    cout << "Total: " << Counter::getTotalObjects() << endl;
    
    return 0;
}
```

## Why Use Private Members?

### Benefits of Encapsulation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string name;
    double price;
    int quantity;
    
    // Private validation logic
    bool isValidPrice(double p) {
        return p >= 0;
    }
    
    bool isValidQuantity(int q) {
        return q >= 0;
    }
    
public:
    Product(string n, double p, int q) {
        name = n;
        setPrice(p);
        setQuantity(q);
    }
    
    void setPrice(double p) {
        if (isValidPrice(p)) {
            price = p;
        } else {
            cout << "Invalid price!" << endl;
            price = 0;
        }
    }
    
    void setQuantity(int q) {
        if (isValidQuantity(q)) {
            quantity = q;
        } else {
            cout << "Invalid quantity!" << endl;
            quantity = 0;
        }
    }
    
    double getTotalValue() const {
        return price * quantity;
    }
    
    void display() const {
        cout << name << ": $" << price << " x " << quantity 
             << " = $" << getTotalValue() << endl;
    }
};

int main() {
    Product p1("Laptop", 999.99, 10);
    Product p2("Phone", -50, -5);  // Invalid values - will be corrected
    
    p1.display();
    p2.display();
    
    // Cannot directly corrupt data
    // p1.price = -100;      // Error! Private
    // p1.quantity = -10;    // Error! Private
    
    p1.setPrice(799.99);     // Valid
    p1.setQuantity(-5);      // Invalid - will be rejected
    
    p1.display();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Making everything public | No encapsulation, data corruption | Use private for data |
| Making everything private | No interface, unusable class | Provide public methods |
| Forgetting to initialize private members | Garbage values | Initialize in constructor |
| Accessing private members in derived class | Compilation error | Use protected instead |
| Private virtual functions | Cannot override | Make protected or public |

## Quick Reference

| Access Level | Inside Class | Derived Class | Outside |
|--------------|--------------|---------------|---------|
| Private | ✅ Yes | ❌ No | ❌ No |
| Protected | ✅ Yes | ✅ Yes | ❌ No |
| Public | ✅ Yes | ✅ Yes | ✅ Yes |

## Summary

- **Private** members are only accessible within the class
- **Encapsulation** hides implementation details
- **Data hiding** prevents invalid state
- **Private helper functions** organize internal logic
- **Getters/Setters** provide controlled access
- **Constructors** initialize private members
- **Friends** can bypass private access (use sparingly)
- **Static private members** shared across objects

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class MyClass {
private:
    int data;
    string name;
    static int count;
    
    void privateHelper() {
        // Internal logic
    }
    
public:
    MyClass(string n, int d) : name(n), data(d) { count++; }
    
    int getData() const { return data; }
    string getName() const { return name; }
    static int getCount() { return count; }
    
    void setData(int d) {
        if (d >= 0) data = d;
    }
    
    void display() const {
        cout << name << ": " << data << endl;
    }
};

int MyClass::count = 0;

int main() {
    MyClass obj("Test", 42);
    obj.display();
    obj.setData(100);
    obj.display();
    cout << "Count: " << MyClass::getCount() << endl;
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
    int data;
    string name;
    static int count;
    
    void privateHelper();
    
public:
    MyClass(string n, int d);
    int getData() const;
    string getName() const;
    static int getCount();
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

int MyClass::count = 0;

MyClass::MyClass(string n, int d) : name(n), data(d) { count++; }

void MyClass::privateHelper() {
    // Internal logic
}

int MyClass::getData() const { return data; }
string MyClass::getName() const { return name; }
int MyClass::getCount() { return count; }

void MyClass::setData(int d) {
    if (d >= 0) data = d;
}

void MyClass::display() const {
    cout << name << ": " << data << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "myclass.h"
using namespace std;

int main() {
    MyClass obj("Test", 42);
    obj.display();
    obj.setData(100);
    obj.display();
    cout << "Count: " << MyClass::getCount() << endl;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*