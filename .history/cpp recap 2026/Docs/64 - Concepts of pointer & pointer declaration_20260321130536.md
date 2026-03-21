# 64 - Concepts of Pointer & Pointer Declaration in C++

## What is a Pointer?
A pointer is a variable that stores the memory address of another variable. Instead of holding a value directly, it holds the location where a value is stored. Think of it like a house address instead of the house itself.

## Memory Address Concept

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    
    cout << "Value: " << value << endl;
    cout << "Address of value: " << &value << endl;
    
    return 0;
}
```

## Pointer Declaration Syntax

```cpp
data_type *pointer_name;
```

```cpp
#include <iostream>
using namespace std;

int main() {
    int *intPtr;        // Pointer to integer
    double *doublePtr;  // Pointer to double
    char *charPtr;      // Pointer to character
    bool *boolPtr;      // Pointer to boolean
    
    cout << "Pointers declared but not initialized" << endl;
    
    return 0;
}
```

## Initializing Pointers

### Initializing with Address of Variable
```cpp
#include <iostream>
using namespace std;

int main() {
    int number = 10;
    int *ptr = &number;  // ptr stores address of number
    
    cout << "Value of number: " << number << endl;
    cout << "Address of number: " << &number << endl;
    cout << "Value stored in ptr: " << ptr << endl;
    cout << "Value pointed by ptr: " << *ptr << endl;
    
    return 0;
}
```

### Initializing with nullptr
```cpp
#include <iostream>
using namespace std;

int main() {
    int *ptr1 = nullptr;   // Modern C++ (recommended)
    int *ptr2 = NULL;      // Old style (C)
    int *ptr3 = 0;         // Also works but less clear
    
    if (ptr1 == nullptr) {
        cout << "ptr1 is a null pointer" << endl;
    }
    
    return 0;
}
```

## Dereferencing Pointers

The dereference operator `*` gives access to the value at the address stored in the pointer.

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int *ptr = &value;
    
    cout << "Original value: " << value << endl;
    cout << "Pointer points to: " << *ptr << endl;
    
    // Modify value through pointer
    *ptr = 100;
    
    cout << "After dereference modification: " << value << endl;
    
    return 0;
}
```

## Pointers with Different Data Types

### Integer Pointer
```cpp
#include <iostream>
using namespace std;

int main() {
    int num = 25;
    int *intPtr = &num;
    
    cout << "Integer: " << num << endl;
    cout << "Pointer value: " << intPtr << endl;
    cout << "Dereferenced: " << *intPtr << endl;
    
    *intPtr = 50;
    cout << "After change: " << num << endl;
    
    return 0;
}
```

### Double Pointer
```cpp
#include <iostream>
using namespace std;

int main() {
    double pi = 3.14159;
    double *doublePtr = &pi;
    
    cout << "Double: " << pi << endl;
    cout << "Pointer: " << doublePtr << endl;
    cout << "Dereferenced: " << *doublePtr << endl;
    
    *doublePtr = 2.71828;
    cout << "After change: " << pi << endl;
    
    return 0;
}
```

### Char Pointer
```cpp
#include <iostream>
using namespace std;

int main() {
    char letter = 'A';
    char *charPtr = &letter;
    
    cout << "Char: " << letter << endl;
    cout << "Pointer: " << (void*)charPtr << endl;  // Cast to print address
    cout << "Dereferenced: " << *charPtr << endl;
    
    *charPtr = 'Z';
    cout << "After change: " << letter << endl;
    
    return 0;
}
```

## Pointers to Arrays

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // arr is pointer to first element
    
    cout << "Array elements using pointer:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "*(ptr + " << i << ") = " << *(ptr + i) << endl;
    }
    
    cout << "\nArray name as pointer:" << endl;
    cout << "arr = " << arr << endl;
    cout << "&arr[0] = " << &arr[0] << endl;
    
    return 0;
}
```

## Pointers and Constants

### Pointer to Constant (Can't change value)
```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 10;
    const int *ptr = &value;  // Pointer to constant
    
    cout << "Value: " << *ptr << endl;
    
    // *ptr = 20;  // ERROR! Can't modify value through pointer
    
    value = 20;  // OK - can modify original variable
    
    cout << "After original modification: " << *ptr << endl;
    
    return 0;
}
```

### Constant Pointer (Can't change address)
```cpp
#include <iostream>
using namespace std;

int main() {
    int value1 = 10;
    int value2 = 20;
    int *const ptr = &value1;  // Constant pointer
    
    *ptr = 30;  // OK - can modify value
    // ptr = &value2;  // ERROR! Can't change address
    
    cout << "Value: " << *ptr << endl;
    
    return 0;
}
```

### Constant Pointer to Constant (Can't change either)
```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 10;
    const int *const ptr = &value;  // Constant pointer to constant
    
    // *ptr = 20;  // ERROR! Can't modify value
    // ptr = &value;  // ERROR! Can't change address
    
    cout << "Value: " << *ptr << endl;
    
    return 0;
}
```

## Pointer Size and Memory

```cpp
#include <iostream>
using namespace std;

int main() {
    int *intPtr;
    double *doublePtr;
    char *charPtr;
    
    cout << "Size of int pointer: " << sizeof(intPtr) << " bytes" << endl;
    cout << "Size of double pointer: " << sizeof(doublePtr) << " bytes" << endl;
    cout << "Size of char pointer: " << sizeof(charPtr) << " bytes" << endl;
    
    // All pointers are the same size (usually 8 bytes on 64-bit systems)
    
    return 0;
}
```

## Practical Examples

### Example 1: Swapping Values Using Pointers
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

### Example 2: Finding Max Element Using Pointers
```cpp
#include <iostream>
using namespace std;

int* findMax(int *arr, int size) {
    int *maxPtr = arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *maxPtr) {
            maxPtr = arr + i;
        }
    }
    return maxPtr;
}

int main() {
    int numbers[] = {45, 23, 78, 12, 89, 34};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int *max = findMax(numbers, size);
    
    cout << "Maximum value: " << *max << endl;
    cout << "Address of maximum: " << max << endl;
    
    return 0;
}
```

### Example 3: Pointer to Function
```cpp
#include <iostream>
using namespace std;

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
double divide(int a, int b) { return (double)a / b; }

int main() {
    // Pointer to function
    int (*operation)(int, int);
    
    operation = add;
    cout << "Add: " << operation(10, 5) << endl;
    
    operation = subtract;
    cout << "Subtract: " << operation(10, 5) << endl;
    
    operation = multiply;
    cout << "Multiply: " << operation(10, 5) << endl;
    
    return 0;
}
```

### Example 4: Dynamic Memory Allocation
```cpp
#include <iostream>
using namespace std;

int main() {
    // Single integer
    int *single = new int(42);
    cout << "Single integer: " << *single << endl;
    
    // Array of integers
    int *arr = new int[5];
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Clean up
    delete single;
    delete[] arr;
    
    return 0;
}
```

### Example 5: Pointer to Pointer (Double Pointer)
```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int *ptr = &value;
    int **doublePtr = &ptr;
    
    cout << "Value: " << value << endl;
    cout << "Pointer value: " << *ptr << endl;
    cout << "Double pointer dereferenced: " << **doublePtr << endl;
    
    cout << "\nAddresses:" << endl;
    cout << "Address of value: " << &value << endl;
    cout << "Address stored in ptr: " << ptr << endl;
    cout << "Address of ptr: " << &ptr << endl;
    cout << "Address stored in doublePtr: " << doublePtr << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Uninitialized Pointer
```cpp
int *ptr;  // Uninitialized - contains garbage address
*ptr = 10;  // DANGEROUS! Writing to random memory
```

### Mistake 2: Forgetting & When Assigning Address
```cpp
int value = 10;
int *ptr = value;  // WRONG - assigns value to pointer, not address

int *ptr = &value;  // CORRECT - assigns address
```

### Mistake 3: Dereferencing Null Pointer
```cpp
int *ptr = nullptr;
*ptr = 10;  // CRASH! Dereferencing null pointer
```

### Mistake 4: Memory Leak
```cpp
int *ptr = new int(10);
ptr = new int(20);  // Lost access to first memory - memory leak
delete ptr;  // Only deletes second allocation
```

### Mistake 5: Using After Delete
```cpp
int *ptr = new int(10);
delete ptr;
*ptr = 20;  // Undefined behavior - using deleted memory
```

## Pointer Operators Summary

| Operator | Name | Purpose |
|----------|------|---------|
| `&` | Address-of | Gets memory address of variable |
| `*` | Dereference | Gets value at address stored in pointer |
| `*` (declaration) | Pointer | Declares a pointer variable |
| `->` | Arrow | Access member through pointer |
| `new` | New | Allocates dynamic memory |
| `delete` | Delete | Deallocates dynamic memory |

## Quick Reference

| Declaration | Meaning |
|-------------|---------|
| `int *p;` | Pointer to integer |
| `int* p, q;` | p is pointer, q is int |
| `int *p, *q;` | Both are pointers |
| `int *p = &x;` | Pointer to x |
| `int *p = nullptr;` | Null pointer |
| `const int *p;` | Pointer to constant int |
| `int *const p;` | Constant pointer to int |
| `int **p;` | Pointer to pointer to int |

## Summary

- **Pointer** stores memory address of another variable
- Declare with `*`: `int *ptr;`
- Get address with `&`: `ptr = &variable;`
- Dereference with `*`: `*ptr = value;`
- Always **initialize pointers** before use
- **nullptr** represents pointer pointing to nothing
- Pointers of all types have same size
- Used for **dynamic memory**, **arrays**, **function parameters**
- **Pointers to pointers** for multi-level indirection
- Must **delete** dynamically allocated memory

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    // Basic pointer declaration
    int value = 42;
    int *ptr = &value;
    
    cout << "Value: " << value << endl;
    cout << "Address: " << &value << endl;
    cout << "Pointer: " << ptr << endl;
    cout << "Dereferenced: " << *ptr << endl;
    
    // Modify through pointer
    *ptr = 100;
    cout << "Modified value: " << value << endl;
    
    // Null pointer
    int *nullPtr = nullptr;
    if (nullPtr == nullptr) {
        cout << "Null pointer" << endl;
    }
    
    // Pointer to array
    int arr[3] = {1, 2, 3};
    int *arrPtr = arr;
    
    cout << "Array through pointer: ";
    for (int i = 0; i < 3; i++) {
        cout << *(arrPtr + i) << " ";
    }
    cout << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*