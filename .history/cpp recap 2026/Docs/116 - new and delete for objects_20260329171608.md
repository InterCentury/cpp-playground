
# 116 - new and delete for Objects in C++

## What are new and delete?
The `new` operator dynamically allocates memory for objects on the heap, and `delete` deallocates that memory. Unlike `malloc()` and `free()`, `new` and `delete` call constructors and destructors automatically.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int id;
    double gpa;
    
public:
    Student(string n, int i, double g) : name(n), id(i), gpa(g) {
        cout << "Constructor called for " << name << endl;
    }
    
    ~Student() {
        cout << "Destructor called for " << name << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", ID: " << id << ", GPA: " << gpa << endl;
    }
};

int main() {
    // Single object allocation
    Student* s1 = new Student("John Doe", 101, 3.5);
    s1->display();
    delete s1;  // Must delete to free memory
    
    // Array of objects
    Student* students = new Student[3]{
        {"Alice", 102, 3.8},
        {"Bob", 103, 3.2},
        {"Carol", 104, 3.9}
    };
    
    for (int i = 0; i < 3; i++) {
        students[i].display();
    }
    
    delete[] students;  // Use delete[] for arrays
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### student.h
```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student {
private:
    string name;
    int id;
    double gpa;
    
public:
    Student(string n, int i, double g);
    ~Student();
    void display() const;
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

Student::Student(string n, int i, double g) : name(n), id(i), gpa(g) {
    cout << "Constructor called for " << name << endl;
}

Student::~Student() {
    cout << "Destructor called for " << name << endl;
}

void Student::display() const {
    cout << "Name: " << name << ", ID: " << id << ", GPA: " << gpa << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "student.h"
using namespace std;

int main() {
    Student* s = new Student("John", 101, 3.5);
    s->display();
    delete s;
    return 0;
}
```

## new and delete for Single Objects

```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
    
public:
    Rectangle(double l = 0, double w = 0) : length(l), width(w) {
        cout << "Rectangle created: " << length << " x " << width << endl;
    }
    
    ~Rectangle() {
        cout << "Rectangle destroyed: " << length << " x " << width << endl;
    }
    
    double area() const { return length * width; }
};

int main() {
    // Different ways to allocate with new
    Rectangle* r1 = new Rectangle;           // Default constructor
    Rectangle* r2 = new Rectangle();         // Default constructor
    Rectangle* r3 = new Rectangle(5, 3);     // Parameterized constructor
    
    cout << "r3 area: " << r3->area() << endl;
    
    // Cleanup
    delete r1;
    delete r2;
    delete r3;
    
    return 0;
}
```

## new and delete for Arrays

```cpp
#include <iostream>
using namespace std;

class Point {
private:
    int x, y;
    
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {
        cout << "Point(" << x << ", " << y << ") created" << endl;
    }
    
    ~Point() {
        cout << "Point(" << x << ", " << y << ") destroyed" << endl;
    }
    
    void display() const {
        cout << "(" << x << ", " << y << ")";
    }
};

int main() {
    // Array of objects
    Point* points = new Point[5];
    
    // Initialize array elements
    for (int i = 0; i < 5; i++) {
        points[i] = Point(i, i * 2);
    }
    
    // Display
    for (int i = 0; i < 5; i++) {
        points[i].display();
        cout << " ";
    }
    cout << endl;
    
    // Must use delete[] for arrays
    delete[] points;
    
    return 0;
}
```

## Placement new

```cpp
#include <iostream>
#include <new>
using namespace std;

class Widget {
private:
    int id;
    string name;
    
public:
    Widget(int i, string n) : id(i), name(n) {
        cout << "Widget " << name << " constructed" << endl;
    }
    
    ~Widget() {
        cout << "Widget " << name << " destroyed" << endl;
    }
    
    void display() const {
        cout << "Widget: " << id << ", " << name << endl;
    }
};

int main() {
    // Allocate raw memory
    char* buffer = new char[sizeof(Widget) * 3];
    
    // Placement new - construct objects in pre-allocated memory
    Widget* w1 = new (buffer) Widget(1, "First");
    Widget* w2 = new (buffer + sizeof(Widget)) Widget(2, "Second");
    Widget* w3 = new (buffer + 2 * sizeof(Widget)) Widget(3, "Third");
    
    // Use objects
    w1->display();
    w2->display();
    w3->display();
    
    // Manually call destructors
    w1->~Widget();
    w2->~Widget();
    w3->~Widget();
    
    // Deallocate raw memory
    delete[] buffer;
    
    return 0;
}
```

## Practical Examples

### Example 1: Dynamic Array Class

#### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;
    
public:
    DynamicArray(int cap = 10) : capacity(cap), size(0) {
        data = new int[capacity];
        cout << "Array created with capacity " << capacity << endl;
    }
    
    ~DynamicArray() {
        delete[] data;
        cout << "Array destroyed" << endl;
    }
    
    void add(int value) {
        if (size >= capacity) {
            // Resize
            capacity *= 2;
            int* newData = new int[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            cout << "Resized to capacity " << capacity << endl;
        }
        data[size++] = value;
    }
    
    int get(int index) const {
        if (index >= 0 && index < size) return data[index];
        return -1;
    }
    
    int getSize() const { return size; }
    
    void display() const {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    DynamicArray arr(3);
    
    arr.add(10);
    arr.add(20);
    arr.add(30);
    arr.add(40);  // Triggers resize
    arr.add(50);
    
    arr.display();
    cout << "Size: " << arr.getSize() << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**dynamicarray.h**
```cpp
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;
    
public:
    DynamicArray(int cap = 10);
    ~DynamicArray();
    void add(int value);
    int get(int index) const;
    int getSize() const;
    void display() const;
};

#endif
```

**dynamicarray.cpp**
```cpp
#include "dynamicarray.h"
#include <iostream>
using namespace std;

DynamicArray::DynamicArray(int cap) : capacity(cap), size(0) {
    data = new int[capacity];
    cout << "Array created with capacity " << capacity << endl;
}

DynamicArray::~DynamicArray() {
    delete[] data;
    cout << "Array destroyed" << endl;
}

void DynamicArray::add(int value) {
    if (size >= capacity) {
        capacity *= 2;
        int* newData = new int[capacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
        cout << "Resized to capacity " << capacity << endl;
    }
    data[size++] = value;
}

int DynamicArray::get(int index) const {
    if (index >= 0 && index < size) return data[index];
    return -1;
}

int DynamicArray::getSize() const { return size; }

void DynamicArray::display() const {
    for (int i = 0; i < size; i++) cout << data[i] << " ";
    cout << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "dynamicarray.h"
using namespace std;

int main() {
    DynamicArray arr(3);
    arr.add(10);
    arr.add(20);
    arr.add(30);
    arr.add(40);
    arr.display();
    return 0;
}
```

### Example 2: Linked List with Dynamic Nodes

#### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {
        cout << "Node " << data << " created" << endl;
    }
    
    ~Node() {
        cout << "Node " << data << " destroyed" << endl;
    }
};

class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    void insert(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    
    void display() const {
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    LinkedList list;
    
    list.insert(10);
    list.insert(20);
    list.insert(30);
    
    list.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**node.h**
```cpp
#ifndef NODE_H
#define NODE_H

class Node {
public:
    int data;
    Node* next;
    
    Node(int val);
    ~Node();
};

#endif
```

**node.cpp**
```cpp
#include "node.h"
#include <iostream>
using namespace std;

Node::Node(int val) : data(val), next(nullptr) {
    cout << "Node " << data << " created" << endl;
}

Node::~Node() {
    cout << "Node " << data << " destroyed" << endl;
}
```

**linkedlist.h**
```cpp
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

class LinkedList {
private:
    Node* head;
    
public:
    LinkedList();
    ~LinkedList();
    void insert(int value);
    void display() const;
};

#endif
```

**linkedlist.cpp**
```cpp
#include "linkedlist.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void LinkedList::insert(int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

void LinkedList::display() const {
    Node* current = head;
    while (current) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "linkedlist.h"
using namespace std;

int main() {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.display();
    return 0;
}
```

### Example 3: Database Connection Pool

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DatabaseConnection {
private:
    string connectionString;
    bool connected;
    static int connectionCount;
    
public:
    DatabaseConnection(string conn) : connectionString(conn), connected(false) {
        connectionCount++;
        cout << "Connection object created. Total: " << connectionCount << endl;
    }
    
    ~DatabaseConnection() {
        if (connected) disconnect();
        connectionCount--;
        cout << "Connection object destroyed. Remaining: " << connectionCount << endl;
    }
    
    void connect() {
        if (!connected) {
            connected = true;
            cout << "Connected to " << connectionString << endl;
        }
    }
    
    void disconnect() {
        if (connected) {
            connected = false;
            cout << "Disconnected from " << connectionString << endl;
        }
    }
    
    void executeQuery(const string& query) {
        if (connected) {
            cout << "Executing: " << query << endl;
        }
    }
    
    static int getConnectionCount() { return connectionCount; }
};

int DatabaseConnection::connectionCount = 0;

class ConnectionPool {
private:
    vector<DatabaseConnection*> pool;
    string connectionString;
    int maxSize;
    
public:
    ConnectionPool(string conn, int max) : connectionString(conn), maxSize(max) {}
    
    ~ConnectionPool() {
        for (auto conn : pool) {
            delete conn;
        }
    }
    
    DatabaseConnection* acquire() {
        for (auto conn : pool) {
            if (!conn->isConnected) {  // Would need isConnected getter
                conn->connect();
                return conn;
            }
        }
        
        if (pool.size() < maxSize) {
            DatabaseConnection* newConn = new DatabaseConnection(connectionString);
            pool.push_back(newConn);
            newConn->connect();
            return newConn;
        }
        
        return nullptr;
    }
    
    void release(DatabaseConnection* conn) {
        if (conn) {
            conn->disconnect();
        }
    }
};

int main() {
    // Single connection
    DatabaseConnection* db1 = new DatabaseConnection("localhost:3306/mydb");
    db1->connect();
    db1->executeQuery("SELECT * FROM users");
    delete db1;
    
    // Array of connections
    DatabaseConnection** connections = new DatabaseConnection*[3];
    for (int i = 0; i < 3; i++) {
        connections[i] = new DatabaseConnection("localhost:3306/mydb");
        connections[i]->connect();
    }
    
    for (int i = 0; i < 3; i++) {
        delete connections[i];
    }
    delete[] connections;
    
    return 0;
}
```

#### Type 2: Multiple Files

**databaseconnection.h**
```cpp
#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <string>
using namespace std;

class DatabaseConnection {
private:
    string connectionString;
    bool connected;
    static int connectionCount;
    
public:
    DatabaseConnection(string conn);
    ~DatabaseConnection();
    void connect();
    void disconnect();
    void executeQuery(const string& query);
    static int getConnectionCount();
};

#endif
```

**databaseconnection.cpp**
```cpp
#include "databaseconnection.h"
#include <iostream>
using namespace std;

int DatabaseConnection::connectionCount = 0;

DatabaseConnection::DatabaseConnection(string conn) : connectionString(conn), connected(false) {
    connectionCount++;
    cout << "Connection created. Total: " << connectionCount << endl;
}

DatabaseConnection::~DatabaseConnection() {
    if (connected) disconnect();
    connectionCount--;
    cout << "Connection destroyed. Remaining: " << connectionCount << endl;
}

void DatabaseConnection::connect() {
    if (!connected) {
        connected = true;
        cout << "Connected to " << connectionString << endl;
    }
}

void DatabaseConnection::disconnect() {
    if (connected) {
        connected = false;
        cout << "Disconnected from " << connectionString << endl;
    }
}

void DatabaseConnection::executeQuery(const string& query) {
    if (connected) {
        cout << "Executing: " << query << endl;
    }
}

int DatabaseConnection::getConnectionCount() { return connectionCount; }
```

**main.cpp**
```cpp
#include <iostream>
#include "databaseconnection.h"
using namespace std;

int main() {
    DatabaseConnection* db = new DatabaseConnection("localhost:3306/mydb");
    db->connect();
    db->executeQuery("SELECT * FROM users");
    delete db;
    return 0;
}
```

## new and delete vs malloc/free

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

class Test {
public:
    Test() { cout << "Constructor called" << endl; }
    ~Test() { cout << "Destructor called" << endl; }
};

int main() {
    cout << "Using malloc/free (C style):" << endl;
    Test* t1 = (Test*)malloc(sizeof(Test));
    // Constructor not called!
    free(t1);
    // Destructor not called!
    
    cout << "\nUsing new/delete (C++ style):" << endl;
    Test* t2 = new Test();  // Constructor called
    delete t2;              // Destructor called
    
    return 0;
}
```

## new Handler for Out-of-Memory

```cpp
#include <iostream>
#include <new>
using namespace std;

void outOfMemoryHandler() {
    cout << "Out of memory! Cannot allocate more memory." << endl;
    throw bad_alloc();
}

int main() {
    // Set custom new handler
    set_new_handler(outOfMemoryHandler);
    
    try {
        // Try to allocate huge amount of memory
        int* huge = new int[1000000000];
        delete[] huge;
    } catch (const bad_alloc& e) {
        cout << "Caught bad_alloc exception" << endl;
    }
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting delete | Memory leak | Always delete allocated memory |
| Mismatched new/delete | Undefined behavior | Use delete for single, delete[] for arrays |
| Double delete | Undefined behavior | Set pointer to nullptr after delete |
| Using deleted memory | Crash | Don't access after delete |
| Not checking allocation failure | Crash | Use try-catch or check for nullptr |

## Summary

- **new** allocates memory and calls constructor
- **delete** calls destructor and deallocates memory
- Use **new[]** and **delete[]** for arrays
- **Placement new** constructs objects in pre-allocated memory
- Always **match** new with delete, new[] with delete[]
- Set pointers to **nullptr** after delete
- **RAII** (smart pointers) preferred over manual new/delete

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class MyClass {
private:
    int* data;
    int size;
    
public:
    MyClass(int s) : size(s) {
        data = new int[size];
        for (int i = 0; i < size; i++) data[i] = 0;
        cout << "Object created with array of size " << size << endl;
    }
    
    ~MyClass() {
        delete[] data;
        cout << "Object destroyed" << endl;
    }
};

int main() {
    MyClass* obj = new MyClass(10);
    delete obj;
    return 0;
}
```

### Type 2: Multiple Files

**myclass.h**
```cpp
#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass {
private:
    int* data;
    int size;
    
public:
    MyClass(int s);
    ~MyClass();
};

#endif
```

**myclass.cpp**
```cpp
#include "myclass.h"
#include <iostream>
using namespace std;

MyClass::MyClass(int s) : size(s) {
    data = new int[size];
    for (int i = 0; i < size; i++) data[i] = 0;
    cout << "Object created" << endl;
}

MyClass::~MyClass() {
    delete[] data;
    cout << "Object destroyed" << endl;
}
```

**main.cpp**
```cpp
#include "myclass.h"

int main() {
    MyClass* obj = new MyClass(10);
    delete obj;
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*