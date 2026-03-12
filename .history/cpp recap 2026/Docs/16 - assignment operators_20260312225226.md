# 16 - Assignment Operators in C++

## What are Assignment Operators?
Assignment operators are used to assign values to variables. The most basic is `=`, but there are compound assignment operators that combine assignment with another operation.

## The Basic Assignment Operator (=)

```cpp
#include <iostream>
using namespace std;

int main() {
    int x;           // Declare variable
    x = 10;          // Assign value 10 to x
    
    cout << "x = " << x << endl;
    
    // Assignment can be chained
    int a, b, c;
    a = b = c = 5;   // All three get value 5
    
    cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
    
    return 0;
}
```

## Compound Assignment Operators

| Operator | Name | Example | Meaning |
|----------|------|---------|---------|
| `+=` | Add and assign | `x += 5` | `x = x + 5` |
| `-=` | Subtract and assign | `x -= 5` | `x = x - 5` |
| `*=` | Multiply and assign | `x *= 5` | `x = x * 5` |
| `/=` | Divide and assign | `x /= 5` | `x = x / 5` |
| `%=` | Modulus and assign | `x %= 5` | `x = x % 5` |

## Addition Assignment (+=)

```cpp
#include <iostream>
using namespace std;

int main() {
    int score = 10;
    cout << "Initial score: " << score << endl;
    
    score += 5;  // score = score + 5
    cout << "After += 5: " << score << endl;  // 15
    
    score += 3;  // score = score + 3
    cout << "After += 3: " << score << endl;  // 18
    
    // Works with variables too
    int bonus = 7;
    score += bonus;  // score = score + bonus
    cout << "After += bonus (7): " << score << endl;  // 25
    
    return 0;
}
```

## Subtraction Assignment (-=)

```cpp
#include <iostream>
using namespace std;

int main() {
    int health = 100;
    cout << "Initial health: " << health << endl;
    
    health -= 20;  // health = health - 20
    cout << "After -= 20: " << health << endl;  // 80
    
    health -= 15;  // health = health - 15
    cout << "After -= 15: " << health << endl;  // 65
    
    int damage = 30;
    health -= damage;  // health = health - damage
    cout << "After -= damage (30): " << health << endl;  // 35
    
    return 0;
}
```

## Multiplication Assignment (*=)

```cpp
#include <iostream>
using namespace std;

int main() {
    int money = 10;
    cout << "Initial money: $" << money << endl;
    
    money *= 2;  // money = money * 2
    cout << "After *= 2: $" << money << endl;  // 20
    
    money *= 3;  // money = money * 3
    cout << "After *= 3: $" << money << endl;  // 60
    
    int multiplier = 4;
    money *= multiplier;  // money = money * multiplier
    cout << "After *= multiplier (4): $" << money << endl;  // 240
    
    return 0;
}
```

## Division Assignment (/=)

```cpp
#include <iostream>
using namespace std;

int main() {
    int pizza = 8;
    cout << "Initial pizza slices: " << pizza << endl;
    
    pizza /= 2;  // pizza = pizza / 2
    cout << "After /= 2: " << pizza << endl;  // 4
    
    pizza /= 2;  // pizza = pizza / 2
    cout << "After /= 2: " << pizza << endl;  // 2
    
    // Careful with integer division!
    int cookies = 10;
    cookies /= 3;  // 10 / 3 = 3 (truncated)
    cout << "10 cookies shared among 3: " << cookies << endl;  // 3
    
    return 0;
}
```

## Modulus Assignment (%=)

```cpp
#include <iostream>
using namespace std;

int main() {
    int number = 17;
    cout << "Initial number: " << number << endl;
    
    number %= 5;  // number = number % 5
    cout << "After %= 5: " << number << endl;  // 2 (remainder of 17/5)
    
    int num = 24;
    num %= 7;  // 24 % 7 = 3
    cout << "24 %= 7: " << num << endl;  // 3
    
    return 0;
}
```

## All Operators in One Example

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 20;
    cout << "Starting with x = " << x << endl;
    
    x += 5;   cout << "x += 5  → " << x << endl;   // 25
    x -= 3;   cout << "x -= 3  → " << x << endl;   // 22
    x *= 2;   cout << "x *= 2  → " << x << endl;   // 44
    x /= 4;   cout << "x /= 4  → " << x << endl;   // 11
    x %= 3;   cout << "x %= 3  → " << x << endl;   // 2
    
    return 0;
}
```

## Practical Examples

### Example 1: Game Score System
```cpp
#include <iostream>
using namespace std;

int main() {
    int score = 0;
    int level = 1;
    
    cout << "Game Started!" << endl;
    cout << "Level: " << level << ", Score: " << score << endl;
    
    // Complete level 1
    score += 100;
    level += 1;
    cout << "Level " << level-1 << " completed!" << endl;
    cout << "Level: " << level << ", Score: " << score << endl;
    
    // Collect bonus
    score += 50;
    cout << "Bonus collected!" << endl;
    cout << "Score: " << score << endl;
    
    // Buy item (spend points)
    score -= 30;
    cout << "Bought item! Score: " << score << endl;
    
    // Double points event
    score *= 2;
    cout << "Double points! Score: " << score << endl;
    
    return 0;
}
```

### Example 2: Shopping Cart
```cpp
#include <iostream>
using namespace std;

int main() {
    double total = 0.0;
    double price;
    char choice;
    
    do {
        cout << "Enter item price: $";
        cin >> price;
        
        total += price;  // Add to total
        
        cout << "Current total: $" << total << endl;
        cout << "Add another item? (y/n): ";
        cin >> choice;
        
    } while (choice == 'y' || choice == 'Y');
    
    // Apply discount
    cout << "\nApplying 10% discount..." << endl;
    total *= 0.9;  // 10% off
    
    cout << "Final total after discount: $" << total << endl;
    
    return 0;
}
```

### Example 3: Countdown Timer
```cpp
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    int timer = 10;
    
    cout << "Countdown starting: " << timer << endl;
    
    while (timer > 0) {
        this_thread::sleep_for(chrono::seconds(1));
        timer -= 1;  // Decrease by 1 each second
        cout << timer << "... " << endl;
    }
    
    cout << "Blast off!" << endl;
    
    return 0;
}
```

### Example 4: Bank Account
```cpp
#include <iostream>
using namespace std;

int main() {
    double balance = 1000.0;
    int choice;
    double amount;
    
    cout << "Welcome to Bank ATM" << endl;
    cout << "Current balance: $" << balance << endl;
    
    do {
        cout << "\n1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Enter amount to deposit: $";
                cin >> amount;
                balance += amount;  // Add to balance
                cout << "Deposited: $" << amount << endl;
                cout << "New balance: $" << balance << endl;
                break;
                
            case 2:
                cout << "Enter amount to withdraw: $";
                cin >> amount;
                if (amount <= balance) {
                    balance -= amount;  // Subtract from balance
                    cout << "Withdrawn: $" << amount << endl;
                } else {
                    cout << "Insufficient funds!" << endl;
                }
                cout << "Balance: $" << balance << endl;
                break;
                
            case 3:
                cout << "Current balance: $" << balance << endl;
                break;
        }
    } while (choice != 4);
    
    return 0;
}
```

### Example 5: Student Grade Calculator
```cpp
#include <iostream>
using namespace std;

int main() {
    int totalPoints = 0;
    int numAssignments = 0;
    int score;
    char more;
    
    do {
        cout << "Enter assignment score (0-100): ";
        cin >> score;
        
        totalPoints += score;  // Add to total
        numAssignments++;       // Increment counter
        
        cout << "More assignments? (y/n): ";
        cin >> more;
        
    } while (more == 'y' || more == 'Y');
    
    double average = (double)totalPoints / numAssignments;
    
    cout << "\nTotal points: " << totalPoints << endl;
    cout << "Number of assignments: " << numAssignments << endl;
    cout << "Average: " << average << endl;
    
    return 0;
}
```

## Assignment with Different Data Types

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Integer assignment
    int count = 0;
    count += 5;      // 5
    count *= 2;      // 10
    cout << "Count: " << count << endl;
    
    // Double assignment
    double price = 10.99;
    price *= 1.1;    // Add 10% tax
    cout << "Price with tax: $" << price << endl;
    
    // String concatenation with +=
    string message = "Hello";
    message += " World";  // Hello World
    cout << message << endl;
    
    string name = "John";
    name += " Doe";       // John Doe
    cout << name << endl;
    
    return 0;
}
```

## Chained Assignment

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b, c, d;
    
    // All get the same value
    a = b = c = d = 10;
    
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    
    // This works right to left
    int x = 5;
    int y = (x += 3);  // x becomes 8, y becomes 8
    
    cout << "x = " << x << ", y = " << y << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Using = Instead of ==
```cpp
int x = 5;

// Wrong - assignment, not comparison
if (x = 10) {
    // This always runs, x becomes 10
}

// Correct
if (x == 10) {
    // Check if x equals 10
}
```

### Mistake 2: Wrong Order in Compound Assignment
```cpp
int x = 10;

// Wrong
x =+ 5;  // This is x = 5 (typo, actually assigns +5)

// Correct
x += 5;  // x becomes 15
```

### Mistake 3: Division by Zero
```cpp
int x = 10;
int y = 0;

// x /= y;  // ❌ Crash! Division by zero

// Check first
if (y != 0) {
    x /= y;
} else {
    cout << "Cannot divide by zero" << endl;
}
```

### Mistake 4: Modulus with Floats
```cpp
double x = 10.5;

// x %= 3;  // ❌ Error! % not for floats

// Correct for integers
int a = 10;
a %= 3;  // a = 1
```

### Mistake 5: Forgetting Assignment Returns Value
```cpp
int x;
cout << x = 5;  // ❌ Error! << has higher precedence

// Correct
x = 5;
cout << x;

// Or
cout << (x = 5);  // Prints 5
```

## Best Practices

### ✅ Do This
```cpp
// Use compound operators for shorter code
x += 5;  // Better than x = x + 5

// Initialize before using
int score = 0;
score += 10;

// Check for division by zero
if (denominator != 0) {
    result /= denominator;
}

// Use meaningful variable names
totalPrice += itemPrice;
health -= damage;
score *= multiplier;
```

### ❌ Avoid This
```cpp
// Don't confuse = and ==
if (x = 5) { }  // Assignment inside if

// Don't write x =+ 5 (typo)
x =+ 5;  // Actually x = 5

// Don't divide by zero
x /= 0;

// Don't use % with floats
float f = 10.5;
f %= 3;  // Wrong!

// Don't chain too many assignments (hard to read)
a = b = c = d = e = f = g = 10;
```

## Quick Reference Table

| Operator | Example | Meaning | Result (if x=10) |
|----------|---------|---------|------------------|
| `=` | `x = 5` | Assign | `x = 5` |
| `+=` | `x += 5` | Add and assign | `x = 15` |
| `-=` | `x -= 5` | Subtract and assign | `x = 5` |
| `*=` | `x *= 5` | Multiply and assign | `x = 50` |
| `/=` | `x /= 5` | Divide and assign | `x = 2` |
| `%=` | `x %= 5` | Modulus and assign | `x = 0` |

## Summary

- **=** is the basic assignment operator
- **Compound operators** combine operation with assignment
- `+=`, `-=`, `*=`, `/=`, `%=` are compound operators
- They make code shorter and clearer
- Assignment can be chained: `a = b = c = 5`
- Be careful with `=` vs `==` in conditions
- Check for division by zero before using `/=` 
- Modulus (`%=`) only works with integers
- String concatenation works with `+=`
- Compound operators work with all numeric types

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 10;
    
    cout << "Initial value: " << value << endl;
    
    // Try each operator
    value += 5;
    cout << "After += 5: " << value << endl;
    
    value -= 3;
    cout << "After -= 3: " << value << endl;
    
    value *= 2;
    cout << "After *= 2: " << value << endl;
    
    value /= 4;
    cout << "After /= 4: " << value << endl;
    
    value %= 3;
    cout << "After %= 3: " << value << endl;
    
    return 0;
}
```

  *This documentation belongs to https://github.com/InterCentury*