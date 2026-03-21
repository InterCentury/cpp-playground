# 77 - Public Access Specifier in C++

## What is Public Access Specifier?
The `public` access specifier allows members (variables and functions) to be accessed from anywhere in the program. This includes outside the class, from derived classes, and from other parts of the program.

## Basic Syntax

```cpp
class ClassName {
public:
    // Public members
    int publicVariable;
    void publicFunction();
};
```

## Type 1: Single File Implementation

### Example: Student Class with Public Members

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    // Public member variables
    string name;
    int rollNumber;
    double gpa;
    
    // Public member functions
    void display() {
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "GPA: " << gpa << endl;
    }
    
    void updateGPA(double newGPA) {
        if (newGPA >= 0.0 && newGPA <= 4.0) {
            gpa = newGPA;
        } else {
            cout << "Invalid GPA!" << endl;
        }
    }
};

int main() {
    // Creating object
    Student student;
    
    // Accessing public members directly
    student.name = "John Doe";
    student.rollNumber = 101;
    student.gpa = 3.5;
    
    // Calling public member functions
    student.display();
    
    student.updateGPA(3.8);
    cout << "\nAfter GPA update:" << endl;
    student.display();
    
    // Direct modification (allowed because public)
    student.gpa = 4.0;
    cout << "\nAfter direct modification:" << endl;
    student.display();
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### File: student.h (Header File)
```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
public:
    // Public member variables
    string name;
    int rollNumber;
    double gpa;
    
    // Public member function declarations
    void display();
    void updateGPA(double newGPA);
};

#endif
```

### File: student.cpp (Implementation File)
```cpp
#include "student.h"
#include <iostream>
using namespace std;

// Public member function definitions
void Student::display() {
    cout << "Name: " << name << endl;
    cout << "Roll Number: " << rollNumber << endl;
    cout << "GPA: " << gpa << endl;
}

void Student::updateGPA(double newGPA) {
    if (newGPA >= 0.0 && newGPA <= 4.0) {
        gpa = newGPA;
    } else {
        cout << "Invalid GPA!" << endl;
    }
}
```

### File: main.cpp (Driver File)
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    // Creating object
    Student student;
    
    // Accessing public members directly
    student.name = "John Doe";
    student.rollNumber = 101;
    student.gpa = 3.5;
    
    // Calling public member functions
    student.display();
    
    student.updateGPA(3.8);
    cout << "\nAfter GPA update:" << endl;
    student.display();
    
    // Direct modification (allowed because public)
    student.gpa = 4.0;
    cout << "\nAfter direct modification:" << endl;
    student.display();
    
    return 0;
}
```

## Practical Examples

### Example 1: Car Class with Public Members

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    string brand;
    string model;
    int year;
    double mileage;
    
    void start() {
        cout << brand << " " << model << " is starting..." << endl;
    }
    
    void drive(double distance) {
        mileage += distance;
        cout << "Driven " << distance << " km. Total mileage: " << mileage << " km" << endl;
    }
    
    void display() {
        cout << "Car: " << brand << " " << model << " (" << year << ")" << endl;
        cout << "Mileage: " << mileage << " km" << endl;
    }
};

int main() {
    Car myCar;
    
    myCar.brand = "Toyota";
    myCar.model = "Camry";
    myCar.year = 2022;
    myCar.mileage = 0;
    
    myCar.display();
    myCar.start();
    myCar.drive(100);
    myCar.drive(50);
    
    // Direct modification
    myCar.mileage = 5000;
    cout << "\nAfter direct mileage change:" << endl;
    myCar.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**car.h**
```cpp
#ifndef CAR_H
#define CAR_H

#include <string>
using namespace std;

class Car {
public:
    string brand;
    string model;
    int year;
    double mileage;
    
    void start();
    void drive(double distance);
    void display();
};

#endif
```

**car.cpp**
```cpp
#include "car.h"
#include <iostream>
using namespace std;

void Car::start() {
    cout << brand << " " << model << " is starting..." << endl;
}

void Car::drive(double distance) {
    mileage += distance;
    cout << "Driven " << distance << " km. Total mileage: " << mileage << " km" << endl;
}

void Car::display() {
    cout << "Car: " << brand << " " << model << " (" << year << ")" << endl;
    cout << "Mileage: " << mileage << " km" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "car.h"
using namespace std;

int main() {
    Car myCar;
    
    myCar.brand = "Toyota";
    myCar.model = "Camry";
    myCar.year = 2022;
    myCar.mileage = 0;
    
    myCar.display();
    myCar.start();
    myCar.drive(100);
    myCar.drive(50);
    
    // Direct modification
    myCar.mileage = 5000;
    cout << "\nAfter direct mileage change:" << endl;
    myCar.display();
    
    return 0;
}
```

### Example 2: Calculator Class with Public Methods

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Calculator {
public:
    // Public member variables
    double lastResult;
    string lastOperation;
    
    // Public member functions
    double add(double a, double b) {
        lastResult = a + b;
        lastOperation = "Addition";
        return lastResult;
    }
    
    double subtract(double a, double b) {
        lastResult = a - b;
        lastOperation = "Subtraction";
        return lastResult;
    }
    
    double multiply(double a, double b) {
        lastResult = a * b;
        lastOperation = "Multiplication";
        return lastResult;
    }
    
    double divide(double a, double b) {
        if (b != 0) {
            lastResult = a / b;
            lastOperation = "Division";
            return lastResult;
        } else {
            cout << "Error: Division by zero!" << endl;
            return 0;
        }
    }
    
    double power(double base, double exponent) {
        lastResult = pow(base, exponent);
        lastOperation = "Power";
        return lastResult;
    }
    
    void displayLastResult() {
        cout << "Last operation: " << lastOperation << endl;
        cout << "Result: " << lastResult << endl;
    }
    
    void clear() {
        lastResult = 0;
        lastOperation = "Cleared";
        cout << "Calculator cleared!" << endl;
    }
};

int main() {
    Calculator calc;
    
    cout << "10 + 5 = " << calc.add(10, 5) << endl;
    cout << "10 - 5 = " << calc.subtract(10, 5) << endl;
    cout << "10 * 5 = " << calc.multiply(10, 5) << endl;
    cout << "10 / 5 = " << calc.divide(10, 5) << endl;
    cout << "2^8 = " << calc.power(2, 8) << endl;
    
    calc.displayLastResult();
    
    calc.clear();
    calc.displayLastResult();
    
    // Direct access to public variables
    calc.lastResult = 999;
    cout << "\nAfter direct modification: " << calc.lastResult << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**calculator.h**
```cpp
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
using namespace std;

class Calculator {
public:
    // Public member variables
    double lastResult;
    string lastOperation;
    
    // Public member function declarations
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    double power(double base, double exponent);
    void displayLastResult();
    void clear();
};

#endif
```

**calculator.cpp**
```cpp
#include "calculator.h"
#include <iostream>
#include <cmath>
using namespace std;

double Calculator::add(double a, double b) {
    lastResult = a + b;
    lastOperation = "Addition";
    return lastResult;
}

double Calculator::subtract(double a, double b) {
    lastResult = a - b;
    lastOperation = "Subtraction";
    return lastResult;
}

double Calculator::multiply(double a, double b) {
    lastResult = a * b;
    lastOperation = "Multiplication";
    return lastResult;
}

double Calculator::divide(double a, double b) {
    if (b != 0) {
        lastResult = a / b;
        lastOperation = "Division";
        return lastResult;
    } else {
        cout << "Error: Division by zero!" << endl;
        return 0;
    }
}

double Calculator::power(double base, double exponent) {
    lastResult = pow(base, exponent);
    lastOperation = "Power";
    return lastResult;
}

void Calculator::displayLastResult() {
    cout << "Last operation: " << lastOperation << endl;
    cout << "Result: " << lastResult << endl;
}

void Calculator::clear() {
    lastResult = 0;
    lastOperation = "Cleared";
    cout << "Calculator cleared!" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "calculator.h"
using namespace std;

int main() {
    Calculator calc;
    
    cout << "10 + 5 = " << calc.add(10, 5) << endl;
    cout << "10 - 5 = " << calc.subtract(10, 5) << endl;
    cout << "10 * 5 = " << calc.multiply(10, 5) << endl;
    cout << "10 / 5 = " << calc.divide(10, 5) << endl;
    cout << "2^8 = " << calc.power(2, 8) << endl;
    
    calc.displayLastResult();
    
    calc.clear();
    calc.displayLastResult();
    
    // Direct access to public variables
    calc.lastResult = 999;
    cout << "\nAfter direct modification: " << calc.lastResult << endl;
    
    return 0;
}
```

### Example 3: Rectangle Class with Public Members

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Rectangle {
public:
    double length;
    double width;
    
    double area() {
        return length * width;
    }
    
    double perimeter() {
        return 2 * (length + width);
    }
    
    double diagonal() {
        return sqrt(length * length + width * width);
    }
    
    bool isSquare() {
        return length == width;
    }
    
    void display() {
        cout << "Rectangle " << length << " x " << width << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
        cout << "Diagonal: " << diagonal() << endl;
        cout << "Is Square: " << (isSquare() ? "Yes" : "No") << endl;
    }
};

int main() {
    Rectangle rect1;
    Rectangle rect2;
    
    rect1.length = 5.0;
    rect1.width = 3.0;
    
    rect2.length = 4.0;
    rect2.width = 4.0;
    
    cout << "Rectangle 1:" << endl;
    rect1.display();
    
    cout << "\nRectangle 2:" << endl;
    rect2.display();
    
    // Direct modification
    rect1.length = 10.0;
    cout << "\nAfter modifying length:" << endl;
    rect1.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**rectangle.h**
```cpp
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    double length;
    double width;
    
    double area();
    double perimeter();
    double diagonal();
    bool isSquare();
    void display();
};

#endif
```

**rectangle.cpp**
```cpp
#include "rectangle.h"
#include <iostream>
#include <cmath>
using namespace std;

double Rectangle::area() {
    return length * width;
}

double Rectangle::perimeter() {
    return 2 * (length + width);
}

double Rectangle::diagonal() {
    return sqrt(length * length + width * width);
}

bool Rectangle::isSquare() {
    return length == width;
}

void Rectangle::display() {
    cout << "Rectangle " << length << " x " << width << endl;
    cout << "Area: " << area() << endl;
    cout << "Perimeter: " << perimeter() << endl;
    cout << "Diagonal: " << diagonal() << endl;
    cout << "Is Square: " << (isSquare() ? "Yes" : "No") << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "rectangle.h"
using namespace std;

int main() {
    Rectangle rect1;
    Rectangle rect2;
    
    rect1.length = 5.0;
    rect1.width = 3.0;
    
    rect2.length = 4.0;
    rect2.width = 4.0;
    
    cout << "Rectangle 1:" << endl;
    rect1.display();
    
    cout << "\nRectangle 2:" << endl;
    rect2.display();
    
    // Direct modification
    rect1.length = 10.0;
    cout << "\nAfter modifying length:" << endl;
    rect1.display();
    
    return 0;
}
```

### Example 4: Book Class with Public Members

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    double price;
    int pages;
    
    void display() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Price: $" << price << endl;
        cout << "Pages: " << pages << endl;
    }
    
    double discountedPrice(double discountPercent) {
        return price * (1 - discountPercent / 100);
    }
    
    string getBookInfo() {
        return title + " by " + author;
    }
    
    bool isExpensive() {
        return price > 50.0;
    }
    
    int readingTime(int wordsPerMinute) {
        // Assuming 300 words per page average
        int estimatedWords = pages * 300;
        return estimatedWords / wordsPerMinute;
    }
};

int main() {
    Book book;
    
    book.title = "C++ Programming";
    book.author = "Bjarne Stroustrup";
    book.isbn = "978-0321563842";
    book.price = 79.99;
    book.pages = 1368;
    
    book.display();
    
    cout << "\nDiscounted price (20% off): $" 
         << book.discountedPrice(20) << endl;
    cout << "Book info: " << book.getBookInfo() << endl;
    cout << "Is expensive? " << (book.isExpensive() ? "Yes" : "No") << endl;
    cout << "Estimated reading time at 200 wpm: " 
         << book.readingTime(200) << " minutes" << endl;
    
    // Direct modification
    book.price = 49.99;
    cout << "\nAfter price change: $" << book.price << endl;
    cout << "Is expensive now? " << (book.isExpensive() ? "Yes" : "No") << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**book.h**
```cpp
#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    double price;
    int pages;
    
    void display();
    double discountedPrice(double discountPercent);
    string getBookInfo();
    bool isExpensive();
    int readingTime(int wordsPerMinute);
};

#endif
```

**book.cpp**
```cpp
#include "book.h"
#include <iostream>
using namespace std;

void Book::display() {
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Price: $" << price << endl;
    cout << "Pages: " << pages << endl;
}

double Book::discountedPrice(double discountPercent) {
    return price * (1 - discountPercent / 100);
}

string Book::getBookInfo() {
    return title + " by " + author;
}

bool Book::isExpensive() {
    return price > 50.0;
}

int Book::readingTime(int wordsPerMinute) {
    // Assuming 300 words per page average
    int estimatedWords = pages * 300;
    return estimatedWords / wordsPerMinute;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "book.h"
using namespace std;

int main() {
    Book book;
    
    book.title = "C++ Programming";
    book.author = "Bjarne Stroustrup";
    book.isbn = "978-0321563842";
    book.price = 79.99;
    book.pages = 1368;
    
    book.display();
    
    cout << "\nDiscounted price (20% off): $" 
         << book.discountedPrice(20) << endl;
    cout << "Book info: " << book.getBookInfo() << endl;
    cout << "Is expensive? " << (book.isExpensive() ? "Yes" : "No") << endl;
    cout << "Estimated reading time at 200 wpm: " 
         << book.readingTime(200) << " minutes" << endl;
    
    // Direct modification
    book.price = 49.99;
    cout << "\nAfter price change: $" << book.price << endl;
    cout << "Is expensive now? " << (book.isExpensive() ? "Yes" : "No") << endl;
    
    return 0;
}
```

## Common Mistakes with Public Members

### Mistake 1: Exposing Sensitive Data
```cpp
class BankAccount {
public:
    double balance;  // Bad - anyone can modify balance directly
};

// Better approach
class BankAccount {
private:
    double balance;  // Encapsulated
public:
    void deposit(double amount) { balance += amount; }
    double getBalance() const { return balance; }
};
```

### Mistake 2: No Input Validation
```cpp
class Student {
public:
    int age;  // Can be set to negative values!
};

// Better approach
class Student {
private:
    int age;
public:
    void setAge(int a) {
        if (a >= 0 && a <= 150) {
            age = a;
        }
    }
};
```

### Mistake 3: Forgetting to Initialize
```cpp
class Point {
public:
    int x, y;  // Uninitialized - garbage values
};

// Better approach
class Point {
public:
    int x = 0;  // Default initialization
    int y = 0;
};
```

## Quick Reference

| Access Level | Accessibility |
|--------------|---------------|
| Public | Accessible from anywhere |
| Private | Only within class |
| Protected | Within class and derived classes |
| Default | Private (if no specifier given) |

## Summary

- **Public members** can be accessed from anywhere
- **Public member functions** define the interface
- **Public member variables** allow direct access (use with caution)
- Encapsulation suggests making data private and providing public methods
- Public members are useful for simple data structures
- Always validate input in public setters
- Keep public interface minimal and well-defined

---
*This documentation belongs to https://github.com/InterCentury*