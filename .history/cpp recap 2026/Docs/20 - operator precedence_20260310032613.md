# 20 - Operator Precedence in C++

## What is Operator Precedence?
Operator precedence determines the order in which operators are evaluated in expressions. Operators with higher precedence are evaluated first.

## Why Precedence Matters

```cpp
#include <iostream>
using namespace std;

int main() {
    // Without understanding precedence
    int result = 5 + 3 * 2;  // 5 + (3 * 2) = 5 + 6 = 11
    cout << "5 + 3 * 2 = " << result << endl;
    
    // With parentheses (changing order)
    result = (5 + 3) * 2;  // 8 * 2 = 16
    cout << "(5 + 3) * 2 = " << result << endl;
    
    return 0;
}
```

## Precedence Table (Highest to Lowest)

| Level | Operators | Description | Associativity |
|-------|-----------|-------------|---------------|
| 1 | `::` | Scope resolution | Left to right |
| 2 | `()` `[]` `->` `.` | Postfix | Left to right |
| 3 | `++` `--` (postfix) | Postfix increment/decrement | Left to right |
| 4 | `++` `--` (prefix) `!` `+` `-` `*` `&` | Unary | Right to left |
| 5 | `*` `/` `%` | Multiplicative | Left to right |
| 6 | `+` `-` | Additive | Left to right |
| 7 | `<<` `>>` | Shift | Left to right |
| 8 | `<` `>` `<=` `>=` | Relational | Left to right |
| 9 | `==` `!=` | Equality | Left to right |
| 10 | `&` | Bitwise AND | Left to right |
| 11 | `^` | Bitwise XOR | Left to right |
| 12 | `|` | Bitwise OR | Left to right |
| 13 | `&&` | Logical AND | Left to right |
| 14 | `||` | Logical OR | Left to right |
| 15 | `?:` | Ternary | Right to left |
| 16 | `=` `+=` `-=` etc. | Assignment | Right to left |
| 17 | `,` | Comma | Left to right |

## Arithmetic Precedence

```cpp
#include <iostream>
using namespace std;

int main() {
    // Multiplication and division before addition/subtraction
    cout << "3 + 4 * 5 = " << (3 + 4 * 5) << endl;        // 3 + 20 = 23
    cout << "(3 + 4) * 5 = " << ((3 + 4) * 5) << endl;    // 7 * 5 = 35
    
    cout << "10 - 6 / 2 = " << (10 - 6 / 2) << endl;      // 10 - 3 = 7
    cout << "(10 - 6) / 2 = " << ((10 - 6) / 2) << endl;  // 4 / 2 = 2
    
    cout << "2 * 3 + 4 / 2 = " << (2 * 3 + 4 / 2) << endl; // 6 + 2 = 8
    
    return 0;
}
```

## Relational and Logical Precedence

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 10, c = 15;
    
    cout << boolalpha;
    
    // Comparisons happen before logical operators
    bool result1 = a < b && b < c;  // (a < b) && (b < c)
    cout << "a < b && b < c = " << result1 << endl;  // true
    
    // Without parentheses, it's still clear
    bool result2 = a < b || b > c && c == 15;  
    // a < b || (b > c && c == 15) = true || (false && true) = true
    
    cout << "a < b || b > c && c == 15 = " << result2 << endl;
    
    // Better with parentheses
    bool result3 = (a < b) || ((b > c) && (c == 15));
    cout << "With parentheses: " << result3 << endl;
    
    return 0;
}
```

## Assignment Precedence

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    
    // Assignment has low precedence
    a = b = c = 5;  // Works right to left: c = 5, then b = c, then a = b
    
    cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
    
    // But careful with expressions
    int x = 5;
    int y = x + (x = 3);  // Don't do this! Undefined behavior
    
    // Better:
    x = 5;
    int temp = x;
    x = 3;
    y = temp + x;
    cout << "Better approach: " << y << endl;
    
    return 0;
}
```

## Precedence with Increment/Decrement

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5;
    
    // Postfix has higher precedence than prefix
    int y = ++x * 3;  // (++x) * 3 = 6 * 3 = 18
    cout << "++x * 3 = " << y << ", x = " << x << endl;
    
    x = 5;
    y = x++ * 3;      // (x++) * 3 = 5 * 3 = 15, then x becomes 6
    cout << "x++ * 3 = " << y << ", x = " << x << endl;
    
    return 0;
}
```

## Ternary Operator Precedence

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 10;
    
    // Ternary has low precedence
    int result = x > y ? x : y + 2;  // x > y ? x : (y + 2) = false → 12
    cout << "x > y ? x : y + 2 = " << result << endl;
    
    // With parentheses for clarity
    result = (x > y) ? x : (y + 2);
    cout << "With parentheses: " << result << endl;
    
    return 0;
}
```

## Complex Examples

### Example 1: Mixed Arithmetic and Comparisons
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 3, c = 8;
    
    // Step by step evaluation
    bool result = a + b > c && c - b < a;
    // 1. a + b = 8
    // 2. 8 > c = 8 > 8 = false
    // 3. c - b = 5
    // 4. 5 < a = 5 < 5 = false
    // 5. false && false = false
    
    cout << "a + b > c && c - b < a = " << boolalpha << result << endl;
    
    // Equivalent with parentheses
    result = ((a + b) > c) && ((c - b) < a);
    cout << "With parentheses: " << result << endl;
    
    return 0;
}
```

### Example 2: Mathematical Expression
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x = 2.5;
    
    // Complex math expression
    double result = 3 * pow(x, 2) + 2 * x - 5;
    // 3 * (x^2) + (2 * x) - 5
    // = 3 * 6.25 + 5 - 5
    // = 18.75 + 5 - 5 = 18.75
    
    cout << "3x² + 2x - 5 where x = " << x << " = " << result << endl;
    
    // Quadratic formula (partial)
    double a = 1, b = -5, c = 6;
    double discriminant = b * b - 4 * a * c;
    // (b * b) - (4 * a * c) = 25 - 24 = 1
    
    cout << "Discriminant = " << discriminant << endl;
    
    return 0;
}
```

### Example 3: Logical Expression with Multiple Operators
```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 25;
    bool hasLicense = true;
    bool hasInsurance = false;
    
    // Complex condition
    bool canRent = age >= 21 && hasLicense && !hasInsurance;
    // (age >= 21) && hasLicense && (!hasInsurance)
    // true && true && true = true
    
    cout << boolalpha;
    cout << "Can rent car: " << canRent << endl;
    
    // With different precedence
    bool special = age > 18 || !hasLicense && hasInsurance;
    // age > 18 || (!hasLicense && hasInsurance)
    // true || (false && false) = true || false = true
    
    cout << "Special case: " << special << endl;
    
    return 0;
}
```

### Example 4: Bitwise vs Logical
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 3;
    
    // Bitwise AND (&) has higher precedence than logical AND (&&)
    bool result = a > b & b < a && a == 5;
    // (a > b & b < a) && (a == 5)
    // (true & true) && true = (1 & 1) && true = 1 && true = true
    
    cout << boolalpha;
    cout << "Bitwise + logical: " << result << endl;
    
    // Better with parentheses
    result = (a > b) & (b < a) && (a == 5);
    cout << "With parentheses: " << result << endl;
    
    return 0;
}
```

### Example 5: Assignment in Expression
```cpp
#include <iostream>
using namespace std;

int main() {
    int x, y, z;
    
    // Assignment has very low precedence
    x = y = z = 10;
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
    
    // But careful in conditions
    int value;
    if (value = 5) {  // Assignment, not comparison!
        cout << "This always prints, value = " << value << endl;
    }
    
    // What you probably meant:
    if (value == 5) {
        cout << "Value is 5" << endl;
    }
    
    return 0;
}
```

## Associativity

Associativity determines the order when operators have the same precedence.

```cpp
#include <iostream>
using namespace std;

int main() {
    // Left-to-right associativity (most operators)
    int a = 10 - 5 - 3;  // (10 - 5) - 3 = 5 - 3 = 2
    cout << "10 - 5 - 3 = " << a << endl;
    
    // Right-to-left associativity (assignment, unary)
    int x, y, z;
    x = y = z = 5;  // x = (y = (z = 5))
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
    
    return 0;
}
```

## Using Parentheses for Clarity

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 3, c = 8;
    
    // Hard to read
    bool result1 = a + b > c && c - b < a || a == 5;
    
    // Easy to read
    bool result2 = ((a + b) > c) && ((c - b) < a) || (a == 5);
    
    cout << boolalpha;
    cout << "Without parentheses (hard): " << result1 << endl;
    cout << "With parentheses (clear): " << result2 << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Assuming Left-to-Right Always
```cpp
int x = 5;
int y = 10;

// Wrong assumption
int result = x + y * 2;  // Thinks: (x + y) * 2 = 30
// Actually: x + (y * 2) = 5 + 20 = 25
```

### Mistake 2: Comparison Chain
```cpp
int x = 5;

// Wrong
if (1 < x < 10) {  // (1 < x) < 10 → true < 10 → 1 < 10 → true
    cout << "x is between 1 and 10" << endl;  // Always runs!
}

// Correct
if (1 < x && x < 10) {
    cout << "x is between 1 and 10" << endl;
}
```

### Mistake 3: Assignment in Condition
```cpp
int x = 5;

// Wrong - assignment instead of comparison
if (x = 10) {
    cout << "x is 10" << endl;  // Always runs, x becomes 10
}

// Correct
if (x == 10) {
    cout << "x is 10" << endl;
}
```

### Mistake 4: Mixing && and || Without Parentheses
```cpp
bool a = true, b = false, c = true;

// Unclear
bool result = a && b || c;  // (a && b) || c = false || true = true

// Clear
bool result = (a && b) || c;
```

### Mistake 5: Increment in Complex Expression
```cpp
int x = 5;
int y = ++x + x++;  // Undefined behavior! Don't do this
```

## Quick Reference Card

| Category | Operators | Precedence |
|----------|-----------|------------|
| Parentheses | `()` | Highest |
| Unary | `++` `--` `!` `+` `-` | High |
| Multiplicative | `*` `/` `%` | Medium-High |
| Additive | `+` `-` | Medium |
| Relational | `<` `>` `<=` `>=` | Medium-Low |
| Equality | `==` `!=` | Low |
| Logical AND | `&&` | Lower |
| Logical OR | `||` | Even Lower |
| Assignment | `=` `+=` `-=` etc. | Very Low |
| Comma | `,` | Lowest |

## Summary

- **Precedence** determines evaluation order
- **Associativity** determines order for same precedence
- **Multiplication/division** before addition/subtraction
- **Comparisons** before logical operators
- **Logical AND** before logical OR
- **Assignment** has very low precedence
- **Parentheses** override default precedence
- Use parentheses for complex expressions
- Don't rely on precedence for unclear code
- When in doubt, add parentheses

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 3, c = 2;
    
    // Without parentheses (relies on precedence)
    int result1 = a + b * c;
    
    // With parentheses (explicit)
    int result2 = a + (b * c);
    int result3 = (a + b) * c;
    
    cout << "a + b * c = " << result1 << endl;
    cout << "a + (b * c) = " << result2 << endl;
    cout << "(a + b) * c = " << result3 << endl;
    
    // Logical example
    bool flag = a > b && b > c || a == 5;
    cout << boolalpha;
    cout << "Complex condition: " << flag << endl;
    
    return 0;
}
```