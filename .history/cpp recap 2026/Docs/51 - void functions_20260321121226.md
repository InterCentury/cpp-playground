# 51 - void Functions in C++

## What are void Functions?
Void functions are functions that do not return a value. They perform an action like printing, modifying data, or updating state without giving back a result.

## Basic Syntax

```cpp
void function_name(parameters) {
    // function body
    // No return statement needed (optional)
}
```

## Simple Examples

```cpp
#include <iostream>
using namespace std;

// Simple void function - prints a greeting
void sayHello() {
    cout << "Hello!" << endl;
}

// Void function with parameters
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
}

// Void function that modifies a reference parameter
void increment(int &x) {
    x++;
}

int main() {
    sayHello();
    greet("John");
    
    int num = 5;
    cout << "Before: " << num << endl;
    increment(num);
    cout << "After: " << num << endl;
    
    return 0;
}
```

## Void Functions with and without return

### No Return Statement
```cpp
#include <iostream>
using namespace std;

// No return statement - perfectly fine
void printMessage() {
    cout << "This is a message" << endl;
    cout << "No return needed" << endl;
}

void displayMenu() {
    cout << "1. Start Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Settings" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    printMessage();
    displayMenu();
    
    return 0;
}
```

### With Optional Return Statement
```cpp
#include <iostream>
using namespace std;

// Using return in void function (optional)
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
    return;  // Optional - can be omitted
}

// Early return in void function
void processNumber(int num) {
    if (num < 0) {
        cout << "Negative number - stopping" << endl;
        return;  // Exit function early
    }
    
    cout << "Processing: " << num << endl;
    // More processing...
}

int main() {
    greet("John");
    
    processNumber(-5);
    processNumber(10);
    
    return 0;
}
```

## Practical Examples

### Example 1: Print Functions
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

void printLine() {
    cout << "--------------------" << endl;
}

void printHeader(string title) {
    cout << "\n=== " << title << " ===" << endl;
}

void printArray(const int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void printTable(int rows, int cols) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            cout << setw(4) << i * j;
        }
        cout << endl;
    }
}

int main() {
    printHeader("PRINT FUNCTIONS");
    
    printLine();
    cout << "Hello" << endl;
    printLine();
    
    int numbers[] = {10, 20, 30, 40, 50};
    cout << "Array: ";
    printArray(numbers, 5);
    
    cout << "\nMultiplication Table (3x5):" << endl;
    printTable(3, 5);
    
    return 0;
}
```

### Example 2: Input Functions
```cpp
#include <iostream>
#include <string>
#include <limits>
using namespace std;

void getInput(string &name, int &age) {
    cout << "Enter name: ";
    getline(cin, name);
    
    cout << "Enter age: ";
    cin >> age;
    cin.ignore();
}

void getNumbers(int &a, int &b) {
    cout << "Enter first number: ";
    cin >> a;
    cout << "Enter second number: ";
    cin >> b;
}

void getArray(int arr[], int size) {
    cout << "Enter " << size << " numbers:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "]: ";
        cin >> arr[i];
    }
}

int main() {
    string name;
    int age;
    getInput(name, age);
    cout << "Name: " << name << ", Age: " << age << endl;
    
    int x, y;
    getNumbers(x, y);
    cout << "Sum: " << x + y << endl;
    
    int numbers[5];
    getArray(numbers, 5);
    cout << "You entered: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 3: Modification Functions (by reference)
```cpp
#include <iostream>
using namespace std;

void increment(int &x) {
    x++;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void doubleArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

void toUpperCase(string &text) {
    for (char &c : text) {
        c = toupper(c);
    }
}

int main() {
    int num = 5;
    increment(num);
    cout << "After increment: " << num << endl;
    
    int x = 10, y = 20;
    swap(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    int numbers[] = {1, 2, 3, 4, 5};
    doubleArray(numbers, 5);
    cout << "Doubled array: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    string text = "hello world";
    toUpperCase(text);
    cout << "Uppercase: " << text << endl;
    
    return 0;
}
```

### Example 4: Display Functions
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

void displayWelcome() {
    cout << "==================================" << endl;
    cout << "      WELCOME TO MY PROGRAM       " << endl;
    cout << "==================================" << endl;
}

void displayMenu() {
    cout << "\n--- MENU ---" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Settings" << endl;
    cout << "4. Exit" << endl;
    cout << "Choice: ";
}

void displayResult(string operation, double result) {
    cout << fixed << setprecision(2);
    cout << operation << " result: " << result << endl;
}

void displayStats(const int scores[], int size) {
    int sum = 0;
    int max = scores[0];
    int min = scores[0];
    
    for (int i = 0; i < size; i++) {
        sum += scores[i];
        if (scores[i] > max) max = scores[i];
        if (scores[i] < min) min = scores[i];
    }
    double avg = static_cast<double>(sum) / size;
    
    cout << "\n--- STATISTICS ---" << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Maximum: " << max << endl;
    cout << "Minimum: " << min << endl;
}

int main() {
    displayWelcome();
    
    displayMenu();
    int choice;
    cin >> choice;
    
    displayResult("Calculation", 42.5);
    
    int scores[] = {85, 92, 78, 90, 88};
    displayStats(scores, 5);
    
    return 0;
}
```

### Example 5: Validation and Processing Functions
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void validateUsername(string &username) {
    while (username.length() < 3 || username.length() > 20) {
        cout << "Username must be 3-20 characters. Try again: ";
        getline(cin, username);
    }
}

void sanitizeInput(string &input) {
    // Remove leading/trailing spaces
    size_t start = input.find_first_not_of(" \t");
    size_t end = input.find_last_not_of(" \t");
    
    if (start == string::npos) {
        input = "";
    } else {
        input = input.substr(start, end - start + 1);
    }
}

void convertToLower(string &text) {
    for (char &c : text) {
        c = tolower(c);
    }
}

void processCommand(string command) {
    if (command == "start") {
        cout << "Starting game..." << endl;
    } else if (command == "load") {
        cout << "Loading game..." << endl;
    } else if (command == "exit") {
        cout << "Goodbye!" << endl;
    } else {
        cout << "Unknown command: " << command << endl;
    }
}

int main() {
    string username;
    cout << "Enter username: ";
    getline(cin, username);
    validateUsername(username);
    cout << "Valid username: " << username << endl;
    
    string input = "  Hello World  ";
    cout << "Original: '" << input << "'" << endl;
    sanitizeInput(input);
    cout << "Sanitized: '" << input << "'" << endl;
    
    string command = "START";
    convertToLower(command);
    processCommand(command);
    
    return 0;
}
```

## Void Functions with Reference Parameters

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Modifying single variables
void addBonus(int &score, int bonus) {
    score += bonus;
}

// Modifying arrays
void fillArray(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}

// Modifying vectors
void addNumbers(vector<int> &vec, int count) {
    for (int i = 0; i < count; i++) {
        vec.push_back(i * 10);
    }
}

// Modifying strings
void addSuffix(string &text, string suffix) {
    text += suffix;
}

int main() {
    int score = 85;
    addBonus(score, 10);
    cout << "Score: " << score << endl;
    
    int numbers[5];
    fillArray(numbers, 5, 42);
    cout << "Array: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    vector<int> vec;
    addNumbers(vec, 5);
    cout << "Vector: ";
    for (int v : vec) cout << v << " ";
    cout << endl;
    
    string msg = "Hello";
    addSuffix(msg, " World!");
    cout << msg << endl;
    
    return 0;
}
```

## Void Functions with Early Returns

```cpp
#include <iostream>
using namespace std;

void processNumber(int num) {
    if (num < 0) {
        cout << "Negative numbers not allowed!" << endl;
        return;  // Early exit
    }
    
    cout << "Processing: " << num << endl;
    cout << "Square: " << num * num << endl;
    cout << "Cube: " << num * num * num << endl;
}

void displayUserInfo(string name, int age) {
    if (name.empty()) {
        cout << "Error: Name cannot be empty!" << endl;
        return;
    }
    
    if (age < 0 || age > 150) {
        cout << "Error: Invalid age!" << endl;
        return;
    }
    
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    
    if (age >= 18) {
        cout << "Status: Adult" << endl;
    } else {
        cout << "Status: Minor" << endl;
    }
}

void processArray(const int arr[], int size) {
    if (size <= 0) {
        cout << "Error: Empty array!" << endl;
        return;
    }
    
    cout << "Processing array of size " << size << "..." << endl;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            cout << "Negative value found at index " << i << " - stopping!" << endl;
            return;  // Exit on negative value
        }
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    processNumber(-5);   // Early exit
    processNumber(5);    // Normal processing
    
    cout << endl;
    displayUserInfo("", 25);        // Error: empty name
    displayUserInfo("John", 200);   // Error: invalid age
    displayUserInfo("Alice", 30);   // Normal display
    
    cout << endl;
    int nums[] = {10, 20, -5, 30, 40};
    processArray(nums, 5);  // Stops at negative value
    
    return 0;
}
```

## Void Functions with Static Variables

```cpp
#include <iostream>
using namespace std;

void countCalls() {
    static int callCount = 0;  // Static variable persists between calls
    callCount++;
    cout << "Function called " << callCount << " times" << endl;
}

void resetCounter() {
    static int calls = 0;  // Another static variable
    calls++;
    cout << "Reset function called " << calls << " times" << endl;
}

void trackAverage() {
    static double sum = 0;
    static int count = 0;
    
    double num;
    cout << "Enter a number (0 to stop): ";
    cin >> num;
    
    if (num == 0) {
        if (count > 0) {
            cout << "Average: " << sum / count << endl;
        }
        sum = 0;
        count = 0;
        return;
    }
    
    sum += num;
    count++;
    cout << "Running average: " << sum / count << endl;
}

int main() {
    for (int i = 0; i < 3; i++) {
        countCalls();
    }
    
    for (int i = 0; i < 2; i++) {
        resetCounter();
    }
    
    trackAverage();
    trackAverage();
    trackAverage();
    trackAverage();  // Enter 0 to stop
    
    return 0;
}
```

## Void Functions vs Non-void Functions

```cpp
#include <iostream>
using namespace std;

// Void function - modifies by reference
void addNumbers(int a, int b, int &result) {
    result = a + b;  // Stores result in reference parameter
}

// Non-void function - returns value
int addNumbers(int a, int b) {
    return a + b;  // Returns the result
}

// Void function - prints directly
void printSum(int a, int b) {
    cout << a << " + " << b << " = " << a + b << endl;
}

// Void function - modifies array
void doubleArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

int main() {
    // Using void with reference
    int sum1;
    addNumbers(5, 3, sum1);
    cout << "Sum (reference): " << sum1 << endl;
    
    // Using non-void with return
    int sum2 = addNumbers(5, 3);
    cout << "Sum (return): " << sum2 << endl;
    
    // Using void that prints
    printSum(5, 3);
    
    // Using void that modifies array
    int arr[] = {1, 2, 3};
    doubleArray(arr, 3);
    cout << "Array after double: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Trying to Use Return Value
```cpp
void getNumber() {
    // No return
}

int main() {
    // WRONG - trying to assign void function
    // int x = getNumber();  // Error!
    
    // CORRECT - just call void function
    getNumber();
    
    return 0;
}
```

### Mistake 2: Returning a Value from void
```cpp
// WRONG - cannot return value from void
void getNumber() {
    return 5;  // Error!
}

// CORRECT - use non-void function
int getNumber() {
    return 5;
}
```

### Mistake 3: Missing Early Return
```cpp
void process(int x) {
    if (x < 0) {
        cout << "Error!" << endl;
        // Missing return - continues execution!
    }
    
    cout << "Processing: " << x << endl;  // Runs even when x < 0
}

// CORRECT
void process(int x) {
    if (x < 0) {
        cout << "Error!" << endl;
        return;  // Exit function
    }
    
    cout << "Processing: " << x << endl;
}
```

### Mistake 4: Forgetting & for Reference Parameter
```cpp
// WRONG - passes by value, doesn't modify original
void increment(int x) {
    x++;  // Modifies local copy only
}

// CORRECT - passes by reference
void increment(int &x) {
    x++;  // Modifies original
}
```

### Mistake 5: Using void for Functions That Should Return
```cpp
// WRONG - should return result, not void
void add(int a, int b) {
    int result = a + b;
    // No way to get result back
}

// CORRECT
int add(int a, int b) {
    return a + b;
}
```

## Quick Reference

| Void Function Type | Example | Use Case |
|-------------------|---------|----------|
| No parameters | `void print();` | Simple actions |
| With parameters | `void greet(string name);` | Actions with input |
| With references | `void inc(int &x);` | Modify variables |
| With arrays | `void sort(int arr[], int n);` | Modify arrays |
| Early return | `void check(int x);` | Validation/exit |
| Static variable | `void counter();` | Track calls |

## When to Use void Functions

### ✅ Good Uses for void Functions
```cpp
void printReport();           // Printing
void saveToFile();           // I/O operations
void updateDatabase();       // Side effects
void sortArray(int arr[]);   // Modify data
void logMessage(string msg); // Logging
void clearScreen();          // System actions
```

### ❌ Bad Uses for void Functions
```cpp
// Should return result
void calculateSum(int a, int b);  // Bad - use int instead

// Should return status
void deleteFile(string name);     // Consider bool for success/failure

// Should return data
void getUserInput();              // Should return input
```

## Summary

- **void functions** do not return a value
- Used for **actions**, **modifications**, and **side effects**
- Can use `return;` optionally (especially for early exit)
- Commonly used for **printing**, **input**, **modifying data**
- **Reference parameters** allow modifying variables
- **Static variables** preserve state between calls
- Cannot be used in expressions that expect a value
- Perfect for functions that perform actions without returning results

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Simple void function
void printWelcome() {
    cout << "Welcome to my program!" << endl;
}

// Void with parameters
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
}

// Void with reference parameter
void increment(int &value) {
    value++;
}

// Void with early return
void validateAge(int age) {
    if (age < 0 || age > 150) {
        cout << "Invalid age!" << endl;
        return;
    }
    cout << "Age is valid: " << age << endl;
}

int main() {
    printWelcome();
    greet("John");
    
    int num = 5;
    increment(num);
    cout << "Incremented: " << num << endl;
    
    validateAge(25);
    validateAge(-5);
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*