# 46 - Function Declaration and Prototype in C++

## What is a Function?
A function is a reusable block of code that performs a specific task. It helps organize code, avoid repetition, and make programs easier to understand and maintain.

## Basic Function Structure

```cpp
return_type function_name(parameter_list) {
    // function body
    // code to execute
    return value;  // if return_type is not void
}
```

## Function Declaration (Prototype)

A function declaration tells the compiler about the function's name, return type, and parameters before it's actually defined.

```cpp
#include <iostream>
using namespace std;

// Function declarations (prototypes)
void sayHello();
int add(int a, int b);
double multiply(double x, double y);
void printName(string name);

int main() {
    // Function calls
    sayHello();
    
    int sum = add(5, 3);
    cout << "Sum: " << sum << endl;
    
    double product = multiply(2.5, 4.0);
    cout << "Product: " << product << endl;
    
    printName("John");
    
    return 0;
}

// Function definitions
void sayHello() {
    cout << "Hello!" << endl;
}

int add(int a, int b) {
    return a + b;
}

double multiply(double x, double y) {
    return x * y;
}

void printName(string name) {
    cout << "Name: " << name << endl;
}
```

## Why Use Function Prototypes?

### Without Prototype (Error)
```cpp
#include <iostream>
using namespace std;

int main() {
    // Error: function not declared yet
    int result = add(5, 3);  // Compiler doesn't know about add()
    cout << result << endl;
    return 0;
}

int add(int a, int b) {
    return a + b;
}
```

### With Prototype (Works)
```cpp
#include <iostream>
using namespace std;

// Prototype - tells compiler about add()
int add(int a, int b);

int main() {
    int result = add(5, 3);  // Now compiler knows
    cout << result << endl;
    return 0;
}

int add(int a, int b) {
    return a + b;
}
```

## Different Ways to Write Prototypes

### Parameter Names Optional
```cpp
// With parameter names (more readable)
int add(int a, int b);
double multiply(double x, double y);

// Without parameter names (just types)
int add(int, int);
double multiply(double, double);
void printMessage(string);
```

### Multiple Parameters
```cpp
// Various parameter combinations
int calculate(int a, int b, int c);
double average(double scores[], int size);
void process(int id, string name, double value);
char getGrade(int score, bool extraCredit);
```

## Return Types

### void Functions (No Return Value)
```cpp
#include <iostream>
using namespace std;

// Prototypes
void greet(string name);
void displayMenu();
void printLine();

int main() {
    greet("Alice");
    displayMenu();
    printLine();
    
    return 0;
}

void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
    // No return statement needed
}

void displayMenu() {
    cout << "1. Start" << endl;
    cout << "2. Load" << endl;
    cout << "3. Exit" << endl;
}

void printLine() {
    cout << "--------------------" << endl;
}
```

### Functions with Return Values
```cpp
#include <iostream>
using namespace std;

// Prototypes
int getNumber();
double calculateArea(double radius);
bool isEven(int num);
string getGreeting(string name);

int main() {
    int num = getNumber();
    cout << "Number: " << num << endl;
    
    double area = calculateArea(5.0);
    cout << "Area: " << area << endl;
    
    cout << "5 is even? " << isEven(5) << endl;
    cout << getGreeting("John") << endl;
    
    return 0;
}

int getNumber() {
    return 42;  // Returns integer
}

double calculateArea(double radius) {
    return 3.14159 * radius * radius;  // Returns double
}

bool isEven(int num) {
    return num % 2 == 0;  // Returns boolean
}

string getGreeting(string name) {
    return "Hello, " + name + "!";  // Returns string
}
```

## Parameter Types

### Pass by Value
```cpp
#include <iostream>
using namespace std;

// Prototype
void increment(int x);

int main() {
    int num = 5;
    cout << "Before: " << num << endl;
    increment(num);
    cout << "After: " << num << endl;  // Still 5! (value not changed)
    
    return 0;
}

void increment(int x) {
    x++;  // Only modifies local copy
}
```

### Pass by Reference
```cpp
#include <iostream>
using namespace std;

// Prototype with reference parameter
void increment(int &x);
void swap(int &a, int &b);

int main() {
    int num = 5;
    cout << "Before: " << num << endl;
    increment(num);
    cout << "After: " << num << endl;  // Now 6! (original changed)
    
    int a = 10, b = 20;
    cout << "Before swap: a=" << a << ", b=" << b << endl;
    swap(a, b);
    cout << "After swap: a=" << a << ", b=" << b << endl;
    
    return 0;
}

void increment(int &x) {
    x++;  // Modifies original variable
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
```

### Pass by const Reference
```cpp
#include <iostream>
#include <string>
using namespace std;

// Prototype with const reference (for large objects)
void printMessage(const string &msg);
double calculateTotal(const double &price, int quantity);

int main() {
    string message = "Hello World";
    printMessage(message);  // No copy, but can't modify
    
    double total = calculateTotal(19.99, 3);
    cout << "Total: $" << total << endl;
    
    return 0;
}

void printMessage(const string &msg) {
    cout << msg << endl;
    // msg += "!";  // Error! Can't modify const reference
}

double calculateTotal(const double &price, int quantity) {
    return price * quantity;  // Can read, can't modify price
}
```

## Default Arguments

```cpp
#include <iostream>
#include <string>
using namespace std;

// Prototypes with default arguments
void greet(string name, string greeting = "Hello");
int multiply(int a, int b = 1);
void display(string item, int count = 1, bool showPrice = false);

int main() {
    greet("John");                 // Uses default greeting
    greet("Jane", "Hi");           // Uses provided greeting
    
    cout << multiply(5) << endl;        // 5 * 1 = 5
    cout << multiply(5, 3) << endl;     // 5 * 3 = 15
    
    display("apple");                   // 1 apple
    display("banana", 3);               // 3 bananas
    display("orange", 2, true);         // 2 oranges with price
    
    return 0;
}

void greet(string name, string greeting) {
    cout << greeting << ", " << name << "!" << endl;
}

int multiply(int a, int b) {
    return a * b;
}

void display(string item, int count, bool showPrice) {
    cout << count << " " << item;
    if (count > 1) cout << "s";
    if (showPrice) cout << " - $1.99 each";
    cout << endl;
}
```

## Function Overloading (Same Name, Different Parameters)

```cpp
#include <iostream>
using namespace std;

// Function prototypes - same name, different parameters
int add(int a, int b);
double add(double a, double b);
int add(int a, int b, int c);

int main() {
    cout << "add(5, 3): " << add(5, 3) << endl;           // Calls int version
    cout << "add(2.5, 3.7): " << add(2.5, 3.7) << endl;   // Calls double version
    cout << "add(1, 2, 3): " << add(1, 2, 3) << endl;     // Calls 3-param version
    
    return 0;
}

int add(int a, int b) {
    cout << "int version: ";
    return a + b;
}

double add(double a, double b) {
    cout << "double version: ";
    return a + b;
}

int add(int a, int b, int c) {
    cout << "three int version: ";
    return a + b + c;
}
```

## Practical Examples

### Example 1: Math Utility Functions
```cpp
#include <iostream>
#include <cmath>
using namespace std;

// Function prototypes
double circleArea(double radius);
double rectangleArea(double length, double width);
double triangleArea(double base, double height);
double celsiusToFahrenheit(double celsius);
double fahrenheitToCelsius(double fahrenheit);

int main() {
    cout << "Circle area (r=5): " << circleArea(5) << endl;
    cout << "Rectangle area (4x6): " << rectangleArea(4, 6) << endl;
    cout << "Triangle area (base=3, height=4): " << triangleArea(3, 4) << endl;
    cout << "25°C to Fahrenheit: " << celsiusToFahrenheit(25) << endl;
    cout << "77°F to Celsius: " << fahrenheitToCelsius(77) << endl;
    
    return 0;
}

double circleArea(double radius) {
    return 3.14159 * radius * radius;
}

double rectangleArea(double length, double width) {
    return length * width;
}

double triangleArea(double base, double height) {
    return 0.5 * base * height;
}

double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0/5.0) + 32;
}

double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32) * 5.0/9.0;
}
```

### Example 2: Array Processing Functions
```cpp
#include <iostream>
using namespace std;

// Function prototypes
void printArray(int arr[], int size);
int sumArray(int arr[], int size);
double averageArray(int arr[], int size);
int findMax(int arr[], int size);
int findMin(int arr[], int size);
void reverseArray(int arr[], int size);

int main() {
    int numbers[] = {5, 3, 8, 1, 9, 2, 7};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printArray(numbers, size);
    cout << "Sum: " << sumArray(numbers, size) << endl;
    cout << "Average: " << averageArray(numbers, size) << endl;
    cout << "Max: " << findMax(numbers, size) << endl;
    cout << "Min: " << findMin(numbers, size) << endl;
    
    reverseArray(numbers, size);
    cout << "Reversed: ";
    printArray(numbers, size);
    
    return 0;
}

void printArray(int arr[], int size) {
    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

double averageArray(int arr[], int size) {
    if (size == 0) return 0;
    return static_cast<double>(sumArray(arr, size)) / size;
}

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

int findMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}
```

### Example 3: String Validation Functions
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function prototypes
bool isValidUsername(string username);
bool isValidPassword(string password);
bool isValidEmail(string email);
string toUpperCase(string text);
string toLowerCase(string text);

int main() {
    cout << boolalpha;
    
    cout << "Username 'john123': " << isValidUsername("john123") << endl;
    cout << "Username 'jo': " << isValidUsername("jo") << endl;
    
    cout << "Password 'pass123': " << isValidPassword("pass123") << endl;
    cout << "Password 'Pass123!': " << isValidPassword("Pass123!") << endl;
    
    cout << "Email 'test@test.com': " << isValidEmail("test@test.com") << endl;
    cout << "Email 'invalid': " << isValidEmail("invalid") << endl;
    
    cout << "Uppercase: " << toUpperCase("Hello World") << endl;
    cout << "Lowercase: " << toLowerCase("Hello World") << endl;
    
    return 0;
}

bool isValidUsername(string username) {
    if (username.length() < 3 || username.length() > 20) return false;
    
    for (char c : username) {
        if (!isalnum(c)) return false;
    }
    return true;
}

bool isValidPassword(string password) {
    if (password.length() < 6) return false;
    
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        else if (islower(c)) hasLower = true;
        else if (isdigit(c)) hasDigit = true;
    }
    
    return hasUpper && hasLower && hasDigit;
}

bool isValidEmail(string email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    
    return atPos != string::npos && 
           dotPos != string::npos && 
           atPos > 0 && 
           dotPos > atPos + 1 && 
           dotPos < email.length() - 1;
}

string toUpperCase(string text) {
    string result = text;
    for (char &c : result) {
        c = toupper(c);
    }
    return result;
}

string toLowerCase(string text) {
    string result = text;
    for (char &c : result) {
        c = tolower(c);
    }
    return result;
}
```

### Example 4: Math Operation Functions
```cpp
#include <iostream>
using namespace std;

// Function prototypes
double calculate(double a, double b, char op);
int factorial(int n);
bool isPrime(int n);
int gcd(int a, int b);
int lcm(int a, int b);

int main() {
    cout << "5 + 3 = " << calculate(5, 3, '+') << endl;
    cout << "10 - 4 = " << calculate(10, 4, '-') << endl;
    cout << "6 * 7 = " << calculate(6, 7, '*') << endl;
    cout << "15 / 3 = " << calculate(15, 3, '/') << endl;
    
    cout << "Factorial of 5: " << factorial(5) << endl;
    cout << "Is 17 prime? " << boolalpha << isPrime(17) << endl;
    cout << "GCD of 12 and 18: " << gcd(12, 18) << endl;
    cout << "LCM of 12 and 18: " << lcm(12, 18) << endl;
    
    return 0;
}

double calculate(double a, double b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b != 0) return a / b;
            else return 0;
        default: return 0;
    }
}

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
```

### Example 5: Menu System with Functions
```cpp
#include <iostream>
#include <string>
using namespace std;

// Function prototypes
void displayMenu();
int getChoice();
void processChoice(int choice);
void startGame();
void loadGame();
void showSettings();
void exitGame();

int main() {
    int choice;
    
    do {
        displayMenu();
        choice = getChoice();
        processChoice(choice);
    } while (choice != 4);
    
    return 0;
}

void displayMenu() {
    cout << "\n=== MAIN MENU ===" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Settings" << endl;
    cout << "4. Exit" << endl;
    cout << "=================" << endl;
}

int getChoice() {
    int choice;
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

void processChoice(int choice) {
    switch(choice) {
        case 1: startGame(); break;
        case 2: loadGame(); break;
        case 3: showSettings(); break;
        case 4: exitGame(); break;
        default: cout << "Invalid choice!" << endl;
    }
}

void startGame() {
    cout << "Starting game..." << endl;
    // Game logic here
}

void loadGame() {
    cout << "Loading game..." << endl;
    // Load logic here
}

void showSettings() {
    cout << "Settings menu..." << endl;
    // Settings logic here
}

void exitGame() {
    cout << "Goodbye!" << endl;
}
```

## Common Mistakes

### Mistake 1: Missing Prototype
```cpp
// Wrong - no prototype
int main() {
    display();  // Error! Function not declared
    return 0;
}

void display() {
    cout << "Hello" << endl;
}

// Correct - with prototype
void display();  // Prototype

int main() {
    display();  // OK
    return 0;
}

void display() {
    cout << "Hello" << endl;
}
```

### Mistake 2: Wrong Return Type
```cpp
// Wrong - returns int but declared void
void getNumber() {
    return 5;  // Error!
}

// Correct
int getNumber() {
    return 5;
}
```

### Mistake 3: Parameter Type Mismatch
```cpp
// Wrong - parameter type mismatch
void process(int x);
int main() {
    process(3.14);  // Double to int conversion (truncates)
    return 0;
}

// Better - match types
void process(double x);
```

### Mistake 4: Missing Semicolon in Prototype
```cpp
// Wrong - missing semicolon
void display()  // No semicolon

// Correct
void display();
```

### Mistake 5: Prototype vs Definition Mismatch
```cpp
// Wrong - prototype and definition don't match
int add(int a, int b);     // Prototype

int add(int x, int y, int z) {  // Definition has 3 parameters
    return x + y + z;
}

// Correct - they match
int add(int a, int b);
int add(int a, int b) {
    return a + b;
}
```

## Quick Reference

| Prototype | Description |
|-----------|-------------|
| `void func();` | No parameters, no return |
| `int func();` | Returns int, no parameters |
| `void func(int x);` | One int parameter, no return |
| `double func(double a, double b);` | Two double parameters, returns double |
| `string func(string s, int n);` | Mixed parameters, returns string |
| `int func(int a, int b = 0);` | Default parameter |
| `int& func();` | Returns reference |

## Summary

- **Function prototype** declares function before use
- Prototype includes: return type, name, parameter types
- Allows functions to be defined after main()
- Parameter names in prototype are optional
- Functions can have default arguments
- Function overloading: same name, different parameters
- void functions don't return values
- Pass by value copies data
- Pass by reference allows modification
- const reference for efficiency without modification

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Function prototypes
void greet(string name);
int add(int a, int b);
double calculateAverage(double scores[], int size);
bool isValid(int value);

int main() {
    // Function calls
    greet("John");
    
    int sum = add(5, 3);
    cout << "Sum: " << sum << endl;
    
    double scores[] = {85.5, 90.0, 78.5};
    double avg = calculateAverage(scores, 3);
    cout << "Average: " << avg << endl;
    
    cout << boolalpha;
    cout << "Is 10 valid? " << isValid(10) << endl;
    
    return 0;
}

// Function definitions
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
}

int add(int a, int b) {
    return a + b;
}

double calculateAverage(double scores[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return sum / size;
}

bool isValid(int value) {
    return value > 0 && value < 100;
}
```

---
*This documentation belongs to https://github.com/InterCentury*