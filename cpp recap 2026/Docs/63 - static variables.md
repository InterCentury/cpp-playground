# 63 - Static Variables in C++

## What are Static Variables?
Static variables retain their value between function calls. Unlike regular local variables that are created and destroyed each time a function is called, static variables are initialized only once and persist throughout the program's lifetime.

## Basic Syntax

```cpp
static data_type variable_name = initial_value;
```

## Simple Example - Static Local Variable

```cpp
#include <iostream>
using namespace std;

void counter() {
    static int count = 0;  // Static local - initialized only once
    count++;
    cout << "Function called " << count << " times" << endl;
}

int main() {
    counter();  // Called 1 times
    counter();  // Called 2 times
    counter();  // Called 3 times
    
    return 0;
}
```

## Static vs Regular Local Variables

```cpp
#include <iostream>
using namespace std;

void regularCounter() {
    int count = 0;  // Regular local - recreated each call
    count++;
    cout << "Regular: " << count << endl;
}

void staticCounter() {
    static int count = 0;  // Static local - persists between calls
    count++;
    cout << "Static: " << count << endl;
}

int main() {
    cout << "Regular counter:" << endl;
    regularCounter();
    regularCounter();
    regularCounter();
    
    cout << "\nStatic counter:" << endl;
    staticCounter();
    staticCounter();
    staticCounter();
    
    return 0;
}
```

## Static Local Variables in Different Contexts

### Example 1: Function Call Counter
```cpp
#include <iostream>
using namespace std;

int getNextId() {
    static int nextId = 1;  // Static counter
    return nextId++;
}

int main() {
    cout << "IDs: ";
    for (int i = 0; i < 10; i++) {
        cout << getNextId() << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 2: Caching Results (Memoization)
```cpp
#include <iostream>
#include <cmath>
using namespace std;

double calculateE(int iterations) {
    static double result = 0.0;
    static int lastIteration = 0;
    
    if (iterations <= lastIteration) {
        cout << "Using cached result" << endl;
        return result;
    }
    
    cout << "Calculating from scratch..." << endl;
    result = 0.0;
    for (int i = lastIteration; i < iterations; i++) {
        result += 1.0 / tgamma(i + 1);
    }
    lastIteration = iterations;
    
    return result;
}

int main() {
    cout << "e (10 terms): " << calculateE(10) << endl;
    cout << "e (20 terms): " << calculateE(20) << endl;
    cout << "e (10 terms again): " << calculateE(10) << endl;
    
    return 0;
}
```

### Example 3: Generating Sequential IDs
```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int id;
    string name;
    
public:
    Student(string n) : name(n) {
        static int nextId = 1000;  // Static counter for all objects
        id = nextId++;
    }
    
    void display() {
        cout << "ID: " << id << ", Name: " << name << endl;
    }
};

int main() {
    Student s1("John");
    Student s2("Jane");
    Student s3("Bob");
    
    s1.display();
    s2.display();
    s3.display();
    
    return 0;
}
```

## Static Global Variables

Static global variables are only accessible within the file they are declared in.

**file1.cpp**
```cpp
#include <iostream>
using namespace std;

static int fileCounter = 0;  // Only visible in this file

void incrementFile1() {
    fileCounter++;
    cout << "File1 counter: " << fileCounter << endl;
}
```

**file2.cpp**
```cpp
#include <iostream>
using namespace std;

static int fileCounter = 0;  // Separate counter for this file

void incrementFile2() {
    fileCounter++;
    cout << "File2 counter: " << fileCounter << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
using namespace std;

// Can't access fileCounter from file1 or file2 directly
// They are private to their respective files

void incrementFile1();  // Declaration
void incrementFile2();  // Declaration

int main() {
    incrementFile1();  // 1
    incrementFile1();  // 2
    incrementFile2();  // 1
    incrementFile2();  // 2
    incrementFile1();  // 3
    
    return 0;
}
```

## Static Member Variables in Classes

Static member variables are shared across all objects of a class.

```cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string owner;
    double balance;
    static double interestRate;  // Shared by all accounts
    static int accountCount;      // Shared counter
    
public:
    BankAccount(string name, double initial) : owner(name), balance(initial) {
        accountCount++;
    }
    
    static void setInterestRate(double rate) {
        interestRate = rate;
    }
    
    static int getAccountCount() {
        return accountCount;
    }
    
    void addInterest() {
        balance += balance * interestRate;
    }
    
    void display() {
        cout << owner << ": $" << balance << endl;
    }
};

// Define static members outside class
double BankAccount::interestRate = 0.05;
int BankAccount::accountCount = 0;

int main() {
    BankAccount acc1("John", 1000);
    BankAccount acc2("Jane", 2000);
    BankAccount acc3("Bob", 1500);
    
    cout << "Total accounts: " << BankAccount::getAccountCount() << endl;
    
    BankAccount::setInterestRate(0.10);  // Change rate for all
    
    acc1.addInterest();
    acc2.addInterest();
    acc3.addInterest();
    
    acc1.display();
    acc2.display();
    acc3.display();
    
    return 0;
}
```

## Static Member Functions

Static member functions can be called without an object and can only access static members.

```cpp
#include <iostream>
#include <string>
using namespace std;

class MathUtils {
public:
    static const double PI;
    static const double E;
    
    static double square(double x) {
        return x * x;
    }
    
    static double cube(double x) {
        return x * x * x;
    }
    
    static double circleArea(double radius) {
        return PI * radius * radius;
    }
    
    static double circleCircumference(double radius) {
        return 2 * PI * radius;
    }
};

const double MathUtils::PI = 3.14159;
const double MathUtils::E = 2.71828;

int main() {
    // Call static methods without creating object
    cout << "Square of 5: " << MathUtils::square(5) << endl;
    cout << "Cube of 3: " << MathUtils::cube(3) << endl;
    cout << "Circle area (r=5): " << MathUtils::circleArea(5) << endl;
    cout << "PI: " << MathUtils::PI << endl;
    cout << "E: " << MathUtils::E << endl;
    
    return 0;
}
```

## Static Variables in Functions vs Static Variables in Classes

```cpp
#include <iostream>
using namespace std;

// Static local variable in function
int getNextID() {
    static int id = 0;
    return id++;
}

// Static member variable in class
class IDGenerator {
private:
    static int nextID;
    
public:
    static int getNext() {
        return nextID++;
    }
};

int IDGenerator::nextID = 1000;

int main() {
    cout << "Function static:" << endl;
    cout << getNextID() << endl;  // 0
    cout << getNextID() << endl;  // 1
    cout << getNextID() << endl;  // 2
    
    cout << "\nClass static:" << endl;
    cout << IDGenerator::getNext() << endl;  // 1000
    cout << IDGenerator::getNext() << endl;  // 1001
    cout << IDGenerator::getNext() << endl;  // 1002
    
    return 0;
}
```

## Practical Examples

### Example 1: Logger with Static Counter
```cpp
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Logger {
private:
    static int logCount;
    
public:
    static void log(string message, string level = "INFO") {
        logCount++;
        time_t now = time(0);
        char* dt = ctime(&now);
        dt[strlen(dt) - 1] = '\0';
        
        cout << "[" << dt << "] [" << level << "] " 
             << message << " (Log #" << logCount << ")" << endl;
    }
    
    static int getLogCount() {
        return logCount;
    }
};

int Logger::logCount = 0;

int main() {
    Logger::log("Application started");
    Logger::log("User logged in", "INFO");
    Logger::log("Database connection failed", "ERROR");
    Logger::log("Application exiting", "WARNING");
    
    cout << "\nTotal logs: " << Logger::getLogCount() << endl;
    
    return 0;
}
```

### Example 2: Singleton Pattern
```cpp
#include <iostream>
#include <string>
using namespace std;

class Configuration {
private:
    static Configuration* instance;
    string setting;
    
    // Private constructor (prevents direct creation)
    Configuration() : setting("Default") {}
    
public:
    static Configuration* getInstance() {
        if (instance == nullptr) {
            instance = new Configuration();
        }
        return instance;
    }
    
    string getSetting() { return setting; }
    void setSetting(string s) { setting = s; }
    
    ~Configuration() {
        if (instance) delete instance;
    }
};

Configuration* Configuration::instance = nullptr;

int main() {
    // Can't create object directly - must use getInstance()
    Configuration* config1 = Configuration::getInstance();
    Configuration* config2 = Configuration::getInstance();
    
    cout << "config1 setting: " << config1->getSetting() << endl;
    config1->setSetting("Production");
    cout << "config2 setting: " << config2->getSetting() << endl;
    
    // Both pointers point to same object
    cout << "Same instance? " << (config1 == config2 ? "Yes" : "No") << endl;
    
    return 0;
}
```

### Example 3: Random Number Generator with Static Seed
```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Random {
private:
    static bool seeded;
    
public:
    static int get(int min, int max) {
        if (!seeded) {
            srand(time(0));
            seeded = true;
        }
        return min + rand() % (max - min + 1);
    }
    
    static double getDouble(double min, double max) {
        if (!seeded) {
            srand(time(0));
            seeded = true;
        }
        return min + (double)rand() / RAND_MAX * (max - min);
    }
};

bool Random::seeded = false;

int main() {
    cout << "Random integers (1-100):" << endl;
    for (int i = 0; i < 5; i++) {
        cout << Random::get(1, 100) << " ";
    }
    cout << endl;
    
    cout << "\nRandom doubles (0.0-1.0):" << endl;
    for (int i = 0; i < 5; i++) {
        cout << Random::getDouble(0.0, 1.0) << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 4: Static Factory Method
```cpp
#include <iostream>
#include <string>
using namespace std;

class Shape {
protected:
    string type;
    
public:
    Shape(string t) : type(t) {}
    virtual void draw() = 0;
    
    static Shape* createCircle(double radius);
    static Shape* createRectangle(double width, double height);
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : Shape("Circle"), radius(r) {}
    
    void draw() override {
        cout << "Drawing Circle with radius " << radius << endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) {}
    
    void draw() override {
        cout << "Drawing Rectangle " << width << "x" << height << endl;
    }
};

Shape* Shape::createCircle(double radius) {
    return new Circle(radius);
}

Shape* Shape::createRectangle(double width, double height) {
    return new Rectangle(width, height);
}

int main() {
    Shape* shapes[3];
    
    shapes[0] = Shape::createCircle(5);
    shapes[1] = Shape::createRectangle(4, 6);
    shapes[2] = Shape::createCircle(3);
    
    for (int i = 0; i < 3; i++) {
        shapes[i]->draw();
    }
    
    // Clean up
    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }
    
    return 0;
}
```

### Example 5: Static Array for Memory Pool
```cpp
#include <iostream>
using namespace std;

class MemoryPool {
private:
    static const int POOL_SIZE = 100;
    static int pool[POOL_SIZE];
    static int nextFree;
    
public:
    static int* allocate() {
        if (nextFree < POOL_SIZE) {
            return &pool[nextFree++];
        }
        return nullptr;
    }
    
    static void reset() {
        nextFree = 0;
    }
    
    static int getUsedCount() {
        return nextFree;
    }
    
    static int getFreeCount() {
        return POOL_SIZE - nextFree;
    }
};

int MemoryPool::pool[MemoryPool::POOL_SIZE];
int MemoryPool::nextFree = 0;

int main() {
    cout << "Free slots: " << MemoryPool::getFreeCount() << endl;
    
    int* p1 = MemoryPool::allocate();
    int* p2 = MemoryPool::allocate();
    int* p3 = MemoryPool::allocate();
    
    *p1 = 10;
    *p2 = 20;
    *p3 = 30;
    
    cout << "Used slots: " << MemoryPool::getUsedCount() << endl;
    cout << "Free slots: " << MemoryPool::getFreeCount() << endl;
    cout << "Values: " << *p1 << ", " << *p2 << ", " << *p3 << endl;
    
    MemoryPool::reset();
    cout << "\nAfter reset - used slots: " << MemoryPool::getUsedCount() << endl;
    
    return 0;
}
```

## Static vs Regular Variables Summary

| Feature | Static Local | Regular Local | Static Global | Regular Global |
|---------|--------------|---------------|---------------|----------------|
| Initialization | Once | Each call | Once | Once |
| Lifetime | Program lifetime | Function call | Program lifetime | Program lifetime |
| Scope | Function only | Function only | File only | Entire program |
| Default value | 0 | Garbage | 0 | 0 |
| Memory | Data segment | Stack | Data segment | Data segment |
| Persistence | Between calls | No | Yes | Yes |

## Common Mistakes

### Mistake 1: Using Static for Everything
```cpp
// WRONG - unnecessary static
void badFunction() {
    static int x = 10;  // Doesn't need to be static
    x++;
    cout << x << endl;
}

// BETTER - regular local
void goodFunction() {
    int x = 10;  // Will be 10 each call
    x++;
    cout << x << endl;
}
```

### Mistake 2: Forgetting to Define Static Members
```cpp
class MyClass {
    static int counter;  // Declaration only
};

// WRONG - missing definition
// int MyClass::counter;  // Must define!

// CORRECT
int MyClass::counter = 0;
```

### Mistake 3: Initializing Static Local with Non-Constant
```cpp
// WRONG - dynamic initialization
void bad() {
    static int x = rand();  // OK actually, but initialized once
    // This works, but be aware it's initialized only once
}

// OK - fine for random seed
void good() {
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
}
```

### Mistake 4: Static in Header Without Definition
```cpp
// header.h
class MyClass {
    static int value;  // Declaration only - OK
};

// WRONG - missing definition in .cpp
// int MyClass::value = 0;  // Must be in .cpp
```

## When to Use Static Variables

### ✅ Good Uses
```cpp
// Function call counter
int getCallCount() {
    static int count = 0;
    return ++count;
}

// Caching results
double computeExpensive() {
    static double cached = 0.0;
    if (cached == 0.0) {
        cached = expensiveCalculation();
    }
    return cached;
}

// Singleton pattern
static MyClass* getInstance() {
    static MyClass instance;
    return &instance;
}

// File-scoped variables (static global)
static int fileCounter = 0;  // Only visible in this file
```

### ❌ Poor Uses
```cpp
// Simple counter that should be parameter
void process(int n) {
    static int count = 0;  // Should be parameter or return value
    count += n;
}

// Replacing proper class design
void manageData() {
    static vector<int> data;  // Should be class member
    data.push_back(42);
}
```

## Quick Reference

| Declaration | Scope | Lifetime | Default |
|-------------|-------|----------|---------|
| `static int x;` (local) | Function | Program | 0 |
| `static int x;` (global) | File | Program | 0 |
| `static int x = 5;` | File/Function | Program | 5 |
| `class::staticMember` | Class | Program | Must define |

## Summary

- **Static local variables** retain value between function calls
- Initialized only **once**, first time function is called
- **Static global variables** are limited to the file they're declared in
- **Static class members** are shared across all objects
- **Static member functions** can be called without an object
- Used for **counters**, **caching**, **singletons**, **utility functions**
- **Thread safety** considerations for multi-threaded programs
- **Prefer local variables** unless static behavior is needed

## Basic Template
```cpp
#include <iostream>
using namespace std;

// Static local variable
int getNextID() {
    static int nextID = 1;  // Initialized only once
    return nextID++;
}

// Static global (file scope)
static int fileCounter = 0;

void incrementFileCounter() {
    fileCounter++;
}

// Static class members
class Utility {
public:
    static int callCount;
    static void process() {
        callCount++;
    }
};

int Utility::callCount = 0;  // Definition

int main() {
    // Static local demo
    cout << "Static local IDs:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << getNextID() << " ";
    }
    cout << endl;
    
    // Static global demo
    incrementFileCounter();
    incrementFileCounter();
    cout << "File counter: " << fileCounter << endl;
    
    // Static class member demo
    Utility::process();
    Utility::process();
    Utility::process();
    cout << "Class call count: " << Utility::callCount << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*