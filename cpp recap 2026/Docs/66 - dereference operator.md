# 66 - Dereference Operator (*) in C++

## What is the Dereference Operator?
The dereference operator `*` is used to access the value stored at the memory address held by a pointer. It "follows" the pointer to get to the actual data.

## Basic Syntax

```cpp
*pointer_name
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* ptr = &value;  // ptr holds address of value
    
    cout << "Value: " << value << endl;
    cout << "Address: " << &value << endl;
    cout << "Pointer holds: " << ptr << endl;
    cout << "Dereferenced pointer: " << *ptr << endl;
    
    return 0;
}
```

## The Confusing Part: `*` in Different Contexts

The asterisk `*` has different meanings in different contexts:

| Context | Meaning | Example |
|---------|---------|---------|
| Multiplication | Arithmetic operation | `x = a * b;` |
| Pointer declaration | "is a pointer to" | `int* ptr;` |
| Dereference | "value at address" | `*ptr = 10;` |

## Dereference in Action

### Reading Value Through Pointer

```cpp
#include <iostream>
using namespace std;

int main() {
    int num = 100;
    int* ptr = &num;
    
    // Reading value using dereference
    int value = *ptr;
    
    cout << "Original: " << num << endl;
    cout << "Through pointer: " << value << endl;
    
    return 0;
}
```

### Modifying Value Through Pointer

```cpp
#include <iostream>
using namespace std;

int main() {
    int score = 85;
    int* ptr = &score;
    
    cout << "Original score: " << score << endl;
    
    // Modify through pointer
    *ptr = 95;
    
    cout << "After dereference: " << score << endl;
    
    // Another modification
    (*ptr) += 5;
    
    cout << "After addition: " << score << endl;
    
    return 0;
}
```

## Dereference with Different Data Types

### Integer Pointer
```cpp
#include <iostream>
using namespace std;

int main() {
    int num = 42;
    int* ptr = &num;
    
    cout << "int value: " << *ptr << endl;
    *ptr = 100;
    cout << "Modified: " << *ptr << endl;
    
    return 0;
}
```

### Double Pointer
```cpp
#include <iostream>
using namespace std;

int main() {
    double pi = 3.14159;
    double* ptr = &pi;
    
    cout << "double value: " << *ptr << endl;
    *ptr = 2.71828;
    cout << "Modified: " << *ptr << endl;
    
    return 0;
}
```

### Char Pointer
```cpp
#include <iostream>
using namespace std;

int main() {
    char letter = 'A';
    char* ptr = &letter;
    
    cout << "char value: " << *ptr << endl;
    *ptr = 'Z';
    cout << "Modified: " << *ptr << endl;
    
    return 0;
}
```

### Boolean Pointer
```cpp
#include <iostream>
using namespace std;

int main() {
    bool flag = false;
    bool* ptr = &flag;
    
    cout << boolalpha;
    cout << "bool value: " << *ptr << endl;
    *ptr = true;
    cout << "Modified: " << *ptr << endl;
    
    return 0;
}
```

## Dereference with Arrays

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // Points to first element
    
    cout << "Using array indexing:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    cout << "Using pointer dereference:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
    
    // Modify through pointer
    *(ptr + 2) = 300;
    cout << "After modification arr[2]: " << arr[2] << endl;
    
    return 0;
}
```

## Dereference with Pointer Arithmetic

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    cout << "Pointer arithmetic demonstration:" << endl;
    cout << "*ptr = " << *ptr << endl;           // arr[0]
    cout << "*(ptr + 1) = " << *(ptr + 1) << endl; // arr[1]
    cout << "*(ptr + 2) = " << *(ptr + 2) << endl; // arr[2]
    
    // Moving pointer
    ptr++;  // Now points to arr[1]
    cout << "\nAfter ptr++:" << endl;
    cout << "*ptr = " << *ptr << endl;
    
    ptr += 2;  // Now points to arr[3]
    cout << "After ptr += 2:" << endl;
    cout << "*ptr = " << *ptr << endl;
    
    return 0;
}
```

## Double Dereference (Pointer to Pointer)

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* ptr = &value;
    int** doublePtr = &ptr;
    
    cout << "Value: " << value << endl;
    cout << "*ptr: " << *ptr << endl;
    cout << "**doublePtr: " << **doublePtr << endl;
    
    // Modify through double pointer
    **doublePtr = 100;
    cout << "\nAfter **doublePtr = 100:" << endl;
    cout << "value: " << value << endl;
    
    // Change what ptr points to through double pointer
    int newValue = 200;
    *doublePtr = &newValue;
    cout << "\nAfter *doublePtr = &newValue:" << endl;
    cout << "*ptr: " << *ptr << endl;
    cout << "newValue: " << newValue << endl;
    
    return 0;
}
```

## Dereference with Functions

### Passing Pointer to Function
```cpp
#include <iostream>
using namespace std;

void increment(int* ptr) {
    (*ptr)++;  // Dereference and increment
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    
    cout << "Before increment: " << x << endl;
    increment(&x);
    cout << "After increment: " << x << endl;
    
    cout << "\nBefore swap: x=" << x << ", y=" << y << endl;
    swap(&x, &y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    return 0;
}
```

### Returning Pointer from Function
```cpp
#include <iostream>
using namespace std;

int* getMax(int* a, int* b) {
    if (*a > *b) {
        return a;  // Return pointer to larger
    } else {
        return b;
    }
}

int main() {
    int x = 10, y = 20;
    
    int* maxPtr = getMax(&x, &y);
    cout << "Max value: " << *maxPtr << endl;
    
    // Modify through returned pointer
    *maxPtr = 100;
    cout << "After modification: x=" << x << ", y=" << y << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Finding Maximum in Array Using Pointers
```cpp
#include <iostream>
using namespace std;

int* findMax(int* arr, int size) {
    int* maxPtr = arr;
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
    
    int* max = findMax(numbers, size);
    cout << "Maximum value: " << *max << endl;
    cout << "Position: " << (max - numbers) << endl;
    
    // Modify through pointer
    *max = 999;
    cout << "After modification: " << numbers[4] << endl;
    
    return 0;
}
```

### Example 2: Reversing Array Using Pointers
```cpp
#include <iostream>
using namespace std;

void reverseArray(int* start, int* end) {
    while (start < end) {
        // Swap values using pointers
        int temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Original: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    reverseArray(arr, arr + size - 1);
    
    cout << "Reversed: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 3: String Manipulation with Pointers
```cpp
#include <iostream>
#include <cstring>
using namespace std;

void toUpperCase(char* str) {
    while (*str) {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 32;  // Convert to uppercase
        }
        str++;
    }
}

int stringLength(const char* str) {
    int length = 0;
    while (*str) {
        length++;
        str++;
    }
    return length;
}

int main() {
    char text[] = "Hello World";
    
    cout << "Original: " << text << endl;
    cout << "Length: " << stringLength(text) << endl;
    
    toUpperCase(text);
    cout << "Uppercase: " << text << endl;
    
    return 0;
}
```

### Example 4: Dynamic Memory with Dereference
```cpp
#include <iostream>
using namespace std;

int main() {
    // Single integer
    int* num = new int(42);
    cout << "Value: " << *num << endl;
    *num = 100;
    cout << "Modified: " << *num << endl;
    delete num;
    
    // Array
    int* arr = new int[5];
    for (int i = 0; i < 5; i++) {
        *(arr + i) = i * 10;
    }
    
    cout << "\nArray values: ";
    for (int i = 0; i < 5; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
    
    delete[] arr;
    
    return 0;
}
```

### Example 5: Linked List with Dereference
```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    // Create nodes
    Node* head = new Node{10, nullptr};
    Node* second = new Node{20, nullptr};
    Node* third = new Node{30, nullptr};
    
    // Link nodes
    head->next = second;
    second->next = third;
    
    // Traverse using dereference
    cout << "Linked List: ";
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
    
    // Modify through pointer
    head->data = 100;
    cout << "After modification: " << head->data << endl;
    
    // Clean up
    delete head;
    delete second;
    delete third;
    
    return 0;
}
```

## Dereference with const

### Pointer to const (Can't modify value)
```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    const int* ptr = &value;
    
    cout << "Value: " << *ptr << endl;
    // *ptr = 100;  // ERROR! Can't modify through pointer to const
    
    value = 100;  // OK - can modify original
    cout << "After original change: " << *ptr << endl;
    
    return 0;
}
```

### Const pointer (Can't change address)
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;
    int* const ptr = &a;
    
    *ptr = 100;  // OK - can modify value
    // ptr = &b;  // ERROR! Can't change pointer
    
    cout << "a: " << a << endl;
    
    return 0;
}
```

### Const pointer to const (Can't modify either)
```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    const int* const ptr = &value;
    
    // *ptr = 100;  // ERROR! Can't modify value
    // ptr = &value;  // ERROR! Can't change pointer
    
    cout << "Value: " << *ptr << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Dereferencing Uninitialized Pointer
```cpp
int* ptr;        // Uninitialized
*ptr = 10;       // CRASH! Writing to random memory

// Always initialize
int* ptr = nullptr;
int value;
int* ptr = &value;
```

### Mistake 2: Dereferencing Null Pointer
```cpp
int* ptr = nullptr;
*ptr = 10;  // CRASH! Null pointer dereference

// Always check
if (ptr != nullptr) {
    *ptr = 10;
}
```

### Mistake 3: Forgetting * When Modifying
```cpp
int x = 10;
int* ptr = &x;

ptr = 20;   // WRONG! Changes pointer, not value
*ptr = 20;  // CORRECT! Changes value
```

### Mistake 4: Wrong Number of Dereferences
```cpp
int x = 10;
int* ptr = &x;
int** dptr = &ptr;

cout << *ptr;   // OK - value
cout << *dptr;  // WRONG! Prints address, not value
cout << **dptr; // CORRECT! Gets value through double pointer
```

### Mistake 5: Dereferencing After Delete
```cpp
int* ptr = new int(10);
delete ptr;
*ptr = 20;  // Undefined behavior - using deleted memory

// After delete, set to nullptr
delete ptr;
ptr = nullptr;
```

## Dereference vs Other Operators

| Operator | Meaning | Example |
|----------|---------|---------|
| `*ptr` | Dereference - get value at address | `int x = *ptr;` |
| `ptr->member` | Arrow - access member through pointer | `ptr->data` |
| `&var` | Address-of - get address | `int* p = &x;` |
| `ptr[index]` | Array subscript | `ptr[0] = 10;` |

## Quick Reference

| Operation | Code | Meaning |
|-----------|------|---------|
| Dereference | `*ptr` | Value at address stored in ptr |
| Modify through pointer | `*ptr = value` | Change value at address |
| Read through pointer | `x = *ptr` | Read value |
| Pointer arithmetic | `*(ptr + i)` | Access element i |
| Double dereference | `**dptr` | Value through pointer to pointer |
| Arrow operator | `ptr->member` | Same as `(*ptr).member` |

## Summary

- **Dereference operator** `*` accesses value at pointer's address
- Used for **reading** and **modifying** data through pointers
- Must ensure pointer points to **valid memory** before dereferencing
- **Pointer arithmetic** allows accessing array elements: `*(ptr + i)`
- **Double dereference** for pointer to pointer: `**dptr`
- Always **check for null** before dereferencing
- Cannot dereference **void pointers** without casting
- Used extensively in **dynamic memory**, **arrays**, **data structures**

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    // Basic dereference
    int value = 42;
    int* ptr = &value;
    
    cout << "Value: " << *ptr << endl;
    *ptr = 100;
    cout << "Modified: " << value << endl;
    
    // Array with pointer
    int arr[5] = {10, 20, 30, 40, 50};
    int* arrPtr = arr;
    
    cout << "\nArray elements:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "*(arrPtr + " << i << ") = " << *(arrPtr + i) << endl;
    }
    
    // Double pointer
    int** dptr = &ptr;
    cout << "\nDouble dereference: " << **dptr << endl;
    
    // Null check
    int* nullPtr = nullptr;
    if (nullPtr != nullptr) {
        cout << *nullPtr << endl;  // Won't execute
    } else {
        cout << "\nNull pointer - safe to not dereference" << endl;
    }
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*