# 56 - Pass by Reference in C++

## What is Pass by Reference?
Pass by reference means that when you pass an argument to a function, the function receives a **reference** to the original variable, not a copy. Any modifications made to the parameter inside the function **affect the original variable**.

## Basic Concept

```cpp
#include <iostream>
using namespace std;

void increment(int &x) {  // & indicates reference parameter
    x++;  // Modifies the original variable
    cout << "Inside function: x = " << x << endl;
}

int main() {
    int num = 5;
    cout << "Before call: num = " << num << endl;
    
    increment(num);  // Passes reference to num
    
    cout << "After call: num = " << num << endl;  // Now 6!
    
    return 0;
}
```

## How Pass by Reference Works

```cpp
#include <iostream>
using namespace std;

void modifyValue(int &value) {
    cout << "Inside function - before: " << value << endl;
    value = 100;  // Changes the original variable
    cout << "Inside function - after: " << value << endl;
}

int main() {
    int original = 10;
    
    cout << "Before function call: original = " << original << endl;
    
    modifyValue(original);  // Reference to original is passed
    
    cout << "After function call: original = " << original << endl;  // Now 100!
    
    return 0;
}
```

## Pass by Reference with Different Data Types

### Integer
```cpp
#include <iostream>
using namespace std;

void modifyInt(int &x) {
    x = 100;
    cout << "Inside: x = " << x << endl;
}

int main() {
    int num = 5;
    modifyInt(num);
    cout << "Outside: num = " << num << endl;  // Now 100
    
    return 0;
}
```

### Double
```cpp
#include <iostream>
using namespace std;

void modifyDouble(double &d) {
    d = 3.14159;
    cout << "Inside: d = " << d << endl;
}

int main() {
    double pi = 3.14;
    modifyDouble(pi);
    cout << "Outside: pi = " << pi << endl;  // Now 3.14159
    
    return 0;
}
```

### Char
```cpp
#include <iostream>
using namespace std;

void modifyChar(char &c) {
    c = 'Z';
    cout << "Inside: c = " << c << endl;
}

int main() {
    char letter = 'A';
    modifyChar(letter);
    cout << "Outside: letter = " << letter << endl;  // Now 'Z'
    
    return 0;
}
```

### Boolean
```cpp
#include <iostream>
using namespace std;

void modifyBool(bool &b) {
    b = true;
    cout << "Inside: b = " << boolalpha << b << endl;
}

int main() {
    bool flag = false;
    modifyBool(flag);
    cout << "Outside: flag = " << boolalpha << flag << endl;  // Now true
    
    return 0;
}
```

## Pass by Reference with Strings

```cpp
#include <iostream>
#include <string>
using namespace std;

void modifyString(string &s) {
    s = "Modified";
    cout << "Inside: s = " << s << endl;
}

int main() {
    string text = "Hello";
    modifyString(text);
    cout << "Outside: text = " << text << endl;  // Now "Modified"
    
    return 0;
}
```

## Pass by Reference with Arrays

```cpp
#include <iostream>
using namespace std;

// Arrays are automatically passed by reference (as pointers)
void modifyArray(int arr[], int size) {
    arr[0] = 100;  // Modifies original array
    cout << "Inside array[0]: " << arr[0] << endl;
}

int main() {
    int numbers[3] = {1, 2, 3};
    cout << "Before: numbers[0] = " << numbers[0] << endl;
    
    modifyArray(numbers, 3);
    
    cout << "After: numbers[0] = " << numbers[0] << endl;  // Now 100
    
    return 0;
}
```

## Pass by Reference with Structures

```cpp
#include <iostream>
#include <string>
using namespace std;

struct Person {
    string name;
    int age;
};

void modifyPerson(Person &p) {
    p.name = "Modified";
    p.age = 99;
    cout << "Inside: " << p.name << ", " << p.age << endl;
}

int main() {
    Person john = {"John", 25};
    
    cout << "Before: " << john.name << ", " << john.age << endl;
    modifyPerson(john);
    cout << "After: " << john.name << ", " << john.age << endl;  // Now modified
    
    return 0;
}
```

## Pass by Reference with Classes

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

void modifyStudent(Student &s) {
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
    john.display();  // Now modified!
    
    return 0;
}
```

## Practical Examples

### Example 1: Swap Function
```cpp
#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;
    
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swap(x, y);
    cout << "After swap: x = " << x << ", y = " << y << endl;
    
    return 0;
}
```

### Example 2: Multiple Return Values
```cpp
#include <iostream>
#include <cmath>
using namespace std;

void getStats(int a, int b, int &sum, int &product, int &max) {
    sum = a + b;
    product = a * b;
    max = (a > b) ? a : b;
}

void minMax(int arr[], int size, int &min, int &max) {
    min = arr[0];
    max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
}

int main() {
    int s, p, m;
    getStats(10, 5, s, p, m);
    cout << "Sum: " << s << ", Product: " << p << ", Max: " << m << endl;
    
    int numbers[] = {45, 23, 78, 12, 89, 34};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int minVal, maxVal;
    minMax(numbers, size, minVal, maxVal);
    cout << "Min: " << minVal << ", Max: " << maxVal << endl;
    
    return 0;
}
```

### Example 3: Increment Functions
```cpp
#include <iostream>
using namespace std;

void increment(int &x) {
    x++;
}

void incrementBy(int &x, int amount) {
    x += amount;
}

void multiplyBy(int &x, int factor) {
    x *= factor;
}

int main() {
    int value = 5;
    
    cout << "Initial: " << value << endl;
    
    increment(value);
    cout << "After increment: " << value << endl;
    
    incrementBy(value, 3);
    cout << "After +3: " << value << endl;
    
    multiplyBy(value, 2);
    cout << "After ×2: " << value << endl;
    
    return 0;
}
```

### Example 4: String Processing (Modifying Original)
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void toUpperCase(string &s) {
    for (char &c : s) {
        c = toupper(c);
    }
}

void toLowerCase(string &s) {
    for (char &c : s) {
        c = tolower(c);
    }
}

void reverse(string &s) {
    int n = s.length();
    for (int i = 0; i < n / 2; i++) {
        swap(s[i], s[n - 1 - i]);
    }
}

void removeSpaces(string &s) {
    string result;
    for (char c : s) {
        if (c != ' ') {
            result += c;
        }
    }
    s = result;
}

int main() {
    string text = "Hello World";
    
    cout << "Original: " << text << endl;
    
    toUpperCase(text);
    cout << "Uppercase: " << text << endl;
    
    toLowerCase(text);
    cout << "Lowercase: " << text << endl;
    
    reverse(text);
    cout << "Reversed: " << text << endl;
    
    text = "Hello World";
    removeSpaces(text);
    cout << "No spaces: " << text << endl;
    
    return 0;
}
```

### Example 5: Array Processing (Modifying Original)
```cpp
#include <iostream>
using namespace std;

void doubleArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        swap(arr[i], arr[size - 1 - i]);
    }
}

void fillArray(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Original: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    doubleArray(numbers, size);
    cout << "Doubled: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    reverseArray(numbers, size);
    cout << "Reversed: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    fillArray(numbers, size, 99);
    cout << "Filled with 99: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    return 0;
}
```

## Pass by Reference vs Pass by Value

```cpp
#include <iostream>
using namespace std;

// Pass by value - copy
void byValue(int x) {
    x = 100;
    cout << "byValue inside: " << x << endl;
}

// Pass by reference - original
void byReference(int &x) {
    x = 100;
    cout << "byReference inside: " << x << endl;
}

int main() {
    int a = 10, b = 10;
    
    cout << "Before byValue: a = " << a << endl;
    byValue(a);
    cout << "After byValue: a = " << a << endl;  // Still 10
    
    cout << "\nBefore byReference: b = " << b << endl;
    byReference(b);
    cout << "After byReference: b = " << b << endl;  // Now 100
    
    return 0;
}
```

## Pass by Reference with const

```cpp
#include <iostream>
#include <string>
using namespace std;

// const reference - read-only, no copy
void printMessage(const string &msg) {
    cout << msg << endl;
    // msg = "New";  // ERROR! Can't modify const reference
}

// Reference - can modify
void modifyMessage(string &msg) {
    msg = "Modified";
}

int main() {
    string text = "Hello World";
    
    printMessage(text);      // Read-only, efficient
    modifyMessage(text);     // Modifies original
    printMessage(text);      // Prints "Modified"
    
    return 0;
}
```

## Performance Comparison

```cpp
#include <iostream>
#include <string>
#include <chrono>
using namespace std;

// Pass by value (copies large object)
void processByValue(string s) {
    // Do nothing
}

// Pass by reference (no copy)
void processByReference(string &s) {
    // Do nothing
}

// Pass by const reference (no copy, read-only)
void processByConstRef(const string &s) {
    // Do nothing
}

int main() {
    string largeText(1000000, 'X');  // 1 million characters
    
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        processByValue(largeText);  // Copies each time
    }
    auto end = chrono::high_resolution_clock::now();
    auto valueTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        processByReference(largeText);  // No copy
    }
    end = chrono::high_resolution_clock::now();
    auto refTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        processByConstRef(largeText);  // No copy
    }
    end = chrono::high_resolution_clock::now();
    auto constRefTime = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Pass by value time: " << valueTime.count() << " ms" << endl;
    cout << "Pass by reference time: " << refTime.count() << " ms" << endl;
    cout << "Pass by const reference time: " << constRefTime.count() << " ms" << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Missing & in Parameter
```cpp
// WRONG - passes by value, won't modify original
void increment(int x) {
    x++;
}

// CORRECT - passes by reference
void increment(int &x) {
    x++;
}
```

### Mistake 2: Passing Literal to Non-const Reference
```cpp
void modify(int &x) {
    x = 100;
}

int main() {
    // WRONG - cannot pass literal to non-const reference
    // modify(5);  // Error!
    
    // CORRECT - pass variable
    int num = 5;
    modify(num);
    
    // For literals, use const reference
    return 0;
}
```

### Mistake 3: Returning Reference to Local Variable
```cpp
// WRONG - returns reference to destroyed local
int& getValue() {
    int x = 5;
    return x;  // Error! x destroyed after function
}

// CORRECT - return by value
int getValue() {
    int x = 5;
    return x;
}
```

### Mistake 4: Not Using const When Needed
```cpp
// WRONG - should be const if not modifying
void printArray(int arr[], int size) {  // Should be const int[]
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}

// CORRECT - indicates no modification
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}
```

### Mistake 5: Confusing & in Declaration vs Usage
```cpp
int x = 5;
int &ref = x;  // & in declaration means reference

void func(int &x) {  // & in parameter means reference
    x++;  // Modifies original
}

// & in expression is address-of operator
int *ptr = &x;  // & here means address of
```

## When to Use Pass by Reference

### ✅ Good Uses
```cpp
// Need to modify original
void increment(int &x);

// Return multiple values
void getStats(int arr[], int size, int &sum, int &avg);

// Swap values
void swap(int &a, int &b);

// Large objects (efficiency)
void processData(vector<int> &data);

// Avoid copying large objects
void displayPerson(const Person &p);
```

### ❌ Poor Uses
```cpp
// Simple types - pass by value is fine
void increment(int &x);  // For int, pass by value is simpler

// When you don't modify - use const reference
void print(const string &s);  // Good - no copy, read-only

// Returning multiple values - consider using struct
void getValues(int &a, int &b, int &c, int &d);  // Hard to read
```

## Quick Reference

| Aspect | Pass by Value | Pass by Reference | Pass by const Reference |
|--------|---------------|-------------------|------------------------|
| Syntax | `void f(int x)` | `void f(int &x)` | `void f(const int &x)` |
| Copy | Yes | No | No |
| Can modify | Copy only | Original | No |
| Performance | Copy cost | No copy | No copy |
| Use for | Small types | Need modification | Large read-only objects |
| Literals | Allowed | Not allowed | Allowed |

## Summary

- **Pass by reference** allows function to modify original variables
- Uses `&` in parameter declaration
- No copy is made (efficient for large objects)
- Can return **multiple values** through reference parameters
- Use **const reference** for large read-only objects
- Cannot pass literals to non-const references
- Essential for **swap**, **modification**, **multiple return** functions
- **Arrays** are automatically passed by reference
- More efficient than pass by value for large objects
- Must be careful about **lifetime** of referenced objects

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Pass by reference examples
void increment(int &x) {
    x++;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void toUpperCase(string &s) {
    for (char &c : s) {
        c = toupper(c);
    }
}

void getMinMax(int arr[], int size, int &min, int &max) {
    min = arr[0];
    max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
}

int main() {
    // Single variable modification
    int num = 5;
    cout << "Before: " << num << endl;
    increment(num);
    cout << "After: " << num << endl;
    
    // Swapping
    int x = 10, y = 20;
    cout << "\nBefore swap: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    // String modification
    string text = "hello";
    cout << "\nBefore: " << text << endl;
    toUpperCase(text);
    cout << "After: " << text << endl;
    
    // Multiple return values
    int numbers[] = {45, 23, 78, 12, 89};
    int minVal, maxVal;
    getMinMax(numbers, 5, minVal, maxVal);
    cout << "\nMin: " << minVal << ", Max: " << maxVal << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*