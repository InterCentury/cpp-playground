# 80 - this Pointer in C++

## What is the this Pointer?
`this` is a special pointer that holds the address of the current object. It is implicitly passed to all non-static member functions and can be used to refer to the calling object.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    
public:
    Student(string name, int age) {
        // Using this to distinguish parameter from member
        this->name = name;
        this->age = age;
    }
    
    void display() {
        cout << "Object address: " << this << endl;
        cout << "Name: " << this->name << ", Age: " << this->age << endl;
    }
    
    // Returning this for method chaining
    Student& setName(string name) {
        this->name = name;
        return *this;
    }
    
    Student& setAge(int age) {
        this->age = age;
        return *this;
    }
    
    void show() {
        cout << name << " (" << age << ")" << endl;
    }
};

int main() {
    Student s1("John", 20);
    Student s2("Alice", 22);
    
    s1.display();
    s2.display();
    
    // Method chaining
    s1.setName("Jonathan").setAge(25);
    s1.show();
    
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
    
public:
    Student(string name, int age);
    void display() const;
    Student& setName(string name);
    Student& setAge(int age);
    void show() const;
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student(string name, int age) {
    this->name = name;
    this->age = age;
}

void Student::display() const {
    cout << "Object address: " << this << endl;
    cout << "Name: " << this->name << ", Age: " << this->age << endl;
}

Student& Student::setName(string name) {
    this->name = name;
    return *this;
}

Student& Student::setAge(int age) {
    this->age = age;
    return *this;
}

void Student::show() const {
    cout << name << " (" << age << ")" << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student s1("John", 20);
    s1.display();
    s1.setName("Jonathan").setAge(25);
    s1.show();
    return 0;
}
```

## Key Uses of this Pointer

### 1. Resolving Name Conflicts

```cpp
#include <iostream>
using namespace std;

class Employee {
private:
    string name;
    double salary;
    
public:
    // Without this - parameter shadows member
    Employee(string n, double s) {
        name = n;      // OK - different name
        salary = s;    // OK - different name
    }
    
    // With this - same names, but resolved
    Employee(string name, double salary) {
        this->name = name;        // this->name is member
        this->salary = salary;    // this->salary is member
    }
    
    void display() {
        cout << name << ": $" << salary << endl;
    }
};

int main() {
    Employee e1("John", 50000);
    e1.display();
    return 0;
}
```

### 2. Method Chaining (Fluent Interface)

```cpp
#include <iostream>
#include <string>
using namespace std;

class Calculator {
private:
    double value;
    
public:
    Calculator() : value(0) {}
    
    Calculator& add(double x) {
        value += x;
        return *this;
    }
    
    Calculator& subtract(double x) {
        value -= x;
        return *this;
    }
    
    Calculator& multiply(double x) {
        value *= x;
        return *this;
    }
    
    Calculator& divide(double x) {
        if (x != 0) value /= x;
        return *this;
    }
    
    double getValue() const {
        return value;
    }
    
    void display() const {
        cout << "Result: " << value << endl;
    }
};

int main() {
    Calculator calc;
    
    // Method chaining using this
    calc.add(10).subtract(3).multiply(2).divide(7);
    calc.display();
    
    // Equivalent to:
    calc.add(10);
    calc.subtract(3);
    calc.multiply(2);
    calc.divide(7);
    
    return 0;
}
```

### 3. Returning Reference to Current Object

```cpp
#include <iostream>
#include <string>
using namespace std;

class StringBuilder {
private:
    string content;
    
public:
    StringBuilder& append(const string& text) {
        content += text;
        return *this;
    }
    
    StringBuilder& appendLine(const string& text) {
        content += text + "\n";
        return *this;
    }
    
    StringBuilder& clear() {
        content.clear();
        return *this;
    }
    
    string toString() const {
        return content;
    }
    
    void display() const {
        cout << content;
    }
};

int main() {
    StringBuilder sb;
    
    sb.append("Hello").appendLine(" World")
      .append("This is ").append("C++").appendLine(" programming")
      .append("Method chaining is ").appendLine("powerful!");
    
    sb.display();
    
    return 0;
}
```

### 4. Comparing Objects

```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    
public:
    Person(string n, int a) : name(n), age(a) {}
    
    bool isOlderThan(const Person& other) const {
        return this->age > other.age;
    }
    
    bool isSameAge(const Person& other) const {
        return this->age == other.age;
    }
    
    void compare(const Person& other) const {
        cout << name << " vs " << other.name << ":" << endl;
        if (this->isOlderThan(other)) {
            cout << "  " << name << " is older" << endl;
        } else if (other.isOlderThan(*this)) {
            cout << "  " << other.name << " is older" << endl;
        } else {
            cout << "  Same age" << endl;
        }
    }
    
    void display() const {
        cout << name << " (" << age << ")" << endl;
    }
};

int main() {
    Person p1("John", 30);
    Person p2("Alice", 25);
    Person p3("Bob", 30);
    
    p1.compare(p2);
    p1.compare(p3);
    
    return 0;
}
```

## Practical Examples

### Example 1: Matrix Class with Method Chaining

#### Type 1: Single File
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
    
    Matrix& set(int r, int c, int value) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            data[r][c] = value;
        }
        return *this;
    }
    
    Matrix& add(const Matrix& other) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }
    
    Matrix& multiply(int scalar) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }
    
    Matrix& fill(int value) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = value;
            }
        }
        return *this;
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
    Matrix m1(3, 3);
    Matrix m2(3, 3);
    
    m1.fill(2);
    m2.fill(3);
    
    cout << "Matrix 1:" << endl;
    m1.display();
    
    cout << "\nMatrix 2:" << endl;
    m2.display();
    
    // Method chaining
    m1.add(m2).multiply(2);
    
    cout << "\nAfter (m1 + m2) * 2:" << endl;
    m1.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**matrix.h**
```cpp
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int rows, cols;
    
public:
    Matrix(int r, int c);
    Matrix& set(int r, int c, int value);
    Matrix& add(const Matrix& other);
    Matrix& multiply(int scalar);
    Matrix& fill(int value);
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
    data.resize(rows, vector<int>(cols, 0));
}

Matrix& Matrix::set(int r, int c, int value) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        data[r][c] = value;
    }
    return *this;
}

Matrix& Matrix::add(const Matrix& other) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] += other.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::multiply(int scalar) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] *= scalar;
        }
    }
    return *this;
}

Matrix& Matrix::fill(int value) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = value;
        }
    }
    return *this;
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
    Matrix m1(3, 3);
    Matrix m2(3, 3);
    
    m1.fill(2);
    m2.fill(3);
    
    cout << "Matrix 1:" << endl;
    m1.display();
    
    cout << "\nMatrix 2:" << endl;
    m2.display();
    
    m1.add(m2).multiply(2);
    
    cout << "\nAfter (m1 + m2) * 2:" << endl;
    m1.display();
    
    return 0;
}
```

### Example 2: Assignment Operator Overloading

#### Type 1: Single File
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* str;
    int length;
    
public:
    String(const char* s = "") {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }
    
    // Copy constructor
    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }
    
    // Assignment operator with this pointer
    String& operator=(const String& other) {
        if (this != &other) {  // Check for self-assignment
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        return *this;  // Return reference to current object
    }
    
    // Compound assignment
    String& operator+=(const String& other) {
        char* newStr = new char[length + other.length + 1];
        strcpy(newStr, str);
        strcat(newStr, other.str);
        delete[] str;
        str = newStr;
        length += other.length;
        return *this;
    }
    
    void display() const {
        cout << str << endl;
    }
    
    ~String() {
        delete[] str;
    }
};

int main() {
    String s1("Hello");
    String s2(" World");
    String s3;
    
    cout << "s1: "; s1.display();
    cout << "s2: "; s2.display();
    
    s3 = s1;  // Copy assignment
    cout << "s3 = s1: "; s3.display();
    
    s1 += s2;  // Compound assignment
    cout << "s1 += s2: "; s1.display();
    
    s3 = s1;  // Assignment
    cout << "s3 = s1: "; s3.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**string.h**
```cpp
#ifndef STRING_H
#define STRING_H

class String {
private:
    char* str;
    int length;
    
public:
    String(const char* s = "");
    String(const String& other);
    String& operator=(const String& other);
    String& operator+=(const String& other);
    void display() const;
    ~String();
};

#endif
```

**string.cpp**
```cpp
#include "string.h"
#include <iostream>
#include <cstring>
using namespace std;

String::String(const char* s) {
    length = strlen(s);
    str = new char[length + 1];
    strcpy(str, s);
}

String::String(const String& other) {
    length = other.length;
    str = new char[length + 1];
    strcpy(str, other.str);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }
    return *this;
}

String& String::operator+=(const String& other) {
    char* newStr = new char[length + other.length + 1];
    strcpy(newStr, str);
    strcat(newStr, other.str);
    delete[] str;
    str = newStr;
    length += other.length;
    return *this;
}

void String::display() const {
    cout << str << endl;
}

String::~String() {
    delete[] str;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "string.h"
using namespace std;

int main() {
    String s1("Hello");
    String s2(" World");
    String s3;
    
    s3 = s1;
    s3.display();
    
    s1 += s2;
    s1.display();
    
    return 0;
}
```

### Example 3: Builder Pattern with this

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Email {
private:
    string from;
    vector<string> to;
    string subject;
    string body;
    
public:
    Email() {}
    
    Email& setFrom(const string& sender) {
        this->from = sender;
        return *this;
    }
    
    Email& addTo(const string& recipient) {
        this->to.push_back(recipient);
        return *this;
    }
    
    Email& setSubject(const string& subj) {
        this->subject = subj;
        return *this;
    }
    
    Email& setBody(const string& content) {
        this->body = content;
        return *this;
    }
    
    void send() const {
        cout << "Sending email..." << endl;
        cout << "From: " << from << endl;
        cout << "To: ";
        for (size_t i = 0; i < to.size(); i++) {
            cout << to[i];
            if (i < to.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "Subject: " << subject << endl;
        cout << "Body: " << body << endl;
        cout << "Email sent!" << endl;
    }
};

int main() {
    Email email;
    
    email.setFrom("admin@example.com")
         .addTo("user1@example.com")
         .addTo("user2@example.com")
         .setSubject("Welcome!")
         .setBody("Thank you for joining our service.");
    
    email.send();
    
    return 0;
}
```

#### Type 2: Multiple Files

**email.h**
```cpp
#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include <vector>
using namespace std;

class Email {
private:
    string from;
    vector<string> to;
    string subject;
    string body;
    
public:
    Email();
    Email& setFrom(const string& sender);
    Email& addTo(const string& recipient);
    Email& setSubject(const string& subj);
    Email& setBody(const string& content);
    void send() const;
};

#endif
```

**email.cpp**
```cpp
#include "email.h"
#include <iostream>
using namespace std;

Email::Email() {}

Email& Email::setFrom(const string& sender) {
    this->from = sender;
    return *this;
}

Email& Email::addTo(const string& recipient) {
    this->to.push_back(recipient);
    return *this;
}

Email& Email::setSubject(const string& subj) {
    this->subject = subj;
    return *this;
}

Email& Email::setBody(const string& content) {
    this->body = content;
    return *this;
}

void Email::send() const {
    cout << "Sending email..." << endl;
    cout << "From: " << from << endl;
    cout << "To: ";
    for (size_t i = 0; i < to.size(); i++) {
        cout << to[i];
        if (i < to.size() - 1) cout << ", ";
    }
    cout << endl;
    cout << "Subject: " << subject << endl;
    cout << "Body: " << body << endl;
    cout << "Email sent!" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "email.h"
using namespace std;

int main() {
    Email email;
    
    email.setFrom("admin@example.com")
         .addTo("user1@example.com")
         .addTo("user2@example.com")
         .setSubject("Welcome!")
         .setBody("Thank you for joining our service.");
    
    email.send();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting to dereference | Using `this` without `->` | `this->member` or `(*this).member` |
| Returning by value instead of reference | Broken chaining | Return `*this` by reference |
| Not checking self-assignment | Memory corruption | `if (this != &other)` |
| Using `this` in static functions | Compilation error | `this` only in non-static |
| Returning `this` instead of `*this` | Type mismatch | `return *this` for reference |

## Summary

- **this** pointer points to current object
- Used to **resolve name conflicts** between parameters and members
- Enables **method chaining** (fluent interface)
- Required for **operator overloading** returning reference
- Used in **assignment operators** to detect self-assignment
- Only available in **non-static member functions**
- Can be used to **compare objects** within member functions
- **`*this`** returns reference to current object

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class MyClass {
private:
    int value;
    
public:
    MyClass(int value) {
        this->value = value;  // Resolve name conflict
    }
    
    MyClass& setValue(int value) {
        this->value = value;  // Use this
        return *this;         // Return reference for chaining
    }
    
    int getValue() const {
        return this->value;   // Explicit use of this
    }
    
    void display() const {
        cout << "Object: " << this << ", Value: " << this->value << endl;
    }
};

int main() {
    MyClass obj(42);
    obj.display();
    
    obj.setValue(100).setValue(200);
    obj.display();
    
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
    int value;
    
public:
    MyClass(int value);
    MyClass& setValue(int value);
    int getValue() const;
    void display() const;
};

#endif
```

**myclass.cpp**
```cpp
#include "myclass.h"
#include <iostream>
using namespace std;

MyClass::MyClass(int value) {
    this->value = value;
}

MyClass& MyClass::setValue(int value) {
    this->value = value;
    return *this;
}

int MyClass::getValue() const {
    return this->value;
}

void MyClass::display() const {
    cout << "Object: " << this << ", Value: " << this->value << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "myclass.h"
using namespace std;

int main() {
    MyClass obj(42);
    obj.display();
    obj.setValue(100).setValue(200);
    obj.display();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*