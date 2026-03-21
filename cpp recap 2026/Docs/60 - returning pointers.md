# 60 - Returning Pointers in C++

## What is Returning Pointers?
Returning a pointer from a function allows the caller to receive a memory address, enabling direct access and manipulation of data. This is useful for returning dynamically allocated memory, array elements, or indicating special conditions.

## Basic Syntax

```cpp
return_type* function_name(parameters) {
    // function body
    return pointer;  // Returns address
}
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

int* getInteger() {
    int* ptr = new int(42);  // Dynamically allocate
    return ptr;  // Return pointer
}

int main() {
    int* num = getInteger();
    cout << "Value: " << *num << endl;
    delete num;  // Must free memory
    
    return 0;
}
```

## Returning Pointers to Different Types

### Returning int Pointer
```cpp
#include <iostream>
using namespace std;

int* createArray(int size, int value) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
    return arr;
}

int main() {
    int* numbers = createArray(5, 10);
    
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    delete[] numbers;  // Free memory
    
    return 0;
}
```

### Returning double Pointer
```cpp
#include <iostream>
using namespace std;

double* getDoubles(int size) {
    double* arr = new double[size];
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 1.5;
    }
    return arr;
}

int main() {
    double* values = getDoubles(5);
    
    for (int i = 0; i < 5; i++) {
        cout << values[i] << " ";
    }
    cout << endl;
    
    delete[] values;
    
    return 0;
}
```

### Returning char Pointer (C-string)
```cpp
#include <iostream>
#include <cstring>
using namespace std;

char* duplicateString(const char* source) {
    int len = strlen(source);
    char* dest = new char[len + 1];
    strcpy(dest, source);
    return dest;
}

int main() {
    char* text = duplicateString("Hello World");
    cout << "Duplicated: " << text << endl;
    delete[] text;
    
    return 0;
}
```

## Safe Ways to Return Pointers

### Returning Dynamically Allocated Memory
```cpp
#include <iostream>
using namespace std;

int* createInt(int value) {
    int* ptr = new int(value);
    return ptr;  // Safe - memory persists
}

int main() {
    int* num = createInt(42);
    cout << "Value: " << *num << endl;
    delete num;  // Must delete
    
    return 0;
}
```

### Returning Static Variables
```cpp
#include <iostream>
using namespace std;

int* getCounter() {
    static int counter = 0;  // Static - persists
    counter++;
    return &counter;
}

int main() {
    cout << *getCounter() << endl;  // 1
    cout << *getCounter() << endl;  // 2
    cout << *getCounter() << endl;  // 3
    
    return 0;
}
```

### Returning Global Variables
```cpp
#include <iostream>
using namespace std;

int globalValue = 100;

int* getGlobal() {
    return &globalValue;  // Returns address of global
}

int main() {
    int* ptr = getGlobal();
    cout << "Value: " << *ptr << endl;
    
    *ptr = 200;  // Modify through pointer
    cout << "Modified: " << globalValue << endl;
    
    return 0;
}
```

### Returning Array Elements
```cpp
#include <iostream>
using namespace std;

int arr[5] = {10, 20, 30, 40, 50};

int* getElement(int index) {
    if (index >= 0 && index < 5) {
        return &arr[index];  // Returns address of element
    }
    return nullptr;  // Indicate error
}

int main() {
    int* ptr = getElement(2);
    if (ptr) {
        cout << "Element: " << *ptr << endl;
        *ptr = 100;  // Modify through pointer
        cout << "Modified element: " << arr[2] << endl;
    }
    
    return 0;
}
```

## Practical Examples

### Example 1: Dynamic Array Creation
```cpp
#include <iostream>
using namespace std;

int* createIntArray(int size) {
    if (size <= 0) return nullptr;
    
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
    return arr;
}

int* createFibonacciArray(int size) {
    if (size <= 0) return nullptr;
    
    int* arr = new int[size];
    arr[0] = 0;
    if (size > 1) arr[1] = 1;
    
    for (int i = 2; i < size; i++) {
        arr[i] = arr[i-1] + arr[i-2];
    }
    return arr;
}

int* createSquaresArray(int size) {
    if (size <= 0) return nullptr;
    
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * (i + 1);
    }
    return arr;
}

int main() {
    int* squares = createSquaresArray(10);
    if (squares) {
        cout << "Squares: ";
        for (int i = 0; i < 10; i++) {
            cout << squares[i] << " ";
        }
        cout << endl;
        delete[] squares;
    }
    
    int* fib = createFibonacciArray(15);
    if (fib) {
        cout << "Fibonacci: ";
        for (int i = 0; i < 15; i++) {
            cout << fib[i] << " ";
        }
        cout << endl;
        delete[] fib;
    }
    
    return 0;
}
```

### Example 2: String Processing Functions
```cpp
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

char* toUpperCase(const char* str) {
    int len = strlen(str);
    char* result = new char[len + 1];
    
    for (int i = 0; i < len; i++) {
        result[i] = toupper(str[i]);
    }
    result[len] = '\0';
    return result;
}

char* toLowerCase(const char* str) {
    int len = strlen(str);
    char* result = new char[len + 1];
    
    for (int i = 0; i < len; i++) {
        result[i] = tolower(str[i]);
    }
    result[len] = '\0';
    return result;
}

char* reverse(const char* str) {
    int len = strlen(str);
    char* result = new char[len + 1];
    
    for (int i = 0; i < len; i++) {
        result[i] = str[len - 1 - i];
    }
    result[len] = '\0';
    return result;
}

char* concatenate(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char* result = new char[len1 + len2 + 1];
    
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

int main() {
    const char* text = "Hello World";
    
    char* upper = toUpperCase(text);
    char* lower = toLowerCase(text);
    char* rev = reverse(text);
    char* concat = concatenate(text, "!!!");
    
    cout << "Original: " << text << endl;
    cout << "Uppercase: " << upper << endl;
    cout << "Lowercase: " << lower << endl;
    cout << "Reversed: " << rev << endl;
    cout << "Concatenated: " << concat << endl;
    
    delete[] upper;
    delete[] lower;
    delete[] rev;
    delete[] concat;
    
    return 0;
}
```

### Example 3: Linked List Implementation
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
    
    // Return pointer to node with value
    Node* find(int val) {
        Node* current = head;
        while (current) {
            if (current->data == val) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    // Return pointer to node at position
    Node* at(int index) {
        Node* current = head;
        for (int i = 0; i < index && current; i++) {
            current = current->next;
        }
        return current;
    }
    
    // Return pointer to head
    Node* getHead() {
        return head;
    }
    
    void display() const {
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
    
    ~LinkedList() {
        while (head) {
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
    list.push(40);
    
    cout << "List: ";
    list.display();
    
    Node* found = list.find(30);
    if (found) {
        cout << "Found node with value: " << found->data << endl;
        found->data = 300;  // Modify through pointer
        cout << "After modification: ";
        list.display();
    }
    
    Node* pos = list.at(2);
    if (pos) {
        cout << "Node at index 2: " << pos->data << endl;
    }
    
    return 0;
}
```

### Example 4: Matrix Operations
```cpp
#include <iostream>
using namespace std;

// Create 2D array dynamically
int** createMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

// Fill matrix with sequential values
void fillMatrix(int** matrix, int rows, int cols) {
    int counter = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = counter++;
        }
    }
}

// Get row pointer
int* getRow(int** matrix, int row) {
    return matrix[row];
}

// Get element pointer
int* getElement(int** matrix, int row, int col) {
    return &matrix[row][col];
}

void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    int rows = 3, cols = 4;
    int** mat = createMatrix(rows, cols);
    fillMatrix(mat, rows, cols);
    
    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
    
    // Modify through row pointer
    int* row2 = getRow(mat, 1);
    row2[0] = 100;
    row2[2] = 200;
    
    // Modify through element pointer
    int* elem = getElement(mat, 2, 3);
    *elem = 999;
    
    cout << "\nAfter modification:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
    
    deleteMatrix(mat, rows);
    
    return 0;
}
```

### Example 5: Searching and Filtering
```cpp
#include <iostream>
using namespace std;

int* findFirst(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return &arr[i];  // Return pointer to found element
        }
    }
    return nullptr;
}

int* findAll(int arr[], int size, int target, int& resultSize) {
    // First count occurrences
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) count++;
    }
    
    if (count == 0) {
        resultSize = 0;
        return nullptr;
    }
    
    // Allocate array of pointers
    int** temp = new int*[count];
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            temp[index++] = &arr[i];
        }
    }
    
    // Convert to 1D array of ints (dereferenced)
    int* result = new int[count];
    for (int i = 0; i < count; i++) {
        result[i] = *temp[i];
    }
    
    delete[] temp;
    resultSize = count;
    return result;
}

int* filterEven(int arr[], int size, int& newSize) {
    // Count even numbers
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) count++;
    }
    
    if (count == 0) {
        newSize = 0;
        return nullptr;
    }
    
    int* result = new int[count];
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            result[index++] = arr[i];
        }
    }
    
    newSize = count;
    return result;
}

int main() {
    int numbers[] = {10, 23, 45, 10, 67, 10, 89, 34};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Array: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Find first occurrence
    int* found = findFirst(numbers, size, 10);
    if (found) {
        cout << "Found 10 at address: " << found << " (value: " << *found << ")" << endl;
        *found = 100;  // Modify through pointer
        cout << "After modification: ";
        for (int n : numbers) cout << n << " ";
        cout << endl;
    }
    
    // Find all occurrences
    int count;
    int* allFound = findAll(numbers, size, 100, count);
    if (allFound) {
        cout << "Found " << count << " occurrences of 100" << endl;
        delete[] allFound;
    }
    
    // Filter even numbers
    int evenCount;
    int* evens = filterEven(numbers, size, evenCount);
    if (evens) {
        cout << "Even numbers: ";
        for (int i = 0; i < evenCount; i++) {
            cout << evens[i] << " ";
        }
        cout << endl;
        delete[] evens;
    }
    
    return 0;
}
```

## Dangerous Returns (What NOT to Do)

### Returning Pointer to Local Variable (DANGEROUS!)
```cpp
#include <iostream>
using namespace std;

// DANGEROUS - returns pointer to local variable
int* getLocal() {
    int x = 5;
    return &x;  // x destroyed after function ends!
}

int main() {
    int* ptr = getLocal();  // Undefined behavior!
    cout << *ptr << endl;    // May crash or print garbage
    return 0;
}
```

### Returning Pointer to Temporary (DANGEROUS!)
```cpp
#include <iostream>
#include <string>
using namespace std;

// DANGEROUS - returns pointer to temporary
const char* getTemp() {
    string s = "Hello";
    return s.c_str();  // s destroyed after function!
}

int main() {
    const char* str = getTemp();  // Undefined behavior!
    cout << str << endl;
    return 0;
}
```

### Returning Pointer to Deleted Memory (DANGEROUS!)
```cpp
int* getMemory() {
    int* ptr = new int(5);
    delete ptr;  // Deleted memory
    return ptr;  // Returns dangling pointer!
}
```

## Null Pointer Returns

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
    int numbers[] = {1, 2, 3, 4, 5};
    
    int* ptr = findValue(numbers, 5, 10);
    
    if (ptr) {
        cout << "Found: " << *ptr << endl;
    } else {
        cout << "Not found" << endl;
    }
    
    // Always check for null before dereferencing!
    if (ptr) {
        *ptr = 100;
    }
    
    return 0;
}
```

## Pointer vs Reference Return

| Aspect | Return Pointer | Return Reference |
|--------|----------------|------------------|
| Nullability | Can return nullptr | Cannot be null |
| Syntax | `T* func()` | `T& func()` |
| Call | `ptr = func();` | `ref = func();` |
| Null check | `if (ptr)` | Not needed |
| Reassign | Can point elsewhere | Cannot rebind |
| C-style | Common | Not in C |
| C++ style | Sometimes | Often preferred |

## Common Mistakes

### Mistake 1: Returning Local Address
```cpp
// WRONG
int* getValue() {
    int x = 5;
    return &x;  // x destroyed!
}

// CORRECT
int getValue() {
    int x = 5;
    return x;  // Return by value
}
```

### Mistake 2: Forgetting to Check Null
```cpp
int* find(int arr[], int size, int target) {
    // ... returns nullptr if not found
}

int main() {
    int* ptr = find(numbers, 10, 99);
    // WRONG - no null check
    *ptr = 100;  // May crash!
}
```

### Mistake 3: Memory Leak
```cpp
int* createArray(int size) {
    return new int[size];
}

int main() {
    int* arr = createArray(10);
    // Use array...
    // WRONG - forgot to delete!
    // delete[] arr;  // Missing!
}
```

### Mistake 4: Double Delete
```cpp
int* ptr = new int(5);
delete ptr;
delete ptr;  // WRONG - double delete!
```

### Mistake 5: Returning Pointer to Static Local (Actually OK)
```cpp
// This is actually OK for static
int* getStatic() {
    static int x = 5;  // Static persists
    return &x;  // Safe!
}
```

## Quick Reference

| Return Type | Syntax | When to Use |
|-------------|--------|-------------|
| Pointer to new | `T* func()` | Dynamic allocation |
| Pointer to static | `T* func()` | Singleton/global access |
| Pointer to member | `T* func()` | Class member access |
| Pointer to array | `T* func()` | Array creation |
| Null pointer | `return nullptr` | Indicate error/not found |

## Summary

- **Return pointer** to provide address of data
- Must ensure data **outlives** function (new, static, global, member)
- **Always check for nullptr** before dereferencing
- **Must delete** dynamically allocated memory
- Useful for **dynamic allocation**, **arrays**, **optional returns**
- **Returning local address** is dangerous (undefined behavior)
- **Returning static** or **global** is safe
- **nullptr** indicates error or not found
- C-style alternative to **returning references**

## Basic Template
```cpp
#include <iostream>
using namespace std;

// Safe pointer returns
int* createInt(int value) {
    int* ptr = new int(value);
    return ptr;
}

int* getStaticInt() {
    static int value = 42;
    return &value;
}

int* findElement(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return &arr[i];
        }
    }
    return nullptr;
}

int main() {
    // Dynamic allocation
    int* num = createInt(100);
    cout << "Dynamic: " << *num << endl;
    delete num;
    
    // Static variable
    int* stat = getStaticInt();
    cout << "Static: " << *stat << endl;
    
    // Array search
    int numbers[] = {10, 20, 30, 40, 50};
    int* found = findElement(numbers, 5, 30);
    
    if (found) {
        cout << "Found: " << *found << endl;
        *found = 300;  // Modify through pointer
        cout << "Modified array[2]: " << numbers[2] << endl;
    }
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*