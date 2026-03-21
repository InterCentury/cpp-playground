# 76 - Member Functions in C++

## What are Member Functions?
Member functions (also called methods) are functions that belong to a class. They define the behavior and operations that can be performed on objects of that class. Member functions have access to the class's private and protected members.

## Basic Syntax

```cpp
class ClassName {
public:
    return_type function_name(parameters) {
        // Function body
        // Can access member variables
    }
};
```

## Simple Example

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int age;
    
    // Member function
    void display() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

int main() {
    Student s;
    s.name = "John";
    s.age = 20;
    s.display();  // Calling member function
    
    return 0;
}
```

## Defining Member Functions

### Inside Class Definition (Inline)
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Circle {
private:
    double radius;
    
public:
    void setRadius(double r) {
        if (r >= 0) {
            radius = r;
        }
    }
    
    double getRadius() {
        return radius;
    }
    
    double area() {
        return 3.14159 * radius * radius;
    }
    
    double circumference() {
        return 2 * 3.14159 * radius;
    }
};

int main() {
    Circle c;
    c.setRadius(5.0);
    
    cout << "Radius: " << c.getRadius() << endl;
    cout << "Area: " << c.area() << endl;
    cout << "Circumference: " << c.circumference() << endl;
    
    return 0;
}
```

### Outside Class Definition (Using Scope Resolution)
```cpp
#include <iostream>
#include <string>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
    
public:
    void setDimensions(double l, double w);
    double area();
    double perimeter();
    void display();
};

// Member function definitions outside class
void Rectangle::setDimensions(double l, double w) {
    if (l >= 0 && w >= 0) {
        length = l;
        width = w;
    }
}

double Rectangle::area() {
    return length * width;
}

double Rectangle::perimeter() {
    return 2 * (length + width);
}

void Rectangle::display() {
    cout << "Length: " << length << ", Width: " << width << endl;
    cout << "Area: " << area() << endl;
    cout << "Perimeter: " << perimeter() << endl;
}

int main() {
    Rectangle rect;
    rect.setDimensions(5.0, 3.0);
    rect.display();
    
    return 0;
}
```

## Types of Member Functions

### Accessor (Getter) Functions
```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;
    
public:
    // Accessor functions - return values without modifying
    string getAccountNumber() const {
        return accountNumber;
    }
    
    double getBalance() const {
        return balance;
    }
    
    // Mutator functions - modify values
    void setAccountNumber(string accNum) {
        if (accNum.length() >= 5) {
            accountNumber = accNum;
        }
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

int main() {
    BankAccount acc;
    acc.setAccountNumber("ACC12345");
    acc.deposit(1000);
    
    cout << "Account: " << acc.getAccountNumber() << endl;
    cout << "Balance: $" << acc.getBalance() << endl;
    
    if (acc.withdraw(500)) {
        cout << "Withdrawal successful" << endl;
    }
    
    cout << "New balance: $" << acc.getBalance() << endl;
    
    return 0;
}
```

### Const Member Functions
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
    
    // Const member functions - promise not to modify object
    string getName() const {
        // name = "Modified";  // ❌ Error! Cannot modify in const function
        return name;
    }
    
    int getAge() const {
        return age;
    }
    
    // Non-const function - can modify
    void setAge(int a) {
        if (a >= 0) {
            age = a;
        }
    }
    
    void display() const {
        cout << name << ", " << age << endl;
    }
};

int main() {
    Person p1("John", 25);           // Non-const object
    const Person p2("Alice", 30);     // Const object
    
    p1.setAge(26);    // ✅ OK - non-const object, non-const function
    p1.display();     // ✅ OK - non-const object, const function
    
    // p2.setAge(31);  // ❌ Error! Const object cannot call non-const function
    p2.display();     // ✅ OK - const object, const function
    
    return 0;
}
```

### Static Member Functions
```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int id;
    static int studentCount;  // Static member variable
    
public:
    Student(string n) : name(n) {
        id = ++studentCount;
        cout << "Student " << name << " created (ID: " << id << ")" << endl;
    }
    
    // Static member function - can only access static members
    static int getStudentCount() {
        return studentCount;
    }
    
    // Non-static function - can access both static and non-static
    void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
        cout << "Total students: " << studentCount << endl;
    }
};

int Student::studentCount = 0;

int main() {
    cout << "Initial count: " << Student::getStudentCount() << endl;
    
    Student s1("John");
    Student s2("Alice");
    Student s3("Bob");
    
    cout << "\nAfter creating students: " << Student::getStudentCount() << endl;
    
    s1.display();
    
    return 0;
}
```

### Inline Member Functions
```cpp
#include <iostream>
#include <string>
using namespace std;

class Math {
public:
    // Implicitly inline (defined inside class)
    int square(int x) {
        return x * x;
    }
    
    // Explicitly inline (defined outside)
    inline int cube(int x);
};

// Inline function definition
inline int Math::cube(int x) {
    return x * x * x;
}

int main() {
    Math m;
    cout << "Square of 5: " << m.square(5) << endl;
    cout << "Cube of 5: " << m.cube(5) << endl;
    
    return 0;
}
```

## Special Member Functions

### Constructor
```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int pages;
    
public:
    // Default constructor
    Book() : title("Unknown"), author("Unknown"), pages(0) {
        cout << "Default constructor called" << endl;
    }
    
    // Parameterized constructor
    Book(string t, string a, int p) : title(t), author(a), pages(p) {
        cout << "Parameterized constructor called for " << title << endl;
    }
    
    // Copy constructor
    Book(const Book& other) 
        : title(other.title), author(other.author), pages(other.pages) {
        cout << "Copy constructor called for " << title << endl;
    }
    
    void display() const {
        cout << title << " by " << author << ", " << pages << " pages" << endl;
    }
};

int main() {
    Book b1;                           // Default constructor
    Book b2("C++ Programming", "Bjarne", 1200);  // Parameterized
    Book b3(b2);                       // Copy constructor
    
    b1.display();
    b2.display();
    b3.display();
    
    return 0;
}
```

### Destructor
```cpp
#include <iostream>
#include <string>
using namespace std;

class Resource {
private:
    string name;
    int* data;
    
public:
    Resource(string n, int size) : name(n) {
        data = new int[size];
        cout << "Resource " << name << " allocated" << endl;
    }
    
    ~Resource() {
        delete[] data;
        cout << "Resource " << name << " destroyed" << endl;
    }
    
    void display() const {
        cout << "Resource: " << name << endl;
    }
};

int main() {
    Resource r1("First", 100);
    Resource r2("Second", 200);
    
    r1.display();
    r2.display();
    
    // Destructors called automatically when objects go out of scope
    return 0;
}
```

## Operator Overloading as Member Functions

```cpp
#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // Operator overloading as member function
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
    
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    Complex sum = c1 + c2;
    Complex diff = c1 - c2;
    Complex prod = c1 * c2;
    
    cout << "c1: "; c1.display();
    cout << "c2: "; c2.display();
    cout << "Sum: "; sum.display();
    cout << "Difference: "; diff.display();
    cout << "Product: "; prod.display();
    
    cout << "c1 == c2? " << (c1 == c2 ? "Yes" : "No") << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Stack Class with Member Functions
```cpp
#include <iostream>
#include <string>
using namespace std;

class Stack {
private:
    static const int MAX_SIZE = 100;
    int data[MAX_SIZE];
    int top;
    
public:
    // Constructor
    Stack() : top(-1) {}
    
    // Member functions
    bool isEmpty() const {
        return top == -1;
    }
    
    bool isFull() const {
        return top == MAX_SIZE - 1;
    }
    
    bool push(int value) {
        if (isFull()) {
            cout << "Stack overflow!" << endl;
            return false;
        }
        data[++top] = value;
        return true;
    }
    
    bool pop(int& value) {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            return false;
        }
        value = data[top--];
        return true;
    }
    
    bool peek(int& value) const {
        if (isEmpty()) {
            return false;
        }
        value = data[top];
        return true;
    }
    
    int size() const {
        return top + 1;
    }
    
    void clear() {
        top = -1;
    }
    
    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        for (int i = top; i >= 0; i--) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack s;
    
    s.push(10);
    s.push(20);
    s.push(30);
    s.display();
    
    int value;
    s.pop(value);
    cout << "Popped: " << value << endl;
    s.display();
    
    s.peek(value);
    cout << "Top: " << value << endl;
    cout << "Size: " << s.size() << endl;
    
    s.clear();
    s.display();
    
    return 0;
}
```

### Example 2: String Class Implementation
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private:
    char* str;
    int length;
    
public:
    // Constructor
    MyString(const char* s = "") {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }
    
    // Copy constructor
    MyString(const MyString& other) {
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }
    
    // Destructor
    ~MyString() {
        delete[] str;
    }
    
    // Assignment operator
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
        }
        return *this;
    }
    
    // Member functions
    int getLength() const {
        return length;
    }
    
    const char* c_str() const {
        return str;
    }
    
    MyString operator+(const MyString& other) const {
        char* temp = new char[length + other.length + 1];
        strcpy(temp, str);
        strcat(temp, other.str);
        MyString result(temp);
        delete[] temp;
        return result;
    }
    
    bool operator==(const MyString& other) const {
        return strcmp(str, other.str) == 0;
    }
    
    char& operator[](int index) {
        if (index >= 0 && index < length) {
            return str[index];
        }
        static char dummy = '\0';
        return dummy;
    }
    
    void display() const {
        cout << str;
    }
};

int main() {
    MyString s1("Hello");
    MyString s2(" World");
    MyString s3 = s1 + s2;
    
    cout << "s1: "; s1.display(); cout << endl;
    cout << "s2: "; s2.display(); cout << endl;
    cout << "s3: "; s3.display(); cout << endl;
    cout << "Length of s3: " << s3.getLength() << endl;
    
    s3[0] = 'J';
    cout << "Modified s3: "; s3.display(); cout << endl;
    
    return 0;
}
```

### Example 3: Bank Account with Transaction History
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Transaction {
private:
    string type;
    double amount;
    time_t timestamp;
    
public:
    Transaction(string t, double a) : type(t), amount(a) {
        timestamp = time(nullptr);
    }
    
    void display() const {
        cout << "  " << ctime(&timestamp);
        cout << "  " << type << ": $" << amount << endl;
    }
};

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;
    vector<Transaction> history;
    
public:
    BankAccount(string number, string holder, double initial = 0) 
        : accountNumber(number), accountHolder(holder), balance(initial) {
        if (initial > 0) {
            history.push_back(Transaction("Initial deposit", initial));
        }
    }
    
    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        return true;
    }
    
    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        history.push_back(Transaction("Withdrawal", amount));
        return true;
    }
    
    double getBalance() const {
        return balance;
    }
    
    string getAccountNumber() const {
        return accountNumber;
    }
    
    string getAccountHolder() const {
        return accountHolder;
    }
    
    void displayStatement() const {
        cout << "\n=== Account Statement ===" << endl;
        cout << "Account: " << accountNumber << endl;
        cout << "Holder: " << accountHolder << endl;
        cout << "Current Balance: $" << balance << endl;
        cout << "\nTransaction History:" << endl;
        
        if (history.empty()) {
            cout << "  No transactions" << endl;
        } else {
            for (const auto& t : history) {
                t.display();
            }
        }
    }
};

int main() {
    BankAccount acc("123456", "John Doe", 1000);
    
    acc.deposit(500);
    acc.withdraw(200);
    acc.deposit(300);
    acc.withdraw(100);
    
    acc.displayStatement();
    
    return 0;
}
```

### Example 4: Date Class with Utility Functions
```cpp
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
    
    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    
    int daysInMonth() const {
        if (month == 2) {
            return isLeapYear() ? 29 : 28;
        }
        if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        }
        return 31;
    }
    
    void normalize() {
        while (day > daysInMonth()) {
            day -= daysInMonth();
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        while (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day += daysInMonth();
        }
    }
    
public:
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {
        normalize();
    }
    
    // Accessors
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    
    // Mutators
    void setDay(int d) { day = d; normalize(); }
    void setMonth(int m) { month = m; normalize(); }
    void setYear(int y) { year = y; normalize(); }
    
    // Operations
    void addDays(int days) {
        day += days;
        normalize();
    }
    
    void addMonths(int months) {
        month += months;
        while (month > 12) {
            month -= 12;
            year++;
        }
        while (month < 1) {
            month += 12;
            year--;
        }
        normalize();
    }
    
    void addYears(int years) {
        year += years;
        normalize();
    }
    
    int daysBetween(const Date& other) const {
        // Simplified calculation
        Date temp = *this;
        int days = 0;
        while (temp != other) {
            if (temp < other) {
                temp.addDays(1);
                days++;
            } else {
                temp.addDays(-1);
                days--;
            }
        }
        return days;
    }
    
    // Comparison operators
    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    bool operator>(const Date& other) const {
        return other < *this;
    }
    
    // Display
    void display() const {
        cout << setfill('0') 
             << setw(2) << day << "/"
             << setw(2) << month << "/"
             << year;
    }
    
    string toString() const {
        char buffer[20];
        sprintf(buffer, "%02d/%02d/%04d", day, month, year);
        return string(buffer);
    }
};

int main() {
    Date today(22, 3, 2024);
    Date birthday(15, 5, 1990);
    
    cout << "Today: "; today.display(); cout << endl;
    cout << "Birthday: "; birthday.display(); cout << endl;
    
    today.addDays(10);
    cout << "10 days later: "; today.display(); cout << endl;
    
    Date tomorrow = today;
    tomorrow.addDays(1);
    cout << "Tomorrow: "; tomorrow.display(); cout << endl;
    
    return 0;
}
```

### Example 5: Shape Hierarchy with Virtual Functions
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void display() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void display() const override {
        cout << "Circle (r=" << radius << ")" << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void display() const override {
        cout << "Rectangle (" << width << "x" << height << ")" << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
};

class Triangle : public Shape {
private:
    double a, b, c;
    
public:
    Triangle(double side1, double side2, double side3) 
        : a(side1), b(side2), c(side3) {}
    
    double area() const override {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    
    double perimeter() const override {
        return a + b + c;
    }
    
    void display() const override {
        cout << "Triangle (" << a << ", " << b << ", " << c << ")" << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
};

int main() {
    Shape* shapes[3];
    
    shapes[0] = new Circle(5);
    shapes[1] = new Rectangle(4, 6);
    shapes[2] = new Triangle(3, 4, 5);
    
    for (int i = 0; i < 3; i++) {
        shapes[i]->display();
        cout << endl;
        delete shapes[i];
    }
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Forgetting to Define Member Functions
```cpp
class MyClass {
public:
    void doSomething();  // Declaration only
};

int main() {
    MyClass obj;
    obj.doSomething();  // Linker error! No definition
    
    return 0;
}
```

### Mistake 2: Const Correctness
```cpp
class MyClass {
    int value;
public:
    // Should be const, but isn't
    int getValue() { return value; }  // Can't be called on const objects
};

int main() {
    const MyClass obj;
    cout << obj.getValue();  // ❌ Error! getValue not const
    
    return 0;
}
```

### Mistake 3: Forgetting this Pointer
```cpp
class MyClass {
    int value;
public:
    void setValue(int value) {
        value = value;  // Sets parameter, not member! Ambiguous
    }
    
    // Correct
    void setValue(int val) {
        value = val;
    }
    
    // Or use this
    void setValue(int value) {
        this->value = value;
    }
};
```

### Mistake 4: Returning Reference to Local
```cpp
class MyClass {
public:
    int& getValue() {
        int x = 10;
        return x;  // DANGEROUS! Returns reference to local
    }
};
```

### Mistake 5: Missing const in Operator Overloading
```cpp
class Complex {
    double real, imag;
public:
    Complex operator+(const Complex& other) {  // Should be const
        return Complex(real + other.real, imag + other.imag);
    }
};
```

## Quick Reference Table

| Member Function Type | Syntax | Purpose |
|---------------------|--------|---------|
| Accessor | `int getX() const` | Return value, no modification |
| Mutator | `void setX(int x)` | Modify member variables |
| Const | `void display() const` | Promise not to modify |
| Static | `static int count()` | Class-level, no object needed |
| Inline | `inline int square(int x)` | Reduce call overhead |
| Virtual | `virtual void draw()` | Polymorphism |
| Pure Virtual | `virtual void draw() = 0` | Abstract class |

## Summary

- **Member functions** define object behavior
- Can be defined inside or outside class
- **Accessor functions** (getters) return member values
- **Mutator functions** (setters) modify member values
- **Const member functions** promise not to modify object
- **Static member functions** belong to class, not objects
- **Constructor** initializes objects
- **Destructor** cleans up resources
- **Operator overloading** provides intuitive syntax
- **Virtual functions** enable polymorphism

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

class MyClass {
private:
    int id;
    string name;
    static int counter;
    
public:
    // Constructor
    MyClass(string n) : name(n) {
        id = ++counter;
    }
    
    // Destructor
    ~MyClass() {
        cout << "Destroying: " << name << endl;
    }
    
    // Accessors (const)
    int getId() const { return id; }
    string getName() const { return name; }
    static int getCounter() { return counter; }
    
    // Mutators
    void setName(string n) { name = n; }
    
    // Other member functions
    void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
    }
    
    // Operator overloading
    bool operator==(const MyClass& other) const {
        return name == other.name;
    }
};

int MyClass::counter = 0;

int main() {
    MyClass obj1("First");
    MyClass obj2("Second");
    MyClass obj3("First");
    
    obj1.display();
    obj2.display();
    
    cout << "Total objects: " << MyClass::getCounter() << endl;
    cout << "obj1 == obj3? " << (obj1 == obj3 ? "Yes" : "No") << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*