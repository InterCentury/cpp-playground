# 73 - Class Definition in C++

## What is a Class?
A class is a blueprint for creating objects. It defines the data (attributes) and functions (methods) that objects of that class will have. Classes are the foundation of Object-Oriented Programming in C++.

## Basic Class Syntax

```cpp
class ClassName {
    // Access specifiers
    public:
        // Public members (accessible from anywhere)
    private:
        // Private members (accessible only within the class)
    protected:
        // Protected members (accessible in derived classes)
};
```

## Simple Class Example

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    // Public members
    string name;
    int age;
    double gpa;
    
    void display() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "GPA: " << gpa << endl;
    }
};

int main() {
    // Create an object
    Student student1;
    
    // Access members
    student1.name = "John Doe";
    student1.age = 20;
    student1.gpa = 3.5;
    
    // Call member function
    student1.display();
    
    return 0;
}
```

## Access Specifiers

### Public Members
```cpp
#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    string brand;
    string model;
    
    void display() {
        cout << brand << " " << model << endl;
    }
};

int main() {
    Car myCar;
    myCar.brand = "Toyota";     // ✅ Accessible
    myCar.model = "Corolla";    // ✅ Accessible
    myCar.display();            // ✅ Accessible
    
    return 0;
}
```

### Private Members
```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    double balance;     // Private - cannot be accessed directly
    string accountNumber;
    
public:
    void setBalance(double amount) {
        if (amount >= 0) {
            balance = amount;
        }
    }
    
    double getBalance() {
        return balance;
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
};

int main() {
    BankAccount account;
    
    // account.balance = 1000;  // ❌ Error! Private member
    
    account.setBalance(1000);   // ✅ Access through public method
    account.deposit(500);        // ✅ Access through public method
    
    cout << "Balance: " << account.getBalance() << endl;
    
    return 0;
}
```

### Protected Members
```cpp
#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
    string name;      // Protected - accessible in derived classes
    int age;
    
public:
    void setName(string n) { name = n; }
};

class Dog : public Animal {
public:
    void bark() {
        cout << name << " says: Woof!" << endl;  // ✅ Accessible
    }
};

int main() {
    Dog myDog;
    myDog.setName("Buddy");
    myDog.bark();
    
    // myDog.name = "Max";  // ❌ Error! Protected member
    
    return 0;
}
```

## Class with Member Functions

### Defining Member Functions Inside Class
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
    Circle circle;
    circle.setRadius(5.0);
    
    cout << "Radius: " << circle.getRadius() << endl;
    cout << "Area: " << circle.area() << endl;
    cout << "Circumference: " << circle.circumference() << endl;
    
    return 0;
}
```

### Defining Member Functions Outside Class
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
    rect.setDimensions(4.5, 3.2);
    rect.display();
    
    return 0;
}
```

## Constructor and Destructor

```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    
public:
    // Constructor - called when object is created
    Person() {
        name = "Unknown";
        age = 0;
        cout << "Default constructor called" << endl;
    }
    
    // Parameterized constructor
    Person(string n, int a) {
        name = n;
        age = a;
        cout << "Parameterized constructor called" << endl;
    }
    
    // Destructor - called when object is destroyed
    ~Person() {
        cout << "Destructor called for " << name << endl;
    }
    
    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main() {
    Person p1;                    // Default constructor
    Person p2("John", 25);        // Parameterized constructor
    
    p1.display();
    p2.display();
    
    return 0;
}
```

## Practical Examples

### Example 1: Student Class with Getters/Setters
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    vector<double> grades;
    double average;
    
    void calculateAverage() {
        if (grades.empty()) {
            average = 0;
            return;
        }
        
        double sum = 0;
        for (double grade : grades) {
            sum += grade;
        }
        average = sum / grades.size();
    }
    
public:
    // Constructor
    Student(string n, int roll) {
        name = n;
        rollNumber = roll;
        average = 0;
    }
    
    // Getters
    string getName() const { return name; }
    int getRollNumber() const { return rollNumber; }
    double getAverage() const { return average; }
    
    // Setters
    void setName(string n) { name = n; }
    void setRollNumber(int roll) { rollNumber = roll; }
    
    // Add grade
    void addGrade(double grade) {
        if (grade >= 0 && grade <= 100) {
            grades.push_back(grade);
            calculateAverage();
        }
    }
    
    void display() {
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Grades: ";
        for (double grade : grades) {
            cout << grade << " ";
        }
        cout << endl;
        cout << "Average: " << average << endl;
    }
};

int main() {
    Student student("Alice", 101);
    
    student.addGrade(85.5);
    student.addGrade(92.0);
    student.addGrade(78.5);
    student.addGrade(88.0);
    
    student.display();
    
    return 0;
}
```

### Example 2: Bank Account Class
```cpp
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;
    string accountType;
    static int accountCounter;
    
    string generateAccountNumber() {
        accountCounter++;
        return "ACC" + to_string(accountCounter);
    }
    
public:
    // Constructor
    BankAccount(string holder, string type = "Savings") {
        accountHolder = holder;
        accountType = type;
        balance = 0;
        accountNumber = generateAccountNumber();
        cout << "Account created for " << holder << endl;
    }
    
    // Destructor
    ~BankAccount() {
        cout << "Account " << accountNumber << " closed" << endl;
    }
    
    // Public methods
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
            cout << "New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount" << endl;
        }
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
            cout << "New balance: $" << balance << endl;
            return true;
        }
        cout << "Insufficient funds or invalid amount" << endl;
        return false;
    }
    
    void display() const {
        cout << "==================" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: $" << balance << endl;
        cout << "==================" << endl;
    }
    
    // Getters
    string getAccountNumber() const { return accountNumber; }
    string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }
};

int BankAccount::accountCounter = 0;

int main() {
    BankAccount acc1("John Doe");
    BankAccount acc2("Jane Smith", "Checking");
    
    acc1.deposit(1000);
    acc1.withdraw(250);
    acc1.display();
    
    acc2.deposit(500);
    acc2.withdraw(100);
    acc2.display();
    
    return 0;
}
```

### Example 3: Time Class
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
    // Constructors
    Time() : hours(0), minutes(0), seconds(0) {}
    
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        normalize();
    }
    
    // Member functions
    void addSeconds(int s) {
        seconds += s;
        normalize();
    }
    
    void addMinutes(int m) {
        minutes += m;
        normalize();
    }
    
    void addHours(int h) {
        hours += h;
        normalize();
    }
    
    Time add(const Time& other) {
        Time result;
        result.hours = hours + other.hours;
        result.minutes = minutes + other.minutes;
        result.seconds = seconds + other.seconds;
        result.normalize();
        return result;
    }
    
    bool equals(const Time& other) const {
        return hours == other.hours && 
               minutes == other.minutes && 
               seconds == other.seconds;
    }
    
    void display() const {
        cout << setfill('0') 
             << setw(2) << hours << ":"
             << setw(2) << minutes << ":"
             << setw(2) << seconds << endl;
    }
};

int main() {
    Time t1(2, 30, 45);
    Time t2(1, 45, 30);
    
    cout << "t1: ";
    t1.display();
    
    cout << "t2: ";
    t2.display();
    
    t1.addMinutes(45);
    cout << "t1 after +45 minutes: ";
    t1.display();
    
    Time t3 = t1.add(t2);
    cout << "t1 + t2: ";
    t3.display();
    
    return 0;
}
```

### Example 4: Product Class
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    int quantity;
    static int nextId;
    
public:
    // Constructor
    Product(string n, double p, int q = 0) {
        id = nextId++;
        name = n;
        price = p;
        quantity = q;
    }
    
    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    
    // Setters
    void setPrice(double p) { 
        if (p >= 0) price = p;
    }
    
    void setQuantity(int q) {
        if (q >= 0) quantity = q;
    }
    
    void addStock(int q) {
        if (q > 0) quantity += q;
    }
    
    bool sell(int q) {
        if (q > 0 && q <= quantity) {
            quantity -= q;
            return true;
        }
        return false;
    }
    
    double getTotalValue() const {
        return price * quantity;
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Price: $" << price 
             << ", Stock: " << quantity 
             << ", Value: $" << getTotalValue() << endl;
    }
};

int Product::nextId = 1;

class Inventory {
private:
    vector<Product> products;
    
public:
    void addProduct(const Product& p) {
        products.push_back(p);
        cout << "Product added: " << p.getName() << endl;
    }
    
    Product* findProduct(int id) {
        for (auto& p : products) {
            if (p.getId() == id) {
                return &p;
            }
        }
        return nullptr;
    }
    
    void displayAll() const {
        if (products.empty()) {
            cout << "Inventory empty" << endl;
            return;
        }
        
        double totalValue = 0;
        cout << "\n--- Inventory ---" << endl;
        for (const auto& p : products) {
            p.display();
            totalValue += p.getTotalValue();
        }
        cout << "Total Inventory Value: $" << totalValue << endl;
    }
};

int main() {
    Inventory inv;
    
    inv.addProduct(Product("Laptop", 999.99, 10));
    inv.addProduct(Product("Mouse", 29.99, 50));
    inv.addProduct(Product("Keyboard", 79.99, 25));
    
    inv.displayAll();
    
    Product* laptop = inv.findProduct(1);
    if (laptop) {
        laptop->sell(2);
        cout << "\nSold 2 laptops" << endl;
    }
    
    inv.displayAll();
    
    return 0;
}
```

### Example 5: Point Class with Operator Overloading
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double x, y;
    
public:
    // Constructors
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    
    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    
    // Setters
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    
    // Member functions
    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx*dx + dy*dy);
    }
    
    void translate(double dx, double dy) {
        x += dx;
        y += dy;
    }
    
    // Display
    void display() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
    
    // Static function
    static double distance(const Point& p1, const Point& p2) {
        return p1.distanceTo(p2);
    }
};

class Line {
private:
    Point p1, p2;
    
public:
    Line(const Point& start, const Point& end) : p1(start), p2(end) {}
    
    double length() const {
        return p1.distanceTo(p2);
    }
    
    void display() const {
        cout << "Line from ";
        p1.display();
        cout << " to ";
        p2.display();
        cout << "Length: " << length() << endl;
    }
};

int main() {
    Point origin;
    Point p1(3, 4);
    Point p2(6, 8);
    
    cout << "Origin: ";
    origin.display();
    
    cout << "p1: ";
    p1.display();
    
    cout << "p2: ";
    p2.display();
    
    cout << "Distance between origin and p1: " << origin.distanceTo(p1) << endl;
    cout << "Distance between p1 and p2: " << Point::distance(p1, p2) << endl;
    
    p1.translate(1, 1);
    cout << "p1 after translation: ";
    p1.display();
    
    Line line(origin, p2);
    line.display();
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Missing Semicolon After Class
```cpp
class MyClass {
    // members
}  // ❌ Missing semicolon!

// Correct
class MyClass {
    // members
};
```

### Mistake 2: Accessing Private Members Directly
```cpp
class BankAccount {
private:
    double balance;
};

int main() {
    BankAccount acc;
    acc.balance = 1000;  // ❌ Error! Private member
    
    return 0;
}
```

### Mistake 3: Forgetting to Define Member Functions
```cpp
class Rectangle {
public:
    void setDimensions(double l, double w);  // Declaration only
};

// Missing definition!
int main() {
    Rectangle rect;
    rect.setDimensions(4, 5);  // ❌ Linker error!
    
    return 0;
}
```

### Mistake 4: Using Class Before Definition
```cpp
int main() {
    MyClass obj;  // ❌ Error! MyClass not defined yet
    return 0;
}

class MyClass { };  // Defined after use
```

### Mistake 5: Missing Public/Private Specification
```cpp
class MyClass {
    int x;  // Private by default
    int y;  // Private by default
    
public:
    int z;  // Public
};
```

## Quick Reference Table

| Syntax | Description |
|--------|-------------|
| `class ClassName { };` | Class definition |
| `public:` | Members accessible anywhere |
| `private:` | Members accessible only within class |
| `protected:` | Members accessible in derived classes |
| `ClassName obj;` | Create object |
| `obj.member` | Access member |
| `ClassName::function` | Define member function outside class |
| `this->member` | Access current object's member |

## Summary

- **Class** is blueprint for objects
- **Public** members accessible from anywhere
- **Private** members accessible only within class
- **Protected** members accessible in derived classes
- **Member functions** define behavior
- **Constructor** initializes objects
- **Destructor** cleans up objects
- **this pointer** refers to current object
- **Static members** shared across all objects

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

class ClassName {
private:
    // Private data members
    string data;
    int value;
    
public:
    // Constructor
    ClassName() : data(""), value(0) {
        cout << "Constructor called" << endl;
    }
    
    ClassName(string d, int v) : data(d), value(v) {
        cout << "Parameterized constructor" << endl;
    }
    
    // Destructor
    ~ClassName() {
        cout << "Destructor called" << endl;
    }
    
    // Getters
    string getData() const { return data; }
    int getValue() const { return value; }
    
    // Setters
    void setData(string d) { data = d; }
    void setValue(int v) { value = v; }
    
    // Other member functions
    void display() const {
        cout << "Data: " << data << ", Value: " << value << endl;
    }
};

int main() {
    ClassName obj1;
    obj1.setData("Hello");
    obj1.setValue(42);
    obj1.display();
    
    ClassName obj2("World", 100);
    obj2.display();
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*