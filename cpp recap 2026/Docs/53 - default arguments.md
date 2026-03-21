# 53 - Default Arguments in C++

## What are Default Arguments?
Default arguments are values provided in function parameters that are used when the caller doesn't supply an argument for that parameter. They make functions more flexible and reduce the need for multiple overloaded functions.

## Basic Syntax

```cpp
return_type function_name(parameter1 = default_value, parameter2 = default_value) {
    // function body
}
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

// Default argument for greeting
void greet(string name, string greeting = "Hello") {
    cout << greeting << ", " << name << "!" << endl;
}

int main() {
    greet("John");              // Uses default greeting "Hello"
    greet("Jane", "Hi");        // Uses provided greeting "Hi"
    greet("Bob", "Good morning"); // Uses provided greeting
    
    return 0;
}
```

## Single Default Parameter

```cpp
#include <iostream>
using namespace std;

void display(int value, int width = 1) {
    cout << "Value: " << value << ", Width: " << width << endl;
}

int main() {
    display(42);       // width defaults to 1
    display(42, 5);    // width is 5
    
    return 0;
}
```

## Multiple Default Parameters

```cpp
#include <iostream>
using namespace std;

void printInfo(string name, int age = 0, string city = "Unknown") {
    cout << "Name: " << name << ", Age: " << age << ", City: " << city << endl;
}

int main() {
    printInfo("John");                    // Uses both defaults
    printInfo("Jane", 25);                // Uses city default
    printInfo("Bob", 30, "New York");     // No defaults used
    
    return 0;
}
```

## Rules for Default Arguments

### Must be from Right to Left
```cpp
// CORRECT - defaults from right to left
void func1(int a, int b = 10);           // OK
void func2(int a, int b = 10, int c = 20); // OK

// WRONG - cannot have non-default after default
// void func3(int a = 5, int b, int c = 10); // Error!
// void func4(int a = 5, int b, int c);      // Error!
```

### Example of Correct Order
```cpp
#include <iostream>
using namespace std;

// Correct order: non-default parameters first, defaults at the end
void display(string name, int age = 0, bool active = true) {
    cout << name << ", Age: " << age;
    cout << ", Active: " << (active ? "Yes" : "No") << endl;
}

int main() {
    display("John");                  // age=0, active=true
    display("Jane", 25);              // active=true
    display("Bob", 30, false);        // all provided
    
    return 0;
}
```

## Practical Examples

### Example 1: Discount Calculator
```cpp
#include <iostream>
using namespace std;

double calculatePrice(double price, double discount = 0.0, double tax = 0.08) {
    double afterDiscount = price * (1 - discount);
    double finalPrice = afterDiscount * (1 + tax);
    return finalPrice;
}

int main() {
    cout << "Regular price: $" << calculatePrice(100) << endl;
    cout << "10% discount: $" << calculatePrice(100, 0.10) << endl;
    cout << "10% discount, 5% tax: $" << calculatePrice(100, 0.10, 0.05) << endl;
    
    return 0;
}
```

### Example 2: Greeting Function
```cpp
#include <iostream>
#include <string>
using namespace std;

void printGreeting(string name, string title = "Mr.", bool formal = true) {
    if (formal) {
        cout << "Good day, " << title << " " << name << "!" << endl;
    } else {
        cout << "Hey, " << name << "!" << endl;
    }
}

int main() {
    printGreeting("Smith");                     // Formal: Mr. Smith
    printGreeting("Johnson", "Ms.");            // Formal: Ms. Johnson
    printGreeting("Tom", "", false);            // Informal: Hey, Tom!
    
    return 0;
}
```

### Example 3: Array Print Function
```cpp
#include <iostream>
using namespace std;

void printArray(int arr[], int size, string separator = " ", bool newline = true) {
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << separator;
    }
    if (newline) cout << endl;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printArray(numbers, size);                    // "1 2 3 4 5" with newline
    printArray(numbers, size, ", ");              // "1, 2, 3, 4, 5" with newline
    printArray(numbers, size, " | ", false);      // "1 | 2 | 3 | 4 | 5" no newline
    
    return 0;
}
```

### Example 4: Logger Function
```cpp
#include <iostream>
#include <string>
using namespace std;

void logMessage(string message, string level = "INFO", bool timestamp = true) {
    if (timestamp) {
        cout << "[LOG] ";
    }
    cout << "[" << level << "] " << message << endl;
}

int main() {
    logMessage("Application started");                    // [LOG] [INFO] ...
    logMessage("User logged in", "DEBUG");                // [LOG] [DEBUG] ...
    logMessage("Error occurred", "ERROR", false);         // [ERROR] ...
    
    return 0;
}
```

### Example 5: Shape Area Functions
```cpp
#include <iostream>
#include <cmath>
using namespace std;

double area(double radius, double pi = 3.14159) {
    return pi * radius * radius;  // Circle area
}

double area(double length, double width, bool isRectangle = true) {
    return length * width;  // Rectangle area
}

double area(double base, double height, const string& shape = "triangle") {
    return 0.5 * base * height;  // Triangle area
}

int main() {
    cout << "Circle (r=5): " << area(5.0) << endl;
    cout << "Circle with exact pi: " << area(5.0, 3.14159265359) << endl;
    cout << "Rectangle (4x6): " << area(4.0, 6.0) << endl;
    cout << "Triangle (base=3, height=4): " << area(3.0, 4.0, "triangle") << endl;
    
    return 0;
}
```

## Default Arguments in Constructors

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    string course;
    
public:
    // Constructor with default arguments
    Student(string n = "Unknown", int a = 18, string c = "General") 
        : name(n), age(a), course(c) {}
    
    void display() {
        cout << name << ", " << age << " years, " << course << endl;
    }
};

int main() {
    Student s1;                           // Uses all defaults
    Student s2("John");                   // Uses age and course defaults
    Student s3("Jane", 20);               // Uses course default
    Student s4("Bob", 22, "Computer Science"); // No defaults
    
    s1.display();
    s2.display();
    s3.display();
    s4.display();
    
    return 0;
}
```

## Default Arguments in Overloaded Functions

```cpp
#include <iostream>
using namespace std;

// Using default arguments (simpler)
void show(string msg, int count = 1) {
    for (int i = 0; i < count; i++) {
        cout << msg << " ";
    }
    cout << endl;
}

// Without default arguments (would need multiple overloads)
// void show(string msg) {
//     show(msg, 1);
// }

int main() {
    show("Hello");           // Prints once
    show("Hello", 3);        // Prints three times
    
    return 0;
}
```

## Default Arguments vs Function Overloading

```cpp
#include <iostream>
using namespace std;

// Using default arguments (cleaner)
void createUser(string name, int age = 18, string role = "user") {
    cout << "User: " << name << ", Age: " << age << ", Role: " << role << endl;
}

// Using function overloading (more code)
// void createUser(string name) {
//     createUser(name, 18, "user");
// }
// void createUser(string name, int age) {
//     createUser(name, age, "user");
// }
// void createUser(string name, int age, string role) {
//     // actual implementation
// }

int main() {
    createUser("Alice");
    createUser("Bob", 25);
    createUser("Charlie", 30, "admin");
    
    return 0;
}
```

## Default Arguments with Pointers

```cpp
#include <iostream>
using namespace std;

void process(int *ptr = nullptr, int value = 0) {
    if (ptr != nullptr) {
        *ptr = value;
        cout << "Pointer updated: " << *ptr << endl;
    } else {
        cout << "Null pointer received" << endl;
    }
}

int main() {
    int x = 10;
    
    process(&x, 42);    // Updates x to 42
    process();          // Uses default nullptr
    
    cout << "x = " << x << endl;
    
    return 0;
}
```

## Default Arguments with References

```cpp
#include <iostream>
using namespace std;

void increment(int &x, int amount = 1) {
    x += amount;
}

int main() {
    int num = 5;
    
    increment(num);      // Adds 1
    cout << "After +1: " << num << endl;
    
    increment(num, 3);   // Adds 3
    cout << "After +3: " << num << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Skipping Parameters Incorrectly
```cpp
void display(int a, int b = 10, int c = 20) {
    cout << a << ", " << b << ", " << c << endl;
}

int main() {
    // WRONG - can't skip b and provide c
    // display(5, , 30);  // Error!
    
    // CORRECT - provide parameters in order
    display(5);          // a=5, b=10, c=20
    display(5, 15);      // a=5, b=15, c=20
    display(5, 15, 25);  // a=5, b=15, c=25
    
    return 0;
}
```

### Mistake 2: Non-Default After Default
```cpp
// WRONG
// void func(int a = 5, int b, int c = 10); // Error!

// CORRECT
void func(int a, int b, int c = 10);  // OK
void func(int a, int b = 5, int c = 10);  // OK
void func(int a = 5, int b = 5, int c = 10);  // OK
```

### Mistake 3: Default in Both Declaration and Definition
```cpp
// WRONG - default specified in both
void func(int a = 5);  // In header

void func(int a = 5) {  // In definition - error!
    cout << a << endl;
}

// CORRECT - default only in declaration (header)
void func(int a = 5);  // In header

void func(int a) {      // In definition - no default
    cout << a << endl;
}
```

### Mistake 4: Overloading with Default Arguments
```cpp
// WRONG - ambiguous
void print(int a) {
    cout << "One param: " << a << endl;
}

void print(int a, int b = 0) {
    cout << "Two params: " << a << ", " << b << endl;
}

int main() {
    // print(5);  // Ambiguous! Which one to call?
    
    return 0;
}

// CORRECT - avoid such combinations
void print(int a) {
    cout << a << endl;
}

void print(int a, int b) {
    cout << a << ", " << b << endl;
}
```

### Mistake 5: Using Default with Pass by Reference
```cpp
// WRONG - can't have default reference to temporary
void func(int &x = 5) {  // Error! Reference to temporary
    x++;
}

// CORRECT - const reference can have default
void func(const int &x = 5) {  // OK
    cout << x << endl;
}

// Or use pointer
void func(int *x = nullptr) {  // OK
    if (x) *x = 42;
}
```

## Default Arguments in Header Files

### Correct Way

**myfunction.h**
```cpp
#ifndef MYFUNCTION_H
#define MYFUNCTION_H

// Default arguments only in declaration
void display(int value, int width = 1, bool newline = true);

#endif
```

**myfunction.cpp**
```cpp
#include "myfunction.h"
#include <iostream>
using namespace std;

// No defaults in definition
void display(int value, int width, bool newline) {
    // Implementation
}
```

**main.cpp**
```cpp
#include "myfunction.h"

int main() {
    display(42);           // Uses defaults
    display(42, 5);        // Uses newline default
    display(42, 5, false); // No defaults
    
    return 0;
}
```

## Quick Reference

| Rule | Example |
|------|---------|
| Defaults from right to left | `void f(int a, int b = 10, int c = 20);` |
| Default only in declaration | In header, not in definition |
| Cannot skip parameters | Provide in order |
| Avoid overloading with defaults | Can cause ambiguity |
| const reference for temporary | `void f(const int &x = 5);` |

## When to Use Default Arguments

### ✅ Good Uses
```cpp
// Configuration parameters
void connect(string host, int port = 8080, bool secure = false);

// Optional features
void log(string message, string level = "INFO", bool timestamp = true);

// Convenience wrappers
void print(int value, int width = 1);
void print(double value, int precision = 2);

// Constructors
Student(string name = "Unknown", int age = 18);
```

### ❌ Bad Uses
```cpp
// Too many defaults (hard to understand)
void process(int a = 1, int b = 2, int c = 3, int d = 4, int e = 5);

// Defaults that don't make sense
void divide(int a, int b = 0);  // Division by zero default!

// Confusing defaults
void calculate(double tax = 0.08, bool applyDiscount = false, int quantity = 1);
```

## Summary

- **Default arguments** provide fallback values when arguments are omitted
- Must be specified from **right to left**
- Typically declared in **function prototype** (header), not definition
- Cannot **skip parameters** when calling
- Avoid overloading with default arguments (causes ambiguity)
- Useful for **optional parameters** and **configuration**
- **const references** can have defaults (temporary allowed)
- Makes functions **more flexible** with **less code**

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Function with default arguments
void displayInfo(string name, int age = 0, string city = "Unknown", bool active = true) {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "City: " << city << endl;
    cout << "Active: " << (active ? "Yes" : "No") << endl;
    cout << "---" << endl;
}

int main() {
    displayInfo("John");                      // Uses all defaults
    displayInfo("Jane", 25);                  // Uses city and active defaults
    displayInfo("Bob", 30, "New York");       // Uses active default
    displayInfo("Alice", 28, "London", false); // No defaults used
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*