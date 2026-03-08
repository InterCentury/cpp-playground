# 08 - Integer Types (int, short, long, long long) in C++

## What are Integers?
Integers are whole numbers (no decimal points). Examples: -5, 0, 42, 1000, -999

## Why Different Integer Types?
Different integer types use different amounts of memory and can store different ranges of numbers.

## The Four Main Integer Types

| Type | Size (typical) | Range | When to Use |
|------|---------------|--------|-------------|
| `short` | 2 bytes | -32,768 to 32,767 | Small numbers, saving memory |
| `int` | 4 bytes | -2.1 billion to 2.1 billion | Default choice for integers |
| `long` | 4 or 8 bytes* | At least -2.1 billion to 2.1 billion | When need larger range |
| `long long` | 8 bytes | -9 quintillion to 9 quintillion | Very large numbers |

*Size depends on system/compiler

## Simple Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    short small = 100;
    int normal = 1000;
    long large = 100000;
    long long veryLarge = 1000000000;
    
    cout << "short: " << small << endl;
    cout << "int: " << normal << endl;
    cout << "long: " << large << endl;
    cout << "long long: " << veryLarge << endl;
    
    return 0;
}
```

## Memory Size Demonstration

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Size in bytes:" << endl;
    cout << "short: " << sizeof(short) << " bytes" << endl;
    cout << "int: " << sizeof(int) << " bytes" << endl;
    cout << "long: " << sizeof(long) << " bytes" << endl;
    cout << "long long: " << sizeof(long long) << " bytes" << endl;
    
    return 0;
}
```
Output (typical):
```
Size in bytes:
short: 2 bytes
int: 4 bytes
long: 4 bytes
long long: 8 bytes
```

## Range Demonstration

```cpp
#include <iostream>
#include <climits>  // For integer limits
using namespace std;

int main() {
    cout << "short ranges:" << endl;
    cout << "Min: " << SHRT_MIN << endl;
    cout << "Max: " << SHRT_MAX << endl << endl;
    
    cout << "int ranges:" << endl;
    cout << "Min: " << INT_MIN << endl;
    cout << "Max: " << INT_MAX << endl << endl;
    
    cout << "long long ranges:" << endl;
    cout << "Min: " << LLONG_MIN << endl;
    cout << "Max: " << LLONG_MAX << endl;
    
    return 0;
}
```

## When to Use Each Type

### short - For Small Numbers
```cpp
short temperature = -5;      // Temperature in Celsius
short year = 2024;           // Year
short age = 25;              // Person's age
short score = 95;            // Test score
```

### int - Default Choice (Most Common)
```cpp
int population = 50000;      // City population
int distance = 1500;         // Distance in meters
int count = 1000;            // Item count
int salary = 50000;          // Annual salary
```

### long - For Larger Numbers
```cpp
long worldPopulation = 7800000000;     // World population
long distance = 384400000;              // Earth to moon (meters)
long fileSize = 5000000000;             // File size in bytes
```

### long long - For Very Large Numbers
```cpp
long long starsInGalaxy = 100000000000;  // Stars in Milky Way
long long nationalDebt = 31000000000000; // US debt in dollars
long long bytesInTB = 1099511627776;     // 1 TB in bytes
```

## Overflow Example (What happens when too big)

```cpp
#include <iostream>
using namespace std;

int main() {
    short small = 32767;  // Max short value
    cout << "small: " << small << endl;
    
    small = small + 1;     // Overflow!
    cout << "small + 1: " << small << endl;
    
    small = small + 1;     // Overflow again!
    cout << "small + 2: " << small << endl;
    
    return 0;
}
```
Output:
```
small: 32767
small + 1: -32768
small + 2: -32767
```

## Unsigned Integers (Only Positive)

```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned short positive = 65535;  // Max for unsigned short
    // unsigned short negative = -5;  // ❌ Error or weird value
    
    unsigned int count = 4000000000;   // Can store bigger positives
    unsigned long long big = 18000000000000000000;
    
    cout << "Positive: " << positive << endl;
    cout << "Count: " << count << endl;
    
    return 0;
}
```

| Type | Size | Range (Unsigned) |
|------|------|-------------------|
| `unsigned short` | 2 bytes | 0 to 65,535 |
| `unsigned int` | 4 bytes | 0 to 4.2 billion |
| `unsigned long long` | 8 bytes | 0 to 18 quintillion |

## Practical Examples

### Example 1: Age Calculator
```cpp
#include <iostream>
using namespace std;

int main() {
    short birthYear = 2000;
    short currentYear = 2024;
    short age = currentYear - birthYear;
    
    cout << "Born: " << birthYear << endl;
    cout << "Age: " << age << " years" << endl;
    
    return 0;
}
```

### Example 2: Bank Balance
```cpp
#include <iostream>
using namespace std;

int main() {
    int balance = 5000;
    int deposit = 1500;
    int withdrawal = 2000;
    
    balance = balance + deposit;
    cout << "After deposit: $" << balance << endl;
    
    balance = balance - withdrawal;
    cout << "After withdrawal: $" << balance << endl;
    
    return 0;
}
```

### Example 3: Large Number Multiplication
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 50000;
    int b = 50000;
    long long result = (long long)a * b;  // Cast to avoid overflow
    
    cout << a << " × " << b << " = " << result << endl;
    
    // Wrong way - overflow
    int wrong = a * b;
    cout << "Wrong result: " << wrong << endl;
    
    return 0;
}
```

### Example 4: Counter Program
```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned int count = 0;
    
    cout << "Counting to 5:" << endl;
    count = count + 1;
    cout << "Count: " << count << endl;
    
    count = count + 1;
    cout << "Count: " << count << endl;
    
    count = count + 1;
    cout << "Count: " << count << endl;
    
    return 0;
}
```

## Integer Literals

```cpp
#include <iostream>
using namespace std;

int main() {
    // Decimal (base 10) - normal
    int decimal = 42;
    
    // Hexadecimal (base 16) - starts with 0x
    int hex = 0x2A;        // 42 in decimal
    
    // Octal (base 8) - starts with 0
    int octal = 052;       // 42 in decimal
    
    // Binary (base 2) - C++14 onwards
    int binary = 0b101010; // 42 in decimal
    
    // With suffixes
    long large = 100000L;
    long long veryLarge = 100000LL;
    unsigned int positive = 100U;
    
    cout << "Decimal: " << decimal << endl;
    cout << "Hex: " << hex << endl;
    cout << "Octal: " << octal << endl;
    cout << "Binary: " << binary << endl;
    
    return 0;
}
```

## Integer Suffixes

| Suffix | Meaning | Example |
|--------|---------|---------|
| `U` or `u` | Unsigned | `100U` |
| `L` or `l` | Long | `100000L` |
| `LL` or `ll` | Long long | `1000000000LL` |
| `UL` | Unsigned long | `100UL` |
| `ULL` | Unsigned long long | `100ULL` |

## Common Operations with Integers

```cpp
int a = 10, b = 3;

cout << "Addition: " << a + b << endl;        // 13
cout << "Subtraction: " << a - b << endl;     // 7
cout << "Multiplication: " << a * b << endl;  // 30
cout << "Division: " << a / b << endl;        // 3 (truncated)
cout << "Modulus: " << a % b << endl;         // 1 (remainder)
```

## Integer Division Quirk

```cpp
int x = 5;
int y = 2;
int result = x / y;      // result = 2 (not 2.5!)

// Fix with casting
float correct = (float)x / y;  // correct = 2.5
```

## Choosing the Right Type - Guidelines

| If you need to store | Use |
|---------------------|-----|
| Person's age (0-150) | `short` or `int` |
| Test score (0-100) | `short` |
| Year (1900-2100) | `short` |
| Population of a city | `int` |
| Distance in meters | `int` or `long` |
| File size in bytes | `long long` |
| Count of items (< 1000) | `short` |
| Never negative numbers | `unsigned` version |

## Quick Reference Table

```cpp
// Declaration examples
short s = 100;
int i = 1000;
long l = 100000L;
long long ll = 1000000000LL;

// Unsigned versions
unsigned short us = 50000;
unsigned int ui = 4000000000U;
unsigned long long ull = 10000000000000ULL;

// Size in bytes
sizeof(short);      // usually 2
sizeof(int);        // usually 4
sizeof(long);       // usually 4 or 8
sizeof(long long);  // usually 8
```

## Common Mistakes

### Mistake 1: Overflow
```cpp
// Wrong
short x = 100000;     // Too big for short

// Correct
int x = 100000;
```

### Mistake 2: Unsigned with Negative
```cpp
// Wrong
unsigned int x = -5;  // Will wrap to huge number

// Correct
int x = -5;
```

### Mistake 3: Division Truncation
```cpp
// Wrong thinking
int a = 7, b = 2;
float result = a / b;  // result = 3.0, not 3.5!

// Correct
float result = (float)a / b;  // result = 3.5
```

### Mistake 4: Wrong Suffix
```cpp
// May cause warning
long x = 10000000000;  // Too big for int

// Correct
long x = 10000000000L;
long long y = 10000000000LL;
```

### Mistake 5: Mixing Signed and Unsigned
```cpp
unsigned int u = 10;
int s = -5;

if (u > s) {  // Problem! s converts to unsigned
    // This might not work as expected
}
```

## Best Practices

### ✅ Do This
```cpp
// Use int for most cases
int score = 95;

// Use short when memory matters
short age = 25;

// Use long long for huge numbers
long long galaxyStars = 100000000000LL;

// Use unsigned for non-negative
unsigned int count = 0;

// Cast when doing division
float result = (float)x / y;
```

### ❌ Avoid This
```cpp
// Don't guess sizes
int x = 1000000000000;  // Might overflow

// Don't mix signed/unsigned carelessly
unsigned int a = 10;
int b = -5;
if (a > b) { }  // Unexpected behavior

// Don't forget suffixes
long big = 1234567890123;  // Might be int
```

## Summary

- **short** - 2 bytes, small numbers (-32K to 32K)
- **int** - 4 bytes, default choice (-2.1B to 2.1B)
- **long** - 4-8 bytes, larger numbers
- **long long** - 8 bytes, very large numbers
- **unsigned** versions for only positive numbers
- Use `<climits>` to see exact ranges
- Be careful with overflow
- Division truncates with integers
- Use suffixes for large literals
- Choose based on number size needed
- `sizeof()` shows bytes used

## Basic Template
```cpp
#include <iostream>
#include <climits>
using namespace std;

int main() {
    // Different integer types
    short small = 100;
    int normal = 10000;
    long large = 1000000L;
    long long veryLarge = 10000000000LL;
    
    // Unsigned versions
    unsigned short positive = 50000;
    
    // Display values
    cout << "short: " << small << endl;
    cout << "int: " << normal << endl;
    cout << "long: " << large << endl;
    cout << "long long: " << veryLarge << endl;
    
    // Size information
    cout << "\nSizes in bytes:" << endl;
    cout << "short: " << sizeof(short) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "long: " << sizeof(long) << endl;
    cout << "long long: " << sizeof(long long) << endl;
    
    return 0;
}
```