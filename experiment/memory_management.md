I'll create comprehensive documentation about C++ memory management including pointers.

# Comprehensive Guide to C++ Memory Management

## Table of Contents
1. [Introduction to Memory Management](#introduction)
2. [Stack vs Heap Memory](#stack-vs-heap)
3. [Pointers Fundamentals](#pointers-fundamentals)
4. [Dynamic Memory Allocation](#dynamic-memory-allocation)
5. [Smart Pointers](#smart-pointers)
6. [Memory Leaks and Prevention](#memory-leaks)
7. [Best Practices](#best-practices)
8. [Advanced Topics](#advanced-topics)

---

## 1. Introduction to Memory Management {#introduction}

C++ gives programmers direct control over memory management, which provides flexibility but also requires careful handling to avoid errors. Memory management involves:
- Allocating memory for program variables
- Deallocating memory when no longer needed
- Preventing memory leaks and undefined behavior

---

## 2. Stack vs Heap Memory {#stack-vs-heap}

### Stack Memory
- **Automatic management**: Variables are automatically allocated and deallocated
- **LIFO structure**: Functions push/pop frames
- **Fixed size**: Limited memory (typically 1-8 MB)
- **Fast access**: Direct memory addressing
- **Scope-bound**: Variables exist only within their scope

```cpp
void stackExample() {
    int x = 10;              // Stored on stack
    int arr[100];            // Array on stack
    std::string str = "Hello"; // String object on stack (data may be on heap)
} // All stack variables automatically destroyed here
```

### Heap Memory
- **Manual management**: Explicit allocation/deallocation required
- **Dynamic size**: Can allocate large amounts of memory
- **Slower access**: Requires pointer indirection
- **Persistent**: Memory persists until explicitly freed
- **Fragmentation potential**: Can cause memory fragmentation over time

---

## 3. Pointers Fundamentals {#pointers-fundamentals}

### Basic Pointer Concepts

```cpp
#include <iostream>

int main() {
    // Pointer declaration
    int* ptr;                    // Uninitialized pointer (dangerous!)
    int* ptr2 = nullptr;         // Null pointer (safe initialization)
    
    int value = 42;
    int* ptr3 = &value;          // Pointer to value's address
    
    // Dereferencing
    std::cout << *ptr3;          // Outputs: 42
    *ptr3 = 100;                 // Changes value to 100
    
    // Pointer arithmetic
    int arr[] = {10, 20, 30, 40};
    int* arrPtr = arr;            // Points to arr[0]
    std::cout << *(arrPtr + 2);   // Outputs: 30 (arr[2])
    
    return 0;
}
```

### Types of Pointers

```cpp
// 1. Raw Pointers
int* rawPtr = new int(42);
delete rawPtr;

// 2. Pointers to Pointers (Double Pointers)
int value = 42;
int* ptr = &value;
int** doublePtr = &ptr;
std::cout << **doublePtr;  // Outputs: 42

// 3. Function Pointers
int add(int a, int b) { return a + b; }
int (*funcPtr)(int, int) = &add;
std::cout << funcPtr(5, 3);  // Outputs: 8

// 4. Void Pointers (Type-erased)
void* voidPtr = new int(42);
int* intPtr = static_cast<int*>(voidPtr);
delete intPtr;

// 5. Const Pointers
int x = 10, y = 20;
const int* ptr1 = &x;      // Pointer to const int (can't modify value)
int* const ptr2 = &x;      // Const pointer (can't change address)
const int* const ptr3 = &x; // Both const
```

### Pointer Arithmetic

```cpp
void pointerArithmetic() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // Points to arr[0]
    
    // Increment/Decrement
    ptr++;           // Now points to arr[1]
    ptr--;           // Back to arr[0]
    
    // Addition/Subtraction
    ptr = ptr + 2;   // Points to arr[2]
    ptr = ptr - 1;   // Points to arr[1]
    
    // Difference between pointers
    int* start = arr;
    int* end = arr + 5;
    ptrdiff_t diff = end - start;  // 5
    
    // Comparison
    if (ptr < end) {
        // Valid comparison for pointers in same array
    }
}
```

---

## 4. Dynamic Memory Allocation {#dynamic-memory-allocation}

### new and delete Operators

```cpp
// Single object allocation
int* pInt = new int;           // Uninitialized
int* pInt2 = new int(42);      // Initialized to 42
int* pInt3 = new int();        // Zero-initialized

delete pInt;
delete pInt2;
delete pInt3;

// Array allocation
int* pArray = new int[100];     // Allocates array of 100 ints
delete[] pArray;                // Must use delete[] for arrays

// 2D array allocation
int** matrix = new int*[3];     // Allocate rows
for (int i = 0; i < 3; ++i) {
    matrix[i] = new int[4];      // Allocate columns
}

// Deallocate 2D array
for (int i = 0; i < 3; ++i) {
    delete[] matrix[i];
}
delete[] matrix;
```

### Placement New

```cpp
#include <new>

void placementNew() {
    char buffer[sizeof(int)];
    int* pInt = new (buffer) int(42);  // Constructs int in buffer
    
    std::cout << *pInt;                 // Outputs: 42
    
    pInt->~int();                       // Must call destructor manually
}
```

### Memory Alignment

```cpp
#include <memory>

void alignment() {
    alignas(16) int alignedInt;         // 16-byte aligned
    alignas(alignof(double)) char buffer[sizeof(double)];
    
    // C++17: aligned allocation
    double* pDouble = new (std::align_val_t{alignof(double)}) double(3.14);
    delete pDouble;
}
```

---

## 5. Smart Pointers {#smart-pointers}

### std::unique_ptr
Exclusive ownership, cannot be copied, only moved.

```cpp
#include <memory>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
    void doWork() { std::cout << "Working...\n"; }
};

void uniquePtrExamples() {
    // Creating unique_ptr
    auto p1 = std::make_unique<Resource>();  // Preferred
    std::unique_ptr<Resource> p2(new Resource());  // Legacy way
    
    // Transfer ownership
    auto p3 = std::move(p1);  // p1 now null, p3 owns resource
    
    // Custom deleter
    auto p4 = std::unique_ptr<FILE, decltype(&fclose)>(
        fopen("test.txt", "r"), fclose);
    
    // Release ownership
    Resource* raw = p3.release();  // p3 loses ownership, no deletion
    delete raw;                     // Must manually delete
    
    // Reset
    p2.reset();                     // Deletes managed object
    p2.reset(new Resource());       // Deletes old, manages new
    
    // Access
    if (p3) {                       // Check if not null
        p3->doWork();
        (*p3).doWork();
    }
}

// Returning unique_ptr from function
std::unique_ptr<Resource> createResource() {
    return std::make_unique<Resource>();  // Move semantics automatically applied
}
```

### std::shared_ptr
Shared ownership, reference counting.

```cpp
#include <memory>

void sharedPtrExamples() {
    // Creating shared_ptr
    auto sp1 = std::make_shared<Resource>();  // Preferred
    std::shared_ptr<Resource> sp2(new Resource());
    
    // Shared ownership
    auto sp3 = sp1;  // Reference count increases to 2
    
    std::cout << "Use count: " << sp1.use_count();  // Outputs: 2
    
    // Custom deleter
    auto sp4 = std::shared_ptr<Resource>(
        new Resource(),
        [](Resource* p) { delete p; }
    );
    
    // Cyclic references problem
    struct Node {
        std::shared_ptr<Node> next;
        ~Node() { std::cout << "Node destroyed\n"; }
    };
    
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    node1->next = node2;
    node2->next = node1;  // Circular reference - memory leak!
    
    // Solution: use weak_ptr
    struct NodeSafe {
        std::weak_ptr<NodeSafe> next;
        ~NodeSafe() { std::cout << "Node destroyed\n"; }
    };
}
```

### std::weak_ptr
Non-owning reference, breaks circular references.

```cpp
void weakPtrExamples() {
    auto sp = std::make_shared<Resource>();
    std::weak_ptr<Resource> wp = sp;  // Doesn't increase reference count
    
    // Check if resource still exists
    if (auto locked = wp.lock()) {
        locked->doWork();  // Resource still exists
    } else {
        std::cout << "Resource destroyed\n";
    }
    
    // Check expiration
    if (wp.expired()) {
        std::cout << "Weak pointer expired\n";
    }
}
```

### Smart Pointer Comparison

| Feature | unique_ptr | shared_ptr | weak_ptr |
|---------|------------|------------|----------|
| Ownership | Exclusive | Shared | Non-owning |
| Overhead | Minimal | Reference counting | Minimal |
| Copyable | No | Yes | Yes |
| Movable | Yes | Yes | Yes |
| Thread-safe | No | Yes (ref count) | Yes |
| Use case | Single ownership | Shared ownership | Break cycles, caching |

---

## 6. Memory Leaks and Prevention {#memory-leaks}

### Common Memory Leak Patterns

```cpp
// 1. Forgetting to delete
void leak1() {
    int* p = new int(42);
    // No delete - memory leak
}

// 2. Exception before delete
void leak2() {
    int* p = new int(42);
    throw std::runtime_error("Error");
    delete p;  // Never reached
}

// 3. Array delete mismatch
void leak3() {
    int* arr = new int[100];
    delete arr;  // Should be delete[] arr
}

// 4. Circular references
struct Parent {
    std::shared_ptr<Child> child;
};
struct Child {
    std::shared_ptr<Parent> parent;  // Circular reference
};
```

### Detection Tools

```cpp
// Using Valgrind (Linux)
// $ valgrind --leak-check=full ./program

// Using AddressSanitizer (Clang/GCC)
// $ g++ -fsanitize=address -g program.cpp -o program

// Custom leak detection
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
```

### RAII (Resource Acquisition Is Initialization)

```cpp
// Manual resource management (BAD)
class BadResource {
    int* data;
public:
    BadResource(size_t size) {
        data = new int[size];
    }
    ~BadResource() {
        delete[] data;  // What if copy occurs?
    }
    // Missing copy/move operations - will cause double delete!
};

// RAII with smart pointers (GOOD)
class GoodResource {
    std::unique_ptr<int[]> data;
public:
    GoodResource(size_t size) : data(std::make_unique<int[]>(size)) {}
    // Copy/move operations are properly handled
};

// Custom RAII wrapper
template<typename T>
class RAIIWrapper {
    T* resource;
public:
    RAIIWrapper(T* ptr = nullptr) : resource(ptr) {}
    ~RAIIWrapper() { delete resource; }
    
    RAIIWrapper(const RAIIWrapper&) = delete;
    RAIIWrapper& operator=(const RAIIWrapper&) = delete;
    
    RAIIWrapper(RAIIWrapper&& other) noexcept : resource(other.resource) {
        other.resource = nullptr;
    }
    
    RAIIWrapper& operator=(RAIIWrapper&& other) noexcept {
        if (this != &other) {
            delete resource;
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }
    
    T* operator->() { return resource; }
    T& operator*() { return *resource; }
};
```

---

## 7. Best Practices {#best-practices}

### Memory Management Guidelines

```cpp
// 1. Prefer stack allocation over heap when possible
void bestPractice1() {
    // GOOD
    int arr[100];
    std::vector<int> vec(100);  // Still uses heap but managed
    
    // AVOID unless necessary
    int* arr = new int[100];
    delete[] arr;
}

// 2. Use smart pointers instead of raw pointers for ownership
void bestPractice2() {
    // GOOD
    auto ptr = std::make_unique<Resource>();
    
    // AVOID
    Resource* raw = new Resource();
    delete raw;
}

// 3. Use nullptr instead of NULL or 0
void bestPractice3() {
    int* ptr = nullptr;  // GOOD
    // int* ptr = NULL;  // AVOID
    // int* ptr = 0;     // AVOID
}

// 4. Follow Rule of Three/Five/Zero
class RuleOfFive {
    int* data;
    size_t size;
public:
    // Rule of Zero - use smart pointers
    // Or implement Rule of Five
    RuleOfFive() : data(nullptr), size(0) {}
    
    ~RuleOfFive() { delete[] data; }
    
    RuleOfFive(const RuleOfFive& other) : size(other.size) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
    }
    
    RuleOfFive(RuleOfFive&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
    
    RuleOfFive& operator=(const RuleOfFive& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }
    
    RuleOfFive& operator=(RuleOfFive&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
};

// 5. Use make_unique/make_shared
void bestPractice4() {
    // GOOD - exception safe, single allocation
    auto ptr = std::make_unique<Resource>();
    auto sptr = std::make_shared<Resource>();
    
    // AVOID - exception unsafe, double allocation (shared_ptr)
    std::shared_ptr<Resource> bad(new Resource());
}

// 6. Never return raw pointers to owned resources
class Database {
    std::unique_ptr<Connection> conn;
public:
    // BAD - exposes ownership
    Connection* getConnection() { return conn.get(); }
    
    // GOOD - provides access without ownership
    Connection& getConnection() { return *conn; }
};

// 7. Use std::array for fixed-size arrays
void bestPractice5() {
    std::array<int, 10> arr;  // GOOD - stack allocated
    int carr[10];              // Also OK but less features
}
```

### Performance Considerations

```cpp
// 1. Avoid unnecessary allocations
void performance1() {
    // BAD - allocates in loop
    for (int i = 0; i < 1000; ++i) {
        std::vector<int> vec(100);
        // use vec
    }
    
    // GOOD - single allocation
    std::vector<int> vec(100);
    for (int i = 0; i < 1000; ++i) {
        vec.clear();  // Reuse memory
        // use vec
    }
}

// 2. Use reserve to avoid reallocations
void performance2() {
    std::vector<int> vec;
    vec.reserve(1000);  // Allocate once
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);
    }
}

// 3. Use move semantics
void performance3() {
    std::vector<int> createVector() {
        std::vector<int> vec(1000);
        return vec;  // Move or RVO
    }
    
    auto vec = createVector();  // No copy
}
```

---

## 8. Advanced Topics {#advanced-topics}

### Custom Allocators

```cpp
#include <memory>

template<typename T>
class PoolAllocator {
    struct Block {
        Block* next;
    };
    
    Block* freeList;
    void* pool;
    size_t blockSize;
    size_t poolSize;
    
public:
    using value_type = T;
    
    PoolAllocator(size_t numBlocks) 
        : blockSize(sizeof(T) > sizeof(Block*) ? sizeof(T) : sizeof(Block*)),
          poolSize(blockSize * numBlocks) {
        pool = std::malloc(poolSize);
        freeList = static_cast<Block*>(pool);
        
        // Initialize free list
        auto current = freeList;
        for (size_t i = 0; i < numBlocks - 1; ++i) {
            current->next = reinterpret_cast<Block*>(
                reinterpret_cast<char*>(current) + blockSize);
            current = current->next;
        }
        current->next = nullptr;
    }
    
    ~PoolAllocator() {
        std::free(pool);
    }
    
    T* allocate(size_t n) {
        if (n != 1) throw std::bad_alloc();
        
        if (!freeList) throw std::bad_alloc();
        
        auto block = freeList;
        freeList = freeList->next;
        return reinterpret_cast<T*>(block);
    }
    
    void deallocate(T* ptr, size_t n) {
        auto block = reinterpret_cast<Block*>(ptr);
        block->next = freeList;
        freeList = block;
    }
    
    template<typename U>
    bool operator==(const PoolAllocator<U>& other) const {
        return pool == other.pool;
    }
    
    template<typename U>
    bool operator!=(const PoolAllocator<U>& other) const {
        return !(*this == other);
    }
};

// Usage
void customAllocator() {
    std::vector<int, PoolAllocator<int>> vec(PoolAllocator<int>(100));
    vec.reserve(100);
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);  // Uses pool allocator
    }
}
```

### Memory Pools

```cpp
class MemoryPool {
    struct Chunk {
        Chunk* next;
    };
    
    Chunk* freeList;
    size_t chunkSize;
    std::vector<void*> pools;
    
public:
    MemoryPool(size_t size, size_t initialSize = 1024) 
        : chunkSize(size) {
        allocatePool(initialSize);
    }
    
    ~MemoryPool() {
        for (auto pool : pools) {
            std::free(pool);
        }
    }
    
    void* allocate() {
        if (!freeList) {
            allocatePool(pools.size() * 2);
        }
        
        void* memory = freeList;
        freeList = freeList->next;
        return memory;
    }
    
    void deallocate(void* ptr) {
        auto chunk = static_cast<Chunk*>(ptr);
        chunk->next = freeList;
        freeList = chunk;
    }
    
private:
    void allocatePool(size_t numChunks) {
        size_t poolSize = chunkSize * numChunks;
        void* pool = std::malloc(poolSize);
        pools.push_back(pool);
        
        // Initialize free list with new chunks
        char* current = static_cast<char*>(pool);
        for (size_t i = 0; i < numChunks; ++i) {
            auto chunk = reinterpret_cast<Chunk*>(current);
            chunk->next = freeList;
            freeList = chunk;
            current += chunkSize;
        }
    }
};
```

### Memory Barriers and Atomics

```cpp
#include <atomic>
#include <thread>

void memoryBarriers() {
    std::atomic<int> data;
    std::atomic<bool> ready;
    
    // Producer
    std::thread producer([&]() {
        data.store(42, std::memory_order_relaxed);
        ready.store(true, std::memory_order_release);  // Release barrier
    });
    
    // Consumer
    std::thread consumer([&]() {
        while (!ready.load(std::memory_order_acquire));  // Acquire barrier
        int value = data.load(std::memory_order_relaxed);
        // Guaranteed to see 42
    });
    
    producer.join();
    consumer.join();
}
```

### Debugging Memory Issues

```cpp
// Memory tracking for debugging
#ifdef _DEBUG
class MemoryTracker {
    struct Allocation {
        void* ptr;
        size_t size;
        const char* file;
        int line;
    };
    
    std::unordered_map<void*, Allocation> allocations;
    std::mutex mutex;
    
public:
    void* allocate(size_t size, const char* file, int line) {
        void* ptr = std::malloc(size);
        std::lock_guard<std::mutex> lock(mutex);
        allocations[ptr] = {ptr, size, file, line};
        return ptr;
    }
    
    void deallocate(void* ptr) {
        std::lock_guard<std::mutex> lock(mutex);
        allocations.erase(ptr);
        std::free(ptr);
    }
    
    void reportLeaks() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!allocations.empty()) {
            std::cerr << "Memory leaks detected:\n";
            for (const auto& [ptr, alloc] : allocations) {
                std::cerr << "  " << alloc.file << ":" << alloc.line 
                          << " - " << alloc.size << " bytes\n";
            }
        }
    }
};

MemoryTracker g_tracker;

void* operator new(size_t size, const char* file, int line) {
    return g_tracker.allocate(size, file, line);
}

void operator delete(void* ptr) {
    g_tracker.deallocate(ptr);
}

#define new new(__FILE__, __LINE__)
#endif
```

---

## Summary

C++ memory management provides powerful control but requires careful attention to:

1. **Stack vs Heap**: Use stack for short-lived, small data; heap for dynamic, persistent data
2. **Pointers**: Understand pointer arithmetic, const correctness, and void pointers
3. **Smart Pointers**: Prefer `unique_ptr` for exclusive ownership, `shared_ptr` for shared ownership, and `weak_ptr` to break cycles
4. **RAII**: Always tie resource management to object lifetime
5. **Best Practices**: Follow the Rule of Three/Five/Zero, use `make_unique`/`make_shared`, avoid raw owning pointers
6. **Performance**: Minimize allocations, use custom allocators when needed
7. **Debugging**: Use tools like Valgrind, AddressSanitizer, and custom trackers

Remember: With great power comes great responsibility. Modern C++ encourages using smart pointers and RAII to make memory management safer and more intuitive.