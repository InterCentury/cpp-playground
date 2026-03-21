# 55 - Pass by Value in C++

## What is Pass by Value?
Pass by value means that when you pass an argument to a function, a **copy** of the argument's value is made and stored in the function's parameter. The function works with this copy, and any modifications made to the parameter do NOT affect the original variable.

## Basic Concept

```cpp
#include <iostream>
using namespace std;

void increment(int x) {
    x++;  // Modifies the local copy
    cout << "Inside function: x = " << x << endl;
}

int main() {
    int num = 5;
    cout << "Before call: num = " << num << endl;
    
    increment(num);  // Passes a copy of num
    
    cout << "After call: num = " << num << endl;  // Still 5!
    
    return 0;
}
```

## How Pass by Value Works

```cpp
#include <iostream>
using namespace std;

void modifyValue(int value) {
    cout << "Inside function - before: " << value << endl;
    value = 100;  // Changes only the copy
    cout << "Inside function - after: " << value << endl;
}

int main() {
    int original = 10;
    
    cout << "Before function call: original = " << original << endl;
    
    modifyValue(original);  // Copy of original is passed
    
    cout << "After function call: original = " << original << endl;  // Still 10!
    
    return 0;
}
```

## Pass by Value with Different Data Types

### Integer
```cpp
#include <iostream>
using namespace std;

void modifyInt(int x) {
    x = 100;
    cout << "Inside: x = " << x << endl;
}

int main() {
    int num = 5;
    modifyInt(num);
    cout << "Outside: num = " << num << endl;  // Still 5
    
    return 0;
}
```

### Double
```cpp
#include <iostream>
using namespace std;

void modifyDouble(double d) {
    d = 3.14159;
    cout << "Inside: d = " << d << endl;
}

int main() {
    double pi = 3.14;
    modifyDouble(pi);
    cout << "Outside: pi = " << pi << endl;  // Still 3.14
    
    return 0;
}
```

### Char
```cpp
#include <iostream>
using namespace std;

void modifyChar(char c) {
    c = 'Z';
    cout << "Inside: c = " << c << endl;
}

int main() {
    char letter = 'A';
    modifyChar(letter);
    cout << "Outside: letter = " << letter << endl;  // Still 'A'
    
    return 0;
}
```

### Boolean
```cpp
#include <iostream>
using namespace std;

void modifyBool(bool b) {
    b = true;
    cout << "Inside: b = " << boolalpha << b << endl;
}

int main() {
    bool flag = false;
    modifyBool(flag);
    cout << "Outside: flag = " << boolalpha << flag << endl;  // Still false
    
    return 0;
}
```

## Pass by Value with Strings

```cpp
#include <iostream>
#include <string>
using namespace std;

void modifyString(string s) {
    s = "Modified";
    cout << "Inside: s = " << s << endl;
}

int main() {
    string text = "Hello";
    modifyString(text);
    cout << "Outside: text = " << text << endl;  // Still "Hello"
    
    return 0;
}
```

## Pass by Value with Arrays

```cpp
#include <iostream>
using namespace std;

// Note: Arrays are NOT passed by value (they decay to pointers)
// This is actually pass by address, but we'll see the effect
void modifyArray(int arr[], int size) {
    arr[0] = 100;  // This DOES modify the original array!
    cout << "Inside array[0]: " << arr[0] << endl;
}

int main() {
    int numbers[3] = {1, 2, 3};
    cout << "Before: numbers[0] = " << numbers[0] << endl;
    
    modifyArray(numbers, 3);
    
    cout << "After: numbers[0] = " << numbers[0] << endl;  // Changed to 100!
    
    return 0;
}
```

## Pass by Value with Structures

```cpp
#include <iostream>
#include <string>
using namespace std;

struct Person {
    string name;
    int age;
};

void modifyPerson(Person p) {
    p.name = "Modified";
    p.age = 99;
    cout << "Inside: " << p.name << ", " << p.age << endl;
}

int main() {
    Person john = {"John", 25};
    
    cout << "Before: " << john.name << ", " << john.age << endl;
    modifyPerson(john);
    cout << "After: " << john.name << ", " << john.age << endl;  // Still original!
    
    return 0;
}
```

## Pass by Value with Classes

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int id;
    
    Student(string n, int i) : name(n), id(i) {}
    
    void display() const {
        cout << name << " (ID: " << id << ")" << endl;
    }
};

void modifyStudent(Student s) {
    s.name = "Modified";
    s.id = 999;
    cout << "Inside: ";
    s.display();
}

int main() {
    Student john("John", 123);
    
    cout << "Before: ";
    john.display();
    
    modifyStudent(john);
    
    cout << "After: ";
    john.display();  // Still original!
    
    return 0;
}
```

## Practical Examples

### Example 1: Simple Calculator (No Side Effects)
```cpp
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;  // Returns result, doesn't modify arguments
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

double divide(int a, int b) {
    if (b != 0) return static_cast<double>(a) / b;
    return 0;
}

int main() {
    int x = 10, y = 5;
    
    cout << x << " + " << y << " = " << add(x, y) << endl;
    cout << x << " - " << y << " = " << subtract(x, y) << endl;
    cout << x << " * " << y << " = " << multiply(x, y) << endl;
    cout << x << " / " << y << " = " << divide(x, y) << endl;
    
    // Original values unchanged
    cout << "Original x = " << x << ", y = " << y << endl;
    
    return 0;
}
```

### Example 2: Mathematical Functions
```cpp
#include <iostream>
#include <cmath>
using namespace std;

double power(double base, int exponent) {
    double result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

double absolute(double x) {
    return (x < 0) ? -x : x;
}

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    double num = -5.5;
    int n = 5;
    
    cout << "Absolute of " << num << " = " << absolute(num) << endl;
    cout << "Power: " << 2 << "^" << n << " = " << power(2, n) << endl;
    cout << "Factorial of " << n << " = " << factorial(n) << endl;
    
    // Original values unchanged
    cout << "Original num = " << num << ", n = " << n << endl;
    
    return 0;
}
```

### Example 3: String Processing (No Modification)
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string toUpperCase(string s) {
    for (char &c : s) {
        c = toupper(c);
    }
    return s;
}

string toLowerCase(string s) {
    for (char &c : s) {
        c = tolower(c);
    }
    return s;
}

int countVowels(string s) {
    int count = 0;
    for (char c : s) {
        c = tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

int main() {
    string text = "Hello World";
    
    cout << "Original: " << text << endl;
    cout << "Uppercase: " << toUpperCase(text) << endl;
    cout << "Lowercase: " << toLowerCase(text) << endl;
    cout << "Vowels: " << countVowels(text) << endl;
    cout << "After functions: " << text << endl;  // Still original
    
    return 0;
}
```

### Example 4: Array Element Processing (Value of Elements)
```cpp
#include <iostream>
using namespace std;

void processElement(int x) {
    x = x * 2;  // Modifies copy
    cout << "Inside: " << x << endl;
}

int main() {
    int numbers[] = {10, 20, 30};
    
    for (int i = 0; i < 3; i++) {
        cout << "Before processing numbers[" << i << "] = " << numbers[i] << endl;
        processElement(numbers[i]);  // Passes copy of array element
        cout << "After processing numbers[" << i << "] = " << numbers[i] << endl;
        cout << endl;
    }
    
    return 0;
}
```

### Example 5: Validation Functions
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isValidAge(int age) {
    return age >= 0 && age <= 150;
}

bool isValidScore(int score) {
    return score >= 0 && score <= 100;
}

bool isValidUsername(string username) {
    if (username.length() < 3 || username.length() > 20) {
        return false;
    }
    
    for (char c : username) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    int age = 25;
    int score = 85;
    string username = "john123";
    
    cout << boolalpha;
    cout << "Age " << age << " valid? " << isValidAge(age) << endl;
    cout << "Score " << score << " valid? " << isValidScore(score) << endl;
    cout << "Username '" << username << "' valid? " << isValidUsername(username) << endl;
    
    return 0;
}
```

## Memory and Performance Considerations

```cpp
#include <iostream>
#include <string>
#include <chrono>
using namespace std;

// Pass by value (copies large object)
void processByValue(string s) {
    // Works with copy
}

// Pass by reference (no copy)
void processByReference(const string &s) {
    // Works with original (read-only)
}

int main() {
    string largeText = "This is a very large string that will be copied many times...";
    
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        processByValue(largeText);  // Creates copy each time
    }
    auto end = chrono::high_resolution_clock::now();
    auto valueTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        processByReference(largeText);  // No copy
    }
    end = chrono::high_resolution_clock::now();
    auto refTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Pass by value time: " << valueTime.count() << " ms" << endl;
    cout << "Pass by reference time: " << refTime.count() << " ms" << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Expecting Changes to Affect Original
```cpp
void increment(int x) {
    x++;  // Wrong assumption - this doesn't change original
}

int main() {
    int num = 5;
    increment(num);
    cout << num;  // Still 5 - unexpected!
    
    // Correct - return value or use reference
    return 0;
}
```

### Mistake 2: Large Objects Passed by Value (Inefficient)
```cpp
// WRONG - copies entire large object
void processLargeArray(int arr[1000]) {  // This is actually a pointer
    // Actually arrays are passed by address
}

// But for strings, vectors, etc.
void processLargeString(string s) {  // Copies entire string
    // Inefficient for large strings
}

// CORRECT - use const reference
void processLargeString(const string &s) {
    // No copy, read-only
}
```

### Mistake 3: Modifying Array Elements Thinking They're Copies
```cpp
void modifyArray(int arr[], int size) {
    arr[0] = 100;  // This DOES modify original!
    // Arrays are not passed by value
}

int main() {
    int nums[3] = {1, 2, 3};
    modifyArray(nums, 3);
    cout << nums[0];  // 100 - changed!
    
    return 0;
}
```

### Mistake 4: Returning Local Variable (Actually Pass by Value)
```cpp
// This is actually correct - returning a copy
int getNumber() {
    int x = 5;
    return x;  // Returns copy, not reference to local
}

// Dangerous - returning reference to local
int& getNumberBad() {
    int x = 5;
    return x;  // Error! x destroyed after function
}
```

### Mistake 5: Using Pass by Value When Modification Needed
```cpp
void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;  // Swaps copies, not originals
}

int main() {
    int x = 10, y = 20;
    swap(x, y);  // Does nothing!
    cout << x << ", " << y;  // Still 10, 20
    
    // Correct - use references
    return 0;
}
```

## Pass by Value vs Other Methods

| Aspect | Pass by Value | Pass by Reference | Pass by const Reference |
|--------|---------------|-------------------|------------------------|
| Syntax | `void f(int x)` | `void f(int &x)` | `void f(const int &x)` |
| Copy | Yes | No | No |
| Can modify | Yes (copy only) | Yes (original) | No |
| Performance | Copy cost | No copy | No copy |
| Safety | Very safe | Can modify original | Very safe |
| Use for | Small types, need copy | Need to modify | Large objects, read-only |

## Quick Reference

| Data Type | Pass by Value Behavior |
|-----------|------------------------|
| `int` | Copy created |
| `double` | Copy created |
| `char` | Copy created |
| `bool` | Copy created |
| `string` | Copy created (can be expensive) |
| `array` | Actually passes pointer (not value) |
| `struct` | Copy created |
| `class` | Copy created (calls copy constructor) |

## Summary

- **Pass by value** creates a copy of the argument
- Modifications inside function **do not affect** original
- Safe because original cannot be accidentally modified
- **Performance cost** for copying large objects
- Use for **small types** (int, double, char, etc.)
- Use for **functions that need a copy** to work with
- **Arrays** are not passed by value (they decay to pointers)
- **Strings, vectors, structures** can be expensive to copy
- Consider **const reference** for large read-only objects
- Use **reference** when you need to modify original

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Pass by value examples
int add(int a, int b) {
    return a + b;  // Returns sum, a and b are copies
}

string greet(string name) {
    return "Hello, " + name + "!";  // Returns new string
}

void demonstrateCopy(int x) {
    x = 100;  // Modifies copy only
    cout << "Inside function: x = " << x << endl;
}

int main() {
    int num = 5;
    string name = "John";
    
    cout << "add(5,3) = " << add(5, 3) << endl;
    cout << "greet('John') = " << greet(name) << endl;
    
    cout << "Before: num = " << num << endl;
    demonstrateCopy(num);
    cout << "After: num = " << num << endl;  // Still 5
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*