# 09 - Floating-Point Types (float, double) in C++

## What are Floating-Point Numbers?
Floating-point numbers are numbers with decimal points. Examples: 3.14, -0.5, 99.99, 2.0, 0.33333

## The Two Main Floating-Point Types

| Type | Size | Precision | Decimal Digits | When to Use |
|------|------|-----------|----------------|-------------|
| `float` | 4 bytes | ~7 digits | 6-7 | Memory saving, less precision needed |
| `double` | 8 bytes | ~15 digits | 15-16 | Default choice for decimals |

## Simple Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    float price = 19.99f;        // Note: 'f' suffix for float
    double pi = 3.14159265358979; // No suffix needed
    
    cout << "Price: $" << price << endl;
    cout << "Pi: " << pi << endl;
    
    return 0;
}
```

## Memory Size Comparison

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Size in bytes:" << endl;
    cout << "float: " << sizeof(float) << " bytes" << endl;
    cout << "double: " << sizeof(double) << " bytes" << endl;
    
    return 0;
}
```
Output:
```
Size in bytes:
float: 4 bytes
double: 8 bytes
```

## Precision Demonstration

```cpp
#include <iostream>
#include <iomanip>  // for setprecision
using namespace std;

int main() {
    float f = 1.0f / 3.0f;
    double d = 1.0 / 3.0;
    
    cout << "float precision (10 digits): " << setprecision(10) << f << endl;
    cout << "double precision (10 digits): " << setprecision(10) << d << endl;
    cout << "double precision (15 digits): " << setprecision(15) << d << endl;
    
    return 0;
}
```
Output (approximate):
```
float precision (10 digits): 0.3333333433
double precision (10 digits): 0.3333333333
double precision (15 digits): 0.333333333333333
```

## Declaring Floating-Point Variables

### Different Ways to Declare

```cpp
// float declarations
float a = 3.14f;        // with 'f' suffix
float b = 3.14F;        // 'F' also works
float c = 3.14;         // warning: double to float conversion
float d = {};           // zero initialization (0.0f)

// double declarations
double x = 3.14159;     // normal way
double y = 2.5e-3;      // scientific notation (0.0025)
double z = {};          // zero initialization (0.0)
```

### Multiple Variables
```cpp
float temp1 = 98.6f, temp2 = 100.2f, temp3 = 97.5f;
double length = 15.75, width = 8.5, height = 3.2;
```

## Scientific Notation (E Notation)

```cpp
#include <iostream>
using namespace std;

int main() {
    double avogadro = 6.022e23;      // 6.022 × 10²³
    double electron = 1.602e-19;     // 1.602 × 10⁻¹⁹
    double speedOfLight = 3e8;       // 3 × 10⁸ (300,000,000)
    double small = 1e-6;              // 0.000001 (1 micro)
    
    cout << "Avogadro's number: " << avogadro << endl;
    cout << "Electron charge: " << electron << endl;
    cout << "Speed of light: " << speedOfLight << endl;
    cout << "One micron: " << small << endl;
    
    return 0;
}
```

## Common Operations

```cpp
#include <iostream>
#include <cmath>  // for math functions
using namespace std;

int main() {
    double a = 10.5, b = 3.2;
    
    // Basic arithmetic
    cout << "a + b = " << a + b << endl;     // 13.7
    cout << "a - b = " << a - b << endl;     // 7.3
    cout << "a * b = " << a * b << endl;     // 33.6
    cout << "a / b = " << a / b << endl;     // 3.28125
    
    // Math functions
    cout << "sqrt(25) = " << sqrt(25) << endl;           // 5
    cout << "pow(2, 3) = " << pow(2, 3) << endl;         // 8
    cout << "abs(-5.7) = " << abs(-5.7) << endl;         // 5.7
    cout << "round(3.6) = " << round(3.6) << endl;       // 4
    cout << "ceil(3.2) = " << ceil(3.2) << endl;         // 4
    cout << "floor(3.8) = " << floor(3.8) << endl;       // 3
    
    return 0;
}
```

## Float vs Double - When to Use Each

### Use float when:
- Memory is limited (games, embedded systems)
- Precision isn't critical
- Working with graphics (OpenGL, DirectX)
- Storing large arrays of decimals

### Use double when:
- Need high precision (scientific calculations)
- Default choice for general use
- Financial calculations
- Most C++ math functions return double

## Practical Examples

### Example 1: Temperature Converter
```cpp
#include <iostream>
using namespace std;

int main() {
    double celsius, fahrenheit;
    
    cout << "Enter temperature in Celsius: ";
    cin >> celsius;
    
    fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
    
    cout << celsius << "°C = " << fahrenheit << "°F" << endl;
    
    return 0;
}
```

### Example 2: Circle Calculator
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double PI = 3.14159265358979;
    double radius;
    
    cout << "Enter circle radius: ";
    cin >> radius;
    
    double area = PI * radius * radius;
    double circumference = 2 * PI * radius;
    
    cout << "Area: " << area << endl;
    cout << "Circumference: " << circumference << endl;
    
    return 0;
}
```

### Example 3: Average Calculator
```cpp
#include <iostream>
using namespace std;

int main() {
    double score1, score2, score3, score4, score5;
    
    cout << "Enter 5 test scores: ";
    cin >> score1 >> score2 >> score3 >> score4 >> score5;
    
    double total = score1 + score2 + score3 + score4 + score5;
    double average = total / 5.0;
    
    cout << "Total: " << total << endl;
    cout << "Average: " << average << endl;
    
    return 0;
}
```

### Example 4: Compound Interest
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double principal = 1000.0;
    double rate = 0.05;  // 5%
    int years = 10;
    
    double amount = principal * pow(1 + rate, years);
    
    cout << "Initial: $" << principal << endl;
    cout << "After " << years << " years: $" << amount << endl;
    
    return 0;
}
```

## Precision and Formatting

```cpp
#include <iostream>
#include <iomanip>  // for formatting
using namespace std;

int main() {
    double pi = 3.14159265358979;
    
    cout << "Default: " << pi << endl;
    cout << fixed << "Fixed: " << pi << endl;
    cout << setprecision(2) << "2 decimals: " << pi << endl;
    cout << setprecision(5) << "5 decimals: " << pi << endl;
    cout << scientific << "Scientific: " << pi << endl;
    
    return 0;
}
```
Output:
```
Default: 3.14159
Fixed: 3.141593
2 decimals: 3.14
5 decimals: 3.14159
Scientific: 3.14159e+00
```

## Common Floating-Point Issues

### Issue 1: Precision Loss
```cpp
float f = 0.1f + 0.2f;
cout << "0.1 + 0.2 = " << f << endl;  // Might be 0.300000004
```

### Issue 2: Comparing Floats
```cpp
// Wrong way
float a = 0.1f + 0.2f;
if (a == 0.3f) {  // May not be true!
    cout << "Equal";
}

// Correct way
float epsilon = 0.00001f;
if (abs(a - 0.3f) < epsilon) {
    cout << "Approximately equal";
}
```

### Issue 3: Division by Zero
```cpp
float x = 5.0f;
float y = 0.0f;

float result = x / y;  // Infinity or error
cout << result << endl;  // Prints "inf" or "nan"
```

### Issue 4: Accumulating Errors
```cpp
float sum = 0.0f;
for (int i = 0; i < 1000000; i++) {
    sum += 0.000001f;  // Small errors add up
}
cout << "Expected: 1.0, Got: " << sum << endl;
```

## Special Floating-Point Values

```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    double infinity = 1.0 / 0.0;
    double negInfinity = -1.0 / 0.0;
    double nan = 0.0 / 0.0;
    double max = numeric_limits<double>::max();
    
    cout << "Infinity: " << infinity << endl;
    cout << "NaN: " << nan << endl;
    cout << "Max double: " << max << endl;
    
    return 0;
}
```

## Quick Reference Table

| Operation | float | double |
|-----------|-------|--------|
| Declaration | `float x = 3.14f;` | `double x = 3.14;` |
| Suffix | `f` or `F` | none |
| Size | 4 bytes | 8 bytes |
| Precision | ~7 digits | ~15 digits |
| Range | 1.2e-38 to 3.4e38 | 2.2e-308 to 1.8e308 |
| Zero | `0.0f` | `0.0` |

## Common Mistakes

### Mistake 1: Forgetting 'f' Suffix
```cpp
// Wrong - double assigned to float (warning)
float x = 3.14;

// Correct
float x = 3.14f;
```

### Mistake 2: Integer Division
```cpp
// Wrong - integer division first
float result = 1 / 3;    // result = 0.0

// Correct
float result = 1.0f / 3.0f;  // result = 0.333
```

### Mistake 3: Direct Equality Comparison
```cpp
// Wrong
if (x == 0.1) { }

// Correct
if (abs(x - 0.1) < 0.00001) { }
```

### Mistake 4: Using float for Money
```cpp
// Wrong - float can lose cents
float balance = 0.0f;
balance += 0.1f;  // Might be 0.100000004

// Better - use double or special decimal types
double balance = 0.0;
```

### Mistake 5: Uninitialized Variables
```cpp
// Wrong
float x;
cout << x;  // Garbage value

// Correct
float x = 0.0f;
```

## Best Practices

### ✅ Do This
```cpp
// Use double by default
double price = 19.99;

// Use float only when needed
float textureCoord = 0.5f;  // Graphics

// Use epsilon for comparisons
const double EPSILON = 1e-10;
if (abs(a - b) < EPSILON) { }

// Format output nicely
cout << fixed << setprecision(2) << price;

// Use scientific for very large/small
double lightYears = 9.461e15;
```

### ❌ Avoid This
```cpp
// Don't compare directly
if (x == 0.1) { }

// Don't mix types without casting
float result = 1 / 3;  // integer division

// Don't use float for precise calculations
float accountBalance = 0.0f;  // Money needs precision

// Don't ignore compiler warnings
float x = 3.14;  // Warning!
```

## Summary

- **float** - 4 bytes, ~7 digits precision, use 'f' suffix
- **double** - 8 bytes, ~15 digits precision, default choice
- Use scientific notation (e notation) for very large/small numbers
- Never compare floats directly with ==
- Use epsilon for float comparisons
- Be careful with precision loss in calculations
- Double is preferred for most applications
- Float is for memory-critical situations
- Include `<cmath>` for math functions
- Use `<iomanip>` and `setprecision()` for formatting
- Watch out for integer division when working with floats

## Basic Template
```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    // Declare variables
    float f = 3.14f;
    double d = 3.1415926535;
    
    // Input
    double radius;
    cout << "Enter radius: ";
    cin >> radius;
    
    // Calculations
    double area = M_PI * radius * radius;
    double circumference = 2 * M_PI * radius;
    
    // Output with formatting
    cout << fixed << setprecision(2);
    cout << "Area: " << area << endl;
    cout << "Circumference: " << circumference << endl;
    
    return 0;
}
```