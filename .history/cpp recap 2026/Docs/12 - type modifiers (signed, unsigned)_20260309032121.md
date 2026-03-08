# 12 - Type Modifiers (signed, unsigned) in C++

## What are Type Modifiers?
Type modifiers change how variables store data. They affect the range and whether numbers can be negative.

## The Two Main Type Modifiers

| Modifier | Meaning | Allows Negative? |
|----------|---------|------------------|
| `signed` | Can store positive and negative numbers | ✅ Yes |
| `unsigned` | Can only store positive numbers (and zero) | ❌ No |

## Basic Syntax

```cpp
signed int x = -10;     // Can be negative
unsigned int y = 10;    // Cannot be negative
signed short z = -5;    // Signed short
unsigned long w = 100;  // Unsigned long
```

## Signed vs Unsigned - Visual Comparison

```cpp
#include <iostream>
using namespace std;

int main() {
    signed int s = -10;     // Works fine
    unsigned int u = 10;    // Works fine
    
    cout << "signed: " << s << endl;       // -10
    cout << "unsigned: " << u << endl;     // 10
    
    // This would cause problems:
    // unsigned int bad = -5;  // ❌ Wraps to huge number
    
    return 0;
}
```

## Range Differences

```cpp
#include <iostream>
#include <climits>
using namespace std;

int main() {
    cout << "INT ranges:" << endl;
    cout << "signed int:   " << INT_MIN << " to " << INT_MAX << endl;
    cout << "unsigned int: 0 to " << UINT_MAX << endl << endl;
    
    cout << "SHORT ranges:" << endl;
    cout << "signed short:   " << SHRT_MIN << " to " << SHRT_MAX << endl;
    cout << "unsigned short: 0 to " << USHRT_MAX << endl << endl;
    
    cout << "LONG ranges:" << endl;
    cout << "signed long:   " << LONG_MIN << " to " << LONG_MAX << endl;
    cout << "unsigned long: 0 to " << ULONG_MAX << endl;
    
    return 0;
}
```

## Size Comparison (Same Size, Different Range)

| Type | Size | Range |
|------|------|--------|
| `signed short` | 2 bytes | -32,768 to 32,767 |
| `unsigned short` | 2 bytes | 0 to 65,535 |
| `signed int` | 4 bytes | -2.1B to 2.1B |
| `unsigned int` | 4 bytes | 0 to 4.2B |
| `signed long long` | 8 bytes | -9 quintillion to 9 quintillion |
| `unsigned long long` | 8 bytes | 0 to 18 quintillion |

## Default Behavior

```cpp
#include <iostream>
using namespace std;

int main() {
    int normal = -10;           // 'int' means 'signed int' by default
    short s = -5;               // 'short' means 'signed short'
    long l = -1000;             // 'long' means 'signed long'
    
    unsigned int u = 10;        // Must specify 'unsigned'
    
    cout << "normal: " << normal << endl;
    cout << "unsigned: " << u << endl;
    
    return 0;
}
```

## Overflow Behavior

### Signed Overflow (Undefined Behavior)
```cpp
#include <iostream>
using namespace std;

int main() {
    signed int max = INT_MAX;  // 2,147,483,647
    cout << "Max signed: " << max << endl;
    
    max = max + 1;  // Overflow - undefined behavior
    cout << "After +1: " << max << endl;  // Might be negative
    
    return 0;
}
```

### Unsigned Overflow (Wraps Around)
```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned int max = UINT_MAX;  // 4,294,967,295
    cout << "Max unsigned: " << max << endl;
    
    max = max + 1;  // Wraps to 0 (defined behavior)
    cout << "After +1: " << max << endl;  // 0
    
    unsigned int min = 0;
    min = min - 1;  // Wraps to UINT_MAX
    cout << "0 - 1: " << min << endl;  // 4,294,967,295
    
    return 0;
}
```

## Practical Examples

### Example 1: Age Storage (Never Negative)
```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned int age;  // Age can't be negative
    
    cout << "Enter your age: ";
    cin >> age;
    
    // What if user enters negative?
    // cin will still accept, but value will be huge
    cout << "Age: " << age << endl;
    
    // Better to validate
    if (age > 150) {
        cout << "Invalid age!" << endl;
    }
    
    return 0;
}
```

### Example 2: Counter (Always Positive)
```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned int count = 0;
    
    cout << "Counting up:" << endl;
    for (int i = 0; i < 5; i++) {
        count++;
        cout << count << " ";
    }
    
    cout << "\n\nCounting down with unsigned?" << endl;
    // This would cause problems:
    // for (unsigned int i = 5; i >= 0; i--) {  // Infinite loop!
    //     cout << i << " ";
    // }
    
    return 0;
}
```

### Example 3: Array Index (Never Negative)
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    
    // Good use of unsigned for index
    for (unsigned int i = 0; i < 5; i++) {
        cout << "numbers[" << i << "] = " << numbers[i] << endl;
    }
    
    return 0;
}
```

### Example 4: Bank Account Balance
```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned int balance = 1000;  // Balance can't be negative
    
    cout << "Balance: $" << balance << endl;
    
    int withdrawal;
    cout << "Enter withdrawal amount: $";
    cin >> withdrawal;
    
    // Check if enough money
    if (withdrawal <= balance) {
        balance = balance - withdrawal;
        cout << "New balance: $" << balance << endl;
    } else {
        cout << "Insufficient funds!" << endl;
    }
    
    return 0;
}
```

### Example 5: Comparing Signed and Unsigned
```cpp
#include <iostream>
using namespace std;

int main() {
    signed int s = -10;
    unsigned int u = 10;
    
    // Dangerous comparison!
    if (s < u) {
        cout << "-10 is less than 10" << endl;  // This won't print!
    } else {
        cout << "Unexpected result!" << endl;
    }
    
    // Why? -10 converts to huge unsigned number
    cout << "s as unsigned: " << (unsigned int)s << endl;
    
    return 0;
}
```

## When to Use Each

### Use `signed` when:
- Numbers can be negative (temperature, debt, coordinates)
- Doing math that might produce negatives
- Default choice for most variables

### Use `unsigned` when:
- Numbers are always positive (age, count, size)
- Need extra positive range
- Bit manipulation
- Array indices
- Representing flags or masks

## Common Use Cases

### Use Case 1: Population (Always Positive)
```cpp
unsigned int population = 7800000000;
```

### Use Case 2: Temperature (Can Be Negative)
```cpp
signed int temperature = -5;  // Below freezing
```

### Use Case 3: File Size (Always Positive)
```cpp
unsigned long long fileSize = 1099511627776;  // 1 TB
```

### Use Case 4: Score Difference (Can Be Negative)
```cpp
signed int scoreDifference = teamAScore - teamBScore;
```

## Common Mistakes

### Mistake 1: Unsigned with Negative
```cpp
// Wrong
unsigned int x = -5;  // Becomes huge number

// Correct
signed int x = -5;
```

### Mistake 2: Infinite Loop
```cpp
// Wrong - infinite loop
for (unsigned int i = 5; i >= 0; i--) {
    cout << i;  // Never ends, i wraps from 0 to UINT_MAX
}

// Correct
for (int i = 5; i >= 0; i--) {
    cout << i;
}
```

### Mistake 3: Mixed Comparison
```cpp
unsigned int u = 10;
signed int s = -5;

// Wrong - unexpected result
if (u > s) { }  // s converts to unsigned, becomes huge

// Correct - cast to signed
if ((signed int)u > s) { }
```

### Mistake 4: Forgetting Default is Signed
```cpp
// Both are signed by default
int a = -10;      // signed
short b = -5;     // signed
long c = -1000;   // signed
```

### Mistake 5: Subtraction Going Negative
```cpp
unsigned int a = 5;
unsigned int b = 10;

// Wrong - result wraps to huge number
unsigned int result = a - b;  // 5 - 10 = huge number

// Correct - use signed
signed int result = (signed int)a - (signed int)b;  // -5
```

## Best Practices

### ✅ Do This
```cpp
// Use unsigned for positive-only values
unsigned int studentCount = 25;
unsigned long fileSize = 1048576;

// Use signed when negative possible
signed int temperature = -10;
signed int balance = -50;  // Overdrawn

// Cast when mixing types
if ((signed int)u > s) { }

// Validate unsigned input
unsigned int age;
cin >> age;
if (age > 0 && age < 150) { }
```

### ❌ Avoid This
```cpp
// Don't use unsigned for loop counting down
for (unsigned int i = 10; i >= 0; i--) { }

// Don't mix signed/unsigned in comparisons
if (u > s) { }

// Don't assume unsigned won't wrap
unsigned int x = 0;
x = x - 1;  // Becomes huge

// Don't use unsigned for small ranges
unsigned short tiny = 100000;  // Still overflows
```

## Quick Reference Table

| Type | Bytes | Min | Max |
|------|-------|-----|-----|
| `signed short` | 2 | -32,768 | 32,767 |
| `unsigned short` | 2 | 0 | 65,535 |
| `signed int` | 4 | -2,147,483,648 | 2,147,483,647 |
| `unsigned int` | 4 | 0 | 4,294,967,295 |
| `signed long long` | 8 | -9.22e18 | 9.22e18 |
| `unsigned long long` | 8 | 0 | 1.84e19 |

## Summary Table

| Type | Can be Negative? | Range | Use For |
|------|------------------|-------|---------|
| `signed int` | ✅ Yes | -2.1B to 2.1B | Default, general math |
| `unsigned int` | ❌ No | 0 to 4.2B | Counts, sizes, indices |
| `signed short` | ✅ Yes | -32K to 32K | Small numbers that can be negative |
| `unsigned short` | ❌ No | 0 to 65K | Small positive numbers |
| `signed long` | ✅ Yes | Large negative/positive | Large numbers that can be negative |
| `unsigned long` | ❌ No | Very large positive | Very large positive numbers |

## Key Points to Remember

- `signed` allows negative numbers (default)
- `unsigned` only allows positive numbers and zero
- Unsigned gives double the positive range
- Mixing signed/unsigned can cause bugs
- Unsigned wraps around on overflow (defined behavior)
- Signed overflow is undefined behavior
- Use unsigned for values that are never negative
- Use signed when negative values are possible
- Be careful with loop counters (unsigned can cause infinite loops)
- Always validate unsigned input to catch negative entries

## Basic Template
```cpp
#include <iostream>
#include <climits>
using namespace std;

int main() {
    // Signed examples
    signed int temp = -10;
    signed int balance = -500;
    
    // Unsigned examples
    unsigned int age = 25;
    unsigned int count = 100;
    unsigned long fileSize = 1048576UL;
    
    // Display
    cout << "Signed values:" << endl;
    cout << "Temperature: " << temp << endl;
    cout << "Balance: " << balance << endl;
    
    cout << "\nUnsigned values:" << endl;
    cout << "Age: " << age << endl;
    cout << "Count: " << count << endl;
    cout << "File size: " << fileSize << " bytes" << endl;
    
    // Check ranges
    cout << "\nUnsigned int max: " << UINT_MAX << endl;
    cout << "Signed int max: " << INT_MAX << endl;
    cout << "Signed int min: " << INT_MIN << endl;
    
    return 0;
}
```