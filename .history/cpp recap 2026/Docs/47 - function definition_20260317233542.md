# 47 - Function Definition in C++

## What is a Function Definition?
A function definition contains the actual code that runs when the function is called. It includes the function header (same as prototype) and the function body with the implementation.

## Basic Syntax

```cpp
return_type function_name(parameter_list) {
    // Function body
    // Statements
    // Return value (if not void)
}
```

## Simple Examples

```cpp
#include <iostream>
using namespace std;

// Function definitions
void sayHello() {
    cout << "Hello!" << endl;
}

int add(int a, int b) {
    int sum = a + b;
    return sum;
}

double multiply(double x, double y) {
    return x * y;
}

int main() {
    sayHello();
    
    int result = add(5, 3);
    cout << "Sum: " << result << endl;
    
    double product = multiply(2.5, 4.0);
    cout << "Product: " << product << endl;
    
    return 0;
}
```

## Parts of a Function Definition

```cpp
int add(int a, int b) {  // Header (return type, name, parameters)
//  ↑   ↑    ↑     ↑
// return name param1 param2
//  type

    int sum = a + b;     // Body (implementation)
    return sum;          // Return statement
}                        // Closing brace
```

## Function Definitions with Different Return Types

### void Functions (No Return)
```cpp
#include <iostream>
#include <string>
using namespace std;

// void function definitions
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
    // No return statement needed
}

void printLine() {
    cout << "--------------------" << endl;
}

void displayMenu() {
    cout << "1. Start" << endl;
    cout << "2. Load" << endl;
    cout << "3. Exit" << endl;
}

int main() {
    greet("Alice");
    printLine();
    displayMenu();
    
    return 0;
}
```

### int Functions (Return Integer)
```cpp
#include <iostream>
using namespace std;

int getNumber() {
    return 42;  // Returns integer
}

int add(int a, int b) {
    return a + b;  // Returns sum
}

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    cout << "Number: " << getNumber() << endl;
    cout << "Sum: " << add(5, 3) << endl;
    cout << "Factorial of 5: " << factorial(5) << endl;
    
    return 0;
}
```

### double Functions (Return Floating Point)
```cpp
#include <iostream>
#include <cmath>
using namespace std;

double circleArea(double radius) {
    return 3.14159 * radius * radius;
}

double average(double a, double b) {
    return (a + b) / 2.0;
}

double power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int main() {
    cout << "Circle area (r=5): " << circleArea(5) << endl;
    cout << "Average of 10 and 20: " << average(10, 20) << endl;
    cout << "2^5: " << power(2, 5) << endl;
    
    return 0;
}
```

### bool Functions (Return True/False)
```cpp
#include <iostream>
#include <string>
using namespace std;

bool isEven(int num) {
    return num % 2 == 0;
}

bool isPositive(int num) {
    return num > 0;
}

bool isValidEmail(string email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    
    return atPos != string::npos && 
           dotPos != string::npos && 
           atPos > 0 && 
           dotPos > atPos + 1;
}

int main() {
    cout << boolalpha;
    cout << "5 is even? " << isEven(5) << endl;
    cout << "10 is positive? " << isPositive(10) << endl;
    cout << "test@test.com valid? " << isValidEmail("test@test.com") << endl;
    
    return 0;
}
```

### string Functions (Return Text)
```cpp
#include <iostream>
#include <string>
using namespace std;

string getGreeting(string name) {
    return "Hello, " + name + "!";
}

string toUpperCase(string text) {
    string result = text;
    for (char &c : result) {
        c = toupper(c);
    }
    return result;
}

string repeat(string text, int times) {
    string result;
    for (int i = 0; i < times; i++) {
        result += text;
    }
    return result;
}

int main() {
    cout << getGreeting("John") << endl;
    cout << toUpperCase("hello") << endl;
    cout << repeat("Ha", 3) << endl;
    
    return 0;
}
```

## Parameter Passing in Function Definitions

### Pass by Value
```cpp
#include <iostream>
using namespace std;

// Parameter 'x' receives a COPY of the argument
void increment(int x) {
    x++;  // Modifies only the local copy
    cout << "Inside function: " << x << endl;
}

int main() {
    int num = 5;
    cout << "Before: " << num << endl;
    increment(num);
    cout << "After: " << num << endl;  // Still 5!
    
    return 0;
}
```

### Pass by Reference
```cpp
#include <iostream>
using namespace std;

// Parameter 'x' is a REFERENCE to the original variable
void increment(int &x) {
    x++;  // Modifies the original variable
    cout << "Inside function: " << x << endl;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int num = 5;
    cout << "Before: " << num << endl;
    increment(num);
    cout << "After: " << num << endl;  // Now 6!
    
    int x = 10, y = 20;
    cout << "\nBefore swap: x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    return 0;
}
```

### Pass by const Reference
```cpp
#include <iostream>
#include <string>
using namespace std;

// const reference - efficient and safe (can't modify)
void printMessage(const string &msg) {
    cout << msg << endl;
    // msg += "!";  // ERROR! Can't modify const reference
}

double calculateTotal(const double &price, int quantity) {
    return price * quantity;  // Can read, but can't modify
}

int main() {
    string message = "Hello World";
    printMessage(message);  // No copy, efficient
    
    double total = calculateTotal(19.99, 3);
    cout << "Total: $" << total << endl;
    
    return 0;
}
```

### Array Parameters
```cpp
#include <iostream>
using namespace std;

// Array parameter - actually receives pointer
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void modifyArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Modifies original array
    }
}

int sumArray(const int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];  // Can read, but can't modify
    }
    return total;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Original: ";
    printArray(numbers, size);
    
    cout << "Sum: " << sumArray(numbers, size) << endl;
    
    modifyArray(numbers, size);
    cout << "After modify: ";
    printArray(numbers, size);
    
    return 0;
}
```

## Multiple Return Statements

```cpp
#include <iostream>
using namespace std;

// Multiple return statements
int absolute(int x) {
    if (x < 0) {
        return -x;  // Return if negative
    }
    return x;       // Return if positive or zero
}

string getGrade(int score) {
    if (score >= 90) return "A";
    if (score >= 80) return "B";
    if (score >= 70) return "C";
    if (score >= 60) return "D";
    return "F";  // Default return
}

int main() {
    cout << "Absolute of -5: " << absolute(-5) << endl;
    cout << "Grade for 85: " << getGrade(85) << endl;
    
    return 0;
}
```

## Early Return

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Early return for efficiency
bool searchValue(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return true;  // Early return when found
        }
    }
    return false;  // Return after loop if not found
}

int findFirstEven(const vector<int>& numbers) {
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] % 2 == 0) {
            return i;  // Return immediately when found
        }
    }
    return -1;  // Return -1 if no even number found
}

int main() {
    int arr[] = {1, 3, 5, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    cout << boolalpha;
    cout << "Found 8? " << searchValue(arr, size, 8) << endl;
    
    vector<int> nums = {1, 3, 5, 7, 9, 2, 4};
    int pos = findFirstEven(nums);
    if (pos != -1) {
        cout << "First even at index: " << pos << endl;
    }
    
    return 0;
}
```

## Recursive Function Definitions

```cpp
#include <iostream>
using namespace std;

// Recursive function definitions
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void countdown(int n) {
    if (n <= 0) {
        cout << "Blast off!" << endl;
        return;
    }
    cout << n << "... ";
    countdown(n - 1);
}

int main() {
    cout << "Factorial of 5: " << factorial(5) << endl;
    cout << "Fibonacci(10): " << fibonacci(10) << endl;
    cout << "Countdown: ";
    countdown(5);
    
    return 0;
}
```

## Inline Functions

```cpp
#include <iostream>
using namespace std;

// Inline function definition (suggests to compiler to insert code directly)
inline int square(int x) {
    return x * x;
}

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    cout << "Square of 5: " << square(5) << endl;
    cout << "Max of 10 and 20: " << max(10, 20) << endl;
    
    // Compiler may replace square(5) with (5 * 5)
    // instead of function call overhead
    
    return 0;
}
```

## Static Variables in Functions

```cpp
#include <iostream>
using namespace std;

// Function with static variable
int counter() {
    static int count = 0;  // Initialized only once
    count++;
    return count;
}

void showCount() {
    static int calls = 0;
    calls++;
    cout << "This function called " << calls << " times" << endl;
}

int main() {
    cout << "Counter: " << counter() << endl;  // 1
    cout << "Counter: " << counter() << endl;  // 2
    cout << "Counter: " << counter() << endl;  // 3
    
    showCount();  // Called 1 times
    showCount();  // Called 2 times
    showCount();  // Called 3 times
    
    return 0;
}
```

## Practical Examples

### Example 1: Math Operations Library
```cpp
#include <iostream>
#include <cmath>
using namespace std;

// Function definitions for math operations
double circleArea(double radius) {
    const double PI = 3.14159265359;
    return PI * radius * radius;
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

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
    cout << "Circle area (r=5): " << circleArea(5) << endl;
    cout << "Rectangle area (4x6): " << rectangleArea(4, 6) << endl;
    cout << "Triangle area (base=3, height=4): " << triangleArea(3, 4) << endl;
    cout << "25°C to Fahrenheit: " << celsiusToFahrenheit(25) << endl;
    cout << "77°F to Celsius: " << fahrenheitToCelsius(77) << endl;
    cout << "Distance between (0,0) and (3,4): " << distance(0, 0, 3, 4) << endl;
    
    return 0;
}
```

### Example 2: String Processing Library
```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

// String processing function definitions
int countVowels(const string& text) {
    int count = 0;
    for (char c : text) {
        c = tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

int countWords(const string& text) {
    int count = 0;
    bool inWord = false;
    
    for (char c : text) {
        if (isspace(c)) {
            inWord = false;
        } else if (!inWord) {
            count++;
            inWord = true;
        }
    }
    return count;
}

string reverse(const string& text) {
    string result = text;
    int n = result.length();
    for (int i = 0; i < n / 2; i++) {
        swap(result[i], result[n - 1 - i]);
    }
    return result;
}

bool isPalindrome(const string& text) {
    string cleaned;
    for (char c : text) {
        if (isalnum(c)) {
            cleaned += tolower(c);
        }
    }
    
    int left = 0, right = cleaned.length() - 1;
    while (left < right) {
        if (cleaned[left] != cleaned[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

string toTitleCase(string text) {
    bool newWord = true;
    for (char &c : text) {
        if (isspace(c)) {
            newWord = true;
        } else if (newWord) {
            c = toupper(c);
            newWord = false;
        } else {
            c = tolower(c);
        }
    }
    return text;
}

int main() {
    string sample = "Hello World, how are you?";
    
    cout << "Original: " << sample << endl;
    cout << "Vowels: " << countVowels(sample) << endl;
    cout << "Words: " << countWords(sample) << endl;
    cout << "Reversed: " << reverse(sample) << endl;
    cout << "Is palindrome? " << boolalpha << isPalindrome("racecar") << endl;
    cout << "Title case: " << toTitleCase(sample) << endl;
    
    return 0;
}
```

### Example 3: Array Processing Library
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

// Array processing function definitions
void fillArray(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}

void printArray(const int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int sumArray(const int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
}

double averageArray(const int arr[], int size) {
    if (size == 0) return 0;
    return static_cast<double>(sumArray(arr, size)) / size;
}

int findMax(const int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

int findMin(const int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

int findIndex(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        swap(arr[i], arr[size - 1 - i]);
    }
}

void rotateArray(int arr[], int size, int positions) {
    positions = positions % size;
    if (positions < 0) positions += size;
    
    // Create temporary array
    int* temp = new int[positions];
    
    // Copy last 'positions' elements
    for (int i = 0; i < positions; i++) {
        temp[i] = arr[size - positions + i];
    }
    
    // Shift elements
    for (int i = size - 1; i >= positions; i--) {
        arr[i] = arr[i - positions];
    }
    
    // Copy back
    for (int i = 0; i < positions; i++) {
        arr[i] = temp[i];
    }
    
    delete[] temp;
}

int main() {
    int numbers[10];
    
    fillArray(numbers, 10, 5);
    cout << "After fill: ";
    printArray(numbers, 10);
    
    int data[] = {4, 2, 7, 1, 9, 3, 8, 5, 6};
    int size = sizeof(data) / sizeof(data[0]);
    
    cout << "Original: ";
    printArray(data, size);
    
    cout << "Sum: " << sumArray(data, size) << endl;
    cout << "Average: " << averageArray(data, size) << endl;
    cout << "Max: " << findMax(data, size) << endl;
    cout << "Min: " << findMin(data, size) << endl;
    cout << "Index of 7: " << findIndex(data, size, 7) << endl;
    
    reverseArray(data, size);
    cout << "Reversed: ";
    printArray(data, size);
    
    rotateArray(data, size, 3);
    cout << "Rotated right by 3: ";
    printArray(data, size);
    
    return 0;
}
```

### Example 4: Validation Functions
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Validation function definitions
bool isValidUsername(const string& username) {
    // 3-20 characters, alphanumeric only
    if (username.length() < 3 || username.length() > 20) {
        return false;
    }
    
    for (char c : username) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

bool isValidPassword(const string& password) {
    // At least 8 chars, must contain uppercase, lowercase, digit
    if (password.length() < 8) return false;
    
    bool hasUpper = false, hasLower = false, hasDigit = false;
    
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        else if (islower(c)) hasLower = true;
        else if (isdigit(c)) hasDigit = true;
    }
    
    return hasUpper && hasLower && hasDigit;
}

bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos + 2);
    
    if (atPos == string::npos || dotPos == string::npos) {
        return false;
    }
    
    if (atPos == 0 || dotPos == email.length() - 1) {
        return false;
    }
    
    if (dotPos - atPos <= 2) {
        return false;
    }
    
    return true;
}

bool isValidAge(int age) {
    return age >= 0 && age <= 150;
}

bool isValidScore(int score) {
    return score >= 0 && score <= 100;
}

bool isValidPhone(const string& phone) {
    // Simple: only digits, 10-15 chars
    if (phone.length() < 10 || phone.length() > 15) {
        return false;
    }
    
    for (char c : phone) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    cout << boolalpha;
    
    cout << "Username 'john123': " << isValidUsername("john123") << endl;
    cout << "Username 'jo': " << isValidUsername("jo") << endl;
    
    cout << "Password 'Pass123!': " << isValidPassword("Pass123!") << endl;
    cout << "Password 'password': " << isValidPassword("password") << endl;
    
    cout << "Email 'test@test.com': " << isValidEmail("test@test.com") << endl;
    cout << "Email 'invalid': " << isValidEmail("invalid") << endl;
    
    cout << "Age 25: " << isValidAge(25) << endl;
    cout << "Age 200: " << isValidAge(200) << endl;
    
    cout << "Score 85: " << isValidScore(85) << endl;
    cout << "Score -5: " << isValidScore(-5) << endl;
    
    cout << "Phone '1234567890': " << isValidPhone("1234567890") << endl;
    cout << "Phone '123-456-7890': " << isValidPhone("123-456-7890") << endl;
    
    return 0;
}
```

### Example 5: Date and Time Functions
```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// Date/time function definitions
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

bool isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month, year)) return false;
    return true;
}

string formatDate(int day, int month, int year) {
    stringstream ss;
    ss << setfill('0') << setw(2) << day << "/"
       << setw(2) << month << "/"
       << year;
    return ss.str();
}

int dayOfWeek(int day, int month, int year) {
    // Zeller's congruence (simplified)
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int k = year % 100;
    int j = year / 100;
    int result = (day + (13 * (month + 1)) / 5 + k + k/4 + j/4 + 5*j) % 7;
    
    // Convert to Monday=1, Sunday=7
    return ((result + 5) % 7) + 1;
}

string getDayName(int day, int month, int year) {
    int dow = dayOfWeek(day, month, year);
    string days[] = {"Monday", "Tuesday", "Wednesday", 
                     "Thursday", "Friday", "Saturday", "Sunday"};
    return days[dow - 1];
}

int ageInYears(int birthDay, int birthMonth, int birthYear,
               int currentDay, int currentMonth, int currentYear) {
    int age = currentYear - birthYear;
    
    if (currentMonth < birthMonth || 
        (currentMonth == birthMonth && currentDay < birthDay)) {
        age--;
    }
    return age;
}

int main() {
    cout << "Leap year 2024? " << boolalpha << isLeapYear(2024) << endl;
    cout << "Days in Feb 2024: " << daysInMonth(2, 2024) << endl;
    
    int d = 15, m = 3, y = 2024;
    cout << "Date " << formatDate(d, m, y) << " valid? " 
         << isValidDate(d, m, y) << endl;
    
    cout << "Day of week: " << getDayName(d, m, y) << endl;
    
    int age = ageInYears(10, 5, 1990, d, m, y);
    cout << "Age: " << age << endl;
    
    return 0;
}
```

## Common Mistakes in Function Definitions

### Mistake 1: Missing Return Statement
```cpp
// WRONG - missing return
int add(int a, int b) {
    int sum = a + b;
    // No return statement! Undefined behavior
}

// CORRECT
int add(int a, int b) {
    int sum = a + b;
    return sum;
}
```

### Mistake 2: Returning Wrong Type
```cpp
// WRONG - returning double from int function
int getValue() {
    return 3.14;  // Truncated to 3
}

// CORRECT
double getValue() {
    return 3.14;
}
```

### Mistake 3: Not Handling All Paths
```cpp
// WRONG - missing return for else case
int absolute(int x) {
    if (x < 0) {
        return -x;
    }
    // What if x >= 0? Missing return!
}

// CORRECT
int absolute(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}
```

### Mistake 4: Unreachable Code
```cpp
// WRONG - code after return never executes
int getNumber() {
    return 5;
    cout << "This never prints!" << endl;  // Unreachable
}

// CORRECT
int getNumber() {
    cout << "Getting number..." << endl;
    return 5;
}
```

### Mistake 5: Modifying Parameters That Shouldn't Be Modified
```cpp
// WRONG - modifies input parameter
int doubleValue(int x) {
    x *= 2;  // Modifies local copy only - pointless
    return x;
}

// CORRECT
int doubleValue(int x) {
    return x * 2;  // Returns doubled value
}

// Or use reference if you want to modify original
void doubleValue(int &x) {
    x *= 2;
}
```

## Quick Reference

| Component | Description | Example |
|-----------|-------------|---------|
| Return type | Type of value returned | `int`, `double`, `void` |
| Function name | Identifier | `add`, `calculate` |
| Parameters | Input values | `(int a, int b)` |
| Body | Implementation | `{ return a + b; }` |
| Return | Value to return | `return result;` |

## Summary

- **Function definition** contains the actual implementation
- Must match the prototype (if declared)
- **Return type** specifies what the function returns
- **void** functions don't return anything
- Parameters can be passed by value, reference, or const reference
- Functions can have multiple return statements
- **Early return** can improve efficiency
- **Recursive** functions call themselves
- **Static** variables retain values between calls
- **Inline** functions suggest code insertion to avoid call overhead

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Function definition examples
void printMessage(string message) {
    cout << message << endl;
}

int add(int a, int b) {
    return a + b;
}

double average(double a, double b) {
    return (a + b) / 2;
}

bool isEven(int num) {
    return num % 2 == 0;
}

string greet(string name) {
    return "Hello, " + name + "!";
}

int main() {
    printMessage("Testing functions");
    
    cout << "5 + 3 = " << add(5, 3) << endl;
    cout << "Average of 10 and 20: " << average(10, 20) << endl;
    cout << "Is 6 even? " << boolalpha << isEven(6) << endl;
    cout << greet("John") << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*