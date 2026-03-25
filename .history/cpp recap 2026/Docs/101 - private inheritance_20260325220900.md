# 101 - Private Inheritance in C++

## What is Private Inheritance?
Private inheritance is a form of inheritance where all members of the base class become private in the derived class. This establishes an "implemented-in-terms-of" relationship, similar to composition, but with access to protected members and the ability to override virtual functions.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Base class
class Array {
protected:
    vector<int> data;
    
public:
    void add(int value) {
        data.push_back(value);
        cout << "Added: " << value << endl;
    }
    
    int get(int index) const {
        if (index >= 0 && index < data.size()) {
            return data[index];
        }
        return -1;
    }
    
    int size() const {
        return data.size();
    }
    
    void display() const {
        for (int v : data) {
            cout << v << " ";
        }
        cout << endl;
    }
};

// Private inheritance - all Array members become private
class Stack : private Array {
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
    
    // Cannot access Array's members
    // s.add(40);    // Error! add is private
    // s.display();  // Error! display is private
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### array.h
```cpp
#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
using namespace std;

class Array {
protected:
    vector<int> data;
    
public:
    void add(int value);
    int get(int index) const;
    int size() const;
    void display() const;
};

#endif
```

### array.cpp
```cpp
#include "array.h"
#include <iostream>
using namespace std;

void Array::add(int value) {
    data.push_back(value);
    cout << "Added: " << value << endl;
}

int Array::get(int index) const {
    if (index >= 0 && index < data.size()) {
        return data[index];
    }
    return -1;
}

int Array::size() const {
    return data.size();
}

void Array::display() const {
    for (int v : data) {
        cout << v << " ";
    }
    cout << endl;
}
```

### stack.h
```cpp
#ifndef STACK_H
#define STACK_H

#include "array.h"

class Stack : private Array {
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

### stack.cpp
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

### main.cpp
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

## Private vs Protected vs Public Inheritance

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

// Private inheritance
class Derived : private Base {
public:
    void derivedAccess() {
        cout << "Derived: " << baseProtected << ", " << basePublic << endl;
    }
};

// Further derived class - cannot access Base members!
class MoreDerived : public Derived {
public:
    void moreDerivedAccess() {
        // Cannot access baseProtected or basePublic here
        // because they are private in Derived
        // cout << baseProtected;  // Error!
        // cout << basePublic;     // Error!
        cout << "MoreDerived cannot access Base members" << endl;
    }
};

int main() {
    Derived d;
    MoreDerived md;
    
    d.derivedAccess();
    md.moreDerivedAccess();
    
    return 0;
}
```

## Practical Examples

### Example 1: Timer Implementation

#### Type 1: Single File
```cpp
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

// Base timer class
class TimerBase {
protected:
    chrono::steady_clock::time_point startTime;
    bool running;
    
public:
    TimerBase() : running(false) {}
    
    void start() {
        startTime = chrono::steady_clock::now();
        running = true;
        cout << "Timer started" << endl;
    }
    
    double elapsed() const {
        if (running) {
            auto now = chrono::steady_clock::now();
            return chrono::duration<double>(now - startTime).count();
        }
        return 0;
    }
    
    void stop() {
        running = false;
        cout << "Timer stopped" << endl;
    }
};

// Stopwatch using private inheritance
class Stopwatch : private TimerBase {
private:
    double totalTime;
    
public:
    Stopwatch() : totalTime(0) {}
    
    void startWatch() {
        start();
    }
    
    void stopWatch() {
        totalTime += elapsed();
        stop();
        cout << "Lap time: " << elapsed() << " seconds" << endl;
    }
    
    void reset() {
        totalTime = 0;
        cout << "Stopwatch reset" << endl;
    }
    
    double getTotalTime() const {
        return totalTime;
    }
    
    void lap() {
        if (running) {
            cout << "Lap: " << elapsed() << " seconds" << endl;
        }
    }
};

int main() {
    Stopwatch sw;
    
    sw.startWatch();
    this_thread::sleep_for(chrono::milliseconds(1500));
    sw.lap();
    this_thread::sleep_for(chrono::milliseconds(1000));
    sw.stopWatch();
    
    cout << "Total time: " << sw.getTotalTime() << " seconds" << endl;
    
    // Cannot access TimerBase methods
    // sw.start();  // Error! start is private
    
    return 0;
}
```

#### Type 2: Multiple Files

**timerbase.h**
```cpp
#ifndef TIMERBASE_H
#define TIMERBASE_H

#include <chrono>
using namespace std;

class TimerBase {
protected:
    chrono::steady_clock::time_point startTime;
    bool running;
    
public:
    TimerBase();
    void start();
    double elapsed() const;
    void stop();
};

#endif
```

**timerbase.cpp**
```cpp
#include "timerbase.h"
#include <iostream>
using namespace std;

TimerBase::TimerBase() : running(false) {}

void TimerBase::start() {
    startTime = chrono::steady_clock::now();
    running = true;
    cout << "Timer started" << endl;
}

double TimerBase::elapsed() const {
    if (running) {
        auto now = chrono::steady_clock::now();
        return chrono::duration<double>(now - startTime).count();
    }
    return 0;
}

void TimerBase::stop() {
    running = false;
    cout << "Timer stopped" << endl;
}
```

**stopwatch.h**
```cpp
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "timerbase.h"

class Stopwatch : private TimerBase {
private:
    double totalTime;
    
public:
    Stopwatch();
    void startWatch();
    void stopWatch();
    void reset();
    double getTotalTime() const;
    void lap();
};

#endif
```

**stopwatch.cpp**
```cpp
#include "stopwatch.h"
#include <iostream>
using namespace std;

Stopwatch::Stopwatch() : totalTime(0) {}

void Stopwatch::startWatch() {
    start();
}

void Stopwatch::stopWatch() {
    totalTime += elapsed();
    stop();
    cout << "Lap time: " << elapsed() << " seconds" << endl;
}

void Stopwatch::reset() {
    totalTime = 0;
    cout << "Stopwatch reset" << endl;
}

double Stopwatch::getTotalTime() const {
    return totalTime;
}

void Stopwatch::lap() {
    if (running) {
        cout << "Lap: " << elapsed() << " seconds" << endl;
    }
}
```

**main.cpp**
```cpp
#include <iostream>
#include <thread>
#include "stopwatch.h"
using namespace std;

int main() {
    Stopwatch sw;
    sw.startWatch();
    this_thread::sleep_for(chrono::milliseconds(1500));
    sw.lap();
    this_thread::sleep_for(chrono::milliseconds(1000));
    sw.stopWatch();
    cout << "Total: " << sw.getTotalTime() << " seconds" << endl;
    return 0;
}
```

### Example 2: Counter Implementation

#### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class CounterBase {
protected:
    int value;
    
public:
    CounterBase() : value(0) {}
    
    void increment() {
        value++;
    }
    
    void decrement() {
        value--;
    }
    
    int getValue() const {
        return value;
    }
    
    void reset() {
        value = 0;
    }
};

// Bounded counter using private inheritance
class BoundedCounter : private CounterBase {
private:
    int minValue;
    int maxValue;
    
public:
    BoundedCounter(int minVal, int maxVal) : minValue(minVal), maxValue(maxVal) {
        if (minVal > maxVal) {
            minValue = 0;
            maxValue = 100;
        }
    }
    
    void increment() {
        if (value < maxValue) {
            CounterBase::increment();
            cout << "Increased to: " << value << endl;
        } else {
            cout << "Already at maximum!" << endl;
        }
    }
    
    void decrement() {
        if (value > minValue) {
            CounterBase::decrement();
            cout << "Decreased to: " << value << endl;
        } else {
            cout << "Already at minimum!" << endl;
        }
    }
    
    int getValue() const {
        return CounterBase::getValue();
    }
    
    void setValue(int newValue) {
        if (newValue >= minValue && newValue <= maxValue) {
            value = newValue;
            cout << "Value set to: " << value << endl;
        } else {
            cout << "Value out of range!" << endl;
        }
    }
};

int main() {
    BoundedCounter counter(0, 10);
    
    counter.increment();
    counter.increment();
    counter.increment();
    counter.decrement();
    
    cout << "Current value: " << counter.getValue() << endl;
    
    counter.setValue(15);
    counter.setValue(5);
    
    for (int i = 0; i < 12; i++) {
        counter.increment();
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**counterbase.h**
```cpp
#ifndef COUNTERBASE_H
#define COUNTERBASE_H

class CounterBase {
protected:
    int value;
    
public:
    CounterBase();
    void increment();
    void decrement();
    int getValue() const;
    void reset();
};

#endif
```

**counterbase.cpp**
```cpp
#include "counterbase.h"
#include <iostream>
using namespace std;

CounterBase::CounterBase() : value(0) {}

void CounterBase::increment() {
    value++;
}

void CounterBase::decrement() {
    value--;
}

int CounterBase::getValue() const {
    return value;
}

void CounterBase::reset() {
    value = 0;
}
```

**boundedcounter.h**
```cpp
#ifndef BOUNDEDCOUNTER_H
#define BOUNDEDCOUNTER_H

#include "counterbase.h"

class BoundedCounter : private CounterBase {
private:
    int minValue;
    int maxValue;
    
public:
    BoundedCounter(int minVal, int maxVal);
    void increment();
    void decrement();
    int getValue() const;
    void setValue(int newValue);
};

#endif
```

**boundedcounter.cpp**
```cpp
#include "boundedcounter.h"
#include <iostream>
using namespace std;

BoundedCounter::BoundedCounter(int minVal, int maxVal) : minValue(minVal), maxValue(maxVal) {
    if (minVal > maxVal) {
        minValue = 0;
        maxValue = 100;
    }
}

void BoundedCounter::increment() {
    if (value < maxValue) {
        CounterBase::increment();
        cout << "Increased to: " << value << endl;
    } else {
        cout << "Already at maximum!" << endl;
    }
}

void BoundedCounter::decrement() {
    if (value > minValue) {
        CounterBase::decrement();
        cout << "Decreased to: " << value << endl;
    } else {
        cout << "Already at minimum!" << endl;
    }
}

int BoundedCounter::getValue() const {
    return CounterBase::getValue();
}

void BoundedCounter::setValue(int newValue) {
    if (newValue >= minValue && newValue <= maxValue) {
        value = newValue;
        cout << "Value set to: " << value << endl;
    } else {
        cout << "Value out of range!" << endl;
    }
}
```

**main.cpp**
```cpp
#include <iostream>
#include "boundedcounter.h"
using namespace std;

int main() {
    BoundedCounter counter(0, 5);
    
    counter.increment();
    counter.increment();
    counter.increment();
    counter.decrement();
    cout << "Value: " << counter.getValue() << endl;
    
    return 0;
}
```

### Example 3: Logger with File Output

#### Type 1: Single File
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class BaseLogger {
protected:
    string name;
    ofstream file;
    bool fileOpen;
    
    string getTimestamp() {
        time_t now = time(0);
        return ctime(&now);
    }
    
public:
    BaseLogger(string n) : name(n), fileOpen(false) {}
    
    bool openFile(const string& filename) {
        file.open(filename, ios::app);
        fileOpen = file.is_open();
        if (fileOpen) {
            cout << "File opened: " << filename << endl;
        }
        return fileOpen;
    }
    
    void write(const string& message) {
        if (fileOpen) {
            file << "[" << getTimestamp() << "] " << name << ": " << message;
            file.flush();
        }
    }
    
    void closeFile() {
        if (fileOpen) {
            file.close();
            fileOpen = false;
            cout << "File closed" << endl;
        }
    }
    
    ~BaseLogger() {
        closeFile();
    }
};

// Specific logger using private inheritance
class ErrorLogger : private BaseLogger {
private:
    int errorCount;
    
public:
    ErrorLogger(string n) : BaseLogger(n), errorCount(0) {}
    
    bool initialize(const string& filename) {
        return openFile(filename);
    }
    
    void logError(const string& error) {
        errorCount++;
        string logMsg = "ERROR #" + to_string(errorCount) + ": " + error + "\n";
        write(logMsg);
        cout << "Error logged: " << error << endl;
    }
    
    void logWarning(const string& warning) {
        string logMsg = "WARNING: " + warning + "\n";
        write(logMsg);
        cout << "Warning logged: " << warning << endl;
    }
    
    int getErrorCount() const {
        return errorCount;
    }
    
    void shutdown() {
        closeFile();
    }
};

int main() {
    ErrorLogger logger("AppLogger");
    
    if (logger.initialize("errors.log")) {
        logger.logError("Database connection failed");
        logger.logError("Invalid user input");
        logger.logWarning("Low disk space");
        logger.logWarning("High memory usage");
        
        cout << "Total errors: " << logger.getErrorCount() << endl;
        
        logger.shutdown();
    }
    
    // Cannot access BaseLogger methods
    // logger.write("Test");  // Error! write is private
    
    return 0;
}
```

#### Type 2: Multiple Files

**baselogger.h**
```cpp
#ifndef BASELOGGER_H
#define BASELOGGER_H

#include <string>
#include <fstream>
using namespace std;

class BaseLogger {
protected:
    string name;
    ofstream file;
    bool fileOpen;
    
    string getTimestamp();
    
public:
    BaseLogger(string n);
    bool openFile(const string& filename);
    void write(const string& message);
    void closeFile();
    ~BaseLogger();
};

#endif
```

**baselogger.cpp**
```cpp
#include "baselogger.h"
#include <iostream>
#include <ctime>
using namespace std;

BaseLogger::BaseLogger(string n) : name(n), fileOpen(false) {}

string BaseLogger::getTimestamp() {
    time_t now = time(0);
    return ctime(&now);
}

bool BaseLogger::openFile(const string& filename) {
    file.open(filename, ios::app);
    fileOpen = file.is_open();
    if (fileOpen) {
        cout << "File opened: " << filename << endl;
    }
    return fileOpen;
}

void BaseLogger::write(const string& message) {
    if (fileOpen) {
        file << "[" << getTimestamp() << "] " << name << ": " << message;
        file.flush();
    }
}

void BaseLogger::closeFile() {
    if (fileOpen) {
        file.close();
        fileOpen = false;
        cout << "File closed" << endl;
    }
}

BaseLogger::~BaseLogger() {
    closeFile();
}
```

**errorlogger.h**
```cpp
#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#include "baselogger.h"
#include <string>
using namespace std;

class ErrorLogger : private BaseLogger {
private:
    int errorCount;
    
public:
    ErrorLogger(string n);
    bool initialize(const string& filename);
    void logError(const string& error);
    void logWarning(const string& warning);
    int getErrorCount() const;
    void shutdown();
};

#endif
```

**errorlogger.cpp**
```cpp
#include "errorlogger.h"
#include <iostream>
using namespace std;

ErrorLogger::ErrorLogger(string n) : BaseLogger(n), errorCount(0) {}

bool ErrorLogger::initialize(const string& filename) {
    return openFile(filename);
}

void ErrorLogger::logError(const string& error) {
    errorCount++;
    string logMsg = "ERROR #" + to_string(errorCount) + ": " + error + "\n";
    write(logMsg);
    cout << "Error logged: " << error << endl;
}

void ErrorLogger::logWarning(const string& warning) {
    string logMsg = "WARNING: " + warning + "\n";
    write(logMsg);
    cout << "Warning logged: " << warning << endl;
}

int ErrorLogger::getErrorCount() const {
    return errorCount;
}

void ErrorLogger::shutdown() {
    closeFile();
}
```

**main.cpp**
```cpp
#include <iostream>
#include "errorlogger.h"
using namespace std;

int main() {
    ErrorLogger logger("AppLogger");
    
    if (logger.initialize("errors.log")) {
        logger.logError("Database connection failed");
        logger.logWarning("Low disk space");
        cout << "Errors: " << logger.getErrorCount() << endl;
        logger.shutdown();
    }
    
    return 0;
}
```

## Private Inheritance vs Composition

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Private inheritance approach
class StackInherit : private vector<int> {
public:
    void push(int value) {
        push_back(value);
    }
    
    int pop() {
        if (empty()) return -1;
        int value = back();
        pop_back();
        return value;
    }
    
    bool isEmpty() const {
        return empty();
    }
    
    int size() const {
        return vector<int>::size();
    }
};

// Composition approach
class StackCompose {
private:
    vector<int> data;
    
public:
    void push(int value) {
        data.push_back(value);
    }
    
    int pop() {
        if (data.empty()) return -1;
        int value = data.back();
        data.pop_back();
        return value;
    }
    
    bool isEmpty() const {
        return data.empty();
    }
    
    int size() const {
        return data.size();
    }
};

int main() {
    StackInherit s1;
    StackCompose s2;
    
    s1.push(10);
    s2.push(10);
    
    cout << "Inheritance: " << s1.pop() << endl;
    cout << "Composition: " << s2.pop() << endl;
    
    return 0;
}
```

## When to Use Private Inheritance

### ✅ Good Uses
```cpp
// When you need access to protected members
class Timer : private Clock {
    // Need Clock's protected methods
};

// When you need to override virtual functions
class Button : private Control {
    virtual void onClick() override { /* ... */ }
};

// When empty base optimization matters
class EmptyBase { };
class Derived : private EmptyBase {
    // No size overhead for EmptyBase
};
```

### ❌ Avoid
```cpp
// When composition is simpler
class Stack : private vector<int> { };  // Use composition instead

// When "is-a" relationship exists
class Dog : private Animal { };  // Should be public

// When you need polymorphic behavior
void process(Base* b);  // Can't pass PrivateDerived*
```

## Private Inheritance vs Composition - Decision Guide

| Factor | Private Inheritance | Composition |
|--------|---------------------|-------------|
| Access to protected members | Yes | No |
| Override virtual functions | Yes | No (requires wrapper) |
| Empty base optimization | Yes | No |
| Multiple inheritance | Yes | Yes |
| Clearer semantics | No | Yes |
| Coupling | Tighter | Looser |

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Using private inheritance for polymorphism | Cannot use base class pointers | Use public inheritance |
| Expecting public interface | All members become private | Use composition or provide accessors |
| Forgetting access to base members | Compilation errors | Use Base::member or provide wrapper |
| Overusing private inheritance | Complex hierarchies | Prefer composition when possible |

## Summary

- **Private inheritance** makes all base members private
- Establishes **"implemented-in-terms-of"** relationship
- Not an **"is-a"** relationship (no polymorphism)
- Further derived classes **cannot** access base members
- Use when you need **protected access** or **virtual function override**
- Prefer **composition** for most implementation reuse cases
- Provides **empty base optimization** benefits

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

class Derived : private Base {
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
    // d.value;      // Error! Private
    // d.showBase(); // Error! Private
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

class Derived : private Base {
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