# 57 - Pass by Address (Pointer) in C++

## What is Pass by Address?
Pass by address means passing a pointer to a variable as an argument to a function. The function receives the memory address (pointer) of the variable, allowing it to access and modify the original variable indirectly through dereferencing.

## Basic Concept

```cpp
#include <iostream>
using namespace std;

void increment(int *ptr) {  // Receives pointer to int
    (*ptr)++;  // Dereference and increment
    cout << "Inside function: *ptr = " << *ptr << endl;
}

int main() {
    int num = 5;
    cout << "Before call: num = " << num << endl;
    
    increment(&num);  // Pass address of num
    
    cout << "After call: num = " << num << endl;  // Now 6
    
    return 0;
}
```

## Pass by Address vs Pass by Reference

```cpp
#include <iostream>
using namespace std;

// Pass by reference
void byReference(int &x) {
    x = 100;
}

// Pass by address (pointer)
void byAddress(int *x) {
    *x = 100;
}

int main() {
    int a = 10, b = 10;
    
    byReference(a);
    cout << "After byReference: a = " << a << endl;
    
    byAddress(&b);
    cout << "After byAddress: b = " << b << endl;
    
    return 0;
}
```

## Simple Examples with Different Types

### Integer Pointer
```cpp
#include <iostream>
using namespace std;

void modifyInt(int *ptr) {
    *ptr = 100;
    cout << "Inside: *ptr = " << *ptr << endl;
}

int main() {
    int num = 5;
    modifyInt(&num);
    cout << "Outside: num = " << num << endl;  // Now 100
    
    return 0;
}
```

### Double Pointer
```cpp
#include <iostream>
using namespace std;

void modifyDouble(double *ptr) {
    *ptr = 3.14159;
    cout << "Inside: *ptr = " << *ptr << endl;
}

int main() {
    double pi = 3.14;
    modifyDouble(&pi);
    cout << "Outside: pi = " << pi << endl;  // Now 3.14159
    
    return 0;
}
```

### Char Pointer
```cpp
#include <iostream>
using namespace std;

void modifyChar(char *ptr) {
    *ptr = 'Z';
    cout << "Inside: *ptr = " << *ptr << endl;
}

int main() {
    char letter = 'A';
    modifyChar(&letter);
    cout << "Outside: letter = " << letter << endl;  // Now 'Z'
    
    return 0;
}
```

## Pointer Parameters with Null Check

```cpp
#include <iostream>
using namespace std;

void safeIncrement(int *ptr) {
    if (ptr != nullptr) {
        (*ptr)++;
        cout << "Incremented to: " << *ptr << endl;
    } else {
        cout << "Null pointer - cannot increment" << endl;
    }
}

int main() {
    int num = 5;
    int *nullPtr = nullptr;
    
    safeIncrement(&num);     // Works
    safeIncrement(nullPtr);  // Safe - no crash
    
    cout << "num = " << num << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Swap Function (Using Pointers)
```cpp
#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swap(&x, &y);
    cout << "After swap: x = " << x << ", y = " << y << endl;
    
    return 0;
}
```

### Example 2: Multiple Return Values
```cpp
#include <iostream>
using namespace std;

void getMinMax(int arr[], int size, int *min, int *max) {
    *min = arr[0];
    *max = arr[0];
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

void getStats(int a, int b, int *sum, int *product, int *max) {
    *sum = a + b;
    *product = a * b;
    *max = (a > b) ? a : b;
}

int main() {
    int numbers[] = {45, 23, 78, 12, 89, 34};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int minVal, maxVal;
    
    getMinMax(numbers, size, &minVal, &maxVal);
    cout << "Min: " << minVal << ", Max: " << maxVal << endl;
    
    int sum, product, max;
    getStats(10, 5, &sum, &product, &max);
    cout << "Sum: " << sum << ", Product: " << product << ", Max: " << max << endl;
    
    return 0;
}
```

### Example 3: Modifying Array Elements
```cpp
#include <iostream>
using namespace std;

void doubleValue(int *ptr) {
    *ptr *= 2;
}

void squareValue(int *ptr) {
    *ptr = (*ptr) * (*ptr);
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    
    cout << "Original: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    for (int i = 0; i < 5; i++) {
        doubleValue(&numbers[i]);
    }
    
    cout << "Doubled: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    for (int i = 0; i < 5; i++) {
        squareValue(&numbers[i]);
    }
    
    cout << "Squared: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    return 0;
}
```

### Example 4: String Processing with Pointers
```cpp
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

void toUpperCase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

void toLowerCase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

void reverseString(char *str) {
    int len = strlen(str);
    char *start = str;
    char *end = str + len - 1;
    
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    char text[] = "Hello World";
    
    cout << "Original: " << text << endl;
    
    toUpperCase(text);
    cout << "Uppercase: " << text << endl;
    
    toLowerCase(text);
    cout << "Lowercase: " << text << endl;
    
    reverseString(text);
    cout << "Reversed: " << text << endl;
    
    return 0;
}
```

### Example 5: Dynamic Memory Allocation
```cpp
#include <iostream>
using namespace std;

void createArray(int **arr, int size, int value) {
    *arr = new int[size];
    for (int i = 0; i < size; i++) {
        (*arr)[i] = value;
    }
}

void resizeArray(int **arr, int oldSize, int newSize, int fillValue) {
    int *newArr = new int[newSize];
    
    // Copy old elements
    for (int i = 0; i < oldSize && i < newSize; i++) {
        newArr[i] = (*arr)[i];
    }
    
    // Fill remaining
    for (int i = oldSize; i < newSize; i++) {
        newArr[i] = fillValue;
    }
    
    delete[] *arr;
    *arr = newArr;
}

int main() {
    int *arr = nullptr;
    int size = 5;
    
    createArray(&arr, size, 42);
    
    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    resizeArray(&arr, size, 8, 99);
    size = 8;
    
    cout << "Resized: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;
    
    return 0;
}
```

## Pass by Address with const Pointers

```cpp
#include <iostream>
using namespace std;

// Pointer to const - cannot modify value
void printValue(const int *ptr) {
    cout << "Value: " << *ptr << endl;
    // *ptr = 100;  // ERROR! Cannot modify through const pointer
}

// Const pointer - cannot change pointer address
void modifyValue(int * const ptr) {
    *ptr = 100;  // Can modify value
    // ptr = nullptr;  // ERROR! Cannot change pointer
}

// Const pointer to const - neither can change
void readOnly(const int * const ptr) {
    cout << "Value: " << *ptr << endl;
    // *ptr = 100;  // ERROR!
    // ptr = nullptr;  // ERROR!
}

int main() {
    int num = 5;
    
    printValue(&num);
    modifyValue(&num);
    cout << "After modify: " << num << endl;
    readOnly(&num);
    
    return 0;
}
```

## Pointer Arithmetic in Functions

```cpp
#include <iostream>
using namespace std;

int sumArray(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);  // Pointer arithmetic
    }
    return sum;
}

void fillArray(int *arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        *(arr + i) = value;  // Pointer arithmetic
    }
}

int main() {
    int numbers[5];
    
    fillArray(numbers, 5, 10);
    
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    cout << "Sum: " << sumArray(numbers, 5) << endl;
    
    return 0;
}
```

## Pass by Address vs Pass by Reference Comparison

```cpp
#include <iostream>
using namespace std;

// Pass by reference
void byReference(int &x) {
    x = 100;
    // No need to check for null (references can't be null)
}

// Pass by address
void byAddress(int *x) {
    if (x != nullptr) {  // Must check for null
        *x = 100;
    }
}

int main() {
    int a = 10, b = 10;
    
    byReference(a);
    cout << "By reference: " << a << endl;
    
    byAddress(&b);
    cout << "By address: " << b << endl;
    
    // byAddress(nullptr);  // Safe with null check
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Dereferencing Null Pointer
```cpp
void increment(int *ptr) {
    // WRONG - no null check
    (*ptr)++;  // Will crash if ptr is null
}

// CORRECT
void increment(int *ptr) {
    if (ptr != nullptr) {
        (*ptr)++;
    }
}
```

### Mistake 2: Forgetting &
```cpp
void modify(int *ptr) {
    *ptr = 100;
}

int main() {
    int num = 5;
    
    // WRONG - passing value instead of address
    // modify(num);  // Error!
    
    // CORRECT
    modify(&num);
    
    return 0;
}
```

### Mistake 3: Returning Address of Local Variable
```cpp
// WRONG - returns address of local variable
int* getValue() {
    int x = 5;
    return &x;  // x destroyed after function ends!
}

// CORRECT - use dynamic allocation or static
int* getValue() {
    int *ptr = new int(5);
    return ptr;  // Must delete later
}
```

### Mistake 4: Confusing * in Declaration vs Dereference
```cpp
int x = 5;
int *ptr = &x;  // * in declaration means pointer

*ptr = 10;      // * in statement means dereference

void func(int *p) {  // * in parameter means pointer
    *p = 20;         // * here means dereference
}
```

### Mistake 5: Pointer Arithmetic Errors
```cpp
void process(int *arr, int size) {
    // WRONG - goes out of bounds
    for (int i = 0; i <= size; i++) {
        cout << *(arr + i) << " ";  // Accesses arr[size] (out of bounds)
    }
    
    // CORRECT
    for (int i = 0; i < size; i++) {
        cout << *(arr + i) << " ";
    }
}
```

## When to Use Pass by Address vs Reference

| Situation | Pass by Address | Pass by Reference |
|-----------|-----------------|-------------------|
| Need null check | ✅ Yes | ❌ No (can't be null) |
| Need to change pointer | ✅ Yes | ❌ No |
| C-style code | ✅ Common | ❌ Not available |
| C++ style code | ⚠️ Less common | ✅ Preferred |
| Array parameters | ✅ Common | ❌ Not directly |
| Simple modification | ⚠️ Verbose | ✅ Simple |
| Optional parameters | ✅ Using nullptr | ❌ No |

## Quick Reference

| Operation | Pass by Address | Pass by Reference |
|-----------|-----------------|-------------------|
| Parameter syntax | `void f(int *p)` | `void f(int &r)` |
| Call syntax | `f(&x)` | `f(x)` |
| Access inside | `*p = value` | `r = value` |
| Null check | `if (p)` | Not needed |
| Reassign parameter | `p = &y` | Not possible |
| Can be null | Yes | No |

## Summary

- **Pass by address** passes a pointer to the variable
- Function receives memory address, must dereference to access
- Requires **explicit null checks** for safety
- Useful for **optional parameters** (can pass nullptr)
- Allows **changing what the pointer points to**
- **C-style** approach (common in C code)
- **Pointer arithmetic** for array traversal
- More **verbose** than pass by reference
- **C++ prefers references** for most cases
- Essential for **dynamic memory allocation** functions

## Basic Template
```cpp
#include <iostream>
using namespace std;

// Pass by address examples
void increment(int *ptr) {
    if (ptr) (*ptr)++;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void getStats(int a, int b, int *sum, int *product, int *max) {
    *sum = a + b;
    *product = a * b;
    *max = (a > b) ? a : b;
}

void processArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        *(arr + i) *= 2;
    }
}

int main() {
    // Single variable
    int num = 5;
    increment(&num);
    cout << "After increment: " << num << endl;
    
    // Swap
    int x = 10, y = 20;
    swap(&x, &y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    // Multiple returns
    int sum, product, max;
    getStats(10, 5, &sum, &product, &max);
    cout << "Sum: " << sum << ", Product: " << product << ", Max: " << max << endl;
    
    // Array processing
    int numbers[] = {1, 2, 3, 4, 5};
    processArray(numbers, 5);
    cout << "Processed array: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*