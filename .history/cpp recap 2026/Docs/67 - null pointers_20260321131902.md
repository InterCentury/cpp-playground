# 67 - Null Pointers in C++

## What is a Null Pointer?
A null pointer is a pointer that does not point to any valid memory location. It represents "pointing to nothing." Dereferencing a null pointer causes undefined behavior (usually a crash).

## Null Pointer Representations

```cpp
#include <iostream>
using namespace std;

int main() {
    // Modern C++ (recommended)
    int* ptr1 = nullptr;
    
    // Old C-style (still works)
    int* ptr2 = NULL;
    
    // Also works (but less clear)
    int* ptr3 = 0;
    
    cout << "ptr1 (nullptr): " << ptr1 << endl;
    cout << "ptr2 (NULL): " << ptr2 << endl;
    cout << "ptr3 (0): " << ptr3 << endl;
    
    // All print 0 or (nil)
    
    return 0;
}
```

## Why Null Pointers Matter

Null pointers are used to indicate that a pointer is not currently pointing to valid memory.

```cpp
#include <iostream>
using namespace std;

int* findValue(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return &arr[i];  // Return pointer to found element
        }
    }
    return nullptr;  // Not found - return null pointer
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    
    int* found = findValue(numbers, 5, 30);
    
    if (found != nullptr) {
        cout << "Found: " << *found << endl;
        *found = 300;  // Safe to modify
    } else {
        cout << "Not found" << endl;
    }
    
    // This is the key: ALWAYS check before dereferencing
    int* notFound = findValue(numbers, 5, 99);
    if (notFound != nullptr) {
        cout << *notFound << endl;  // Won't execute
    }
    
    return 0;
}
```

## nullptr vs NULL vs 0

| Representation | Type | When to Use |
|----------------|------|-------------|
| `nullptr` | `std::nullptr_t` | C++11 and later (preferred) |
| `NULL` | `long` or `int` | Legacy C++ code |
| `0` | `int` | Works but less clear |

```cpp
#include <iostream>
using namespace std;

void function(int x) {
    cout << "int version called" << endl;
}

void function(char* ptr) {
    cout << "pointer version called" << endl;
}

int main() {
    function(0);       // Calls int version (0 is int)
    function(NULL);    // May call int version (NULL is often 0)
    function(nullptr); // Calls pointer version (correct!)
    
    return 0;
}
```

## Checking for Null Pointers

### Explicit Check
```cpp
#include <iostream>
using namespace std;

int main() {
    int* ptr = nullptr;
    
    // Check before using
    if (ptr != nullptr) {
        *ptr = 10;  // Safe
    } else {
        cout << "Pointer is null, cannot dereference" << endl;
    }
    
    // Alternative syntax
    if (ptr) {
        *ptr = 10;  // Executes if ptr is NOT null
    }
    
    if (!ptr) {
        cout << "Pointer is null" << endl;  // Executes if ptr IS null
    }
    
    return 0;
}
```

### Function with Null Check
```cpp
#include <iostream>
using namespace std;

void safeIncrement(int* ptr) {
    if (ptr != nullptr) {
        (*ptr)++;
        cout << "Incremented to: " << *ptr << endl;
    } else {
        cout << "Error: Cannot increment null pointer" << endl;
    }
}

int main() {
    int value = 5;
    int* validPtr = &value;
    int* nullPtr = nullptr;
    
    safeIncrement(validPtr);  // Works
    safeIncrement(nullPtr);   // Safe - doesn't crash
    
    return 0;
}
```

## Null Pointers in Dynamic Memory

```cpp
#include <iostream>
using namespace std;

int main() {
    // Initialize to nullptr
    int* ptr = nullptr;
    
    // Allocate memory
    ptr = new int(42);
    
    if (ptr != nullptr) {
        cout << "Value: " << *ptr << endl;
    }
    
    // Delete and set to nullptr
    delete ptr;
    ptr = nullptr;  // Important: prevent dangling pointer
    
    // Now safe to check
    if (ptr != nullptr) {
        // Won't execute
        cout << *ptr << endl;
    } else {
        cout << "Pointer is null after delete" << endl;
    }
    
    return 0;
}
```

## Dangling Pointers vs Null Pointers

```cpp
#include <iostream>
using namespace std;

int main() {
    // Null pointer - safe to check
    int* nullPtr = nullptr;
    
    // Dangling pointer - points to deleted memory
    int* danglingPtr = new int(10);
    delete danglingPtr;
    // danglingPtr now points to freed memory - dangerous!
    
    cout << "nullPtr: " << nullPtr << endl;
    cout << "danglingPtr: " << danglingPtr << endl;
    
    // Both may look similar, but:
    if (nullPtr == nullptr) {  // true
        cout << "nullPtr is null" << endl;
    }
    
    if (danglingPtr == nullptr) {  // false!
        cout << "danglingPtr is null" << endl;  // Won't print
    }
    
    // Danger: danglingPtr is not null but points to invalid memory
    // *danglingPtr = 20;  // UNDEFINED BEHAVIOR!
    
    // Always set to nullptr after delete
    delete danglingPtr;
    danglingPtr = nullptr;  // Now it's safe
    
    return 0;
}
```

## Practical Examples

### Example 1: Safe Array Search
```cpp
#include <iostream>
using namespace std;

int* findFirstEven(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            return &arr[i];
        }
    }
    return nullptr;
}

int main() {
    int numbers[] = {1, 3, 5, 7, 8, 9, 11};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int* even = findFirstEven(numbers, size);
    
    if (even != nullptr) {
        cout << "Found even number: " << *even << endl;
        *even = 100;  // Modify through pointer
        cout << "After modification: " << numbers[4] << endl;
    } else {
        cout << "No even numbers found" << endl;
    }
    
    return 0;
}
```

### Example 2: Optional Parameter
```cpp
#include <iostream>
using namespace std;

void processNumbers(int* ptr = nullptr) {
    if (ptr != nullptr) {
        cout << "Processing value: " << *ptr << endl;
        *ptr *= 2;
    } else {
        cout << "No value provided" << endl;
    }
}

int main() {
    int value = 10;
    
    processNumbers();        // No parameter
    processNumbers(&value);  // With parameter
    cout << "After processing: " << value << endl;
    
    return 0;
}
```

### Example 3: Linked List with Null Pointers
```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }
    
    Node* find(int val) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == val) {
                return current;
            }
            current = current->next;
        }
        return nullptr;  // Not found
    }
    
    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
    
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;
    list.push(10);
    list.push(20);
    list.push(30);
    
    list.display();
    
    Node* found = list.find(20);
    if (found != nullptr) {
        cout << "Found: " << found->data << endl;
        found->data = 200;
        cout << "Modified to: " << found->data << endl;
    }
    
    Node* notFound = list.find(99);
    if (notFound == nullptr) {
        cout << "99 not found" << endl;
    }
    
    list.display();
    
    return 0;
}
```

### Example 4: Dynamic Array with Null Checks
```cpp
#include <iostream>
using namespace std;

int* createArray(int size, int value) {
    if (size <= 0) {
        return nullptr;  // Invalid size
    }
    
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
    return arr;
}

void safePrintArray(int* arr, int size) {
    if (arr == nullptr) {
        cout << "Array is null!" << endl;
        return;
    }
    
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int* arr1 = createArray(5, 10);
    int* arr2 = createArray(-1, 0);  // Invalid
    
    safePrintArray(arr1, 5);
    safePrintArray(arr2, 0);
    
    delete[] arr1;
    // delete[] arr2;  // arr2 is nullptr, safe to delete but check
    
    if (arr2 != nullptr) {
        delete[] arr2;
    }
    
    return 0;
}
```

### Example 5: Function Returning Null for Error
```cpp
#include <iostream>
#include <cmath>
using namespace std;

double* solveQuadratic(double a, double b, double c) {
    double discriminant = b*b - 4*a*c;
    
    if (discriminant < 0) {
        return nullptr;  // No real roots
    }
    
    double* roots = new double[2];
    roots[0] = (-b + sqrt(discriminant)) / (2*a);
    roots[1] = (-b - sqrt(discriminant)) / (2*a);
    
    return roots;
}

int main() {
    // Quadratic with real roots
    double* roots1 = solveQuadratic(1, -5, 6);
    if (roots1 != nullptr) {
        cout << "Roots: " << roots1[0] << ", " << roots1[1] << endl;
        delete[] roots1;
    } else {
        cout << "No real roots" << endl;
    }
    
    // Quadratic with complex roots
    double* roots2 = solveQuadratic(1, 0, 1);
    if (roots2 != nullptr) {
        cout << "Roots: " << roots2[0] << ", " << roots2[1] << endl;
        delete[] roots2;
    } else {
        cout << "No real roots" << endl;
    }
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Dereferencing Without Check
```cpp
int* ptr = nullptr;
*ptr = 10;  // CRASH! Always check first

// Correct
if (ptr != nullptr) {
    *ptr = 10;
}
```

### Mistake 2: Comparing with NULL or 0 (Potential Issue)
```cpp
int* ptr = nullptr;

if (ptr == NULL) { }  // Works but nullptr is better
if (ptr == 0) { }     // Works but less clear
if (ptr == nullptr) { }  // Best - type-safe
```

### Mistake 3: Not Setting to nullptr After Delete
```cpp
int* ptr = new int(10);
delete ptr;
// ptr now dangling - points to freed memory

// Correct
delete ptr;
ptr = nullptr;  // Now safe
```

### Mistake 4: Assuming new Never Returns nullptr
```cpp
int* ptr = new int(10);  // In modern C++, throws exception on failure
// In older C++, could return nullptr

// Better to handle exceptions
try {
    int* ptr = new int(10);
    // Use ptr
    delete ptr;
} catch (bad_alloc& e) {
    cout << "Allocation failed" << endl;
}
```

### Mistake 5: Double Delete
```cpp
int* ptr = new int(10);
delete ptr;
delete ptr;  // Undefined behavior!

// Correct
delete ptr;
ptr = nullptr;
delete ptr;  // Safe to delete nullptr
```

## Null Pointer Safety Patterns

### Pattern 1: Always Initialize
```cpp
int* ptr = nullptr;  // Good habit
// Use later...
if (condition) {
    ptr = &value;
}
if (ptr != nullptr) {
    // Use safely
}
```

### Pattern 2: Check Before Use
```cpp
void process(int* ptr) {
    if (ptr == nullptr) {
        return;  // Early return for null
    }
    // Safe to use ptr here
    *ptr = 100;
}
```

### Pattern 3: Set to Null After Delete
```cpp
delete ptr;
ptr = nullptr;
```

### Pattern 4: Use Smart Pointers (Modern C++)
```cpp
#include <memory>
// unique_ptr automatically manages null state
unique_ptr<int> ptr = make_unique<int>(10);
if (ptr) {
    *ptr = 20;
}
// No manual delete needed
```

## Quick Reference

| Operation | Code | Result |
|-----------|------|--------|
| Declare null | `int* ptr = nullptr;` | Points to nothing |
| Check null | `if (ptr == nullptr)` | True if null |
| Check not null | `if (ptr != nullptr)` | True if valid |
| Check existence | `if (ptr)` | True if not null |
| Dereference safely | `if (ptr) *ptr = 10;` | Only if valid |
| Set to null | `ptr = nullptr;` | After delete |

## Summary

- **Null pointer** points to no valid memory location
- Use **nullptr** in modern C++ (C++11+)
- **Always check** for null before dereferencing
- Return **nullptr** to indicate "not found" or "error"
- Set pointers to **nullptr** after delete
- **Dangling pointers** are dangerous - they look valid but aren't
- **Smart pointers** (unique_ptr, shared_ptr) handle null automatically
- Never dereference a null pointer (causes crash)

## Basic Template
```cpp
#include <iostream>
using namespace std;

int* findValue(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return &arr[i];
        }
    }
    return nullptr;  // Not found
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    
    // Find existing value
    int* found = findValue(numbers, 5, 30);
    if (found != nullptr) {
        cout << "Found: " << *found << endl;
        *found = 300;  // Safe to modify
    }
    
    // Find non-existing value
    int* notFound = findValue(numbers, 5, 99);
    if (notFound == nullptr) {
        cout << "Value not found" << endl;
    }
    
    // Dynamic memory with null safety
    int* ptr = new int(42);
    if (ptr != nullptr) {
        cout << "Allocated: " << *ptr << endl;
        delete ptr;
        ptr = nullptr;  // Prevent dangling
    }
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*