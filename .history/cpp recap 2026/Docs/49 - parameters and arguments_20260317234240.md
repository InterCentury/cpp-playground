# 49 - Parameters and Arguments in C++

## What are Parameters and Arguments?
- **Parameters** are variables listed in the function definition that receive values
- **Arguments** are the actual values passed to the function when calling it

## Basic Terminology

```cpp
#include <iostream>
using namespace std;

// Parameters: a and b (defined in function)
int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 5, y = 3;
    
    // Arguments: x and y (passed to function)
    int result = add(x, y);
    
    cout << "Result: " << result << endl;
    return 0;
}
```

## Parameter vs Argument - Visual Comparison

```cpp
#include <iostream>
using namespace std;

// FUNCTION DEFINITION
// Parameters: name, age, height
void displayPerson(string name, int age, double height) {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << endl;
}

int main() {
    string studentName = "John";
    int studentAge = 25;
    double studentHeight = 1.75;
    
    // FUNCTION CALL
    // Arguments: studentName, studentAge, studentHeight
    displayPerson(studentName, studentAge, studentHeight);
    
    // Arguments can be literals too
    displayPerson("Alice", 30, 1.65);
    
    return 0;
}
```

## Types of Parameters

### 1. Value Parameters (Pass by Value)
```cpp
#include <iostream>
using namespace std;

// Value parameter - receives a COPY
void increment(int x) {
    x++;  // Modifies only the local copy
    cout << "Inside function: x = " << x << endl;
}

int main() {
    int num = 5;
    cout << "Before call: num = " << num << endl;
    
    increment(num);  // Passes a copy
    
    cout << "After call: num = " << num << endl;  // Still 5
    
    return 0;
}
```

### 2. Reference Parameters (Pass by Reference)
```cpp
#include <iostream>
using namespace std;

// Reference parameter - receives a REFERENCE to original
void increment(int &x) {
    x++;  // Modifies the original variable
    cout << "Inside function: x = " << x << endl;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int num = 5;
    cout << "Before call: num = " << num << endl;
    
    increment(num);  // Passes reference
    
    cout << "After call: num = " << num << endl;  // Now 6
    
    int x = 10, y = 20;
    cout << "\nBefore swap: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    return 0;
}
```

### 3. const Reference Parameters
```cpp
#include <iostream>
#include <string>
using namespace std;

// const reference - efficient and safe (cannot modify)
void printMessage(const string &msg) {
    cout << msg << endl;
    // msg += "!";  // ERROR! Cannot modify const reference
}

double calculateTotal(const double &price, int quantity) {
    // price = 10.0;  // ERROR! Cannot modify
    return price * quantity;  // Can read
}

int main() {
    string text = "Hello World";
    printMessage(text);  // No copy, efficient
    
    double total = calculateTotal(19.99, 3);
    cout << "Total: $" << total << endl;
    
    return 0;
}
```

### 4. Array Parameters
```cpp
#include <iostream>
using namespace std;

// Array parameter - actually receives pointer
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void modifyArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Modifies original array
    }
}

// const array parameter - read-only
int sumArray(const int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];  // Can read, can't modify
    }
    return total;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Original: ";
    printArray(numbers, size);
    
    cout << "Sum: " << sumArray(numbers, size) << endl;
    
    modifyArray(numbers, size);
    cout << "After modify: ";
    printArray(numbers, size);
    
    return 0;
}
```

### 5. Default Parameters
```cpp
#include <iostream>
using namespace std;

// Parameters with default values
void display(string item, int count = 1, bool showPrice = false) {
    cout << count << " " << item;
    if (count > 1) cout << "s";
    if (showPrice) cout << " - $1.99 each";
    cout << endl;
}

int calculate(int a, int b = 1, int c = 1) {
    return a * b * c;
}

int main() {
    // Arguments can be omitted for default parameters
    display("apple");                    // Uses both defaults
    display("banana", 3);                // Uses showPrice default
    display("orange", 2, true);          // No defaults used
    
    cout << calculate(5) << endl;        // 5 * 1 * 1 = 5
    cout << calculate(5, 2) << endl;     // 5 * 2 * 1 = 10
    cout << calculate(5, 2, 3) << endl;  // 5 * 2 * 3 = 30
    
    return 0;
}
```

## Types of Arguments

### 1. Literal Arguments
```cpp
#include <iostream>
using namespace std;

void printValues(int a, double b, string c) {
    cout << "int: " << a << ", double: " << b << ", string: " << c << endl;
}

int main() {
    // Passing literal values directly
    printValues(10, 3.14, "Hello");
    
    return 0;
}
```

### 2. Variable Arguments
```cpp
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 5, y = 3;
    int z = 10;
    
    // Passing variables
    int result1 = add(x, y);
    cout << x << " + " << y << " = " << result1 << endl;
    
    // Passing expressions
    int result2 = add(x * 2, y + z);
    cout << "10 + 13 = " << result2 << endl;
    
    return 0;
}
```

### 3. Expression Arguments
```cpp
#include <iostream>
using namespace std;

int square(int x) {
    return x * x;
}

int main() {
    // Passing expressions
    cout << square(5 + 3) << endl;           // square(8) = 64
    cout << square(square(2)) << endl;       // square(4) = 16
    cout << square(10) + square(5) << endl;  // 100 + 25 = 125
    
    return 0;
}
```

### 4. Function Call as Argument
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    // Using function calls as arguments
    int result = add(multiply(2, 3), multiply(4, 5));
    // add(6, 20) = 26
    
    cout << "Result: " << result << endl;
    
    // Nested function calls
    double val = sqrt(abs(-25));  // abs(-25)=25, sqrt(25)=5
    cout << "sqrt(abs(-25)) = " << val << endl;
    
    return 0;
}
```

## Parameter Passing Examples

### Example 1: Multiple Parameters
```cpp
#include <iostream>
#include <string>
using namespace std;

// Function with multiple parameters
void createProfile(string name, int age, double height, bool isStudent) {
    cout << "\n--- Profile ---" << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << "m" << endl;
    cout << "Student: " << (isStudent ? "Yes" : "No") << endl;
}

int main() {
    // Arguments must match order
    createProfile("John", 25, 1.75, true);
    createProfile("Alice", 30, 1.65, false);
    
    return 0;
}
```

### Example 2: Mixing Parameter Types
```cpp
#include <iostream>
using namespace std;

// Mix of value and reference parameters
void processNumbers(int a, int &b, const int &c) {
    a = a * 2;     // Modifies local copy only
    b = b * 2;     // Modifies original
    // c = c * 2;  // ERROR! Can't modify const reference
    
    cout << "Inside - a: " << a << ", b: " << b << ", c: " << c << endl;
}

int main() {
    int x = 5, y = 5, z = 5;
    
    cout << "Before - x: " << x << ", y: " << y << ", z: " << z << endl;
    
    processNumbers(x, y, z);
    
    cout << "After - x: " << x << ", y: " << y << ", z: " << z << endl;
    // x unchanged (value), y changed (reference), z unchanged (const reference)
    
    return 0;
}
```

### Example 3: Array and Size Parameters
```cpp
#include <iostream>
using namespace std;

// Array parameter needs size parameter
double calculateAverage(const int scores[], int size) {
    if (size == 0) return 0;
    
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return static_cast<double>(sum) / size;
}

void addBonus(int scores[], int size, int bonus) {
    for (int i = 0; i < size; i++) {
        scores[i] += bonus;
    }
}

int main() {
    int grades[] = {85, 90, 78, 92, 88};
    int numStudents = sizeof(grades) / sizeof(grades[0]);
    
    cout << "Average: " << calculateAverage(grades, numStudents) << endl;
    
    addBonus(grades, numStudents, 5);
    cout << "After bonus: " << calculateAverage(grades, numStudents) << endl;
    
    return 0;
}
```

### Example 4: Default Parameters in Different Positions
```cpp
#include <iostream>
using namespace std;

// Correct - defaults from right to left
void func1(int a, int b = 10);           // OK
void func2(int a, int b = 10, int c = 20); // OK
// void func3(int a = 5, int b, int c = 20); // ERROR! Can't have non-default after default

void display(int a, int b = 5, int c = 10) {
    cout << "a=" << a << ", b=" << b << ", c=" << c << endl;
}

int main() {
    display(1);           // a=1, b=5, c=10
    display(1, 2);        // a=1, b=2, c=10
    display(1, 2, 3);     // a=1, b=2, c=3
    
    return 0;
}
```

### Example 5: String Parameters
```cpp
#include <iostream>
#include <string>
using namespace std;

// Different ways to pass strings
void byValue(string s) {
    s += "!";  // Modifies local copy
    cout << "Inside byValue: " << s << endl;
}

void byReference(string &s) {
    s += "!";  // Modifies original
    cout << "Inside byReference: " << s << endl;
}

void byConstReference(const string &s) {
    // s += "!";  // ERROR! Can't modify
    cout << "Inside byConstReference: " << s << endl;
}

int main() {
    string text = "Hello";
    
    cout << "Original: " << text << endl;
    
    byValue(text);
    cout << "After byValue: " << text << endl;  // Unchanged
    
    byReference(text);
    cout << "After byReference: " << text << endl;  // Changed
    
    byConstReference(text);
    
    return 0;
}
```

## Parameter Matching and Type Conversion

### Implicit Type Conversion
```cpp
#include <iostream>
using namespace std;

void display(double x) {
    cout << "double: " << x << endl;
}

void display(int x) {
    cout << "int: " << x << endl;
}

int main() {
    // Implicit conversions
    display(5);        // Calls int version
    display(5.0);      // Calls double version
    display(5.0f);     // float converts to double
    display('A');      // char converts to int (65)
    
    return 0;
}
```

### Function Overloading Resolution
```cpp
#include <iostream>
using namespace std;

void print(int i) {
    cout << "Integer: " << i << endl;
}

void print(double d) {
    cout << "Double: " << d << endl;
}

void print(string s) {
    cout << "String: " << s << endl;
}

void print(int i, string s) {
    cout << "Integer and String: " << i << ", " << s << endl;
}

int main() {
    print(10);           // Calls int version
    print(3.14);         // Calls double version
    print("Hello");      // Calls string version (const char* converts to string)
    print(42, "Answer"); // Calls two-parameter version
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Wrong Number of Arguments
```cpp
int add(int a, int b) {
    return a + b;
}

int main() {
    // WRONG - too few arguments
    // int result = add(5);  // Error!
    
    // WRONG - too many arguments
    // int result = add(5, 3, 2);  // Error!
    
    // CORRECT
    int result = add(5, 3);
    
    return 0;
}
```

### Mistake 2: Wrong Argument Order
```cpp
void printPerson(string name, int age) {
    cout << name << " is " << age << " years old" << endl;
}

int main() {
    string n = "John";
    int a = 25;
    
    // WRONG - argument order reversed
    // printPerson(a, n);  // Error or wrong output
    
    // CORRECT
    printPerson(n, a);
    
    return 0;
}
```

### Mistake 3: Type Mismatch
```cpp
void process(int x) {
    cout << "Processing: " << x << endl;
}

int main() {
    // WRONG - type mismatch (but may compile with warning)
    process(3.14);  // Truncated to 3
    
    // CORRECT
    process(static_cast<int>(3.14));  // Explicit conversion
    
    return 0;
}
```

### Mistake 4: Modifying const Reference
```cpp
void display(const string &s) {
    // WRONG - trying to modify const reference
    // s += "!";  // Error!
    
    // CORRECT
    cout << s << endl;
}
```

### Mistake 5: Forgetting & for Reference Parameters
```cpp
void increment(int x) {  // Forgot & - now it's pass by value
    x++;
}

int main() {
    int num = 5;
    increment(num);
    cout << num << endl;  // Still 5! Not what we wanted
    
    return 0;
}
```

## Parameter Passing Summary

| Parameter Type | Syntax | Modifies Original? | Efficiency | Use Case |
|----------------|--------|-------------------|------------|----------|
| Value | `void f(int x)` | No | Copy cost | Small types, don't need modification |
| Reference | `void f(int &x)` | Yes | No copy | Need to modify, large objects |
| const Reference | `void f(const int &x)` | No | No copy | Large objects, read-only |
| Array | `void f(int arr[])` | Yes (usually) | No copy | Arrays (decays to pointer) |
| Default | `void f(int x = 0)` | Depends | Depends | Optional parameters |

## Quick Reference

| Term | Definition | Example |
|------|------------|---------|
| Parameter | Variable in function definition | `int add(int a, int b)` |
| Argument | Value passed in function call | `add(5, 3)` |
| Pass by Value | Receives copy | `void f(int x)` |
| Pass by Reference | Receives reference to original | `void f(int &x)` |
| const Reference | Read-only reference | `void f(const int &x)` |
| Default Parameter | Has default value | `void f(int x = 0)` |

## Summary

- **Parameters** are defined in functions, **arguments** are passed in calls
- **Pass by value** creates a copy (safe but potentially expensive)
- **Pass by reference** shares the original (efficient but can modify)
- **const reference** is efficient and safe (read-only)
- **Default parameters** allow optional arguments
- Arguments must match parameters in **number, order, and type**
- Arrays are always passed by reference (actually pointer)
- Function overloading resolves based on argument types
- Implicit conversions may occur if no exact match

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Function with various parameter types
void demonstrateParameters(
    int byValue,           // Pass by value
    int &byReference,      // Pass by reference
    const int &byConstRef, // Pass by const reference
    string text,           // String by value
    int arr[],             // Array parameter
    int size,              // Size for array
    int defaultValue = 10  // Default parameter
) {
    byValue *= 2;           // Modifies local copy only
    byReference *= 2;       // Modifies original
    // byConstRef *= 2;     // ERROR! Can't modify const
    
    cout << "byValue (local): " << byValue << endl;
    cout << "byReference: " << byReference << endl;
    cout << "byConstRef: " << byConstRef << endl;
    cout << "text: " << text << endl;
    
    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    cout << "Default value: " << defaultValue << endl;
}

int main() {
    int x = 5, y = 5, z = 5;
    string msg = "Hello";
    int nums[] = {1, 2, 3, 4, 5};
    int size = sizeof(nums) / sizeof(nums[0]);
    
    demonstrateParameters(x, y, z, msg, nums, size);
    
    cout << "\nAfter call:" << endl;
    cout << "x (by value): " << x << endl;      // Unchanged
    cout << "y (by ref): " << y << endl;        // Changed
    cout << "z (const ref): " << z << endl;     // Unchanged
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*