# 72 - References vs Pointers in C++

## Overview
References and pointers are both used to indirectly access variables, but they have fundamental differences in syntax, behavior, and usage. Understanding these differences is crucial for writing correct and efficient C++ code.

## Quick Comparison Table

| Feature | Reference | Pointer |
|---------|-----------|---------|
| Syntax | `int& ref = var;` | `int* ptr = &var;` |
| Must initialize | ✅ Yes | ❌ No (can be null) |
| Can be null | ❌ No | ✅ Yes (nullptr) |
| Can be reassigned | ❌ No | ✅ Yes |
| Access value | Direct (`ref`) | Dereference (`*ptr`) |
| Memory overhead | None (alias) | 4-8 bytes (address) |
| Array access | Not directly | Pointer arithmetic |
| Function parameters | Clean syntax | Explicit syntax |
| Operator overloading | Common | Rare |

## Basic Differences

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    
    // Reference - alias to existing variable
    int& ref = value;  // Must be initialized immediately
    
    // Pointer - can be initialized later
    int* ptr = &value;  // Or int* ptr = nullptr;
    
    cout << "Original value: " << value << endl;
    
    // Using reference (direct)
    ref = 100;
    cout << "After ref = 100: " << value << endl;
    
    // Using pointer (dereference)
    *ptr = 200;
    cout << "After *ptr = 200: " << value << endl;
    
    // Pointer can be reassigned
    int another = 500;
    ptr = &another;  // OK - pointer now points to another
    *ptr = 600;
    cout << "another: " << another << endl;
    
    // Reference cannot be reassigned
    // ref = another;  // This assigns value, not reassigns reference
    
    return 0;
}
```

## Initialization Requirements

```cpp
#include <iostream>
using namespace std;

int main() {
    // References MUST be initialized
    int& ref;  // ❌ Error! Reference must be initialized
    
    int value = 10;
    int& ref2 = value;  // ✅ OK - initialized
    
    // Pointers can be uninitialized (but dangerous)
    int* ptr1;  // ⚠️ Contains garbage address
    int* ptr2 = nullptr;  // ✅ Good practice
    int* ptr3 = &value;  // ✅ OK
    
    return 0;
}
```

## Nullability

```cpp
#include <iostream>
using namespace std;

int* findValue(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return &arr[i];
        }
    }
    return nullptr;  // Pointer can return null
}

// Cannot do this with references
// int& findValueRef(...) { }  // No null reference possible

int main() {
    int numbers[] = {10, 20, 30};
    
    int* found = findValue(numbers, 3, 99);
    if (found != nullptr) {
        cout << "Found: " << *found << endl;
    } else {
        cout << "Not found (null pointer)" << endl;
    }
    
    return 0;
}
```

## Memory and Size

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int& ref = value;
    int* ptr = &value;
    
    cout << "sizeof(value): " << sizeof(value) << " bytes" << endl;
    cout << "sizeof(ref): " << sizeof(ref) << " bytes (same as value)" << endl;
    cout << "sizeof(ptr): " << sizeof(ptr) << " bytes (pointer size)" << endl;
    
    // References take no extra memory (conceptually)
    // Pointers store address (4-8 bytes)
    
    return 0;
}
```

## Reassignment Behavior

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;
    
    // Reference
    int& ref = a;
    cout << "ref refers to a = " << ref << endl;
    
    ref = b;  // This ASSIGNS value, doesn't rebind reference
    cout << "After ref = b: a = " << a << endl;  // a becomes 20
    cout << "ref still refers to a: " << ref << endl;
    
    // Pointer
    int* ptr = &a;
    cout << "\nptr points to a = " << *ptr << endl;
    
    ptr = &b;  // This rebinds pointer to b
    cout << "After ptr = &b: *ptr = " << *ptr << endl;
    cout << "a remains: " << a << endl;
    
    return 0;
}
```

## Function Parameters

### Pass by Reference (Cleaner)
```cpp
#include <iostream>
using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
    // No dereferencing needed
}

void increment(int& x) {
    x++;
}

int main() {
    int x = 10, y = 20;
    
    cout << "Before swap: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    increment(x);
    cout << "After increment: x=" << x << endl;
    
    return 0;
}
```

### Pass by Pointer (More Explicit)
```cpp
#include <iostream>
using namespace std;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    // Must dereference
}

void increment(int* x) {
    if (x != nullptr) {  // Must check for null
        (*x)++;
    }
}

int main() {
    int x = 10, y = 20;
    
    cout << "Before swap: x=" << x << ", y=" << y << endl;
    swap(&x, &y);  // Must pass addresses
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    increment(&x);
    cout << "After increment: x=" << x << endl;
    
    increment(nullptr);  // Safe - null check prevents crash
    
    return 0;
}
```

## const with References and Pointers

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 10;
    
    // Reference to const (can't modify through reference)
    const int& constRef = value;
    // constRef = 20;  // ❌ Error! Can't modify const reference
    
    // Pointer to const (can't modify through pointer)
    const int* constPtr = &value;
    // *constPtr = 20;  // ❌ Error! Can't modify const pointer
    
    // Const pointer (can't change address)
    int* const ptrConst = &value;
    *ptrConst = 20;  // ✅ OK - can modify value
    // ptrConst = &another;  // ❌ Error! Can't change address
    
    // Const pointer to const (can't modify either)
    const int* const constPtrConst = &value;
    // *constPtrConst = 20;  // ❌ Error!
    // constPtrConst = &another;  // ❌ Error!
    
    return 0;
}
```

## Arrays and Pointer Arithmetic

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    
    // Pointer can do arithmetic
    int* ptr = arr;
    cout << "Pointer arithmetic: ";
    for (int i = 0; i < 5; i++) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
    
    // Reference to array (must specify size)
    int (&refArr)[5] = arr;
    cout << "Reference access: ";
    for (int i = 0; i < 5; i++) {
        cout << refArr[i] << " ";
    }
    cout << endl;
    
    // Cannot do pointer arithmetic with reference
    // refArr++;  // ❌ Error!
    
    return 0;
}
```

## Return Values

### Returning Reference (Alias to existing)
```cpp
#include <iostream>
using namespace std;

int global = 100;

int& getGlobal() {
    return global;  // Returns reference to global
}

int& getElement(int arr[], int index) {
    return arr[index];  // Returns reference to array element
}

int main() {
    // Can modify through returned reference
    getGlobal() = 200;
    cout << "global: " << global << endl;
    
    int arr[3] = {1, 2, 3};
    getElement(arr, 1) = 20;
    cout << "arr[1]: " << arr[1] << endl;
    
    return 0;
}
```

### Returning Pointer (Can be null)
```cpp
#include <iostream>
using namespace std;

int* findValue(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return &arr[i];
        }
    }
    return nullptr;  // Can return null for not found
}

int main() {
    int numbers[] = {10, 20, 30};
    
    int* found = findValue(numbers, 3, 25);
    if (found != nullptr) {
        cout << "Found: " << *found << endl;
    } else {
        cout << "Not found" << endl;
    }
    
    return 0;
}
```

## Practical Examples

### Example 1: Optional Parameters
```cpp
#include <iostream>
using namespace std;

// Using pointer (can be optional)
void processWithPointer(int* ptr = nullptr) {
    if (ptr != nullptr) {
        cout << "Processing: " << *ptr << endl;
        *ptr *= 2;
    } else {
        cout << "No value provided" << endl;
    }
}

// Using reference (cannot be optional - must have default reference)
void processWithReference(int& ref) {
    cout << "Processing: " << ref << endl;
    ref *= 2;
}

int main() {
    int value = 10;
    
    // Pointer version - can be called without argument
    processWithPointer();     // Optional - no value
    processWithPointer(&value); // With value
    
    // Reference version - must always have argument
    processWithReference(value);
    
    return 0;
}
```

### Example 2: Data Structures
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
    
    // Returns pointer (can be null)
    Node* find(int val) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == val) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    // Returns reference to data (must exist)
    int& front() {
        if (head != nullptr) {
            return head->data;
        }
        static int dummy = -1;
        return dummy;
    }
    
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }
};

int main() {
    LinkedList list;
    list.push(10);
    list.push(20);
    list.push(30);
    
    // Using pointer (may be null)
    Node* found = list.find(20);
    if (found != nullptr) {
        cout << "Found: " << found->data << endl;
        found->data = 200;
    }
    
    // Using reference (always valid)
    list.front() = 100;
    
    return 0;
}
```

### Example 3: Large Object Passing
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Inefficient - copies large object
void processCopy(vector<string> data) {
    // Works on copy
}

// Efficient - no copy, but can modify
void processReference(vector<string>& data) {
    // Can modify original
    data.push_back("New");
}

// Efficient - no copy, read-only
void processConstReference(const vector<string>& data) {
    // Cannot modify
    cout << "Size: " << data.size() << endl;
}

// Efficient - can be null
void processPointer(vector<string>* data) {
    if (data != nullptr) {
        data->push_back("From pointer");
    }
}

int main() {
    vector<string> data = {"A", "B", "C"};
    
    processConstReference(data);  // Read-only, efficient
    processReference(data);       // Can modify
    processPointer(&data);        // Can modify, null-check
    
    return 0;
}
```

### Example 4: Operator Overloading
```cpp
#include <iostream>
using namespace std;

class Counter {
private:
    int value;
    
public:
    Counter(int v = 0) : value(v) {}
    
    // Prefix increment (returns reference)
    Counter& operator++() {
        ++value;
        return *this;  // Returns reference to self
    }
    
    // Postfix increment (returns copy)
    Counter operator++(int) {
        Counter temp = *this;
        ++value;
        return temp;  // Returns copy
    }
    
    // Assignment operator (returns reference)
    Counter& operator=(const Counter& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;  // Returns reference for chaining
    }
    
    int getValue() const { return value; }
};

int main() {
    Counter c1(5), c2(10);
    
    // Returns reference - allows chaining
    ++c1;  // Returns reference to c1
    (++c1) = Counter(100);  // Can assign because returns reference
    
    // Assignment returns reference for chaining
    c2 = c1 = Counter(50);
    
    cout << "c1: " << c1.getValue() << endl;
    cout << "c2: " << c2.getValue() << endl;
    
    return 0;
}
```

### Example 5: Polymorphism
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() const override {
        cout << "Drawing Circle" << endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        cout << "Drawing Square" << endl;
    }
};

int main() {
    // Using pointers (can be null, can be reassigned)
    Shape* shape1 = new Circle();
    Shape* shape2 = new Square();
    
    vector<Shape*> shapes = {shape1, shape2};
    
    for (Shape* s : shapes) {
        s->draw();  // Polymorphic call
    }
    
    // Using references (cannot be null, cannot be reassigned)
    Circle circle;
    Square square;
    
    Shape& ref1 = circle;
    Shape& ref2 = square;
    
    ref1.draw();  // Polymorphic call
    ref2.draw();
    
    // Cleanup
    delete shape1;
    delete shape2;
    
    return 0;
}
```

## When to Use Each

### Use References When:
```cpp
// 1. You need an alias that cannot be null
int& ref = value;

// 2. Function parameters that modify original
void increment(int& x);

// 3. Operator overloading
Matrix& operator+=(const Matrix& other);

// 4. Returning class members for modification
int& getValue();

// 5. Avoiding copies for large objects
void process(const LargeObject& obj);
```

### Use Pointers When:
```cpp
// 1. You need null to indicate "no object"
int* ptr = nullptr;

// 2. Dynamic memory allocation
int* arr = new int[10];

// 3. Array iteration and pointer arithmetic
int* end = arr + size;

// 4. Optional parameters
void process(int* ptr = nullptr);

// 5. Polymorphic containers
vector<Shape*> shapes;

// 6. You need to reassign what you point to
ptr = &another;
```

## Common Mistakes

### Mistake 1: Dangling Reference
```cpp
int& bad() {
    int x = 10;
    return x;  // DANGEROUS! Reference to local
}

// Correct - return value or use static
int good() {
    int x = 10;
    return x;  // Returns copy
}
```

### Mistake 2: Null Reference (Impossible)
```cpp
int& ref = *nullptr;  // Undefined behavior!
// References cannot be null - don't try to create null reference
```

### Mistake 3: Forgetting & for Reference Parameters
```cpp
void increment(int x) { x++; }  // Pass by value, no effect

// Correct
void increment(int& x) { x++; }
```

### Mistake 4: Forgetting * for Pointer Parameters
```cpp
void swap(int a, int b) {  // Pass by value, won't swap
    int temp = a;
    a = b;
    b = temp;
}

// Correct
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

## Quick Reference Table

| Operation | Reference | Pointer |
|-----------|-----------|---------|
| Declaration | `int& r = x;` | `int* p = &x;` |
| Access value | `r = 10;` | `*p = 10;` |
| Get address | `&r` (address of x) | `p` (address of x) |
| Null check | Not needed | `if (p) { }` |
| Reassign | Not possible | `p = &y;` |
| Function param | `void f(int& x)` | `void f(int* x)` |
| Call function | `f(x)` | `f(&x)` |
| Return from function | `return x;` | `return &x;` |

## Summary

- **References** are aliases, **pointers** store addresses
- References **cannot be null**, pointers can be null
- References **cannot be reassigned**, pointers can
- References use **direct syntax**, pointers need dereference `*`
- References have **no memory overhead**, pointers store address
- Use **references** for pass by reference, operator overloading, aliases
- Use **pointers** for dynamic memory, optional values, pointer arithmetic
- References are **safer**, pointers are **more flexible**
- **const reference** for efficient read-only access

## Basic Template
```cpp
#include <iostream>
using namespace std;

// Reference parameter
void increment(int& x) {
    x++;
}

// Pointer parameter
void doubleValue(int* x) {
    if (x != nullptr) {
        *x *= 2;
    }
}

int main() {
    // Reference usage
    int value = 10;
    int& ref = value;
    
    cout << "Reference demo:" << endl;
    cout << "value: " << value << endl;
    ref = 20;
    cout << "After ref = 20: " << value << endl;
    increment(value);
    cout << "After increment: " << value << endl;
    
    // Pointer usage
    int num = 10;
    int* ptr = &num;
    
    cout << "\nPointer demo:" << endl;
    cout << "num: " << num << endl;
    *ptr = 20;
    cout << "After *ptr = 20: " << num << endl;
    doubleValue(ptr);
    cout << "After doubleValue: " << num << endl;
    
    // Null pointer
    int* nullPtr = nullptr;
    doubleValue(nullPtr);  // Safe - null check prevents crash
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*