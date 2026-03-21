# 62 - Scope Rules (Local vs Global) in C++

## What is Scope?
Scope defines where a variable can be accessed within a program. It determines the visibility and lifetime of variables. Understanding scope is crucial for writing bug-free code and avoiding naming conflicts.

## Basic Scope Types

```cpp
#include <iostream>
using namespace std;

int globalVar = 100;  // Global variable - accessible everywhere

int main() {
    int localVar = 50;  // Local variable - accessible only in main
    
    cout << "Global: " << globalVar << endl;  // ✅ Accessible
    cout << "Local: " << localVar << endl;    // ✅ Accessible
    
    return 0;
}
```

## Global Variables

Global variables are declared outside any function and are accessible throughout the entire program.

```cpp
#include <iostream>
using namespace std;

// Global variables
int globalCounter = 0;
string globalMessage = "Hello";
const double PI = 3.14159;

void incrementCounter() {
    globalCounter++;  // ✅ Can access and modify global
}

void displayMessage() {
    cout << globalMessage << endl;  // ✅ Can access global
}

int main() {
    cout << "Initial counter: " << globalCounter << endl;
    incrementCounter();
    incrementCounter();
    cout << "After increments: " << globalCounter << endl;
    
    cout << "PI: " << PI << endl;
    
    return 0;
}
```

## Local Variables

Local variables are declared inside a function or block and are only accessible within that scope.

```cpp
#include <iostream>
using namespace std;

void functionA() {
    int localA = 10;  // Local to functionA
    cout << "In functionA: " << localA << endl;
    // cout << localB;  // ❌ Error - localB not in scope
}

void functionB() {
    int localB = 20;  // Local to functionB
    cout << "In functionB: " << localB << endl;
    // cout << localA;  // ❌ Error - localA not in scope
}

int main() {
    int localMain = 30;  // Local to main
    cout << "In main: " << localMain << endl;
    
    functionA();
    functionB();
    
    // cout << localA;  // ❌ Error - not in scope
    // cout << localB;  // ❌ Error - not in scope
    
    return 0;
}
```

## Block Scope

Variables declared inside a block (within `{}`) are only accessible within that block.

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    
    {  // Start of inner block
        int y = 20;  // y exists only in this block
        cout << "Inside block: x = " << x << endl;  // ✅ Can access outer
        cout << "Inside block: y = " << y << endl;  // ✅ Accessible
    }  // End of inner block - y is destroyed
    
    cout << "Outside block: x = " << x << endl;  // ✅ Still accessible
    // cout << y;  // ❌ Error - y out of scope
    
    return 0;
}
```

## Variable Shadowing

When a local variable has the same name as a global variable, the local variable "shadows" the global one within its scope.

```cpp
#include <iostream>
using namespace std;

int value = 100;  // Global variable

void function() {
    int value = 50;  // Local variable shadows global
    cout << "Inside function - local value: " << value << endl;
}

int main() {
    int value = 25;  // Local variable shadows global
    cout << "In main - local value: " << value << endl;
    
    function();
    
    cout << "Global value: " << ::value << endl;  // Access global with ::
    
    return 0;
}
```

## Accessing Global Variable When Shadowed

```cpp
#include <iostream>
using namespace std;

int score = 100;  // Global variable

int main() {
    int score = 50;  // Local shadows global
    
    cout << "Local score: " << score << endl;
    cout << "Global score: " << ::score << endl;  // :: accesses global
    
    // Modify global using ::
    ::score = 200;
    cout << "Modified global: " << ::score << endl;
    
    return 0;
}
```

## Scope in Loops

```cpp
#include <iostream>
using namespace std;

int main() {
    // Variable declared outside loop - accessible after loop
    int i;
    for (i = 0; i < 5; i++) {
        cout << i << " ";
    }
    cout << "\nAfter loop: i = " << i << endl;
    
    // Variable declared in loop header - only accessible in loop
    for (int j = 0; j < 5; j++) {
        cout << j << " ";
    }
    // cout << j;  // ❌ Error - j not in scope after loop
    
    return 0;
}
```

## Scope in if Statements

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    
    if (x > 5) {
        int y = 20;  // y exists only in this block
        cout << "Inside if: x = " << x << ", y = " << y << endl;
    }
    
    cout << "Outside if: x = " << x << endl;
    // cout << y;  // ❌ Error - y out of scope
    
    return 0;
}
```

## Scope in switch Statements

```cpp
#include <iostream>
using namespace std;

int main() {
    int choice = 2;
    
    switch (choice) {
        case 1: {
            int x = 10;
            cout << "Case 1: " << x << endl;
            break;
        }
        case 2: {
            int x = 20;  // Different scope - OK
            cout << "Case 2: " << x << endl;
            break;
        }
    }
    
    return 0;
}
```

## Function Parameter Scope

```cpp
#include <iostream>
using namespace std;

void process(int param) {  // param is local to this function
    cout << "Parameter: " << param << endl;
    // param can be modified inside function
    param = 100;
    cout << "Modified parameter: " << param << endl;
}

int main() {
    int value = 50;
    process(value);
    cout << "Original value: " << value << endl;  // Still 50
    
    return 0;
}
```

## Practical Examples

### Example 1: Counter Using Global
```cpp
#include <iostream>
using namespace std;

// Global counter
int functionCallCount = 0;

void myFunction() {
    functionCallCount++;  // Increment global counter
    cout << "Function called " << functionCallCount << " times" << endl;
}

int main() {
    myFunction();
    myFunction();
    myFunction();
    
    cout << "Total calls: " << functionCallCount << endl;
    
    return 0;
}
```

### Example 2: Local vs Global Preference
```cpp
#include <iostream>
using namespace std;

int data = 100;  // Global

void display() {
    int data = 50;  // Local shadows global
    cout << "Inside display - data: " << data << endl;
    cout << "Inside display - global data: " << ::data << endl;
}

int main() {
    int data = 25;  // Local shadows global
    cout << "In main - data: " << data << endl;
    cout << "In main - global data: " << ::data << endl;
    
    display();
    
    return 0;
}
```

### Example 3: Nested Scopes
```cpp
#include <iostream>
using namespace std;

int level = 1;  // Global

int main() {
    int level = 2;  // Local to main
    
    cout << "Main level: " << level << endl;
    cout << "Global level: " << ::level << endl;
    
    {
        int level = 3;  // Block level
        cout << "Block level: " << level << endl;
        cout << "Global level from block: " << ::level << endl;
        
        {
            int level = 4;  // Inner block
            cout << "Inner block level: " << level << endl;
        }
        
        cout << "Back to block level: " << level << endl;
    }
    
    cout << "Back to main level: " << level << endl;
    
    return 0;
}
```

### Example 4: Loop Scope with Accumulator
```cpp
#include <iostream>
using namespace std;

int main() {
    int sum = 0;  // Accessible throughout main
    
    for (int i = 1; i <= 5; i++) {
        int square = i * i;  // Only accessible in loop
        sum += square;
        cout << i << "² = " << square << endl;
    }
    
    cout << "Sum of squares: " << sum << endl;
    // cout << square;  // ❌ Error - square out of scope
    
    return 0;
}
```

### Example 5: Static Local Variables
```cpp
#include <iostream>
using namespace std;

void counter() {
    static int count = 0;  // Static local - persists between calls
    count++;
    cout << "Called " << count << " times" << endl;
}

void regularCounter() {
    int count = 0;  // Regular local - recreated each call
    count++;
    cout << "Regular called " << count << " times" << endl;
}

int main() {
    cout << "Static counter:" << endl;
    counter();
    counter();
    counter();
    
    cout << "\nRegular counter:" << endl;
    regularCounter();
    regularCounter();
    regularCounter();
    
    return 0;
}
```

## Scope with Classes

```cpp
#include <iostream>
using namespace std;

class MyClass {
private:
    int privateVar;  // Class scope - accessible only within class
    
public:
    int publicVar;   // Class scope - accessible anywhere with object
    
    void setValues(int p, int pub) {
        privateVar = p;  // Accessible within class
        publicVar = pub;
    }
    
    void display() {
        cout << "Private: " << privateVar << endl;
        cout << "Public: " << publicVar << endl;
    }
};

int main() {
    MyClass obj;
    obj.publicVar = 50;  // ✅ Accessible
    // obj.privateVar = 10;  // ❌ Error - private
    
    obj.setValues(10, 20);
    obj.display();
    
    return 0;
}
```

## Namespace Scope

```cpp
#include <iostream>
using namespace std;

namespace Math {
    const double PI = 3.14159;
    int add(int a, int b) {
        return a + b;
    }
}

namespace Physics {
    const double G = 9.81;
    double weight(double mass) {
        return mass * G;
    }
}

int main() {
    cout << "PI: " << Math::PI << endl;
    cout << "Add: " << Math::add(5, 3) << endl;
    cout << "Gravity: " << Physics::G << endl;
    cout << "Weight (10kg): " << Physics::weight(10) << endl;
    
    // Using namespace
    using namespace Math;
    cout << "PI (after using): " << PI << endl;
    cout << "Add (after using): " << add(10, 20) << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Using Uninitialized Local Variable
```cpp
int main() {
    int x;  // Uninitialized - contains garbage
    cout << x;  // Undefined behavior - prints garbage
    
    int y = 0;  // Always initialize local variables
    return 0;
}
```

### Mistake 2: Variable Name Conflict
```cpp
int value = 10;  // Global

void function() {
    int value = 20;  // Local shadows global
    // Can't access global without :: inside function
    cout << "Local: " << value << endl;
    cout << "Global: " << ::value << endl;  // Use :: to access global
}
```

### Mistake 3: Using Variable Outside Its Scope
```cpp
int main() {
    if (true) {
        int x = 10;
        cout << x << endl;  // ✅ OK
    }
    // cout << x;  // ❌ Error - x out of scope
    
    return 0;
}
```

### Mistake 4: Loop Variable Scope Confusion
```cpp
// WRONG - assuming i accessible after loop
for (int i = 0; i < 10; i++) {
    // Do something
}
// cout << i;  // ❌ Error - i not accessible

// CORRECT - declare before loop
int i;
for (i = 0; i < 10; i++) {
    // Do something
}
cout << i;  // ✅ OK
```

### Mistake 5: Global Variable Overuse
```cpp
// WRONG - excessive global variables
int a, b, c, d, e;  // Hard to track, easy to modify accidentally

// BETTER - use local variables or pass parameters
void function(int a, int b) {
    // Use parameters
}
```

## Scope Summary Table

| Scope Type | Declaration Location | Accessibility | Lifetime |
|------------|---------------------|---------------|----------|
| Global | Outside any function | Entire program | Program lifetime |
| Local | Inside function | Only within that function | Function execution |
| Block | Inside `{}` | Only within that block | Block execution |
| Static Local | Inside function with `static` | Only within function | Program lifetime |
| Class Member | Inside class | With class access rules | Object lifetime |
| Namespace | Inside namespace | With `::` or using | Program lifetime |

## Best Practices

### ✅ Do This
```cpp
// Use local variables when possible
void function() {
    int localVar = 10;  // Local - limited scope
    // Use local
}

// Use parameters instead of globals
void process(int value) {  // Parameter
    // Process value
}

// Use static for persistent local state
void counter() {
    static int count = 0;  // Persists between calls
    count++;
}

// Use const for constants
const double PI = 3.14159;  // Global constant is fine
```

### ❌ Avoid This
```cpp
// Avoid global variables
int globalCounter;  // Hard to debug

// Avoid shadowing
int value = 10;
void bad() {
    int value = 20;  // Shadows global - confusing
}

// Avoid large scope
int main() {
    int x, y, z, a, b, c;  // Declare closer to use
    // Lots of code...
    // Hard to track variables
}
```

## Quick Reference

| Rule | Description |
|------|-------------|
| Local > Global | Local variables shadow globals |
| Block scope | Variables inside `{}` only |
| Loop scope | Loop variable scope depends on declaration |
| :: operator | Access global when shadowed |
| static local | Persists between function calls |
| Minimize globals | Use local or parameters instead |

## Summary

- **Global variables** accessible everywhere (use sparingly)
- **Local variables** accessible only in their function/block
- **Block scope** variables declared inside `{}` are limited to that block
- **Shadowing** occurs when local variable has same name as global
- Use `::` to access global variable when shadowed
- **Static local** variables retain value between function calls
- **Minimize global variables** to reduce bugs
- Always **initialize local variables** before use
- **Declare variables** as close to their use as possible

## Basic Template
```cpp
#include <iostream>
using namespace std;

// Global variable (use sparingly)
int globalCounter = 0;

void demonstrateScope() {
    // Local variable
    int localVar = 10;
    
    // Static local variable (persists between calls)
    static int staticLocal = 0;
    staticLocal++;
    
    cout << "Local: " << localVar << endl;
    cout << "Static local: " << staticLocal << endl;
    cout << "Global: " << globalCounter << endl;
}

int main() {
    // Main local variable
    int mainLocal = 20;
    
    demonstrateScope();
    
    // Block scope
    {
        int blockVar = 30;
        cout << "Block variable: " << blockVar << endl;
    }
    // cout << blockVar;  // Error - out of scope
    
    // Loop scope
    for (int i = 0; i < 3; i++) {
        cout << "Loop i: " << i << endl;
    }
    // cout << i;  // Error - i out of scope
    
    // Shadowing example
    int value = 50;
    cout << "Local value: " << value << endl;
    cout << "Global value: " << ::globalCounter << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*