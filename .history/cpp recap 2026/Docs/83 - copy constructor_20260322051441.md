# 83 - Copy Constructor in C++

## What is a Copy Constructor?
A copy constructor is a special constructor that creates a new object as a copy of an existing object. It is called when a new object is initialized from another object of the same class.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    double gpa;
    
public:
    // Regular constructor
    Student(string n, int a, double g) : name(n), age(a), gpa(g) {
        cout << "Regular constructor called for " << name << endl;
    }
    
    // Copy constructor
    Student(const Student& other) {
        name = other.name;
        age = other.age;
        gpa = other.gpa;
        cout << "Copy constructor called for " << name << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << ", GPA: " << gpa << endl;
    }
};

int main() {
    Student s1("John", 20, 3.5);      // Regular constructor
    Student s2(s1);                    // Copy constructor
    Student s3 = s1;                   // Copy constructor
    Student s4 = Student(s1);          // Copy constructor
    
    cout << "\nOriginal: ";
    s1.display();
    
    cout << "Copy 1: ";
    s2.display();
    
    cout << "Copy 2: ";
    s3.display();
    
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
    string name;
    int age;
    double gpa;
    
public:
    Student(string n, int a, double g);
    Student(const Student& other);
    void display() const;
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student(string n, int a, double g) : name(n), age(a), gpa(g) {
    cout << "Regular constructor called for " << name << endl;
}

Student::Student(const Student& other) {
    name = other.name;
    age = other.age;
    gpa = other.gpa;
    cout << "Copy constructor called for " << name << endl;
}

void Student::display() const {
    cout << "Name: " << name << ", Age: " << age << ", GPA: " << gpa << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student s1("John", 20, 3.5);
    Student s2(s1);
    
    s1.display();
    s2.display();
    
    return 0;
}
```

## When Copy Constructor is Called

```cpp
#include <iostream>
#include <string>
using namespace std;

class Demo {
private:
    string name;
    
public:
    Demo(string n) : name(n) {
        cout << "Constructor: " << name << endl;
    }
    
    Demo(const Demo& other) : name(other.name + " (copy)") {
        cout << "Copy constructor: " << name << endl;
    }
    
    ~Demo() {
        cout << "Destructor: " << name << endl;
    }
    
    void display() const {
        cout << "Object: " << name << endl;
    }
};

Demo createObject() {
    Demo temp("Temp");
    return temp;  // Copy constructor may be called
}

void passByValue(Demo d) {
    d.display();  // Copy constructor called
}

int main() {
    cout << "--- Direct initialization ---" << endl;
    Demo obj1("Original");
    
    cout << "\n--- Copy initialization ---" << endl;
    Demo obj2 = obj1;      // Copy constructor
    
    cout << "\n--- Pass by value ---" << endl;
    passByValue(obj1);     // Copy constructor
    
    cout << "\n--- Return by value ---" << endl;
    Demo obj3 = createObject();  // Copy constructor (may be optimized)
    
    cout << "\n--- End of main ---" << endl;
    return 0;
}
```

## Shallow Copy vs Deep Copy

### Shallow Copy (Default - Problematic with Pointers)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class ShallowString {
private:
    char* str;
    
public:
    ShallowString(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
        cout << "Constructor: " << str << endl;
    }
    
    // Default copy constructor (shallow) - DANGEROUS!
    // ShallowString(const ShallowString& other) = default;
    
    ~ShallowString() {
        cout << "Destructor: " << str << endl;
        delete[] str;
    }
    
    void display() const {
        cout << str << endl;
    }
};

int main() {
    ShallowString s1("Hello");
    ShallowString s2 = s1;  // Shallow copy - both point to same memory!
    
    s1.display();
    s2.display();
    
    // When destructors run, double delete occurs! (Undefined behavior)
    return 0;
}
```

### Deep Copy (Correct Implementation)

#### Type 1: Single File
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class DeepString {
private:
    char* str;
    int length;
    
public:
    // Constructor
    DeepString(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
        cout << "Constructor: " << str << endl;
    }
    
    // Deep copy constructor
    DeepString(const DeepString& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
        cout << "Deep copy constructor: " << str << endl;
    }
    
    // Assignment operator
    DeepString& operator=(const DeepString& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
            cout << "Assignment operator: " << str << endl;
        }
        return *this;
    }
    
    void display() const {
        cout << str << " (addr: " << (void*)str << ")" << endl;
    }
    
    ~DeepString() {
        cout << "Destructor: " << str << endl;
        delete[] str;
    }
};

int main() {
    DeepString s1("Hello");
    DeepString s2 = s1;  // Deep copy - separate memory
    
    cout << "\ns1: ";
    s1.display();
    
    cout << "s2: ";
    s2.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**deepstring.h**
```cpp
#ifndef DEEPSTRING_H
#define DEEPSTRING_H

class DeepString {
private:
    char* str;
    int length;
    
public:
    DeepString(const char* s);
    DeepString(const DeepString& other);
    DeepString& operator=(const DeepString& other);
    void display() const;
    ~DeepString();
};

#endif
```

**deepstring.cpp**
```cpp
#include "deepstring.h"
#include <iostream>
#include <cstring>
using namespace std;

DeepString::DeepString(const char* s) {
    length = strlen(s);
    str = new char[length + 1];
    strcpy(str, s);
    cout << "Constructor: " << str << endl;
}

DeepString::DeepString(const DeepString& other) {
    length = other.length;
    str = new char[length + 1];
    strcpy(str, other.str);
    cout << "Deep copy constructor: " << str << endl;
}

DeepString& DeepString::operator=(const DeepString& other) {
    if (this != &other) {
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
        cout << "Assignment operator: " << str << endl;
    }
    return *this;
}

void DeepString::display() const {
    cout << str << " (addr: " << (void*)str << ")" << endl;
}

DeepString::~DeepString() {
    cout << "Destructor: " << str << endl;
    delete[] str;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "deepstring.h"
using namespace std;

int main() {
    DeepString s1("Hello");
    DeepString s2 = s1;
    
    s1.display();
    s2.display();
    
    return 0;
}
```

## Practical Examples

### Example 1: Array Class with Deep Copy

#### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class IntArray {
private:
    int* data;
    int size;
    
public:
    // Constructor
    IntArray(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
        cout << "Array created (size " << size << ")" << endl;
    }
    
    // Deep copy constructor
    IntArray(const IntArray& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Deep copy constructor (size " << size << ")" << endl;
    }
    
    // Assignment operator
    IntArray& operator=(const IntArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
            cout << "Assignment operator (size " << size << ")" << endl;
        }
        return *this;
    }
    
    int& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        static int dummy = -1;
        return dummy;
    }
    
    int getSize() const { return size; }
    
    void display() const {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    
    ~IntArray() {
        cout << "Array destroyed (size " << size << ")" << endl;
        delete[] data;
    }
};

int main() {
    IntArray arr1(5);
    for (int i = 0; i < 5; i++) {
        arr1[i] = i * 10;
    }
    
    cout << "arr1: ";
    arr1.display();
    
    IntArray arr2 = arr1;  // Deep copy
    cout << "arr2: ";
    arr2.display();
    
    arr1[0] = 999;
    cout << "\nAfter modifying arr1[0]:" << endl;
    cout << "arr1: ";
    arr1.display();
    cout << "arr2: ";
    arr2.display();  // Unchanged - deep copy
    
    return 0;
}
```

#### Type 2: Multiple Files

**intarray.h**
```cpp
#ifndef INTARRAY_H
#define INTARRAY_H

class IntArray {
private:
    int* data;
    int size;
    
public:
    IntArray(int s);
    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);
    int& operator[](int index);
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
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
    cout << "Array created (size " << size << ")" << endl;
}

IntArray::IntArray(const IntArray& other) : size(other.size) {
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
    cout << "Deep copy constructor (size " << size << ")" << endl;
}

IntArray& IntArray::operator=(const IntArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Assignment operator (size " << size << ")" << endl;
    }
    return *this;
}

int& IntArray::operator[](int index) {
    if (index >= 0 && index < size) {
        return data[index];
    }
    static int dummy = -1;
    return dummy;
}

int IntArray::getSize() const { return size; }

void IntArray::display() const {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

IntArray::~IntArray() {
    cout << "Array destroyed (size " << size << ")" << endl;
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
    for (int i = 0; i < 5; i++) {
        arr1[i] = i * 10;
    }
    
    IntArray arr2 = arr1;
    
    cout << "arr1: ";
    arr1.display();
    cout << "arr2: ";
    arr2.display();
    
    return 0;
}
```

### Example 2: Student Records with Copy Constructor

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class StudentRecord {
private:
    int rollNumber;
    string name;
    double* grades;
    int gradeCount;
    
public:
    // Constructor
    StudentRecord(int roll, string n, int count, const double* gradeArray) 
        : rollNumber(roll), name(n), gradeCount(count) {
        grades = new double[gradeCount];
        for (int i = 0; i < gradeCount; i++) {
            grades[i] = gradeArray[i];
        }
        cout << "Constructor for " << name << endl;
    }
    
    // Deep copy constructor
    StudentRecord(const StudentRecord& other) 
        : rollNumber(other.rollNumber), name(other.name), gradeCount(other.gradeCount) {
        grades = new double[gradeCount];
        for (int i = 0; i < gradeCount; i++) {
            grades[i] = other.grades[i];
        }
        cout << "Copy constructor for " << name << endl;
    }
    
    double calculateAverage() const {
        if (gradeCount == 0) return 0;
        double sum = 0;
        for (int i = 0; i < gradeCount; i++) {
            sum += grades[i];
        }
        return sum / gradeCount;
    }
    
    void display() const {
        cout << "Roll: " << rollNumber << ", Name: " << name << endl;
        cout << "Grades: ";
        for (int i = 0; i < gradeCount; i++) {
            cout << grades[i] << " ";
        }
        cout << "\nAverage: " << calculateAverage() << endl;
    }
    
    ~StudentRecord() {
        cout << "Destructor for " << name << endl;
        delete[] grades;
    }
};

int main() {
    double grades1[] = {85.5, 90.0, 78.5, 92.0};
    StudentRecord s1(101, "John", 4, grades1);
    
    StudentRecord s2 = s1;  // Copy constructor
    
    cout << "\nOriginal Student:" << endl;
    s1.display();
    
    cout << "\nCopied Student:" << endl;
    s2.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**studentrecord.h**
```cpp
#ifndef STUDENTRECORD_H
#define STUDENTRECORD_H

#include <string>
using namespace std;

class StudentRecord {
private:
    int rollNumber;
    string name;
    double* grades;
    int gradeCount;
    
public:
    StudentRecord(int roll, string n, int count, const double* gradeArray);
    StudentRecord(const StudentRecord& other);
    double calculateAverage() const;
    void display() const;
    ~StudentRecord();
};

#endif
```

**studentrecord.cpp**
```cpp
#include "studentrecord.h"
#include <iostream>
using namespace std;

StudentRecord::StudentRecord(int roll, string n, int count, const double* gradeArray) 
    : rollNumber(roll), name(n), gradeCount(count) {
    grades = new double[gradeCount];
    for (int i = 0; i < gradeCount; i++) {
        grades[i] = gradeArray[i];
    }
    cout << "Constructor for " << name << endl;
}

StudentRecord::StudentRecord(const StudentRecord& other) 
    : rollNumber(other.rollNumber), name(other.name), gradeCount(other.gradeCount) {
    grades = new double[gradeCount];
    for (int i = 0; i < gradeCount; i++) {
        grades[i] = other.grades[i];
    }
    cout << "Copy constructor for " << name << endl;
}

double StudentRecord::calculateAverage() const {
    if (gradeCount == 0) return 0;
    double sum = 0;
    for (int i = 0; i < gradeCount; i++) {
        sum += grades[i];
    }
    return sum / gradeCount;
}

void StudentRecord::display() const {
    cout << "Roll: " << rollNumber << ", Name: " << name << endl;
    cout << "Grades: ";
    for (int i = 0; i < gradeCount; i++) {
        cout << grades[i] << " ";
    }
    cout << "\nAverage: " << calculateAverage() << endl;
}

StudentRecord::~StudentRecord() {
    cout << "Destructor for " << name << endl;
    delete[] grades;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "studentrecord.h"
using namespace std;

int main() {
    double grades[] = {85.5, 90.0, 78.5, 92.0};
    StudentRecord s1(101, "John", 4, grades);
    StudentRecord s2 = s1;
    
    s1.display();
    s2.display();
    
    return 0;
}
```

### Example 3: Preventing Copying (Deleted Copy Constructor)

```cpp
#include <iostream>
#include <string>
using namespace std;

class UniqueResource {
private:
    string name;
    int* resource;
    
public:
    UniqueResource(string n) : name(n) {
        resource = new int(42);
        cout << "Resource created: " << name << endl;
    }
    
    // Delete copy constructor - prevent copying
    UniqueResource(const UniqueResource& other) = delete;
    
    // Delete assignment operator
    UniqueResource& operator=(const UniqueResource& other) = delete;
    
    void display() const {
        cout << name << ": " << *resource << endl;
    }
    
    ~UniqueResource() {
        delete resource;
        cout << "Resource destroyed: " << name << endl;
    }
};

int main() {
    UniqueResource r1("First");
    // UniqueResource r2 = r1;  // Error! Copy constructor deleted
    
    r1.display();
    
    return 0;
}
```

## Rule of Three (or Five)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class RuleOfThree {
private:
    char* data;
    
public:
    // Constructor
    RuleOfThree(const char* s) {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
        cout << "Constructor: " << data << endl;
    }
    
    // Copy constructor (Rule of Three)
    RuleOfThree(const RuleOfThree& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        cout << "Copy constructor: " << data << endl;
    }
    
    // Assignment operator (Rule of Three)
    RuleOfThree& operator=(const RuleOfThree& other) {
        if (this != &other) {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
            cout << "Assignment operator: " << data << endl;
        }
        return *this;
    }
    
    // Destructor (Rule of Three)
    ~RuleOfThree() {
        cout << "Destructor: " << data << endl;
        delete[] data;
    }
    
    void display() const {
        cout << data << endl;
    }
};

int main() {
    RuleOfThree r1("Hello");
    RuleOfThree r2 = r1;      // Copy constructor
    RuleOfThree r3("World");
    r3 = r1;                   // Assignment operator
    
    r1.display();
    r2.display();
    r3.display();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Default copy constructor with pointers | Double delete, memory corruption | Implement deep copy |
| Forgetting to copy all members | Partial copy, inconsistent state | Copy all members |
| Not handling self-assignment | Memory leak, corruption | Check `this != &other` |
| Copying without allocating memory | Crash, undefined behavior | Allocate new memory |
| Not deleting old memory | Memory leak | Delete before reassigning |

## Summary

- **Copy constructor** creates new object as copy of existing
- Called during **initialization**, not assignment
- **Shallow copy** copies pointers only (dangerous)
- **Deep copy** creates separate copies of dynamic memory
- **Rule of Three**: If you need one of (destructor, copy constructor, assignment operator), you need all three
- **Deleted copy constructor** prevents copying
- Essential for classes with **dynamic memory**

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private:
    char* str;
    int len;
    
public:
    // Constructor
    MyString(const char* s) {
        len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
    }
    
    // Copy constructor
    MyString(const MyString& other) {
        len = other.len;
        str = new char[len + 1];
        strcpy(str, other.str);
        cout << "Copy constructor: " << str << endl;
    }
    
    void display() const {
        cout << str << " (addr: " << (void*)str << ")" << endl;
    }
    
    ~MyString() {
        delete[] str;
    }
};

int main() {
    MyString s1("Hello");
    MyString s2 = s1;
    
    s1.display();
    s2.display();
    
    return 0;
}
```

### Type 2: Multiple Files

**mystring.h**
```cpp
#ifndef MYSTRING_H
#define MYSTRING_H

class MyString {
private:
    char* str;
    int len;
    
public:
    MyString(const char* s);
    MyString(const MyString& other);
    void display() const;
    ~MyString();
};

#endif
```

**mystring.cpp**
```cpp
#include "mystring.h"
#include <iostream>
#include <cstring>
using namespace std;

MyString::MyString(const char* s) {
    len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
}

MyString::MyString(const MyString& other) {
    len = other.len;
    str = new char[len + 1];
    strcpy(str, other.str);
    cout << "Copy constructor: " << str << endl;
}

void MyString::display() const {
    cout << str << " (addr: " << (void*)str << ")" << endl;
}

MyString::~MyString() {
    delete[] str;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "mystring.h"
using namespace std;

int main() {
    MyString s1("Hello");
    MyString s2 = s1;
    
    s1.display();
    s2.display();
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*