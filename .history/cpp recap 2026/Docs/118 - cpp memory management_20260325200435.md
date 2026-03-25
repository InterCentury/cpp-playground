# C++ Memory Management - Complete Guide

## Table of Contents
1. [Introduction to Memory Management](#introduction-to-memory-management)
2. [Stack Memory](#stack-memory)
3. [Heap Memory](#heap-memory)
4. [Static Memory](#static-memory)
5. [Dynamic Memory Allocation (new and delete)](#dynamic-memory-allocation-new-and-delete)
6. [Pointers and Memory](#pointers-and-memory)
7. [Memory Leaks and Prevention](#memory-leaks-and-prevention)
8. [Smart Pointers](#smart-pointers)
9. [RAII (Resource Acquisition Is Initialization)](#raii-resource-acquisition-is-initialization)
10. [Memory Allocation for Arrays](#memory-allocation-for-arrays)
11. [Placement new](#placement-new)
12. [Memory Alignment and Padding](#memory-alignment-and-padding)
13. [Best Practices](#best-practices)

---

## Introduction to Memory Management

Memory management in C++ refers to the process of allocating, using, and freeing memory during program execution. C++ gives programmers direct control over memory, which provides flexibility but also responsibility.

### Memory Segments

```cpp
#include <iostream>
using namespace std;

int globalVar = 10;        // Data segment (initialized)
static int staticVar = 20; // Data segment (initialized)
int uninitGlobal;          // BSS segment (uninitialized)

const int constVar = 30;   // Read-only data segment

void function() {
    int localVar = 40;     // Stack
    static int staticLocal = 50; // Data segment (initialized once)
    int* heapVar = new int(60);  // Heap
    
    delete heapVar;
}

int main() {
    int stackVar = 70;     // Stack
    function();
    return 0;
}
```

### Memory Layout

```
High Address
┌─────────────────────────┐
│         Stack           │ ← Local variables, function calls (grows downward)
├─────────────────────────┤
│           ↓             │
│           ↑             │
├─────────────────────────┤
│         Heap            │ ← Dynamic allocation (grows upward)
├─────────────────────────┤
│   Uninitialized Data    │ ← BSS (Block Started by Symbol)
├─────────────────────────┤
│    Initialized Data     │ ← Data segment
├─────────────────────────┤
│      Text/Code          │ ← Program instructions
└─────────────────────────┘
Low Address
```

---

## Stack Memory

Stack memory is automatically managed. Variables are allocated when functions are called and deallocated when functions return.

### Stack Allocation

```cpp
#include <iostream>
using namespace std;

void function() {
    int x = 10;          // Stack allocation
    double arr[100];     // Stack allocation (fixed size)
    string s = "Hello";  // String object on stack, data on heap
}  // All stack variables automatically destroyed here

int main() {
    function();
    return 0;
}
```

### Stack Overflow

```cpp
// Dangerous recursion - causes stack overflow
void infiniteRecursion() {
    int largeArray[10000];  // Large stack allocation
    infiniteRecursion();    // No base case
}

// Stack overflow with deep recursion
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);  // Recursion depth = n
}

int main() {
    // factorial(1000000);  // Stack overflow!
    return 0;
}
```

---

## Heap Memory

Heap memory is dynamically allocated and must be manually managed by the programmer using `new` and `delete`.

### Heap Allocation

```cpp
#include <iostream>
using namespace std;

int main() {
    // Single variable
    int* ptr = new int(42);
    cout << "Value: " << *ptr << endl;
    delete ptr;
    
    // Array
    int* arr = new int[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = i * 10;
    }
    delete[] arr;
    
    return 0;
}
```

### Heap vs Stack Comparison

```cpp
#include <iostream>
#include <chrono>
using namespace std;

class LargeObject {
    char data[1024 * 1024]; // 1MB
};

int main() {
    // Stack allocation (fast, but limited)
    auto start = chrono::high_resolution_clock::now();
    LargeObject stackObj;  // Allocated on stack
    auto end = chrono::high_resolution_clock::now();
    auto stackTime = chrono::duration_cast<chrono::nanoseconds>(end - start);
    
    // Heap allocation (slower, more flexible)
    start = chrono::high_resolution_clock::now();
    LargeObject* heapObj = new LargeObject();  // Allocated on heap
    end = chrono::high_resolution_clock::now();
    auto heapTime = chrono::duration_cast<chrono::nanoseconds>(end - start);
    
    cout << "Stack allocation: " << stackTime.count() << " ns" << endl;
    cout << "Heap allocation: " << heapTime.count() << " ns" << endl;
    
    delete heapObj;
    
    return 0;
}
```

---

## Static Memory

Static variables are allocated once and persist for the entire program lifetime.

### Static Variables

```cpp
#include <iostream>
using namespace std;

class Counter {
private:
    static int count;  // Static member - one per class
    
public:
    Counter() { count++; }
    ~Counter() { count--; }
    static int getCount() { return count; }
};

int Counter::count = 0;  // Definition

void function() {
    static int callCount = 0;  // Static local - initialized once
    callCount++;
    cout << "Function called " << callCount << " times" << endl;
}

int main() {
    function();
    function();
    function();
    
    Counter c1, c2, c3;
    cout << "Counter objects: " << Counter::getCount() << endl;
    
    return 0;
}
```

---

## Dynamic Memory Allocation (new and delete)

### new and delete for Single Objects

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    
public:
    Student(string n, int a) : name(n), age(a) {
        cout << "Student created: " << name << endl;
    }
    
    ~Student() {
        cout << "Student destroyed: " << name << endl;
    }
    
    void display() const {
        cout << name << ", " << age << " years" << endl;
    }
};

int main() {
    // Allocate single object
    Student* s1 = new Student("John", 20);
    s1->display();
    delete s1;
    
    // Allocate with default constructor
    int* num = new int(42);
    cout << "*num = " << *num << endl;
    delete num;
    
    // Allocate array
    int* arr = new int[5];
    for (int i = 0; i < 5; i++) arr[i] = i * 10;
    delete[] arr;
    
    return 0;
}
```

### new and delete for Arrays

```cpp
#include <iostream>
using namespace std;

int main() {
    // 1D array
    int* arr1D = new int[10];
    delete[] arr1D;
    
    // 2D array (array of pointers)
    int** arr2D = new int*[3];
    for (int i = 0; i < 3; i++) {
        arr2D[i] = new int[4];
    }
    
    // Use the array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            arr2D[i][j] = i * 4 + j;
        }
    }
    
    // Cleanup - reverse order of allocation
    for (int i = 0; i < 3; i++) {
        delete[] arr2D[i];
    }
    delete[] arr2D;
    
    // 3D array
    int*** arr3D = new int**[2];
    for (int i = 0; i < 2; i++) {
        arr3D[i] = new int*[3];
        for (int j = 0; j < 3; j++) {
            arr3D[i][j] = new int[4];
        }
    }
    
    // Cleanup
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            delete[] arr3D[i][j];
        }
        delete[] arr3D[i];
    }
    delete[] arr3D;
    
    return 0;
}
```

### new with Initialization

```cpp
#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

int main() {
    // Different initialization methods
    int* p1 = new int;        // Uninitialized
    int* p2 = new int();      // Zero-initialized
    int* p3 = new int(42);    // Value-initialized
    
    Point* pt1 = new Point;        // Default constructor
    Point* pt2 = new Point(10, 20); // Parameterized constructor
    
    cout << "*p2 = " << *p2 << endl;
    cout << "*p3 = " << *p3 << endl;
    cout << "Point: (" << pt2->x << ", " << pt2->y << ")" << endl;
    
    delete p1;
    delete p2;
    delete p3;
    delete pt1;
    delete pt2;
    
    return 0;
}
```

---

## Pointers and Memory

### Pointer Basics

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* ptr = &value;      // Pointer to value
    
    cout << "Value: " << value << endl;
    cout << "Address: " << &value << endl;
    cout << "Pointer value: " << ptr << endl;
    cout << "Dereferenced: " << *ptr << endl;
    
    // Modify through pointer
    *ptr = 100;
    cout << "After modification: " << value << endl;
    
    // Null pointer
    int* nullPtr = nullptr;
    if (nullPtr != nullptr) {
        *nullPtr = 10;  // Won't execute
    }
    
    return 0;
}
```

### Pointer Arithmetic

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    cout << "Pointer arithmetic:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "*(ptr + " << i << ") = " << *(ptr + i) << endl;
    }
    
    cout << "\nMoving pointer:" << endl;
    cout << "*ptr = " << *ptr << endl;
    ptr++;
    cout << "*ptr++ = " << *ptr << endl;
    ptr += 2;
    cout << "ptr += 2: " << *ptr << endl;
    
    // Pointer difference
    int* start = arr;
    int* end = arr + 5;
    cout << "\nNumber of elements: " << (end - start) << endl;
    
    return 0;
}
```

### Pointers to Pointers

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
    cout << "After modification: " << value << endl;
    
    // Change pointer through double pointer
    int newValue = 200;
    *doublePtr = &newValue;
    cout << "*ptr now points to: " << *ptr << endl;
    
    return 0;
}
```

### Void Pointers

```cpp
#include <iostream>
using namespace std;

int main() {
    int intValue = 42;
    double doubleValue = 3.14;
    
    void* voidPtr;
    
    voidPtr = &intValue;
    cout << "int value: " << *(static_cast<int*>(voidPtr)) << endl;
    
    voidPtr = &doubleValue;
    cout << "double value: " << *(static_cast<double*>(voidPtr)) << endl;
    
    // Cannot dereference void pointer directly
    // cout << *voidPtr;  // Error!
    
    return 0;
}
```

---

## Memory Leaks and Prevention

### What is a Memory Leak?

```cpp
#include <iostream>
using namespace std;

void memoryLeak() {
    int* leak = new int(10);
    // No delete - memory leak!
}  // Memory remains allocated after function exits

void noLeak() {
    int* ptr = new int(10);
    delete ptr;  // Proper cleanup
}

int main() {
    for (int i = 0; i < 1000; i++) {
        memoryLeak();  // Leaks memory each call
        // noLeak();   // No leak
    }
    
    return 0;
}
```

### Detecting Memory Leaks

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

// Simple memory tracker
class MemoryTracker {
private:
    static size_t allocations;
    static size_t deallocations;
    
public:
    static void* allocate(size_t size) {
        allocations++;
        return malloc(size);
    }
    
    static void deallocate(void* ptr) {
        if (ptr) {
            deallocations++;
            free(ptr);
        }
    }
    
    static void report() {
        cout << "Allocations: " << allocations << endl;
        cout << "Deallocations: " << deallocations << endl;
        if (allocations != deallocations) {
            cout << "Memory leak detected! " 
                 << (allocations - deallocations) << " leaks" << endl;
        }
    }
};

size_t MemoryTracker::allocations = 0;
size_t MemoryTracker::deallocations = 0;

void* operator new(size_t size) {
    return MemoryTracker::allocate(size);
}

void operator delete(void* ptr) noexcept {
    MemoryTracker::deallocate(ptr);
}

int main() {
    int* p1 = new int(10);
    int* p2 = new int(20);
    // delete p2;  // Uncomment to fix leak
    
    MemoryTracker::report();
    
    delete p1;
    
    return 0;
}
```

### Common Causes of Memory Leaks

```cpp
#include <iostream>
#include <string>
using namespace std;

class Resource {
public:
    int* data;
    Resource() {
        data = new int[1000];
        cout << "Resource allocated" << endl;
    }
    ~Resource() {
        delete[] data;
        cout << "Resource freed" << endl;
    }
};

// 1. Lost pointer
void lostPointer() {
    int* ptr = new int(10);
    ptr = new int(20);  // Lost access to first allocation
    delete ptr;
}

// 2. Exception before delete
void exceptionLeak() {
    int* ptr = new int(10);
    throw runtime_error("Exception");  // Delete never reached
    delete ptr;
}

// 3. Circular references
class Node {
public:
    Node* next;
    Node() : next(nullptr) {}
    ~Node() { cout << "Node destroyed" << endl; }
};

void circularReference() {
    Node* a = new Node();
    Node* b = new Node();
    a->next = b;
    b->next = a;  // Circular reference
    // Both nodes leaked
}

// 4. Forgetting to delete array properly
void wrongDelete() {
    int* arr = new int[10];
    delete arr;  // Should be delete[] arr
}

int main() {
    // Resource r;  // Stack object - automatically cleaned
    
    // lostPointer();
    // exceptionLeak();
    // circularReference();
    // wrongDelete();
    
    return 0;
}
```

---

## Smart Pointers

### unique_ptr (C++11)

```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Widget {
private:
    int id;
    static int nextId;
    
public:
    Widget() : id(nextId++) {
        cout << "Widget " << id << " created" << endl;
    }
    ~Widget() {
        cout << "Widget " << id << " destroyed" << endl;
    }
    void doSomething() {
        cout << "Widget " << id << " doing something" << endl;
    }
};

int Widget::nextId = 1;

int main() {
    // Basic unique_ptr
    unique_ptr<Widget> ptr1(new Widget());
    ptr1->doSomething();
    
    // Transfer ownership (move)
    unique_ptr<Widget> ptr2 = move(ptr1);
    if (!ptr1) {
        cout << "ptr1 is now null" << endl;
    }
    ptr2->doSomething();
    
    // Array with unique_ptr
    unique_ptr<int[]> arr(new int[5]);
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Vector of unique_ptr
    vector<unique_ptr<Widget>> widgets;
    widgets.push_back(make_unique<Widget>());
    widgets.push_back(make_unique<Widget>());
    
    return 0;
}
```

### shared_ptr (C++11)

```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class SharedResource {
private:
    string name;
    
public:
    SharedResource(string n) : name(n) {
        cout << "Resource " << name << " created" << endl;
    }
    ~SharedResource() {
        cout << "Resource " << name << " destroyed" << endl;
    }
    void use() {
        cout << "Using resource " << name << endl;
    }
};

int main() {
    // Basic shared_ptr
    shared_ptr<SharedResource> ptr1 = make_shared<SharedResource>("A");
    {
        shared_ptr<SharedResource> ptr2 = ptr1;  // Share ownership
        shared_ptr<SharedResource> ptr3 = ptr1;  // Share ownership
        cout << "Reference count: " << ptr1.use_count() << endl;
        ptr2->use();
    }  // ptr2 and ptr3 destroyed, resource still alive
    cout << "Reference count: " << ptr1.use_count() << endl;
    
    // Vector of shared_ptr
    vector<shared_ptr<SharedResource>> resources;
    resources.push_back(make_shared<SharedResource>("X"));
    resources.push_back(make_shared<SharedResource>("Y"));
    resources.push_back(make_shared<SharedResource>("Z"));
    
    // Circular reference problem
    struct Node {
        shared_ptr<Node> next;
        ~Node() { cout << "Node destroyed" << endl; }
    };
    
    auto a = make_shared<Node>();
    auto b = make_shared<Node>();
    a->next = b;
    b->next = a;  // Circular reference - memory leak!
    
    return 0;
}
```

### weak_ptr (C++11)

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Observer {
public:
    void update() {
        cout << "Observer updated" << endl;
    }
};

class Subject {
private:
    weak_ptr<Observer> observer;
    
public:
    void registerObserver(shared_ptr<Observer> obs) {
        observer = obs;
    }
    
    void notify() {
        if (auto obs = observer.lock()) {
            obs->update();
        } else {
            cout << "Observer no longer exists" << endl;
        }
    }
};

int main() {
    Subject subject;
    
    {
        auto observer = make_shared<Observer>();
        subject.registerObserver(observer);
        subject.notify();  // Observer exists
    }  // Observer destroyed
    
    subject.notify();  // Observer no longer exists
    
    return 0;
}
```

### Smart Pointer Comparison

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Test {
public:
    Test() { cout << "Created" << endl; }
    ~Test() { cout << "Destroyed" << endl; }
};

int main() {
    // raw pointer - manual management
    Test* raw = new Test();
    delete raw;
    
    // unique_ptr - exclusive ownership
    unique_ptr<Test> unique = make_unique<Test>();
    // unique_ptr cannot be copied
    // unique_ptr<Test> unique2 = unique;  // Error!
    
    // shared_ptr - shared ownership
    shared_ptr<Test> shared1 = make_shared<Test>();
    shared_ptr<Test> shared2 = shared1;  // OK
    cout << "Shared count: " << shared1.use_count() << endl;
    
    // weak_ptr - non-owning reference
    weak_ptr<Test> weak = shared1;
    if (auto shared = weak.lock()) {
        cout << "Still alive" << endl;
    }
    
    return 0;
}
```

---

## RAII (Resource Acquisition Is Initialization)

### Basic RAII Pattern

```cpp
#include <iostream>
#include <fstream>
#include <mutex>
using namespace std;

// RAII for file handling
class FileHandler {
private:
    FILE* file;
    
public:
    FileHandler(const char* filename, const char* mode) {
        file = fopen(filename, mode);
        if (!file) {
            throw runtime_error("Cannot open file");
        }
        cout << "File opened" << endl;
    }
    
    ~FileHandler() {
        if (file) {
            fclose(file);
            cout << "File closed" << endl;
        }
    }
    
    void write(const char* data) {
        fprintf(file, "%s", data);
    }
};

// RAII for mutex
class LockGuard {
private:
    mutex& mtx;
    
public:
    LockGuard(mutex& m) : mtx(m) {
        mtx.lock();
        cout << "Mutex locked" << endl;
    }
    
    ~LockGuard() {
        mtx.unlock();
        cout << "Mutex unlocked" << endl;
    }
};

int main() {
    // File handling with RAII
    try {
        FileHandler file("test.txt", "w");
        file.write("Hello World");
        // File automatically closed when file goes out of scope
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // Mutex with RAII
    mutex mtx;
    {
        LockGuard lock(mtx);
        // Critical section
        cout << "Critical section" << endl;
    }  // Mutex automatically unlocked
    
    return 0;
}
```

### Custom RAII Class

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Buffer {
private:
    char* data;
    size_t size;
    
public:
    // Constructor - acquires resource
    Buffer(size_t s) : size(s) {
        data = new char[size];
        cout << "Buffer allocated: " << size << " bytes" << endl;
    }
    
    // Destructor - releases resource
    ~Buffer() {
        delete[] data;
        cout << "Buffer deallocated" << endl;
    }
    
    // Copy constructor - deep copy
    Buffer(const Buffer& other) : size(other.size) {
        data = new char[size];
        memcpy(data, other.data, size);
        cout << "Buffer copied" << endl;
    }
    
    // Assignment operator - deep copy
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size];
            memcpy(data, other.data, size);
            cout << "Buffer assigned" << endl;
        }
        return *this;
    }
    
    // Move constructor - transfer ownership
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "Buffer moved" << endl;
    }
    
    char* get() { return data; }
    size_t getSize() const { return size; }
};

int main() {
    {
        Buffer buf1(1024);
        Buffer buf2 = buf1;  // Copy
        Buffer buf3 = move(buf1);  // Move
    }  // All buffers automatically destroyed
    
    return 0;
}
```

---

## Memory Allocation for Arrays

### 1D Arrays

```cpp
#include <iostream>
using namespace std;

int main() {
    // Stack allocation (fixed size)
    int stackArr[100];
    
    // Heap allocation (dynamic size)
    int size;
    cout << "Enter array size: ";
    cin >> size;
    int* heapArr = new int[size];
    
    // Initialize
    for (int i = 0; i < size; i++) {
        heapArr[i] = i * 10;
    }
    
    // Use
    for (int i = 0; i < size; i++) {
        cout << heapArr[i] << " ";
    }
    cout << endl;
    
    // Cleanup
    delete[] heapArr;
    
    return 0;
}
```

### 2D Arrays (Different Methods)

```cpp
#include <iostream>
using namespace std;

// Method 1: Array of pointers (jagged arrays)
int** create2DArray1(int rows, int cols) {
    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }
    return arr;
}

void delete2DArray1(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

// Method 2: Single contiguous block
int* create2DArray2(int rows, int cols) {
    return new int[rows * cols];
}

int& getElement2(int* arr, int rows, int cols, int i, int j) {
    return arr[i * cols + j];
}

// Method 3: Using 1D array of 1D arrays
int (*create2DArray3(int rows, int cols))[4] {
    // Only works if cols is known at compile time
    int (*arr)[4] = new int[rows][4];
    return arr;
}

int main() {
    int rows = 3, cols = 4;
    
    // Method 1
    int** arr1 = create2DArray1(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr1[i][j] = i * cols + j;
        }
    }
    delete2DArray1(arr1, rows);
    
    // Method 2
    int* arr2 = create2DArray2(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            getElement2(arr2, rows, cols, i, j) = i * cols + j;
        }
    }
    delete[] arr2;
    
    return 0;
}
```

### 3D Arrays

```cpp
#include <iostream>
using namespace std;

int*** create3DArray(int depth, int rows, int cols) {
    int*** arr = new int**[depth];
    for (int i = 0; i < depth; i++) {
        arr[i] = new int*[rows];
        for (int j = 0; j < rows; j++) {
            arr[i][j] = new int[cols];
        }
    }
    return arr;
}

void delete3DArray(int*** arr, int depth, int rows) {
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < rows; j++) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
}

int main() {
    int depth = 2, rows = 3, cols = 4;
    int*** arr = create3DArray(depth, rows, cols);
    
    // Initialize
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                arr[i][j][k] = i * 100 + j * 10 + k;
            }
        }
    }
    
    // Use
    for (int i = 0; i < depth; i++) {
        cout << "Layer " << i << ":" << endl;
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                cout << arr[i][j][k] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    delete3DArray(arr, depth, rows);
    
    return 0;
}
```

---

## Placement new

```cpp
#include <iostream>
#include <new>
using namespace std;

class MyClass {
private:
    int value;
    
public:
    MyClass(int v) : value(v) {
        cout << "MyClass constructed with value " << value << endl;
    }
    
    ~MyClass() {
        cout << "MyClass destructed" << endl;
    }
    
    void show() {
        cout << "Value: " << value << endl;
    }
};

int main() {
    // Allocate raw memory
    char* buffer = new char[sizeof(MyClass)];
    
    // Construct object in pre-allocated memory
    MyClass* obj = new (buffer) MyClass(42);
    obj->show();
    
    // Manually call destructor
    obj->~MyClass();
    
    // Deallocate raw memory
    delete[] buffer;
    
    // Placement new with array
    char* buffer2 = new char[3 * sizeof(MyClass)];
    MyClass* arr = reinterpret_cast<MyClass*>(buffer2);
    
    for (int i = 0; i < 3; i++) {
        new (&arr[i]) MyClass(i * 10);
    }
    
    for (int i = 0; i < 3; i++) {
        arr[i].show();
        arr[i].~MyClass();
    }
    
    delete[] buffer2;
    
    return 0;
}
```

---

## Memory Alignment and Padding

```cpp
#include <iostream>
#include <cstddef>
using namespace std;

struct A {
    char c;      // 1 byte
    int i;       // 4 bytes
    short s;     // 2 bytes
};  // Typical size: 12 bytes (with padding)

struct B {
    int i;       // 4 bytes
    char c;      // 1 byte
    short s;     // 2 bytes
};  // Typical size: 8 bytes (more efficient packing)

struct C {
    char c1;     // 1 byte
    char c2;     // 1 byte
    int i;       // 4 bytes
};  // Typical size: 8 bytes

struct D {
    char c;      // 1 byte
    double d;    // 8 bytes
};  // Typical size: 16 bytes (8-byte alignment for double)

#pragma pack(push, 1)
struct Packed {
    char c;      // 1 byte
    int i;       // 4 bytes
    short s;     // 2 bytes
};  // Size: 7 bytes (no padding)
#pragma pack(pop)

int main() {
    cout << "sizeof(A) = " << sizeof(A) << " bytes" << endl;
    cout << "sizeof(B) = " << sizeof(B) << " bytes" << endl;
    cout << "sizeof(C) = " << sizeof(C) << " bytes" << endl;
    cout << "sizeof(D) = " << sizeof(D) << " bytes" << endl;
    cout << "sizeof(Packed) = " << sizeof(Packed) << " bytes" << endl;
    
    // Member offsets
    cout << "\nOffsets in A:" << endl;
    cout << "c: " << offsetof(A, c) << endl;
    cout << "i: " << offsetof(A, i) << endl;
    cout << "s: " << offsetof(A, s) << endl;
    
    cout << "\nOffsets in B:" << endl;
    cout << "i: " << offsetof(B, i) << endl;
    cout << "c: " << offsetof(B, c) << endl;
    cout << "s: " << offsetof(B, s) << endl;
    
    return 0;
}
```

---

## Best Practices

### 1. Prefer Stack Allocation When Possible

```cpp
// Good - stack allocation
void good() {
    int arr[100];
    string s = "Hello";
    vector<int> v(1000);  // Vector manages heap internally
}

// Avoid unnecessary heap allocation
void bad() {
    int* arr = new int[100];
    string* s = new string("Hello");
    delete[] arr;
    delete s;
}
```

### 2. Use Smart Pointers

```cpp
// Good - automatic memory management
void good() {
    unique_ptr<int> ptr = make_unique<int>(42);
    shared_ptr<vector<int>> vec = make_shared<vector<int>>();
}

// Avoid raw pointers
void bad() {
    int* ptr = new int(42);
    delete ptr;
}
```

### 3. Follow RAII Principle

```cpp
class ResourceManager {
private:
    int* data;
    size_t size;
    
public:
    ResourceManager(size_t s) : size(s) {
        data = new int[size];
    }
    
    ~ResourceManager() {
        delete[] data;
    }
    
    // Prevent copying or implement properly
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    // Move semantics
    ResourceManager(ResourceManager&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
};
```

### 4. Use Standard Containers

```cpp
// Good - standard containers manage memory
void good() {
    vector<int> vec(1000);
    map<string, int> dict;
    list<double> lst;
}

// Avoid manual memory management
void bad() {
    int* arr = new int[1000];
    delete[] arr;
}
```

### 5. Be Aware of Memory Alignment

```cpp
// Order members by size (largest to smallest) to reduce padding
struct Efficient {
    double d;      // 8 bytes
    int i;         // 4 bytes
    short s;       // 2 bytes
    char c;        // 1 byte
};  // Typically 16 bytes

struct Inefficient {
    char c;        // 1 byte
    double d;      // 8 bytes
    int i;         // 4 bytes
    short s;       // 2 bytes
};  // Typically 24 bytes
```

### 6. Use move Semantics for Large Objects

```cpp
vector<int> createLargeVector() {
    vector<int> v(1000000);
    // Fill vector
    return v;  // Move semantics (no copy)
}

int main() {
    vector<int> big = createLargeVector();  // Efficient move
    return 0;
}
```

### 7. Avoid Memory Leaks in Exception-Prone Code

```cpp
// Bad - memory leak on exception
void bad() {
    int* ptr = new int(10);
    throw runtime_error("Error");  // Memory leak!
    delete ptr;
}

// Good - RAII prevents leak
void good() {
    unique_ptr<int> ptr = make_unique<int>(10);
    throw runtime_error("Error");  // No leak
}
```

### 8. Use Custom Allocators When Needed

```cpp
#include <memory>
#include <vector>
using namespace std;

template<typename T>
class PoolAllocator {
    // Custom allocation strategy
};

int main() {
    // Use custom allocator for specific needs
    vector<int, PoolAllocator<int>> vec;
    return 0;
}
```

---

## Summary

| Memory Type | Allocation | Deallocation | Lifetime | Scope |
|-------------|------------|--------------|----------|-------|
| Stack | Automatic | Automatic | Function scope | Local |
| Heap | `new`, `malloc` | `delete`, `free` | Until deleted | Program-wide |
| Static | Compile-time | Program end | Program lifetime | Global/Class |
| Thread-local | Thread start | Thread end | Thread lifetime | Thread |

### Key Principles

1. **Always match `new` with `delete`, `new[]` with `delete[]`**
2. **Prefer stack allocation over heap when possible**
3. **Use smart pointers instead of raw pointers**
4. **Follow RAII principle - acquire resources in constructor, release in destructor**
5. **Use standard containers instead of manual arrays**
6. **Be aware of memory alignment and padding**
7. **Use move semantics for efficient transfers**
8. **Never return pointers/references to local variables**
9. **Always check for null after allocation**
10. **Use tools like Valgrind to detect memory leaks**

### Memory Management Tools

- **Valgrind** - Memory leak detection
- **AddressSanitizer** - Memory error detection
- **Dr. Memory** - Memory monitoring
- **Visual Studio Diagnostic Tools** - Memory profiling

---
*This documentation belongs to https://github.com/InterCentury*