# 71 - References in C++

## What is a Reference?
A reference is an alias (another name) for an existing variable. Once a reference is initialized to a variable, it cannot be changed to refer to another variable. Think of it as a permanent nickname.

## Basic Syntax

```cpp
data_type &reference_name = variable_name;
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

int main() {
    int original = 42;
    int& ref = original;  // ref is a reference to original
    
    cout << "original: " << original << endl;
    cout << "ref: " << ref << endl;
    
    // Modifying through reference changes original
    ref = 100;
    cout << "\nAfter ref = 100:" << endl;
    cout << "original: " << original << endl;
    cout << "ref: " << ref << endl;
    
    return 0;
}
```

## References vs Pointers

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    
    // Reference
    int& ref = value;  // Must be initialized
    // int& ref2;      // Error! Must be initialized
    
    // Pointer
    int* ptr = &value;  // Can be null
    int* ptr2 = nullptr; // OK - can be null
    
    cout << "Reference: " << ref << endl;
    cout << "Pointer: " << *ptr << endl;
    
    // Modifying through reference
    ref = 100;
    cout << "\nAfter ref = 100: value = " << value << endl;
    
    // Modifying through pointer
    *ptr = 200;
    cout << "After *ptr = 200: value = " << value << endl;
    
    // References cannot be reassigned
    int another = 500;
    // ref = another;  // This assigns value, not reassigns reference
    
    // Pointers can be reassigned
    ptr = &another;
    cout << "\nAfter ptr = &another: *ptr = " << *ptr << endl;
    
    return 0;
}
```

## References vs Pointers Comparison Table

| Feature | Reference | Pointer |
|---------|-----------|---------|
| Syntax | `int& ref = var;` | `int* ptr = &var;` |
| Must initialize | Yes | No (can be null) |
| Can be null | No | Yes |
| Can reassign | No | Yes |
| Access value | `ref` (direct) | `*ptr` (dereference) |
| Memory overhead | None (alias) | 4-8 bytes |
| Type safety | Higher | Lower |
| Used in | Pass by reference, operator overloading | Dynamic memory, arrays |

## References as Function Parameters

### Pass by Reference
```cpp
#include <iostream>
using namespace std;

void increment(int& x) {
    x++;  // Modifies original
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int num = 10;
    cout << "Before increment: " << num << endl;
    increment(num);
    cout << "After increment: " << num << endl;
    
    int x = 10, y = 20;
    cout << "\nBefore swap: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    return 0;
}
```

### const Reference (Read-only, Efficient)
```cpp
#include <iostream>
#include <string>
using namespace std;

void printMessage(const string& msg) {
    cout << msg << endl;
    // msg = "New";  // Error! Cannot modify const reference
}

double calculateTotal(const double& price, int quantity) {
    return price * quantity;  // Can read, can't modify
}

int main() {
    string text = "Hello World";
    printMessage(text);  // No copy, efficient
    
    double total = calculateTotal(19.99, 3);
    cout << "Total: $" << total << endl;
    
    return 0;
}
```

## References as Return Values

```cpp
#include <iostream>
using namespace std;

// Safe: returning reference to global/static
int globalVar = 100;

int& getGlobal() {
    return globalVar;  // Safe - global exists
}

int& getStatic() {
    static int value = 50;  // Static - persists
    return value;
}

// DANGEROUS: returning reference to local
int& getLocal() {
    int x = 10;
    return x;  // DANGEROUS! x destroyed after function
}

// Safe: returning reference to array element
int arr[5] = {10, 20, 30, 40, 50};

int& getElement(int index) {
    if (index >= 0 && index < 5) {
        return arr[index];
    }
    static int dummy = -1;
    return dummy;
}

int main() {
    // Safe usage
    getGlobal() = 200;
    cout << "globalVar: " << globalVar << endl;
    
    getStatic() = 75;
    cout << "static value: " << getStatic() << endl;
    
    // Array element
    getElement(2) = 300;
    cout << "arr[2]: " << arr[2] << endl;
    
    // DANGEROUS - don't do this
    // int& bad = getLocal();  // Undefined behavior
    
    return 0;
}
```

## References in Classes

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    
public:
    Student(string n, int a) : name(n), age(a) {}
    
    // Return reference to member (allows modification)
    string& getName() {
        return name;
    }
    
    // Const version for read-only
    const string& getName() const {
        return name;
    }
    
    int& getAge() {
        return age;
    }
    
    void display() const {
        cout << name << ", " << age << endl;
    }
};

int main() {
    Student john("John", 25);
    
    cout << "Original: ";
    john.display();
    
    // Modify through reference
    john.getName() = "Jonathan";
    john.getAge() = 30;
    
    cout << "Modified: ";
    john.display();
    
    return 0;
}
```

## References to References (Not Allowed)

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 10;
    int& ref = value;
    
    // int&& ref2 = ref;  // Error! Cannot have reference to reference
    // In C++, references are not objects, so no reference to reference
    
    // But you can have pointer to reference? No.
    // int&* ptr = &ref;  // Error! Cannot have pointer to reference
    
    // However, you can have reference to pointer
    int* ptr = &value;
    int*& refToPtr = ptr;  // Reference to pointer
    *refToPtr = 20;
    cout << "value: " << value << endl;
    
    return 0;
}
```

## Reference to Pointer

```cpp
#include <iostream>
using namespace std;

void modifyPointer(int*& ptr) {
    // Can modify the pointer itself
    int* newPtr = new int(100);
    delete ptr;
    ptr = newPtr;
}

int main() {
    int* ptr = new int(50);
    cout << "Before: *ptr = " << *ptr << endl;
    
    modifyPointer(ptr);
    cout << "After: *ptr = " << *ptr << endl;
    
    delete ptr;
    
    return 0;
}
```

## Practical Examples

### Example 1: Returning Multiple Values
```cpp
#include <iostream>
#include <cmath>
using namespace std;

void getMinMax(int arr[], int size, int& min, int& max) {
    min = arr[0];
    max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
}

void getStats(const vector<double>& data, double& sum, double& avg, double& max) {
    sum = 0;
    max = data[0];
    for (double val : data) {
        sum += val;
        if (val > max) max = val;
    }
    avg = sum / data.size();
}

int main() {
    int numbers[] = {45, 23, 78, 12, 89, 34};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int min, max;
    
    getMinMax(numbers, size, min, max);
    cout << "Min: " << min << ", Max: " << max << endl;
    
    vector<double> data = {10.5, 20.3, 15.7, 25.1, 18.9};
    double sum, avg, maxVal;
    
    getStats(data, sum, avg, maxVal);
    cout << "Sum: " << sum << ", Avg: " << avg << ", Max: " << maxVal << endl;
    
    return 0;
}
```

### Example 2: Matrix Class with Reference Access
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int rows, cols;
    
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(rows, vector<int>(cols, 0));
    }
    
    // Return reference to element (allows modification)
    int& at(int row, int col) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        }
        static int dummy = -1;
        return dummy;
    }
    
    // Const version for reading
    const int& at(int row, int col) const {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        }
        static int dummy = -1;
        return dummy;
    }
    
    // Return reference to row
    vector<int>& operator[](int row) {
        return data[row];
    }
    
    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    Matrix mat(3, 4);
    
    // Fill using reference
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            mat.at(i, j) = i * 4 + j + 1;
        }
    }
    
    cout << "Matrix:" << endl;
    mat.display();
    
    // Modify through reference
    mat.at(1, 2) = 100;
    mat[2][3] = 200;  // Using operator[]
    
    cout << "\nAfter modification:" << endl;
    mat.display();
    
    return 0;
}
```

### Example 3: Buffer Manager with Reference
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Buffer {
private:
    char* data;
    int size;
    
public:
    Buffer(int s) : size(s) {
        data = new char[size];
        memset(data, 0, size);
    }
    
    // Return reference to character
    char& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        static char dummy = '\0';
        return dummy;
    }
    
    const char& operator[](int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        static char dummy = '\0';
        return dummy;
    }
    
    // Return reference to entire buffer (dangerous but possible)
    char*& getData() {
        return data;
    }
    
    void display() const {
        for (int i = 0; i < size; i++) {
            cout << data[i];
        }
        cout << endl;
    }
    
    ~Buffer() {
        delete[] data;
    }
};

int main() {
    Buffer buf(10);
    
    // Write using reference
    buf[0] = 'H';
    buf[1] = 'e';
    buf[2] = 'l';
    buf[3] = 'l';
    buf[4] = 'o';
    
    cout << "Buffer: ";
    buf.display();
    
    // Read using reference
    cout << "First char: " << buf[0] << endl;
    
    return 0;
}
```

### Example 4: Reference to Array
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    
    // Reference to array
    int (&refArr)[5] = arr;  // Must specify size
    
    cout << "Original array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Modify through reference
    for (int i = 0; i < 5; i++) {
        refArr[i] *= 2;
    }
    
    cout << "After reference modification: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 5: Configuration Manager with References
```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;

class Config {
private:
    map<string, string> settings;
    
public:
    Config() {
        settings["username"] = "guest";
        settings["theme"] = "light";
        settings["language"] = "en";
    }
    
    // Return reference to setting value
    string& get(string key) {
        if (settings.find(key) != settings.end()) {
            return settings[key];
        }
        static string dummy;
        return dummy;
    }
    
    const string& get(string key) const {
        auto it = settings.find(key);
        if (it != settings.end()) {
            return it->second;
        }
        static string dummy;
        return dummy;
    }
    
    void display() const {
        for (const auto& pair : settings) {
            cout << pair.first << " = " << pair.second << endl;
        }
    }
};

int main() {
    Config config;
    
    cout << "Original settings:" << endl;
    config.display();
    
    // Modify through reference
    config.get("username") = "john_doe";
    config.get("theme") = "dark";
    config.get("language") = "fr";
    
    cout << "\nModified settings:" << endl;
    config.display();
    
    // Add new setting
    config.get("font_size") = "14";
    
    cout << "\nAfter adding setting:" << endl;
    config.display();
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Uninitialized Reference
```cpp
int& ref;  // Error! Must be initialized

// Correct
int x = 10;
int& ref = x;
```

### Mistake 2: Trying to Reassign Reference
```cpp
int a = 10, b = 20;
int& ref = a;
ref = b;  // This assigns value, doesn't make ref refer to b
cout << a;  // 20 - a changed, ref still refers to a
```

### Mistake 3: Returning Reference to Local
```cpp
int& badFunction() {
    int x = 10;
    return x;  // DANGEROUS! x destroyed after function
}
```

### Mistake 4: Reference to Temporary
```cpp
int& ref = 5;  // Error! Cannot bind reference to temporary

// Correct - const reference can bind to temporary
const int& ref = 5;  // OK
```

### Mistake 5: Forgetting const for Large Objects
```cpp
// Inefficient - copies large object
void process(string s) { }

// Better - const reference (no copy, read-only)
void process(const string& s) { }
```

## Quick Reference Table

| Operation | Syntax | Notes |
|-----------|--------|-------|
| Declare reference | `int& ref = var;` | Must initialize |
| Use reference | `ref = 10;` | Affects original |
| Const reference | `const int& ref = var;` | Read-only |
| Reference parameter | `void f(int& x)` | Modifies original |
| Const reference param | `void f(const int& x)` | Efficient, read-only |
| Return reference | `int& f()` | Must point to valid object |
| Reference to pointer | `int*& ptr` | Modify pointer itself |

## When to Use References

### ✅ Good Uses
```cpp
// Function parameters (modify original)
void increment(int& x);

// Function parameters (efficient for large objects)
void print(const string& s);

// Operator overloading
Matrix& operator=(const Matrix& other);

// Returning class members for modification
int& getValue();

// Aliases for long names
auto& vec = myObject.getVector();
```

### ❌ Avoid
```cpp
// Returning reference to local
int& bad();

// Uninitialized references
int& ref;  // Not allowed

// References to references
int&& ref2;  // Not directly
```

## Summary

- **Reference** is an alias for existing variable
- Must be **initialized** when declared
- Cannot be **reassigned** to refer to different variable
- No **null references** (always refer to valid object)
- Used for **pass by reference** (modify original)
- **const reference** for efficient read-only access
- Can return **reference to class members**
- Cannot return **reference to local variable**
- **Less error-prone** than pointers
- **Operator overloading** often returns references

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Reference parameters
void increment(int& x) {
    x++;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Const reference parameter
void printMessage(const string& msg) {
    cout << msg << endl;
}

// Return reference
int& getElement(int arr[], int index) {
    static int dummy = -1;
    if (index >= 0 && index < 5) {
        return arr[index];
    }
    return dummy;
}

int main() {
    // Basic reference
    int value = 42;
    int& ref = value;
    
    cout << "Original: " << value << endl;
    ref = 100;
    cout << "After ref = 100: " << value << endl;
    
    // Reference parameters
    int num = 5;
    increment(num);
    cout << "\nAfter increment: " << num << endl;
    
    int x = 10, y = 20;
    swap(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    // Const reference
    string text = "Hello";
    printMessage(text);
    
    // Return reference
    int arr[5] = {1, 2, 3, 4, 5};
    getElement(arr, 2) = 30;
    cout << "\narr[2] after modification: " << arr[2] << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*