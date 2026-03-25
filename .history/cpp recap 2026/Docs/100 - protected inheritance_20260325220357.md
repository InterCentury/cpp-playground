# 100 - Protected Inheritance in C++

## What is Protected Inheritance?
Protected inheritance is a form of inheritance where public and protected members of the base class become protected members in the derived class. This establishes an "implemented-in-terms-of" relationship rather than an "is-a" relationship.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Base {
private:
    int privateVar = 1;
protected:
    int protectedVar = 2;
public:
    int publicVar = 3;
    
    void showBase() {
        cout << "Base: private=" << privateVar 
             << ", protected=" << protectedVar 
             << ", public=" << publicVar << endl;
    }
};

// Protected inheritance
class Derived : protected Base {
public:
    void showDerived() {
        // cout << privateVar;  // Error! Private not accessible
        cout << "Derived accessing protectedVar: " << protectedVar << endl;
        cout << "Derived accessing publicVar: " << publicVar << endl;
        
        // Can modify protected and public members
        protectedVar = 20;
        publicVar = 30;
    }
    
    void callBase() {
        showBase();  // Can call base class public method
    }
};

int main() {
    Base b;
    Derived d;
    
    // Base class members access
    b.publicVar = 10;      // OK
    // b.protectedVar = 20;  // Error! Protected
    
    // Derived class access through object
    // d.publicVar = 40;      // Error! publicVar became protected
    // d.protectedVar = 50;   // Error! protectedVar is protected
    // d.privateVar = 60;     // Error! private not accessible
    
    d.showDerived();        // OK - public method
    d.callBase();           // OK - public method
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### base.h
```cpp
#ifndef BASE_H
#define BASE_H

class Base {
private:
    int privateVar;
protected:
    int protectedVar;
public:
    int publicVar;
    
    Base();
    void showBase();
};

#endif
```

### base.cpp
```cpp
#include "base.h"
#include <iostream>
using namespace std;

Base::Base() : privateVar(1), protectedVar(2), publicVar(3) {}

void Base::showBase() {
    cout << "Base: private=" << privateVar 
         << ", protected=" << protectedVar 
         << ", public=" << publicVar << endl;
}
```

### derived.h
```cpp
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"

class Derived : protected Base {
public:
    void showDerived();
    void callBase();
};

#endif
```

### derived.cpp
```cpp
#include "derived.h"
#include <iostream>
using namespace std;

void Derived::showDerived() {
    cout << "Derived accessing protectedVar: " << protectedVar << endl;
    cout << "Derived accessing publicVar: " << publicVar << endl;
    protectedVar = 20;
    publicVar = 30;
}

void Derived::callBase() {
    showBase();
}
```

### main.cpp
```cpp
#include <iostream>
#include "derived.h"
using namespace std;

int main() {
    Derived d;
    d.showDerived();
    d.callBase();
    return 0;
}
```

## Public vs Protected vs Private Inheritance

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    int publicMember = 1;
protected:
    int protectedMember = 2;
private:
    int privateMember = 3;
};

// Public inheritance
class PublicDerived : public Base {
public:
    void show() {
        cout << "Public inheritance:" << endl;
        cout << "  publicMember: " << publicMember << endl;    // Public
        cout << "  protectedMember: " << protectedMember << endl; // Protected
        // cout << privateMember;  // Not accessible
    }
};

// Protected inheritance
class ProtectedDerived : protected Base {
public:
    void show() {
        cout << "Protected inheritance:" << endl;
        cout << "  publicMember: " << publicMember << endl;    // Becomes Protected
        cout << "  protectedMember: " << protectedMember << endl; // Protected
        // cout << privateMember;  // Not accessible
    }
};

// Private inheritance
class PrivateDerived : private Base {
public:
    void show() {
        cout << "Private inheritance:" << endl;
        cout << "  publicMember: " << publicMember << endl;    // Becomes Private
        cout << "  protectedMember: " << protectedMember << endl; // Becomes Private
        // cout << privateMember;  // Not accessible
    }
};

int main() {
    PublicDerived pub;
    ProtectedDerived prot;
    PrivateDerived priv;
    
    pub.publicMember = 10;     // OK
    // pub.protectedMember = 20;  // Error
    
    // prot.publicMember = 10;    // Error - became protected
    // priv.publicMember = 10;    // Error - became private
    
    pub.show();
    prot.show();
    priv.show();
    
    return 0;
}
```

## Access in Further Derived Classes

```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    int baseProtected = 10;
public:
    int basePublic = 20;
};

// Protected inheritance
class Derived : protected Base {
public:
    void derivedAccess() {
        cout << "Derived: " << baseProtected << ", " << basePublic << endl;
    }
};

// Further derived class
class MoreDerived : public Derived {
public:
    void moreDerivedAccess() {
        // Can access baseProtected and basePublic because they are
        // still protected in Derived (protected inheritance preserves protection)
        cout << "MoreDerived: " << baseProtected << ", " << basePublic << endl;
    }
};

int main() {
    Derived d;
    MoreDerived md;
    
    d.derivedAccess();
    md.moreDerivedAccess();
    
    // Cannot access from outside
    // d.baseProtected;  // Error
    // d.basePublic;     // Error
    
    return 0;
}
```

## Practical Examples

### Example 1: Stack Implementation with Protected Inheritance

#### Type 1: Single File
```cpp
#include <iostream>
#include <vector>
using namespace std;

// Base container class
class Container {
protected:
    vector<int> data;
    
public:
    void add(int value) {
        data.push_back(value);
        cout << "Added: " << value << endl;
    }
    
    int size() const {
        return data.size();
    }
    
    void clear() {
        data.clear();
        cout << "Container cleared" << endl;
    }
    
    void display() const {
        for (int v : data) {
            cout << v << " ";
        }
        cout << endl;
    }
};

// Stack using protected inheritance (implemented-in-terms-of)
class Stack : protected Container {
public:
    void push(int value) {
        add(value);
    }
    
    int pop() {
        if (size() == 0) {
            cout << "Stack underflow!" << endl;
            return -1;
        }
        int value = data.back();
        data.pop_back();
        return value;
    }
    
    int top() const {
        if (size() == 0) {
            cout << "Stack empty!" << endl;
            return -1;
        }
        return data.back();
    }
    
    bool isEmpty() const {
        return size() == 0;
    }
    
    int getSize() const {
        return size();
    }
    
    void show() const {
        cout << "Stack (top to bottom): ";
        for (int i = data.size() - 1; i >= 0; i--) {
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
    
    s.show();
    
    cout << "Top: " << s.top() << endl;
    cout << "Pop: " << s.pop() << endl;
    cout << "Pop: " << s.pop() << endl;
    
    s.show();
    cout << "Size: " << s.getSize() << endl;
    
    // Cannot access Container's methods directly
    // s.add(40);    // Error! add is protected
    // s.clear();    // Error! clear is protected
    
    return 0;
}
```

#### Type 2: Multiple Files

**container.h**
```cpp
#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
using namespace std;

class Container {
protected:
    vector<int> data;
    
public:
    void add(int value);
    int size() const;
    void clear();
    void display() const;
};

#endif
```

**container.cpp**
```cpp
#include "container.h"
#include <iostream>
using namespace std;

void Container::add(int value) {
    data.push_back(value);
    cout << "Added: " << value << endl;
}

int Container::size() const {
    return data.size();
}

void Container::clear() {
    data.clear();
    cout << "Container cleared" << endl;
}

void Container::display() const {
    for (int v : data) {
        cout << v << " ";
    }
    cout << endl;
}
```

**stack.h**
```cpp
#ifndef STACK_H
#define STACK_H

#include "container.h"

class Stack : protected Container {
public:
    void push(int value);
    int pop();
    int top() const;
    bool isEmpty() const;
    int getSize() const;
    void show() const;
};

#endif
```

**stack.cpp**
```cpp
#include "stack.h"
#include <iostream>
using namespace std;

void Stack::push(int value) {
    add(value);
}

int Stack::pop() {
    if (size() == 0) {
        cout << "Stack underflow!" << endl;
        return -1;
    }
    int value = data.back();
    data.pop_back();
    return value;
}

int Stack::top() const {
    if (size() == 0) {
        cout << "Stack empty!" << endl;
        return -1;
    }
    return data.back();
}

bool Stack::isEmpty() const {
    return size() == 0;
}

int Stack::getSize() const {
    return size();
}

void Stack::show() const {
    cout << "Stack (top to bottom): ";
    for (int i = data.size() - 1; i >= 0; i--) {
        cout << data[i] << " ";
    }
    cout << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "stack.h"
using namespace std;

int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.show();
    cout << "Pop: " << s.pop() << endl;
    s.show();
    return 0;
}
```

### Example 2: Queue Implementation with Protected Inheritance

#### Type 1: Single File
```cpp
#include <iostream>
#include <deque>
using namespace std;

// Base class
class Sequence {
protected:
    deque<int> elements;
    
public:
    void addFront(int value) {
        elements.push_front(value);
        cout << "Added to front: " << value << endl;
    }
    
    void addBack(int value) {
        elements.push_back(value);
        cout << "Added to back: " << value << endl;
    }
    
    int removeFront() {
        if (elements.empty()) return -1;
        int value = elements.front();
        elements.pop_front();
        return value;
    }
    
    int removeBack() {
        if (elements.empty()) return -1;
        int value = elements.back();
        elements.pop_back();
        return value;
    }
    
    bool isEmpty() const {
        return elements.empty();
    }
    
    int getSize() const {
        return elements.size();
    }
    
    void display() const {
        for (int v : elements) {
            cout << v << " ";
        }
        cout << endl;
    }
};

// Queue using protected inheritance
class Queue : protected Sequence {
public:
    void enqueue(int value) {
        addBack(value);
    }
    
    int dequeue() {
        return removeFront();
    }
    
    int front() const {
        if (isEmpty()) return -1;
        return elements.front();
    }
    
    bool isEmpty() const {
        return Sequence::isEmpty();
    }
    
    int getSize() const {
        return Sequence::getSize();
    }
    
    void show() const {
        cout << "Queue (front to back): ";
        display();
    }
};

int main() {
    Queue q;
    
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    
    q.show();
    
    cout << "Front: " << q.front() << endl;
    cout << "Dequeue: " << q.dequeue() << endl;
    cout << "Dequeue: " << q.dequeue() << endl;
    
    q.show();
    cout << "Size: " << q.getSize() << endl;
    
    // Cannot access Sequence methods directly
    // q.addFront(40);   // Error! addFront is protected
    // q.removeBack();   // Error! removeBack is protected
    
    return 0;
}
```

#### Type 2: Multiple Files

**sequence.h**
```cpp
#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <deque>
using namespace std;

class Sequence {
protected:
    deque<int> elements;
    
public:
    void addFront(int value);
    void addBack(int value);
    int removeFront();
    int removeBack();
    bool isEmpty() const;
    int getSize() const;
    void display() const;
};

#endif
```

**sequence.cpp**
```cpp
#include "sequence.h"
#include <iostream>
using namespace std;

void Sequence::addFront(int value) {
    elements.push_front(value);
    cout << "Added to front: " << value << endl;
}

void Sequence::addBack(int value) {
    elements.push_back(value);
    cout << "Added to back: " << value << endl;
}

int Sequence::removeFront() {
    if (elements.empty()) return -1;
    int value = elements.front();
    elements.pop_front();
    return value;
}

int Sequence::removeBack() {
    if (elements.empty()) return -1;
    int value = elements.back();
    elements.pop_back();
    return value;
}

bool Sequence::isEmpty() const {
    return elements.empty();
}

int Sequence::getSize() const {
    return elements.size();
}

void Sequence::display() const {
    for (int v : elements) {
        cout << v << " ";
    }
    cout << endl;
}
```

**queue.h**
```cpp
#ifndef QUEUE_H
#define QUEUE_H

#include "sequence.h"

class Queue : protected Sequence {
public:
    void enqueue(int value);
    int dequeue();
    int front() const;
    bool isEmpty() const;
    int getSize() const;
    void show() const;
};

#endif
```

**queue.cpp**
```cpp
#include "queue.h"
#include <iostream>
using namespace std;

void Queue::enqueue(int value) {
    addBack(value);
}

int Queue::dequeue() {
    return removeFront();
}

int Queue::front() const {
    if (isEmpty()) return -1;
    return elements.front();
}

bool Queue::isEmpty() const {
    return Sequence::isEmpty();
}

int Queue::getSize() const {
    return Sequence::getSize();
}

void Queue::show() const {
    cout << "Queue (front to back): ";
    display();
}
```

**main.cpp**
```cpp
#include <iostream>
#include "queue.h"
using namespace std;

int main() {
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.show();
    cout << "Dequeue: " << q.dequeue() << endl;
    q.show();
    return 0;
}
```

### Example 3: Logger Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

// Base logger class
class Logger {
protected:
    string name;
    int logLevel;
    
    string getTimestamp() {
        time_t now = time(0);
        return ctime(&now);
    }
    
public:
    Logger(string n, int level = 1) : name(n), logLevel(level) {
        cout << "Logger created: " << name << endl;
    }
    
    virtual void log(const string& message, int level = 1) {
        if (level >= logLevel) {
            cout << "[" << getTimestamp() << "] " << name << ": " << message;
        }
    }
    
    virtual ~Logger() {
        cout << "Logger destroyed: " << name << endl;
    }
};

// File logger using protected inheritance
class FileLogger : protected Logger {
private:
    ofstream file;
    string filename;
    
public:
    FileLogger(string n, string fname, int level = 1) 
        : Logger(n, level), filename(fname) {
        file.open(filename, ios::app);
        cout << "FileLogger created: logging to " << filename << endl;
    }
    
    void writeLog(const string& message, int level = 1) {
        if (level >= logLevel) {
            string timestamp = getTimestamp();
            file << "[" << timestamp << "] " << name << ": " << message;
            file.flush();
        }
    }
    
    void setLogLevel(int level) {
        logLevel = level;
    }
    
    void close() {
        if (file.is_open()) {
            file.close();
            cout << "File closed" << endl;
        }
    }
    
    ~FileLogger() {
        close();
        cout << "FileLogger destroyed" << endl;
    }
};

// Database logger
class DBLogger : protected Logger {
private:
    string connectionString;
    bool connected;
    
public:
    DBLogger(string n, string conn, int level = 1) 
        : Logger(n, level), connectionString(conn), connected(false) {
        cout << "DBLogger created: connecting to " << conn << endl;
        connected = true;
    }
    
    void writeLog(const string& message, int level = 1) {
        if (level >= logLevel && connected) {
            string timestamp = getTimestamp();
            cout << "[DB] Inserting log: " << name << " - " << message;
        }
    }
    
    void setLogLevel(int level) {
        logLevel = level;
    }
    
    void disconnect() {
        connected = false;
        cout << "Disconnected from database" << endl;
    }
    
    ~DBLogger() {
        disconnect();
        cout << "DBLogger destroyed" << endl;
    }
};

int main() {
    FileLogger fileLog("AppLog", "app.log", 2);
    DBLogger dbLog("SystemLog", "postgresql://localhost/logs", 1);
    
    fileLog.writeLog("Application started", 1);
    fileLog.writeLog("User logged in", 2);
    fileLog.writeLog("Error occurred", 3);
    
    dbLog.writeLog("System initialized", 1);
    dbLog.writeLog("Memory usage: 45%", 2);
    
    fileLog.setLogLevel(3);
    fileLog.writeLog("This won't be logged", 2);
    
    fileLog.close();
    dbLog.disconnect();
    
    return 0;
}
```

#### Type 2: Multiple Files

**logger.h**
```cpp
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
using namespace std;

class Logger {
protected:
    string name;
    int logLevel;
    
    string getTimestamp();
    
public:
    Logger(string n, int level = 1);
    virtual void log(const string& message, int level = 1);
    virtual ~Logger();
};

#endif
```

**logger.cpp**
```cpp
#include "logger.h"
#include <iostream>
#include <ctime>
using namespace std;

Logger::Logger(string n, int level) : name(n), logLevel(level) {
    cout << "Logger created: " << name << endl;
}

string Logger::getTimestamp() {
    time_t now = time(0);
    return ctime(&now);
}

void Logger::log(const string& message, int level) {
    if (level >= logLevel) {
        cout << "[" << getTimestamp() << "] " << name << ": " << message;
    }
}

Logger::~Logger() {
    cout << "Logger destroyed: " << name << endl;
}
```

**filelogger.h**
```cpp
#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "logger.h"
#include <fstream>
#include <string>
using namespace std;

class FileLogger : protected Logger {
private:
    ofstream file;
    string filename;
    
public:
    FileLogger(string n, string fname, int level = 1);
    void writeLog(const string& message, int level = 1);
    void setLogLevel(int level);
    void close();
    ~FileLogger();
};

#endif
```

**filelogger.cpp**
```cpp
#include "filelogger.h"
#include <iostream>
using namespace std;

FileLogger::FileLogger(string n, string fname, int level) 
    : Logger(n, level), filename(fname) {
    file.open(filename, ios::app);
    cout << "FileLogger created: logging to " << filename << endl;
}

void FileLogger::writeLog(const string& message, int level) {
    if (level >= logLevel) {
        string timestamp = getTimestamp();
        file << "[" << timestamp << "] " << name << ": " << message;
        file.flush();
    }
}

void FileLogger::setLogLevel(int level) {
    logLevel = level;
}

void FileLogger::close() {
    if (file.is_open()) {
        file.close();
        cout << "File closed" << endl;
    }
}

FileLogger::~FileLogger() {
    close();
    cout << "FileLogger destroyed" << endl;
}
```

**dblogger.h**
```cpp
#ifndef DBLOGGER_H
#define DBLOGGER_H

#include "logger.h"
#include <string>
using namespace std;

class DBLogger : protected Logger {
private:
    string connectionString;
    bool connected;
    
public:
    DBLogger(string n, string conn, int level = 1);
    void writeLog(const string& message, int level = 1);
    void setLogLevel(int level);
    void disconnect();
    ~DBLogger();
};

#endif
```

**dblogger.cpp**
```cpp
#include "dblogger.h"
#include <iostream>
using namespace std;

DBLogger::DBLogger(string n, string conn, int level) 
    : Logger(n, level), connectionString(conn), connected(false) {
    cout << "DBLogger created: connecting to " << conn << endl;
    connected = true;
}

void DBLogger::writeLog(const string& message, int level) {
    if (level >= logLevel && connected) {
        string timestamp = getTimestamp();
        cout << "[DB] Inserting log: " << name << " - " << message;
    }
}

void DBLogger::setLogLevel(int level) {
    logLevel = level;
}

void DBLogger::disconnect() {
    connected = false;
    cout << "Disconnected from database" << endl;
}

DBLogger::~DBLogger() {
    disconnect();
    cout << "DBLogger destroyed" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "filelogger.h"
#include "dblogger.h"
using namespace std;

int main() {
    FileLogger fileLog("AppLog", "app.log", 2);
    DBLogger dbLog("SystemLog", "postgresql://localhost/logs", 1);
    
    fileLog.writeLog("Application started", 1);
    fileLog.writeLog("User logged in", 2);
    dbLog.writeLog("System initialized", 1);
    
    fileLog.close();
    dbLog.disconnect();
    
    return 0;
}
```

## Access Table Summary

| Inheritance Type | Base Class Member | Access in Derived Class | Access Outside |
|------------------|-------------------|-------------------------|----------------|
| Public | public | public | Yes |
| Public | protected | protected | No |
| Public | private | private | No |
| Protected | public | protected | No |
| Protected | protected | protected | No |
| Protected | private | private | No |
| Private | public | private | No |
| Private | protected | private | No |
| Private | private | private | No |

## When to Use Protected Inheritance

### ✅ Good Uses
```cpp
// "Implemented-in-terms-of" relationship
class Stack : protected Vector { };

// When you want to hide interface but allow further derivation
class Base : protected Implementation { };

// Reusing implementation without exposing interface
class Timer : protected Clock { };
```

### ❌ Avoid
```cpp
// When "is-a" relationship exists (use public inheritance)
class Dog : protected Animal { };  // Should be public

// When you need to use objects polymorphically
void process(Base* b);  // Can't pass ProtectedDerived*

// When interface needs to be exposed
class String : protected vector<char> { };  // Should use composition
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Using protected inheritance for polymorphism | Cannot use base class pointers | Use public inheritance |
| Expecting public interface | Members become protected | Use public inheritance or provide accessors |
| Confusing with composition | Wrong relationship | Use composition for "has-a" |
| Overusing protected inheritance | Complex hierarchies | Prefer composition when possible |

## Summary

- **Protected inheritance** makes public members become protected
- Establishes **"implemented-in-terms-of"** relationship
- Not an **"is-a"** relationship (no polymorphism with base pointers)
- Further derived classes can still access members
- Useful for **implementation reuse** without exposing interface
- Use when you want to **hide interface** but allow further derivation

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class Base {
protected:
    int value;
    
public:
    Base(int v) : value(v) {}
    void showBase() { cout << "Base: " << value << endl; }
};

class Derived : protected Base {
public:
    Derived(int v) : Base(v) {}
    
    void showDerived() {
        cout << "Derived accessing: " << value << endl;
        showBase();
    }
};

int main() {
    Derived d(42);
    d.showDerived();
    // d.value;      // Error! Protected
    // d.showBase(); // Error! Protected
    return 0;
}
```

### Type 2: Multiple Files

**base.h**
```cpp
#ifndef BASE_H
#define BASE_H

class Base {
protected:
    int value;
    
public:
    Base(int v);
    void showBase();
};

#endif
```

**base.cpp**
```cpp
#include "base.h"
#include <iostream>
using namespace std;

Base::Base(int v) : value(v) {}

void Base::showBase() {
    cout << "Base: " << value << endl;
}
```

**derived.h**
```cpp
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"

class Derived : protected Base {
public:
    Derived(int v);
    void showDerived();
};

#endif
```

**derived.cpp**
```cpp
#include "derived.h"
#include <iostream>
using namespace std;

Derived::Derived(int v) : Base(v) {}

void Derived::showDerived() {
    cout << "Derived accessing: " << value << endl;
    showBase();
}
```

**main.cpp**
```cpp
#include <iostream>
#include "derived.h"
using namespace std;

int main() {
    Derived d(42);
    d.showDerived();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*