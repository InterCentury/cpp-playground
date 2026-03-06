# 07 - Variable Declaration and Initialization in C++

## What is a Variable?
A variable is a container that stores data in memory. Think of it as a labeled box where you can store values.

## Variable Declaration vs Initialization

| Concept | What it does | Example |
|---------|--------------|---------|
| **Declaration** | Creates variable (reserves memory) | `int age;` |
| **Initialization** | Assigns first value | `age = 25;` |
| **Declaration + Initialization** | Both at once | `int age = 25;` |

## Basic Syntax

### 1. Declaration Only
```cpp
int age;           // declared but has garbage value
float price;       // declared but not initialized
char grade;        // declared but empty
```

### 2. Initialization After Declaration
```cpp
int age;           // declaration
age = 25;          // initialization

float price;
price = 99.99;     // initialization
```

### 3. Declaration + Initialization (Recommended)
```cpp
int age = 25;
float price = 99.99;
char grade = 'A';
bool isPassed = true;
```

## Multiple Variables

### Same Type - Different Lines
```cpp
int age = 25;
int score = 100;
int count = 0;
```

### Same Type - Same Line
```cpp
int age = 25, score = 100, count = 0;
```

### Different Types
```cpp
int age = 25;
float price = 99.99;
char grade = 'A';
string name = "John";
```

## Ways to Initialize Variables

### Method 1: Assignment `=`
```cpp
int x = 10;           // C-style initialization
```

### Method 2: Constructor `()`
```cpp
int x(10);            // Constructor initialization
```

### Method 3: Uniform `{}` (C++11)
```cpp
int x{10};            // Uniform initialization (safe)
int y{};              // Zero initialization (y = 0)
```

## Examples with Different Data Types

### Integer Types
```cpp
int age = 25;
short small = 100;
long big = 100000;
long long veryBig = 1000000000;
```

### Floating Point Types
```cpp
float price = 99.99f;           // f suffix for float
double pi = 3.1415926535;       // more precision
long double large = 3.14L;       // L suffix
```

### Character Type
```cpp
char grade = 'A';
char newline = '\n';
char digit = '5';
```

### Boolean Type
```cpp
bool isPassed = true;
bool isFinished = false;
bool isValid = 1;        // 1 = true
bool isDone = 0;         // 0 = false
```

### String Type
```cpp
string name = "John";
string message = "Hello World";
string empty = "";       // empty string
```

## Variable Naming Rules

### ✅ Allowed
```cpp
int age;              // letters
int age2;             // letters and numbers
int _age;             // underscore
int studentAge;       // camelCase
int student_age;      // snake_case
```

### ❌ Not Allowed
```cpp
int 2age;             // can't start with number
int my-age;           // hyphen not allowed
int my age;           // space not allowed
int int;              // keywords not allowed
int $age;             // special chars not allowed
```

## Default Values

### Global Variables (outside main)
```cpp
#include <iostream>
using namespace std;

int globalInt;        // automatically 0
double globalDouble;  // automatically 0.0
char globalChar;      // automatically '\0'
bool globalBool;      // automatically false

int main() {
    cout << globalInt;    // prints 0
    return 0;
}
```

### Local Variables (inside main)
```cpp
int main() {
    int localInt;         // garbage value (not 0)
    cout << localInt;     // prints random number
    
    int safe = 0;         // always initialize!
    return 0;
}
```

## Common Initialization Patterns

### Pattern 1: Zero Initialization
```cpp
int count = 0;
float total = 0.0f;
char letter = '\0';
bool flag = false;
string text = "";
```

### Pattern 2: Initialize with Calculation
```cpp
int sum = 10 + 20;
int product = 5 * 6;
int average = (100 + 200) / 2;
```

### Pattern 3: Initialize with Other Variables
```cpp
int x = 10;
int y = x;              // y = 10
int z = x + y;          // z = 20
```

### Pattern 4: Constant Variables
```cpp
const int MAX = 100;            // can't change
const float PI = 3.14159;       // read-only
const string WELCOME = "Hi";    // constant string
```

## Practical Examples

### Example 1: Student Info
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declaration and initialization
    string name = "Alex";
    int age = 20;
    float gpa = 3.75;
    char grade = 'A';
    bool isEnrolled = true;
    
    // Display values
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "GPA: " << gpa << endl;
    cout << "Grade: " << grade << endl;
    cout << "Enrolled: " << isEnrolled << endl;
    
    return 0;
}
```

### Example 2: Calculator Variables
```cpp
#include <iostream>
using namespace std;

int main() {
    // Initialize with values
    int num1 = 15;
    int num2 = 4;
    
    // Initialize with calculations
    int sum = num1 + num2;
    int difference = num1 - num2;
    int product = num1 * num2;
    float quotient = (float)num1 / num2;  // type casting
    
    cout << num1 << " + " << num2 << " = " << sum << endl;
    cout << num1 << " - " << num2 << " = " << difference << endl;
    cout << num1 << " * " << num2 << " = " << product << endl;
    cout << num1 << " / " << num2 << " = " << quotient << endl;
    
    return 0;
}
```

### Example 3: User Input Variables
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declare variables first
    string name;
    int age;
    float height;
    
    // Initialize through user input
    cout << "Enter name: ";
    cin >> name;
    
    cout << "Enter age: ";
    cin >> age;
    
    cout << "Enter height (meters): ";
    cin >> height;
    
    // Display
    cout << "\n--- Profile ---" << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << "m" << endl;
    
    return 0;
}
```

## Variable Scope Examples

### Local Variables
```cpp
int main() {
    int x = 10;        // local to main
    {
        int y = 20;    // local to this block
        cout << x;     // ✅ can access x
        cout << y;     // ✅ can access y
    }
    // cout << y;      // ❌ error: y not accessible
    return 0;
}
```

### Global Variables
```cpp
int global = 100;      // global variable

void display() {
    cout << global;    // ✅ can access global
}

int main() {
    cout << global;    // ✅ can access global
    return 0;
}
```

## Common Mistakes

### Mistake 1: Using Uninitialized Variable
```cpp
// Wrong
int x;
cout << x;        // prints garbage value

// Correct
int x = 0;
cout << x;        // prints 0
```

### Mistake 2: Wrong Type
```cpp
// Wrong
int price = 99.99;     // loses decimal part (becomes 99)

// Correct
float price = 99.99;
```

### Mistake 3: Redeclaration
```cpp
// Wrong
int x = 10;
int x = 20;        // error: redeclaration

// Correct
int x = 10;
x = 20;            // reassign, not redeclare
```

### Mistake 4: Case Sensitivity
```cpp
int age = 25;
cout << Age;       // error: Age != age
```

### Mistake 5: Using Before Declaration
```cpp
// Wrong
x = 10;            // error: x not declared
int x;

// Correct
int x;
x = 10;
```

## Best Practices

### ✅ Do This
```cpp
// Initialize when declared
int score = 0;

// Use meaningful names
int studentCount = 0;

// One variable per line (for clarity)
int age = 25;
string name = "John";

// Constants in UPPERCASE
const int MAX_SIZE = 100;
```

### ❌ Avoid This
```cpp
// Don't leave uninitialized
int x;              // bad

// Don't use meaningless names
int a = 10;         // what is 'a'?

// Don't cram multiple on one line
int x=10,y=20,z=30; // hard to read
```

## Variable Naming Conventions

| Style | Example | When to use |
|-------|---------|-------------|
| camelCase | `studentAge` | Variables, functions |
| PascalCase | `StudentAge` | Classes, structs |
| snake_case | `student_age` | Common in older code |
| UPPER_CASE | `MAX_VALUE` | Constants |

## Quick Reference Table

| Data Type | Declaration | Initialization | Example |
|-----------|-------------|----------------|---------|
| int | `int x;` | `x = 5;` | `int age = 25;` |
| float | `float f;` | `f = 3.14;` | `float price = 9.99;` |
| double | `double d;` | `d = 3.14159;` | `double pi = 3.14159;` |
| char | `char c;` | `c = 'A';` | `char grade = 'B';` |
| bool | `bool b;` | `b = true;` | `bool flag = false;` |
| string | `string s;` | `s = "Hi";` | `string name = "John";` |

## Summary

- **Declaration** creates variable (`int age;`)
- **Initialization** gives first value (`age = 25;`)
- Always initialize variables before use
- Use meaningful variable names
- Follow naming rules (letters, numbers, underscore)
- Local variables have garbage values (initialize!)
- Global variables auto-initialize to zero
- Different initialization methods: `=`, `()`, `{}`
- Constants cannot change after initialization
- Variables must be declared before use
- Same name can't be declared twice
- Case-sensitive: `Age` ≠ `age`

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declare and initialize variables
    int number = 10;
    float decimal = 5.75;
    char letter = 'X';
    bool flag = true;
    string text = "Hello";
    
    // Use variables
    cout << "Number: " << number << endl;
    cout << "Decimal: " << decimal << endl;
    cout << "Letter: " << letter << endl;
    cout << "Boolean: " << flag << endl;
    cout << "String: " << text << endl;
    
    return 0;
}
```