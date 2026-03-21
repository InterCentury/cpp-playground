# 58 - Returning Values in C++

## What is Returning Values?
Returning values is how functions send results back to the caller. When a function finishes execution, it can return a value using the `return` statement. This allows functions to compute results and pass them back for further use.

## Basic Return Syntax

```cpp
return_type function_name(parameters) {
    // function body
    return value;  // value must match return_type
}
```

## Simple Examples

```cpp
#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;  // Returns the sum
}

double square(double x) {
    return x * x;  // Returns the square
}

string getGreeting(string name) {
    return "Hello, " + name + "!";  // Returns a string
}

int main() {
    int sum = add(5, 3);
    double sq = square(4.5);
    string greeting = getGreeting("John");
    
    cout << "Sum: " << sum << endl;
    cout << "Square: " << sq << endl;
    cout << greeting << endl;
    
    return 0;
}
```

## Returning Different Data Types

### Returning int
```cpp
#include <iostream>
using namespace std;

int getNumber() {
    return 42;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    cout << "Number: " << getNumber() << endl;
    cout << "Max of 5 and 3: " << max(5, 3) << endl;
    cout << "Factorial of 5: " << factorial(5) << endl;
    
    return 0;
}
```

### Returning double
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

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
    cout << "Circle area (r=5): " << circleArea(5) << endl;
    cout << "Average of 10 and 20: " << average(10, 20) << endl;
    cout << "Distance between (0,0) and (3,4): " << distance(0, 0, 3, 4) << endl;
    
    return 0;
}
```

### Returning bool
```cpp
#include <iostream>
using namespace std;

bool isEven(int n) {
    return n % 2 == 0;
}

bool isPositive(int n) {
    return n > 0;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main() {
    cout << boolalpha;
    cout << "5 is even? " << isEven(5) << endl;
    cout << "10 is positive? " << isPositive(10) << endl;
    cout << "2024 is leap year? " << isLeapYear(2024) << endl;
    
    return 0;
}
```

### Returning string
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string toUpperCase(string text) {
    for (char &c : text) {
        c = toupper(c);
    }
    return text;
}

string getGrade(int score) {
    if (score >= 90) return "A";
    if (score >= 80) return "B";
    if (score >= 70) return "C";
    if (score >= 60) return "D";
    return "F";
}

string repeat(string text, int times) {
    string result;
    for (int i = 0; i < times; i++) {
        result += text;
    }
    return result;
}

int main() {
    cout << "Uppercase: " << toUpperCase("hello") << endl;
    cout << "Grade 85: " << getGrade(85) << endl;
    cout << "Repeat: " << repeat("Ha", 3) << endl;
    
    return 0;
}
```

## Returning by Value vs Reference

### Return by Value (Safe)
```cpp
#include <iostream>
using namespace std;

int getValue() {
    int x = 10;
    return x;  // Returns a copy - safe
}

int main() {
    int result = getValue();
    cout << result << endl;
    return 0;
}
```

### Return by Reference (Dangerous - Don't Do This)
```cpp
#include <iostream>
using namespace std;

// DANGEROUS - returns reference to local variable
int& getBadReference() {
    int x = 10;
    return x;  // x destroyed after function ends!
}

int main() {
    int &ref = getBadReference();  // Undefined behavior!
    cout << ref << endl;  // May crash or print garbage
    
    return 0;
}
```

### Safe Return by Reference
```cpp
#include <iostream>
using namespace std;

int& getMax(int &a, int &b) {
    return (a > b) ? a : b;  // Returns reference to existing variable
}

int main() {
    int x = 10, y = 20;
    
    getMax(x, y) = 100;  // Assigns 100 to the larger variable
    
    cout << "x = " << x << ", y = " << y << endl;  // y becomes 100
    
    return 0;
}
```

## Returning Arrays (via Pointer)

```cpp
#include <iostream>
using namespace std;

// Returns pointer to first element
int* createArray(int size, int value) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
    return arr;  // Returns pointer
}

int main() {
    int* numbers = createArray(5, 42);
    
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    delete[] numbers;  // Must free memory
    
    return 0;
}
```

## Returning Structures

```cpp
#include <iostream>
#include <string>
using namespace std;

struct Person {
    string name;
    int age;
    double height;
};

Person createPerson(string name, int age, double height) {
    Person p;
    p.name = name;
    p.age = age;
    p.height = height;
    return p;  // Returns the whole structure
}

struct Point {
    double x, y;
};

Point getMidpoint(Point p1, Point p2) {
    Point mid;
    mid.x = (p1.x + p2.x) / 2;
    mid.y = (p1.y + p2.y) / 2;
    return mid;
}

int main() {
    Person john = createPerson("John", 25, 1.75);
    cout << john.name << ", " << john.age << ", " << john.height << endl;
    
    Point a = {0, 0};
    Point b = {10, 10};
    Point mid = getMidpoint(a, b);
    cout << "Midpoint: (" << mid.x << ", " << mid.y << ")" << endl;
    
    return 0;
}
```

## Returning Multiple Values (Using Pair/Tuple)

```cpp
#include <iostream>
#include <utility>
#include <tuple>
using namespace std;

// Using pair for two values
pair<int, double> getMinMax(int a, int b) {
    if (a < b) {
        return {a, b};  // min, max
    } else {
        return {b, a};
    }
}

// Using tuple for three values
tuple<int, int, double> getStats(int arr[], int size) {
    int sum = 0;
    int max = arr[0];
    int min = arr[0];
    
    for (int i = 0; i < size; i++) {
        sum += arr[i];
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    
    double avg = static_cast<double>(sum) / size;
    return {sum, max, avg};  // sum, max, average
}

int main() {
    auto [minVal, maxVal] = getMinMax(10, 5);
    cout << "Min: " << minVal << ", Max: " << maxVal << endl;
    
    int numbers[] = {10, 20, 30, 40, 50};
    auto [sum, max, avg] = getStats(numbers, 5);
    cout << "Sum: " << sum << ", Max: " << max << ", Avg: " << avg << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Mathematical Functions
```cpp
#include <iostream>
#include <cmath>
using namespace std;

double power(double base, int exponent) {
    double result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
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

double quadraticRoot(int a, int b, int c, bool positive) {
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) return 0;
    
    if (positive) {
        return (-b + sqrt(discriminant)) / (2*a);
    } else {
        return (-b - sqrt(discriminant)) / (2*a);
    }
}

int main() {
    cout << "2^5 = " << power(2, 5) << endl;
    cout << "GCD of 12 and 18: " << gcd(12, 18) << endl;
    cout << "LCM of 12 and 18: " << lcm(12, 18) << endl;
    cout << "Quadratic roots of x² - 5x + 6: " << endl;
    cout << "  Root1: " << quadraticRoot(1, -5, 6, true) << endl;
    cout << "  Root2: " << quadraticRoot(1, -5, 6, false) << endl;
    
    return 0;
}
```

### Example 2: String Processing Functions
```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

string reverse(string text) {
    string result = text;
    int n = result.length();
    for (int i = 0; i < n / 2; i++) {
        swap(result[i], result[n - 1 - i]);
    }
    return result;
}

string toUpperCase(string text) {
    string result = text;
    for (char &c : result) {
        c = toupper(c);
    }
    return result;
}

int countVowels(string text) {
    int count = 0;
    for (char c : text) {
        c = tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

bool isPalindrome(string text) {
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

int main() {
    string text = "Hello World";
    
    cout << "Original: " << text << endl;
    cout << "Reversed: " << reverse(text) << endl;
    cout << "Uppercase: " << toUpperCase(text) << endl;
    cout << "Vowels: " << countVowels(text) << endl;
    cout << "Is 'racecar' palindrome? " << boolalpha << isPalindrome("racecar") << endl;
    
    return 0;
}
```

### Example 3: Array Statistics Functions
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int sumArray(int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
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

int findIndex(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int main() {
    int numbers[] = {45, 23, 78, 12, 89, 34};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Array: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    cout << "Sum: " << sumArray(numbers, size) << endl;
    cout << "Average: " << averageArray(numbers, size) << endl;
    cout << "Max: " << findMax(numbers, size) << endl;
    cout << "Min: " << findMin(numbers, size) << endl;
    cout << "Index of 78: " << findIndex(numbers, size, 78) << endl;
    
    return 0;
}
```

### Example 4: Validation Functions
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isValidUsername(string username) {
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

bool isValidPassword(string password) {
    if (password.length() < 8) return false;
    
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
    size_t dotPos = email.find('.', atPos + 2);
    
    if (atPos == string::npos) return false;
    if (dotPos == string::npos) return false;
    if (atPos == 0) return false;
    if (dotPos == email.length() - 1) return false;
    
    return true;
}

string validateAll(string username, string password, string email) {
    string result;
    
    if (!isValidUsername(username)) {
        result += "Invalid username. ";
    }
    if (!isValidPassword(password)) {
        result += "Invalid password. ";
    }
    if (!isValidEmail(email)) {
        result += "Invalid email.";
    }
    
    if (result.empty()) {
        result = "All valid!";
    }
    
    return result;
}

int main() {
    cout << "Username 'john123': " << boolalpha << isValidUsername("john123") << endl;
    cout << "Password 'Pass123!': " << isValidPassword("Pass123!") << endl;
    cout << "Email 'test@test.com': " << isValidEmail("test@test.com") << endl;
    
    cout << "\nValidation result: " << validateAll("john123", "Pass123!", "test@test.com") << endl;
    cout << "Validation result: " << validateAll("jo", "pass", "invalid") << endl;
    
    return 0;
}
```

### Example 5: File Operations (Simulated)
```cpp
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Simulated file read
string readFile(string filename) {
    if (filename.empty()) {
        return "";  // Return empty string for invalid
    }
    
    // Simulate reading
    return "File content of " + filename;
}

bool writeFile(string filename, string content) {
    if (filename.empty() || content.empty()) {
        return false;  // Return false for failure
    }
    
    // Simulate writing
    return true;
}

int getFileSize(string filename) {
    if (filename.empty()) {
        return -1;  // Return -1 for error
    }
    
    // Simulate getting size
    return 1024;
}

string getFileExtension(string filename) {
    size_t dotPos = filename.find_last_of('.');
    if (dotPos != string::npos) {
        return filename.substr(dotPos + 1);
    }
    return "";
}

int main() {
    string filename = "document.txt";
    
    cout << "Reading file: " << readFile(filename) << endl;
    cout << "File size: " << getFileSize(filename) << " bytes" << endl;
    cout << "Extension: " << getFileExtension(filename) << endl;
    
    bool written = writeFile(filename, "Hello World");
    cout << "Write success: " << boolalpha << written << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Forgetting Return Statement
```cpp
// WRONG - missing return
int add(int a, int b) {
    int sum = a + b;
    // No return - undefined behavior!
}

// CORRECT
int add(int a, int b) {
    int sum = a + b;
    return sum;
}
```

### Mistake 2: Returning Local Variable Address
```cpp
// WRONG - returns address of local variable
int* getPointer() {
    int x = 5;
    return &x;  // x destroyed after function!
}

// CORRECT - return value, not pointer
int getValue() {
    int x = 5;
    return x;
}
```

### Mistake 3: Wrong Return Type
```cpp
// WRONG - returns double but declared int
int getValue() {
    return 3.14;  // Truncated to 3
}

// CORRECT
double getValue() {
    return 3.14;
}
```

### Mistake 4: Not Handling All Return Paths
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

### Mistake 5: Unreachable Code After Return
```cpp
int getNumber() {
    return 42;
    cout << "This never prints!" << endl;  // Unreachable
}
```

## Return Value Optimization (RVO)

```cpp
#include <iostream>
#include <string>
using namespace std;

class LargeObject {
public:
    string data;
    LargeObject() { cout << "Constructor\n"; }
    LargeObject(const LargeObject&) { cout << "Copy constructor\n"; }
};

LargeObject createObject() {
    LargeObject obj;
    return obj;  // RVO may eliminate copy
}

int main() {
    LargeObject obj = createObject();  // May avoid copy
    cout << "Object created\n";
    return 0;
}
```

## Quick Reference

| Return Type | Syntax | Example |
|-------------|--------|---------|
| int | `return value;` | `return 42;` |
| double | `return value;` | `return 3.14;` |
| bool | `return condition;` | `return x > 0;` |
| string | `return expr;` | `return "Hello";` |
| Reference | `return variable;` | `return x;` |
| Pointer | `return ptr;` | `return arr;` |
| Structure | `return {values};` | `return {1, 2};` |

## Summary

- **return** sends value back to caller
- Must match function's declared return type
- **void** functions have no return value (or `return;`)
- Return by **value** creates a copy (safe)
- Return by **reference** returns a reference (must exist after function)
- **Multiple return** statements allowed (early returns)
- **Unreachable code** after return
- **Local variables** are destroyed after return
- **RVO** optimizes away copies of large objects
- Use **pair/tuple** for multiple return values

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

// Basic return examples
int add(int a, int b) {
    return a + b;
}

double average(int a, int b) {
    return (a + b) / 2.0;
}

bool isEven(int n) {
    return n % 2 == 0;
}

string greet(string name) {
    return "Hello, " + name + "!";
}

int main() {
    // Using returned values
    int sum = add(5, 3);
    double avg = average(10, 20);
    bool even = isEven(6);
    string greeting = greet("John");
    
    // Display results
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Is even: " << boolalpha << even << endl;
    cout << greeting << endl;
    
    // Direct use in expressions
    cout << "10 + 20 = " << add(10, 20) << endl;
    cout << "Square of 5 = " << [](int x) { return x * x; }(5) << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*