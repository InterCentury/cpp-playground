# 115 - Overloading Subscript Operator [] in C++

## What is Subscript Operator Overloading?
The subscript operator `[]` is used to access elements in array-like containers. Overloading it allows user-defined types to support intuitive index-based access, similar to built-in arrays.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

class IntArray {
private:
    int* data;
    int size;
    
public:
    IntArray(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    
    ~IntArray() {
        delete[] data;
    }
    
    // Non-const version - allows modification
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    // Const version - read-only access
    const int& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    int getSize() const { return size; }
};

int main() {
    IntArray arr(5);
    
    // Writing using subscript operator
    for (int i = 0; i < arr.getSize(); i++) {
        arr[i] = i * 10;
    }
    
    // Reading using subscript operator
    cout << "Array elements: ";
    for (int i = 0; i < arr.getSize(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Const access
    const IntArray& constRef = arr;
    cout << "First element via const ref: " << constRef[0] << endl;
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### intarray.h
```cpp
#ifndef INTARRAY_H
#define INTARRAY_H

#include <iostream>
using namespace std;

class IntArray {
private:
    int* data;
    int size;
    
public:
    IntArray(int s);
    ~IntArray();
    
    int& operator[](int index);
    const int& operator[](int index) const;
    int getSize() const;
};

#endif
```

### intarray.cpp
```cpp
#include "intarray.h"
#include <stdexcept>
using namespace std;

IntArray::IntArray(int s) : size(s) {
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = 0;
}

IntArray::~IntArray() {
    delete[] data;
}

int& IntArray::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}

const int& IntArray::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}

int IntArray::getSize() const { return size; }
```

### main.cpp
```cpp
#include <iostream>
#include "intarray.h"
using namespace std;

int main() {
    IntArray arr(5);
    for (int i = 0; i < 5; i++) arr[i] = i * 10;
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
```

## Key Principles of Subscript Operator

### 1. Must Return Reference for Modifiable Access
```cpp
// Correct - returns reference
int& operator[](int index) { return data[index]; }

// Wrong - returns by value (can't modify)
int operator[](int index) { return data[index]; }
```

### 2. Provide Const and Non-Const Versions
```cpp
// For modification
int& operator[](int index);

// For reading from const objects
const int& operator[](int index) const;
```

### 3. Always Check Bounds
```cpp
int& operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}
```

## Practical Examples

### Example 1: Matrix Class with Row/Column Access

#### Type 1: Single File
```cpp
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    vector<vector<int>> data;
    
public:
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {}
    
    // Return row as vector (allows [row][col] access)
    vector<int>& operator[](int row) {
        if (row < 0 || row >= rows) {
            throw out_of_range("Row index out of bounds");
        }
        return data[row];
    }
    
    const vector<int>& operator[](int row) const {
        if (row < 0 || row >= rows) {
            throw out_of_range("Row index out of bounds");
        }
        return data[row];
    }
    
    // Alternative: single subscript with two indices
    int& at(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Index out of bounds");
        }
        return data[row][col];
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
    
    // Using [row][col] syntax
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] = i * 4 + j + 1;
        }
    }
    
    cout << "Matrix:" << endl;
    mat.display();
    
    // Modify element
    mat[1][2] = 100;
    cout << "\nAfter modification:" << endl;
    mat.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**matrix.h**
```cpp
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    vector<vector<int>> data;
    
public:
    Matrix(int r, int c);
    
    vector<int>& operator[](int row);
    const vector<int>& operator[](int row) const;
    int& at(int row, int col);
    void display() const;
};

#endif
```

**matrix.cpp**
```cpp
#include "matrix.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {}

vector<int>& Matrix::operator[](int row) {
    if (row < 0 || row >= rows) {
        throw out_of_range("Row index out of bounds");
    }
    return data[row];
}

const vector<int>& Matrix::operator[](int row) const {
    if (row < 0 || row >= rows) {
        throw out_of_range("Row index out of bounds");
    }
    return data[row];
}

int& Matrix::at(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw out_of_range("Index out of bounds");
    }
    return data[row][col];
}

void Matrix::display() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
}
```

**main.cpp**
```cpp
#include <iostream>
#include "matrix.h"
using namespace std;

int main() {
    Matrix mat(3, 4);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] = i * 4 + j + 1;
        }
    }
    
    mat.display();
    
    return 0;
}
```

### Example 2: String Class with Character Access

#### Type 1: Single File
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private:
    char* data;
    int length;
    
public:
    MyString(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
    
    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }
    
    ~MyString() {
        delete[] data;
    }
    
    // Non-const subscript - allows modification
    char& operator[](int index) {
        if (index < 0 || index >= length) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    // Const subscript - read-only
    const char& operator[](int index) const {
        if (index < 0 || index >= length) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    int getLength() const { return length; }
    
    friend ostream& operator<<(ostream& os, const MyString& s) {
        os << s.data;
        return os;
    }
};

int main() {
    MyString s1("Hello");
    MyString s2("World");
    
    cout << "s1 = " << s1 << endl;
    cout << "s1[0] = " << s1[0] << endl;
    cout << "s1[4] = " << s1[4] << endl;
    
    // Modify character
    s1[0] = 'J';
    cout << "After s1[0] = 'J': " << s1 << endl;
    
    // Const access
    const MyString& ref = s2;
    cout << "const ref[0] = " << ref[0] << endl;
    // ref[0] = 'X';  // Error! Cannot modify const object
    
    return 0;
}
```

#### Type 2: Multiple Files

**mystring.h**
```cpp
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using namespace std;

class MyString {
private:
    char* data;
    int length;
    
public:
    MyString(const char* str = "");
    MyString(const MyString& other);
    ~MyString();
    
    char& operator[](int index);
    const char& operator[](int index) const;
    int getLength() const;
    
    friend ostream& operator<<(ostream& os, const MyString& s);
};

#endif
```

**mystring.cpp**
```cpp
#include "mystring.h"
#include <cstring>
#include <stdexcept>
#include <iostream>
using namespace std;

MyString::MyString(const char* str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
}

MyString::MyString(const MyString& other) {
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
}

MyString::~MyString() {
    delete[] data;
}

char& MyString::operator[](int index) {
    if (index < 0 || index >= length) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}

const char& MyString::operator[](int index) const {
    if (index < 0 || index >= length) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}

int MyString::getLength() const { return length; }

ostream& operator<<(ostream& os, const MyString& s) {
    os << s.data;
    return os;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "mystring.h"
using namespace std;

int main() {
    MyString s("Hello");
    s[0] = 'J';
    cout << s << endl;
    return 0;
}
```

### Example 3: Sparse Vector Class

#### Type 1: Single File
```cpp
#include <iostream>
#include <map>
#include <stdexcept>
using namespace std;

class SparseVector {
private:
    map<int, double> elements;
    int size;
    
public:
    SparseVector(int s) : size(s) {}
    
    // Subscript operator for sparse vector
    double& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return elements[index];  // Creates entry if not exists
    }
    
    const double& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        static double zero = 0;
        auto it = elements.find(index);
        if (it != elements.end()) {
            return it->second;
        }
        return zero;
    }
    
    int getSize() const { return size; }
    
    void display() const {
        for (int i = 0; i < size; i++) {
            cout << (*this)[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    SparseVector v(10);
    
    // Set only a few elements
    v[2] = 3.14;
    v[5] = 2.71;
    v[8] = 1.41;
    
    cout << "Sparse vector: ";
    v.display();
    
    cout << "v[2] = " << v[2] << endl;
    cout << "v[3] = " << v[3] << " (default zero)" << endl;
    
    // Modify existing element
    v[5] = 9.99;
    cout << "After modification, v[5] = " << v[5] << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**sparsevector.h**
```cpp
#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

#include <iostream>
#include <map>
using namespace std;

class SparseVector {
private:
    map<int, double> elements;
    int size;
    
public:
    SparseVector(int s);
    
    double& operator[](int index);
    const double& operator[](int index) const;
    int getSize() const;
    void display() const;
};

#endif
```

**sparsevector.cpp**
```cpp
#include "sparsevector.h"
#include <stdexcept>
#include <iostream>
using namespace std;

SparseVector::SparseVector(int s) : size(s) {}

double& SparseVector::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return elements[index];
}

const double& SparseVector::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    static double zero = 0;
    auto it = elements.find(index);
    if (it != elements.end()) {
        return it->second;
    }
    return zero;
}

int SparseVector::getSize() const { return size; }

void SparseVector::display() const {
    for (int i = 0; i < size; i++) {
        cout << (*this)[i] << " ";
    }
    cout << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "sparsevector.h"
using namespace std;

int main() {
    SparseVector v(10);
    v[2] = 3.14;
    v[5] = 2.71;
    v.display();
    return 0;
}
```

### Example 4: Safe Array with Range Checking

#### Type 1: Single File
```cpp
#include <iostream>
#include <stdexcept>
#include <initializer_list>
using namespace std;

template<typename T>
class SafeArray {
private:
    T* data;
    int size;
    
public:
    SafeArray(int s) : size(s) {
        data = new T[size];
        for (int i = 0; i < size; i++) data[i] = T();
    }
    
    SafeArray(initializer_list<T> list) : size(list.size()) {
        data = new T[size];
        int i = 0;
        for (const T& val : list) {
            data[i++] = val;
        }
    }
    
    ~SafeArray() {
        delete[] data;
    }
    
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index " + to_string(index) + 
                               " out of range [0, " + to_string(size - 1) + "]");
        }
        return data[index];
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index " + to_string(index) + 
                               " out of range [0, " + to_string(size - 1) + "]");
        }
        return data[index];
    }
    
    int getSize() const { return size; }
    
    void display() const {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]";
    }
};

int main() {
    SafeArray<int> arr1(5);
    SafeArray<int> arr2 = {10, 20, 30, 40, 50};
    
    // Initialize
    for (int i = 0; i < arr1.getSize(); i++) {
        arr1[i] = i * 10;
    }
    
    cout << "arr1: "; arr1.display(); cout << endl;
    cout << "arr2: "; arr2.display(); cout << endl;
    
    // Modify
    arr1[2] = 99;
    cout << "After modification: "; arr1.display(); cout << endl;
    
    // Test bounds checking
    try {
        cout << arr1[10] << endl;
    } catch (const out_of_range& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**safearray.h**
```cpp
#ifndef SAFEARRAY_H
#define SAFEARRAY_H

#include <iostream>
#include <initializer_list>
using namespace std;

template<typename T>
class SafeArray {
private:
    T* data;
    int size;
    
public:
    SafeArray(int s);
    SafeArray(initializer_list<T> list);
    ~SafeArray();
    
    T& operator[](int index);
    const T& operator[](int index) const;
    int getSize() const;
    void display() const;
};

#endif
```

**safearray.cpp**
```cpp
#include "safearray.h"
#include <stdexcept>
#include <iostream>
using namespace std;

template<typename T>
SafeArray<T>::SafeArray(int s) : size(s) {
    data = new T[size];
    for (int i = 0; i < size; i++) data[i] = T();
}

template<typename T>
SafeArray<T>::SafeArray(initializer_list<T> list) : size(list.size()) {
    data = new T[size];
    int i = 0;
    for (const T& val : list) {
        data[i++] = val;
    }
}

template<typename T>
SafeArray<T>::~SafeArray() {
    delete[] data;
}

template<typename T>
T& SafeArray<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}

template<typename T>
const T& SafeArray<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}

template<typename T>
int SafeArray<T>::getSize() const { return size; }

template<typename T>
void SafeArray<T>::display() const {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]";
}

// Explicit instantiation
template class SafeArray<int>;
template class SafeArray<double>;
```

**main.cpp**
```cpp
#include <iostream>
#include "safearray.h"
using namespace std;

int main() {
    SafeArray<int> arr(5);
    for (int i = 0; i < 5; i++) arr[i] = i * 10;
    arr.display();
    cout << endl;
    return 0;
}
```

### Example 5: Dictionary/Map Class with String Keys

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Dictionary {
private:
    struct Entry {
        string key;
        string value;
        Entry(string k, string v) : key(k), value(v) {}
    };
    
    vector<Entry> entries;
    
    int findIndex(const string& key) const {
        for (size_t i = 0; i < entries.size(); i++) {
            if (entries[i].key == key) return i;
        }
        return -1;
    }
    
public:
    // Subscript operator for dictionary access
    string& operator[](const string& key) {
        int index = findIndex(key);
        if (index == -1) {
            entries.push_back(Entry(key, ""));
            return entries.back().value;
        }
        return entries[index].value;
    }
    
    const string& operator[](const string& key) const {
        int index = findIndex(key);
        if (index == -1) {
            static string empty = "";
            return empty;
        }
        return entries[index].value;
    }
    
    void display() const {
        for (const auto& entry : entries) {
            cout << entry.key << " = " << entry.value << endl;
        }
    }
};

int main() {
    Dictionary dict;
    
    // Adding entries using subscript
    dict["name"] = "John Doe";
    dict["age"] = "25";
    dict["city"] = "New York";
    
    // Accessing entries
    cout << "name = " << dict["name"] << endl;
    cout << "age = " << dict["age"] << endl;
    cout << "city = " << dict["city"] << endl;
    
    // Modifying existing entry
    dict["age"] = "26";
    cout << "\nAfter modification:" << endl;
    cout << "age = " << dict["age"] << endl;
    
    // Display all entries
    cout << "\nAll entries:" << endl;
    dict.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**dictionary.h**
```cpp
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Dictionary {
private:
    struct Entry {
        string key;
        string value;
        Entry(string k, string v);
    };
    
    vector<Entry> entries;
    int findIndex(const string& key) const;
    
public:
    string& operator[](const string& key);
    const string& operator[](const string& key) const;
    void display() const;
};

#endif
```

**dictionary.cpp**
```cpp
#include "dictionary.h"
#include <iostream>
using namespace std;

Dictionary::Entry::Entry(string k, string v) : key(k), value(v) {}

int Dictionary::findIndex(const string& key) const {
    for (size_t i = 0; i < entries.size(); i++) {
        if (entries[i].key == key) return i;
    }
    return -1;
}

string& Dictionary::operator[](const string& key) {
    int index = findIndex(key);
    if (index == -1) {
        entries.push_back(Entry(key, ""));
        return entries.back().value;
    }
    return entries[index].value;
}

const string& Dictionary::operator[](const string& key) const {
    int index = findIndex(key);
    if (index == -1) {
        static string empty = "";
        return empty;
    }
    return entries[index].value;
}

void Dictionary::display() const {
    for (const auto& entry : entries) {
        cout << entry.key << " = " << entry.value << endl;
    }
}
```

**main.cpp**
```cpp
#include <iostream>
#include "dictionary.h"
using namespace std;

int main() {
    Dictionary dict;
    dict["name"] = "John";
    dict["age"] = "25";
    cout << dict["name"] << endl;
    return 0;
}
```

## Subscript Operator Rules

| Rule | Description |
|------|-------------|
| Must be member function | Cannot be non-member |
| Return reference | To allow modification |
| Provide const overload | For const objects |
| Check bounds | Always validate index |
| One parameter | Only one index parameter |

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Returning by value | Cannot modify elements | Return reference |
| Missing const version | Const objects can't use [] | Provide const overload |
| No bounds checking | Undefined behavior | Always check bounds |
| Returning local reference | Dangling reference | Return member reference |
| Using as non-member | Compilation error | Must be member function |

## Summary

- **Subscript operator** `[]` enables array-like access
- Must be **member function** (cannot be non-member)
- Return **reference** to allow modification
- Provide **const and non-const** versions
- Always **check bounds** before accessing
- Can be overloaded for **multiple dimensions** (returns proxy)
- Useful for **containers**, **strings**, **matrices**, **sparse arrays**

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

class MyArray {
private:
    int* data;
    int size;
    
public:
    MyArray(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = 0;
    }
    
    ~MyArray() { delete[] data; }
    
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    const int& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    int getSize() const { return size; }
};

int main() {
    MyArray arr(5);
    for (int i = 0; i < 5; i++) arr[i] = i * 10;
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
```

### Type 2: Multiple Files

**myarray.h**
```cpp
#ifndef MYARRAY_H
#define MYARRAY_H

class MyArray {
private:
    int* data;
    int size;
    
public:
    MyArray(int s);
    ~MyArray();
    
    int& operator[](int index);
    const int& operator[](int index) const;
    int getSize() const;
};

#endif
```

**myarray.cpp**
```cpp
#include "myarray.h"
#include <stdexcept>
using namespace std;

MyArray::MyArray(int s) : size(s) {
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = 0;
}

MyArray::~MyArray() { delete[] data; }

int& MyArray::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}

const int& MyArray::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}

int MyArray::getSize() const { return size; }
```

**main.cpp**
```cpp
#include <iostream>
#include "myarray.h"
using namespace std;

int main() {
    MyArray arr(5);
    for (int i = 0; i < 5; i++) arr[i] = i * 10;
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*