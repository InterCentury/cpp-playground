# 87 - Virtual Destructor in C++

## What is a Virtual Destructor?
A virtual destructor ensures that when a derived class object is deleted through a base class pointer, the correct destructor (both base and derived) is called in the proper order. Without a virtual destructor, only the base class destructor runs, leading to resource leaks.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructor" << endl; }
    
    // Virtual destructor
    virtual ~Base() { cout << "Base destructor" << endl; }
};

class Derived : public Base {
private:
    int* data;
    
public:
    Derived() : data(new int[100]) {
        cout << "Derived constructor - allocated memory" << endl;
    }
    
    ~Derived() {
        delete[] data;
        cout << "Derived destructor - freed memory" << endl;
    }
};

int main() {
    cout << "=== Using base pointer with virtual destructor ===" << endl;
    Base* ptr = new Derived();
    delete ptr;  // Both destructors called!
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### base.h
```cpp
#ifndef BASE_H
#define BASE_H

class Base {
public:
    Base();
    virtual ~Base();
};

#endif
```

### base.cpp
```cpp
#include "base.h"
#include <iostream>
using namespace std;

Base::Base() {
    cout << "Base constructor" << endl;
}

Base::~Base() {
    cout << "Base destructor" << endl;
}
```

### derived.h
```cpp
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"

class Derived : public Base {
private:
    int* data;
    
public:
    Derived();
    ~Derived();
};

#endif
```

### derived.cpp
```cpp
#include "derived.h"
#include <iostream>
using namespace std;

Derived::Derived() : data(new int[100]) {
    cout << "Derived constructor - allocated memory" << endl;
}

Derived::~Derived() {
    delete[] data;
    cout << "Derived destructor - freed memory" << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "derived.h"
using namespace std;

int main() {
    Base* ptr = new Derived();
    delete ptr;
    return 0;
}
```

## Without Virtual Destructor (Problem)

```cpp
#include <iostream>
#include <string>
using namespace std;

class BaseNoVirtual {
public:
    BaseNoVirtual() { cout << "Base constructor" << endl; }
    ~BaseNoVirtual() { cout << "Base destructor ONLY!" << endl; }
};

class DerivedNoVirtual : public BaseNoVirtual {
private:
    int* data;
    
public:
    DerivedNoVirtual() : data(new int[100]) {
        cout << "Derived constructor - allocated memory" << endl;
    }
    
    ~DerivedNoVirtual() {
        delete[] data;
        cout << "Derived destructor - NOT CALLED!" << endl;
    }
};

int main() {
    cout << "=== Without virtual destructor - MEMORY LEAK! ===" << endl;
    BaseNoVirtual* ptr = new DerivedNoVirtual();
    delete ptr;  // Only Base destructor runs!
    
    return 0;
}
```

## Why Virtual Destructor is Needed

```cpp
#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
    Animal() { cout << "Animal created" << endl; }
    virtual ~Animal() { cout << "Animal destroyed" << endl; }
    virtual void speak() const = 0;
};

class Dog : public Animal {
private:
    string* name;
    
public:
    Dog(const string& n) : name(new string(n)) {
        cout << "Dog " << *name << " created" << endl;
    }
    
    ~Dog() {
        delete name;
        cout << "Dog destroyed" << endl;
    }
    
    void speak() const override {
        cout << *name << " says: Woof!" << endl;
    }
};

class Cat : public Animal {
private:
    string* name;
    
public:
    Cat(const string& n) : name(new string(n)) {
        cout << "Cat " << *name << " created" << endl;
    }
    
    ~Cat() {
        delete name;
        cout << "Cat destroyed" << endl;
    }
    
    void speak() const override {
        cout << *name << " says: Meow!" << endl;
    }
};

int main() {
    Animal* animals[2];
    
    animals[0] = new Dog("Buddy");
    animals[1] = new Cat("Whiskers");
    
    animals[0]->speak();
    animals[1]->speak();
    
    // Proper cleanup with virtual destructor
    for (int i = 0; i < 2; i++) {
        delete animals[i];  // Both Animal and derived destructors run
    }
    
    return 0;
}
```

## Practical Examples

### Example 1: Shape Hierarchy with Virtual Destructor

#### Type 1: Single File
```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Shape {
public:
    Shape() { cout << "Shape created" << endl; }
    virtual ~Shape() { cout << "Shape destroyed" << endl; }
    virtual double area() const = 0;
    virtual void display() const = 0;
};

class Circle : public Shape {
private:
    double* radius;
    
public:
    Circle(double r) : radius(new double(r)) {
        cout << "Circle created (r=" << *radius << ")" << endl;
    }
    
    ~Circle() {
        delete radius;
        cout << "Circle destroyed" << endl;
    }
    
    double area() const override {
        return 3.14159 * (*radius) * (*radius);
    }
    
    void display() const override {
        cout << "Circle: radius=" << *radius << ", area=" << area() << endl;
    }
};

class Rectangle : public Shape {
private:
    double* width;
    double* height;
    
public:
    Rectangle(double w, double h) : width(new double(w)), height(new double(h)) {
        cout << "Rectangle created (" << *width << "x" << *height << ")" << endl;
    }
    
    ~Rectangle() {
        delete width;
        delete height;
        cout << "Rectangle destroyed" << endl;
    }
    
    double area() const override {
        return (*width) * (*height);
    }
    
    void display() const override {
        cout << "Rectangle: " << *width << "x" << *height 
             << ", area=" << area() << endl;
    }
};

int main() {
    Shape* shapes[2];
    
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 3.0);
    
    for (int i = 0; i < 2; i++) {
        shapes[i]->display();
    }
    
    // Cleanup with virtual destructor
    for (int i = 0; i < 2; i++) {
        delete shapes[i];
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**shape.h**
```cpp
#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
    Shape();
    virtual ~Shape();
    virtual double area() const = 0;
    virtual void display() const = 0;
};

#endif
```

**shape.cpp**
```cpp
#include "shape.h"
#include <iostream>
using namespace std;

Shape::Shape() {
    cout << "Shape created" << endl;
}

Shape::~Shape() {
    cout << "Shape destroyed" << endl;
}
```

**circle.h**
```cpp
#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
private:
    double* radius;
    
public:
    Circle(double r);
    ~Circle();
    double area() const override;
    void display() const override;
};

#endif
```

**circle.cpp**
```cpp
#include "circle.h"
#include <iostream>
#include <cmath>
using namespace std;

Circle::Circle(double r) : radius(new double(r)) {
    cout << "Circle created (r=" << *radius << ")" << endl;
}

Circle::~Circle() {
    delete radius;
    cout << "Circle destroyed" << endl;
}

double Circle::area() const {
    return 3.14159 * (*radius) * (*radius);
}

void Circle::display() const {
    cout << "Circle: radius=" << *radius << ", area=" << area() << endl;
}
```

**rectangle.h**
```cpp
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
private:
    double* width;
    double* height;
    
public:
    Rectangle(double w, double h);
    ~Rectangle();
    double area() const override;
    void display() const override;
};

#endif
```

**rectangle.cpp**
```cpp
#include "rectangle.h"
#include <iostream>
using namespace std;

Rectangle::Rectangle(double w, double h) : width(new double(w)), height(new double(h)) {
    cout << "Rectangle created (" << *width << "x" << *height << ")" << endl;
}

Rectangle::~Rectangle() {
    delete width;
    delete height;
    cout << "Rectangle destroyed" << endl;
}

double Rectangle::area() const {
    return (*width) * (*height);
}

void Rectangle::display() const {
    cout << "Rectangle: " << *width << "x" << *height 
         << ", area=" << area() << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "circle.h"
#include "rectangle.h"
using namespace std;

int main() {
    Shape* shapes[2];
    
    shapes[0] = new Circle(5.0);
    shapes[1] = new Rectangle(4.0, 3.0);
    
    for (int i = 0; i < 2; i++) {
        shapes[i]->display();
    }
    
    for (int i = 0; i < 2; i++) {
        delete shapes[i];
    }
    
    return 0;
}
```

### Example 2: Database Connection Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class DatabaseConnection {
protected:
    string connectionString;
    bool connected;
    
public:
    DatabaseConnection(string conn) : connectionString(conn), connected(false) {
        cout << "DatabaseConnection created" << endl;
    }
    
    virtual ~DatabaseConnection() {
        if (connected) disconnect();
        cout << "DatabaseConnection destroyed" << endl;
    }
    
    virtual void connect() {
        cout << "Connecting to: " << connectionString << endl;
        connected = true;
    }
    
    virtual void disconnect() {
        cout << "Disconnecting from: " << connectionString << endl;
        connected = false;
    }
    
    virtual void executeQuery(const string& query) = 0;
};

class MySQLConnection : public DatabaseConnection {
private:
    int* connectionPool;
    
public:
    MySQLConnection(string conn) : DatabaseConnection(conn) {
        connectionPool = new int(5);
        cout << "MySQL connection pool created" << endl;
    }
    
    ~MySQLConnection() {
        delete connectionPool;
        cout << "MySQL connection pool destroyed" << endl;
    }
    
    void executeQuery(const string& query) override {
        if (connected) {
            cout << "[MySQL] Executing: " << query << endl;
        }
    }
};

class PostgreSQLConnection : public DatabaseConnection {
private:
    string* sslCert;
    
public:
    PostgreSQLConnection(string conn) : DatabaseConnection(conn) {
        sslCert = new string("cert.pem");
        cout << "PostgreSQL SSL certificate loaded" << endl;
    }
    
    ~PostgreSQLConnection() {
        delete sslCert;
        cout << "PostgreSQL SSL certificate unloaded" << endl;
    }
    
    void executeQuery(const string& query) override {
        if (connected) {
            cout << "[PostgreSQL] Executing: " << query << endl;
        }
    }
};

int main() {
    DatabaseConnection* connections[2];
    
    connections[0] = new MySQLConnection("localhost:3306/mydb");
    connections[1] = new PostgreSQLConnection("localhost:5432/mydb");
    
    for (int i = 0; i < 2; i++) {
        connections[i]->connect();
        connections[i]->executeQuery("SELECT * FROM users");
    }
    
    for (int i = 0; i < 2; i++) {
        delete connections[i];
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**database.h**
```cpp
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
using namespace std;

class DatabaseConnection {
protected:
    string connectionString;
    bool connected;
    
public:
    DatabaseConnection(string conn);
    virtual ~DatabaseConnection();
    virtual void connect();
    virtual void disconnect();
    virtual void executeQuery(const string& query) = 0;
};

#endif
```

**database.cpp**
```cpp
#include "database.h"
#include <iostream>
using namespace std;

DatabaseConnection::DatabaseConnection(string conn) 
    : connectionString(conn), connected(false) {
    cout << "DatabaseConnection created" << endl;
}

DatabaseConnection::~DatabaseConnection() {
    if (connected) disconnect();
    cout << "DatabaseConnection destroyed" << endl;
}

void DatabaseConnection::connect() {
    cout << "Connecting to: " << connectionString << endl;
    connected = true;
}

void DatabaseConnection::disconnect() {
    cout << "Disconnecting from: " << connectionString << endl;
    connected = false;
}
```

**mysql.h**
```cpp
#ifndef MYSQL_H
#define MYSQL_H

#include "database.h"

class MySQLConnection : public DatabaseConnection {
private:
    int* connectionPool;
    
public:
    MySQLConnection(string conn);
    ~MySQLConnection();
    void executeQuery(const string& query) override;
};

#endif
```

**mysql.cpp**
```cpp
#include "mysql.h"
#include <iostream>
using namespace std;

MySQLConnection::MySQLConnection(string conn) : DatabaseConnection(conn) {
    connectionPool = new int(5);
    cout << "MySQL connection pool created" << endl;
}

MySQLConnection::~MySQLConnection() {
    delete connectionPool;
    cout << "MySQL connection pool destroyed" << endl;
}

void MySQLConnection::executeQuery(const string& query) {
    if (connected) {
        cout << "[MySQL] Executing: " << query << endl;
    }
}
```

**postgresql.h**
```cpp
#ifndef POSTGRESQL_H
#define POSTGRESQL_H

#include "database.h"
#include <string>
using namespace std;

class PostgreSQLConnection : public DatabaseConnection {
private:
    string* sslCert;
    
public:
    PostgreSQLConnection(string conn);
    ~PostgreSQLConnection();
    void executeQuery(const string& query) override;
};

#endif
```

**postgresql.cpp**
```cpp
#include "postgresql.h"
#include <iostream>
using namespace std;

PostgreSQLConnection::PostgreSQLConnection(string conn) : DatabaseConnection(conn) {
    sslCert = new string("cert.pem");
    cout << "PostgreSQL SSL certificate loaded" << endl;
}

PostgreSQLConnection::~PostgreSQLConnection() {
    delete sslCert;
    cout << "PostgreSQL SSL certificate unloaded" << endl;
}

void PostgreSQLConnection::executeQuery(const string& query) {
    if (connected) {
        cout << "[PostgreSQL] Executing: " << query << endl;
    }
}
```

**main.cpp**
```cpp
#include <iostream>
#include "mysql.h"
#include "postgresql.h"
using namespace std;

int main() {
    DatabaseConnection* conn1 = new MySQLConnection("localhost:3306/mydb");
    DatabaseConnection* conn2 = new PostgreSQLConnection("localhost:5432/mydb");
    
    conn1->connect();
    conn2->connect();
    
    conn1->executeQuery("SELECT * FROM users");
    conn2->executeQuery("SELECT * FROM orders");
    
    delete conn1;
    delete conn2;
    
    return 0;
}
```

### Example 3: Plugin System with Virtual Destructor

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Plugin {
protected:
    string name;
    bool loaded;
    
public:
    Plugin(string n) : name(n), loaded(false) {
        cout << "Plugin " << name << " created" << endl;
    }
    
    virtual ~Plugin() {
        if (loaded) unload();
        cout << "Plugin " << name << " destroyed" << endl;
    }
    
    virtual bool load() {
        loaded = true;
        cout << "Plugin " << name << " loaded" << endl;
        return true;
    }
    
    virtual void unload() {
        loaded = false;
        cout << "Plugin " << name << " unloaded" << endl;
    }
    
    virtual void execute() = 0;
};

class AudioPlugin : public Plugin {
private:
    double* buffer;
    
public:
    AudioPlugin(string n) : Plugin(n) {
        buffer = new double[1024];
        cout << "Audio buffer allocated for " << name << endl;
    }
    
    ~AudioPlugin() {
        delete[] buffer;
        cout << "Audio buffer freed for " << name << endl;
    }
    
    void execute() override {
        if (loaded) {
            cout << "AudioPlugin " << name << " processing audio" << endl;
        }
    }
};

class VideoPlugin : public Plugin {
private:
    int* frameBuffer;
    
public:
    VideoPlugin(string n) : Plugin(n) {
        frameBuffer = new int[1920 * 1080];
        cout << "Video frame buffer allocated for " << name << endl;
    }
    
    ~VideoPlugin() {
        delete[] frameBuffer;
        cout << "Video frame buffer freed for " << name << endl;
    }
    
    void execute() override {
        if (loaded) {
            cout << "VideoPlugin " << name << " processing video frame" << endl;
        }
    }
};

int main() {
    vector<Plugin*> plugins;
    
    plugins.push_back(new AudioPlugin("EQ Filter"));
    plugins.push_back(new VideoPlugin("Color Correction"));
    plugins.push_back(new AudioPlugin("Reverb"));
    
    for (auto plugin : plugins) {
        plugin->load();
    }
    
    for (auto plugin : plugins) {
        plugin->execute();
    }
    
    for (auto plugin : plugins) {
        delete plugin;
    }
    
    return 0;
}
```

#### Type 2: Multiple Files

**plugin.h**
```cpp
#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>
using namespace std;

class Plugin {
protected:
    string name;
    bool loaded;
    
public:
    Plugin(string n);
    virtual ~Plugin();
    virtual bool load();
    virtual void unload();
    virtual void execute() = 0;
};

#endif
```

**plugin.cpp**
```cpp
#include "plugin.h"
#include <iostream>
using namespace std;

Plugin::Plugin(string n) : name(n), loaded(false) {
    cout << "Plugin " << name << " created" << endl;
}

Plugin::~Plugin() {
    if (loaded) unload();
    cout << "Plugin " << name << " destroyed" << endl;
}

bool Plugin::load() {
    loaded = true;
    cout << "Plugin " << name << " loaded" << endl;
    return true;
}

void Plugin::unload() {
    loaded = false;
    cout << "Plugin " << name << " unloaded" << endl;
}
```

**audioplugin.h**
```cpp
#ifndef AUDIOPLUGIN_H
#define AUDIOPLUGIN_H

#include "plugin.h"

class AudioPlugin : public Plugin {
private:
    double* buffer;
    
public:
    AudioPlugin(string n);
    ~AudioPlugin();
    void execute() override;
};

#endif
```

**audioplugin.cpp**
```cpp
#include "audioplugin.h"
#include <iostream>
using namespace std;

AudioPlugin::AudioPlugin(string n) : Plugin(n) {
    buffer = new double[1024];
    cout << "Audio buffer allocated for " << name << endl;
}

AudioPlugin::~AudioPlugin() {
    delete[] buffer;
    cout << "Audio buffer freed for " << name << endl;
}

void AudioPlugin::execute() {
    if (loaded) {
        cout << "AudioPlugin " << name << " processing audio" << endl;
    }
}
```

**videoplugin.h**
```cpp
#ifndef VIDEOPLUGIN_H
#define VIDEOPLUGIN_H

#include "plugin.h"

class VideoPlugin : public Plugin {
private:
    int* frameBuffer;
    
public:
    VideoPlugin(string n);
    ~VideoPlugin();
    void execute() override;
};

#endif
```

**videoplugin.cpp**
```cpp
#include "videoplugin.h"
#include <iostream>
using namespace std;

VideoPlugin::VideoPlugin(string n) : Plugin(n) {
    frameBuffer = new int[1920 * 1080];
    cout << "Video frame buffer allocated for " << name << endl;
}

VideoPlugin::~VideoPlugin() {
    delete[] frameBuffer;
    cout << "Video frame buffer freed for " << name << endl;
}

void VideoPlugin::execute() {
    if (loaded) {
        cout << "VideoPlugin " << name << " processing video frame" << endl;
    }
}
```

**main.cpp**
```cpp
#include <iostream>
#include <vector>
#include "audioplugin.h"
#include "videoplugin.h"
using namespace std;

int main() {
    vector<Plugin*> plugins;
    
    plugins.push_back(new AudioPlugin("EQ Filter"));
    plugins.push_back(new VideoPlugin("Color Correction"));
    
    for (auto plugin : plugins) {
        plugin->load();
    }
    
    for (auto plugin : plugins) {
        plugin->execute();
    }
    
    for (auto plugin : plugins) {
        delete plugin;
    }
    
    return 0;
}
```

## Rule of Five (C++11)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Resource {
private:
    char* data;
    int size;
    
public:
    // Constructor
    Resource(const char* s) : size(strlen(s)) {
        data = new char[size + 1];
        strcpy(data, s);
        cout << "Constructor: " << data << endl;
    }
    
    // Destructor
    ~Resource() {
        delete[] data;
        cout << "Destructor: " << data << endl;
    }
    
    // Copy constructor
    Resource(const Resource& other) : size(other.size) {
        data = new char[size + 1];
        strcpy(data, other.data);
        cout << "Copy constructor: " << data << endl;
    }
    
    // Copy assignment
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size + 1];
            strcpy(data, other.data);
            cout << "Copy assignment: " << data << endl;
        }
        return *this;
    }
    
    // Move constructor (C++11)
    Resource(Resource&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "Move constructor" << endl;
    }
    
    // Move assignment (C++11)
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            cout << "Move assignment" << endl;
        }
        return *this;
    }
    
    void display() const {
        cout << data << endl;
    }
};

int main() {
    Resource r1("Hello");
    Resource r2 = r1;  // Copy constructor
    Resource r3("World");
    r3 = r1;           // Copy assignment
    
    Resource r4 = move(r1);  // Move constructor
    
    r2.display();
    r3.display();
    r4.display();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting virtual destructor | Memory leak in polymorphism | Always make base destructor virtual |
| Making destructor virtual unnecessarily | Slight performance overhead | Only when class is intended as base |
| Throwing exceptions in destructor | Program termination | Never throw from destructor |
| Not calling base destructor | Base resources not cleaned | Base destructor called automatically |
| Deleting derived through void* | No destructor called | Never delete through void* |

## Quick Reference

| Scenario | Destructor Type | Reason |
|----------|-----------------|--------|
| Base class with virtual functions | Virtual | Ensures proper cleanup of derived objects |
| Non-polymorphic class | Non-virtual | No overhead needed |
| Abstract base class | Virtual | Will be used polymorphically |
| Leaf class (final) | Non-virtual | Not used as base |
| Interface class | Virtual | Pure virtual functions, used polymorphically |

## Summary

- **Virtual destructor** ensures proper cleanup in inheritance hierarchies
- **Essential** when deleting derived objects through base pointers
- Without virtual destructor → **memory leak**
- Base class destructor is called **automatically** after derived destructor
- **Rule of Five**: If you need a destructor, consider copy/move operations
- **Never throw exceptions** from destructors
- Virtual destructor adds a **vtable** (minor overhead)
- **Abstract classes** should always have virtual destructor

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructor" << endl; }
    virtual ~Base() { cout << "Base destructor" << endl; }
    virtual void display() const = 0;
};

class Derived : public Base {
private:
    string* data;
    
public:
    Derived(const string& s) : data(new string(s)) {
        cout << "Derived constructor: " << *data << endl;
    }
    
    ~Derived() {
        delete data;
        cout << "Derived destructor" << endl;
    }
    
    void display() const override {
        cout << "Data: " << *data << endl;
    }
};

int main() {
    Base* ptr = new Derived("Hello World");
    ptr->display();
    delete ptr;
    return 0;
}
```

### Type 2: Multiple Files

**base.h**
```cpp
#ifndef BASE_H
#define BASE_H

class Base {
public:
    Base();
    virtual ~Base();
    virtual void display() const = 0;
};

#endif
```

**base.cpp**
```cpp
#include "base.h"
#include <iostream>
using namespace std;

Base::Base() {
    cout << "Base constructor" << endl;
}

Base::~Base() {
    cout << "Base destructor" << endl;
}
```

**derived.h**
```cpp
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"
#include <string>
using namespace std;

class Derived : public Base {
private:
    string* data;
    
public:
    Derived(const string& s);
    ~Derived();
    void display() const override;
};

#endif
```

**derived.cpp**
```cpp
#include "derived.h"
#include <iostream>
using namespace std;

Derived::Derived(const string& s) : data(new string(s)) {
    cout << "Derived constructor: " << *data << endl;
}

Derived::~Derived() {
    delete data;
    cout << "Derived destructor" << endl;
}

void Derived::display() const {
    cout << "Data: " << *data << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "derived.h"
using namespace std;

int main() {
    Base* ptr = new Derived("Hello World");
    ptr->display();
    delete ptr;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*