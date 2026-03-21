# 70 - Pointers to Pointers in C++

## What is a Pointer to Pointer?
A pointer to pointer (also called double pointer) is a pointer that stores the address of another pointer. It provides an additional level of indirection, allowing you to modify pointer variables themselves.

## Basic Concept

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* ptr = &value;      // Pointer to int
    int** doublePtr = &ptr;  // Pointer to pointer to int
    
    cout << "Value: " << value << endl;
    cout << "Address of value: " << &value << endl;
    cout << "ptr holds: " << ptr << endl;
    cout << "Address of ptr: " << &ptr << endl;
    cout << "doublePtr holds: " << doublePtr << endl;
    cout << "*doublePtr = " << *doublePtr << endl;
    cout << "**doublePtr = " << **doublePtr << endl;
    
    return 0;
}
```

## Visual Representation

```
Memory Layout:

Variable 'value':
┌─────────────┐
│   Address   │ 0x1000
├─────────────┤
│   Value     │ 42
└─────────────┘

Pointer 'ptr':
┌─────────────┐
│   Address   │ 0x2000
├─────────────┤
│   Value     │ 0x1000  (stores address of value)
└─────────────┘

Double Pointer 'doublePtr':
┌─────────────┐
│   Address   │ 0x3000
├─────────────┤
│   Value     │ 0x2000  (stores address of ptr)
└─────────────┘

Relationships:
doublePtr → ptr → value
**doublePtr = 42
```

## Declaring Pointers to Pointers

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 10;
    
    // Single pointer
    int* ptr = &value;
    
    // Pointer to pointer
    int** ptr2 = &ptr;
    
    // Pointer to pointer to pointer
    int*** ptr3 = &ptr2;
    
    cout << "Value: " << value << endl;
    cout << "*ptr: " << *ptr << endl;
    cout << "**ptr2: " << **ptr2 << endl;
    cout << "***ptr3: " << ***ptr3 << endl;
    
    // All print 10
    
    return 0;
}
```

## Modifying Through Multiple Levels

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;
    int* ptr = &a;
    int** doublePtr = &ptr;
    
    cout << "Initially: a = " << a << ", b = " << b << endl;
    cout << "*ptr = " << *ptr << endl;
    
    // Change value through double pointer
    **doublePtr = 100;
    cout << "\nAfter **doublePtr = 100: a = " << a << endl;
    
    // Change what ptr points to
    *doublePtr = &b;
    cout << "\nAfter *doublePtr = &b:" << endl;
    cout << "*ptr = " << *ptr << endl;  // Now points to b
    cout << "a = " << a << ", b = " << b << endl;
    
    // Change value through new pointer
    **doublePtr = 200;
    cout << "\nAfter **doublePtr = 200:" << endl;
    cout << "b = " << b << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Modifying Pointer in Function
```cpp
#include <iostream>
using namespace std;

// This does NOT modify the original pointer
void badModify(int* ptr) {
    int x = 100;
    ptr = &x;  // Only modifies local copy
}

// This modifies the original pointer
void goodModify(int** ptr) {
    int x = 100;
    *ptr = &x;  // Modifies the original pointer
}

// But careful - x is local, so this is dangerous!
void dangerousModify(int** ptr) {
    int x = 100;  // Local variable
    *ptr = &x;    // ptr now points to local variable!
}

// Safe version with dynamic allocation
void safeModify(int** ptr) {
    *ptr = new int(100);  // Allocate on heap
}

int main() {
    int* ptr = nullptr;
    
    badModify(ptr);
    cout << "After badModify: ptr = " << ptr << endl;
    
    // Dangerous version - don't do this!
    // dangerousModify(&ptr);
    // cout << "After dangerousModify: *ptr = " << *ptr << endl;  // Undefined!
    
    safeModify(&ptr);
    if (ptr != nullptr) {
        cout << "After safeModify: *ptr = " << *ptr << endl;
        delete ptr;
    }
    
    return 0;
}
```

### Example 2: Dynamic 2D Array Allocation
```cpp
#include <iostream>
using namespace std;

int** create2DArray(int rows, int cols) {
    // Allocate array of pointers (rows)
    int** arr = new int*[rows];
    
    // Allocate each row
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            arr[i][j] = i * cols + j + 1;
        }
    }
    
    return arr;
}

void print2DArray(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

void delete2DArray(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main() {
    int rows = 3, cols = 4;
    
    int** matrix = create2DArray(rows, cols);
    
    cout << "2D Array:" << endl;
    print2DArray(matrix, rows, cols);
    
    delete2DArray(matrix, rows);
    
    return 0;
}
```

### Example 3: Resizing Dynamic Arrays
```cpp
#include <iostream>
using namespace std;

void resizeArray(int** arr, int oldSize, int newSize) {
    int* newArr = new int[newSize];
    
    // Copy old elements
    for (int i = 0; i < oldSize && i < newSize; i++) {
        newArr[i] = (*arr)[i];
    }
    
    // Fill remaining
    for (int i = oldSize; i < newSize; i++) {
        newArr[i] = 0;
    }
    
    delete[] *arr;
    *arr = newArr;
}

int main() {
    int size = 5;
    int* arr = new int[size];
    
    // Initialize
    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;
    }
    
    cout << "Original array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Resize larger
    resizeArray(&arr, size, 8);
    size = 8;
    
    cout << "After resize (larger): ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Resize smaller
    resizeArray(&arr, size, 3);
    size = 3;
    
    cout << "After resize (smaller): ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;
    
    return 0;
}
```

### Example 4: Array of Pointers
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Array of pointers to int
    int a = 10, b = 20, c = 30;
    int* arr[3] = {&a, &b, &c};
    
    cout << "Array of pointers:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "arr[" << i << "] points to: " << *arr[i] << endl;
    }
    
    // Modify through pointer array
    *arr[1] = 200;
    cout << "\nAfter modification: b = " << b << endl;
    
    // Array of strings using pointers
    string* names[3];
    names[0] = new string("Alice");
    names[1] = new string("Bob");
    names[2] = new string("Charlie");
    
    cout << "\nNames: ";
    for (int i = 0; i < 3; i++) {
        cout << *names[i] << " ";
    }
    cout << endl;
    
    // Clean up
    for (int i = 0; i < 3; i++) {
        delete names[i];
    }
    
    return 0;
}
```

### Example 5: Command Line Arguments (argv)
```cpp
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    // argv is a pointer to an array of C-strings
    // char* argv[] = pointer to array of pointers to char
    
    cout << "Program name: " << argv[0] << endl;
    cout << "Number of arguments: " << argc - 1 << endl;
    
    for (int i = 1; i < argc; i++) {
        cout << "argv[" << i << "] = " << argv[i] << endl;
    }
    
    // Using pointer arithmetic
    cout << "\nUsing pointer arithmetic:" << endl;
    char** ptr = argv;
    for (int i = 0; i < argc; i++) {
        cout << "Argument " << i << ": " << *(ptr + i) << endl;
    }
    
    return 0;
}
```

## Pointers to Pointers with Strings

```cpp
#include <iostream>
#include <cstring>
using namespace std;

void modifyString(char** ptr) {
    *ptr = new char[20];
    strcpy(*ptr, "Modified");
}

int main() {
    char* text = new char[20];
    strcpy(text, "Original");
    
    cout << "Before: " << text << endl;
    
    modifyString(&text);
    
    cout << "After: " << text << endl;
    
    delete[] text;
    
    return 0;
}
```

## Multi-Level Pointers

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* ptr1 = &value;
    int** ptr2 = &ptr1;
    int*** ptr3 = &ptr2;
    
    cout << "Original value: " << value << endl;
    cout << "*ptr1: " << *ptr1 << endl;
    cout << "**ptr2: " << **ptr2 << endl;
    cout << "***ptr3: " << ***ptr3 << endl;
    
    // Modify through different levels
    ***ptr3 = 100;
    cout << "\nAfter ***ptr3 = 100: value = " << value << endl;
    
    **ptr2 = 200;
    cout << "After **ptr2 = 200: value = " << value << endl;
    
    *ptr1 = 300;
    cout << "After *ptr1 = 300: value = " << value << endl;
    
    return 0;
}
```

## Pointer to Pointer to Array

```cpp
#include <iostream>
using namespace std;

int main() {
    // Array of integers
    int arr[] = {10, 20, 30, 40, 50};
    
    // Pointer to array
    int (*ptrToArray)[5] = &arr;
    
    // Pointer to pointer to array
    int (**doublePtr)[5] = &ptrToArray;
    
    cout << "arr[2] = " << arr[2] << endl;
    cout << "(*ptrToArray)[2] = " << (*ptrToArray)[2] << endl;
    cout << "(**doublePtr)[2] = " << (**doublePtr)[2] << endl;
    
    // Modify through double pointer
    (**doublePtr)[2] = 300;
    cout << "\nAfter modification: arr[2] = " << arr[2] << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Wrong Number of Dereferences
```cpp
int value = 10;
int* ptr = &value;
int** dptr = &ptr;

cout << *dptr;   // WRONG - prints address, not value
cout << **dptr;  // CORRECT - prints 10
```

### Mistake 2: Forgetting & When Taking Address of Pointer
```cpp
int* ptr = nullptr;
void modify(int** p) {
    *p = new int(10);
}

// WRONG - passing pointer, not address of pointer
// modify(ptr);  // Won't modify ptr

// CORRECT
modify(&ptr);  // Passes address of ptr
```

### Mistake 3: Dangling Pointer
```cpp
int** createBad() {
    int x = 10;
    int* ptr = &x;
    return &ptr;  // DANGEROUS! ptr is local
}

// CORRECT - use static or dynamic allocation
int** createGood() {
    static int* ptr = nullptr;
    ptr = new int(10);
    return &ptr;  // Safe if properly managed
}
```

### Mistake 4: Memory Leak with Double Pointers
```cpp
int** arr = new int*[10];
for (int i = 0; i < 10; i++) {
    arr[i] = new int[5];
}
// Forgot to delete! Memory leak

// Correct cleanup
for (int i = 0; i < 10; i++) {
    delete[] arr[i];
}
delete[] arr;
```

### Mistake 5: Confusing Pointer Types
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;
int** dptr = &ptr;  // OK - pointer to pointer to int

// WRONG - can't assign pointer to array to double pointer
// int** wrong = &arr;  // Error! &arr is pointer to array of 5 ints
```

## Quick Reference Table

| Declaration | Meaning | Dereference |
|-------------|---------|-------------|
| `int* ptr` | Pointer to int | `*ptr` gives int |
| `int** dptr` | Pointer to pointer to int | `**dptr` gives int |
| `int*** tptr` | Pointer to pointer to pointer to int | `***tptr` gives int |
| `int* arr[5]` | Array of 5 pointers to int | `*arr[0]` gives int |
| `int (*ptr)[5]` | Pointer to array of 5 ints | `(*ptr)[0]` gives int |

## Summary

- **Pointer to pointer** stores address of another pointer
- Provides **double indirection** for modifying pointers
- Essential for **dynamic 2D arrays**
- Used in **functions that need to modify pointers**
- **argv** is a pointer to array of pointers
- **Triple pointers** (and beyond) possible but rarely needed
- Must **manage memory** carefully with nested pointers
- **Dereference carefully** - each level needs one `*`

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    // Basic double pointer
    int value = 42;
    int* ptr = &value;
    int** dptr = &ptr;
    
    cout << "Value: " << value << endl;
    cout << "*ptr: " << *ptr << endl;
    cout << "**dptr: " << **dptr << endl;
    
    // Modify through double pointer
    **dptr = 100;
    cout << "\nAfter **dptr = 100: value = " << value << endl;
    
    // Change pointer through double pointer
    int newValue = 200;
    *dptr = &newValue;
    cout << "After *dptr = &newValue: *ptr = " << *ptr << endl;
    
    // Dynamic 2D array
    int rows = 3, cols = 4;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }
    
    cout << "\n2D Array:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    // Clean up
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*