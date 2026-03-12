# 01 - Hello World (Getting Started with C++)

## What is Hello World?
The "Hello World" program is the simplest C++ program that displays the message "Hello World" on the screen. It's traditionally the first program written when learning a new programming language.

## The Code
```cpp
#include <iostream>

int main() {
    std::cout << "Hello World!";
    return 0;
}
```

## Line by Line Explanation

### Line 1: `#include <iostream>`
- **#include** is a preprocessor directive that tells the compiler to include a file
- **iostream** stands for input-output stream
- This header file contains definitions for input/output operations
- Without this, you cannot use `cout` (console output)

### Line 3: `int main()`
- **int** means the function returns an integer value
- **main()** is the entry point of every C++ program
- Execution always starts from the main function
- Every C++ program must have a main function

### Line 4: `std::cout << "Hello World!";`
- **std::** is the namespace (standard namespace)
- **cout** stands for "character output"
- **<<** is the stream insertion operator (sends data to cout)
- **"Hello World!"** is a string literal (text to display)
- **;** marks the end of a statement

### Line 5: `return 0;`
- Returns 0 to the operating system
- 0 indicates successful program execution
- Non-zero values typically indicate errors

## Alternative Versions

### Version 2: With newline
```cpp
#include <iostream>
int main() {
    std::cout << "Hello World!" << std::endl;
    return 0;
}
```
- **std::endl** adds a newline and flushes the output buffer

### Version 3: Using namespace std
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello World!" << endl;
    return 0;
}
```
- **using namespace std** allows you to omit `std::` prefix
- Not recommended for large projects (can cause naming conflicts)

### Version 4: Multiple outputs
```cpp
#include <iostream>
int main() {
    std::cout << "Hello" << " " << "World!";
    return 0;
}
```

## Common Variations

### With newline character
```cpp
std::cout << "Hello World!\n";
```
- **\n** is the newline character (faster than endl)

### Printing on multiple lines
```cpp
std::cout << "Hello\n";
std::cout << "World!";
```
Output:
```
Hello
World!
```

## How to Compile and Run

### Using g++ (Linux/Mac)
```bash
g++ hello.cpp -o hello
./hello
```

### Using g++ (Windows)
```bash
g++ hello.cpp -o hello.exe
hello.exe
```

### Using Visual Studio Code
1. Save file as `hello.cpp`
2. Open terminal in VS Code
3. Run: `g++ hello.cpp -o hello && ./hello`

## Common Errors and Solutions

| Error | Cause | Solution |
|-------|-------|----------|
| `'cout' was not declared` | Missing iostream | Add `#include <iostream>` |
| `expected ';' before...` | Missing semicolon | Add `;` at end of statement |
| `undefined reference to main` | No main function | Add `int main()` |
| `'cout' is not a member of 'std'` | Missing iostream | Add `#include <iostream>` |

## Output
```
Hello World!
```

## Practice Exercises

1. **Change the message**: Modify the program to print your name
2. **Print two lines**: Print "Hello" on first line and "World!" on second line
3. **Print numbers**: Modify to print `123` instead of text
4. **Print multiple items**: Print your name, age, and city on same line
5. **Without std::**: Try the version with `using namespace std`

## Expected Outputs for Exercises

Exercise 1:
```
John Doe
```

Exercise 2:
```
Hello
World!
```

Exercise 3:
```
123
```

Exercise 4:
```
John 25 New York
```

## Key Points to Remember
- ✅ Every C++ program needs `#include <iostream>` for input/output
- ✅ Every C++ program needs a `main()` function
- ✅ Statements end with semicolon `;`
- ✅ `cout` prints to console
- ✅ `<<` sends data to cout
- ✅ Strings are enclosed in double quotes `""`
- ✅ `return 0` means program executed successfully

## Quick Reference Card
```cpp
#include <iostream>     // For input/output
int main() {            // Main function
    std::cout << "text"; // Print text
    return 0;            // Success
}
```

## Checklist
- [✅] I can write Hello World program from memory
- [✅] I understand what #include does
- [✅] I know why we need main()
- [✅] I can explain cout and << operator
- [✅] I know difference between " " and ' '
- [✅] I know why we need semicolon
- [✅] I understand return 0
- [✅] I can compile and run the program
- [✅] I completed all practice exercises

