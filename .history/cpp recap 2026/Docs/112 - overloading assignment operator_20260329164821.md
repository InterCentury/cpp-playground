# 112 - Overloading Assignment Operator (=) in C++

## What is Assignment Operator Overloading?
The assignment operator (`=`) is used to copy the values from one object to another existing object. When overloading it, you must handle self-assignment, manage dynamic memory, and return a reference to `*this` to allow chaining.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private:
    char* data;
    int length;
    
public:
    // Constructor
    MyString(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        cout << "Constructor: " << data << endl;
    }
    
    // Copy constructor
    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        cout << "Copy constructor: " << data << endl;
    }
    
    // Assignment operator
    MyString& operator=(const MyString& other) {
        cout << "Assignment operator called" << endl;
        
        // Check for self-assignment
        if (this == &other) {
            cout << "Self-assignment detected, skipping" << endl;
            return *this;
        }
        
        // Delete existing data
        delete[] data;
        
        // Copy new data
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        
        return *this;
    }
    
    // Destructor
    ~MyString() {
        cout << "Destructor: " << data << endl;
        delete[] data;
    }
    
    void display() const {
        cout << data << endl;
    }
};

int main() {
    MyString s1("Hello");
    MyString s2("World");
    MyString s3("Temp");
    
    cout << "\n--- Assignment Operations ---" << endl;
    s2 = s1;  // Assignment
    s3 = s2 = s1;  // Chained assignment
    
    cout << "\n--- Results ---" << endl;
    cout << "s1: "; s1.display();
    cout << "s2: "; s2.display();
    cout << "s3: "; s3.display();
    
    // Self-assignment
    s1 = s1;
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### mystring.h
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
    MyString& operator=(const MyString& other);
    ~MyString();
    void display() const;
};

#endif
```

### mystring.cpp
```cpp
#include "mystring.h"
#include <cstring>
#include <iostream>
using namespace std;

MyString::MyString(const char* str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
    cout << "Constructor: " << data << endl;
}

MyString::MyString(const MyString& other) {
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
    cout << "Copy constructor: " << data << endl;
}

MyString& MyString::operator=(const MyString& other) {
    cout << "Assignment operator called" << endl;
    
    if (this == &other) {
        cout << "Self-assignment detected" << endl;
        return *this;
    }
    
    delete[] data;
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
    
    return *this;
}

MyString::~MyString() {
    cout << "Destructor: " << data << endl;
    delete[] data;
}

void MyString::display() const {
    cout << data << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "mystring.h"
using namespace std;

int main() {
    MyString s1("Hello");
    MyString s2("World");
    
    s2 = s1;
    s1.display();
    s2.display();
    
    return 0;
}
```

## Copy-and-Swap Idiom (Exception Safe)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class SafeString {
private:
    char* data;
    int length;
    
    void swap(SafeString& other) {
        std::swap(data, other.data);
        std::swap(length, other.length);
    }
    
public:
    SafeString(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        cout << "Constructor: " << data << endl;
    }
    
    // Copy constructor
    SafeString(const SafeString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        cout << "Copy constructor: " << data << endl;
    }
    
    // Assignment operator using copy-and-swap (exception safe)
    SafeString& operator=(SafeString other) {  // Pass by value (copy)
        cout << "Assignment operator (copy-and-swap)" << endl;
        swap(other);  // Swap with temporary
        return *this;
    }
    
    ~SafeString() {
        cout << "Destructor: " << data << endl;
        delete[] data;
    }
    
    void display() const {
        cout << data << endl;
    }
};

int main() {
    SafeString s1("Hello");
    SafeString s2("World");
    
    cout << "\n--- Copy-and-Swap Assignment ---" << endl;
    s2 = s1;
    
    cout << "\n--- Results ---" << endl;
    s1.display();
    s2.display();
    
    return 0;
}
```

## Move Assignment Operator (C++11)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class MoveString {
private:
    char* data;
    int length;
    
public:
    // Constructor
    MoveString(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        cout << "Constructor: " << data << endl;
    }
    
    // Copy constructor
    MoveString(const MoveString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        cout << "Copy constructor: " << data << endl;
    }
    
    // Move constructor
    MoveString(MoveString&& other) noexcept 
        : data(other.data), length(other.length) {
        other.data = nullptr;
        other.length = 0;
        cout << "Move constructor" << endl;
    }
    
    // Copy assignment
    MoveString& operator=(const MoveString& other) {
        cout << "Copy assignment" << endl;
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }
    
    // Move assignment
    MoveString& operator=(MoveString&& other) noexcept {
        cout << "Move assignment" << endl;
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }
    
    // Destructor
    ~MoveString() {
        cout << "Destructor: " << (data ? data : "nullptr") << endl;
        delete[] data;
    }
    
    void display() const {
        if (data) cout << data << endl;
        else cout << "nullptr" << endl;
    }
};

int main() {
    MoveString s1("Hello");
    MoveString s2("World");
    
    cout << "\n--- Copy Assignment ---" << endl;
    s2 = s1;
    
    cout << "\n--- Move Assignment ---" << endl;
    MoveString s3("Temporary");
    s1 = std::move(s3);
    
    cout << "\n--- Results ---" << endl;
    cout << "s1: "; s1.display();
    cout << "s2: "; s2.display();
    cout << "s3: "; s3.display();
    
    return 0;
}
```

## Practical Examples

### Example 1: Array Class with Assignment Operator

#### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class IntArray {
private:
    int* data;
    int size;
    
public:
    IntArray(int s = 0) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
        cout << "Constructor: Array of size " << size << endl;
    }
    
    // Copy constructor
    IntArray(const IntArray& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Copy constructor" << endl;
    }
    
    // Assignment operator
    IntArray& operator=(const IntArray& other) {
        cout << "Assignment operator" << endl;
        
        if (this == &other) {
            cout << "Self-assignment" << endl;
            return *this;
        }
        
        // Delete old data
        delete[] data;
        
        // Allocate and copy new data
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        
        return *this;
    }
    
    // Move assignment
    IntArray& operator=(IntArray&& other) noexcept {
        cout << "Move assignment" << endl;
        
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    int& operator[](int index) {
        return data[index];
    }
    
    const int& operator[](int index) const {
        return data[index];
    }
    
    int getSize() const { return size; }
    
    void display() const {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    ~IntArray() {
        cout << "Destructor: Array of size " << size << endl;
        delete[] data;
    }
};

int main() {
    IntArray arr1(5);
    IntArray arr2(3);
    
    // Initialize arr1
    for (int i = 0; i < 5; i++) {
        arr1[i] = i * 10;
    }
    
    cout << "\narr1: "; arr1.display();
    cout << "arr2: "; arr2.display();
    
    cout << "\n--- Assignment ---" << endl;
    arr2 = arr1;
    
    cout << "\narr2 after assignment: "; arr2.display();
    
    cout << "\n--- Move Assignment ---" << endl;
    IntArray arr3(2);
    arr3 = std::move(arr2);
    
    cout << "\narr3: "; arr3.display();
    cout << "arr2 after move: "; arr2.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**intarray.h**
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
    IntArray(int s = 0);
    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);
    IntArray& operator=(IntArray&& other) noexcept;
    int& operator[](int index);
    const int& operator[](int index) const;
    int getSize() const;
    void display() const;
    ~IntArray();
};

#endif
```

**intarray.cpp**
```cpp
#include "intarray.h"
#include <iostream>
using namespace std;

IntArray::IntArray(int s) : size(s) {
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = 0;
    cout << "Constructor: Array of size " << size << endl;
}

IntArray::IntArray(const IntArray& other) : size(other.size) {
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = other.data[i];
    cout << "Copy constructor" << endl;
}

IntArray& IntArray::operator=(const IntArray& other) {
    cout << "Assignment operator" << endl;
    if (this == &other) return *this;
    
    delete[] data;
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = other.data[i];
    
    return *this;
}

IntArray& IntArray::operator=(IntArray&& other) noexcept {
    cout << "Move assignment" << endl;
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

int& IntArray::operator[](int index) { return data[index]; }
const int& IntArray::operator[](int index) const { return data[index]; }
int IntArray::getSize() const { return size; }

void IntArray::display() const {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

IntArray::~IntArray() {
    cout << "Destructor: Array of size " << size << endl;
    delete[] data;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "intarray.h"
using namespace std;

int main() {
    IntArray arr1(5);
    IntArray arr2(3);
    
    for (int i = 0; i < 5; i++) arr1[i] = i * 10;
    
    arr2 = arr1;
    arr1.display();
    arr2.display();
    
    return 0;
}
```

### Example 2: Matrix Class with Assignment Operator

#### Type 1: Single File
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    vector<vector<int>> data;
    
public:
    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {
        cout << "Constructor: " << rows << "x" << cols << " matrix" << endl;
    }
    
    // Copy constructor
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(other.data) {
        cout << "Copy constructor" << endl;
    }
    
    // Assignment operator
    Matrix& operator=(const Matrix& other) {
        cout << "Assignment operator" << endl;
        
        if (this == &other) {
            cout << "Self-assignment" << endl;
            return *this;
        }
        
        rows = other.rows;
        cols = other.cols;
        data = other.data;
        
        return *this;
    }
    
    // Move assignment
    Matrix& operator=(Matrix&& other) noexcept {
        cout << "Move assignment" << endl;
        
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = std::move(other.data);
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }
    
    vector<int>& operator[](int index) {
        return data[index];
    }
    
    const vector<int>& operator[](int index) const {
        return data[index];
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
    Matrix m1(2, 2);
    Matrix m2(3, 3);
    
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;
    
    cout << "\nm1:" << endl;
    m1.display();
    
    cout << "\n--- Assignment ---" << endl;
    m2 = m1;
    
    cout << "\nm2 after assignment:" << endl;
    m2.display();
    
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
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    vector<int>& operator[](int index);
    const vector<int>& operator[](int index) const;
    void display() const;
};

#endif
```

**matrix.cpp**
```cpp
#include "matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {
    cout << "Constructor: " << rows << "x" << cols << " matrix" << endl;
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(other.data) {
    cout << "Copy constructor" << endl;
}

Matrix& Matrix::operator=(const Matrix& other) {
    cout << "Assignment operator" << endl;
    if (this == &other) return *this;
    
    rows = other.rows;
    cols = other.cols;
    data = other.data;
    
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    cout << "Move assignment" << endl;
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = std::move(other.data);
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}

vector<int>& Matrix::operator[](int index) { return data[index]; }
const vector<int>& Matrix::operator[](int index) const { return data[index]; }

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
    Matrix m1(2, 2);
    Matrix m2(3, 3);
    
    m1[0][0] = 1;
    m2 = m1;
    m2.display();
    
    return 0;
}
```

### Example 3: Complex Number with Assignment

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {
        cout << "Constructor: " << *this << endl;
    }
    
    // Copy constructor
    Complex(const Complex& other) : real(other.real), imag(other.imag) {
        cout << "Copy constructor: " << *this << endl;
    }
    
    // Assignment operator
    Complex& operator=(const Complex& other) {
        cout << "Assignment operator: ";
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        cout << *this << endl;
        return *this;
    }
    
    // Move assignment
    Complex& operator=(Complex&& other) noexcept {
        cout << "Move assignment: ";
        if (this != &other) {
            real = other.real;
            imag = other.imag;
            other.real = 0;
            other.imag = 0;
        }
        cout << *this << endl;
        return *this;
    }
    
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << "+";
        os << c.imag << "i";
        return os;
    }
};

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);
    Complex c3(5, 6);
    
    cout << "\n--- Assignment Operations ---" << endl;
    c2 = c1;
    c3 = c2 = c1;
    
    cout << "\n--- Results ---" << endl;
    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    cout << "c3: " << c3 << endl;
    
    cout << "\n--- Move Assignment ---" << endl;
    c3 = std::move(c2);
    cout << "c2 after move: " << c2 << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**complex.h**
```cpp
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0);
    Complex(const Complex& other);
    Complex& operator=(const Complex& other);
    Complex& operator=(Complex&& other) noexcept;
    
    friend ostream& operator<<(ostream& os, const Complex& c);
};

#endif
```

**complex.cpp**
```cpp
#include "complex.h"
#include <iostream>
using namespace std;

Complex::Complex(double r, double i) : real(r), imag(i) {
    cout << "Constructor: " << *this << endl;
}

Complex::Complex(const Complex& other) : real(other.real), imag(other.imag) {
    cout << "Copy constructor: " << *this << endl;
}

Complex& Complex::operator=(const Complex& other) {
    cout << "Assignment operator: ";
    if (this != &other) {
        real = other.real;
        imag = other.imag;
    }
    cout << *this << endl;
    return *this;
}

Complex& Complex::operator=(Complex&& other) noexcept {
    cout << "Move assignment: ";
    if (this != &other) {
        real = other.real;
        imag = other.imag;
        other.real = 0;
        other.imag = 0;
    }
    cout << *this << endl;
    return *this;
}

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) os << "+";
    os << c.imag << "i";
    return os;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "complex.h"
using namespace std;

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    c2 = c1;
    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    
    return 0;
}
```

## Assignment Operator Rules

| Rule | Description |
|------|-------------|
| Return type | `ClassName&` (reference to `*this`) |
| Self-assignment check | `if (this == &other) return *this;` |
| Delete old resources | Free existing memory before allocation |
| Copy new resources | Allocate and copy from other object |
| Exception safety | Use copy-and-swap idiom |
| Chaining | Return `*this` to allow `a = b = c` |

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting self-assignment check | Memory corruption | Check `this != &other` |
| Deleting before copying | Self-assignment crash | Check first or use copy-and-swap |
| Returning void | Can't chain assignments | Return `*this` |
| Returning by value | Extra copy overhead | Return reference |
| Memory leak | Old data not freed | Delete before new allocation |

## Summary

- **Assignment operator** copies values from one object to another existing object
- Always **check for self-assignment** to avoid corruption
- **Delete old resources** before allocating new ones
- **Return reference to `*this`** for chaining
- **Copy-and-swap** idiom provides strong exception guarantee
- **Move assignment** (C++11) transfers resources efficiently
- Part of **Rule of Three/Five** (destructor, copy constructor, copy assignment)

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class MyClass {
private:
    int* data;
    int size;
    
public:
    MyClass(int s = 0) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = 0;
    }
    
    MyClass(const MyClass& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
    }
    
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        return *this;
    }
    
    ~MyClass() {
        delete[] data;
    }
};

int main() {
    MyClass a(5), b(3);
    b = a;
    return 0;
}
```

### Type 2: Multiple Files

**myclass.h**
```cpp
#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass {
private:
    int* data;
    int size;
    
public:
    MyClass(int s = 0);
    MyClass(const MyClass& other);
    MyClass& operator=(const MyClass& other);
    ~MyClass();
};

#endif
```

**myclass.cpp**
```cpp
#include "myclass.h"

MyClass::MyClass(int s) : size(s) {
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = 0;
}

MyClass::MyClass(const MyClass& other) : size(other.size) {
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = other.data[i];
}

MyClass& MyClass::operator=(const MyClass& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = other.data[i];
    }
    return *this;
}

MyClass::~MyClass() {
    delete[] data;
}
```

**main.cpp**
```cpp
#include "myclass.h"

int main() {
    MyClass a(5), b(3);
    b = a;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*
