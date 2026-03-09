# 13 - Constants and const Keyword in C++

## What are Constants?
Constants are variables whose values cannot be changed after initialization. Once set, they are read-only.

## The const Keyword
`const` stands for "constant". It tells the compiler: "This value will never change."

## Basic Syntax

```cpp
const int DAYS_IN_WEEK = 7;
const float PI = 3.14159;
const string WELCOME_MSG = "Hello!";
```

## Simple Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    const int SPEED_OF_LIGHT = 299792458;  // meters per second
    const float GRAVITY = 9.81;             // m/s²
    
    cout << "Speed of light: " << SPEED_OF_LIGHT << " m/s" << endl;
    cout << "Gravity: " << GRAVITY << " m/s²" << endl;
    
    // SPEED_OF_LIGHT = 300000000;  // ❌ Error! Can't modify const
    
    return 0;
}
```

## Why Use Constants?

### 1. Prevent Accidental Changes
```cpp
// Without const
int maxStudents = 30;
maxStudents = 50;  // Oops! Someone changed it

// With const
const int MAX_STUDENTS = 30;
// MAX_STUDENTS = 50;  // ❌ Compiler error - safe!
```

### 2. Make Code More Readable
```cpp
// Hard to understand
double area = 3.14159 * 5 * 5;

// Easy to understand
const double PI = 3.14159;
double radius = 5;
double area = PI * radius * radius;
```

### 3. Easy Maintenance
```cpp
// Change in one place only
const double TAX_RATE = 0.08;

double price1 = 100 * TAX_RATE;
double price2 = 200 * TAX_RATE;
double price3 = 300 * TAX_RATE;
// Change TAX_RATE once, all update automatically
```

## Different Ways to Declare Constants

### Method 1: const keyword (C++ way)
```cpp
const int AGE = 25;
const float TEMP = 98.6;
```

### Method 2: #define (C preprocessor - old way)
```cpp
#define AGE 25
#define PI 3.14159
// Note: No semicolon, no data type
```

### Method 3: enum for integer constants
```cpp
enum { MONTHS = 12, WEEKS = 52 };
```

### Method 4: constexpr (C++11) - compile-time constants
```cpp
constexpr int SQUARE(int x) { return x * x; }
constexpr int VALUE = SQUARE(5);  // Computed at compile time
```

## const vs #define

| Feature | const | #define |
|---------|-------|---------|
| Type safety | ✅ Yes | ❌ No |
| Memory used | ✅ Yes | ❌ No (text replacement) |
| Debugger friendly | ✅ Yes | ❌ No |
| Scope control | ✅ Yes | ❌ No (global) |
| Preferred in C++ | ✅ Yes | ❌ No |

```cpp
// #define (C-style, avoid in C++)
#define MAX 100
#define PI 3.14

// const (C++ style, preferred)
const int MAX = 100;
const double PI = 3.14;
```

## Constants with Different Data Types

### Integer Constants
```cpp
const int MAX_USERS = 1000;
const long DISTANCE = 384400L;  // Moon distance in km
const unsigned int COUNT = 500U;
```

### Floating-Point Constants
```cpp
const float TAX_RATE = 0.08f;
const double PI = 3.1415926535;
const long double BIG_NUM = 3.14e100L;
```

### Character Constants
```cpp
const char GRADE_A = 'A';
const char NEWLINE = '\n';
const char NULL_CHAR = '\0';
```

### String Constants
```cpp
const string APP_NAME = "MyProgram";
const string ERROR_MSG = "Something went wrong!";
```

### Boolean Constants
```cpp
const bool DEBUG_MODE = true;
const bool ENABLE_LOGGING = false;
```

## Constant Naming Conventions

### Common Styles

```cpp
// UPPER_CASE (most common for constants)
const int MAX_VALUE = 100;
const string DEFAULT_NAME = "Guest";

// kCamelCase (Google style)
const int kMaxValue = 100;
const string kDefaultName = "Guest";

// Regular camelCase (less common)
const int maxValue = 100;
```

## Practical Examples

### Example 1: Mathematical Constants
```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double PI = 3.14159265358979;
    const double E = 2.71828182845904;
    const double GOLDEN_RATIO = 1.61803398875;
    
    double radius = 5.0;
    double area = PI * radius * radius;
    double circumference = 2 * PI * radius;
    
    cout << "Circle with radius " << radius << ":" << endl;
    cout << "Area: " << area << endl;
    cout << "Circumference: " << circumference << endl;
    
    return 0;
}
```

### Example 2: Configuration Settings
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // App configuration
    const string APP_NAME = "Student Manager";
    const string VERSION = "1.0.0";
    const int MAX_STUDENTS = 100;
    const double PASSING_GRADE = 60.0;
    const bool DEBUG_ENABLED = false;
    
    cout << APP_NAME << " v" << VERSION << endl;
    cout << "Max students: " << MAX_STUDENTS << endl;
    cout << "Passing grade: " << PASSING_GRADE << endl;
    
    return 0;
}
```

### Example 3: Unit Conversion
```cpp
#include <iostream>
using namespace std;

int main() {
    const double INCH_TO_CM = 2.54;
    const double POUND_TO_KG = 0.453592;
    const double MILE_TO_KM = 1.60934;
    
    double inches = 12;
    double cm = inches * INCH_TO_CM;
    cout << inches << " inches = " << cm << " cm" << endl;
    
    double pounds = 150;
    double kg = pounds * POUND_TO_KG;
    cout << pounds << " pounds = " << kg << " kg" << endl;
    
    return 0;
}
```

### Example 4: Array Size Constants
```cpp
#include <iostream>
using namespace std;

int main() {
    const int DAYS_IN_WEEK = 7;
    const int MONTHS_IN_YEAR = 12;
    const int MAX_SCORES = 5;
    
    // Use constants for array sizes
    int temperatures[DAYS_IN_WEEK];
    double monthlySales[MONTHS_IN_YEAR];
    int scores[MAX_SCORES];
    
    // Fill with sample data
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        temperatures[i] = 20 + i;
    }
    
    cout << "Week temperatures: ";
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        cout << temperatures[i] << " ";
    }
    
    return 0;
}
```

### Example 5: Menu System
```cpp
#include <iostream>
using namespace std;

int main() {
    const int MENU_START = 1;
    const int MENU_LOAD = 2;
    const int MENU_SETTINGS = 3;
    const int MENU_EXIT = 4;
    
    int choice;
    
    cout << "===== MAIN MENU =====" << endl;
    cout << MENU_START << ". Start Game" << endl;
    cout << MENU_LOAD << ". Load Game" << endl;
    cout << MENU_SETTINGS << ". Settings" << endl;
    cout << MENU_EXIT << ". Exit" << endl;
    cout << "Choice: ";
    cin >> choice;
    
    switch(choice) {
        case MENU_START:
            cout << "Starting game..." << endl;
            break;
        case MENU_LOAD:
            cout << "Loading game..." << endl;
            break;
        case MENU_SETTINGS:
            cout << "Settings..." << endl;
            break;
        case MENU_EXIT:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    
    return 0;
}
```

## const with Pointers

### Different const Pointer Combinations

```cpp
int value = 10;
int another = 20;

// 1. Pointer to const data (data can't change)
const int* ptr1 = &value;
// *ptr1 = 15;  // ❌ Error! Can't change data
ptr1 = &another;  // ✅ OK! Can change pointer

// 2. const pointer (pointer can't change)
int* const ptr2 = &value;
*ptr2 = 15;  // ✅ OK! Can change data
// ptr2 = &another;  // ❌ Error! Can't change pointer

// 3. const pointer to const data (neither can change)
const int* const ptr3 = &value;
// *ptr3 = 15;  // ❌ Error! Can't change data
// ptr3 = &another;  // ❌ Error! Can't change pointer
```

## const with Functions

### const Parameters
```cpp
void printValue(const int x) {
    // x = 10;  // ❌ Error! Can't modify const parameter
    cout << x << endl;
}

void displayMessage(const string& msg) {
    // msg = "New";  // ❌ Error! Can't modify const reference
    cout << msg << endl;
}
```

### const Return Values
```cpp
const int getValue() {
    return 42;
}

// getValue() = 10;  // ❌ Error! Can't assign to const return
```

### const Member Functions (OOP)
```cpp
class Student {
private:
    string name;
    int age;
    
public:
    string getName() const {  // const function - doesn't modify object
        return name;
    }
    
    int getAge() const {
        return age;
    }
};
```

## Compile-Time Constants with constexpr

```cpp
#include <iostream>
using namespace std;

constexpr int square(int x) {
    return x * x;
}

constexpr int CUBE(int x) { return x * x * x; }

int main() {
    constexpr int SIZE = 10;           // Compile-time constant
    constexpr int AREA = square(5);     // Computed at compile time
    constexpr int VOLUME = CUBE(3);      // Computed at compile time
    
    int array[SIZE];                     // ✅ OK - SIZE is constant
    int grid[AREA];                       // ✅ OK - AREA computed at compile time
    
    cout << "Square of 5: " << AREA << endl;
    cout << "Cube of 3: " << VOLUME << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Modifying const
```cpp
const int MAX = 100;
// MAX = 200;  // ❌ Error! Can't modify const
```

### Mistake 2: Uninitialized const
```cpp
// Wrong
const int VALUE;  // ❌ Error! Must initialize

// Correct
const int VALUE = 10;
```

### Mistake 3: Using #define instead of const
```cpp
// Old C-style (avoid)
#define MAX 100
#define PI 3.14

// Better C++ style
const int MAX = 100;
const double PI = 3.14;
```

### Mistake 4: const with cin
```cpp
const int age;
// cin >> age;  // ❌ Error! Can't change const

// Correct
int age;
cin >> age;
```

### Mistake 5: const in headers without extern
```cpp
// Wrong in header (creates multiple copies)
const int MAX = 100;

// Better
extern const int MAX;  // Declaration
// In .cpp file: const int MAX = 100;  // Definition
```

## Best Practices

### ✅ Do This
```cpp
// Use const for values that shouldn't change
const double TAX_RATE = 0.08;

// Use meaningful names
const int MAX_LOGIN_ATTEMPTS = 3;

// Use const for array sizes
const int ARRAY_SIZE = 10;
int data[ARRAY_SIZE];

// Use const parameters for read-only
void display(const string& msg);

// Use constexpr for compile-time constants
constexpr int SIZE = 100;

// Group related constants
const int MONDAY = 1;
const int TUESDAY = 2;
const int WEDNESDAY = 3;
```

### ❌ Avoid This
```cpp
// Don't use magic numbers
double area = 3.14159 * r * r;  // What's 3.14159?

// Don't use #define in C++
#define MAX 100

// Don't modify const parameters
void bad(const int x) {
    // const_cast to modify - don't do this!
}

// Don't use const for values that change
const int counter = 0;  // If you need to increment
```

## Quick Reference Table

| Declaration | Meaning | Can Change Value? | Can Change Pointer? |
|-------------|---------|-------------------|---------------------|
| `const int x = 5;` | x is constant | ❌ No | N/A |
| `const int* p = &x;` | Pointer to const int | ❌ No | ✅ Yes |
| `int* const p = &x;` | Const pointer to int | ✅ Yes | ❌ No |
| `const int* const p = &x;` | Const pointer to const int | ❌ No | ❌ No |

## When to Use Constants

| Situation | Example | Why Constant? |
|-----------|---------|---------------|
| Mathematical constants | `PI`, `E` | Values never change |
| Configuration | `MAX_USERS`, `TIMEOUT` | Centralized control |
| Physical constants | `SPEED_OF_LIGHT` | Scientific accuracy |
| Magic numbers | `DAYS_IN_WEEK` | Code readability |
| Array sizes | `BUFFER_SIZE` | Memory allocation |
| Error messages | `ERROR_NOT_FOUND` | Consistent messaging |

## Summary

- **const** makes variables read-only
- Must initialize when declared
- Prevents accidental changes
- Makes code more readable
- Centralizes configuration
- const pointers have different rules
- Use `constexpr` for compile-time constants
- Prefer `const` over `#define` in C++
- const parameters prevent modification
- const member functions don't modify object

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Constants for configuration
    const string APP_NAME = "My Application";
    const string VERSION = "1.0.0";
    const int MAX_ITEMS = 100;
    const double TAX_RATE = 0.08;
    const bool DEBUG_MODE = false;
    
    // Mathematical constants
    const double PI = 3.14159265359;
    const double GRAVITY = 9.81;
    
    // Display information
    cout << APP_NAME << " v" << VERSION << endl;
    cout << "Max items: " << MAX_ITEMS << endl;
    cout << "Tax rate: " << TAX_RATE * 100 << "%" << endl;
    cout << "Pi: " << PI << endl;
    
    // Using constants in calculations
    double radius = 5.0;
    double area = PI * radius * radius;
    cout << "\nCircle area: " << area << endl;
    
    return 0;
}
```