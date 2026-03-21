# 68 - Pointer Arithmetic in C++

## What is Pointer Arithmetic?
Pointer arithmetic is the ability to perform arithmetic operations on pointers. When you add or subtract from a pointer, it moves by the size of the data type it points to, not by 1 byte.

## Basic Concept

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // Points to first element
    
    cout << "ptr points to: " << *ptr << endl;      // 10
    cout << "ptr + 1 points to: " << *(ptr + 1) << endl;  // 20
    cout << "ptr + 2 points to: " << *(ptr + 2) << endl;  // 30
    
    return 0;
}
```

## Why Pointer Arithmetic Moves by Type Size

```cpp
#include <iostream>
using namespace std;

int main() {
    int intArr[] = {10, 20, 30};
    int* intPtr = intArr;
    
    double doubleArr[] = {1.1, 2.2, 3.3};
    double* doublePtr = doubleArr;
    
    char charArr[] = {'A', 'B', 'C'};
    char* charPtr = charArr;
    
    cout << "int pointer arithmetic:" << endl;
    cout << "intPtr: " << intPtr << endl;
    cout << "intPtr + 1: " << intPtr + 1 << endl;
    cout << "Difference: " << ((char*)(intPtr + 1) - (char*)intPtr) << " bytes" << endl;
    
    cout << "\ndouble pointer arithmetic:" << endl;
    cout << "doublePtr: " << doublePtr << endl;
    cout << "doublePtr + 1: " << doublePtr + 1 << endl;
    cout << "Difference: " << ((char*)(doublePtr + 1) - (char*)doublePtr) << " bytes" << endl;
    
    cout << "\nchar pointer arithmetic:" << endl;
    cout << "charPtr: " << (void*)charPtr << endl;
    cout << "charPtr + 1: " << (void*)(charPtr + 1) << endl;
    cout << "Difference: 1 byte" << endl;
    
    return 0;
}
```

## Pointer Arithmetic Operations

### Addition (+)
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    cout << "Initial: *ptr = " << *ptr << endl;     // 10
    
    ptr = ptr + 2;  // Move forward 2 elements
    cout << "After ptr + 2: *ptr = " << *ptr << endl;  // 30
    
    ptr += 1;  // Move forward 1 more
    cout << "After ptr += 1: *ptr = " << *ptr << endl;  // 40
    
    return 0;
}
```

### Subtraction (-)
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = &arr[4];  // Points to last element
    
    cout << "Initial: *ptr = " << *ptr << endl;     // 50
    
    ptr = ptr - 2;  // Move backward 2 elements
    cout << "After ptr - 2: *ptr = " << *ptr << endl;  // 30
    
    ptr -= 1;  // Move backward 1 more
    cout << "After ptr -= 1: *ptr = " << *ptr << endl;  // 20
    
    return 0;
}
```

### Increment (++)
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    cout << "Postfix increment:" << endl;
    cout << "*ptr++ = " << *ptr++ << endl;  // Gets 10, then moves to 20
    cout << "Now *ptr = " << *ptr << endl;  // 20
    
    ptr = arr;  // Reset
    
    cout << "\nPrefix increment:" << endl;
    cout << "*++ptr = " << *++ptr << endl;  // Moves to 20, then gets 20
    cout << "Now *ptr = " << *ptr << endl;  // 20
    
    return 0;
}
```

### Decrement (--)
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = &arr[4];  // Points to last element
    
    cout << "Postfix decrement:" << endl;
    cout << "*ptr-- = " << *ptr-- << endl;  // Gets 50, then moves to 40
    cout << "Now *ptr = " << *ptr << endl;  // 40
    
    ptr = &arr[4];  // Reset
    
    cout << "\nPrefix decrement:" << endl;
    cout << "*--ptr = " << *--ptr << endl;  // Moves to 40, then gets 40
    cout << "Now *ptr = " << *ptr << endl;  // 40
    
    return 0;
}
```

### Pointer Difference
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* start = arr;
    int* end = &arr[4];
    
    int difference = end - start;
    cout << "Number of elements between: " << difference << endl;  // 4
    
    // Can also do pointer subtraction
    int* ptr1 = &arr[1];  // 20
    int* ptr2 = &arr[4];  // 50
    cout << "ptr2 - ptr1 = " << ptr2 - ptr1 << endl;  // 3
    
    return 0;
}
```

## Practical Examples

### Example 1: Traversing Array with Pointers
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    // Forward traversal
    cout << "Forward: ";
    for (int* ptr = numbers; ptr < numbers + size; ptr++) {
        cout << *ptr << " ";
    }
    cout << endl;
    
    // Reverse traversal
    cout << "Reverse: ";
    for (int* ptr = numbers + size - 1; ptr >= numbers; ptr--) {
        cout << *ptr << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 2: Array Sum Using Pointers
```cpp
#include <iostream>
using namespace std;

int sumArray(int* start, int* end) {
    int sum = 0;
    for (int* ptr = start; ptr < end; ptr++) {
        sum += *ptr;
    }
    return sum;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int total = sumArray(numbers, numbers + size);
    cout << "Sum of array: " << total << endl;
    
    // Sum first 5 elements
    int firstFive = sumArray(numbers, numbers + 5);
    cout << "Sum of first 5: " << firstFive << endl;
    
    return 0;
}
```

### Example 3: Finding Max with Pointer Arithmetic
```cpp
#include <iostream>
using namespace std;

int* findMax(int* start, int* end) {
    int* maxPtr = start;
    for (int* ptr = start + 1; ptr < end; ptr++) {
        if (*ptr > *maxPtr) {
            maxPtr = ptr;
        }
    }
    return maxPtr;
}

int main() {
    int numbers[] = {45, 23, 78, 12, 89, 34, 67};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int* max = findMax(numbers, numbers + size);
    cout << "Maximum value: " << *max << endl;
    cout << "Index: " << (max - numbers) << endl;
    
    return 0;
}
```

### Example 4: Reverse Array with Pointers
```cpp
#include <iostream>
using namespace std;

void reverseArray(int* start, int* end) {
    end--;  // Point to last element
    while (start < end) {
        // Swap using pointers
        int temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Original: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    reverseArray(numbers, numbers + size);
    
    cout << "Reversed: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 5: String Operations with Pointers
```cpp
#include <iostream>
#include <cstring>
using namespace std;

int stringLength(const char* str) {
    const char* ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }
    return ptr - str;
}

void stringCopy(char* dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void stringReverse(char* str) {
    int len = stringLength(str);
    char* start = str;
    char* end = str + len - 1;
    
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
    char buffer[50];
    
    cout << "Original: " << text << endl;
    cout << "Length: " << stringLength(text) << endl;
    
    stringCopy(buffer, text);
    cout << "Copied: " << buffer << endl;
    
    stringReverse(buffer);
    cout << "Reversed: " << buffer << endl;
    
    return 0;
}
```

## Advanced Pointer Arithmetic

### 2D Array with Pointer Arithmetic
```cpp
#include <iostream>
using namespace std;

int main() {
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Using pointer to row
    int (*rowPtr)[4] = matrix;  // Pointer to array of 4 ints
    
    cout << "Accessing with pointer arithmetic:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << *(*(rowPtr + i) + j) << "\t";
        }
        cout << endl;
    }
    
    // Using single pointer (treat as 1D)
    int* ptr = &matrix[0][0];
    cout << "\nTreating as 1D array:" << endl;
    for (int i = 0; i < 12; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Pointer Arithmetic with void* (Not Allowed)
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30};
    void* vptr = arr;
    
    // Cannot do arithmetic on void* directly
    // vptr++;  // Error! Cannot increment void*
    
    // Must cast to appropriate type
    int* iptr = (int*)vptr;
    iptr++;
    cout << "After cast and increment: " << *iptr << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Forgetting Pointer Arithmetic Moves by Type Size
```cpp
int arr[] = {10, 20, 30};
int* ptr = arr;

// WRONG - thinking ptr + 1 moves 1 byte
// cout << *(char*)ptr + 1;  // Wrong interpretation

// CORRECT - moves to next int (4 bytes)
cout << *(ptr + 1);  // 20
```

### Mistake 2: Going Out of Bounds
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

// DANGEROUS - going beyond array bounds
ptr += 10;
cout << *ptr;  // Undefined behavior!

// Always stay within [arr, arr + size)
```

### Mistake 3: Subtracting Pointers of Different Types
```cpp
int arr1[5];
double arr2[5];

// WRONG - cannot subtract pointers of different types
// int diff = arr2 - arr1;  // Error!
```

### Mistake 4: Confusing Pointer Arithmetic with Value Arithmetic
```cpp
int arr[] = {10, 20, 30};
int* ptr = arr;

// WRONG - thinking *ptr++ increments value
*ptr++;  // Actually moves pointer, not increment value

// To increment value:
(*ptr)++;  // Increments the value
```

### Mistake 5: Using After Deletion
```cpp
int* ptr = new int(10);
delete ptr;

ptr++;  // Undefined behavior! ptr now points to deleted memory
```

## Quick Reference Table

| Operation | Meaning | Example (int*) |
|-----------|---------|----------------|
| `ptr + n` | Move forward n elements | `ptr + 3` moves 12 bytes |
| `ptr - n` | Move backward n elements | `ptr - 2` moves 8 bytes |
| `ptr++` | Move to next element (post) | `*ptr++` gets, then moves |
| `++ptr` | Move to next element (pre) | `*++ptr` moves, then gets |
| `ptr--` | Move to previous element | `*ptr--` gets, then moves |
| `--ptr` | Move to previous element | `*--ptr` moves, then gets |
| `ptr2 - ptr1` | Number of elements between | Returns integer |
| `ptr < ptr2` | Compare addresses | Valid if same array |

## Summary

- **Pointer arithmetic** moves by size of data type, not by byte
- **Adding** moves pointer forward
- **Subtracting** moves pointer backward
- **Increment/decrement** (++, --) for step-by-step movement
- **Pointer subtraction** gives number of elements between
- **Compare pointers** to check relative position
- **Always stay within array bounds**
- **Cannot do arithmetic on void pointers**
- Useful for **array traversal**, **buffer management**, **string operations**

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    // Basic pointer arithmetic
    int* ptr = arr;
    
    cout << "Array traversal with pointer arithmetic:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "*(ptr + " << i << ") = " << *(ptr + i) << endl;
    }
    
    // Moving pointer
    cout << "\nMoving pointer:" << endl;
    cout << "*ptr = " << *ptr << endl;
    ptr++;
    cout << "After ptr++: *ptr = " << *ptr << endl;
    ptr += 2;
    cout << "After ptr += 2: *ptr = " << *ptr << endl;
    
    // Pointer difference
    int* start = arr;
    int* end = arr + size - 1;
    cout << "\nElements between: " << (end - start) << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*