# 96 - Multilevel Inheritance in C++

## What is Multilevel Inheritance?
Multilevel inheritance is a type of inheritance where a class is derived from another derived class, forming a chain of inheritance. It represents a hierarchical relationship where each level adds more specific functionality.

## Type 1: Single File Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class - Level 1
class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a) : name(n), age(a) {
        cout << "Animal constructor called" << endl;
    }
    
    void eat() {
        cout << name << " is eating" << endl;
    }
    
    void sleep() {
        cout << name << " is sleeping" << endl;
    }
    
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    virtual ~Animal() {
        cout << "Animal destructor called" << endl;
    }
};

// Derived class - Level 2
class Mammal : public Animal {
protected:
    string furColor;
    
public:
    Mammal(string n, int a, string fur) : Animal(n, a), furColor(fur) {
        cout << "Mammal constructor called" << endl;
    }
    
    void feedMilk() {
        cout << name << " is feeding milk to young" << endl;
    }
    
    void display() const {
        Animal::display();
        cout << "Fur Color: " << furColor << endl;
    }
    
    ~Mammal() {
        cout << "Mammal destructor called" << endl;
    }
};

// Derived class - Level 3
class Dog : public Mammal {
private:
    string breed;
    
public:
    Dog(string n, int a, string fur, string b) : Mammal(n, a, fur), breed(b) {
        cout << "Dog constructor called" << endl;
    }
    
    void bark() {
        cout << name << " says: Woof! Woof!" << endl;
    }
    
    void fetch() {
        cout << name << " is fetching the ball" << endl;
    }
    
    void display() const {
        Mammal::display();
        cout << "Breed: " << breed << endl;
    }
    
    ~Dog() {
        cout << "Dog destructor called" << endl;
    }
};

int main() {
    Dog dog("Buddy", 3, "Golden", "Golden Retriever");
    
    cout << "\n--- Dog Details ---" << endl;
    dog.display();
    
    cout << "\n--- Dog Actions ---" << endl;
    dog.eat();      // From Animal
    dog.sleep();    // From Animal
    dog.feedMilk(); // From Mammal
    dog.bark();     // Dog's own
    dog.fetch();    // Dog's own
    
    return 0;
}
```

## Type 2: Multiple Files Implementation

### animal.h
```cpp
#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(string n, int a);
    void eat();
    void sleep();
    void display() const;
    virtual ~Animal();
};

#endif
```

### animal.cpp
```cpp
#include "animal.h"
#include <iostream>
using namespace std;

Animal::Animal(string n, int a) : name(n), age(a) {
    cout << "Animal constructor called" << endl;
}

void Animal::eat() {
    cout << name << " is eating" << endl;
}

void Animal::sleep() {
    cout << name << " is sleeping" << endl;
}

void Animal::display() const {
    cout << "Name: " << name << ", Age: " << age << endl;
}

Animal::~Animal() {
    cout << "Animal destructor called" << endl;
}
```

### mammal.h
```cpp
#ifndef MAMMAL_H
#define MAMMAL_H

#include "animal.h"
#include <string>
using namespace std;

class Mammal : public Animal {
protected:
    string furColor;
    
public:
    Mammal(string n, int a, string fur);
    void feedMilk();
    void display() const;
    ~Mammal();
};

#endif
```

### mammal.cpp
```cpp
#include "mammal.h"
#include <iostream>
using namespace std;

Mammal::Mammal(string n, int a, string fur) : Animal(n, a), furColor(fur) {
    cout << "Mammal constructor called" << endl;
}

void Mammal::feedMilk() {
    cout << name << " is feeding milk to young" << endl;
}

void Mammal::display() const {
    Animal::display();
    cout << "Fur Color: " << furColor << endl;
}

Mammal::~Mammal() {
    cout << "Mammal destructor called" << endl;
}
```

### dog.h
```cpp
#ifndef DOG_H
#define DOG_H

#include "mammal.h"
#include <string>
using namespace std;

class Dog : public Mammal {
private:
    string breed;
    
public:
    Dog(string n, int a, string fur, string b);
    void bark();
    void fetch();
    void display() const;
    ~Dog();
};

#endif
```

### dog.cpp
```cpp
#include "dog.h"
#include <iostream>
using namespace std;

Dog::Dog(string n, int a, string fur, string b) : Mammal(n, a, fur), breed(b) {
    cout << "Dog constructor called" << endl;
}

void Dog::bark() {
    cout << name << " says: Woof! Woof!" << endl;
}

void Dog::fetch() {
    cout << name << " is fetching the ball" << endl;
}

void Dog::display() const {
    Mammal::display();
    cout << "Breed: " << breed << endl;
}

Dog::~Dog() {
    cout << "Dog destructor called" << endl;
}
```

### main.cpp
```cpp
#include <iostream>
#include "dog.h"
using namespace std;

int main() {
    Dog dog("Buddy", 3, "Golden", "Golden Retriever");
    
    dog.display();
    dog.eat();
    dog.feedMilk();
    dog.bark();
    
    return 0;
}
```

## Constructor and Destructor Order

```cpp
#include <iostream>
#include <string>
using namespace std;

class GrandParent {
public:
    GrandParent() { cout << "GrandParent constructor" << endl; }
    ~GrandParent() { cout << "GrandParent destructor" << endl; }
};

class Parent : public GrandParent {
public:
    Parent() { cout << "Parent constructor" << endl; }
    ~Parent() { cout << "Parent destructor" << endl; }
};

class Child : public Parent {
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
Output:
```
Creating Child object:
GrandParent constructor
Parent constructor
Child constructor

Destroying Child object:
Child destructor
Parent destructor
GrandParent destructor
```

## Member Access in Multilevel Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

class Base {
protected:
    int protectedValue = 10;
    
public:
    int publicValue = 20;
    
    void showBase() {
        cout << "Base: protected=" << protectedValue 
             << ", public=" << publicValue << endl;
    }
};

class Derived : public Base {
protected:
    int derivedValue = 30;
    
public:
    void showDerived() {
        cout << "Derived: protected=" << protectedValue 
             << ", public=" << publicValue 
             << ", derived=" << derivedValue << endl;
    }
};

class MostDerived : public Derived {
public:
    void showMostDerived() {
        cout << "MostDerived: protected=" << protectedValue 
             << ", public=" << publicValue 
             << ", derived=" << derivedValue << endl;
    }
};

int main() {
    MostDerived obj;
    
    obj.showBase();
    obj.showDerived();
    obj.showMostDerived();
    
    // obj.protectedValue;  // Error! Protected member
    obj.publicValue = 100;  // OK
    
    return 0;
}
```

## Function Overriding in Multilevel Inheritance

```cpp
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    virtual void start() {
        cout << "Vehicle starting" << endl;
    }
    
    virtual void display() {
        cout << "This is a vehicle" << endl;
    }
    
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    void start() override {
        cout << "Car starting with key" << endl;
    }
    
    void display() override {
        cout << "This is a car" << endl;
    }
};

class SportsCar : public Car {
public:
    void start() override {
        cout << "SportsCar starting with push button" << endl;
    }
    
    void display() override {
        cout << "This is a sports car" << endl;
    }
    
    void turboBoost() {
        cout << "Turbo boost activated!" << endl;
    }
};

int main() {
    SportsCar sc;
    
    sc.start();      // Overridden in SportsCar
    sc.display();    // Overridden in SportsCar
    
    // Calling base class versions
    sc.Car::start();      // Call Car version
    sc.Vehicle::start();  // Call Vehicle version
    
    sc.turboBoost();      // SportsCar's own method
    
    return 0;
}
```

## Practical Examples

### Example 1: Employee Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Level 1: Person
class Person {
protected:
    string name;
    int age;
    string email;
    
public:
    Person(string n, int a, string e) : name(n), age(a), email(e) {
        cout << "Person created: " << name << endl;
    }
    
    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
        cout << "Email: " << email << endl;
    }
    
    virtual double calculateBonus() const {
        return 0;
    }
    
    virtual ~Person() {
        cout << "Person destroyed: " << name << endl;
    }
};

// Level 2: Employee
class Employee : public Person {
protected:
    int employeeId;
    double salary;
    string department;
    static int nextId;
    
public:
    Employee(string n, int a, string e, double s, string dept) 
        : Person(n, a, e), salary(s), department(dept) {
        employeeId = nextId++;
        cout << "Employee created: ID=" << employeeId << endl;
    }
    
    double getSalary() const { return salary; }
    int getId() const { return employeeId; }
    
    void display() const override {
        Person::display();
        cout << "Employee ID: " << employeeId << endl;
        cout << "Department: " << department << endl;
        cout << "Salary: $" << salary << endl;
    }
    
    double calculateBonus() const override {
        return salary * 0.1;
    }
    
    ~Employee() {
        cout << "Employee destroyed: " << name << endl;
    }
};

int Employee::nextId = 1000;

// Level 3: Manager
class Manager : public Employee {
private:
    int teamSize;
    vector<string> teamMembers;
    
public:
    Manager(string n, int a, string e, double s, string dept, int size) 
        : Employee(n, a, e, s, dept), teamSize(size) {
        cout << "Manager created: Team size=" << teamSize << endl;
    }
    
    void addTeamMember(string member) {
        teamMembers.push_back(member);
    }
    
    void display() const override {
        Employee::display();
        cout << "Team Size: " << teamSize << endl;
        cout << "Team Members: ";
        for (const auto& m : teamMembers) {
            cout << m << " ";
        }
        cout << endl;
    }
    
    double calculateBonus() const override {
        return Employee::calculateBonus() + (teamSize * 1000);
    }
    
    void conductMeeting() {
        cout << name << " is conducting team meeting" << endl;
    }
    
    ~Manager() {
        cout << "Manager destroyed: " << name << endl;
    }
};

// Level 4: SeniorManager
class SeniorManager : public Manager {
private:
    int managedDepartments;
    vector<string> departments;
    
public:
    SeniorManager(string n, int a, string e, double s, string dept, int size, int depts) 
        : Manager(n, a, e, s, dept, size), managedDepartments(depts) {
        cout << "SeniorManager created: Manages " << managedDepartments << " departments" << endl;
    }
    
    void addDepartment(string dept) {
        departments.push_back(dept);
    }
    
    void display() const override {
        Manager::display();
        cout << "Managed Departments: " << managedDepartments << endl;
        cout << "Departments: ";
        for (const auto& d : departments) {
            cout << d << " ";
        }
        cout << endl;
    }
    
    double calculateBonus() const override {
        return Manager::calculateBonus() + (managedDepartments * 2000);
    }
    
    void strategicPlanning() {
        cout << name << " is doing strategic planning" << endl;
    }
    
    ~SeniorManager() {
        cout << "SeniorManager destroyed: " << name << endl;
    }
};

int main() {
    SeniorManager sm("Alice Johnson", 45, "alice@company.com", 120000, "Executive", 8, 3);
    
    sm.addTeamMember("Bob");
    sm.addTeamMember("Carol");
    sm.addDepartment("Engineering");
    sm.addDepartment("Sales");
    sm.addDepartment("Marketing");
    
    cout << "\n=== Senior Manager Details ===" << endl;
    sm.display();
    
    cout << "\n=== Actions ===" << endl;
    sm.conductMeeting();
    sm.strategicPlanning();
    cout << "Bonus: $" << sm.calculateBonus() << endl;
    
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
    string email;
    
public:
    Person(string n, int a, string e);
    virtual void display() const;
    virtual double calculateBonus() const;
    virtual ~Person();
};

#endif
```

**person.cpp**
```cpp
#include "person.h"
#include <iostream>
using namespace std;

Person::Person(string n, int a, string e) : name(n), age(a), email(e) {
    cout << "Person created: " << name << endl;
}

void Person::display() const {
    cout << "Name: " << name << ", Age: " << age << endl;
    cout << "Email: " << email << endl;
}

double Person::calculateBonus() const {
    return 0;
}

Person::~Person() {
    cout << "Person destroyed: " << name << endl;
}
```

**employee.h**
```cpp
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "person.h"
#include <string>
using namespace std;

class Employee : public Person {
protected:
    int employeeId;
    double salary;
    string department;
    static int nextId;
    
public:
    Employee(string n, int a, string e, double s, string dept);
    double getSalary() const;
    int getId() const;
    void display() const override;
    double calculateBonus() const override;
    ~Employee();
};

#endif
```

**employee.cpp**
```cpp
#include "employee.h"
#include <iostream>
using namespace std;

int Employee::nextId = 1000;

Employee::Employee(string n, int a, string e, double s, string dept) 
    : Person(n, a, e), salary(s), department(dept) {
    employeeId = nextId++;
    cout << "Employee created: ID=" << employeeId << endl;
}

double Employee::getSalary() const { return salary; }
int Employee::getId() const { return employeeId; }

void Employee::display() const {
    Person::display();
    cout << "Employee ID: " << employeeId << endl;
    cout << "Department: " << department << endl;
    cout << "Salary: $" << salary << endl;
}

double Employee::calculateBonus() const {
    return salary * 0.1;
}

Employee::~Employee() {
    cout << "Employee destroyed: " << name << endl;
}
```

**manager.h**
```cpp
#ifndef MANAGER_H
#define MANAGER_H

#include "employee.h"
#include <vector>
#include <string>
using namespace std;

class Manager : public Employee {
protected:
    int teamSize;
    vector<string> teamMembers;
    
public:
    Manager(string n, int a, string e, double s, string dept, int size);
    void addTeamMember(string member);
    void display() const override;
    double calculateBonus() const override;
    void conductMeeting();
    ~Manager();
};

#endif
```

**manager.cpp**
```cpp
#include "manager.h"
#include <iostream>
using namespace std;

Manager::Manager(string n, int a, string e, double s, string dept, int size) 
    : Employee(n, a, e, s, dept), teamSize(size) {
    cout << "Manager created: Team size=" << teamSize << endl;
}

void Manager::addTeamMember(string member) {
    teamMembers.push_back(member);
}

void Manager::display() const {
    Employee::display();
    cout << "Team Size: " << teamSize << endl;
    cout << "Team Members: ";
    for (const auto& m : teamMembers) {
        cout << m << " ";
    }
    cout << endl;
}

double Manager::calculateBonus() const {
    return Employee::calculateBonus() + (teamSize * 1000);
}

void Manager::conductMeeting() {
    cout << name << " is conducting team meeting" << endl;
}

Manager::~Manager() {
    cout << "Manager destroyed: " << name << endl;
}
```

**seniormanager.h**
```cpp
#ifndef SENIORMANAGER_H
#define SENIORMANAGER_H

#include "manager.h"
#include <vector>
#include <string>
using namespace std;

class SeniorManager : public Manager {
private:
    int managedDepartments;
    vector<string> departments;
    
public:
    SeniorManager(string n, int a, string e, double s, string dept, int size, int depts);
    void addDepartment(string dept);
    void display() const override;
    double calculateBonus() const override;
    void strategicPlanning();
    ~SeniorManager();
};

#endif
```

**seniormanager.cpp**
```cpp
#include "seniormanager.h"
#include <iostream>
using namespace std;

SeniorManager::SeniorManager(string n, int a, string e, double s, string dept, int size, int depts) 
    : Manager(n, a, e, s, dept, size), managedDepartments(depts) {
    cout << "SeniorManager created: Manages " << managedDepartments << " departments" << endl;
}

void SeniorManager::addDepartment(string dept) {
    departments.push_back(dept);
}

void SeniorManager::display() const {
    Manager::display();
    cout << "Managed Departments: " << managedDepartments << endl;
    cout << "Departments: ";
    for (const auto& d : departments) {
        cout << d << " ";
    }
    cout << endl;
}

double SeniorManager::calculateBonus() const {
    return Manager::calculateBonus() + (managedDepartments * 2000);
}

void SeniorManager::strategicPlanning() {
    cout << name << " is doing strategic planning" << endl;
}

SeniorManager::~SeniorManager() {
    cout << "SeniorManager destroyed: " << name << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "seniormanager.h"
using namespace std;

int main() {
    SeniorManager sm("Alice", 45, "alice@company.com", 120000, "Executive", 8, 3);
    
    sm.addTeamMember("Bob");
    sm.addDepartment("Engineering");
    
    sm.display();
    sm.conductMeeting();
    sm.strategicPlanning();
    cout << "Bonus: $" << sm.calculateBonus() << endl;
    
    return 0;
}
```

### Example 2: Electronic Device Hierarchy

#### Type 1: Single File
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Level 1: Device
class Device {
protected:
    string brand;
    string model;
    bool poweredOn;
    
public:
    Device(string b, string m) : brand(b), model(m), poweredOn(false) {
        cout << "Device created: " << brand << " " << model << endl;
    }
    
    virtual void powerOn() {
        poweredOn = true;
        cout << brand << " " << model << " powered on" << endl;
    }
    
    virtual void powerOff() {
        poweredOn = false;
        cout << brand << " " << model << " powered off" << endl;
    }
    
    virtual void display() const {
        cout << "Device: " << brand << " " << model << endl;
        cout << "Status: " << (poweredOn ? "On" : "Off") << endl;
    }
    
    virtual ~Device() {
        cout << "Device destroyed: " << brand << " " << model << endl;
    }
};

// Level 2: Computer
class Computer : public Device {
protected:
    string operatingSystem;
    int ramGB;
    int storageGB;
    
public:
    Computer(string b, string m, string os, int ram, int storage) 
        : Device(b, m), operatingSystem(os), ramGB(ram), storageGB(storage) {
        cout << "Computer created: " << os << ", " << ram << "GB RAM" << endl;
    }
    
    void installSoftware(string software) {
        if (poweredOn) {
            cout << "Installing " << software << " on " << brand << " " << model << endl;
        } else {
            cout << "Cannot install - device off" << endl;
        }
    }
    
    void display() const override {
        Device::display();
        cout << "OS: " << operatingSystem << endl;
        cout << "RAM: " << ramGB << "GB, Storage: " << storageGB << "GB" << endl;
    }
    
    ~Computer() {
        cout << "Computer destroyed: " << brand << " " << model << endl;
    }
};

// Level 3: Laptop
class Laptop : public Computer {
private:
    double weightKg;
    int batteryLifeHours;
    bool hasTouchscreen;
    
public:
    Laptop(string b, string m, string os, int ram, int storage, double weight, int battery, bool touch) 
        : Computer(b, m, os, ram, storage), weightKg(weight), batteryLifeHours(battery), hasTouchscreen(touch) {
        cout << "Laptop created: " << weight << "kg, " << battery << "hrs battery" << endl;
    }
    
    void carry() {
        cout << "Carrying " << brand << " " << model << " (" << weightKg << "kg)" << endl;
    }
    
    void checkBattery() {
        cout << "Battery life: " << batteryLifeHours << " hours remaining" << endl;
    }
    
    void display() const override {
        Computer::display();
        cout << "Weight: " << weightKg << "kg" << endl;
        cout << "Battery: " << batteryLifeHours << " hours" << endl;
        cout << "Touchscreen: " << (hasTouchscreen ? "Yes" : "No") << endl;
    }
    
    ~Laptop() {
        cout << "Laptop destroyed: " << brand << " " << model << endl;
    }
};

// Level 4: GamingLaptop
class GamingLaptop : public Laptop {
private:
    string gpuModel;
    int refreshRateHz;
    vector<string> installedGames;
    
public:
    GamingLaptop(string b, string m, string os, int ram, int storage, double weight, 
                 int battery, bool touch, string gpu, int refresh) 
        : Laptop(b, m, os, ram, storage, weight, battery, touch), gpuModel(gpu), refreshRateHz(refresh) {
        cout << "GamingLaptop created: " << gpu << ", " << refresh << "Hz display" << endl;
    }
    
    void installGame(string game) {
        if (poweredOn) {
            installedGames.push_back(game);
            cout << "Installed game: " << game << endl;
        } else {
            cout << "Cannot install - laptop off" << endl;
        }
    }
    
    void playGame(string game) {
        cout << "Playing " << game << " on " << brand << " " << model << endl;
        cout << "GPU: " << gpuModel << ", Refresh Rate: " << refreshRateHz << "Hz" << endl;
    }
    
    void display() const override {
        Laptop::display();
        cout << "GPU: " << gpuModel << endl;
        cout << "Refresh Rate: " << refreshRateHz << "Hz" << endl;
        cout << "Installed Games: ";
        for (const auto& g : installedGames) {
            cout << g << " ";
        }
        cout << endl;
    }
    
    ~GamingLaptop() {
        cout << "GamingLaptop destroyed: " << brand << " " << model << endl;
    }
};

int main() {
    GamingLaptop gl("ASUS", "ROG Zephyrus", "Windows 11", 32, 1000, 1.9, 8, true, "RTX 4080", 240);
    
    gl.powerOn();
    gl.installGame("Cyberpunk 2077");
    gl.installGame("Starfield");
    gl.playGame("Cyberpunk 2077");
    gl.carry();
    gl.checkBattery();
    
    cout << "\n=== Gaming Laptop Details ===" << endl;
    gl.display();
    
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
    string brand;
    string model;
    bool poweredOn;
    
public:
    Device(string b, string m);
    virtual void powerOn();
    virtual void powerOff();
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

Device::Device(string b, string m) : brand(b), model(m), poweredOn(false) {
    cout << "Device created: " << brand << " " << model << endl;
}

void Device::powerOn() {
    poweredOn = true;
    cout << brand << " " << model << " powered on" << endl;
}

void Device::powerOff() {
    poweredOn = false;
    cout << brand << " " << model << " powered off" << endl;
}

void Device::display() const {
    cout << "Device: " << brand << " " << model << endl;
    cout << "Status: " << (poweredOn ? "On" : "Off") << endl;
}

Device::~Device() {
    cout << "Device destroyed: " << brand << " " << model << endl;
}
```

**computer.h**
```cpp
#ifndef COMPUTER_H
#define COMPUTER_H

#include "device.h"
#include <string>
using namespace std;

class Computer : public Device {
protected:
    string operatingSystem;
    int ramGB;
    int storageGB;
    
public:
    Computer(string b, string m, string os, int ram, int storage);
    void installSoftware(string software);
    void display() const override;
    ~Computer();
};

#endif
```

**computer.cpp**
```cpp
#include "computer.h"
#include <iostream>
using namespace std;

Computer::Computer(string b, string m, string os, int ram, int storage) 
    : Device(b, m), operatingSystem(os), ramGB(ram), storageGB(storage) {
    cout << "Computer created: " << os << ", " << ram << "GB RAM" << endl;
}

void Computer::installSoftware(string software) {
    if (poweredOn) {
        cout << "Installing " << software << " on " << brand << " " << model << endl;
    } else {
        cout << "Cannot install - device off" << endl;
    }
}

void Computer::display() const {
    Device::display();
    cout << "OS: " << operatingSystem << endl;
    cout << "RAM: " << ramGB << "GB, Storage: " << storageGB << "GB" << endl;
}

Computer::~Computer() {
    cout << "Computer destroyed: " << brand << " " << model << endl;
}
```

**laptop.h**
```cpp
#ifndef LAPTOP_H
#define LAPTOP_H

#include "computer.h"

class Laptop : public Computer {
protected:
    double weightKg;
    int batteryLifeHours;
    bool hasTouchscreen;
    
public:
    Laptop(string b, string m, string os, int ram, int storage, double weight, int battery, bool touch);
    void carry();
    void checkBattery();
    void display() const override;
    ~Laptop();
};

#endif
```

**laptop.cpp**
```cpp
#include "laptop.h"
#include <iostream>
using namespace std;

Laptop::Laptop(string b, string m, string os, int ram, int storage, double weight, int battery, bool touch) 
    : Computer(b, m, os, ram, storage), weightKg(weight), batteryLifeHours(battery), hasTouchscreen(touch) {
    cout << "Laptop created: " << weight << "kg, " << battery << "hrs battery" << endl;
}

void Laptop::carry() {
    cout << "Carrying " << brand << " " << model << " (" << weightKg << "kg)" << endl;
}

void Laptop::checkBattery() {
    cout << "Battery life: " << batteryLifeHours << " hours remaining" << endl;
}

void Laptop::display() const {
    Computer::display();
    cout << "Weight: " << weightKg << "kg" << endl;
    cout << "Battery: " << batteryLifeHours << " hours" << endl;
    cout << "Touchscreen: " << (hasTouchscreen ? "Yes" : "No") << endl;
}

Laptop::~Laptop() {
    cout << "Laptop destroyed: " << brand << " " << model << endl;
}
```

**gaminglaptop.h**
```cpp
#ifndef GAMINGLAPTOP_H
#define GAMINGLAPTOP_H

#include "laptop.h"
#include <vector>
#include <string>
using namespace std;

class GamingLaptop : public Laptop {
private:
    string gpuModel;
    int refreshRateHz;
    vector<string> installedGames;
    
public:
    GamingLaptop(string b, string m, string os, int ram, int storage, double weight, 
                 int battery, bool touch, string gpu, int refresh);
    void installGame(string game);
    void playGame(string game);
    void display() const override;
    ~GamingLaptop();
};

#endif
```

**gaminglaptop.cpp**
```cpp
#include "gaminglaptop.h"
#include <iostream>
using namespace std;

GamingLaptop::GamingLaptop(string b, string m, string os, int ram, int storage, double weight, 
                           int battery, bool touch, string gpu, int refresh) 
    : Laptop(b, m, os, ram, storage, weight, battery, touch), gpuModel(gpu), refreshRateHz(refresh) {
    cout << "GamingLaptop created: " << gpu << ", " << refresh << "Hz display" << endl;
}

void GamingLaptop::installGame(string game) {
    if (poweredOn) {
        installedGames.push_back(game);
        cout << "Installed game: " << game << endl;
    } else {
        cout << "Cannot install - laptop off" << endl;
    }
}

void GamingLaptop::playGame(string game) {
    cout << "Playing " << game << " on " << brand << " " << model << endl;
    cout << "GPU: " << gpuModel << ", Refresh Rate: " << refreshRateHz << "Hz" << endl;
}

void GamingLaptop::display() const {
    Laptop::display();
    cout << "GPU: " << gpuModel << endl;
    cout << "Refresh Rate: " << refreshRateHz << "Hz" << endl;
    cout << "Installed Games: ";
    for (const auto& g : installedGames) {
        cout << g << " ";
    }
    cout << endl;
}

GamingLaptop::~GamingLaptop() {
    cout << "GamingLaptop destroyed: " << brand << " " << model << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "gaminglaptop.h"
using namespace std;

int main() {
    GamingLaptop gl("ASUS", "ROG Zephyrus", "Windows 11", 32, 1000, 1.9, 8, true, "RTX 4080", 240);
    
    gl.powerOn();
    gl.installGame("Cyberpunk");
    gl.playGame("Cyberpunk");
    gl.display();
    
    return 0;
}
```

## Access Specifiers in Multilevel Inheritance

```cpp
#include <iostream>
using namespace std;

class Base {
private:
    int privateVar = 1;
protected:
    int protectedVar = 2;
public:
    int publicVar = 3;
};

class Derived : public Base {
public:
    void showDerived() {
        // cout << privateVar;  // Error! Private not accessible
        cout << "Protected: " << protectedVar << endl;
        cout << "Public: " << publicVar << endl;
    }
};

class MostDerived : public Derived {
public:
    void showMostDerived() {
        // cout << privateVar;  // Error! Private not accessible
        cout << "Protected: " << protectedVar << endl;
        cout << "Public: " << publicVar << endl;
    }
};

int main() {
    MostDerived md;
    md.showMostDerived();
    // md.protectedVar;  // Error! Protected not accessible outside class
    md.publicVar = 10;   // OK
    
    return 0;
}
```

## Common Mistakes

| Mistake | Problem | Solution |
|---------|---------|----------|
| Forgetting virtual destructor | Memory leak | Make base destructor virtual |
| Incorrect constructor initialization | Base parts not initialized | Call base constructors in initialization list |
| Function hiding | Unexpected behavior | Use `using` or override |
| Deep inheritance chains | Complexity | Limit inheritance depth |
| Slicing | Loss of derived data | Use pointers/references |

## Summary

- **Multilevel inheritance** forms a chain of inheritance
- **Constructor order**: GrandParent → Parent → Child
- **Destructor order**: Child → Parent → GrandParent
- **Accessibility**: Protected members accessible throughout hierarchy
- **Function overriding** can occur at any level
- **Virtual functions** maintain polymorphic behavior
- **Virtual destructor** ensures proper cleanup

## Basic Template

### Type 1: Single File
```cpp
#include <iostream>
using namespace std;

class GrandParent {
protected:
    int value;
    
public:
    GrandParent(int v) : value(v) {
        cout << "GrandParent constructor" << endl;
    }
    
    virtual void show() {
        cout << "GrandParent: " << value << endl;
    }
    
    virtual ~GrandParent() {}
};

class Parent : public GrandParent {
protected:
    int extra;
    
public:
    Parent(int v, int e) : GrandParent(v), extra(e) {
        cout << "Parent constructor" << endl;
    }
    
    void show() override {
        GrandParent::show();
        cout << "Parent extra: " << extra << endl;
    }
};

class Child : public Parent {
private:
    int more;
    
public:
    Child(int v, int e, int m) : Parent(v, e), more(m) {
        cout << "Child constructor" << endl;
    }
    
    void show() override {
        Parent::show();
        cout << "Child more: " << more << endl;
    }
};

int main() {
    Child c(10, 20, 30);
    c.show();
    return 0;
}
```

### Type 2: Multiple Files

**grandparent.h**
```cpp
#ifndef GRANDPARENT_H
#define GRANDPARENT_H

class GrandParent {
protected:
    int value;
    
public:
    GrandParent(int v);
    virtual void show();
    virtual ~GrandParent();
};

#endif
```

**grandparent.cpp**
```cpp
#include "grandparent.h"
#include <iostream>
using namespace std;

GrandParent::GrandParent(int v) : value(v) {
    cout << "GrandParent constructor" << endl;
}

void GrandParent::show() {
    cout << "GrandParent: " << value << endl;
}

GrandParent::~GrandParent() {}
```

**parent.h**
```cpp
#ifndef PARENT_H
#define PARENT_H

#include "grandparent.h"

class Parent : public GrandParent {
protected:
    int extra;
    
public:
    Parent(int v, int e);
    void show() override;
};

#endif
```

**parent.cpp**
```cpp
#include "parent.h"
#include <iostream>
using namespace std;

Parent::Parent(int v, int e) : GrandParent(v), extra(e) {
    cout << "Parent constructor" << endl;
}

void Parent::show() {
    GrandParent::show();
    cout << "Parent extra: " << extra << endl;
}
```

**child.h**
```cpp
#ifndef CHILD_H
#define CHILD_H

#include "parent.h"

class Child : public Parent {
private:
    int more;
    
public:
    Child(int v, int e, int m);
    void show() override;
};

#endif
```

**child.cpp**
```cpp
#include "child.h"
#include <iostream>
using namespace std;

Child::Child(int v, int e, int m) : Parent(v, e), more(m) {
    cout << "Child constructor" << endl;
}

void Child::show() {
    Parent::show();
    cout << "Child more: " << more << endl;
}
```

**main.cpp**
```cpp
#include <iostream>
#include "child.h"
using namespace std;

int main() {
    Child c(10, 20, 30);
    c.show();
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*