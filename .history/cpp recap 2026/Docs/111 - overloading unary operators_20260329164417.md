# 111 - Overloading Unary Operators in C++

## What are Unary Operators?
Unary operators operate on a single operand. Common unary operators include increment (++), decrement (--), unary minus (-), logical NOT (!), and address-of (&). Overloading them allows user-defined types to support these intuitive operations.

## Type 1: Single File Implementation

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
    
    friend ostream& operator<<(ostream& os, const Counter& c) {
        os << c.value;
        return os;
    }
};

int main() {
    Counter c(5);
    
    cout << "Initial: c = " << c << endl;
    cout << "Prefix ++c: " << ++c << endl;
    cout << "After prefix: c = " << c << endl;
    cout << "Postfix c++: " << c++ << endl;
    cout << "After postfix: c = " << c << endl;
    cout << "Prefix --c: " << --c << endl;
    cout << "Postfix c--: " << c-- << endl;
    cout << "After postfix: c = " << c << endl;
    cout << "-c = " << -c << endl;
    cout << "!c = " << !c << endl;
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### counter.h
```cpp
#ifndef COUNTER_H
#define COUNTER_H

#include <iostream>
using namespace std;

class Counter {
private:
    int value;
    
public:
    Counter(int v = 0);
    
    Counter& operator++();
    Counter operator++(int);
    Counter& operator--();
    Counter operator--(int);
    Counter operator-() const;
    bool operator!() const;
    int getValue() const;
    
    friend ostream& operator<<(ostream& os, const Counter& c);
};

#endif
```

### counter.cpp
```cpp
#include "counter.h"
#include <iostream>
using namespace std;

Counter::Counter(int v) : value(v) {}

Counter& Counter::operator++() {
    ++value;
    return *this;
}

Counter Counter::operator++(int) {
    Counter temp = *this;
    ++value;
    return temp;
}

Counter& Counter::operator--() {
    --value;
    return *this;
}

Counter Counter::operator--(int) {
    Counter temp = *this;
    --value;
    return temp;
}

Counter Counter::operator-() const {
    return Counter(-value);
}

bool Counter::operator!() const {
    return value == 0;
}

int Counter::getValue() const { return value; }

ostream& operator<<(ostream& os, const Counter& c) {
    os << c.value;
    return os;
}
```

### main.cpp
```cpp
#include <iostream>
#include "counter.h"
using namespace std;

int main() {
    Counter c(5);
    cout << ++c << endl;
    cout << c++ << endl;
    return 0;
}
```

## Prefix vs Postfix Implementation

```cpp
#include <iostream>
using namespace std;

class Number {
private:
    int value;
    
public:
    Number(int v = 0) : value(v) {}
    
    // Prefix: increment then return reference
    Number& operator++() {
        ++value;
        cout << "Prefix operator called" << endl;
        return *this;
    }
    
    // Postfix: return copy then increment
    Number operator++(int) {
        cout << "Postfix operator called" << endl;
        Number temp = *this;
        ++value;
        return temp;
    }
    
    int getValue() const { return value; }
    
    friend ostream& operator<<(ostream& os, const Number& n) {
        os << n.value;
        return os;
    }
};

int main() {
    Number n(5);
    
    cout << "n = " << n << endl;
    cout << "++n = " << ++n << endl;
    cout << "After ++n, n = " << n << endl;
    
    cout << "\nn = " << n << endl;
    cout << "n++ = " << n++ << endl;
    cout << "After n++, n = " << n << endl;
    
    return 0;
}
```

## Unary Operators for Different Types

### Vector Class with Unary Operators

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Vector {
private:
    double x, y, z;
    
public:
    Vector(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    // Unary minus - negates all components
    Vector operator-() const {
        return Vector(-x, -y, -z);
    }
    
    // Logical NOT - checks if vector is zero
    bool operator!() const {
        return x == 0 && y == 0 && z == 0;
    }
    
    // Address-of - returns pointer (rarely overloaded)
    Vector* operator&() {
        return this;
    }
    
    double magnitude() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    friend ostream& operator<<(ostream& os, const Vector& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

int main() {
    Vector v1(1, 2, 3);
    Vector v2(0, 0, 0);
    
    cout << "v1 = " << v1 << endl;
    cout << "-v1 = " << -v1 << endl;
    cout << "!v1 = " << !v1 << endl;
    cout << "!v2 = " << !v2 << endl;
    
    Vector* ptr = &v1;
    cout << "Address of v1: " << ptr << endl;
    
    return 0;
}
```

### Complex Class with Unary Operators

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
    
    // Unary minus
    Complex operator-() const {
        return Complex(-real, -imag);
    }
    
    // Logical NOT - checks if complex number is zero
    bool operator!() const {
        return real == 0 && imag == 0;
    }
    
    // Conjugate (using unary ~)
    Complex operator~() const {
        return Complex(real, -imag);
    }
    
    double magnitude() const {
        return sqrt(real*real + imag*imag);
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
    Complex c2(0, 0);
    
    cout << "c1 = " << c1 << endl;
    cout << "-c1 = " << -c1 << endl;
    cout << "~c1 = " << ~c1 << endl;
    cout << "!c1 = " << !c1 << endl;
    cout << "!c2 = " << !c2 << endl;
    cout << "|c1| = " << c1.magnitude() << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Time Class with Increment/Decrement

#### Type 1: Single File
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;
    
    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours >= 24) {
            hours %= 24;
        }
    }
    
public:
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        normalize();
    }
    
    // Prefix increment (add one second)
    Time& operator++() {
        ++seconds;
        normalize();
        return *this;
    }
    
    // Postfix increment
    Time operator++(int) {
        Time temp = *this;
        ++seconds;
        normalize();
        return temp;
    }
    
    // Prefix decrement (subtract one second)
    Time& operator--() {
        --seconds;
        if (seconds < 0) {
            seconds += 60;
            --minutes;
            if (minutes < 0) {
                minutes += 60;
                --hours;
                if (hours < 0) hours += 24;
            }
        }
        return *this;
    }
    
    // Postfix decrement
    Time operator--(int) {
        Time temp = *this;
        --*this;
        return temp;
    }
    
    // Unary plus (returns copy)
    Time operator+() const {
        return *this;
    }
    
    // Unary minus (not typical for time, but for demonstration)
    Time operator-() const {
        return Time(23 - hours, 59 - minutes, 59 - seconds);
    }
    
    bool operator!() const {
        return hours == 0 && minutes == 0 && seconds == 0;
    }
    
    friend ostream& operator<<(ostream& os, const Time& t) {
        os << setfill('0') << setw(2) << t.hours << ":"
           << setw(2) << t.minutes << ":"
           << setw(2) << t.seconds;
        return os;
    }
};

int main() {
    Time t(1, 30, 45);
    
    cout << "Initial: t = " << t << endl;
    cout << "++t = " << ++t << endl;
    cout << "t++ = " << t++ << endl;
    cout << "After t++: t = " << t << endl;
    cout << "--t = " << --t << endl;
    cout << "t-- = " << t-- << endl;
    cout << "After t--: t = " << t << endl;
    cout << "-t = " << -t << endl;
    cout << "!t = " << !t << endl;
    
    Time midnight;
    cout << "midnight = " << midnight << endl;
    cout << "!midnight = " << !midnight << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**time.h**
```cpp
#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;
    
    void normalize();
    
public:
    Time(int h = 0, int m = 0, int s = 0);
    
    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);
    Time operator+() const;
    Time operator-() const;
    bool operator!() const;
    
    friend ostream& operator<<(ostream& os, const Time& t);
};

#endif
```

**time.cpp**
```cpp
#include "time.h"
using namespace std;

void Time::normalize() {
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds %= 60;
    }
    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    }
    if (hours >= 24) {
        hours %= 24;
    }
}

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
    normalize();
}

Time& Time::operator++() {
    ++seconds;
    normalize();
    return *this;
}

Time Time::operator++(int) {
    Time temp = *this;
    ++seconds;
    normalize();
    return temp;
}

Time& Time::operator--() {
    --seconds;
    if (seconds < 0) {
        seconds += 60;
        --minutes;
        if (minutes < 0) {
            minutes += 60;
            --hours;
            if (hours < 0) hours += 24;
        }
    }
    return *this;
}

Time Time::operator--(int) {
    Time temp = *this;
    --*this;
    return temp;
}

Time Time::operator+() const {
    return *this;
}

Time Time::operator-() const {
    return Time(23 - hours, 59 - minutes, 59 - seconds);
}

bool Time::operator!() const {
    return hours == 0 && minutes == 0 && seconds == 0;
}

ostream& operator<<(ostream& os, const Time& t) {
    os << setfill('0') << setw(2) << t.hours << ":"
       << setw(2) << t.minutes << ":"
       << setw(2) << t.seconds;
    return os;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "time.h"
using namespace std;

int main() {
    Time t(1, 30, 45);
    cout << ++t << endl;
    cout << t++ << endl;
    return 0;
}
```

### Example 2: Smart Pointer with Dereference Operators

#### Type 1: Single File
```cpp
#include <iostream>
#include <memory>
using namespace std;

class SmartPointer {
private:
    int* ptr;
    
public:
    SmartPointer(int* p = nullptr) : ptr(p) {}
    
    ~SmartPointer() {
        delete ptr;
    }
    
    // Dereference operator
    int& operator*() {
        return *ptr;
    }
    
    const int& operator*() const {
        return *ptr;
    }
    
    // Arrow operator
    int* operator->() {
        return ptr;
    }
    
    const int* operator->() const {
        return ptr;
    }
    
    // Conversion to bool
    operator bool() const {
        return ptr != nullptr;
    }
    
    // Logical NOT
    bool operator!() const {
        return ptr == nullptr;
    }
};

int main() {
    SmartPointer sp(new int(42));
    
    cout << "*sp = " << *sp << endl;
    *sp = 100;
    cout << "*sp = " << *sp << endl;
    
    if (sp) {
        cout << "Pointer is valid" << endl;
    }
    
    SmartPointer empty;
    if (!empty) {
        cout << "Empty pointer is null" << endl;
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**smartpointer.h**
```cpp
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

class SmartPointer {
private:
    int* ptr;
    
public:
    SmartPointer(int* p = nullptr);
    ~SmartPointer();
    
    int& operator*();
    const int& operator*() const;
    int* operator->();
    const int* operator->() const;
    operator bool() const;
    bool operator!() const;
};

#endif
```

**smartpointer.cpp**
```cpp
#include "smartpointer.h"

SmartPointer::SmartPointer(int* p) : ptr(p) {}

SmartPointer::~SmartPointer() {
    delete ptr;
}

int& SmartPointer::operator*() {
    return *ptr;
}

const int& SmartPointer::operator*() const {
    return *ptr;
}

int* SmartPointer::operator->() {
    return ptr;
}

const int* SmartPointer::operator->() const {
    return ptr;
}

SmartPointer::operator bool() const {
    return ptr != nullptr;
}

bool SmartPointer::operator!() const {
    return ptr == nullptr;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "smartpointer.h"
using namespace std;

int main() {
    SmartPointer sp(new int(42));
    cout << *sp << endl;
    return 0;
}
```

### Example 3: String Class with Unary Operators

#### Type 1: Single File
```cpp
#include <iostream>
#include <cstring>
#include <cctype>
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
    
    // Unary plus - returns copy
    MyString operator+() const {
        return *this;
    }
    
    // Logical NOT - checks if string is empty
    bool operator!() const {
        return length == 0;
    }
    
    // Unary ~ - convert to uppercase
    MyString operator~() const {
        MyString result;
        delete[] result.data;
        result.length = length;
        result.data = new char[length + 1];
        for (int i = 0; i < length; i++) {
            result.data[i] = toupper(data[i]);
        }
        result.data[length] = '\0';
        return result;
    }
    
    int getLength() const { return length; }
    
    friend ostream& operator<<(ostream& os, const MyString& s) {
        os << s.data;
        return os;
    }
};

int main() {
    MyString s1("Hello World");
    MyString s2("");
    
    cout << "s1 = " << s1 << endl;
    cout << "+s1 = " << +s1 << endl;
    cout << "~s1 = " << ~s1 << endl;
    cout << "!s1 = " << !s1 << endl;
    cout << "!s2 = " << !s2 << endl;
    
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
    
    MyString operator+() const;
    bool operator!() const;
    MyString operator~() const;
    int getLength() const;
    
    friend ostream& operator<<(ostream& os, const MyString& s);
};

#endif
```

**mystring.cpp**
```cpp
#include "mystring.h"
#include <cstring>
#include <cctype>
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

MyString MyString::operator+() const {
    return *this;
}

bool MyString::operator!() const {
    return length == 0;
}

MyString MyString::operator~() const {
    MyString result;
    delete[] result.data;
    result.length = length;
    result.data = new char[length + 1];
    for (int i = 0; i < length; i++) {
        result.data[i] = toupper(data[i]);
    }
    result.data[length] = '\0';
    return result;
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
    cout << ~s << endl;
    return 0;
}
```

## Unary Operators Quick Reference

| Operator | Prefix Signature | Postfix Signature | Typical Return |
|----------|------------------|-------------------|----------------|
| `++` | `T& operator++()` | `T operator++(int)` | Reference / Value |
| `--` | `T& operator--()` | `T operator--(int)` | Reference / Value |
| `-` | `T operator-() const` | N/A | Value |
| `+` | `T operator+() const` | N/A | Value |
| `!` | `bool operator!() const` | N/A | bool |
| `~` | `T operator~() const` | N/A | Value |
| `&` | `T* operator&()` | N/A | Pointer |
| `*` | `T& operator*()` | N/A | Reference |

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting int parameter for postfix | Compiler error | Add `int` parameter |
| Returning value for prefix | Can't chain operations | Return reference to `*this` |
| Returning reference for postfix | Returns reference to temporary | Return by value |
| Not marking const for read-only ops | Can't use on const objects | Add `const` qualifier |
| Incorrect side effects | Unexpected behavior | Follow built-in semantics |

## Summary

- **Prefix operators** (`++c`, `--c`) modify and return reference
- **Postfix operators** (`c++`, `c--`) return copy, then modify
- **Unary minus** (`-c`) typically returns negated value
- **Logical NOT** (`!c`) returns boolean
- **Dereference** (`*c`, `c->`) used in smart pointers
- **const correctness** important for read-only operations
- **Postfix** uses dummy `int` parameter to distinguish from prefix

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
    
    Number& operator++() {
        ++value;
        return *this;
    }
    
    Number operator++(int) {
        Number temp = *this;
        ++value;
        return temp;
    }
    
    Number operator-() const {
        return Number(-value);
    }
    
    bool operator!() const {
        return value == 0;
    }
    
    friend ostream& operator<<(ostream& os, const Number& n) {
        os << n.value;
        return os;
    }
};

int main() {
    Number n(5);
    cout << ++n << endl;
    cout << n++ << endl;
    cout << -n << endl;
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
    Number& operator++();
    Number operator++(int);
    Number operator-() const;
    bool operator!() const;
    
    friend ostream& operator<<(ostream& os, const Number& n);
};

#endif
```

**number.cpp**
```cpp
#include "number.h"
using namespace std;

Number::Number(int v) : value(v) {}

Number& Number::operator++() {
    ++value;
    return *this;
}

Number Number::operator++(int) {
    Number temp = *this;
    ++value;
    return temp;
}

Number Number::operator-() const {
    return Number(-value);
}

bool Number::operator!() const {
    return value == 0;
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
    Number n(5);
    cout << ++n << endl;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*
