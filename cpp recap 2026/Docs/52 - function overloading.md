# 52 - Function Overloading in C++

## What is Function Overloading?
Function overloading allows multiple functions with the same name but different parameters (different number, types, or order of parameters). The compiler determines which function to call based on the arguments passed.

## Basic Syntax

```cpp
return_type function_name(parameters1);
return_type function_name(parameters2);
return_type function_name(parameters3);
```

## Simple Examples

```cpp
#include <iostream>
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

int main() {
    cout << add(5, 3) << endl;        // Calls int version
    cout << add(2.5, 3.7) << endl;    // Calls double version
    cout << add(1, 2, 3) << endl;     // Calls three-int version
    
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
using namespace std;

// Different parameter types
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
using namespace std;

// Different order of parameters
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
// double getValue() { return 3.14; }  // Error! Can't overload by return type only

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

## Practical Examples

### Example 1: Math Operations
```cpp
#include <iostream>
#include <cmath>
using namespace std;

double power(double base, int exponent) {
    double result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

double power(double base) {
    return base * base;  // Square
}

double power(int base) {
    return base * base;  // Square of integer
}

int main() {
    cout << "2^3 = " << power(2, 3) << endl;
    cout << "2.5 squared = " << power(2.5) << endl;
    cout << "5 squared = " << power(5) << endl;
    
    return 0;
}
```

### Example 2: Area Functions
```cpp
#include <iostream>
#include <cmath>
using namespace std;

// Circle area
double area(double radius) {
    return 3.14159 * radius * radius;
}

// Rectangle area
double area(double length, double width) {
    return length * width;
}

// Triangle area (base and height)
double area(double base, double height, bool isTriangle) {
    return 0.5 * base * height;
}

// Square area
int area(int side) {
    return side * side;
}

int main() {
    cout << "Circle (r=5): " << area(5.0) << endl;
    cout << "Rectangle (4x6): " << area(4.0, 6.0) << endl;
    cout << "Triangle (base=3, height=4): " << area(3.0, 4.0, true) << endl;
    cout << "Square (side=5): " << area(5) << endl;
    
    return 0;
}
```

### Example 3: Maximum Function
```cpp
#include <iostream>
#include <string>
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

string max(string a, string b) {
    return (a > b) ? a : b;  // Lexicographic comparison
}

int main() {
    cout << "Max of 5 and 3: " << max(5, 3) << endl;
    cout << "Max of 2.5 and 3.7: " << max(2.5, 3.7) << endl;
    cout << "Max of 1, 5, 3: " << max(1, 5, 3) << endl;
    cout << "Max of 'apple' and 'banana': " << max("apple", "banana") << endl;
    
    return 0;
}
```

### Example 4: Print Functions
```cpp
#include <iostream>
#include <vector>
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
    print("Hello");
    
    vector<int> vec = {1, 2, 3, 4, 5};
    print(vec);
    
    int arr[] = {10, 20, 30};
    print(arr, 3);
    
    return 0;
}
```

### Example 5: Date and Time Functions
```cpp
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Format time (hours, minutes)
string formatTime(int hours, int minutes) {
    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":"
       << setw(2) << minutes;
    return ss.str();
}

// Format time (hours, minutes, seconds)
string formatTime(int hours, int minutes, int seconds) {
    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":"
       << setw(2) << minutes << ":"
       << setw(2) << seconds;
    return ss.str();
}

// Format date (month, day)
string formatDate(int month, int day) {
    return to_string(month) + "/" + to_string(day);
}

// Format date (month, day, year)
string formatDate(int month, int day, int year) {
    return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
}

// Format date (day, month, year, different order)
string formatDate(int day, int month, int year, bool dayFirst) {
    if (dayFirst) {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    } else {
        return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
    }
}

int main() {
    cout << "Time (HH:MM): " << formatTime(14, 30) << endl;
    cout << "Time (HH:MM:SS): " << formatTime(14, 30, 45) << endl;
    
    cout << "Date (M/D): " << formatDate(3, 21) << endl;
    cout << "Date (M/D/Y): " << formatDate(3, 21, 2024) << endl;
    cout << "Date (D/M/Y): " << formatDate(21, 3, 2024, true) << endl;
    
    return 0;
}
```

## Overloading with Default Arguments

```cpp
#include <iostream>
using namespace std;

// Functions with default arguments
void display(int a) {
    cout << "One int: " << a << endl;
}

void display(int a, int b = 0) {
    cout << "Two ints: " << a << ", " << b << endl;
}

// Error! Ambiguous call: display(5) could call either
// To avoid ambiguity, don't overload with default arguments like this

// Better approach
void show(int a) {
    cout << "Single: " << a << endl;
}

void show(int a, int b) {
    cout << "Pair: " << a << ", " << b << endl;
}

int main() {
    show(5);       // Calls single parameter version
    show(5, 3);    // Calls two parameter version
    
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

## Overloading with Different Parameter Types

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Different container types
void sum(vector<int> vec) {
    int total = 0;
    for (int v : vec) total += v;
    cout << "Vector sum: " << total << endl;
}

void sum(int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) total += arr[i];
    cout << "Array sum: " << total << endl;
}

void sum(int a, int b) {
    cout << "Two numbers sum: " << a + b << endl;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    sum(nums);
    
    int arr[] = {10, 20, 30, 40};
    sum(arr, 4);
    
    sum(5, 3);
    
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

## Function Overloading vs Function Templates

```cpp
#include <iostream>
using namespace std;

// Overloaded functions (explicit)
int max(int a, int b) {
    cout << "max(int,int): ";
    return (a > b) ? a : b;
}

double max(double a, double b) {
    cout << "max(double,double): ";
    return (a > b) ? a : b;
}

// Function template (generic)
template <typename T>
T min(T a, T b) {
    cout << "min<T>: ";
    return (a < b) ? a : b;
}

int main() {
    cout << max(5, 3) << endl;       // Uses overloaded int version
    cout << max(2.5, 3.7) << endl;   // Uses overloaded double version
    cout << min(5, 3) << endl;       // Uses template, deduces int
    cout << min(2.5, 3.7) << endl;   // Uses template, deduces double
    
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
    // WRONG - ambiguous call
    // func(5, 3);  // Could be version 1 or 2? Both possible!
    
    // CORRECT - explicit casting
    func(static_cast<int>(5), static_cast<double>(3));
    
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
    cout << "One param" << endl;
}

void show(int a, int b) {
    cout << "Two params" << endl;
}
```

### Mistake 4: Overloading with const and Non-const (References)
```cpp
void process(int x) {
    cout << "int" << endl;
}

void process(int &x) {
    cout << "reference" << endl;
}

int main() {
    int a = 5;
    // process(a);  // Ambiguous! Both versions match
    
    process(5);    // Calls int version (temporary)
    process(a);    // Still ambiguous
    
    return 0;
}
```

### Mistake 5: Overloading with Different Order of Defaults
```cpp
// OK - different number of parameters
void print(int a) { }
void print(int a, int b) { }

// NOT OK - same number, different defaults
void display(int a, int b = 0) { }
void display(int a, int b = 1) { }  // Redefinition error
```

## When to Use Function Overloading

### ✅ Good Uses
```cpp
// Different parameter types
void print(int value);
void print(double value);
void print(string value);

// Different number of parameters
double area(double radius);           // Circle
double area(double length, double width); // Rectangle

// Different operations with same name
int max(int a, int b);
int max(int a, int b, int c);

// Constructors
Student();                    // Default constructor
Student(string name);         // Parameterized constructor
Student(string name, int age); // Another constructor
```

### ❌ Bad Uses
```cpp
// Different return types only
int getData();
double getData();  // Not allowed

// Ambiguous overloads
void process(int a, double b);
void process(double a, int b);
// process(5, 3) ambiguous

// Confusing operations
void add(int a, int b);
void add(int a, int b, int c);  // OK
void add(int a, int b, int c, int d);  // Better as separate name
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
- Improves code **readability** and **consistency**
- Common in **constructors**, **math functions**, **print functions**

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Overloaded functions
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
    cout << "int: " << add(5, 3) << endl;
    cout << "double: " << add(2.5, 3.7) << endl;
    cout << "three int: " << add(1, 2, 3) << endl;
    cout << "string: " << add("Hello", " World") << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*