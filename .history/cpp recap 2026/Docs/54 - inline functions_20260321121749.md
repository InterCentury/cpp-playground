# 54 - inline Functions in C++

## What are inline Functions?
Inline functions are a request to the compiler to replace the function call with the actual code of the function at compile time. This can improve performance by eliminating function call overhead for small, frequently used functions.

## Basic Syntax

```cpp
inline return_type function_name(parameters) {
    // function body
}
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

// Inline function
inline int square(int x) {
    return x * x;
}

int main() {
    int result = square(5);  // Compiler may replace with: int result = 5 * 5;
    cout << "Square: " << result << endl;
    
    return 0;
}
```

## How Inline Works

```cpp
#include <iostream>
using namespace std;

// Regular function (not inline)
int addRegular(int a, int b) {
    return a + b;
}

// Inline function
inline int addInline(int a, int b) {
    return a + b;
}

int main() {
    int x = 5, y = 3;
    
    // Regular function call - actual function call overhead
    int result1 = addRegular(x, y);
    
    // Inline function - code may be inserted directly
    int result2 = addInline(x, y);  // Possibly replaced with: int result2 = x + y;
    
    cout << "Regular: " << result1 << endl;
    cout << "Inline: " << result2 << endl;
    
    return 0;
}
```

## When to Use Inline Functions

### ✅ Good Candidates for Inline
```cpp
#include <iostream>
using namespace std;

// Simple getter/setter
inline int getValue() {
    return value;
}

// Simple arithmetic operations
inline int max(int a, int b) {
    return (a > b) ? a : b;
}

// Simple math functions
inline double square(double x) {
    return x * x;
}

// One-line operations
inline bool isEven(int n) {
    return n % 2 == 0;
}
```

### ❌ Poor Candidates for Inline
```cpp
// Complex functions (too large)
inline void complexFunction() {
    // Many lines of code - not good for inline
    for (int i = 0; i < 100; i++) {
        // Complex logic
    }
    // More code...
}

// Recursive functions
inline int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);  // Recursion can't be inlined
}

// Functions with loops (usually too large)
inline void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}
```

## Inline Functions in Classes

### Member Functions Defined Inside Class (Implicitly Inline)
```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double length, width;
    
public:
    // Member functions defined inside class are implicitly inline
    Rectangle(double l, double w) : length(l), width(w) {}
    
    double getLength() { return length; }        // Implicitly inline
    double getWidth() { return width; }          // Implicitly inline
    double area() { return length * width; }     // Implicitly inline
};

int main() {
    Rectangle rect(5, 3);
    cout << "Area: " << rect.area() << endl;
    
    return 0;
}
```

### Member Functions Defined Outside with inline
```cpp
#include <iostream>
using namespace std;

class Circle {
private:
    double radius;
    
public:
    Circle(double r);
    double getRadius();
    double area();
    double circumference();
};

// Constructor defined outside with inline
inline Circle::Circle(double r) : radius(r) {}

// Member function defined outside with inline
inline double Circle::getRadius() {
    return radius;
}

inline double Circle::area() {
    return 3.14159 * radius * radius;
}

inline double Circle::circumference() {
    return 2 * 3.14159 * radius;
}

int main() {
    Circle c(5);
    cout << "Area: " << c.area() << endl;
    cout << "Circumference: " << c.circumference() << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Math Utility Functions
```cpp
#include <iostream>
#include <cmath>
using namespace std;

inline int add(int a, int b) { return a + b; }
inline int subtract(int a, int b) { return a - b; }
inline int multiply(int a, int b) { return a * b; }
inline double divide(double a, double b) { return (b != 0) ? a / b : 0; }

inline int min(int a, int b) { return (a < b) ? a : b; }
inline int max(int a, int b) { return (a > b) ? a : b; }
inline int abs(int x) { return (x < 0) ? -x : x; }
inline double square(double x) { return x * x; }
inline double cube(double x) { return x * x * x; }

int main() {
    cout << "Add: " << add(5, 3) << endl;
    cout << "Subtract: " << subtract(10, 4) << endl;
    cout << "Multiply: " << multiply(6, 7) << endl;
    cout << "Divide: " << divide(15, 3) << endl;
    cout << "Min: " << min(5, 8) << endl;
    cout << "Max: " << max(5, 8) << endl;
    cout << "Absolute: " << abs(-7) << endl;
    cout << "Square: " << square(4) << endl;
    cout << "Cube: " << cube(3) << endl;
    
    return 0;
}
```

### Example 2: Temperature Conversion
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

inline double celsiusToFahrenheit(double c) {
    return (c * 9.0 / 5.0) + 32;
}

inline double fahrenheitToCelsius(double f) {
    return (f - 32) * 5.0 / 9.0;
}

inline double celsiusToKelvin(double c) {
    return c + 273.15;
}

inline double kelvinToCelsius(double k) {
    return k - 273.15;
}

int main() {
    cout << fixed << setprecision(2);
    
    cout << "25°C to Fahrenheit: " << celsiusToFahrenheit(25) << "°F" << endl;
    cout << "77°F to Celsius: " << fahrenheitToCelsius(77) << "°C" << endl;
    cout << "0°C to Kelvin: " << celsiusToKelvin(0) << "K" << endl;
    cout << "300K to Celsius: " << kelvinToCelsius(300) << "°C" << endl;
    
    return 0;
}
```

### Example 3: Validation Functions
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

inline bool isPositive(int n) {
    return n > 0;
}

inline bool isEven(int n) {
    return n % 2 == 0;
}

inline bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

inline bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

inline bool isValidAge(int age) {
    return age >= 0 && age <= 150;
}

int main() {
    cout << boolalpha;
    
    cout << "5 is positive? " << isPositive(5) << endl;
    cout << "6 is even? " << isEven(6) << endl;
    cout << "2024 is leap year? " << isLeapYear(2024) << endl;
    cout << "'a' is vowel? " << isVowel('a') << endl;
    cout << "Age 25 valid? " << isValidAge(25) << endl;
    cout << "Age 200 valid? " << isValidAge(200) << endl;
    
    return 0;
}
```

### Example 4: Simple Geometry Functions
```cpp
#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159;

inline double circleArea(double radius) {
    return PI * radius * radius;
}

inline double circleCircumference(double radius) {
    return 2 * PI * radius;
}

inline double rectangleArea(double length, double width) {
    return length * width;
}

inline double rectanglePerimeter(double length, double width) {
    return 2 * (length + width);
}

inline double triangleArea(double base, double height) {
    return 0.5 * base * height;
}

inline double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
    cout << "Circle (r=5): area=" << circleArea(5) 
         << ", circumference=" << circleCircumference(5) << endl;
    
    cout << "Rectangle (4x6): area=" << rectangleArea(4, 6) 
         << ", perimeter=" << rectanglePerimeter(4, 6) << endl;
    
    cout << "Triangle (base=3, height=4): area=" << triangleArea(3, 4) << endl;
    
    cout << "Distance between (0,0) and (3,4): " << distance(0, 0, 3, 4) << endl;
    
    return 0;
}
```

### Example 5: String Helper Functions
```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

inline char toUpper(char c) {
    return toupper(c);
}

inline char toLower(char c) {
    return tolower(c);
}

inline bool isAlpha(char c) {
    return isalpha(c);
}

inline bool isDigit(char c) {
    return isdigit(c);
}

inline bool isAlnum(char c) {
    return isalnum(c);
}

inline bool isSpace(char c) {
    return isspace(c);
}

inline string toUpperString(string s) {
    for (char &c : s) c = toupper(c);
    return s;
}

inline string toLowerString(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

int main() {
    char ch = 'a';
    cout << "toUpper('a'): " << toUpper(ch) << endl;
    cout << "toLower('A'): " << toLower('A') << endl;
    cout << "isAlpha('5'): " << boolalpha << isAlpha('5') << endl;
    cout << "isDigit('5'): " << isDigit('5') << endl;
    
    string text = "Hello World";
    cout << "toUpperString: " << toUpperString(text) << endl;
    cout << "toLowerString: " << toLowerString(text) << endl;
    
    return 0;
}
```

## Inline with constexpr (C++11)

```cpp
#include <iostream>
using namespace std;

// constexpr implies inline
constexpr int square(int x) {
    return x * x;
}

constexpr int cube(int x) {
    return x * x * x;
}

constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main() {
    // Evaluated at compile time
    constexpr int sq = square(5);      // 25
    constexpr int cu = cube(3);        // 27
    constexpr int fact = factorial(5); // 120
    
    cout << "Square: " << sq << endl;
    cout << "Cube: " << cu << endl;
    cout << "Factorial: " << fact << endl;
    
    return 0;
}
```

## Inline vs Regular Function Performance

```cpp
#include <iostream>
#include <chrono>
using namespace std;

// Regular function
int addRegular(int a, int b) {
    return a + b;
}

// Inline function
inline int addInline(int a, int b) {
    return a + b;
}

int main() {
    const int ITERATIONS = 100000000;
    
    // Test regular function
    auto start = chrono::high_resolution_clock::now();
    int sum = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        sum += addRegular(i, i + 1);
    }
    auto end = chrono::high_resolution_clock::now();
    auto regularTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    // Test inline function
    start = chrono::high_resolution_clock::now();
    sum = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        sum += addInline(i, i + 1);
    }
    end = chrono::high_resolution_clock::now();
    auto inlineTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Regular function time: " << regularTime.count() << " ms" << endl;
    cout << "Inline function time: " << inlineTime.count() << " ms" << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Assuming Inline Always Happens
```cpp
// inline is just a request, compiler may ignore it
inline void complexFunction() {
    // Very large function - compiler will likely ignore inline
    for (int i = 0; i < 10000; i++) {
        // Complex operations
    }
}

// Compiler decides based on function size, complexity
```

### Mistake 2: Inline in Header Without Definition
```cpp
// WRONG - inline function declared but not defined
// inline void func();  // Just declaration

// CORRECT - inline function defined in header
inline void func() {
    // definition
}
```

### Mistake 3: Inline Recursive Functions
```cpp
// WRONG - recursion can't be inlined
inline int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);  // Compiler will ignore inline
}

// Better - use regular function
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

### Mistake 4: Inline Large Functions
```cpp
// WRONG - too large to be beneficial
inline void printAll() {
    cout << "Line 1" << endl;
    cout << "Line 2" << endl;
    // ... 100 more lines
    cout << "Line 100" << endl;
}

// Better - use regular function
void printAll() {
    // 100 lines of code
}
```

### Mistake 5: Inline with Virtual Functions
```cpp
class Base {
public:
    // virtual functions are rarely inlined (runtime dispatch)
    inline virtual void display() {  // inline may be ignored
        cout << "Base" << endl;
    }
};
```

## When to Use Inline

### ✅ Good Uses
```cpp
// Simple getters/setters
inline int getValue() const { return value; }

// Simple arithmetic
inline int add(int a, int b) { return a + b; }

// One-liner conditions
inline bool isPositive(int n) { return n > 0; }

// Constant expressions
constexpr int square(int x) { return x * x; }
```

### ❌ Poor Uses
```cpp
// Complex functions
inline void complexProcess() {
    // Many lines, loops, function calls
}

// Recursive functions
inline int factorial(int n) { return n <= 1 ? 1 : n * factorial(n - 1); }

// Functions with loops
inline void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i];
}

// Virtual functions
inline virtual void draw() const { }
```

## Quick Reference

| Aspect | inline | Regular |
|--------|--------|---------|
| Keyword | `inline` | None |
| Call overhead | Reduced/eliminated | Function call overhead |
| Code size | May increase (code duplication) | Smaller |
| Compiler control | Suggestion only | Must generate function |
| Recursion | Not supported | Supported |
| Header files | Can be defined in header | Usually declared in header, defined in cpp |

## Summary

- **inline** is a request, not a command
- Reduces **function call overhead** for small functions
- Best for **simple, frequently used** functions
- **Getters/setters**, **arithmetic operations**, **simple conditions**
- Cannot inline **recursive** or **very large** functions
- **constexpr** implies inline (C++11)
- Member functions defined inside class are implicitly inline
- Use in **headers** for small utility functions
- Compiler decides whether to actually inline
- May **increase code size** if overused

## Basic Template
```cpp
#include <iostream>
using namespace std;

// Inline utility functions
inline int square(int x) {
    return x * x;
}

inline bool isEven(int n) {
    return n % 2 == 0;
}

inline double celsiusToFahrenheit(double c) {
    return (c * 9.0 / 5.0) + 32;
}

int main() {
    cout << "Square of 5: " << square(5) << endl;
    cout << "Is 6 even? " << boolalpha << isEven(6) << endl;
    cout << "25°C to °F: " << celsiusToFahrenheit(25) << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*