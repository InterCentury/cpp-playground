# 75 - Member Variables in C++

## What are Member Variables?
Member variables (also called data members or attributes) are variables declared inside a class. They represent the state or properties of objects created from that class. Each object has its own copy of member variables (unless declared static).

## Basic Syntax

```cpp
class ClassName {
    // Member variables
    data_type variable_name;
    data_type another_variable;
};
```

## Simple Example

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    // Member variables
    string name;
    int age;
    double gpa;
    char grade;
};

int main() {
    Student student1;
    Student student2;
    
    // Each object has its own copy
    student1.name = "John";
    student1.age = 20;
    student1.gpa = 3.5;
    student1.grade = 'B';
    
    student2.name = "Alice";
    student2.age = 22;
    student2.gpa = 3.8;
    student2.grade = 'A';
    
    cout << student1.name << ": GPA " << student1.gpa << endl;
    cout << student2.name << ": GPA " << student2.gpa << endl;
    
    return 0;
}
```

## Access Specifiers and Member Variables

### Public Member Variables
```cpp
#include <iostream>
using namespace std;

class Point {
public:
    int x;  // Public - accessible anywhere
    int y;  // Public - accessible anywhere
};

int main() {
    Point p;
    p.x = 10;   // ✅ Direct access
    p.y = 20;   // ✅ Direct access
    
    cout << "(" << p.x << ", " << p.y << ")" << endl;
    
    return 0;
}
```

### Private Member Variables (Encapsulation)
```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;  // Private - cannot access directly
    double balance;        // Private - cannot access directly
    
public:
    // Public methods to access private members
    void setAccountNumber(string accNum) {
        if (accNum.length() >= 5) {
            accountNumber = accNum;
        }
    }
    
    string getAccountNumber() {
        return accountNumber;
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
    
    double getBalance() {
        return balance;
    }
};

int main() {
    BankAccount account;
    
    // account.balance = 1000;     // ❌ Error! Private member
    // account.accountNumber = "123"; // ❌ Error! Private member
    
    account.setAccountNumber("ACC12345");  // ✅ Through public method
    account.deposit(500);                   // ✅ Through public method
    
    cout << "Account: " << account.getAccountNumber() << endl;
    cout << "Balance: $" << account.getBalance() << endl;
    
    return 0;
}
```

### Protected Member Variables
```cpp
#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
    string name;   // Protected - accessible in derived classes
    int age;
    
public:
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
};

class Dog : public Animal {
public:
    void bark() {
        cout << name << " says: Woof!" << endl;  // ✅ Accessible
        cout << "Age: " << age << endl;          // ✅ Accessible
    }
};

int main() {
    Dog myDog;
    myDog.setName("Buddy");
    myDog.setAge(3);
    myDog.bark();
    
    // myDog.name = "Max";  // ❌ Error! Protected member
    
    return 0;
}
```

## Types of Member Variables

### Instance Variables (Per Object)
```cpp
#include <iostream>
using namespace std;

class Rectangle {
public:
    // Instance variables - each object has its own copy
    double length;
    double width;
    
    double area() {
        return length * width;
    }
};

int main() {
    Rectangle rect1;
    Rectangle rect2;
    
    rect1.length = 5.0;
    rect1.width = 3.0;
    
    rect2.length = 4.0;
    rect2.width = 2.0;
    
    cout << "Rect1 area: " << rect1.area() << endl;
    cout << "Rect2 area: " << rect2.area() << endl;
    
    return 0;
}
```

### Static Member Variables (Shared Across Objects)
```cpp
#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string name;
    static int employeeCount;  // Static member - shared
    
public:
    Employee(string n) : name(n) {
        employeeCount++;
    }
    
    ~Employee() {
        employeeCount--;
    }
    
    static int getCount() {
        return employeeCount;
    }
    
    void display() {
        cout << name << " (Total: " << employeeCount << ")" << endl;
    }
};

// Initialize static member
int Employee::employeeCount = 0;

int main() {
    cout << "Initial count: " << Employee::getCount() << endl;
    
    Employee e1("John");
    Employee e2("Alice");
    Employee e3("Bob");
    
    e1.display();
    e2.display();
    e3.display();
    
    cout << "Final count: " << Employee::getCount() << endl;
    
    return 0;
}
```

### Const Member Variables
```cpp
#include <iostream>
#include <string>
using namespace std;

class Circle {
private:
    const double PI;  // Const member - must be initialized
    double radius;
    
public:
    Circle(double r) : PI(3.14159), radius(r) {
        // PI = 3.14;  // ❌ Cannot modify const after initialization
    }
    
    double area() {
        return PI * radius * radius;
    }
};

int main() {
    Circle c(5.0);
    cout << "Area: " << c.area() << endl;
    
    return 0;
}
```

### Reference Member Variables
```cpp
#include <iostream>
#include <string>
using namespace std;

class RefHolder {
private:
    int& ref;  // Reference member
    
public:
    RefHolder(int& r) : ref(r) {}  // Must initialize in constructor
    
    void display() {
        cout << "Reference value: " << ref << endl;
    }
    
    void modify() {
        ref = 100;  // Modifies original variable
    }
};

int main() {
    int value = 42;
    RefHolder holder(value);
    
    holder.display();
    holder.modify();
    
    cout << "Original value: " << value << endl;
    
    return 0;
}
```

## Member Variable Initialization

### Constructor Initialization List
```cpp
#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    const int category;
    
public:
    // Constructor with initialization list
    Product(int i, string n, double p, int c) 
        : id(i), name(n), price(p), category(c) {
        // Constructor body - can do additional initialization
        cout << "Product created: " << name << endl;
    }
    
    void display() {
        cout << "ID: " << id << ", Name: " << name 
             << ", Price: $" << price 
             << ", Category: " << category << endl;
    }
};

int main() {
    Product p1(101, "Laptop", 999.99, 1);
    Product p2(102, "Mouse", 29.99, 1);
    
    p1.display();
    p2.display();
    
    return 0;
}
```

### Default Member Initializers (C++11)
```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title = "Unknown";      // Default value
    string author = "Anonymous";    // Default value
    int pages = 0;                  // Default value
    double price = 0.0;             // Default value
    
public:
    Book() {
        cout << "Default book created" << endl;
    }
    
    Book(string t, string a, int p, double pr) 
        : title(t), author(a), pages(p), price(pr) {
        cout << "Parameterized book created" << endl;
    }
    
    void display() {
        cout << title << " by " << author 
             << ", " << pages << " pages, $" << price << endl;
    }
};

int main() {
    Book book1;
    Book book2("C++ Programming", "Bjarne Stroustrup", 1200, 59.99);
    
    book1.display();
    book2.display();
    
    return 0;
}
```

## Practical Examples

### Example 1: Student Records System
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
private:
    int id;
    string name;
    vector<double> grades;
    double average;
    
    void calculateAverage() {
        if (grades.empty()) {
            average = 0;
            return;
        }
        double sum = 0;
        for (double g : grades) {
            sum += g;
        }
        average = sum / grades.size();
    }
    
public:
    // Constructor
    Student(int i, string n) : id(i), name(n), average(0) {}
    
    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    double getAverage() const { return average; }
    const vector<double>& getGrades() const { return grades; }
    
    // Add grade
    void addGrade(double grade) {
        if (grade >= 0 && grade <= 100) {
            grades.push_back(grade);
            calculateAverage();
        }
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name << endl;
        cout << "Grades: ";
        for (double g : grades) {
            cout << g << " ";
        }
        cout << endl;
        cout << "Average: " << average << endl;
    }
};

int main() {
    Student s1(1001, "Alice");
    Student s2(1002, "Bob");
    
    s1.addGrade(85.5);
    s1.addGrade(92.0);
    s1.addGrade(78.5);
    
    s2.addGrade(90.0);
    s2.addGrade(88.5);
    
    s1.display();
    cout << endl;
    s2.display();
    
    return 0;
}
```

### Example 2: Time Class with Member Variables
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
    // Constructor with default values
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        normalize();
    }
    
    // Getters
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }
    
    // Setters with validation
    void setHours(int h) {
        if (h >= 0 && h < 24) {
            hours = h;
        }
    }
    
    void setMinutes(int m) {
        if (m >= 0 && m < 60) {
            minutes = m;
        }
    }
    
    void setSeconds(int s) {
        if (s >= 0 && s < 60) {
            seconds = s;
        }
    }
    
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
    
    void display() const {
        cout << setfill('0') 
             << setw(2) << hours << ":"
             << setw(2) << minutes << ":"
             << setw(2) << seconds << endl;
    }
};

int main() {
    Time t1(2, 30, 45);
    Time t2;  // Default: 00:00:00
    
    cout << "t1: ";
    t1.display();
    
    cout << "t2: ";
    t2.display();
    
    t1.addSeconds(45);
    t1.addMinutes(15);
    cout << "After adding time: ";
    t1.display();
    
    t2.setHours(14);
    t2.setMinutes(30);
    t2.setSeconds(0);
    cout << "t2 after setting: ";
    t2.display();
    
    return 0;
}
```

### Example 3: Inventory System with Static Members
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item {
private:
    static int nextId;
    int id;
    string name;
    double price;
    int quantity;
    static int totalItems;
    static double totalValue;
    
public:
    Item(string n, double p, int q) : name(n), price(p), quantity(q) {
        id = nextId++;
        totalItems++;
        totalValue += price * quantity;
    }
    
    ~Item() {
        totalItems--;
        totalValue -= price * quantity;
    }
    
    // Static getters
    static int getTotalItems() { return totalItems; }
    static double getTotalValue() { return totalValue; }
    
    // Instance methods
    void sell(int q) {
        if (q <= quantity) {
            quantity -= q;
            totalValue -= price * q;
        }
    }
    
    void restock(int q) {
        if (q > 0) {
            quantity += q;
            totalValue += price * q;
        }
    }
    
    void display() const {
        cout << "ID: " << id << ", " << name 
             << ", $" << price << ", Qty: " << quantity << endl;
    }
};

int Item::nextId = 1;
int Item::totalItems = 0;
double Item::totalValue = 0;

int main() {
    cout << "Initial - Items: " << Item::getTotalItems() 
         << ", Value: $" << Item::getTotalValue() << endl;
    
    Item laptop("Laptop", 999.99, 10);
    Item mouse("Mouse", 29.99, 50);
    Item keyboard("Keyboard", 79.99, 25);
    
    cout << "\nAfter adding items - Items: " << Item::getTotalItems() 
         << ", Value: $" << Item::getTotalValue() << endl;
    
    cout << "\n--- Inventory ---" << endl;
    laptop.display();
    mouse.display();
    keyboard.display();
    
    laptop.sell(2);
    cout << "\nSold 2 laptops" << endl;
    cout << "Items: " << Item::getTotalItems() 
         << ", Value: $" << Item::getTotalValue() << endl;
    
    return 0;
}
```

### Example 4: Const Member Variables and Methods
```cpp
#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    const int id;           // Const - cannot change after initialization
    const string name;      // Const - cannot change after initialization
    double salary;
    static int nextId;
    
public:
    Employee(string n, double s) : id(nextId++), name(n), salary(s) {
        if (salary < 0) salary = 0;
    }
    
    // Const member functions - promise not to modify object
    int getId() const { return id; }
    string getName() const { return name; }
    double getSalary() const { return salary; }
    
    // Non-const function - can modify
    void setSalary(double s) {
        if (s >= 0) {
            salary = s;
        }
    }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Salary: $" << salary << endl;
    }
};

int Employee::nextId = 1001;

int main() {
    const Employee emp1("John Doe", 50000);  // Const object
    Employee emp2("Jane Smith", 60000);      // Non-const object
    
    // emp1.setSalary(55000);  // ❌ Error! Can't call non-const on const object
    emp2.setSalary(65000);     // ✅ OK
    
    emp1.display();  // ✅ Can call const functions
    emp2.display();
    
    cout << "ID: " << emp1.getId() << ", Name: " << emp1.getName() << endl;
    
    return 0;
}
```

### Example 5: Class with Reference Members
```cpp
#include <iostream>
#include <string>
using namespace std;

class Logger {
public:
    void log(const string& msg) {
        cout << "[LOG] " << msg << endl;
    }
};

class DataProcessor {
private:
    Logger& logger;      // Reference to Logger
    string& data;        // Reference to external data
    int& count;          // Reference to external counter
    
public:
    DataProcessor(Logger& l, string& d, int& c) 
        : logger(l), data(d), count(c) {}
    
    void process() {
        logger.log("Processing data: " + data);
        data = data + "_processed";
        count++;
        logger.log("Count: " + to_string(count));
    }
    
    void display() const {
        cout << "Current data: " << data << endl;
        cout << "Process count: " << count << endl;
    }
};

int main() {
    Logger logger;
    string text = "Hello World";
    int counter = 0;
    
    DataProcessor processor(logger, text, counter);
    
    processor.display();
    processor.process();
    processor.display();
    
    cout << "\nOriginal text now: " << text << endl;
    cout << "Original counter: " << counter << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Forgetting to Initialize Member Variables
```cpp
class MyClass {
public:
    int value;  // Uninitialized!
    string name;  // String initialized by default constructor
};

int main() {
    MyClass obj;
    cout << obj.value;  // Garbage value!
    cout << obj.name;   // Empty string (OK)
    
    return 0;
}
```

### Mistake 2: Accessing Private Members Directly
```cpp
class Account {
private:
    double balance;
};

int main() {
    Account acc;
    acc.balance = 1000;  // ❌ Error! Private member
    
    return 0;
}
```

### Mistake 3: Using Uninitialized Reference Members
```cpp
class Holder {
    int& ref;  // Reference must be initialized
public:
    Holder() { }  // ❌ Error! ref not initialized
};

// Correct
class Holder {
    int& ref;
public:
    Holder(int& r) : ref(r) { }  // Initialize in constructor
};
```

### Mistake 4: Modifying Const Member in Const Function
```cpp
class MyClass {
    int value;
public:
    void constFunction() const {
        value = 10;  // ❌ Error! Can't modify in const function
    }
};
```

### Mistake 5: Forgetting to Define Static Members
```cpp
class MyClass {
    static int count;  // Declaration only
};

// int MyClass::count = 0;  // Missing definition!
```

## Quick Reference Table

| Member Type | Syntax | Storage | Access |
|-------------|--------|---------|--------|
| Instance | `int value;` | Per object | Through object |
| Static | `static int count;` | Shared | Through class or object |
| Const | `const int ID;` | Per object | Cannot modify |
| Reference | `int& ref;` | Per object | Must initialize |
| Public | `public: int x;` | Anywhere | Direct access |
| Private | `private: int x;` | Within class | Through methods |

## Summary

- **Member variables** store object state
- **Instance variables** - each object has own copy
- **Static variables** - shared across all objects
- **Const members** - cannot change after initialization
- **Reference members** - must be initialized in constructor
- **Private members** - encapsulated, accessed via methods
- **Protected members** - accessible in derived classes
- **Public members** - accessible anywhere
- **Initialization** - constructor initialization list or default values

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

class ClassName {
private:
    // Private member variables
    int id;
    string name;
    static int counter;
    const int version;
    
public:
    // Constructor
    ClassName(string n, int v) : name(n), version(v) {
        id = ++counter;
    }
    
    // Getters (const methods)
    int getId() const { return id; }
    string getName() const { return name; }
    int getVersion() const { return version; }
    static int getCounter() { return counter; }
    
    // Setters
    void setName(string n) { name = n; }
    
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Version: " << version << endl;
    }
};

int ClassName::counter = 0;

int main() {
    ClassName obj1("First", 1);
    ClassName obj2("Second", 2);
    
    obj1.display();
    obj2.display();
    
    cout << "Total objects: " << ClassName::getCounter() << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*