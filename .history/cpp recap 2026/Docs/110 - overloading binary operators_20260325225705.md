# 110 - overloading binary operators

# 110 - Overloading Binary Operators in C++

## What are Binary Operators?
Binary operators are operators that work on two operands (e.g., `a + b`, `x * y`). Overloading them allows user-defined types to support intuitive arithmetic operations.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Binary operators as member functions
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
    
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }
    
    // Comparison operators
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // Compound assignment operators
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
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
    
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c1 + c2 = " << c1 + c2 << endl;
    cout << "c1 - c2 = " << c1 - c2 << endl;
    cout << "c1 * c2 = " << c1 * c2 << endl;
    cout << "c1 / c2 = " << c1 / c2 << endl;
    cout << "c1 == c2? " << (c1 == c2 ? "Yes" : "No") << endl;
    
    c1 += c2;
    cout << "After c1 += c2: c1 = " << c1 << endl;
    
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
    
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    
    friend ostream& operator<<(ostream& os, const Complex& c);
};

#endif
```

### complex.cpp
```cpp
#include "complex.h"
#include <iostream>
using namespace std;

Complex::Complex(double r, double i) : real(r), imag(i) {}

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

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    return Complex((real * other.real + imag * other.imag) / denominator,
                   (imag * other.real - real * other.imag) / denominator);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

Complex& Complex::operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    real -= other.real;
    imag -= other.imag;
    return *this;
}

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) os << "+";
    os << c.imag << "i";
    return os;
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
    
    cout << c1 << " + " << c2 << " = " << c1 + c2 << endl;
    return 0;
}
```

## Member Function vs Friend Function Implementation

```cpp
#include <iostream>
using namespace std;

class Vector {
private:
    int x, y;
    
public:
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    
    // Member function version
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }
    
    // Friend function version (for symmetry with scalar multiplication)
    friend Vector operator*(int scalar, const Vector& v);
    friend Vector operator*(const Vector& v, int scalar);
    
    void display() const {
        cout << "(" << x << ", " << y << ")";
    }
};

// Friend function implementations
Vector operator*(int scalar, const Vector& v) {
    return Vector(scalar * v.x, scalar * v.y);
}

Vector operator*(const Vector& v, int scalar) {
    return scalar * v;  // Reuse the first version
}

int main() {
    Vector v1(2, 3);
    Vector v2(4, 5);
    
    cout << "v1 + v2 = ";
    (v1 + v2).display();
    cout << endl;
    
    cout << "3 * v1 = ";
    (3 * v1).display();
    cout << endl;
    
    cout << "v1 * 3 = ";
    (v1 * 3).display();
    cout << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: String Class with Binary Operators

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
    
    // Comparison operators
    bool operator==(const MyString& other) const {
        return strcmp(data, other.data) == 0;
    }
    
    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }
    
    bool operator<(const MyString& other) const {
        return strcmp(data, other.data) < 0;
    }
    
    bool operator>(const MyString& other) const {
        return strcmp(data, other.data) > 0;
    }
    
    // Compound assignment
    MyString& operator+=(const MyString& other) {
        *this = *this + other;
        return *this;
    }
    
    // Subscript operator
    char& operator[](int index) {
        return data[index];
    }
    
    const char& operator[](int index) const {
        return data[index];
    }
    
    int getLength() const { return length; }
    const char* c_str() const { return data; }
    
    friend ostream& operator<<(ostream& os, const MyString& s) {
        os << s.data;
        return os;
    }
    
    friend istream& operator>>(istream& is, MyString& s) {
        char buffer[1000];
        is >> buffer;
        s = MyString(buffer);
        return is;
    }
};

int main() {
    MyString s1("Hello");
    MyString s2(" World");
    MyString s3("Hello");
    
    MyString s4 = s1 + s2;
    cout << "s1 + s2 = " << s4 << endl;
    
    s1 += s2;
    cout << "After s1 += s2: s1 = " << s1 << endl;
    
    cout << "s1 == s3? " << (s1 == s3 ? "Yes" : "No") << endl;
    cout << "s3 < s2? " << (s3 < s2 ? "Yes" : "No") << endl;
    
    cout << "s1[0] = " << s1[0] << endl;
    s1[0] = 'J';
    cout << "After s1[0] = 'J': s1 = " << s1 << endl;
    
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
    bool operator!=(const MyString& other) const;
    bool operator<(const MyString& other) const;
    bool operator>(const MyString& other) const;
    MyString& operator+=(const MyString& other);
    char& operator[](int index);
    const char& operator[](int index) const;
    int getLength() const;
    const char* c_str() const;
    
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

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

bool MyString::operator<(const MyString& other) const {
    return strcmp(data, other.data) < 0;
}

bool MyString::operator>(const MyString& other) const {
    return strcmp(data, other.data) > 0;
}

MyString& MyString::operator+=(const MyString& other) {
    *this = *this + other;
    return *this;
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

const char* MyString::c_str() const {
    return data;
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
    
    s1 += s2;
    cout << s1 << endl;
    
    return 0;
}
```

### Example 2: Matrix Class with Binary Operators

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
    
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(other.data) {}
    
    int& operator()(int i, int j) {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            throw out_of_range("Index out of bounds");
        }
        return data[i][j];
    }
    
    const int& operator()(int i, int j) const {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            throw out_of_range("Index out of bounds");
        }
        return data[i][j];
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
    
    // Scalar multiplication (right)
    Matrix operator*(int scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }
    
    // Comparison
    bool operator==(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) return false;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] != other.data[i][j]) return false;
            }
        }
        return true;
    }
    
    // Compound assignment
    Matrix& operator+=(const Matrix& other) {
        *this = *this + other;
        return *this;
    }
    
    Matrix& operator-=(const Matrix& other) {
        *this = *this - other;
        return *this;
    }
    
    Matrix& operator*=(const Matrix& other) {
        *this = *this * other;
        return *this;
    }
    
    Matrix& operator*=(int scalar) {
        *this = *this * scalar;
        return *this;
    }
    
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

// Scalar multiplication (left)
Matrix operator*(int scalar, const Matrix& m) {
    return m * scalar;
}

int main() {
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    
    m1(0,0) = 1; m1(0,1) = 2;
    m1(1,0) = 3; m1(1,1) = 4;
    
    m2(0,0) = 5; m2(0,1) = 6;
    m2(1,0) = 7; m2(1,1) = 8;
    
    cout << "Matrix 1:" << endl << m1;
    cout << "Matrix 2:" << endl << m2;
    cout << "Matrix 1 + Matrix 2:" << endl << m1 + m2;
    cout << "Matrix 1 - Matrix 2:" << endl << m1 - m2;
    cout << "Matrix 1 * Matrix 2:" << endl << m1 * m2;
    cout << "3 * Matrix 1:" << endl << 3 * m1;
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
    Matrix(const Matrix& other);
    
    int& operator()(int i, int j);
    const int& operator()(int i, int j) const;
    
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(int scalar) const;
    bool operator==(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(int scalar);
    
    friend ostream& operator<<(ostream& os, const Matrix& m);
    friend Matrix operator*(int scalar, const Matrix& m);
};

#endif
```

**matrix.cpp**
```cpp
#include "matrix.h"
#include <stdexcept>
#include <iostream>
using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(other.data) {}

int& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw out_of_range("Index out of bounds");
    }
    return data[i][j];
}

const int& Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw out_of_range("Index out of bounds");
    }
    return data[i][j];
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

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) return false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (data[i][j] != other.data[i][j]) return false;
        }
    }
    return true;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    *this = *this + other;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    *this = *this - other;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    *this = *this * other;
    return *this;
}

Matrix& Matrix::operator*=(int scalar) {
    *this = *this * scalar;
    return *this;
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
    
    m1(0,0) = 1; m1(0,1) = 2;
    m1(1,0) = 3; m1(1,1) = 4;
    
    m2(0,0) = 5; m2(0,1) = 6;
    m2(1,0) = 7; m2(1,1) = 8;
    
    cout << m1 + m2 << endl;
    
    return 0;
}
```

### Example 3: Vector3D Class with All Binary Operators

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Vector3D {
private:
    double x, y, z;
    
public:
    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    // Arithmetic operators
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }
    
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
    
    // Dot product (scalar)
    double operator*(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    // Cross product (vector)
    Vector3D operator^(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    // Scalar multiplication
    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }
    
    // Division by scalar
    Vector3D operator/(double scalar) const {
        if (scalar != 0) {
            return Vector3D(x / scalar, y / scalar, z / scalar);
        }
        return *this;
    }
    
    // Comparison operators
    bool operator==(const Vector3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
    
    bool operator!=(const Vector3D& other) const {
        return !(*this == other);
    }
    
    // Compound assignment
    Vector3D& operator+=(const Vector3D& other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }
    
    Vector3D& operator-=(const Vector3D& other) {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }
    
    Vector3D& operator*=(double scalar) {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }
    
    Vector3D& operator/=(double scalar) {
        if (scalar != 0) {
            x /= scalar; y /= scalar; z /= scalar;
        }
        return *this;
    }
    
    double magnitude() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    Vector3D normalize() const {
        double mag = magnitude();
        if (mag > 0) {
            return *this / mag;
        }
        return *this;
    }
    
    friend ostream& operator<<(ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
    
    friend Vector3D operator*(double scalar, const Vector3D& v) {
        return v * scalar;
    }
};

int main() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1 + v2 = " << v1 + v2 << endl;
    cout << "v1 - v2 = " << v1 - v2 << endl;
    cout << "v1 · v2 = " << v1 * v2 << endl;
    cout << "v1 × v2 = " << (v1 ^ v2) << endl;
    cout << "3 * v1 = " << 3 * v1 << endl;
    cout << "v1 * 3 = " << v1 * 3 << endl;
    cout << "|v1| = " << v1.magnitude() << endl;
    cout << "Normalized v1 = " << v1.normalize() << endl;
    
    v1 += v2;
    cout << "After v1 += v2: v1 = " << v1 << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**vector3d.h**
```cpp
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
using namespace std;

class Vector3D {
private:
    double x, y, z;
    
public:
    Vector3D(double x = 0, double y = 0, double z = 0);
    
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    double operator*(const Vector3D& other) const;
    Vector3D operator^(const Vector3D& other) const;
    Vector3D operator*(double scalar) const;
    Vector3D operator/(double scalar) const;
    bool operator==(const Vector3D& other) const;
    bool operator!=(const Vector3D& other) const;
    Vector3D& operator+=(const Vector3D& other);
    Vector3D& operator-=(const Vector3D& other);
    Vector3D& operator*=(double scalar);
    Vector3D& operator/=(double scalar);
    
    double magnitude() const;
    Vector3D normalize() const;
    
    friend ostream& operator<<(ostream& os, const Vector3D& v);
    friend Vector3D operator*(double scalar, const Vector3D& v);
};

#endif
```

**vector3d.cpp**
```cpp
#include "vector3d.h"
#include <cmath>
#include <iostream>
using namespace std;

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

double Vector3D::operator*(const Vector3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::operator^(const Vector3D& other) const {
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator/(double scalar) const {
    if (scalar != 0) {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }
    return *this;
}

bool Vector3D::operator==(const Vector3D& other) const {
    return x == other.x && y == other.y && z == other.z;
}

bool Vector3D::operator!=(const Vector3D& other) const {
    return !(*this == other);
}

Vector3D& Vector3D::operator+=(const Vector3D& other) {
    x += other.x; y += other.y; z += other.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other) {
    x -= other.x; y -= other.y; z -= other.z;
    return *this;
}

Vector3D& Vector3D::operator*=(double scalar) {
    x *= scalar; y *= scalar; z *= scalar;
    return *this;
}

Vector3D& Vector3D::operator/=(double scalar) {
    if (scalar != 0) {
        x /= scalar; y /= scalar; z /= scalar;
    }
    return *this;
}

double Vector3D::magnitude() const {
    return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::normalize() const {
    double mag = magnitude();
    if (mag > 0) {
        return *this / mag;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Vector3D& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

Vector3D operator*(double scalar, const Vector3D& v) {
    return v * scalar;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "vector3d.h"
using namespace std;

int main() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    
    cout << v1 + v2 << endl;
    cout << v1 * v2 << endl;
    cout << 3 * v1 << endl;
    
    return 0;
}
```

## Binary Operators Quick Reference

| Operator | Member Function Signature | Friend Function Signature |
|----------|--------------------------|---------------------------|
| `+` | `T operator+(const T&) const` | `T operator+(const T&, const T&)` |
| `-` | `T operator-(const T&) const` | `T operator-(const T&, const T&)` |
| `*` | `T operator*(const T&) const` | `T operator*(const T&, const T&)` |
| `/` | `T operator/(const T&) const` | `T operator/(const T&, const T&)` |
| `==` | `bool operator==(const T&) const` | `bool operator==(const T&, const T&)` |
| `!=` | `bool operator!=(const T&) const` | `bool operator!=(const T&, const T&)` |
| `+=` | `T& operator+=(const T&)` | Not typically friend |
| `-=` | `T& operator-=(const T&)` | Not typically friend |

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Returning by value for compound assignment | Can't chain | Return reference to `*this` |
| Forgetting const for read-only operations | Can't use with const objects | Add const to parameters and member functions |
| Not handling self-assignment | Unexpected behavior | Check `this != &other` |
| Returning local reference | Dangling reference | Return by value or member reference |
| Inconsistent operator semantics | Confusing interface | Follow built-in operator behavior |

## Summary

- **Binary operators** work on two operands
- Can be implemented as **member functions** (left operand is `this`) or **friend functions** (symmetric)
- **Arithmetic operators** should return by value
- **Comparison operators** should return `bool`
- **Compound assignment operators** should return reference to `*this`
- **const correctness** is essential for read-only operations
- **Friend functions** are useful for symmetric operators (like scalar multiplication)

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
};

int main() {
    Number a(5), b(3);
    cout << a << " + " << b << " = " << a + b << endl;
    a += b;
    cout << "After +=: " << a << endl;
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