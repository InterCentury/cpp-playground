# 02 - Basic C++ Program Structure

## What is Program Structure?
Just like a house has different rooms (kitchen, bedroom, bathroom), a C++ program has different sections. Let's look at the simplest possible structure first.

## The Simplest Working C++ Program

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello World";
    return 0;
}
```

## Breaking Down Each Part

### Part 1: The Header (`#include <iostream>`)
```cpp
#include <iostream>
```
- **What it does**: Includes input/output tools
- **Think of it as**: Importing a tool box
- **Why needed**: Without this, you can't print anything
- **iostream** = input + output stream

### Part 2: The Namespace (`using namespace std;`)
```cpp
using namespace std;
```
- **What it does**: Saves you from typing `std::` again and again
- **Think of it as**: Telling C++ "I'll be using standard tools"
- **Without this**: You'd have to write `std::cout` instead of just `cout`

### Part 3: The Main Function (`int main()`)
```cpp
int main() {
    // code goes here
    return 0;
}
```
- **What it does**: This is where your program starts running
- **Think of it as**: The front door of your house
- **Why needed**: Every C++ program MUST have one main function
- The `{ }` curly braces show where the function begins and ends

### Part 4: The Statement (`cout << "Hello World";`)
```cpp
cout << "Hello World";
```
- **What it does**: Prints text on screen
- **Think of it as**: Speaking to the computer screen
- **cout** = see-out (console output)
- **<<** = send this to cout
- **;** = end of statement (like a period in English)

### Part 5: The Return (`return 0;`)
```cpp
return 0;
```
- **What it does**: Tells the computer "program finished successfully"
- **Think of it as**: Saying "mission accomplished" to the operating system
- **0** means success, any other number means error

## Another Simple Example

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "My name is John";
    cout << "I am 25 years old";
    return 0;
}
```
Output:
```
My name is JohnI am 25 years old
```

**Problem**: Everything printed on same line! Let's fix it:

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "My name is John" << endl;
    cout << "I am 25 years old" << endl;
    return 0;
}
```
Output:
```
My name is John
I am 25 years old
```

## Program That Uses Input

```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    
    cout << "Enter your age: ";
    cin >> age;
    
    cout << "You are " << age << " years old";
    
    return 0;
}
```

## Three Essential Parts of Any C++ Program

### 1. **Header Section** (Top part)
```cpp
#include <iostream>
using namespace std;
```
Always at the very top of your program

### 2. **Main Section** (Middle part)
```cpp
int main() {
    // your code
}
```
Always contains your program logic

### 3. **Return Section** (Bottom part)
```cpp
    return 0;
}
```
Always at the end of main function

## Common Program Structures You'll See

### Structure 1: Very Basic (for beginners)
```cpp
#include <iostream>
using namespace std;

int main() {
    // your code
    return 0;
}
```

### Structure 2: Without `using namespace std`
```cpp
#include <iostream>

int main() {
    std::cout << "Hello";
    return 0;
}
```

### Structure 3: With Comments (documentation)
```cpp
// My first program
// Written by: Alex
// Date: 2024

#include <iostream>
using namespace std;

int main() {
    // Print welcome message
    cout << "Welcome to C++";
    
    return 0;
}
```

## Visual Representation

```
┌─────────────────────────────────────┐
│ #include <iostream>                 │  ← Header (tools)
│ using namespace std;                │  ← Namespace (shortcuts)
├─────────────────────────────────────┤
│ int main() {                        │  ← Main (entry point)
│     cout << "Hi";    ← Statement    │
│     return 0;        ← Return       │
│ }                                   │
└─────────────────────────────────────┘
```

## Step-by-Step Program Execution

When you run a C++ program:

1. **Step 1**: Computer looks for `main()`
2. **Step 2**: Executes code line by line inside `{ }`
3. **Step 3**: Sees `return 0` and stops

## Example with Multiple Statements

```cpp
#include <iostream>
using namespace std;

int main() {
    // Statement 1
    cout << "Learning C++" << endl;
    
    // Statement 2
    cout << "Is fun" << endl;
    
    // Statement 3
    cout << "Let's continue" << endl;
    
    // End program
    return 0;
}
```

## Common Beginner Mistakes

### Mistake 1: Missing #include
```cpp
// Wrong
int main() {
    cout << "Hi";  // Error! cout not recognized
    return 0;
}

// Correct
#include <iostream>
using namespace std;
int main() {
    cout << "Hi";
    return 0;
}
```

### Mistake 2: Missing semicolon
```cpp
// Wrong
cout << "Hi"  // Error! missing ;

// Correct
cout << "Hi";
```

### Mistake 3: Wrong brackets
```cpp
// Wrong
int main()  // Missing {
    cout << "Hi";
    return 0;
}  // This } has no matching {

// Correct
int main() {
    cout << "Hi";
    return 0;
}
```

### Mistake 4: No return statement
```cpp
// Wrong (might work but not correct)
int main() {
    cout << "Hi";
}  // missing return 0

// Correct
int main() {
    cout << "Hi";
    return 0;
}
```

## Different Ways to Write Same Program

### Version A: Standard way
```cpp
#include <iostream>
using namespace std;
int main() {
    cout << "Hello";
    return 0;
}
```

### Version B: Without namespace
```cpp
#include <iostream>
int main() {
    std::cout << "Hello";
    return 0;
}
```

### Version C: One line (not recommended)
```cpp
#include <iostream>
using namespace std;
int main() { cout << "Hello"; return 0; }
```

## Memory Aid: "THE Program Structure"

- **T** - Top: `#include` section
- **H** - Header: `using namespace std`
- **E** - Entry point: `int main()`
- **Program** - Your actual code
- **End** - `return 0;`

## Quick Reference

| Section | Syntax | Purpose |
|---------|--------|---------|
| Header | `#include <iostream>` | Gets input/output tools |
| Namespace | `using namespace std;` | Shortens code |
| Main | `int main() {` | Program starts here |
| Statement | `cout << "text";` | Does something |
| Return | `return 0;` | Ends program |
| End Brace | `}` | Closes main |

## Practice Exercises

1. **Exercise 1**: Write a program with three cout statements printing your name, age, and city
2. **Exercise 2**: Write a program without `using namespace std` (use std::cout)
3. **Exercise 3**: Write a program that prints "Start" on first line and "End" on second line
4. **Exercise 4**: Remove return 0 from your program and see what happens
5. **Exercise 5**: Try to write a program without main() and see the error

## Summary

Every C++ program needs:
- ✅ `#include <iostream>` - to print things
- ✅ `int main()` - where program starts
- ✅ `{ }` - to enclose the program
- ✅ `;` - at end of each statement
- ✅ `return 0;` - to end successfully

The structure is always the same, only the code inside `{ }` changes based on what you want the program to do.