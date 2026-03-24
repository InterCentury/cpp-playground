# 95 - Multiple Inheritance in C++

## What is Multiple Inheritance?
Multiple inheritance allows a derived class to inherit from more than one base class. This enables a class to combine features from multiple parent classes, creating more complex relationships.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class 1
class Printable {
public:
    virtual void print() const = 0;
    virtual ~Printable() {}
};

// Base class 2
class Serializable {
public:
    virtual void serialize() const = 0;
    virtual ~Serializable() {}
};

// Derived class inheriting from both
class Document : public Printable, public Serializable {
private:
    string content;
    string title;
    
public:
    Document(string t, string c) : title(t), content(c) {}
    
    void print() const override {
        cout << "=== Document: " << title << " ===" << endl;
        cout << content << endl;
        cout << "==================" << endl;
    }
    
    void serialize() const override {
        cout << "<document>" << endl;
        cout << "  <title>" << title << "</title>" << endl;
        cout << "  <content>" << content << "</content>" << endl;
        cout << "</document>" << endl;
    }
};

int main() {
    Document doc("My Notes", "This is important content.");
    
    cout << "Printing:" << endl;
    doc.print();
    
    cout << "\nSerializing:" << endl;
    doc.serialize();
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### printable.h
```cpp
#ifndef PRINTABLE_H
#define PRINTABLE_H

class Printable {
public:
    virtual void print() const = 0;
    virtual ~Printable() {}
};

#endif
```

### serializable.h
```cpp
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

class Serializable {
public:
    virtual void serialize() const = 0;
    virtual ~Serializable() {}
};

#endif
```

### document.h
```cpp
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "printable.h"
#include "serializable.h"
#include <string>
using namespace std;

class Document : public Printable, public Serializable {
private:
    string content;
    string title;
    
public:
    Document(string t, string c);
    void print() const override;
    void serialize() const override;
};

#endif
```

### document.cpp
```cpp
#include "document.h"
#include <iostream>
using namespace std;

Document::Document(string t, string c) : title(t), content(c) {}

void Document::print() const {
    cout << "=== Document: " << title << " ===" << endl;
    cout << content << endl;
    cout << "==================" << endl;
}

void Document::serialize() const {
    cout << "<document>" << endl;
    cout << "  <title>" << title << "</title>" << endl;
    cout << "  <content>" << content << "</content>" << endl;
    cout << "</document>" << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "document.h"
using namespace std;

int main() {
    Document doc("My Notes", "Important content");
    doc.print();
    doc.serialize();
    return 0;
}
```

## Constructor and Destructor Order in Multiple Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

class Base1 {
public:
    Base1() { cout << "Base1 constructor" << endl; }
    ~Base1() { cout << "Base1 destructor" << endl; }
};

class Base2 {
public:
    Base2() { cout << "Base2 constructor" << endl; }
    ~Base2() { cout << "Base2 destructor" << endl; }
};

class Derived : public Base1, public Base2 {
public:
    Derived() { cout << "Derived constructor" << endl; }
    ~Derived() { cout << "Derived destructor" << endl; }
};

int main() {
    cout << "Creating Derived object:" << endl;
    Derived d;
    cout << "\nDestroying Derived object:" << endl;
    return 0;
}
```
Output:
```
Creating Derived object:
Base1 constructor
Base2 constructor
Derived constructor

Destroying Derived object:
Derived destructor
Base2 destructor
Base1 destructor
```

## Ambiguity in Multiple Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

class A {
public:
    void display() {
        cout << "A's display" << endl;
    }
};

class B {
public:
    void display() {
        cout << "B's display" << endl;
    }
};

class C : public A, public B {
public:
    // Resolving ambiguity
    void show() {
        A::display();  // Call A's version
        B::display();  // Call B's version
    }
    
    // Or override
    void display() {
        A::display();
    }
};

int main() {
    C c;
    // c.display();  // Error! Ambiguous
    c.A::display();   // OK - specify which base class
    c.B::display();   // OK
    c.show();         // OK - resolved in derived class
    c.display();      // OK - overridden version
    
    return 0;
}
```

## Diamond Problem and Virtual Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

// Without virtual inheritance - problem
class Animal {
protected:
    string name;
    
public:
    Animal(string n) : name(n) {
        cout << "Animal constructor: " << name << endl;
    }
    
    void eat() {
        cout << name << " is eating" << endl;
    }
};

class Mammal : public Animal {
public:
    Mammal(string n) : Animal(n) {
        cout << "Mammal constructor" << endl;
    }
};

class Winged : public Animal {
public:
    Winged(string n) : Animal(n) {
        cout << "Winged constructor" << endl;
    }
};

// Without virtual inheritance - Bat has two Animal subobjects
class Bat : public Mammal, public Winged {
public:
    Bat(string n) : Mammal(n), Winged(n) {
        cout << "Bat constructor" << endl;
    }
    // Problem: two copies of Animal! Ambiguity when calling eat()
};

int main() {
    // This would cause compilation error if uncommented
    // Bat bat("Bruce");
    // bat.eat();  // Error! Which Animal?
    
    return 0;
}
```

### Solution with Virtual Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

// With virtual inheritance - solution
class Animal {
protected:
    string name;
    
public:
    Animal(string n) : name(n) {
        cout << "Animal constructor: " << name << endl;
    }
    
    void eat() {
        cout << name << " is eating" << endl;
    }
    
    string getName() const { return name; }
};

class Mammal : virtual public Animal {
public:
    Mammal(string n) : Animal(n) {
        cout << "Mammal constructor" << endl;
    }
};

class Winged : virtual public Animal {
public:
    Winged(string n) : Animal(n) {
        cout << "Winged constructor" << endl;
    }
};

class Bat : public Mammal, public Winged {
public:
    Bat(string n) : Animal(n), Mammal(n), Winged(n) {
        cout << "Bat constructor" << endl;
    }
};

int main() {
    Bat bat("Bruce");
    bat.eat();  // Now works - only one Animal subobject
    cout << "Name: " << bat.getName() << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Employee with Multiple Roles

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
protected:
    string name;
    int age;
    
public:
    Person(string n, int a) : name(n), age(a) {
        cout << "Person created: " << name << endl;
    }
    
    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    virtual ~Person() {
        cout << "Person destroyed: " << name << endl;
    }
};

class Employee {
protected:
    int employeeId;
    double salary;
    static int nextId;
    
public:
    Employee(double s) : employeeId(nextId++), salary(s) {
        cout << "Employee created: ID=" << employeeId << endl;
    }
    
    virtual double calculateBonus() const {
        return salary * 0.1;
    }
    
    virtual void display() const {
        cout << "Employee ID: " << employeeId << ", Salary: $" << salary << endl;
    }
    
    virtual ~Employee() {
        cout << "Employee destroyed: ID=" << employeeId << endl;
    }
};

int Employee::nextId = 1000;

class Manager : public Person, public Employee {
private:
    int teamSize;
    vector<string> teamMembers;
    
public:
    Manager(string n, int a, double s, int size) 
        : Person(n, a), Employee(s), teamSize(size) {
        cout << "Manager created: " << name << " (Team: " << teamSize << ")" << endl;
    }
    
    void addTeamMember(string member) {
        teamMembers.push_back(member);
    }
    
    double calculateBonus() const override {
        return Employee::calculateBonus() + (teamSize * 500);
    }
    
    void display() const override {
        Person::display();
        Employee::display();
        cout << "Team Size: " << teamSize << endl;
        cout << "Team Members: ";
        for (const auto& m : teamMembers) {
            cout << m << " ";
        }
        cout << endl;
    }
    
    ~Manager() {
        cout << "Manager destroyed: " << name << endl;
    }
};

class Developer : public Person, public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, int a, double s, string lang, int projects) 
        : Person(n, a), Employee(s), programmingLanguage(lang), projectsCompleted(projects) {
        cout << "Developer created: " << name << " (" << lang << ")" << endl;
    }
    
    double calculateBonus() const override {
        return Employee::calculateBonus() + (projectsCompleted * 300);
    }
    
    void display() const override {
        Person::display();
        Employee::display();
        cout << "Language: " << programmingLanguage 
             << ", Projects: " << projectsCompleted << endl;
    }
    
    ~Developer() {
        cout << "Developer destroyed: " << name << endl;
    }
};

int main() {
    Manager mgr("Alice Johnson", 35, 80000, 5);
    mgr.addTeamMember("Bob");
    mgr.addTeamMember("Carol");
    
    Developer dev("Bob Smith", 28, 60000, "C++", 8);
    
    cout << "\n--- Manager Details ---" << endl;
    mgr.display();
    cout << "Bonus: $" << mgr.calculateBonus() << endl;
    
    cout << "\n--- Developer Details ---" << endl;
    dev.display();
    cout << "Bonus: $" << dev.calculateBonus() << endl;
    
    return 0;
}
```

#### Type 2: Multiple Files

**person.h**
```cpp
#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    
public:
    Person(string n, int a);
    virtual void display() const;
    virtual ~Person();
};

#endif
```

**person.cpp**
```cpp
#include "person.h"
#include <iostream>
using namespace std;

Person::Person(string n, int a) : name(n), age(a) {
    cout << "Person created: " << name << endl;
}

void Person::display() const {
    cout << "Name: " << name << ", Age: " << age << endl;
}

Person::~Person() {
    cout << "Person destroyed: " << name << endl;
}
```

**employee.h**
```cpp
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
protected:
    int employeeId;
    double salary;
    static int nextId;
    
public:
    Employee(double s);
    virtual double calculateBonus() const;
    virtual void display() const;
    virtual ~Employee();
};

#endif
```

**employee.cpp**
```cpp
#include "employee.h"
#include <iostream>
using namespace std;

int Employee::nextId = 1000;

Employee::Employee(double s) : employeeId(nextId++), salary(s) {
    cout << "Employee created: ID=" << employeeId << endl;
}

double Employee::calculateBonus() const {
    return salary * 0.1;
}

void Employee::display() const {
    cout << "Employee ID: " << employeeId << ", Salary: $" << salary << endl;
}

Employee::~Employee() {
    cout << "Employee destroyed: ID=" << employeeId << endl;
}
```

**manager.h**
```cpp
#ifndef MANAGER_H
#define MANAGER_H

#include "person.h"
#include "employee.h"
#include <string>
#include <vector>
using namespace std;

class Manager : public Person, public Employee {
private:
    int teamSize;
    vector<string> teamMembers;
    
public:
    Manager(string n, int a, double s, int size);
    void addTeamMember(string member);
    double calculateBonus() const override;
    void display() const override;
    ~Manager();
};

#endif
```

**manager.cpp**
```cpp
#include "manager.h"
#include <iostream>
using namespace std;

Manager::Manager(string n, int a, double s, int size) 
    : Person(n, a), Employee(s), teamSize(size) {
    cout << "Manager created: " << name << " (Team: " << teamSize << ")" << endl;
}

void Manager::addTeamMember(string member) {
    teamMembers.push_back(member);
}

double Manager::calculateBonus() const override {
    return Employee::calculateBonus() + (teamSize * 500);
}

void Manager::display() const override {
    Person::display();
    Employee::display();
    cout << "Team Size: " << teamSize << endl;
    cout << "Team Members: ";
    for (const auto& m : teamMembers) {
        cout << m << " ";
    }
    cout << endl;
}

Manager::~Manager() {
    cout << "Manager destroyed: " << name << endl;
}
```

**developer.h**
```cpp
#ifndef DEVELOPER_H
#define DEVELOPER_H

#include "person.h"
#include "employee.h"
#include <string>
using namespace std;

class Developer : public Person, public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, int a, double s, string lang, int projects);
    double calculateBonus() const override;
    void display() const override;
    ~Developer();
};

#endif
```

**developer.cpp**
```cpp
#include "developer.h"
#include <iostream>
using namespace std;

Developer::Developer(string n, int a, double s, string lang, int projects) 
    : Person(n, a), Employee(s), programmingLanguage(lang), projectsCompleted(projects) {
    cout << "Developer created: " << name << " (" << lang << ")" << endl;
}

double Developer::calculateBonus() const override {
    return Employee::calculateBonus() + (projectsCompleted * 300);
}

void Developer::display() const override {
    Person::display();
    Employee::display();
    cout << "Language: " << programmingLanguage 
         << ", Projects: " << projectsCompleted << endl;
}

Developer::~Developer() {
    cout << "Developer destroyed: " << name << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "manager.h"
#include "developer.h"
using namespace std;

int main() {
    Manager mgr("Alice", 35, 80000, 5);
    mgr.addTeamMember("Bob");
    
    Developer dev("Bob", 28, 60000, "C++", 8);
    
    mgr.display();
    dev.display();
    
    return 0;
}
```

### Example 2: Smart Device with Multiple Interfaces

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class NetworkDevice {
protected:
    string ipAddress;
    bool connected;
    
public:
    NetworkDevice() : ipAddress("0.0.0.0"), connected(false) {}
    
    virtual void connect(const string& ip) {
        ipAddress = ip;
        connected = true;
        cout << "Connected to network at " << ipAddress << endl;
    }
    
    virtual void disconnect() {
        connected = false;
        cout << "Disconnected from network" << endl;
    }
    
    virtual void sendData(const string& data) {
        if (connected) {
            cout << "Sending data: " << data << endl;
        } else {
            cout << "Not connected!" << endl;
        }
    }
    
    virtual ~NetworkDevice() {}
};

class StorageDevice {
protected:
    int capacity;
    int usedSpace;
    
public:
    StorageDevice(int cap) : capacity(cap), usedSpace(0) {}
    
    virtual void storeData(const string& data, int size) {
        if (usedSpace + size <= capacity) {
            usedSpace += size;
            cout << "Stored " << size << "MB. Used: " << usedSpace << "/" << capacity << "MB" << endl;
        } else {
            cout << "Insufficient storage!" << endl;
        }
    }
    
    virtual int getFreeSpace() const {
        return capacity - usedSpace;
    }
    
    virtual ~StorageDevice() {}
};

class MediaDevice {
protected:
    bool playing;
    int volume;
    
public:
    MediaDevice() : playing(false), volume(50) {}
    
    virtual void play() {
        playing = true;
        cout << "Playing media at volume " << volume << endl;
    }
    
    virtual void stop() {
        playing = false;
        cout << "Stopped playback" << endl;
    }
    
    virtual void setVolume(int vol) {
        volume = min(100, max(0, vol));
        cout << "Volume set to " << volume << endl;
    }
    
    virtual ~MediaDevice() {}
};

class SmartTV : public NetworkDevice, public MediaDevice, public StorageDevice {
private:
    string model;
    vector<string> apps;
    
public:
    SmartTV(string m, int storage) : StorageDevice(storage), model(m) {
        cout << "SmartTV created: " << model << endl;
    }
    
    void installApp(const string& app) {
        apps.push_back(app);
        cout << "Installed app: " << app << endl;
    }
    
    void streamVideo(const string& url) {
        if (connected) {
            cout << "Streaming video from: " << url << endl;
            play();
        } else {
            cout << "Cannot stream - not connected to network!" << endl;
        }
    }
    
    void recordShow(int duration) {
        int requiredSpace = duration * 100; // 100MB per hour
        storeData("Recording", requiredSpace);
        if (getFreeSpace() >= requiredSpace) {
            cout << "Recording show for " << duration << " minutes" << endl;
        }
    }
    
    void display() const {
        cout << "\n=== SmartTV Info ===" << endl;
        cout << "Model: " << model << endl;
        cout << "Network: " << (connected ? "Connected" : "Disconnected") 
             << " (" << ipAddress << ")" << endl;
        cout << "Storage: " << getFreeSpace() << "/" << capacity << "MB free" << endl;
        cout << "Volume: " << volume << endl;
        cout << "Playing: " << (playing ? "Yes" : "No") << endl;
        cout << "Apps installed: ";
        for (const auto& app : apps) cout << app << " ";
        cout << endl;
    }
};

int main() {
    SmartTV tv("Samsung QLED 65", 10000);
    
    tv.connect("192.168.1.100");
    tv.installApp("Netflix");
    tv.installApp("YouTube");
    tv.setVolume(75);
    tv.streamVideo("https://example.com/movie");
    tv.recordShow(30);
    
    tv.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**networkdevice.h**
```cpp
#ifndef NETWORKDEVICE_H
#define NETWORKDEVICE_H

#include <string>
using namespace std;

class NetworkDevice {
protected:
    string ipAddress;
    bool connected;
    
public:
    NetworkDevice();
    virtual void connect(const string& ip);
    virtual void disconnect();
    virtual void sendData(const string& data);
    virtual ~NetworkDevice();
};

#endif
```

**networkdevice.cpp**
```cpp
#include "networkdevice.h"
#include <iostream>
using namespace std;

NetworkDevice::NetworkDevice() : ipAddress("0.0.0.0"), connected(false) {}

void NetworkDevice::connect(const string& ip) {
    ipAddress = ip;
    connected = true;
    cout << "Connected to network at " << ipAddress << endl;
}

void NetworkDevice::disconnect() {
    connected = false;
    cout << "Disconnected from network" << endl;
}

void NetworkDevice::sendData(const string& data) {
    if (connected) {
        cout << "Sending data: " << data << endl;
    } else {
        cout << "Not connected!" << endl;
    }
}

NetworkDevice::~NetworkDevice() {}
```

**storagedevice.h**
```cpp
#ifndef STORAGEDEVICE_H
#define STORAGEDEVICE_H

#include <string>
using namespace std;

class StorageDevice {
protected:
    int capacity;
    int usedSpace;
    
public:
    StorageDevice(int cap);
    virtual void storeData(const string& data, int size);
    virtual int getFreeSpace() const;
    virtual ~StorageDevice();
};

#endif
```

**storagedevice.cpp**
```cpp
#include "storagedevice.h"
#include <iostream>
using namespace std;

StorageDevice::StorageDevice(int cap) : capacity(cap), usedSpace(0) {}

void StorageDevice::storeData(const string& data, int size) {
    if (usedSpace + size <= capacity) {
        usedSpace += size;
        cout << "Stored " << size << "MB. Used: " << usedSpace << "/" << capacity << "MB" << endl;
    } else {
        cout << "Insufficient storage!" << endl;
    }
}

int StorageDevice::getFreeSpace() const {
    return capacity - usedSpace;
}

StorageDevice::~StorageDevice() {}
```

**mediadevice.h**
```cpp
#ifndef MEDIADEVICE_H
#define MEDIADEVICE_H

class MediaDevice {
protected:
    bool playing;
    int volume;
    
public:
    MediaDevice();
    virtual void play();
    virtual void stop();
    virtual void setVolume(int vol);
    virtual ~MediaDevice();
};

#endif
```

**mediadevice.cpp**
```cpp
#include "mediadevice.h"
#include <iostream>
#include <algorithm>
using namespace std;

MediaDevice::MediaDevice() : playing(false), volume(50) {}

void MediaDevice::play() {
    playing = true;
    cout << "Playing media at volume " << volume << endl;
}

void MediaDevice::stop() {
    playing = false;
    cout << "Stopped playback" << endl;
}

void MediaDevice::setVolume(int vol) {
    volume = min(100, max(0, vol));
    cout << "Volume set to " << volume << endl;
}

MediaDevice::~MediaDevice() {}
```

**smarttv.h**
```cpp
#ifndef SMARTTV_H
#define SMARTTV_H

#include "networkdevice.h"
#include "storagedevice.h"
#include "mediadevice.h"
#include <string>
#include <vector>
using namespace std;

class SmartTV : public NetworkDevice, public MediaDevice, public StorageDevice {
private:
    string model;
    vector<string> apps;
    
public:
    SmartTV(string m, int storage);
    void installApp(const string& app);
    void streamVideo(const string& url);
    void recordShow(int duration);
    void display() const;
};

#endif
```

**smarttv.cpp**
```cpp
#include "smarttv.h"
#include <iostream>
using namespace std;

SmartTV::SmartTV(string m, int storage) : StorageDevice(storage), model(m) {
    cout << "SmartTV created: " << model << endl;
}

void SmartTV::installApp(const string& app) {
    apps.push_back(app);
    cout << "Installed app: " << app << endl;
}

void SmartTV::streamVideo(const string& url) {
    if (connected) {
        cout << "Streaming video from: " << url << endl;
        play();
    } else {
        cout << "Cannot stream - not connected to network!" << endl;
    }
}

void SmartTV::recordShow(int duration) {
    int requiredSpace = duration * 100;
    storeData("Recording", requiredSpace);
    if (getFreeSpace() >= requiredSpace) {
        cout << "Recording show for " << duration << " minutes" << endl;
    }
}

void SmartTV::display() const {
    cout << "\n=== SmartTV Info ===" << endl;
    cout << "Model: " << model << endl;
    cout << "Network: " << (connected ? "Connected" : "Disconnected") 
         << " (" << ipAddress << ")" << endl;
    cout << "Storage: " << getFreeSpace() << "/" << capacity << "MB free" << endl;
    cout << "Volume: " << volume << endl;
    cout << "Playing: " << (playing ? "Yes" : "No") << endl;
    cout << "Apps: ";
    for (const auto& app : apps) cout << app << " ";
    cout << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "smarttv.h"
using namespace std;

int main() {
    SmartTV tv("Samsung QLED", 10000);
    
    tv.connect("192.168.1.100");
    tv.installApp("Netflix");
    tv.setVolume(75);
    tv.streamVideo("https://example.com/movie");
    tv.display();
    
    return 0;
}
```

### Example 3: Flying Car (Multiple Inheritance)

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;
    
public:
    Vehicle(string mk, string md, int y) : make(mk), model(md), year(y) {
        cout << "Vehicle created: " << make << " " << model << endl;
    }
    
    virtual void start() {
        cout << make << " " << model << " starting engine" << endl;
    }
    
    virtual void stop() {
        cout << make << " " << model << " stopping engine" << endl;
    }
    
    virtual void display() const {
        cout << year << " " << make << " " << model << endl;
    }
    
    virtual ~Vehicle() {
        cout << "Vehicle destroyed: " << make << " " << model << endl;
    }
};

class Aircraft {
protected:
    int maxAltitude;
    string registration;
    
public:
    Aircraft(int alt, string reg) : maxAltitude(alt), registration(reg) {
        cout << "Aircraft created: " << registration << " (Alt: " << maxAltitude << "ft)" << endl;
    }
    
    virtual void takeoff() {
        cout << registration << " taking off" << endl;
    }
    
    virtual void land() {
        cout << registration << " landing" << endl;
    }
    
    virtual void fly() {
        cout << registration << " flying at " << maxAltitude << " feet" << endl;
    }
    
    virtual ~Aircraft() {
        cout << "Aircraft destroyed: " << registration << endl;
    }
};

class FlyingCar : public Vehicle, public Aircraft {
private:
    string color;
    bool isFlying;
    
public:
    FlyingCar(string mk, string md, int y, string reg, int alt, string col) 
        : Vehicle(mk, md, y), Aircraft(alt, reg), color(col), isFlying(false) {
        cout << "FlyingCar created: " << color << " " << make << " " << model << endl;
    }
    
    void drive() {
        if (!isFlying) {
            cout << "Driving " << make << " " << model << " on roads" << endl;
        } else {
            cout << "Cannot drive while flying!" << endl;
        }
    }
    
    void start() override {
        if (!isFlying) {
            Vehicle::start();
        } else {
            cout << "Already flying!" << endl;
        }
    }
    
    void takeoff() override {
        if (!isFlying) {
            Aircraft::takeoff();
            isFlying = true;
        } else {
            cout << "Already flying!" << endl;
        }
    }
    
    void land() override {
        if (isFlying) {
            Aircraft::land();
            isFlying = false;
        } else {
            cout << "Not flying!" << endl;
        }
    }
    
    void fly() override {
        if (isFlying) {
            Aircraft::fly();
        } else {
            cout << "Cannot fly - not in air!" << endl;
        }
    }
    
    void display() const override {
        Vehicle::display();
        cout << "Registration: " << registration << ", Color: " << color << endl;
        cout << "Max Altitude: " << maxAltitude << "ft, Status: " 
             << (isFlying ? "Flying" : "On ground") << endl;
    }
    
    ~FlyingCar() {
        cout << "FlyingCar destroyed: " << make << " " << model << endl;
    }
};

int main() {
    FlyingCar flyingCar("Terrafugia", "Transition", 2023, "N123FC", 10000, "Silver");
    
    cout << "\n--- Ground Mode ---" << endl;
    flyingCar.start();
    flyingCar.drive();
    
    cout << "\n--- Transition to Air ---" << endl;
    flyingCar.takeoff();
    flyingCar.fly();
    
    cout << "\n--- Back to Ground ---" << endl;
    flyingCar.land();
    flyingCar.drive();
    
    cout << "\n--- Final Status ---" << endl;
    flyingCar.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**vehicle.h**
```cpp
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;
    
public:
    Vehicle(string mk, string md, int y);
    virtual void start();
    virtual void stop();
    virtual void display() const;
    virtual ~Vehicle();
};

#endif
```

**vehicle.cpp**
```cpp
#include "vehicle.h"
#include <iostream>
using namespace std;

Vehicle::Vehicle(string mk, string md, int y) : make(mk), model(md), year(y) {
    cout << "Vehicle created: " << make << " " << model << endl;
}

void Vehicle::start() {
    cout << make << " " << model << " starting engine" << endl;
}

void Vehicle::stop() {
    cout << make << " " << model << " stopping engine" << endl;
}

void Vehicle::display() const {
    cout << year << " " << make << " " << model << endl;
}

Vehicle::~Vehicle() {
    cout << "Vehicle destroyed: " << make << " " << model << endl;
}
```

**aircraft.h**
```cpp
#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
using namespace std;

class Aircraft {
protected:
    int maxAltitude;
    string registration;
    
public:
    Aircraft(int alt, string reg);
    virtual void takeoff();
    virtual void land();
    virtual void fly();
    virtual ~Aircraft();
};

#endif
```

**aircraft.cpp**
```cpp
#include "aircraft.h"
#include <iostream>
using namespace std;

Aircraft::Aircraft(int alt, string reg) : maxAltitude(alt), registration(reg) {
    cout << "Aircraft created: " << registration << " (Alt: " << maxAltitude << "ft)" << endl;
}

void Aircraft::takeoff() {
    cout << registration << " taking off" << endl;
}

void Aircraft::land() {
    cout << registration << " landing" << endl;
}

void Aircraft::fly() {
    cout << registration << " flying at " << maxAltitude << " feet" << endl;
}

Aircraft::~Aircraft() {
    cout << "Aircraft destroyed: " << registration << endl;
}
```

**flyingcar.h**
```cpp
#ifndef FLYINGCAR_H
#define FLYINGCAR_H

#include "vehicle.h"
#include "aircraft.h"
#include <string>
using namespace std;

class FlyingCar : public Vehicle, public Aircraft {
private:
    string color;
    bool isFlying;
    
public:
    FlyingCar(string mk, string md, int y, string reg, int alt, string col);
    void drive();
    void start() override;
    void takeoff() override;
    void land() override;
    void fly() override;
    void display() const override;
    ~FlyingCar();
};

#endif
```

**flyingcar.cpp**
```cpp
#include "flyingcar.h"
#include <iostream>
using namespace std;

FlyingCar::FlyingCar(string mk, string md, int y, string reg, int alt, string col) 
    : Vehicle(mk, md, y), Aircraft(alt, reg), color(col), isFlying(false) {
    cout << "FlyingCar created: " << color << " " << make << " " << model << endl;
}

void FlyingCar::drive() {
    if (!isFlying) {
        cout << "Driving " << make << " " << model << " on roads" << endl;
    } else {
        cout << "Cannot drive while flying!" << endl;
    }
}

void FlyingCar::start() override {
    if (!isFlying) {
        Vehicle::start();
    } else {
        cout << "Already flying!" << endl;
    }
}

void FlyingCar::takeoff() override {
    if (!isFlying) {
        Aircraft::takeoff();
        isFlying = true;
    } else {
        cout << "Already flying!" << endl;
    }
}

void FlyingCar::land() override {
    if (isFlying) {
        Aircraft::land();
        isFlying = false;
    } else {
        cout << "Not flying!" << endl;
    }
}

void FlyingCar::fly() override {
    if (isFlying) {
        Aircraft::fly();
    } else {
        cout << "Cannot fly - not in air!" << endl;
    }
}

void FlyingCar::display() const override {
    Vehicle::display();
    cout << "Registration: " << registration << ", Color: " << color << endl;
    cout << "Max Altitude: " << maxAltitude << "ft, Status: " 
         << (isFlying ? "Flying" : "On ground") << endl;
}

FlyingCar::~FlyingCar() {
    cout << "FlyingCar destroyed: " << make << " " << model << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "flyingcar.h"
using namespace std;

int main() {
    FlyingCar car("Terrafugia", "Transition", 2023, "N123FC", 10000, "Silver");
    
    car.start();
    car.drive();
    car.takeoff();
    car.fly();
    car.land();
    car.drive();
    car.display();
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Diamond problem | Multiple base copies | Use virtual inheritance |
| Ambiguity | Name conflicts | Use scope resolution or override |
| Constructor order confusion | Incorrect initialization | Follow declaration order |
| Object slicing | Loss of derived data | Use pointers/references |
| Forgetting virtual destructors | Memory leak | Make base destructors virtual |

## Summary

- **Multiple inheritance** allows inheriting from multiple base classes
- **Constructor order** follows declaration order
- **Destructor order** is reverse of constructor order
- **Virtual inheritance** solves diamond problem
- **Ambiguity** resolved with scope resolution `Base::member`
- Use **multiple inheritance** when class truly "is-a" multiple types
- Prefer **composition** over multiple inheritance when possible

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class Base1 {
protected:
    int value1;
    
public:
    Base1(int v1) : value1(v1) {
        cout << "Base1 constructor" << endl;
    }
    
    virtual void show() const {
        cout << "Base1: " << value1 << endl;
    }
    
    virtual ~Base1() {}
};

class Base2 {
protected:
    int value2;
    
public:
    Base2(int v2) : value2(v2) {
        cout << "Base2 constructor" << endl;
    }
    
    virtual void show() const {
        cout << "Base2: " << value2 << endl;
    }
    
    virtual ~Base2() {}
};

class Derived : public Base1, public Base2 {
private:
    int extra;
    
public:
    Derived(int v1, int v2, int e) : Base1(v1), Base2(v2), extra(e) {
        cout << "Derived constructor" << endl;
    }
    
    void show() const override {
        Base1::show();
        Base2::show();
        cout << "Derived extra: " << extra << endl;
    }
};

int main() {
    Derived d(10, 20, 30);
    d.show();
    return 0;
}
```

### Type 2: Multiple Files

**base1.h**
```cpp
#ifndef BASE1_H
#define BASE1_H

class Base1 {
protected:
    int value1;
    
public:
    Base1(int v1);
    virtual void show() const;
    virtual ~Base1();
};

#endif
```

**base1.cpp**
```cpp
#include "base1.h"
#include <iostream>
using namespace std;

Base1::Base1(int v1) : value1(v1) {
    cout << "Base1 constructor" << endl;
}

void Base1::show() const {
    cout << "Base1: " << value1 << endl;
}

Base1::~Base1() {}
```

**base2.h**
```cpp
#ifndef BASE2_H
#define BASE2_H

class Base2 {
protected:
    int value2;
    
public:
    Base2(int v2);
    virtual void show() const;
    virtual ~Base2();
};

#endif
```

**base2.cpp**
```cpp
#include "base2.h"
#include <iostream>
using namespace std;

Base2::Base2(int v2) : value2(v2) {
    cout << "Base2 constructor" << endl;
}

void Base2::show() const {
    cout << "Base2: " << value2 << endl;
}

Base2::~Base2() {}
```

**derived.h**
```cpp
#ifndef DERIVED_H
#define DERIVED_H

#include "base1.h"
#include "base2.h"

class Derived : public Base1, public Base2 {
private:
    int extra;
    
public:
    Derived(int v1, int v2, int e);
    void show() const override;
};

#endif
```

**derived.cpp**
```cpp
#include "derived.h"
#include <iostream>
using namespace std;

Derived::Derived(int v1, int v2, int e) : Base1(v1), Base2(v2), extra(e) {
    cout << "Derived constructor" << endl;
}

void Derived::show() const {
    Base1::show();
    Base2::show();
    cout << "Derived extra: " << extra << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "derived.h"
using namespace std;

int main() {
    Derived d(10, 20, 30);
    d.show();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*