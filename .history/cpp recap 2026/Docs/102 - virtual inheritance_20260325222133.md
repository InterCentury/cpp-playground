# 102 - Virtual Inheritance in C++

## What is Virtual Inheritance?
Virtual inheritance is a technique used in multiple inheritance to solve the diamond problem. It ensures that only one copy of a base class is inherited by a derived class, even if the base class appears multiple times in the inheritance hierarchy.

## The Diamond Problem (Without Virtual Inheritance)

```cpp
#include <iostream>
using namespace std;

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
    
    virtual ~Animal() {
        cout << "Animal destructor: " << name << endl;
    }
};

class Mammal : public Animal {
public:
    Mammal(string n) : Animal(n) {
        cout << "Mammal constructor" << endl;
    }
    
    void feedMilk() {
        cout << name << " is feeding milk" << endl;
    }
    
    ~Mammal() {
        cout << "Mammal destructor" << endl;
    }
};

class Winged : public Animal {
public:
    Winged(string n) : Animal(n) {
        cout << "Winged constructor" << endl;
    }
    
    void fly() {
        cout << name << " is flying" << endl;
    }
    
    ~Winged() {
        cout << "Winged destructor" << endl;
    }
};

// PROBLEM: Bat inherits two copies of Animal!
class Bat : public Mammal, public Winged {
public:
    Bat(string n) : Mammal(n), Winged(n) {
        cout << "Bat constructor" << endl;
    }
    
    ~Bat() {
        cout << "Bat destructor" << endl;
    }
};

int main() {
    // This would cause ambiguity errors
    // Bat bat("Bruce");
    // bat.eat();  // Error! Which Animal?
    
    return 0;
}
```

## Solution with Virtual Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

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
    
    virtual ~Animal() {
        cout << "Animal destructor: " << name << endl;
    }
};

// Virtual inheritance - only one Animal subobject
class Mammal : virtual public Animal {
public:
    Mammal(string n) : Animal(n) {
        cout << "Mammal constructor" << endl;
    }
    
    void feedMilk() {
        cout << name << " is feeding milk" << endl;
    }
    
    ~Mammal() {
        cout << "Mammal destructor" << endl;
    }
};

class Winged : virtual public Animal {
public:
    Winged(string n) : Animal(n) {
        cout << "Winged constructor" << endl;
    }
    
    void fly() {
        cout << name << " is flying" << endl;
    }
    
    ~Winged() {
        cout << "Winged destructor" << endl;
    }
};

// Bat now has only one Animal subobject
class Bat : public Mammal, public Winged {
public:
    Bat(string n) : Animal(n), Mammal(n), Winged(n) {
        cout << "Bat constructor" << endl;
    }
    
    void display() {
        cout << "Bat: " << getName() << endl;
    }
    
    ~Bat() {
        cout << "Bat destructor" << endl;
    }
};

int main() {
    Bat bat("Bruce");
    
    bat.eat();        // Now works fine - only one Animal
    bat.feedMilk();
    bat.fly();
    bat.display();
    
    return 0;
}
```

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Person {
protected:
    string name;
    int age;
    
public:
    Person(string n, int a) : name(n), age(a) {
        cout << "Person constructor: " << name << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    virtual ~Person() {
        cout << "Person destructor: " << name << endl;
    }
};

// Employee with virtual inheritance
class Employee : virtual public Person {
protected:
    int employeeId;
    double salary;
    static int nextId;
    
public:
    Employee(string n, int a, double s) : Person(n, a), salary(s) {
        employeeId = nextId++;
        cout << "Employee constructor: ID=" << employeeId << endl;
    }
    
    void work() {
        cout << name << " is working" << endl;
    }
    
    void display() const {
        Person::display();
        cout << "Employee ID: " << employeeId << ", Salary: $" << salary << endl;
    }
    
    ~Employee() {
        cout << "Employee destructor: ID=" << employeeId << endl;
    }
};

int Employee::nextId = 1000;

// Student with virtual inheritance
class Student : virtual public Person {
protected:
    int studentId;
    double gpa;
    static int nextStudentId;
    
public:
    Student(string n, int a, double g) : Person(n, a), gpa(g) {
        studentId = nextStudentId++;
        cout << "Student constructor: ID=" << studentId << endl;
    }
    
    void study() {
        cout << name << " is studying" << endl;
    }
    
    void display() const {
        Person::display();
        cout << "Student ID: " << studentId << ", GPA: " << gpa << endl;
    }
    
    ~Student() {
        cout << "Student destructor: ID=" << studentId << endl;
    }
};

int Student::nextStudentId = 5000;

// WorkingStudent - multiple inheritance with virtual base
class WorkingStudent : public Employee, public Student {
private:
    string company;
    string university;
    
public:
    WorkingStudent(string n, int a, double s, double g, string comp, string uni)
        : Person(n, a), Employee(n, a, s), Student(n, a, g), company(comp), university(uni) {
        cout << "WorkingStudent constructor: " << name << " works at " << company 
             << " and studies at " << university << endl;
    }
    
    void display() const {
        Person::display();
        cout << "Employee ID: " << employeeId << ", Student ID: " << studentId << endl;
        cout << "Salary: $" << salary << ", GPA: " << gpa << endl;
        cout << "Company: " << company << ", University: " << university << endl;
    }
    
    double calculateBonus() const {
        return salary * 0.1 + (gpa * 500);
    }
    
    ~WorkingStudent() {
        cout << "WorkingStudent destructor: " << name << endl;
    }
};

int main() {
    WorkingStudent ws("Alice Johnson", 25, 60000, 3.8, "Tech Corp", "State University");
    
    cout << "\n=== Working Student Details ===" << endl;
    ws.display();
    cout << "Bonus: $" << ws.calculateBonus() << endl;
    
    cout << "\n=== Actions ===" << endl;
    ws.work();
    ws.study();
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### person.h
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
    void display() const;
    virtual ~Person();
};

#endif
```

### person.cpp
```cpp
#include "person.h"
#include <iostream>
using namespace std;

Person::Person(string n, int a) : name(n), age(a) {
    cout << "Person constructor: " << name << endl;
}

void Person::display() const {
    cout << "Name: " << name << ", Age: " << age << endl;
}

Person::~Person() {
    cout << "Person destructor: " << name << endl;
}
```

### employee.h
```cpp
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "person.h"
#include <string>
using namespace std;

class Employee : virtual public Person {
protected:
    int employeeId;
    double salary;
    static int nextId;
    
public:
    Employee(string n, int a, double s);
    void work();
    void display() const;
    ~Employee();
};

#endif
```

### employee.cpp
```cpp
#include "employee.h"
#include <iostream>
using namespace std;

int Employee::nextId = 1000;

Employee::Employee(string n, int a, double s) : Person(n, a), salary(s) {
    employeeId = nextId++;
    cout << "Employee constructor: ID=" << employeeId << endl;
}

void Employee::work() {
    cout << name << " is working" << endl;
}

void Employee::display() const {
    Person::display();
    cout << "Employee ID: " << employeeId << ", Salary: $" << salary << endl;
}

Employee::~Employee() {
    cout << "Employee destructor: ID=" << employeeId << endl;
}
```

### student.h
```cpp
#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include <string>
using namespace std;

class Student : virtual public Person {
protected:
    int studentId;
    double gpa;
    static int nextStudentId;
    
public:
    Student(string n, int a, double g);
    void study();
    void display() const;
    ~Student();
};

#endif
```

### student.cpp
```cpp
#include "student.h"
#include <iostream>
using namespace std;

int Student::nextStudentId = 5000;

Student::Student(string n, int a, double g) : Person(n, a), gpa(g) {
    studentId = nextStudentId++;
    cout << "Student constructor: ID=" << studentId << endl;
}

void Student::study() {
    cout << name << " is studying" << endl;
}

void Student::display() const {
    Person::display();
    cout << "Student ID: " << studentId << ", GPA: " << gpa << endl;
}

Student::~Student() {
    cout << "Student destructor: ID=" << studentId << endl;
}
```

### workingstudent.h
```cpp
#ifndef WORKINGSTUDENT_H
#define WORKINGSTUDENT_H

#include "employee.h"
#include "student.h"
#include <string>
using namespace std;

class WorkingStudent : public Employee, public Student {
private:
    string company;
    string university;
    
public:
    WorkingStudent(string n, int a, double s, double g, string comp, string uni);
    void display() const;
    double calculateBonus() const;
    ~WorkingStudent();
};

#endif
```

### workingstudent.cpp
```cpp
#include "workingstudent.h"
#include <iostream>
using namespace std;

WorkingStudent::WorkingStudent(string n, int a, double s, double g, string comp, string uni)
    : Person(n, a), Employee(n, a, s), Student(n, a, g), company(comp), university(uni) {
    cout << "WorkingStudent constructor: " << name << " works at " << company 
         << " and studies at " << university << endl;
}

void WorkingStudent::display() const {
    Person::display();
    cout << "Employee ID: " << employeeId << ", Student ID: " << studentId << endl;
    cout << "Salary: $" << salary << ", GPA: " << gpa << endl;
    cout << "Company: " << company << ", University: " << university << endl;
}

double WorkingStudent::calculateBonus() const {
    return salary * 0.1 + (gpa * 500);
}

WorkingStudent::~WorkingStudent() {
    cout << "WorkingStudent destructor: " << name << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "workingstudent.h"
using namespace std;

int main() {
    WorkingStudent ws("Alice", 25, 60000, 3.8, "Tech Corp", "University");
    ws.display();
    cout << "Bonus: $" << ws.calculateBonus() << endl;
    return 0;
}
```

## Constructor Order with Virtual Inheritance

```cpp
#include <iostream>
using namespace std;

class GrandParent {
public:
    GrandParent() { cout << "GrandParent constructor" << endl; }
    ~GrandParent() { cout << "GrandParent destructor" << endl; }
};

class Parent1 : virtual public GrandParent {
public:
    Parent1() { cout << "Parent1 constructor" << endl; }
    ~Parent1() { cout << "Parent1 destructor" << endl; }
};

class Parent2 : virtual public GrandParent {
public:
    Parent2() { cout << "Parent2 constructor" << endl; }
    ~Parent2() { cout << "Parent2 destructor" << endl; }
};

class Child : public Parent1, public Parent2 {
public:
    Child() { cout << "Child constructor" << endl; }
    ~Child() { cout << "Child destructor" << endl; }
};

int main() {
    cout << "Creating Child object:" << endl;
    Child c;
    cout << "\nDestroying Child object:" << endl;
    return 0;
}
```

## Constructor Order Comparison

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructor" << endl; }
    ~Base() { cout << "Base destructor" << endl; }
};

// Without virtual inheritance
class NoVirtualA : public Base {
public:
    NoVirtualA() { cout << "NoVirtualA constructor" << endl; }
    ~NoVirtualA() { cout << "NoVirtualA destructor" << endl; }
};

class NoVirtualB : public Base {
public:
    NoVirtualB() { cout << "NoVirtualB constructor" << endl; }
    ~NoVirtualB() { cout << "NoVirtualB destructor" << endl; }
};

class NoVirtualChild : public NoVirtualA, public NoVirtualB {
public:
    NoVirtualChild() { cout << "NoVirtualChild constructor" << endl; }
    ~NoVirtualChild() { cout << "NoVirtualChild destructor" << endl; }
};

// With virtual inheritance
class VirtualA : virtual public Base {
public:
    VirtualA() { cout << "VirtualA constructor" << endl; }
    ~VirtualA() { cout << "VirtualA destructor" << endl; }
};

class VirtualB : virtual public Base {
public:
    VirtualB() { cout << "VirtualB constructor" << endl; }
    ~VirtualB() { cout << "VirtualB destructor" << endl; }
};

class VirtualChild : public VirtualA, public VirtualB {
public:
    VirtualChild() { cout << "VirtualChild constructor" << endl; }
    ~VirtualChild() { cout << "VirtualChild destructor" << endl; }
};

int main() {
    cout << "=== Without Virtual Inheritance (Two Base copies) ===" << endl;
    NoVirtualChild nvc;
    
    cout << "\n=== With Virtual Inheritance (One Base copy) ===" << endl;
    VirtualChild vc;
    
    return 0;
}
```

## Practical Examples

### Example 1: Device Hierarchy with Virtual Inheritance

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
using namespace std;

class Device {
protected:
    string deviceId;
    bool poweredOn;
    static int nextId;
    
public:
    Device() : poweredOn(false) {
        deviceId = "DEV" + to_string(nextId++);
        cout << "Device created: " << deviceId << endl;
    }
    
    void powerOn() {
        poweredOn = true;
        cout << deviceId << " powered on" << endl;
    }
    
    void powerOff() {
        poweredOn = false;
        cout << deviceId << " powered off" << endl;
    }
    
    virtual void display() const {
        cout << "Device: " << deviceId << ", Status: " << (poweredOn ? "ON" : "OFF") << endl;
    }
    
    virtual ~Device() {
        cout << "Device destroyed: " << deviceId << endl;
    }
};

int Device::nextId = 1;

class Connectable : virtual public Device {
protected:
    string ipAddress;
    bool connected;
    
public:
    Connectable() : ipAddress("0.0.0.0"), connected(false) {
        cout << "Connectable created" << endl;
    }
    
    void connect(const string& ip) {
        ipAddress = ip;
        connected = true;
        cout << deviceId << " connected to " << ipAddress << endl;
    }
    
    void disconnect() {
        connected = false;
        cout << deviceId << " disconnected" << endl;
    }
    
    void display() const override {
        Device::display();
        cout << "Network: " << (connected ? "Connected" : "Disconnected") 
             << " (" << ipAddress << ")" << endl;
    }
    
    ~Connectable() {
        cout << "Connectable destroyed" << endl;
    }
};

class Programmable : virtual public Device {
protected:
    string firmware;
    int version;
    
public:
    Programmable() : firmware("1.0"), version(1) {
        cout << "Programmable created" << endl;
    }
    
    void updateFirmware(const string& newFirmware) {
        firmware = newFirmware;
        version++;
        cout << deviceId << " firmware updated to v" << version << " (" << firmware << ")" << endl;
    }
    
    void display() const override {
        Device::display();
        cout << "Firmware: v" << version << " (" << firmware << ")" << endl;
    }
    
    ~Programmable() {
        cout << "Programmable destroyed" << endl;
    }
};

class SmartTV : public Connectable, public Programmable {
private:
    string resolution;
    int screenSize;
    
public:
    SmartTV(string res, int size) : resolution(res), screenSize(size) {
        cout << "SmartTV created: " << screenSize << "\" " << resolution << endl;
    }
    
    void display() const override {
        Device::display();
        cout << "Screen: " << screenSize << "\" " << resolution << endl;
        cout << "Network: " << (connected ? "Connected" : "Disconnected") 
             << " (" << ipAddress << ")" << endl;
        cout << "Firmware: v" << version << " (" << firmware << ")" << endl;
    }
    
    void streamContent(const string& content) {
        if (poweredOn && connected) {
            cout << deviceId << " streaming: " << content << endl;
        } else {
            cout << deviceId << " cannot stream - check power and network" << endl;
        }
    }
    
    ~SmartTV() {
        cout << "SmartTV destroyed" << endl;
    }
};

int main() {
    SmartTV tv("4K", 65);
    
    tv.powerOn();
    tv.connect("192.168.1.100");
    tv.updateFirmware("2.0");
    tv.streamContent("Netflix - Movie");
    
    cout << "\n=== Device Details ===" << endl;
    tv.display();
    
    return 0;
}
```

#### Type 2: Multiple Files

**device.h**
```cpp
#ifndef DEVICE_H
#define DEVICE_H

#include <string>
using namespace std;

class Device {
protected:
    string deviceId;
    bool poweredOn;
    static int nextId;
    
public:
    Device();
    void powerOn();
    void powerOff();
    virtual void display() const;
    virtual ~Device();
};

#endif
```

**device.cpp**
```cpp
#include "device.h"
#include <iostream>
using namespace std;

int Device::nextId = 1;

Device::Device() : poweredOn(false) {
    deviceId = "DEV" + to_string(nextId++);
    cout << "Device created: " << deviceId << endl;
}

void Device::powerOn() {
    poweredOn = true;
    cout << deviceId << " powered on" << endl;
}

void Device::powerOff() {
    poweredOn = false;
    cout << deviceId << " powered off" << endl;
}

void Device::display() const {
    cout << "Device: " << deviceId << ", Status: " << (poweredOn ? "ON" : "OFF") << endl;
}

Device::~Device() {
    cout << "Device destroyed: " << deviceId << endl;
}
```

**connectable.h**
```cpp
#ifndef CONNECTABLE_H
#define CONNECTABLE_H

#include "device.h"
#include <string>
using namespace std;

class Connectable : virtual public Device {
protected:
    string ipAddress;
    bool connected;
    
public:
    Connectable();
    void connect(const string& ip);
    void disconnect();
    void display() const override;
    ~Connectable();
};

#endif
```

**connectable.cpp**
```cpp
#include "connectable.h"
#include <iostream>
using namespace std;

Connectable::Connectable() : ipAddress("0.0.0.0"), connected(false) {
    cout << "Connectable created" << endl;
}

void Connectable::connect(const string& ip) {
    ipAddress = ip;
    connected = true;
    cout << deviceId << " connected to " << ipAddress << endl;
}

void Connectable::disconnect() {
    connected = false;
    cout << deviceId << " disconnected" << endl;
}

void Connectable::display() const {
    Device::display();
    cout << "Network: " << (connected ? "Connected" : "Disconnected") 
         << " (" << ipAddress << ")" << endl;
}

Connectable::~Connectable() {
    cout << "Connectable destroyed" << endl;
}
```

**programmable.h**
```cpp
#ifndef PROGRAMMABLE_H
#define PROGRAMMABLE_H

#include "device.h"
#include <string>
using namespace std;

class Programmable : virtual public Device {
protected:
    string firmware;
    int version;
    
public:
    Programmable();
    void updateFirmware(const string& newFirmware);
    void display() const override;
    ~Programmable();
};

#endif
```

**programmable.cpp**
```cpp
#include "programmable.h"
#include <iostream>
using namespace std;

Programmable::Programmable() : firmware("1.0"), version(1) {
    cout << "Programmable created" << endl;
}

void Programmable::updateFirmware(const string& newFirmware) {
    firmware = newFirmware;
    version++;
    cout << deviceId << " firmware updated to v" << version << " (" << firmware << ")" << endl;
}

void Programmable::display() const {
    Device::display();
    cout << "Firmware: v" << version << " (" << firmware << ")" << endl;
}

Programmable::~Programmable() {
    cout << "Programmable destroyed" << endl;
}
```

**smarttv.h**
```cpp
#ifndef SMARTTV_H
#define SMARTTV_H

#include "connectable.h"
#include "programmable.h"
#include <string>
using namespace std;

class SmartTV : public Connectable, public Programmable {
private:
    string resolution;
    int screenSize;
    
public:
    SmartTV(string res, int size);
    void display() const override;
    void streamContent(const string& content);
    ~SmartTV();
};

#endif
```

**smarttv.cpp**
```cpp
#include "smarttv.h"
#include <iostream>
using namespace std;

SmartTV::SmartTV(string res, int size) : resolution(res), screenSize(size) {
    cout << "SmartTV created: " << screenSize << "\" " << resolution << endl;
}

void SmartTV::display() const {
    Device::display();
    cout << "Screen: " << screenSize << "\" " << resolution << endl;
    cout << "Network: " << (connected ? "Connected" : "Disconnected") 
         << " (" << ipAddress << ")" << endl;
    cout << "Firmware: v" << version << " (" << firmware << ")" << endl;
}

void SmartTV::streamContent(const string& content) {
    if (poweredOn && connected) {
        cout << deviceId << " streaming: " << content << endl;
    } else {
        cout << deviceId << " cannot stream - check power and network" << endl;
    }
}

SmartTV::~SmartTV() {
    cout << "SmartTV destroyed" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "smarttv.h"
using namespace std;

int main() {
    SmartTV tv("4K", 65);
    tv.powerOn();
    tv.connect("192.168.1.100");
    tv.updateFirmware("2.0");
    tv.streamContent("Netflix");
    tv.display();
    return 0;
}
```

### Example 2: Vehicle Hierarchy with Virtual Inheritance

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
        cout << make << " " << model << " starting" << endl;
    }
    
    virtual void display() const {
        cout << year << " " << make << " " << model << endl;
    }
    
    virtual ~Vehicle() {
        cout << "Vehicle destroyed: " << make << " " << model << endl;
    }
};

class LandVehicle : virtual public Vehicle {
protected:
    int wheels;
    string fuelType;
    
public:
    LandVehicle(string mk, string md, int y, int w, string fuel) 
        : Vehicle(mk, md, y), wheels(w), fuelType(fuel) {
        cout << "LandVehicle created: " << wheels << " wheels, " << fuel << endl;
    }
    
    void drive() {
        cout << make << " " << model << " driving on road" << endl;
    }
    
    void display() const override {
        Vehicle::display();
        cout << "Wheels: " << wheels << ", Fuel: " << fuelType << endl;
    }
    
    ~LandVehicle() {
        cout << "LandVehicle destroyed" << endl;
    }
};

class WaterVehicle : virtual public Vehicle {
protected:
    double displacement;
    string hullType;
    
public:
    WaterVehicle(string mk, string md, int y, double disp, string hull) 
        : Vehicle(mk, md, y), displacement(disp), hullType(hull) {
        cout << "WaterVehicle created: " << disp << " tons, " << hull << " hull" << endl;
    }
    
    void sail() {
        cout << make << " " << model << " sailing on water" << endl;
    }
    
    void display() const override {
        Vehicle::display();
        cout << "Displacement: " << displacement << " tons, Hull: " << hullType << endl;
    }
    
    ~WaterVehicle() {
        cout << "WaterVehicle destroyed" << endl;
    }
};

class AmphibiousVehicle : public LandVehicle, public WaterVehicle {
private:
    string terrainMode;
    
public:
    AmphibiousVehicle(string mk, string md, int y, int w, string fuel, 
                      double disp, string hull, string mode)
        : Vehicle(mk, md, y), LandVehicle(mk, md, y, w, fuel), 
          WaterVehicle(mk, md, y, disp, hull), terrainMode(mode) {
        cout << "AmphibiousVehicle created: " << mode << " mode" << endl;
    }
    
    void switchMode(const string& mode) {
        terrainMode = mode;
        cout << make << " " << model << " switched to " << mode << " mode" << endl;
    }
    
    void display() const override {
        Vehicle::display();
        cout << "Wheels: " << wheels << ", Fuel: " << fuelType << endl;
        cout << "Displacement: " << displacement << " tons, Hull: " << hullType << endl;
        cout << "Current Mode: " << terrainMode << endl;
    }
    
    ~AmphibiousVehicle() {
        cout << "AmphibiousVehicle destroyed" << endl;
    }
};

int main() {
    AmphibiousVehicle av("Gibbs", "Humdinga", 2023, 4, "Gasoline", 
                         2.5, "Planing", "Land");
    
    av.start();
    av.drive();
    av.switchMode("Water");
    av.sail();
    
    cout << "\n=== Vehicle Details ===" << endl;
    av.display();
    
    return 0;
}
```

## Virtual Inheritance Rules

```cpp
#include <iostream>
using namespace std;

class VirtualBase {
public:
    VirtualBase() { cout << "VirtualBase constructor" << endl; }
    VirtualBase(int x) { cout << "VirtualBase constructor with " << x << endl; }
    ~VirtualBase() { cout << "VirtualBase destructor" << endl; }
};

class Derived1 : virtual public VirtualBase {
public:
    Derived1() : VirtualBase() { cout << "Derived1 constructor" << endl; }
    Derived1(int x) : VirtualBase(x) { cout << "Derived1 constructor with " << x << endl; }
    ~Derived1() { cout << "Derived1 destructor" << endl; }
};

class Derived2 : virtual public VirtualBase {
public:
    Derived2() : VirtualBase() { cout << "Derived2 constructor" << endl; }
    Derived2(int x) : VirtualBase(x) { cout << "Derived2 constructor with " << x << endl; }
    ~Derived2() { cout << "Derived2 destructor" << endl; }
};

class MostDerived : public Derived1, public Derived2 {
public:
    // Must initialize virtual base directly
    MostDerived() : VirtualBase(42), Derived1(), Derived2() {
        cout << "MostDerived constructor" << endl;
    }
    
    ~MostDerived() { cout << "MostDerived destructor" << endl; }
};

int main() {
    MostDerived md;
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting virtual keyword | Multiple base copies | Add virtual to intermediate classes |
| Not initializing virtual base | Compilation error | Initialize virtual base in most derived class |
| Confusing constructor order | Wrong initialization | Virtual bases initialized first |
| Using virtual unnecessarily | Performance overhead | Only when diamond problem exists |
| Casting issues | Downcasting problems | Use dynamic_cast for polymorphic types |

## Summary

- **Virtual inheritance** solves the diamond problem
- Ensures **single copy** of base class in hierarchy
- **Constructor order**: Virtual bases first, then non-virtual in declaration order
- **Destructor order**: Reverse of constructor order
- Most derived class is responsible for **initializing virtual base**
- Use when you have **multiple inheritance paths** to same base
- Adds **slight overhead** (vptr for virtual base)
- Essential for complex class hierarchies

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class VirtualBase {
protected:
    int value;
    
public:
    VirtualBase(int v) : value(v) {
        cout << "VirtualBase constructor: " << value << endl;
    }
    
    virtual ~VirtualBase() {
        cout << "VirtualBase destructor" << endl;
    }
};

class Intermediate1 : virtual public VirtualBase {
public:
    Intermediate1(int v) : VirtualBase(v) {
        cout << "Intermediate1 constructor" << endl;
    }
    
    ~Intermediate1() {
        cout << "Intermediate1 destructor" << endl;
    }
};

class Intermediate2 : virtual public VirtualBase {
public:
    Intermediate2(int v) : VirtualBase(v) {
        cout << "Intermediate2 constructor" << endl;
    }
    
    ~Intermediate2() {
        cout << "Intermediate2 destructor" << endl;
    }
};

class MostDerived : public Intermediate1, public Intermediate2 {
public:
    MostDerived(int v) : VirtualBase(v), Intermediate1(v), Intermediate2(v) {
        cout << "MostDerived constructor" << endl;
    }
    
    void show() {
        cout << "Value: " << value << endl;
    }
    
    ~MostDerived() {
        cout << "MostDerived destructor" << endl;
    }
};

int main() {
    MostDerived md(42);
    md.show();
    return 0;
}
```

### Type 2: Multiple Files

**virtualbase.h**
```cpp
#ifndef VIRTUALBASE_H
#define VIRTUALBASE_H

class VirtualBase {
protected:
    int value;
    
public:
    VirtualBase(int v);
    virtual ~VirtualBase();
};

#endif
```

**virtualbase.cpp**
```cpp
#include "virtualbase.h"
#include <iostream>
using namespace std;

VirtualBase::VirtualBase(int v) : value(v) {
    cout << "VirtualBase constructor: " << value << endl;
}

VirtualBase::~VirtualBase() {
    cout << "VirtualBase destructor" << endl;
}
```

**intermediate1.h**
```cpp
#ifndef INTERMEDIATE1_H
#define INTERMEDIATE1_H

#include "virtualbase.h"

class Intermediate1 : virtual public VirtualBase {
public:
    Intermediate1(int v);
    ~Intermediate1();
};

#endif
```

**intermediate1.cpp**
```cpp
#include "intermediate1.h"
#include <iostream>
using namespace std;

Intermediate1::Intermediate1(int v) : VirtualBase(v) {
    cout << "Intermediate1 constructor" << endl;
}

Intermediate1::~Intermediate1() {
    cout << "Intermediate1 destructor" << endl;
}
```

**intermediate2.h**
```cpp
#ifndef INTERMEDIATE2_H
#define INTERMEDIATE2_H

#include "virtualbase.h"

class Intermediate2 : virtual public VirtualBase {
public:
    Intermediate2(int v);
    ~Intermediate2();
};

#endif
```

**intermediate2.cpp**
```cpp
#include "intermediate2.h"
#include <iostream>
using namespace std;

Intermediate2::Intermediate2(int v) : VirtualBase(v) {
    cout << "Intermediate2 constructor" << endl;
}

Intermediate2::~Intermediate2() {
    cout << "Intermediate2 destructor" << endl;
}
```

**mostderived.h**
```cpp
#ifndef MOSTDERIVED_H
#define MOSTDERIVED_H

#include "intermediate1.h"
#include "intermediate2.h"

class MostDerived : public Intermediate1, public Intermediate2 {
public:
    MostDerived(int v);
    void show();
    ~MostDerived();
};

#endif
```

**mostderived.cpp**
```cpp
#include "mostderived.h"
#include <iostream>
using namespace std;

MostDerived::MostDerived(int v) : VirtualBase(v), Intermediate1(v), Intermediate2(v) {
    cout << "MostDerived constructor" << endl;
}

void MostDerived::show() {
    cout << "Value: " << value << endl;
}

MostDerived::~MostDerived() {
    cout << "MostDerived destructor" << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "mostderived.h"
using namespace std;

int main() {
    MostDerived md(42);
    md.show();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*