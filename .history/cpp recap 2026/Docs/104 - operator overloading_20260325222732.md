# 104 - Operator Overloading in C++

## What is Operator Overloading?
Operator overloading allows you to redefine the behavior of C++ operators (like +, -, *, ==, etc.) for user-defined types. This makes user-defined types work intuitively like built-in types.

## Type 1: Single File Implementation

```cpp
#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Unary operator overloading
    Complex operator-() const {
        return Complex(-real, -imag);
    }
    
    // Binary operator overloading as member function
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }
    
    // Comparison operators
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // Assignment operator
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }
    
    // Compound assignment
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    // Stream operators (friend functions)
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);
};

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) os << "+";
    os << c.imag << "i";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    cout << "Enter real and imaginary parts: ";
    is >> c.real >> c.imag;
    return is;
}

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << c1 + c2 << endl;
    cout << "c1 - c2 = " << c1 - c2 << endl;
    cout << "c1 * c2 = " << c1 * c2 << endl;
    cout << "-c1 = " << -c1 << endl;
    
    Complex c3;
    cin >> c3;
    cout << "You entered: " << c3 << endl;
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### complex.h
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
    
    Complex operator-() const;
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    Complex& operator=(const Complex& other);
    Complex& operator+=(const Complex& other);
    
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);
};

#endif
```

### complex.cpp
```cpp
#include "complex.h"
#include <iostream>
using namespace std;

Complex::Complex(double r, double i) : real(r), imag(i) {}

Complex Complex::operator-() const {
    return Complex(-real, -imag);
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - imag * other.imag,
                   real * other.imag + imag * other.real);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

Complex& Complex::operator=(const Complex& other) {
    if (this != &other) {
        real = other.real;
        imag = other.imag;
    }
    return *this;
}

Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
}

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) os << "+";
    os << c.imag << "i";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    is >> c.real >> c.imag;
    return is;
}
```

### main.cpp
```cpp
#include <iostream>
#include "complex.h"
using namespace std;

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << c1 + c2 << endl;
    
    return 0;
}
```

## Types of Operators That Can Be Overloaded

### 1. Unary Operators

```cpp
#include <iostream>
using namespace std;

class Counter {
private:
    int value;
    
public:
    Counter(int v = 0) : value(v) {}
    
    // Prefix increment (++c)
    Counter& operator++() {
        ++value;
        return *this;
    }
    
    // Postfix increment (c++)
    Counter operator++(int) {
        Counter temp = *this;
        ++value;
        return temp;
    }
    
    // Prefix decrement (--c)
    Counter& operator--() {
        --value;
        return *this;
    }
    
    // Postfix decrement (c--)
    Counter operator--(int) {
        Counter temp = *this;
        --value;
        return temp;
    }
    
    // Unary minus (-c)
    Counter operator-() const {
        return Counter(-value);
    }
    
    // Logical NOT (!c)
    bool operator!() const {
        return value == 0;
    }
    
    int getValue() const { return value; }
    
    friend ostream& operator<<(ostream& os, const Counter& c);
};

ostream& operator<<(ostream& os, const Counter& c) {
    os << c.value;
    return os;
}

int main() {
    Counter c(5);
    
    cout << "c = " << c << endl;
    cout << "++c = " << ++c << endl;
    cout << "c++ = " << c++ << endl;
    cout << "c = " << c << endl;
    cout << "--c = " << --c << endl;
    cout << "c-- = " << c-- << endl;
    cout << "c = " << c << endl;
    cout << "-c = " << -c << endl;
    cout << "!c = " << !c << endl;
    
    return 0;
}
```

### 2. Binary Operators

```cpp
#include <iostream>
using namespace std;

class Vector {
private:
    int x, y, z;
    
public:
    Vector(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
    
    // Arithmetic operators
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }
    
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }
    
    // Dot product (scalar multiplication)
    int operator*(const Vector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    // Scalar multiplication
    Vector operator*(int scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }
    
    // Comparison operators
    bool operator==(const Vector& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
    
    // Compound assignment
    Vector& operator+=(const Vector& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    
    friend ostream& operator<<(ostream& os, const Vector& v);
    friend Vector operator*(int scalar, const Vector& v);
};

ostream& operator<<(ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

Vector operator*(int scalar, const Vector& v) {
    return Vector(v.x * scalar, v.y * scalar, v.z * scalar);
}

int main() {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1 + v2 = " << v1 + v2 << endl;
    cout << "v1 - v2 = " << v1 - v2 << endl;
    cout << "v1 * v2 (dot) = " << v1 * v2 << endl;
    cout << "v1 * 3 = " << v1 * 3 << endl;
    cout << "3 * v1 = " << 3 * v1 << endl;
    
    return 0;
}
```

### 3. Subscript Operator []

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
    
    // Non-const version (allows modification)
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    // Const version (read-only)
    const int& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    int getSize() const { return size; }
    
    ~IntArray() {
        delete[] data;
    }
};

int main() {
    IntArray arr(5);
    
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    
    cout << "arr[0] = " << arr[0] << endl;
    cout << "arr[1] = " << arr[1] << endl;
    cout << "arr[2] = " << arr[2] << endl;
    
    return 0;
}
```

### 4. Function Call Operator ()

```cpp
#include <iostream>
using namespace std;

class Multiplier {
private:
    int factor;
    
public:
    Multiplier(int f) : factor(f) {}
    
    // Function call operator
    int operator()(int x) const {
        return x * factor;
    }
    
    int operator()(int x, int y) const {
        return (x + y) * factor;
    }
};

int main() {
    Multiplier times2(2);
    Multiplier times3(3);
    
    cout << "times2(5) = " << times2(5) << endl;
    cout << "times3(5) = " << times3(5) << endl;
    cout << "times2(3, 4) = " << times2(3, 4) << endl;
    
    return 0;
}
```

### 5. Stream Operators (<<, >>)

```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    
public:
    Person(string n = "", int a = 0) : name(n), age(a) {}
    
    friend ostream& operator<<(ostream& os, const Person& p);
    friend istream& operator>>(istream& is, Person& p);
};

ostream& operator<<(ostream& os, const Person& p) {
    os << p.name << " (" << p.age << " years)";
    return os;
}

istream& operator>>(istream& is, Person& p) {
    cout << "Enter name: ";
    is >> p.name;
    cout << "Enter age: ";
    is >> p.age;
    return is;
}

int main() {
    Person p1("John", 25);
    Person p2;
    
    cout << "p1 = " << p1 << endl;
    cin >> p2;
    cout << "p2 = " << p2 << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: String Class with Operators

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
    
    // Assignment operator
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }
    
    // Concatenation
    MyString operator+(const MyString& other) const {
        MyString result;
        delete[] result.data;
        result.length = length + other.length;
        result.data = new char[result.length + 1];
        strcpy(result.data, data);
        strcat(result.data, other.data);
        return result;
    }
    
    // Comparison
    bool operator==(const MyString& other) const {
        return strcmp(data, other.data) == 0;
    }
    
    bool operator<(const MyString& other) const {
        return strcmp(data, other.data) < 0;
    }
    
    bool operator>(const MyString& other) const {
        return strcmp(data, other.data) > 0;
    }
    
    // Subscript
    char& operator[](int index) {
        return data[index];
    }
    
    const char& operator[](int index) const {
        return data[index];
    }
    
    // Length
    int getLength() const { return length; }
    
    // Stream operators
    friend ostream& operator<<(ostream& os, const MyString& s);
    friend istream& operator>>(istream& is, MyString& s);
};

ostream& operator<<(ostream& os, const MyString& s) {
    os << s.data;
    return os;
}

istream& operator>>(istream& is, MyString& s) {
    char buffer[1000];
    is >> buffer;
    s = MyString(buffer);
    return is;
}

int main() {
    MyString s1("Hello");
    MyString s2(" World");
    MyString s3 = s1 + s2;
    
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s3[0] = " << s3[0] << endl;
    
    s3[0] = 'J';
    cout << "After modification: " << s3 << endl;
    
    MyString s4("Hello World");
    if (s3 == s4) {
        cout << "Strings are equal" << endl;
    }
    
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
    
    MyString& operator=(const MyString& other);
    MyString operator+(const MyString& other) const;
    bool operator==(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator>(const MyString& other) const;
    char& operator[](int index);
    const char& operator[](int index) const;
    int getLength() const;
    
    friend ostream& operator<<(ostream& os, const MyString& s);
    friend istream& operator>>(istream& is, MyString& s);
};

#endif
```

**mystring.cpp**
```cpp
#include "mystring.h"
#include <cstring>
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

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }
    return *this;
}

MyString MyString::operator+(const MyString& other) const {
    MyString result;
    delete[] result.data;
    result.length = length + other.length;
    result.data = new char[result.length + 1];
    strcpy(result.data, data);
    strcat(result.data, other.data);
    return result;
}

bool MyString::operator==(const MyString& other) const {
    return strcmp(data, other.data) == 0;
}

bool MyString::operator<(const MyString& other) const {
    return strcmp(data, other.data) < 0;
}

bool MyString::operator>(const MyString& other) const {
    return strcmp(data, other.data) > 0;
}

char& MyString::operator[](int index) {
    return data[index];
}

const char& MyString::operator[](int index) const {
    return data[index];
}

int MyString::getLength() const {
    return length;
}

ostream& operator<<(ostream& os, const MyString& s) {
    os << s.data;
    return os;
}

istream& operator>>(istream& is, MyString& s) {
    char buffer[1000];
    is >> buffer;
    s = MyString(buffer);
    return is;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "mystring.h"
using namespace std;

int main() {
    MyString s1("Hello");
    MyString s2(" World");
    MyString s3 = s1 + s2;
    
    cout << s3 << endl;
    
    return 0;
}
```

### Example 2: Matrix Class with Operators

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
    
    // Subscript operator for row access
    vector<int>& operator[](int index) {
        if (index < 0 || index >= rows) {
            throw out_of_range("Row index out of bounds");
        }
        return data[index];
    }
    
    const vector<int>& operator[](int index) const {
        if (index < 0 || index >= rows) {
            throw out_of_range("Row index out of bounds");
        }
        return data[index];
    }
    
    // Addition
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions mismatch");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    
    // Subtraction
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions mismatch");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
    
    // Multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions incompatible for multiplication");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                int sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }
    
    // Scalar multiplication
    Matrix operator*(int scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }
    
    // Compound assignment
    Matrix& operator+=(const Matrix& other) {
        *this = *this + other;
        return *this;
    }
    
    // Equality
    bool operator==(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) return false;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] != other.data[i][j]) return false;
            }
        }
        return true;
    }
    
    // Stream output
    friend ostream& operator<<(ostream& os, const Matrix& m) {
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                os << m.data[i][j] << "\t";
            }
            os << endl;
        }
        return os;
    }
};

// Scalar multiplication (left side)
Matrix operator*(int scalar, const Matrix& m) {
    return m * scalar;
}

int main() {
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;
    
    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;
    
    cout << "Matrix 1:" << endl << m1;
    cout << "Matrix 2:" << endl << m2;
    cout << "Matrix 1 + Matrix 2:" << endl << m1 + m2;
    cout << "Matrix 1 * Matrix 2:" << endl << m1 * m2;
    cout << "Matrix 1 * 3:" << endl << m1 * 3;
    
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
    
    vector<int>& operator[](int index);
    const vector<int>& operator[](int index) const;
    
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(int scalar) const;
    Matrix& operator+=(const Matrix& other);
    bool operator==(const Matrix& other) const;
    
    friend ostream& operator<<(ostream& os, const Matrix& m);
    friend Matrix operator*(int scalar, const Matrix& m);
};

#endif
```

**matrix.cpp**
```cpp
#include "matrix.h"
#include <stdexcept>
using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {}

vector<int>& Matrix::operator[](int index) {
    if (index < 0 || index >= rows) {
        throw out_of_range("Row index out of bounds");
    }
    return data[index];
}

const vector<int>& Matrix::operator[](int index) const {
    if (index < 0 || index >= rows) {
        throw out_of_range("Row index out of bounds");
    }
    return data[index];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("Matrix dimensions mismatch");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw invalid_argument("Matrix dimensions mismatch");
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw invalid_argument("Matrix dimensions incompatible for multiplication");
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            int sum = 0;
            for (int k = 0; k < cols; k++) {
                sum += data[i][k] * other.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

Matrix Matrix::operator*(int scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    *this = *this + other;
    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) return false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (data[i][j] != other.data[i][j]) return false;
        }
    }
    return true;
}

ostream& operator<<(ostream& os, const Matrix& m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            os << m.data[i][j] << "\t";
        }
        os << endl;
    }
    return os;
}

Matrix operator*(int scalar, const Matrix& m) {
    return m * scalar;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "matrix.h"
using namespace std;

int main() {
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;
    
    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;
    
    cout << "Sum:" << endl << m1 + m2;
    
    return 0;
}
```

## Rules for Operator Overloading

### Can Be Overloaded
- Arithmetic: `+`, `-`, `*`, `/`, `%`
- Relational: `==`, `!=`, `<`, `>`, `<=`, `>=`
- Logical: `&&`, `||`, `!`
- Bitwise: `&`, `|`, `^`, `~`, `<<`, `>>`
- Assignment: `=`, `+=`, `-=`, etc.
- Increment/Decrement: `++`, `--`
- Subscript: `[]`
- Function call: `()`
- Arrow: `->`
- New/Delete: `new`, `delete`

### Cannot Be Overloaded
- Scope resolution: `::`
- Member access: `.`
- Pointer to member: `.*`
- Ternary: `?:`
- sizeof
- typeid

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Returning by value for assignment | Can't chain | Return reference to *this |
| Forgetting const for read-only operations | Can't use with const objects | Add const to appropriate methods |
| Not checking self-assignment | Memory corruption | Check `this != &other` |
| Returning local reference | Dangling reference | Return by value or member reference |
| Overloading operators that don't make sense | Confusing interface | Only overload meaningful operators |

## Summary

- **Operator overloading** makes user-defined types work like built-in types
- Can be implemented as **member functions** or **friend functions**
- **Unary operators** (++, --, !) modify or examine single object
- **Binary operators** (+, -, *, /) combine two objects
- **Assignment operator** should return reference to *this
- **Stream operators** (<<, >>) are typically friend functions
- **Subscript operator** should provide const and non-const versions
- Always maintain **intuitive behavior**

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class Number {
private:
    int value;
    
public:
    Number(int v = 0) : value(v) {}
    
    Number operator+(const Number& other) const {
        return Number(value + other.value);
    }
    
    Number& operator+=(const Number& other) {
        value += other.value;
        return *this;
    }
    
    bool operator==(const Number& other) const {
        return value == other.value;
    }
    
    friend ostream& operator<<(ostream& os, const Number& n) {
        os << n.value;
        return os;
    }
    
    friend istream& operator>>(istream& is, Number& n) {
        is >> n.value;
        return is;
    }
};

int main() {
    Number a(5), b(3);
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a == b? " << (a == b ? "Yes" : "No") << endl;
    return 0;
}
```

### Type 2: Multiple Files

**number.h**
```cpp
#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
using namespace std;

class Number {
private:
    int value;
    
public:
    Number(int v = 0);
    Number operator+(const Number& other) const;
    Number& operator+=(const Number& other);
    bool operator==(const Number& other) const;
    
    friend ostream& operator<<(ostream& os, const Number& n);
    friend istream& operator>>(istream& is, Number& n);
};

#endif
```

**number.cpp**
```cpp
#include "number.h"
using namespace std;

Number::Number(int v) : value(v) {}

Number Number::operator+(const Number& other) const {
    return Number(value + other.value);
}

Number& Number::operator+=(const Number& other) {
    value += other.value;
    return *this;
}

bool Number::operator==(const Number& other) const {
    return value == other.value;
}

ostream& operator<<(ostream& os, const Number& n) {
    os << n.value;
    return os;
}

istream& operator>>(istream& is, Number& n) {
    is >> n.value;
    return is;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "number.h"
using namespace std;

int main() {
    Number a(5), b(3);
    cout << a + b << endl;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*