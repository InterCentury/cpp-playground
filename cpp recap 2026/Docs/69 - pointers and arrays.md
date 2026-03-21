# 69 - Pointers and Arrays in C++

## The Array-Pointer Relationship

In C++, arrays and pointers are closely related. The name of an array acts as a pointer to its first element. Understanding this relationship is crucial for effective C++ programming.

## Basic Relationship

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    
    // Array name is a pointer to first element
    cout << "arr = " << arr << endl;
    cout << "&arr[0] = " << &arr[0] << endl;
    cout << "*arr = " << *arr << endl;  // First element
    
    // These are equivalent:
    cout << "\nEquivalent expressions:" << endl;
    cout << "arr[2] = " << arr[2] << endl;
    cout << "*(arr + 2) = " << *(arr + 2) << endl;
    
    return 0;
}
```

## Arrays Decay to Pointers

When you use an array name in an expression, it "decays" to a pointer to its first element.

```cpp
#include <iostream>
using namespace std;

void printArray(int* ptr, int size) {
    for (int i = 0; i < size; i++) {
        cout << ptr[i] << " ";  // Can use array syntax with pointer
    }
    cout << endl;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    
    // Array decays to pointer when passed to function
    printArray(numbers, 5);  // numbers decays to int*
    
    // Also works with pointer arithmetic
    int* ptr = numbers;
    cout << "Through pointer: ";
    for (int i = 0; i < 5; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Array vs Pointer - The Differences

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    cout << "Size differences:" << endl;
    cout << "sizeof(arr) = " << sizeof(arr) << " bytes (entire array)" << endl;
    cout << "sizeof(ptr) = " << sizeof(ptr) << " bytes (just pointer)" << endl;
    
    cout << "\nAddress differences:" << endl;
    cout << "arr = " << arr << endl;
    cout << "&arr = " << &arr << endl;  // Same value, different type
    cout << "ptr = " << ptr << endl;
    cout << "&ptr = " << &ptr << endl;  // Different - address of pointer
    
    cout << "\nCannot reassign array:" << endl;
    // arr = ptr;  // ERROR! Cannot reassign array name
    
    ptr = arr + 2;  // OK - pointer can be reassigned
    cout << "After ptr = arr + 2: *ptr = " << *ptr << endl;
    
    return 0;
}
```

## Accessing Array Elements with Pointers

### Using Pointer Arithmetic
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    // Method 1: Array subscript
    cout << "Array subscript: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Method 2: Pointer arithmetic
    cout << "Pointer arithmetic: ";
    for (int i = 0; i < 5; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
    
    // Method 3: Moving pointer
    cout << "Moving pointer: ";
    for (int i = 0; i < 5; i++) {
        cout << *ptr << " ";
        ptr++;
    }
    cout << endl;
    
    return 0;
}
```

### Accessing with Different Types
```cpp
#include <iostream>
using namespace std;

int main() {
    // Integer array
    int intArr[] = {1, 2, 3, 4, 5};
    int* intPtr = intArr;
    
    cout << "Integer array: ";
    for (int i = 0; i < 5; i++) {
        cout << *(intPtr + i) << " ";
    }
    cout << endl;
    
    // Character array (C-string)
    char charArr[] = "Hello";
    char* charPtr = charArr;
    
    cout << "Character array: ";
    while (*charPtr != '\0') {
        cout << *charPtr << " ";
        charPtr++;
    }
    cout << endl;
    
    // Double array
    double doubleArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double* doublePtr = doubleArr;
    
    cout << "Double array: ";
    for (int i = 0; i < 5; i++) {
        cout << *(doublePtr + i) << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Summing Array Elements with Pointers
```cpp
#include <iostream>
using namespace std;

int sumArray(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);  // or sum += arr[i];
    }
    return sum;
}

int sumUsingPointer(int* start, int* end) {
    int sum = 0;
    while (start < end) {
        sum += *start;
        start++;
    }
    return sum;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Sum (index method): " << sumArray(numbers, size) << endl;
    cout << "Sum (pointer method): " << sumUsingPointer(numbers, numbers + size) << endl;
    
    // Sum first 5 elements
    cout << "Sum of first 5: " << sumUsingPointer(numbers, numbers + 5) << endl;
    
    return 0;
}
```

### Example 2: Copying Arrays with Pointers
```cpp
#include <iostream>
using namespace std;

void copyArray(int* dest, int* src, int size) {
    for (int i = 0; i < size; i++) {
        *(dest + i) = *(src + i);
    }
}

void copyUsingPointer(int* dest, int* src, int size) {
    int* end = src + size;
    while (src < end) {
        *dest = *src;
        dest++;
        src++;
    }
}

int main() {
    int source[] = {10, 20, 30, 40, 50};
    int destination[5];
    int size = sizeof(source) / sizeof(source[0]);
    
    copyArray(destination, source, size);
    
    cout << "Copied array: ";
    for (int i = 0; i < size; i++) {
        cout << destination[i] << " ";
    }
    cout << endl;
    
    int anotherDest[5];
    copyUsingPointer(anotherDest, source, size);
    
    cout << "Copied (pointer method): ";
    for (int i = 0; i < size; i++) {
        cout << anotherDest[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 3: Finding in Array Using Pointers
```cpp
#include <iostream>
using namespace std;

int* findValue(int* start, int* end, int target) {
    while (start < end) {
        if (*start == target) {
            return start;
        }
        start++;
    }
    return nullptr;
}

int* findLast(int* start, int* end, int target) {
    int* result = nullptr;
    while (start < end) {
        if (*start == target) {
            result = start;
        }
        start++;
    }
    return result;
}

int main() {
    int numbers[] = {10, 20, 30, 20, 40, 50, 20, 60};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int* found = findValue(numbers, numbers + size, 20);
    if (found != nullptr) {
        cout << "Found 20 at position: " << (found - numbers) << endl;
    }
    
    int* last = findLast(numbers, numbers + size, 20);
    if (last != nullptr) {
        cout << "Last 20 at position: " << (last - numbers) << endl;
    }
    
    return 0;
}
```

### Example 4: 2D Arrays and Pointers
```cpp
#include <iostream>
using namespace std;

int main() {
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Method 1: Pointer to first element
    int* ptr = &matrix[0][0];
    cout << "Treating 2D as 1D: ";
    for (int i = 0; i < 12; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
    
    // Method 2: Pointer to row (array of 4 ints)
    int (*rowPtr)[4] = matrix;
    cout << "\nRow-wise access:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << rowPtr[i][j] << "\t";
        }
        cout << endl;
    }
    
    // Method 3: Using pointer arithmetic
    cout << "\nUsing pointer arithmetic:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << *(*(matrix + i) + j) << "\t";
        }
        cout << endl;
    }
    
    return 0;
}
```

### Example 5: Dynamic Array (Pointer to Array)
```cpp
#include <iostream>
using namespace std;

int* createArray(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;
    }
    return arr;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void resizeArray(int*& arr, int oldSize, int newSize) {
    int* newArr = new int[newSize];
    
    // Copy old elements
    for (int i = 0; i < oldSize && i < newSize; i++) {
        newArr[i] = arr[i];
    }
    
    // Fill remaining with default
    for (int i = oldSize; i < newSize; i++) {
        newArr[i] = 0;
    }
    
    delete[] arr;
    arr = newArr;
}

int main() {
    int size = 5;
    int* arr = createArray(size);
    
    cout << "Original array: ";
    printArray(arr, size);
    
    // Resize to larger
    resizeArray(arr, size, 8);
    cout << "After resize (larger): ";
    printArray(arr, 8);
    
    // Resize to smaller
    resizeArray(arr, 8, 3);
    cout << "After resize (smaller): ";
    printArray(arr, 3);
    
    delete[] arr;
    
    return 0;
}
```

## String Arrays and Pointers

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    // Array of strings (C-style)
    char* names[] = {"Alice", "Bob", "Charlie", "Diana"};
    int count = sizeof(names) / sizeof(names[0]);
    
    cout << "Names array:" << endl;
    for (int i = 0; i < count; i++) {
        cout << "  " << names[i] << " at address: " << (void*)names[i] << endl;
    }
    
    // Modify via pointer
    names[2] = "Charles";
    cout << "\nAfter modification: " << names[2] << endl;
    
    // Array of C++ strings
    string cppNames[] = {"Alice", "Bob", "Charlie", "Diana"};
    string* ptr = cppNames;
    
    cout << "\nC++ strings:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "  " << *(ptr + i) << endl;
    }
    
    return 0;
}
```

## Multidimensional Array Pointer Arithmetic

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // arr is pointer to array of 4 ints
    cout << "arr = " << arr << endl;
    cout << "arr + 1 = " << arr + 1 << endl;
    cout << "Difference: " << ((char*)(arr + 1) - (char*)arr) << " bytes" << endl;
    
    // Accessing elements
    cout << "\nElement access:" << endl;
    cout << "arr[1][2] = " << arr[1][2] << endl;
    cout << "*(*(arr + 1) + 2) = " << *(*(arr + 1) + 2) << endl;
    
    // Using a pointer to row
    int (*row)[4] = arr;
    cout << "row[2][3] = " << row[2][3] << endl;
    
    // Using a flat pointer
    int* flat = &arr[0][0];
    cout << "flat[1*4 + 2] = " << flat[1*4 + 2] << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Confusing Array Name with Pointer
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

// WRONG - trying to reassign array name
// arr = ptr;  // Error!

// CORRECT - pointer can be reassigned
ptr = arr + 2;
```

### Mistake 2: sizeof Confusion
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

cout << "sizeof(arr) = " << sizeof(arr) << endl;  // 20 (5 * 4)
cout << "sizeof(ptr) = " << sizeof(ptr) << endl;  // 8 (on 64-bit)
```

### Mistake 3: Out of Bounds Access
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

// DANGEROUS - going beyond bounds
ptr += 10;
cout << *ptr;  // Undefined behavior!
```

### Mistake 4: Returning Pointer to Local Array
```cpp
// WRONG - returns pointer to local array
int* badFunction() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // arr destroyed when function ends!
}

// CORRECT - use static or dynamic allocation
int* goodFunction() {
    static int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // Static persists
}
```

### Mistake 5: Confusing &arr with arr
```cpp
int arr[5] = {1, 2, 3, 4, 5};

cout << "arr = " << arr << endl;      // Address of first element
cout << "&arr = " << &arr << endl;    // Same address, different type
cout << "&arr[0] = " << &arr[0] << endl;  // Same as arr

cout << "arr + 1 = " << arr + 1 << endl;      // +4 bytes
cout << "&arr + 1 = " << &arr + 1 << endl;    // +20 bytes (entire array)
```

## Quick Reference Table

| Expression | Meaning | Type |
|------------|---------|------|
| `arr` | Address of first element | `T*` |
| `&arr[0]` | Same as arr | `T*` |
| `&arr` | Address of entire array | `T(*)[N]` |
| `*arr` | First element value | `T` |
| `arr[i]` | Element at index i | `T` |
| `*(arr + i)` | Same as arr[i] | `T` |
| `arr + i` | Address of element i | `T*` |
| `ptr = arr` | Pointer to first element | `T*` |

## Summary

- **Array name** decays to pointer to first element
- **Array subscript** `arr[i]` is equivalent to `*(arr + i)`
- **sizeof(arr)** gives array size, **sizeof(ptr)** gives pointer size
- **Cannot reassign** array name (not an lvalue)
- **Pointer arithmetic** works with arrays naturally
- **2D arrays** can be accessed as flat or with pointer to row
- **String literals** are constant character arrays
- **Dynamic arrays** are pointers to allocated memory
- **Always check bounds** when using pointer arithmetic

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    // 1D array
    int arr[5] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    cout << "Array traversal:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "arr[" << i << "] = " << arr[i] 
             << ", *(ptr + " << i << ") = " << *(ptr + i) << endl;
    }
    
    // 2D array
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    cout << "\n2D array traversal:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // Pointer to row
    int (*row)[3] = matrix;
    cout << "\nRow pointer access: " << row[1][2] << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*