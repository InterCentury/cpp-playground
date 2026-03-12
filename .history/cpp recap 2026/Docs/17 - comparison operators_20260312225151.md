# 17 - Comparison Operators in C++

## What are Comparison Operators?
Comparison operators are used to compare two values. They always return a boolean result: `true` (1) or `false` (0).

## The Six Comparison Operators

| Operator | Name | Example | Result |
|----------|------|---------|--------|
| `==` | Equal to | `5 == 5` | `true` |
| `!=` | Not equal to | `5 != 3` | `true` |
| `<` | Less than | `3 < 5` | `true` |
| `>` | Greater than | `5 > 3` | `true` |
| `<=` | Less than or equal to | `5 <= 5` | `true` |
| `>=` | Greater than or equal to | `5 >= 3` | `true` |

## Simple Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 5;
    
    cout << boolalpha;  // Show true/false instead of 1/0
    
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a == b: " << (a == b) << endl;  // false
    cout << "a != b: " << (a != b) << endl;  // true
    cout << "a < b: " << (a < b) << endl;    // false
    cout << "a > b: " << (a > b) << endl;    // true
    cout << "a <= b: " << (a <= b) << endl;  // false
    cout << "a >= b: " << (a >= b) << endl;  // true
    
    return 0;
}
```

## Equal to (==)

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5, y = 5, z = 3;
    
    cout << boolalpha;
    cout << x << " == " << y << " : " << (x == y) << endl;  // true
    cout << x << " == " << z << " : " << (x == z) << endl;  // false
    
    // With different types
    double d = 5.0;
    cout << x << " == " << d << " : " << (x == d) << endl;  // true
    
    char ch = 'A';
    int ascii = 65;
    cout << ch << " == " << ascii << " : " << (ch == ascii) << endl;  // true
    
    return 0;
}
```

## Not Equal to (!=)

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 10, c = 20;
    
    cout << boolalpha;
    cout << a << " != " << b << " : " << (a != b) << endl;  // false
    cout << a << " != " << c << " : " << (a != c) << endl;  // true
    
    return 0;
}
```

## Less Than (<)

```cpp
#include <iostream>
using namespace std;

int main() {
    int temperature = 25;
    int freezing = 0;
    int boiling = 100;
    
    cout << boolalpha;
    cout << temperature << " < " << freezing << " : " << (temperature < freezing) << endl;  // false
    cout << temperature << " < " << boiling << " : " << (temperature < boiling) << endl;    // true
    
    // With floating point
    double pi = 3.14159;
    double approx = 3.14;
    cout << approx << " < " << pi << " : " << (approx < pi) << endl;  // true
    
    return 0;
}
```

## Greater Than (>)

```cpp
#include <iostream>
using namespace std;

int main() {
    int score = 85;
    int passing = 60;
    int perfect = 100;
    
    cout << boolalpha;
    cout << score << " > " << passing << " : " << (score > passing) << endl;  // true
    cout << score << " > " << perfect << " : " << (score > perfect) << endl;  // false
    
    return 0;
}
```

## Less Than or Equal To (<=)

```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 18;
    int votingAge = 18;
    int seniorAge = 65;
    
    cout << boolalpha;
    cout << age << " <= " << votingAge << " : " << (age <= votingAge) << endl;  // true
    cout << age << " <= " << seniorAge << " : " << (age <= seniorAge) << endl;  // true
    cout << age << " <= " << 17 << " : " << (age <= 17) << endl;  // false
    
    return 0;
}
```

## Greater Than or Equal To (>=)

```cpp
#include <iostream>
using namespace std;

int main() {
    double grade = 89.5;
    double A_grade = 90;
    double B_grade = 80;
    
    cout << boolalpha;
    cout << grade << " >= " << A_grade << " : " << (grade >= A_grade) << endl;  // false
    cout << grade << " >= " << B_grade << " : " << (grade >= B_grade) << endl;  // true
    
    return 0;
}
```

## Practical Examples

### Example 1: Age Checker
```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    
    cout << "Enter your age: ";
    cin >> age;
    
    cout << boolalpha;
    cout << "Can vote? " << (age >= 18) << endl;
    cout << "Can drive? " << (age >= 16) << endl;
    cout << "Is senior? " << (age >= 65) << endl;
    cout << "Is child? " << (age < 13) << endl;
    
    return 0;
}
```

### Example 2: Grade Calculator
```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    
    cout << "Enter test score (0-100): ";
    cin >> score;
    
    char grade;
    
    if (score >= 90) {
        grade = 'A';
    } else if (score >= 80) {
        grade = 'B';
    } else if (score >= 70) {
        grade = 'C';
    } else if (score >= 60) {
        grade = 'D';
    } else {
        grade = 'F';
    }
    
    cout << "Your grade: " << grade << endl;
    cout << "Passed? " << (score >= 60) << endl;
    
    return 0;
}
```

### Example 3: Temperature Alert
```cpp
#include <iostream>
using namespace std;

int main() {
    double temperature;
    
    cout << "Enter temperature in Celsius: ";
    cin >> temperature;
    
    cout << boolalpha;
    cout << "Freezing? " << (temperature <= 0) << endl;
    cout << "Boiling? " << (temperature >= 100) << endl;
    cout << "Room temperature? " << (temperature >= 18 && temperature <= 24) << endl;
    
    if (temperature < -10) {
        cout << "Extreme cold warning!" << endl;
    } else if (temperature > 40) {
        cout << "Extreme heat warning!" << endl;
    }
    
    return 0;
}
```

### Example 4: Password Validator
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string password;
    string confirm;
    
    cout << "Create password: ";
    cin >> password;
    cout << "Confirm password: ";
    cin >> confirm;
    
    bool match = (password == confirm);
    bool lengthOK = (password.length() >= 8);
    
    cout << boolalpha;
    cout << "Passwords match: " << match << endl;
    cout << "Length OK (>=8): " << lengthOK << endl;
    
    if (match && lengthOK) {
        cout << "Password accepted!" << endl;
    } else {
        cout << "Password requirements not met." << endl;
    }
    
    return 0;
}
```

### Example 5: Number Comparison Game
```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = rand() % 10 + 1;  // Random 1-10
    int guess;
    
    cout << "Guess the number (1-10): ";
    cin >> guess;
    
    cout << boolalpha;
    cout << "Correct? " << (guess == secret) << endl;
    cout << "Too high? " << (guess > secret) << endl;
    cout << "Too low? " << (guess < secret) << endl;
    
    if (guess == secret) {
        cout << "You win!" << endl;
    } else if (guess > secret) {
        cout << "Too high! The number was " << secret << endl;
    } else {
        cout << "Too low! The number was " << secret << endl;
    }
    
    return 0;
}
```

## Comparing Different Types

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << boolalpha;
    
    // int vs double
    cout << "10 == 10.0: " << (10 == 10.0) << endl;      // true
    cout << "10 == 10.5: " << (10 == 10.5) << endl;      // false
    
    // char vs int (ASCII comparison)
    cout << "'A' == 65: " << ('A' == 65) << endl;        // true
    cout << "'A' < 'a': " << ('A' < 'a') << endl;        // true (65 < 97)
    
    // bool vs int
    cout << "true == 1: " << (true == 1) << endl;        // true
    cout << "false == 0: " << (false == 0) << endl;      // true
    
    return 0;
}
```

## Comparing Strings

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name1 = "Alice";
    string name2 = "Alice";
    string name3 = "Bob";
    
    cout << boolalpha;
    cout << name1 << " == " << name2 << ": " << (name1 == name2) << endl;  // true
    cout << name1 << " == " << name3 << ": " << (name1 == name3) << endl;  // false
    cout << name1 << " != " << name3 << ": " << (name1 != name3) << endl;  // true
    
    // Lexicographic (dictionary) comparison
    cout << "apple < banana: " << ("apple" < "banana") << endl;  // true
    cout << "Apple < apple: " << ("Apple" < "apple") << endl;    // true (ASCII)
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Using = Instead of ==
```cpp
int x = 5;

// Wrong - assignment, not comparison
if (x = 10) {
    cout << "This always runs!" << endl;
}

// Correct
if (x == 10) {
    cout << "This runs only if x equals 10" << endl;
}
```

### Mistake 2: Floating Point Comparison
```cpp
double a = 0.1 + 0.2;  // Might be 0.30000000000000004
double b = 0.3;

// Wrong - may not be true due to precision
if (a == b) {
    cout << "Equal" << endl;
}

// Correct - use small epsilon
double epsilon = 0.000001;
if (abs(a - b) < epsilon) {
    cout << "Approximately equal" << endl;
}
```

### Mistake 3: Comparison Chain
```cpp
int x = 5;

// Wrong - doesn't work as expected
if (1 < x < 10) {  // Actually (1 < x) < 10 → true < 10 → 1 < 10 → true
    cout << "x is between 1 and 10" << endl;  // Always runs!
}

// Correct
if (1 < x && x < 10) {
    cout << "x is between 1 and 10" << endl;
}
```

### Mistake 4: Comparing Different Types
```cpp
// Works but can be confusing
cout << (10 < "5") << endl;  // Compares int with pointer! Don't do this

// Be explicit
int a = 10;
int b = 5;
cout << (a < b) << endl;
```

### Mistake 5: Forgetting Parentheses
```cpp
int a = 5, b = 10;

// Wrong - << has higher precedence than <
cout << "a < b is " << a < b << endl;  // Error!

// Correct
cout << "a < b is " << (a < b) << endl;
```

## Using Comparison Results

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 5;
    
    // Store comparison result
    bool isGreater = (x > y);
    bool isEqual = (x == y);
    
    cout << boolalpha;
    cout << "isGreater: " << isGreater << endl;
    cout << "isEqual: " << isEqual << endl;
    
    // Use in conditions
    if (isGreater) {
        cout << x << " is greater than " << y << endl;
    }
    
    // Use in calculations
    int result = (x > y) * 10;  // true=1, so 1*10 = 10
    cout << "Result: " << result << endl;
    
    return 0;
}
```

## Quick Reference Table

| Operator | Name | True Example | False Example |
|----------|------|--------------|---------------|
| `==` | Equal to | `5 == 5` | `5 == 3` |
| `!=` | Not equal | `5 != 3` | `5 != 5` |
| `<` | Less than | `3 < 5` | `5 < 3` |
| `>` | Greater than | `5 > 3` | `3 > 5` |
| `<=` | Less/equal | `5 <= 5` | `7 <= 5` |
| `>=` | Greater/equal | `5 >= 5` | `3 >= 5` |

## Summary

- **Comparison operators** compare two values and return `true` or `false`
- **==** checks equality (not assignment!)
- **!=** checks inequality
- **<**, **>**, **<=**, **>=** check magnitude relationships
- Always use `==` for comparison, not `=`
- Be careful with floating point comparisons (use epsilon)
- Chain comparisons with `&&` (and) or `||` (or)
- Parentheses matter with `cout`
- Strings compare lexicographically (dictionary order)
- Characters compare by ASCII values
- Comparison results can be stored in bool variables

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    
    cout << "Enter two numbers: ";
    cin >> a >> b;
    
    cout << boolalpha;
    cout << a << " == " << b << ": " << (a == b) << endl;
    cout << a << " != " << b << ": " << (a != b) << endl;
    cout << a << " < " << b << ": " << (a < b) << endl;
    cout << a << " > " << b << ": " << (a > b) << endl;
    cout << a << " <= " << b << ": " << (a <= b) << endl;
    cout << a << " >= " << b << ": " << (a >= b) << endl;
    
    return 0;
}
```
  *This documentation belongs to https://github.com/InterCentury*