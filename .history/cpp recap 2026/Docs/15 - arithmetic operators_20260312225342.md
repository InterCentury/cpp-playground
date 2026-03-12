# 15 - Arithmetic Operators in C++

## What are Arithmetic Operators?
Arithmetic operators are used to perform mathematical operations like addition, subtraction, multiplication, and division.

## The Five Basic Arithmetic Operators

| Operator | Name | Example | Result |
|----------|------|---------|--------|
| `+` | Addition | `5 + 3` | `8` |
| `-` | Subtraction | `5 - 3` | `2` |
| `*` | Multiplication | `5 * 3` | `15` |
| `/` | Division | `5 / 2` | `2` (integer) or `2.5` (float) |
| `%` | Modulus (Remainder) | `5 % 2` | `1` |

## Simple Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 3;
    
    cout << "a + b = " << a + b << endl;  // 13
    cout << "a - b = " << a - b << endl;  // 7
    cout << "a * b = " << a * b << endl;  // 30
    cout << "a / b = " << a / b << endl;  // 3 (integer division)
    cout << "a % b = " << a % b << endl;  // 1 (remainder)
    
    return 0;
}
```

## Addition (+)

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 3;
    int sum = x + y;
    
    cout << x << " + " << y << " = " << sum << endl;
    
    // Adding more than two numbers
    int total = 10 + 20 + 30 + 40;
    cout << "Total: " << total << endl;
    
    // Adding variables and literals
    int result = x + 10;
    cout << "x + 10 = " << result << endl;
    
    return 0;
}
```

## Subtraction (-)

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 4;
    int difference = a - b;
    
    cout << a << " - " << b << " = " << difference << endl;
    
    // Can result in negative numbers
    int negative = 5 - 10;
    cout << "5 - 10 = " << negative << endl;
    
    return 0;
}
```

## Multiplication (*)

```cpp
#include <iostream>
using namespace std;

int main() {
    int length = 5, width = 3;
    int area = length * width;
    
    cout << "Area: " << length << " * " << width << " = " << area << endl;
    
    // Multiplying multiple numbers
    int volume = 2 * 3 * 4;
    cout << "Volume: " << volume << endl;
    
    return 0;
}
```

## Division (/)

### Integer Division
```cpp
#include <iostream>
using namespace std;

int main() {
    // Integer division (truncates decimal part)
    cout << "15 / 4 = " << 15 / 4 << endl;      // 3 (not 3.75)
    cout << "8 / 3 = " << 8 / 3 << endl;        // 2 (not 2.666)
    cout << "10 / 5 = " << 10 / 5 << endl;      // 2
    
    return 0;
}
```

### Floating-Point Division
```cpp
#include <iostream>
using namespace std;

int main() {
    // Floating-point division
    cout << "15.0 / 4 = " << 15.0 / 4 << endl;      // 3.75
    cout << "15 / 4.0 = " << 15 / 4.0 << endl;      // 3.75
    cout << "15.0 / 4.0 = " << 15.0 / 4.0 << endl;  // 3.75
    
    // Using variables
    int a = 15, b = 4;
    float result1 = (float)a / b;    // Cast to float
    float result2 = a / (float)b;    // Cast to float
    float result3 = (float)a / (float)b;
    
    cout << "a / b = " << result1 << endl;  // 3.75
    
    return 0;
}
```

## Modulus (%)

The modulus operator gives the remainder of division.

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "10 % 3 = " << 10 % 3 << endl;   // 1 (10/3 = 3 remainder 1)
    cout << "15 % 4 = " << 15 % 4 << endl;   // 3 (15/4 = 3 remainder 3)
    cout << "8 % 2 = " << 8 % 2 << endl;     // 0 (even number)
    cout << "7 % 2 = " << 7 % 2 << endl;     // 1 (odd number)
    
    // Only works with integers
    // cout << 10.5 % 3;  // ❌ Error! % not for float/double
    
    return 0;
}
```

## Common Uses of Modulus

### Check if number is even or odd
```cpp
int num = 7;
if (num % 2 == 0) {
    cout << num << " is even" << endl;
} else {
    cout << num << " is odd" << endl;
}
```

### Extract digits
```cpp
int number = 1234;
int lastDigit = number % 10;        // 4
int remaining = number / 10;        // 123
```

### Wrap around (like clock)
```cpp
int hour = 11;
int nextHour = (hour + 1) % 12;     // 0 (12 o'clock)
```

## Operator Precedence

```cpp
#include <iostream>
using namespace std;

int main() {
    // Multiplication and division happen before addition/subtraction
    int result1 = 5 + 3 * 2;    // 5 + 6 = 11
    int result2 = (5 + 3) * 2;  // 8 * 2 = 16
    
    cout << "5 + 3 * 2 = " << result1 << endl;
    cout << "(5 + 3) * 2 = " << result2 << endl;
    
    // Division and modulus have same precedence
    int result3 = 10 - 8 / 4;    // 10 - 2 = 8
    int result4 = (10 - 8) / 4;  // 2 / 4 = 0
    
    cout << "10 - 8/4 = " << result3 << endl;
    cout << "(10 - 8)/4 = " << result4 << endl;
    
    return 0;
}
```

## Combined Examples

### Example 1: Simple Calculator
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    
    cout << "Enter two numbers: ";
    cin >> a >> b;
    
    cout << "Addition: " << a + b << endl;
    cout << "Subtraction: " << a - b << endl;
    cout << "Multiplication: " << a * b << endl;
    cout << "Division: " << (float)a / b << endl;
    cout << "Remainder: " << a % b << endl;
    
    return 0;
}
```

### Example 2: Average of Numbers
```cpp
#include <iostream>
using namespace std;

int main() {
    int num1, num2, num3, num4, num5;
    
    cout << "Enter 5 numbers: ";
    cin >> num1 >> num2 >> num3 >> num4 >> num5;
    
    int sum = num1 + num2 + num3 + num4 + num5;
    float average = (float)sum / 5;
    
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    
    return 0;
}
```

### Example 3: Area and Perimeter
```cpp
#include <iostream>
using namespace std;

int main() {
    double length, width;
    
    cout << "Enter length and width: ";
    cin >> length >> width;
    
    double area = length * width;
    double perimeter = 2 * (length + width);
    
    cout << "Area: " << area << endl;
    cout << "Perimeter: " << perimeter << endl;
    
    return 0;
}
```

### Example 4: Temperature Conversion
```cpp
#include <iostream>
using namespace std;

int main() {
    double celsius;
    
    cout << "Enter temperature in Celsius: ";
    cin >> celsius;
    
    double fahrenheit = (celsius * 9 / 5) + 32;
    
    cout << celsius << "°C = " << fahrenheit << "°F" << endl;
    
    return 0;
}
```

### Example 5: Digit Extractor
```cpp
#include <iostream>
using namespace std;

int main() {
    int number;
    
    cout << "Enter a 3-digit number: ";
    cin >> number;
    
    int hundreds = number / 100;
    int tens = (number / 10) % 10;
    int units = number % 10;
    
    cout << "Hundreds: " << hundreds << endl;
    cout << "Tens: " << tens << endl;
    cout << "Units: " << units << endl;
    
    return 0;
}
```

## Compound Assignment with Arithmetic

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    
    x += 5;   // same as x = x + 5
    cout << "x += 5: " << x << endl;  // 15
    
    x -= 3;   // same as x = x - 3
    cout << "x -= 3: " << x << endl;  // 12
    
    x *= 2;   // same as x = x * 2
    cout << "x *= 2: " << x << endl;  // 24
    
    x /= 4;   // same as x = x / 4
    cout << "x /= 4: " << x << endl;  // 6
    
    x %= 4;   // same as x = x % 4
    cout << "x %= 4: " << x << endl;  // 2
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Integer Division
```cpp
// Wrong
int a = 5, b = 2;
float result = a / b;  // result = 2.0, not 2.5!

// Correct
float result = (float)a / b;
```

### Mistake 2: Modulus with Floats
```cpp
// Wrong
float x = 10.5;
// int rem = x % 3;  // ❌ Error! % not for floats

// Correct
int a = 10, b = 3;
int rem = a % b;
```

### Mistake 3: Division by Zero
```cpp
// Wrong
int x = 5;
int y = 0;
// int result = x / y;  // ❌ Crash! Division by zero

// Correct
if (y != 0) {
    int result = x / y;
} else {
    cout << "Cannot divide by zero" << endl;
}
```

### Mistake 4: Order of Operations
```cpp
// Wrong assumption
int result = 5 + 3 * 2;  // Thinks it's 16, but it's 11

// Correct - use parentheses
int result = (5 + 3) * 2;  // 16
```

### Mistake 5: Using Single = Instead of ==
```cpp
int x = 5;
// if (x = 10) { }  // Assignment, not comparison! Always true

if (x == 10) { }  // Correct comparison
```

## Quick Reference Table

| Operator | Name | Example | Result |
|----------|------|---------|--------|
| `+` | Addition | `10 + 3` | `13` |
| `-` | Subtraction | `10 - 3` | `7` |
| `*` | Multiplication | `10 * 3` | `30` |
| `/` | Division (int) | `10 / 3` | `3` |
| `/` | Division (float) | `10.0 / 3` | `3.333...` |
| `%` | Modulus | `10 % 3` | `1` |
| `+=` | Add and assign | `x += 5` | `x = x + 5` |
| `-=` | Subtract and assign | `x -= 5` | `x = x - 5` |
| `*=` | Multiply and assign | `x *= 5` | `x = x * 5` |
| `/=` | Divide and assign | `x /= 5` | `x = x / 5` |
| `%=` | Modulus and assign | `x %= 5` | `x = x % 5` |

## Summary

- **Addition (+)** adds numbers
- **Subtraction (-)** subtracts numbers
- **Multiplication (*)** multiplies numbers
- **Division (/)** divides numbers (careful with integer division)
- **Modulus (%)** gives remainder (integers only)
- Use casting for decimal results from integer division
- Parentheses `()` control order of operations
- Compound operators (`+=`, `-=`, etc.) combine operation with assignment
- Check for division by zero
- Modulus is useful for even/odd checks and digit extraction

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    
    cout << "Enter two numbers: ";
    cin >> a >> b;
    
    // Basic arithmetic
    cout << a << " + " << b << " = " << a + b << endl;
    cout << a << " - " << b << " = " << a - b << endl;
    cout << a << " * " << b << " = " << a * b << endl;
    
    // Division with cast
    cout << a << " / " << b << " = " << (float)a / b << endl;
    
    // Modulus
    if (b != 0) {
        cout << a << " % " << b << " = " << a % b << endl;
    }
    
    return 0;
}
```
   *This documentation belongs to https://github.com/In