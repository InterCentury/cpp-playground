# 103 - Function Overloading in C++

## What is Function Overloading?
Function overloading allows multiple functions with the same name but different parameters (different number, types, or order of parameters). The compiler determines which function to call based on the arguments passed.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Overloaded functions with same name, different parameters
int add(int a, int b) {
    cout << "int version: ";
    return a + b;
}

double add(double a, double b) {
    cout << "double version: ";
    return a + b;
}

int add(int a, int b, int c) {
    cout << "three int version: ";
    return a + b + c;
}

string add(string a, string b) {
    cout << "string version: ";
    return a + b;
}

int main() {
    cout << add(5, 3) << endl;           // int version
    cout << add(2.5, 3.7) << endl;       // double version
    cout << add(1, 2, 3) << endl;        // three int version
    cout << add("Hello", " World") << endl; // string version
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### calculator.h
```cpp
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
using namespace std;

int add(int a, int b);
double add(double a, double b);
int add(int a, int b, int c);
string add(string a, string b);

#endif
```

### calculator.cpp
```cpp
#include "calculator.h"
#include <iostream>
using namespace std;

int add(int a, int b) {
    cout << "int version: ";
    return a + b;
}

double add(double a, double b) {
    cout << "double version: ";
    return a + b;
}

int add(int a, int b, int c) {
    cout << "three int version: ";
    return a + b + c;
}

string add(string a, string b) {
    cout << "string version: ";
    return a + b;
}
```

### main.cpp
```cpp
#include <iostream>
#include "calculator.h"
using namespace std;

int main() {
    cout << add(5, 3) << endl;
    cout << add(2.5, 3.7) << endl;
    cout << add(1, 2, 3) << endl;
    cout << add("Hello", " World") << endl;
    return 0;
}
```

## Overloading by Number of Parameters

```cpp
#include <iostream>
using namespace std;

// Different number of parameters
int area(int side) {
    return side * side;  // Square
}

int area(int length, int width) {
    return length * width;  // Rectangle
}

int area(int length, int width, int height) {
    return length * width * height;  // Volume
}

int main() {
    cout << "Square area (5): " << area(5) << endl;
    cout << "Rectangle area (4, 6): " << area(4, 6) << endl;
    cout << "Box volume (2, 3, 4): " << area(2, 3, 4) << endl;
    
    return 0;
}
```

## Overloading by Parameter Types

```cpp
#include <iostream>
#include <string>
using namespace std;

void display(int value) {
    cout << "Integer: " << value << endl;
}

void display(double value) {
    cout << "Double: " << value << endl;
}

void display(string value) {
    cout << "String: " << value << endl;
}

void display(char value) {
    cout << "Character: " << value << endl;
}

int main() {
    display(42);
    display(3.14);
    display("Hello");
    display('A');
    
    return 0;
}
```

## Overloading by Order of Parameters

```cpp
#include <iostream>
#include <string>
using namespace std;

void print(string name, int age) {
    cout << "Name: " << name << ", Age: " << age << endl;
}

void print(int age, string name) {
    cout << "Age: " << age << ", Name: " << name << endl;
}

int main() {
    print("John", 25);
    print(30, "Alice");
    
    return 0;
}
```

## Overloading with Different Return Types (Not Allowed Alone)

```cpp
#include <iostream>
using namespace std;

// Overloading by return type alone is NOT allowed
// int getValue() { return 42; }
// double getValue() { return 3.14; }  // Error!

// Must have different parameters
int getValue(int x) {
    return x;
}

double getValue(double x) {
    return x;
}

int main() {
    cout << getValue(5) << endl;
    cout << getValue(3.14) << endl;
    
    return 0;
}
```

## Overloading with const and References

```cpp
#include <iostream>
using namespace std;

// Overloading by const
void process(int &x) {
    cout << "Non-const reference: " << x << endl;
    x = 100;
}

void process(const int &x) {
    cout << "Const reference: " << x << endl;
}

// Overloading by pointer vs reference
void work(int *ptr) {
    cout << "Pointer: " << *ptr << endl;
}

void work(int &ref) {
    cout << "Reference: " << ref << endl;
}

int main() {
    int a = 5;
    const int b = 10;
    
    process(a);  // Calls non-const version
    process(b);  // Calls const version
    
    work(&a);    // Calls pointer version
    work(a);     // Calls reference version
    
    return 0;
}
```

## Overloading in Classes

```cpp
#include <iostream>
#include <string>
using namespace std;

class Calculator {
public:
    // Overloaded member functions
    int add(int a, int b) {
        return a + b;
    }
    
    double add(double a, double b) {
        return a + b;
    }
    
    int add(int a, int b, int c) {
        return a + b + c;
    }
    
    string add(string a, string b) {
        return a + b;
    }
};

int main() {
    Calculator calc;
    
    cout << "int: " << calc.add(5, 3) << endl;
    cout << "double: " << calc.add(2.5, 3.7) << endl;
    cout << "three int: " << calc.add(1, 2, 3) << endl;
    cout << "string: " << calc.add("Hello", " World") << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Math Operations Library

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

// Max functions
int max(int a, int b) {
    return (a > b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

int max(int a, int b, int c) {
    return max(max(a, b), c);
}

// Min functions
int min(int a, int b) {
    return (a < b) ? a : b;
}

double min(double a, double b) {
    return (a < b) ? a : b;
}

// Power functions
double power(double base, int exponent) {
    double result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

double power(int base, int exponent) {
    return power((double)base, exponent);
}

double power(double base) {
    return base * base;  // Square
}

// Absolute functions
int abs(int x) {
    return (x < 0) ? -x : x;
}

double abs(double x) {
    return (x < 0) ? -x : x;
}

int main() {
    cout << "Max of 5 and 3: " << max(5, 3) << endl;
    cout << "Max of 2.5 and 3.7: " << max(2.5, 3.7) << endl;
    cout << "Max of 1, 5, 3: " << max(1, 5, 3) << endl;
    
    cout << "Min of 5 and 3: " << min(5, 3) << endl;
    cout << "Min of 2.5 and 3.7: " << min(2.5, 3.7) << endl;
    
    cout << "2^5 = " << power(2, 5) << endl;
    cout << "2.5^3 = " << power(2.5, 3) << endl;
    cout << "5 squared = " << power(5.0) << endl;
    
    cout << "Abs of -5: " << abs(-5) << endl;
    cout << "Abs of -3.14: " << abs(-3.14) << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**mathutils.h**
```cpp
#ifndef MATHUTILS_H
#define MATHUTILS_H

int max(int a, int b);
double max(double a, double b);
int max(int a, int b, int c);

int min(int a, int b);
double min(double a, double b);

double power(double base, int exponent);
double power(int base, int exponent);
double power(double base);

int abs(int x);
double abs(double x);

#endif
```

**mathutils.cpp**
```cpp
#include "mathutils.h"
#include <cmath>
using namespace std;

int max(int a, int b) {
    return (a > b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

int max(int a, int b, int c) {
    return max(max(a, b), c);
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

double min(double a, double b) {
    return (a < b) ? a : b;
}

double power(double base, int exponent) {
    double result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

double power(int base, int exponent) {
    return power((double)base, exponent);
}

double power(double base) {
    return base * base;
}

int abs(int x) {
    return (x < 0) ? -x : x;
}

double abs(double x) {
    return (x < 0) ? -x : x;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "mathutils.h"
using namespace std;

int main() {
    cout << max(5, 3) << endl;
    cout << max(2.5, 3.7) << endl;
    cout << power(2, 5) << endl;
    cout << abs(-5) << endl;
    return 0;
}
```

### Example 2: Print Functions Overloading

#### Type 1: Single File
```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void print(int value) {
    cout << "Integer: " << value << endl;
}

void print(double value) {
    cout << "Double: " << value << endl;
}

void print(const string& value) {
    cout << "String: " << value << endl;
}

void print(const vector<int>& vec) {
    cout << "Vector: [";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void print(int arr[], int size) {
    cout << "Array: [";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    print(42);
    print(3.14);
    print("Hello World");
    
    vector<int> vec = {1, 2, 3, 4, 5};
    print(vec);
    
    int arr[] = {10, 20, 30, 40};
    print(arr, 4);
    
    return 0;
}
```

#### Type 2: Multiple Files

**printer.h**
```cpp
#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <vector>
using namespace std;

void print(int value);
void print(double value);
void print(const string& value);
void print(const vector<int>& vec);
void print(int arr[], int size);

#endif
```

**printer.cpp**
```cpp
#include "printer.h"
#include <iostream>
using namespace std;

void print(int value) {
    cout << "Integer: " << value << endl;
}

void print(double value) {
    cout << "Double: " << value << endl;
}

void print(const string& value) {
    cout << "String: " << value << endl;
}

void print(const vector<int>& vec) {
    cout << "Vector: [";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void print(int arr[], int size) {
    cout << "Array: [";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "printer.h"
using namespace std;

int main() {
    print(42);
    print(3.14);
    print("Hello");
    
    int arr[] = {1, 2, 3};
    print(arr, 3);
    
    return 0;
}
```

### Example 3: Area Calculation Overloading

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

// Circle area
double area(double radius) {
    return M_PI * radius * radius;
}

// Rectangle area
double area(double length, double width) {
    return length * width;
}

// Triangle area (base and height)
double area(double base, double height, bool isTriangle) {
    return 0.5 * base * height;
}

// Triangle area (three sides)
double area(double a, double b, double c) {
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// Square area
int area(int side) {
    return side * side;
}

int main() {
    cout << "Circle (r=5): " << area(5.0) << endl;
    cout << "Rectangle (4x6): " << area(4.0, 6.0) << endl;
    cout << "Triangle (base=3, height=4): " << area(3.0, 4.0, true) << endl;
    cout << "Triangle (sides=3,4,5): " << area(3.0, 4.0, 5.0) << endl;
    cout << "Square (side=5): " << area(5) << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**area.h**
```cpp
#ifndef AREA_H
#define AREA_H

double area(double radius);
double area(double length, double width);
double area(double base, double height, bool isTriangle);
double area(double a, double b, double c);
int area(int side);

#endif
```

**area.cpp**
```cpp
#include "area.h"
#include <cmath>
using namespace std;

double area(double radius) {
    return M_PI * radius * radius;
}

double area(double length, double width) {
    return length * width;
}

double area(double base, double height, bool isTriangle) {
    return 0.5 * base * height;
}

double area(double a, double b, double c) {
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

int area(int side) {
    return side * side;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "area.h"
using namespace std;

int main() {
    cout << area(5.0) << endl;
    cout << area(4.0, 6.0) << endl;
    cout << area(5) << endl;
    return 0;
}
```

## Overloading vs Default Arguments

```cpp
#include <iostream>
using namespace std;

// Using default arguments (simpler)
void greet(string name, string greeting = "Hello") {
    cout << greeting << ", " << name << "!" << endl;
}

// Without default arguments (would need multiple overloads)
void greet(string name) {
    greet(name, "Hello");
}

int main() {
    greet("John");        // Uses default
    greet("Jane", "Hi");  // Uses provided
    
    return 0;
}
```

## Function Overloading Resolution

```cpp
#include <iostream>
using namespace std;

void func(int) {
    cout << "int version" << endl;
}

void func(double) {
    cout << "double version" << endl;
}

void func(char) {
    cout << "char version" << endl;
}

void func(int, double) {
    cout << "int, double version" << endl;
}

int main() {
    func(5);        // int version
    func(3.14);     // double version
    func('A');      // char version (char converts to int? No, exact match)
    func(5, 3.14);  // int, double version
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Overloading by Return Type Only
```cpp
// WRONG - can't overload by return type only
// int getValue() { return 42; }
// double getValue() { return 3.14; }  // Error!

// CORRECT - different parameters
int getValue(int x) { return x; }
double getValue(double x) { return x; }
```

### Mistake 2: Ambiguous Overloads
```cpp
void func(int a, double b) {
    cout << "Version 1" << endl;
}

void func(double a, int b) {
    cout << "Version 2" << endl;
}

int main() {
    // func(5, 3);  // Ambiguous! Could be version 1 or 2
    func(5, 3.0);   // OK - version 1
    func(5.0, 3);   // OK - version 2
    
    return 0;
}
```

### Mistake 3: Overloading with Default Arguments
```cpp
// WRONG - ambiguous
void show(int a) {
    cout << "One param" << endl;
}

void show(int a, int b = 0) {
    cout << "Two params (default)" << endl;
}

// show(5);  // Ambiguous! Which one to call?

// CORRECT - avoid such combinations
void show(int a) {
    cout << a << endl;
}

void show(int a, int b) {
    cout << a << ", " << b << endl;
}
```

## Quick Reference

| Overload Criteria | Example |
|-------------------|---------|
| Number of parameters | `func(int a)` vs `func(int a, int b)` |
| Parameter types | `func(int a)` vs `func(double a)` |
| Order of parameters | `func(int a, double b)` vs `func(double a, int b)` |
| const vs non-const | `func(int &a)` vs `func(const int &a)` |
| Reference vs pointer | `func(int &a)` vs `func(int *a)` |

## Summary

- **Function overloading** allows multiple functions with same name
- Must differ in **number**, **types**, or **order** of parameters
- Cannot overload by **return type only**
- **Default arguments** can create ambiguity
- Compiler resolves based on **best match**
- Use for **similar operations** on different data types
- Common in **constructors**, **math functions**, **print functions**

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

string add(string a, string b) {
    return a + b;
}

int main() {
    cout << add(5, 3) << endl;
    cout << add(2.5, 3.7) << endl;
    cout << add(1, 2, 3) << endl;
    cout << add("Hello", " World") << endl;
    return 0;
}
```

### Type 2: Multiple Files

**overload.h**
```cpp
#ifndef OVERLOAD_H
#define OVERLOAD_H

#include <string>
using namespace std;

int add(int a, int b);
double add(double a, double b);
int add(int a, int b, int c);
string add(string a, string b);

#endif
```

**overload.cpp**
```cpp
#include "overload.h"
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

string add(string a, string b) {
    return a + b;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "overload.h"
using namespace std;

int main() {
    cout << add(5, 3) << endl;
    cout << add("Hello", " World") << endl;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*