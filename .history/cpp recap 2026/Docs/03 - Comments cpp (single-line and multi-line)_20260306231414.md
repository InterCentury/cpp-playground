# 03 - Comments in C++ (Single-Line and Multi-Line)

## What are Comments?
Comments are notes in your code that the computer ignores. They're only for humans to read.

## Two Types of Comments

### 1. Single-Line Comments `//`
```cpp
// This is a single-line comment

cout << "Hello"; // Comment after code

// cout << "This won't run"; // Disabled code
```

### 2. Multi-Line Comments `/* */`
```cpp
/* This is a
   multi-line
   comment */

cout << "World"; /* Comment here too */
```

## Why Use Comments?

```cpp
// 1. Explain your code
int age = 18;  // User's age

// 2. Leave reminders
// TODO: Fix this later
// FIXME: This doesn't work

// 3. Disable code temporarily
// cout << "Debug message";

// 4. Organize sections
// ===== INPUT SECTION =====
// ===== OUTPUT SECTION =====
```

## Quick Examples

### Program with Comments
```cpp
#include <iostream>
using namespace std;

int main() {
    // Get user's age
    int age;
    cout << "Enter age: ";
    cin >> age;
    
    /* Check if adult
       18 or older = adult
       under 18 = minor */
    if (age >= 18) {
        cout << "Adult";
    } else {
        cout << "Minor";
    }
    
    return 0;
}
```

## Common Uses

| Use | Example |
|-----|---------|
| Explain variable | `int count; // Number of students` |
| TODO reminder | `// TODO: Add error handling` |
| Disable code | `// cout << "Debug";` |
| Section header | `// ===== MAIN LOOP =====` |

## Don't Do This

```cpp
// Bad - states obvious
int x = 5;  // Set x to 5

// Bad - outdated comment
int total = a + b;  // This multiplies (WRONG!)

// Bad - too much
/* This loop goes through each student... (long novel) */
```

## Quick Reference

| Type | Syntax | Example |
|------|--------|---------|
| Single-line | `// text` | `// Hello` |
| Multi-line | `/* text */` | `/* Hi there */` |

## Summary
- `//` for single line
- `/* */` for multiple lines
- Comments explain WHY, not WHAT
- Keep comments short and updated