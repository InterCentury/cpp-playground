# 59 - Returning References in C++

## What is Returning References?
Returning a reference from a function allows the caller to directly access and modify the original variable that the reference refers to. This is useful for operator overloading, accessing class members, and implementing efficient access patterns.

## Basic Syntax

```cpp
return_type& function_name(parameters) {
    // function body
    return variable;  // Must be a variable that exists after function returns
}
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

int globalValue = 100;

int& getGlobal() {
    return globalValue;  // Returns reference to global variable
}

int main() {
    cout << "Before: " << globalValue << endl;
    
    getGlobal() = 200;  // Modify through returned reference
    
    cout << "After: " << globalValue << endl;  // Now 200
    
    return 0;
}
```

## Safe Ways to Return References

### Returning Global Variables
```cpp
#include <iostream>
using namespace std;

int counter = 0;

int& getCounter() {
    return counter;  // Global exists forever
}

int main() {
    getCounter() = 10;
    cout << "Counter: " << counter << endl;
    
    getCounter()++;
    cout << "Counter: " << counter << endl;
    
    return 0;
}
```

### Returning Static Variables
```cpp
#include <iostream>
using namespace std;

int& getStaticCounter() {
    static int count = 0;  // Static variable persists
    return count;
}

int main() {
    getStaticCounter() = 5;
    cout << "Count: " << getStaticCounter() << endl;
    
    getStaticCounter() += 10;
    cout << "Count: " << getStaticCounter() << endl;
    
    return 0;
}
```

### Returning Class Member Variables
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
    
    string& getName() {
        return name;  // Returns reference to member
    }
    
    int& getAge() {
        return age;   // Returns reference to member
    }
    
    void display() const {
        cout << name << ", " << age << endl;
    }
};

int main() {
    Student john("John", 25);
    
    cout << "Original: ";
    john.display();
    
    // Modify through references
    john.getName() = "Jonathan";
    john.getAge() = 30;
    
    cout << "Modified: ";
    john.display();
    
    return 0;
}
```

### Returning Array Elements
```cpp
#include <iostream>
using namespace std;

int numbers[5] = {10, 20, 30, 40, 50};

int& getElement(int index) {
    if (index >= 0 && index < 5) {
        return numbers[index];  // Returns reference to array element
    }
    static int error = -1;
    return error;
}

int main() {
    cout << "Original: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Modify through reference
    getElement(2) = 100;
    getElement(4) = 200;
    
    cout << "Modified: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Array Wrapper Class
```cpp
#include <iostream>
using namespace std;

class IntArray {
private:
    int arr[10];
    
public:
    IntArray() {
        for (int i = 0; i < 10; i++) {
            arr[i] = i * 10;
        }
    }
    
    // Return reference for modification
    int& operator[](int index) {
        if (index >= 0 && index < 10) {
            return arr[index];
        }
        static int dummy = -1;
        return dummy;
    }
    
    // Const version for read-only access
    const int& operator[](int index) const {
        if (index >= 0 && index < 10) {
            return arr[index];
        }
        static int dummy = -1;
        return dummy;
    }
    
    void display() const {
        for (int i = 0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    IntArray arr;
    
    cout << "Original: ";
    arr.display();
    
    // Modify using returned reference
    arr[3] = 999;
    arr[7] = 777;
    
    cout << "Modified: ";
    arr.display();
    
    return 0;
}
```

### Example 2: Matrix Class
```cpp
#include <iostream>
using namespace std;

class Matrix {
private:
    int data[3][3];
    
public:
    Matrix() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                data[i][j] = i * 3 + j + 1;
            }
        }
    }
    
    // Returns reference to element
    int& at(int row, int col) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            return data[row][col];
        }
        static int dummy = -1;
        return dummy;
    }
    
    // Const version for reading
    const int& at(int row, int col) const {
        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            return data[row][col];
        }
        static int dummy = -1;
        return dummy;
    }
    
    void display() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Matrix mat;
    
    cout << "Original matrix:" << endl;
    mat.display();
    
    // Modify using reference
    mat.at(0, 0) = 100;
    mat.at(1, 1) = 200;
    mat.at(2, 2) = 300;
    
    cout << "\nModified matrix:" << endl;
    mat.display();
    
    return 0;
}
```

### Example 3: Linked List Node Access
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
    
    // Returns reference to data of first node
    int& front() {
        if (head) {
            return head->data;
        }
        static int dummy = -1;
        return dummy;
    }
    
    // Returns reference to data at index
    int& at(int index) {
        Node* current = head;
        for (int i = 0; i < index && current; i++) {
            current = current->next;
        }
        if (current) {
            return current->data;
        }
        static int dummy = -1;
        return dummy;
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
    
    cout << "Original list: ";
    list.display();
    
    // Modify through reference
    list.front() = 100;
    list.at(1) = 200;
    
    cout << "Modified list: ";
    list.display();
    
    return 0;
}
```

### Example 4: Buffer Manager
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
    
    // Return reference to character at position
    char& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        static char dummy = '\0';
        return dummy;
    }
    
    // Const version
    const char& operator[](int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        static char dummy = '\0';
        return dummy;
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
    
    // Modify buffer through reference
    buf[0] = 'H';
    buf[1] = 'e';
    buf[2] = 'l';
    buf[3] = 'l';
    buf[4] = 'o';
    
    cout << "Buffer: ";
    buf.display();
    
    // Read using reference
    cout << "First character: " << buf[0] << endl;
    cout << "Third character: " << buf[2] << endl;
    
    return 0;
}
```

### Example 5: Configuration Manager
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
        // Default settings
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
    
    // Const version for reading
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
    
    // Modify through references
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

## Dangerous Returns (What NOT to Do)

### Returning Reference to Local Variable (DANGEROUS!)
```cpp
#include <iostream>
using namespace std;

// DANGEROUS - returns reference to local variable
int& getLocal() {
    int x = 5;
    return x;  // x destroyed after function ends!
}

int main() {
    int& ref = getLocal();  // Undefined behavior!
    cout << ref << endl;     // May crash or print garbage
    return 0;
}
```

### Returning Reference to Temporary (DANGEROUS!)
```cpp
#include <iostream>
#include <string>
using namespace std;

// DANGEROUS - returns reference to temporary
string& getTemp() {
    string s = "Hello";
    return s;  // s destroyed after function ends!
}

int main() {
    string& ref = getTemp();  // Undefined behavior!
    cout << ref << endl;
    return 0;
}
```

### Safe Alternative - Return by Value
```cpp
#include <iostream>
#include <string>
using namespace std;

// Safe - returns by value (copy)
int getValue() {
    int x = 5;
    return x;  // Returns copy, safe
}

string getString() {
    string s = "Hello";
    return s;  // Returns copy, safe
}

int main() {
    int val = getValue();
    string str = getString();
    cout << val << ", " << str << endl;
    return 0;
}
```

## Reference vs Value Return

```cpp
#include <iostream>
using namespace std;

int global = 10;

// Return by value
int getByValue() {
    return global;  // Returns copy
}

// Return by reference
int& getByReference() {
    return global;  // Returns reference
}

int main() {
    int val1 = getByValue();
    int& ref1 = getByReference();
    
    getByValue() = 20;      // ERROR! Can't assign to rvalue
    getByReference() = 30;  // OK - modifies global
    
    cout << "Global: " << global << endl;
    
    return 0;
}
```

## Returning Reference to Array Element

```cpp
#include <iostream>
using namespace std;

int arr[5] = {1, 2, 3, 4, 5};

int& getElement(int index) {
    return arr[index];  // Returns reference to array element
}

int main() {
    cout << "Original array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Modify through references
    getElement(1) = 20;
    getElement(3) = 40;
    
    cout << "Modified array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Returning Reference to Local
```cpp
// WRONG
int& getValue() {
    int x = 5;
    return x;  // x destroyed!
}

// CORRECT
int getValue() {
    int x = 5;
    return x;  // Return by value
}
```

### Mistake 2: Returning Reference to Temporary
```cpp
// WRONG
string& getString() {
    return "Hello";  // Temporary string
}

// CORRECT
string getString() {
    return "Hello";
}
```

### Mistake 3: Forgetting & in Return Type
```cpp
class Array {
    int data[10];
public:
    // WRONG - returns by value, can't modify
    int operator[](int index) {
        return data[index];
    }
    
    // CORRECT - returns reference
    int& operator[](int index) {
        return data[index];
    }
};
```

### Mistake 4: Returning Reference to Null
```cpp
int& getElement(int arr[], int index, int size) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    // WRONG - returning reference to local
    int dummy = -1;
    return dummy;  // dummy destroyed!
}

// CORRECT
int& getElement(int arr[], int index, int size) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    static int dummy = -1;  // Static variable
    return dummy;
}
```

### Mistake 5: Returning Reference to Const
```cpp
class Data {
    int value;
public:
    // Returns non-const reference - allows modification
    int& getValue() {
        return value;
    }
    
    // For const objects - returns const reference
    const int& getValue() const {
        return value;
    }
};
```

## When to Use Returning References

### ✅ Good Uses
```cpp
// Operator overloading (especially [] and =)
int& operator[](int index);

// Access class members
int& getX();

// Chain assignments
Matrix& operator=(const Matrix& other);

// Large objects (avoid copying)
const LargeObject& getData() const;
```

### ❌ Poor Uses
```cpp
// Simple types (int, char) - pass by value is fine
int& getNumber();  // Overkill

// Returning local variables - dangerous
int& getLocal();  // Never do this

// Returning temporary - dangerous
string& getString();  // Never do this
```

## Quick Reference

| Return Type | Syntax | When to Use |
|-------------|--------|-------------|
| Reference | `T& func()` | Modify existing object, avoid copy |
| Const Reference | `const T& func()` | Read-only access, avoid copy |
| Value | `T func()` | Local variables, simple types |
| Pointer | `T* func()` | Nullable returns, arrays |

## Summary

- **Return reference** to allow modification of original variable
- Must ensure variable **outlives** function (global, static, member, parameter)
- **Never return reference** to local variable or temporary
- Useful for **operator overloading** ([], =)
- Provides **direct access** to class members
- More **efficient** than returning by value for large objects
- **Const reference** for read-only access
- Often used with **getters/setters**
- Can be used for **chain assignments**

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

class Data {
private:
    int value;
    string text;
    
public:
    Data(int v, string t) : value(v), text(t) {}
    
    // Return references for modification
    int& getValue() {
        return value;
    }
    
    string& getText() {
        return text;
    }
    
    // Const versions for read-only
    const int& getValue() const {
        return value;
    }
    
    const string& getText() const {
        return text;
    }
    
    void display() const {
        cout << "Value: " << value << ", Text: " << text << endl;
    }
};

int main() {
    Data data(10, "Hello");
    
    cout << "Original: ";
    data.display();
    
    // Modify through references
    data.getValue() = 100;
    data.getText() = "World";
    
    cout << "Modified: ";
    data.display();
    
    // Array element access pattern
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Function returning reference to array element
    auto& getArr = [&arr](int i) -> int& {
        return arr[i];
    };
    
    getArr(2) = 30;
    cout << "\nArray[2] after modification: " << arr[2] << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*