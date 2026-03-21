# 74 - Creating Objects in C++

## What is an Object?
An object is an instance of a class. It represents a real-world entity with its own data (attributes) and behavior (methods). Objects are created from class blueprints and occupy memory at runtime.

## Basic Object Creation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    string brand;
    string model;
    int year;
    
    void display() {
        cout << brand << " " << model << " (" << year << ")" << endl;
    }
};

int main() {
    // Creating an object (stack allocation)
    Car myCar;
    
    // Accessing members
    myCar.brand = "Toyota";
    myCar.model = "Camry";
    myCar.year = 2022;
    
    myCar.display();
    
    return 0;
}
```

## Different Ways to Create Objects

### 1. Stack Allocation (Automatic Storage)
```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int id;
    
    Student(string n, int i) : name(n), id(i) {
        cout << "Constructor called for " << name << endl;
    }
    
    ~Student() {
        cout << "Destructor called for " << name << endl;
    }
    
    void display() {
        cout << "Name: " << name << ", ID: " << id << endl;
    }
};

int main() {
    // Objects created on stack
    Student s1("John", 101);
    Student s2("Alice", 102);
    
    s1.display();
    s2.display();
    
    // Automatically destroyed when out of scope
    return 0;
}
```

### 2. Heap Allocation (Dynamic Storage)
```cpp
#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
    string name;
    int id;
    
    Employee(string n, int i) : name(n), id(i) {
        cout << "Constructor: " << name << endl;
    }
    
    ~Employee() {
        cout << "Destructor: " << name << endl;
    }
    
    void display() {
        cout << "Employee: " << name << ", ID: " << id << endl;
    }
};

int main() {
    // Creating objects on heap
    Employee* emp1 = new Employee("John", 1001);
    Employee* emp2 = new Employee("Jane", 1002);
    
    emp1->display();  // Arrow operator for pointers
    emp2->display();
    
    // Must explicitly delete heap objects
    delete emp1;
    delete emp2;
    
    return 0;
}
```

### 3. Array of Objects
```cpp
#include <iostream>
#include <string>
using namespace std;

class Point {
public:
    int x, y;
    
    Point() : x(0), y(0) {
        cout << "Default constructor" << endl;
    }
    
    Point(int x, int y) : x(x), y(y) {
        cout << "Parameterized constructor" << endl;
    }
    
    void display() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    // Array of objects (stack)
    Point points1[3];  // Calls default constructor 3 times
    
    // Array with initialization
    Point points2[3] = {
        Point(1, 2),
        Point(3, 4),
        Point(5, 6)
    };
    
    cout << "Points1:" << endl;
    for (int i = 0; i < 3; i++) {
        points1[i].display();
    }
    
    cout << "\nPoints2:" << endl;
    for (int i = 0; i < 3; i++) {
        points2[i].display();
    }
    
    // Dynamic array of objects
    Point* points3 = new Point[3];  // Calls default constructor 3 times
    
    points3[0] = Point(10, 20);
    points3[1] = Point(30, 40);
    points3[2] = Point(50, 60);
    
    cout << "\nPoints3:" << endl;
    for (int i = 0; i < 3; i++) {
        points3[i].display();
    }
    
    delete[] points3;  // Delete array
    
    return 0;
}
```

## Object Initialization

### Default Constructor
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
    Book() {
        title = "Unknown";
        author = "Unknown";
        pages = 0;
        cout << "Default constructor called" << endl;
    }
    
    void display() {
        cout << title << " by " << author << ", " << pages << " pages" << endl;
    }
};

int main() {
    Book book1;      // Default constructor
    Book book2();    // This is a function declaration! Be careful
    Book book3{};    // Uniform initialization (C++11)
    
    book1.display();
    // book2.display();  // Error! book2 is a function
    
    return 0;
}
```

### Parameterized Constructor
```cpp
#include <iostream>
#include <string>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
    
public:
    // Parameterized constructor
    Rectangle(double l, double w) : length(l), width(w) {
        cout << "Rectangle created: " << length << "x" << width << endl;
    }
    
    double area() {
        return length * width;
    }
    
    double perimeter() {
        return 2 * (length + width);
    }
};

int main() {
    // Different ways to call parameterized constructor
    Rectangle rect1(5.0, 3.0);           // Direct initialization
    Rectangle rect2 = Rectangle(4.0, 2.0); // Copy initialization
    Rectangle rect3{6.0, 4.0};            // Uniform initialization (C++11)
    
    cout << "Area: " << rect1.area() << endl;
    cout << "Perimeter: " << rect1.perimeter() << endl;
    
    return 0;
}
```

### Copy Constructor
```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    
public:
    // Constructor
    Person(string n, int a) : name(n), age(a) {
        cout << "Constructor: " << name << endl;
    }
    
    // Copy constructor
    Person(const Person& other) {
        name = other.name;
        age = other.age;
        cout << "Copy constructor: " << name << endl;
    }
    
    void display() {
        cout << name << ", " << age << endl;
    }
};

int main() {
    Person p1("John", 25);           // Constructor
    Person p2 = p1;                  // Copy constructor
    Person p3(p2);                   // Copy constructor
    Person p4{p3};                   // Copy constructor (uniform)
    
    p1.display();
    p2.display();
    p3.display();
    p4.display();
    
    return 0;
}
```

## Object Access

### Dot Operator (.)
```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int roll;
    
    void display() {
        cout << name << " (" << roll << ")" << endl;
    }
};

int main() {
    Student s;
    s.name = "Alice";    // Dot operator
    s.roll = 101;        // Dot operator
    s.display();         // Dot operator
    
    return 0;
}
```

### Arrow Operator (->)
```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int roll;
    
    void display() {
        cout << name << " (" << roll << ")" << endl;
    }
};

int main() {
    Student* ptr = new Student();
    
    // Arrow operator for pointers
    ptr->name = "Bob";
    ptr->roll = 102;
    ptr->display();
    
    // Equivalent to dereference then dot
    (*ptr).name = "Charlie";
    (*ptr).roll = 103;
    (*ptr).display();
    
    delete ptr;
    
    return 0;
}
```

## Practical Examples

### Example 1: Student Management System
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
private:
    int id;
    string name;
    double gpa;
    
public:
    // Constructor
    Student(int i, string n, double g) : id(i), name(n), gpa(g) {}
    
    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    double getGpa() const { return gpa; }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", GPA: " << gpa << endl;
    }
};

class University {
private:
    vector<Student> students;
    
public:
    void addStudent(const Student& s) {
        students.push_back(s);
    }
    
    void displayAll() const {
        cout << "\n--- All Students ---" << endl;
        for (const auto& s : students) {
            s.display();
        }
    }
    
    Student* findStudent(int id) {
        for (auto& s : students) {
            if (s.getId() == id) {
                return &s;
            }
        }
        return nullptr;
    }
};

int main() {
    University uni;
    
    // Creating objects
    Student s1(101, "Alice", 3.8);
    Student s2(102, "Bob", 3.5);
    Student s3(103, "Charlie", 3.9);
    
    // Adding to collection
    uni.addStudent(s1);
    uni.addStudent(s2);
    uni.addStudent(s3);
    
    uni.displayAll();
    
    // Find and modify
    Student* found = uni.findStudent(102);
    if (found) {
        cout << "\nFound: ";
        found->display();
    }
    
    return 0;
}
```

### Example 2: Dynamic Object Creation
```cpp
#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    static int nextId;
    int id;
    string name;
    double price;
    
public:
    Product(string n, double p) : name(n), price(p) {
        id = nextId++;
        cout << "Product created: " << name << " (ID: " << id << ")" << endl;
    }
    
    ~Product() {
        cout << "Product destroyed: " << name << " (ID: " << id << ")" << endl;
    }
    
    void display() const {
        cout << "ID: " << id << ", " << name << ", $" << price << endl;
    }
    
    double getPrice() const { return price; }
};

int Product::nextId = 1;

int main() {
    // Dynamic array of pointers
    Product* inventory[5];
    
    // Creating objects dynamically
    inventory[0] = new Product("Laptop", 999.99);
    inventory[1] = new Product("Mouse", 29.99);
    inventory[2] = new Product("Keyboard", 79.99);
    inventory[3] = new Product("Monitor", 299.99);
    inventory[4] = new Product("Printer", 149.99);
    
    cout << "\n--- Inventory ---" << endl;
    for (int i = 0; i < 5; i++) {
        inventory[i]->display();
    }
    
    // Calculate total
    double total = 0;
    for (int i = 0; i < 5; i++) {
        total += inventory[i]->getPrice();
    }
    cout << "\nTotal value: $" << total << endl;
    
    // Clean up
    for (int i = 0; i < 5; i++) {
        delete inventory[i];
    }
    
    return 0;
}
```

### Example 3: Object Composition
```cpp
#include <iostream>
#include <string>
using namespace std;

class Address {
public:
    string street;
    string city;
    string zip;
    
    Address(string s, string c, string z) : street(s), city(c), zip(z) {}
    
    void display() const {
        cout << street << ", " << city << ", " << zip << endl;
    }
};

class Person {
private:
    string name;
    int age;
    Address* address;  // Composition - Person has an Address
    
public:
    Person(string n, int a, string s, string c, string z) 
        : name(n), age(a) {
        address = new Address(s, c, z);
        cout << "Person created: " << name << endl;
    }
    
    ~Person() {
        delete address;
        cout << "Person destroyed: " << name << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
        cout << "Address: ";
        address->display();
    }
};

int main() {
    // Creating objects with composition
    Person p1("John Doe", 30, "123 Main St", "New York", "10001");
    Person p2("Jane Smith", 25, "456 Oak Ave", "Los Angeles", "90001");
    
    p1.display();
    cout << endl;
    p2.display();
    
    return 0;
}
```

### Example 4: Object Factory Pattern
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Shape {
public:
    virtual void draw() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    void draw() const override {
        cout << "Circle (r=" << radius << ")" << endl;
    }
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    void draw() const override {
        cout << "Rectangle (" << width << "x" << height << ")" << endl;
    }
    
    double area() const override {
        return width * height;
    }
};

class ShapeFactory {
public:
    static Shape* createCircle(double radius) {
        return new Circle(radius);
    }
    
    static Shape* createRectangle(double width, double height) {
        return new Rectangle(width, height);
    }
};

int main() {
    vector<Shape*> shapes;
    
    // Creating objects through factory
    shapes.push_back(ShapeFactory::createCircle(5.0));
    shapes.push_back(ShapeFactory::createRectangle(4.0, 3.0));
    shapes.push_back(ShapeFactory::createCircle(3.0));
    shapes.push_back(ShapeFactory::createRectangle(6.0, 2.0));
    
    cout << "--- Shapes ---" << endl;
    for (const auto& shape : shapes) {
        shape->draw();
        cout << "Area: " << shape->area() << endl << endl;
    }
    
    // Clean up
    for (auto& shape : shapes) {
        delete shape;
    }
    
    return 0;
}
```

### Example 5: Singleton Pattern
```cpp
#include <iostream>
#include <string>
using namespace std;

class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    string connectionString;
    bool connected;
    
    // Private constructor (prevents direct creation)
    DatabaseConnection() : connected(false) {
        cout << "DatabaseConnection created" << endl;
    }
    
public:
    // Static method to get instance
    static DatabaseConnection* getInstance() {
        if (instance == nullptr) {
            instance = new DatabaseConnection();
        }
        return instance;
    }
    
    void connect(const string& connStr) {
        if (!connected) {
            connectionString = connStr;
            connected = true;
            cout << "Connected to: " << connectionString << endl;
        } else {
            cout << "Already connected to: " << connectionString << endl;
        }
    }
    
    void disconnect() {
        if (connected) {
            connected = false;
            cout << "Disconnected" << endl;
        }
    }
    
    void executeQuery(const string& query) {
        if (connected) {
            cout << "Executing: " << query << endl;
        } else {
            cout << "Not connected!" << endl;
        }
    }
    
    // Delete copy constructor and assignment
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
};

DatabaseConnection* DatabaseConnection::instance = nullptr;

int main() {
    // Cannot create object directly
    // DatabaseConnection db;  // Error!
    
    // Get the single instance
    DatabaseConnection* db1 = DatabaseConnection::getInstance();
    DatabaseConnection* db2 = DatabaseConnection::getInstance();
    
    // Both pointers point to same object
    cout << "Same instance? " << (db1 == db2 ? "Yes" : "No") << endl;
    
    db1->connect("localhost:3306/mydb");
    db2->executeQuery("SELECT * FROM users");
    
    db1->disconnect();
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Forgetting to Delete Heap Objects
```cpp
void function() {
    MyClass* obj = new MyClass();
    // Use obj...
    // Missing delete! Memory leak!
}

// Correct
void function() {
    MyClass* obj = new MyClass();
    // Use obj...
    delete obj;  // Must delete
}
```

### Mistake 2: Using Uninitialized Objects
```cpp
class MyClass {
public:
    int value;
};

int main() {
    MyClass obj;  // value is uninitialized!
    cout << obj.value;  // Garbage value!
    
    return 0;
}
```

### Mistake 3: Object Slicing
```cpp
class Base {
public:
    virtual void display() { cout << "Base" << endl; }
};

class Derived : public Base {
public:
    void display() override { cout << "Derived" << endl; }
};

int main() {
    Derived d;
    Base b = d;  // Slicing! Loses Derived data
    b.display();  // Prints "Base", not "Derived"
    
    Base* ptr = &d;  // Correct - use pointer
    ptr->display();  // Prints "Derived"
    
    return 0;
}
```

### Mistake 4: Dangling Pointers
```cpp
MyClass* getObject() {
    MyClass obj;
    return &obj;  // Returns address of local - Dangling!
}

int main() {
    MyClass* ptr = getObject();  // ptr points to destroyed object
    ptr->display();  // Undefined behavior!
    
    return 0;
}
```

### Mistake 5: Using Object Before Construction
```cpp
class MyClass {
public:
    MyClass(int x) : value(x) {}
    int value;
};

int main() {
    MyClass obj;  // Error! No default constructor
    // Must provide arguments
    
    return 0;
}
```

## Quick Reference Table

| Creation Method | Syntax | Memory | Lifetime |
|-----------------|--------|--------|----------|
| Stack | `MyClass obj;` | Stack | End of scope |
| Stack (init) | `MyClass obj(10);` | Stack | End of scope |
| Heap | `MyClass* obj = new MyClass();` | Heap | Until `delete` |
| Heap array | `MyClass* arr = new MyClass[10];` | Heap | Until `delete[]` |
| Copy | `MyClass obj2 = obj1;` | Stack | End of scope |
| Reference | `MyClass& ref = obj;` | Stack | Same as obj |

## Summary

- **Stack objects** - automatic lifetime, fast allocation
- **Heap objects** - manual lifetime, flexible, need `delete`
- **Default constructor** - called when no arguments provided
- **Parameterized constructor** - used with arguments
- **Copy constructor** - creates copy of existing object
- **Dot operator (.)** - access members of stack objects
- **Arrow operator (->)** - access members of pointers to objects
- **Arrays of objects** - can be stack or heap allocated
- **Object composition** - objects containing other objects
- **Factory patterns** - centralized object creation

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

class MyClass {
private:
    string name;
    int value;
    
public:
    // Constructors
    MyClass() : name("Default"), value(0) {
        cout << "Default constructor" << endl;
    }
    
    MyClass(string n, int v) : name(n), value(v) {
        cout << "Parameterized constructor: " << name << endl;
    }
    
    // Copy constructor
    MyClass(const MyClass& other) : name(other.name), value(other.value) {
        cout << "Copy constructor: " << name << endl;
    }
    
    // Destructor
    ~MyClass() {
        cout << "Destructor: " << name << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Value: " << value << endl;
    }
};

int main() {
    // Stack objects
    MyClass obj1;
    MyClass obj2("Hello", 42);
    MyClass obj3 = obj2;  // Copy constructor
    
    obj1.display();
    obj2.display();
    obj3.display();
    
    // Heap objects
    MyClass* ptr1 = new MyClass("Dynamic", 100);
    MyClass* ptr2 = new MyClass(*ptr1);  // Copy
    
    ptr1->display();
    ptr2->display();
    
    // Array of objects
    MyClass arr[2] = {MyClass("First", 1), MyClass("Second", 2)};
    
    for (int i = 0; i < 2; i++) {
        arr[i].display();
    }
    
    // Clean up heap
    delete ptr1;
    delete ptr2;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*