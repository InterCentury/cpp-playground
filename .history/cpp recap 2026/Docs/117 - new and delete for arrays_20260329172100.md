# 117 - new and delete for Arrays in C++

## What are new[] and delete[]?
The `new[]` operator dynamically allocates arrays on the heap, and `delete[]` deallocates them. Unlike `new` for single objects, array versions handle multiple objects and call constructors/destructors for each element.

## Type 1: Single File Implementation

```cpp
#include <iostream>
using namespace std;

class Student {
private:
    int id;
    string name;
    
public:
    Student() : id(0), name("Unknown") {
        cout << "Default constructor called" << endl;
    }
    
    Student(int i, string n) : id(i), name(n) {
        cout << "Parameterized constructor: " << name << endl;
    }
    
    ~Student() {
        cout << "Destructor: " << name << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
    }
};

int main() {
    // Array of default-constructed objects
    Student* students1 = new Student[3];
    
    for (int i = 0; i < 3; i++) {
        students1[i].display();
    }
    
    delete[] students1;
    
    // Array with initializer list (C++11)
    Student* students2 = new Student[3]{
        {101, "Alice"},
        {102, "Bob"},
        {103, "Carol"}
    };
    
    for (int i = 0; i < 3; i++) {
        students2[i].display();
    }
    
    delete[] students2;
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### student.h
```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
private:
    int id;
    string name;
    
public:
    Student();
    Student(int i, string n);
    ~Student();
    void display() const;
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student() : id(0), name("Unknown") {
    cout << "Default constructor called" << endl;
}

Student::Student(int i, string n) : id(i), name(n) {
    cout << "Parameterized constructor: " << name << endl;
}

Student::~Student() {
    cout << "Destructor: " << name << endl;
}

void Student::display() const {
    cout << "ID: " << id << ", Name: " << name << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student* students = new Student[3]{
        {101, "Alice"},
        {102, "Bob"},
        {103, "Carol"}
    };
    
    for (int i = 0; i < 3; i++) {
        students[i].display();
    }
    
    delete[] students;
    return 0;
}
```

## Single-Dimensional Arrays

### Basic Integer Array
```cpp
#include <iostream>
using namespace std;

int main() {
    // Basic array allocation
    int* arr1 = new int[5];
    
    // Initialize
    for (int i = 0; i < 5; i++) {
        arr1[i] = i * 10;
    }
    
    // Display
    for (int i = 0; i < 5; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    delete[] arr1;
    
    // Array with initialization
    int* arr2 = new int[5]{10, 20, 30, 40, 50};
    
    for (int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    delete[] arr2;
    
    // Zero-initialized array
    int* arr3 = new int[5]();
    
    for (int i = 0; i < 5; i++) {
        cout << arr3[i] << " ";
    }
    cout << endl;
    
    delete[] arr3;
    
    return 0;
}
```

### Dynamic Size Array
```cpp
#include <iostream>
using namespace std;

int main() {
    int size;
    
    cout << "Enter array size: ";
    cin >> size;
    
    // Dynamic size array
    int* arr = new int[size];
    
    cout << "Enter " << size << " numbers: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    
    cout << "You entered: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    delete[] arr;
    
    return 0;
}
```

## Two-Dimensional Arrays

### Method 1: Array of Pointers (Jagged Array)

```cpp
#include <iostream>
using namespace std;

int main() {
    int rows = 3, cols = 4;
    
    // Allocate array of row pointers
    int** matrix = new int*[rows];
    
    // Allocate each row
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    
    // Initialize
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
        }
    }
    
    // Display
    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    // Deallocate in reverse order
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    
    return 0;
}
```

### Method 2: Single Contiguous Block

```cpp
#include <iostream>
using namespace std;

int main() {
    int rows = 3, cols = 4;
    
    // Allocate single contiguous block
    int* matrix = new int[rows * cols];
    
    // Access using index calculation: [i * cols + j]
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = i * cols + j + 1;
        }
    }
    
    // Display
    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i * cols + j] << "\t";
        }
        cout << endl;
    }
    
    delete[] matrix;
    
    return 0;
}
```

## Three-Dimensional Arrays

```cpp
#include <iostream>
using namespace std;

int main() {
    int depth = 2, rows = 3, cols = 4;
    
    // Allocate 3D array
    int*** cube = new int**[depth];
    
    for (int i = 0; i < depth; i++) {
        cube[i] = new int*[rows];
        for (int j = 0; j < rows; j++) {
            cube[i][j] = new int[cols];
        }
    }
    
    // Initialize
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                cube[i][j][k] = i * 100 + j * 10 + k;
            }
        }
    }
    
    // Display
    for (int i = 0; i < depth; i++) {
        cout << "Layer " << i << ":" << endl;
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                cout << cube[i][j][k] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    // Deallocate in reverse order
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < rows; j++) {
            delete[] cube[i][j];
        }
        delete[] cube[i];
    }
    delete[] cube;
    
    return 0;
}
```

## Practical Examples

### Example 1: Dynamic Array Class

#### Type 1: Single File
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;
    
    void resize() {
        capacity *= 2;
        int* newData = new int[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    
public:
    DynamicArray(int cap = 10) : size(0), capacity(cap) {
        data = new int[capacity];
        cout << "Array created with capacity " << capacity << endl;
    }
    
    ~DynamicArray() {
        delete[] data;
        cout << "Array destroyed" << endl;
    }
    
    void push(int value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }
    
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
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
        cout << "]" << endl;
    }
};

int main() {
    DynamicArray arr(3);
    
    arr.push(10);
    arr.push(20);
    arr.push(30);
    arr.push(40);  // Triggers resize
    arr.push(50);
    
    arr.display();
    cout << "Size: " << arr.getSize() << endl;
    
    arr[2] = 99;
    cout << "After modification: ";
    arr.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**dynamicarray.h**
```cpp
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;
    
    void resize();
    
public:
    DynamicArray(int cap = 10);
    ~DynamicArray();
    void push(int value);
    int& operator[](int index);
    int getSize() const;
    void display() const;
};

#endif
```

**dynamicarray.cpp**
```cpp
#include "dynamicarray.h"
#include <iostream>
#include <stdexcept>
using namespace std;

DynamicArray::DynamicArray(int cap) : size(0), capacity(cap) {
    data = new int[capacity];
    cout << "Array created with capacity " << capacity << endl;
}

DynamicArray::~DynamicArray() {
    delete[] data;
    cout << "Array destroyed" << endl;
}

void DynamicArray::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (int i = 0; i < size; i++) newData[i] = data[i];
    delete[] data;
    data = newData;
}

void DynamicArray::push(int value) {
    if (size >= capacity) resize();
    data[size++] = value;
}

int& DynamicArray::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return data[index];
}

int DynamicArray::getSize() const { return size; }

void DynamicArray::display() const {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "dynamicarray.h"
using namespace std;

int main() {
    DynamicArray arr(3);
    arr.push(10);
    arr.push(20);
    arr.push(30);
    arr.push(40);
    arr.display();
    return 0;
}
```

### Example 2: Matrix Class with 2D Array

#### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    int** data;
    
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
        cout << "Matrix " << rows << "x" << cols << " created" << endl;
    }
    
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        cout << "Matrix destroyed" << endl;
    }
    
    int* operator[](int row) {
        return data[row];
    }
    
    const int* operator[](int row) const {
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
    
    // Fill matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] = i * 4 + j + 1;
        }
    }
    
    mat.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**matrix.h**
```cpp
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
    int rows;
    int cols;
    int** data;
    
public:
    Matrix(int r, int c);
    ~Matrix();
    int* operator[](int row);
    const int* operator[](int row) const;
    void display() const;
};

#endif
```

**matrix.cpp**
```cpp
#include "matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data = new int*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols];
        for (int j = 0; j < cols; j++) data[i][j] = 0;
    }
    cout << "Matrix " << rows << "x" << cols << " created" << endl;
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) delete[] data[i];
    delete[] data;
    cout << "Matrix destroyed" << endl;
}

int* Matrix::operator[](int row) { return data[row]; }
const int* Matrix::operator[](int row) const { return data[row]; }

void Matrix::display() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) cout << data[i][j] << "\t";
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
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            mat[i][j] = i * 4 + j + 1;
    mat.display();
    return 0;
}
```

### Example 3: Image Buffer (3D Array for RGB)

#### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class Image {
private:
    int width;
    int height;
    int*** pixels;  // [height][width][3] for RGB
    
public:
    Image(int w, int h) : width(w), height(h) {
        // Allocate 3D array
        pixels = new int**[height];
        for (int i = 0; i < height; i++) {
            pixels[i] = new int*[width];
            for (int j = 0; j < width; j++) {
                pixels[i][j] = new int[3]{0, 0, 0};
            }
        }
        cout << "Image " << width << "x" << height << " created" << endl;
    }
    
    ~Image() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                delete[] pixels[i][j];
            }
            delete[] pixels[i];
        }
        delete[] pixels;
        cout << "Image destroyed" << endl;
    }
    
    void setPixel(int x, int y, int r, int g, int b) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x][0] = r;
            pixels[y][x][1] = g;
            pixels[y][x][2] = b;
        }
    }
    
    void display() const {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cout << "(" << pixels[y][x][0] << ","
                     << pixels[y][x][1] << ","
                     << pixels[y][x][2] << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Image img(3, 2);
    
    img.setPixel(0, 0, 255, 0, 0);    // Red
    img.setPixel(1, 0, 0, 255, 0);    // Green
    img.setPixel(2, 0, 0, 0, 255);    // Blue
    img.setPixel(0, 1, 255, 255, 0);  // Yellow
    img.setPixel(1, 1, 0, 255, 255);  // Cyan
    img.setPixel(2, 1, 255, 0, 255);  // Magenta
    
    img.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**image.h**
```cpp
#ifndef IMAGE_H
#define IMAGE_H

class Image {
private:
    int width;
    int height;
    int*** pixels;
    
public:
    Image(int w, int h);
    ~Image();
    void setPixel(int x, int y, int r, int g, int b);
    void display() const;
};

#endif
```

**image.cpp**
```cpp
#include "image.h"
#include <iostream>
using namespace std;

Image::Image(int w, int h) : width(w), height(h) {
    pixels = new int**[height];
    for (int i = 0; i < height; i++) {
        pixels[i] = new int*[width];
        for (int j = 0; j < width; j++) {
            pixels[i][j] = new int[3]{0, 0, 0};
        }
    }
    cout << "Image " << width << "x" << height << " created" << endl;
}

Image::~Image() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) delete[] pixels[i][j];
        delete[] pixels[i];
    }
    delete[] pixels;
    cout << "Image destroyed" << endl;
}

void Image::setPixel(int x, int y, int r, int g, int b) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y][x][0] = r;
        pixels[y][x][1] = g;
        pixels[y][x][2] = b;
    }
}

void Image::display() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cout << "(" << pixels[y][x][0] << ","
                 << pixels[y][x][1] << ","
                 << pixels[y][x][2] << ") ";
        }
        cout << endl;
    }
}
```

**main.cpp**
```cpp
#include <iostream>
#include "image.h"
using namespace std;

int main() {
    Image img(3, 2);
    img.setPixel(0, 0, 255, 0, 0);
    img.display();
    return 0;
}
```

### Example 4: String Array (Array of C-Strings)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int count = 3;
    
    // Array of pointers to char
    char** strings = new char*[count];
    
    // Allocate and copy each string
    strings[0] = new char[6];
    strcpy(strings[0], "Hello");
    
    strings[1] = new char[6];
    strcpy(strings[1], "World");
    
    strings[2] = new char[7];
    strcpy(strings[2], "C++!!!");
    
    // Display
    for (int i = 0; i < count; i++) {
        cout << strings[i] << endl;
    }
    
    // Cleanup
    for (int i = 0; i < count; i++) {
        delete[] strings[i];
    }
    delete[] strings;
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Using delete instead of delete[] | Only first destructor called | Use delete[] for arrays |
| Using delete[] for single object | Undefined behavior | Use delete for single object |
| Forgetting nested array cleanup | Memory leak | Delete in reverse allocation order |
| Out-of-bounds access | Undefined behavior | Always check indices |
| Memory leak in 2D array | Lost memory | Delete all inner arrays first |

## Summary

- **new[]** allocates array, calls constructor for each element
- **delete[]** calls destructor for each element, deallocates memory
- **2D arrays** require nested allocation and deallocation
- **Deallocate in reverse order** of allocation
- **Single contiguous block** (rows*cols) is more cache-friendly
- Always use **delete[]** for arrays allocated with new[]
- **C++11** allows initializer lists with new[]{...}

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

int main() {
    int size = 5;
    
    // 1D array
    int* arr1D = new int[size];
    for (int i = 0; i < size; i++) arr1D[i] = i * 10;
    delete[] arr1D;
    
    // 2D array (array of pointers)
    int** arr2D = new int*[size];
    for (int i = 0; i < size; i++) {
        arr2D[i] = new int[size];
    }
    for (int i = 0; i < size; i++) delete[] arr2D[i];
    delete[] arr2D;
    
    return 0;
}
```

### Type 2: Multiple Files

**arrayutils.h**
```cpp
#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H

class ArrayUtils {
public:
    static int* create1D(int size);
    static void destroy1D(int* arr);
    static int** create2D(int rows, int cols);
    static void destroy2D(int** arr, int rows);
};

#endif
```

**arrayutils.cpp**
```cpp
#include "arrayutils.h"

int* ArrayUtils::create1D(int size) {
    return new int[size];
}

void ArrayUtils::destroy1D(int* arr) {
    delete[] arr;
}

int** ArrayUtils::create2D(int rows, int cols) {
    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }
    return arr;
}

void ArrayUtils::destroy2D(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}
```

**main.cpp**
```cpp
#include "arrayutils.h"

int main() {
    int* arr1D = ArrayUtils::create1D(10);
    ArrayUtils::destroy1D(arr1D);
    
    int** arr2D = ArrayUtils::create2D(3, 4);
    ArrayUtils::destroy2D(arr2D, 3);
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*