# 24 - Nested if Statements in C++

## What are Nested if Statements?
Nested `if` statements are `if` statements inside another `if` or `else` block. They allow you to check more specific conditions after a general condition is met.

## Basic Syntax

```cpp
if (condition1) {
    // code executes if condition1 is true
    
    if (condition2) {
        // code executes if both condition1 and condition2 are true
    }
    
    if (condition3) {
        // code executes if condition1 and condition3 are true
    }
}
``` 

## Simple Example

```cpp
#include <iostream>
using namespace std;

int main() {
    int num = 15;
    
    if (num > 0) {
        cout << "Number is positive." << endl;
        
        if (num % 2 == 0) {
            cout << "Number is even." << endl;
        } else {
            cout << "Number is odd." << endl;
        }
        
        if (num > 10) {
            cout << "Number is greater than 10." << endl;
        }
    }
    
    return 0;
}
```
Output:
```
Number is positive.
Number is odd.
Number is greater than 10.
```

## Nested if with else

```cpp
#include <iostream>
using namespace std;

int main() {
    int num = -5;
    
    if (num >= 0) {
        cout << "Number is non-negative." << endl;
        
        if (num == 0) {
            cout << "Number is zero." << endl;
        } else {
            cout << "Number is positive." << endl;
        }
    } else {
        cout << "Number is negative." << endl;
        
        if (num < -10) {
            cout << "Number is very negative." << endl;
        }
    }
    
    return 0;
}
```

## Practical Examples

### Example 1: Login System with Role Check
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string username;
    string password;
    string role;
    
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    
    if (username == "admin") {
        cout << "Admin username correct." << endl;
        
        if (password == "admin123") {
            cout << "Admin password correct." << endl;
            
            cout << "Enter role (manager/staff): ";
            cin >> role;
            
            if (role == "manager") {
                cout << "Welcome Manager! Full access granted." << endl;
            } else if (role == "staff") {
                cout << "Welcome Staff! Limited access." << endl;
            } else {
                cout << "Invalid role!" << endl;
            }
        } else {
            cout << "Incorrect admin password!" << endl;
        }
    } else if (username == "user") {
        cout << "User username correct." << endl;
        
        if (password == "user123") {
            cout << "Welcome User! Basic access granted." << endl;
        } else {
            cout << "Incorrect user password!" << endl;
        }
    } else {
        cout << "Username not found!" << endl;
    }
    
    return 0;
}
```

### Example 2: Bank Transaction System
```cpp
#include <iostream>
using namespace std;

int main() {
    double balance = 1000.0;
    double amount;
    int transactionType;
    
    cout << "Current balance: $" << balance << endl;
    cout << "1. Withdraw" << endl;
    cout << "2. Deposit" << endl;
    cout << "Choice: ";
    cin >> transactionType;
    
    if (transactionType == 1) {
        cout << "Enter withdrawal amount: $";
        cin >> amount;
        
        if (amount > 0) {
            if (amount <= balance) {
                if (amount <= 500) {
                    balance -= amount;
                    cout << "Withdrawal successful!" << endl;
                    cout << "New balance: $" << balance << endl;
                } else {
                    cout << "Withdrawal limit is $500!" << endl;
                }
            } else {
                cout << "Insufficient funds!" << endl;
            }
        } else {
            cout << "Invalid amount!" << endl;
        }
    } else if (transactionType == 2) {
        cout << "Enter deposit amount: $";
        cin >> amount;
        
        if (amount > 0) {
            if (amount <= 10000) {
                balance += amount;
                cout << "Deposit successful!" << endl;
                cout << "New balance: $" << balance << endl;
            } else {
                cout << "Deposit limit is $10000!" << endl;
            }
        } else {
            cout << "Invalid amount!" << endl;
        }
    } else {
        cout << "Invalid transaction type!" << endl;
    }
    
    return 0;
}
```

### Example 3: Student Grading System
```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    char extraCredit;
    
    cout << "Enter test score (0-100): ";
    cin >> score;
    
    if (score >= 0 && score <= 100) {
        cout << "Valid score." << endl;
        
        if (score >= 60) {
            cout << "Student passed." << endl;
            
            if (score >= 90) {
                cout << "Grade: A" << endl;
                
                cout << "Did student complete extra credit? (y/n): ";
                cin >> extraCredit;
                
                if (extraCredit == 'y' || extraCredit == 'Y') {
                    cout << "Student gets honors!" << endl;
                }
            } else if (score >= 80) {
                cout << "Grade: B" << endl;
            } else if (score >= 70) {
                cout << "Grade: C" << endl;
            } else {
                cout << "Grade: D" << endl;
            }
        } else {
            cout << "Student failed." << endl;
            
            if (score >= 50) {
                cout << "Eligible for retake." << endl;
            } else {
                cout << "Must repeat course." << endl;
            }
        }
    } else {
        cout << "Invalid score!" << endl;
    }
    
    return 0;
}
```

### Example 4: Restaurant Order System
```cpp
#include <iostream>
using namespace std;

int main() {
    int mealType;
    int drinkType;
    int size;
    double total = 0;
    
    cout << "Restaurant Order System" << endl;
    cout << "1. Burger Meal" << endl;
    cout << "2. Pizza Meal" << endl;
    cout << "3. Salad Meal" << endl;
    cout << "Choose meal: ";
    cin >> mealType;
    
    if (mealType == 1) {
        cout << "Burger Meal selected." << endl;
        total += 8.99;
        
        cout << "Choose burger size:" << endl;
        cout << "1. Regular" << endl;
        cout << "2. Large" << endl;
        cin >> size;
        
        if (size == 1) {
            cout << "Regular burger." << endl;
        } else if (size == 2) {
            total += 2.00;
            cout << "Large burger (+$2.00)." << endl;
        } else {
            cout << "Invalid size, default to regular." << endl;
        }
        
        cout << "Add drink? (1 for yes, 0 for no): ";
        cin >> drinkType;
        
        if (drinkType == 1) {
            cout << "1. Soda" << endl;
            cout << "2. Juice" << endl;
            cin >> size;
            
            if (size == 1) {
                total += 1.99;
                cout << "Soda added." << endl;
            } else if (size == 2) {
                total += 2.49;
                cout << "Juice added." << endl;
            }
        }
    } else if (mealType == 2) {
        cout << "Pizza Meal selected." << endl;
        total += 10.99;
        // More pizza options...
    } else if (mealType == 3) {
        cout << "Salad Meal selected." << endl;
        total += 6.99;
        // More salad options...
    }
    
    cout << "Total: $" << total << endl;
    
    return 0;
}
```

### Example 5: Ticket Booking System
```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    char membership;
    char student;
    double ticketPrice = 50.0;
    
    cout << "Enter age: ";
    cin >> age;
    
    if (age > 0 && age < 120) {
        cout << "Valid age." << endl;
        
        if (age < 12) {
            cout << "Child ticket." << endl;
            ticketPrice *= 0.5;  // 50% discount
        } else if (age >= 60) {
            cout << "Senior ticket." << endl;
            ticketPrice *= 0.7;  // 30% discount
        } else {
            cout << "Adult ticket." << endl;
            
            cout << "Have membership? (y/n): ";
            cin >> membership;
            
            if (membership == 'y' || membership == 'Y') {
                cout << "Student? (y/n): ";
                cin >> student;
                
                if (student == 'y' || student == 'Y') {
                    ticketPrice *= 0.6;  // 40% discount
                    cout << "Student with membership!" << endl;
                } else {
                    ticketPrice *= 0.8;  // 20% discount
                    cout << "Member discount applied." << endl;
                }
            } else {
                cout << "Student? (y/n): ";
                cin >> student;
                
                if (student == 'y' || student == 'Y') {
                    ticketPrice *= 0.7;  // 30% discount
                    cout << "Student discount applied." << endl;
                }
            }
        }
        
        cout << "Final ticket price: $" << ticketPrice << endl;
    } else {
        cout << "Invalid age!" << endl;
    }
    
    return 0;
}
```

## Deeply Nested if Statements

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 1, b = 2, c = 3, d = 4;
    
    if (a == 1) {
        cout << "Level 1: a is 1" << endl;
        
        if (b == 2) {
            cout << "Level 2: b is 2" << endl;
            
            if (c == 3) {
                cout << "Level 3: c is 3" << endl;
                
                if (d == 4) {
                    cout << "Level 4: d is 4" << endl;
                    cout << "All conditions met!" << endl;
                }
            }
        }
    }
    
    return 0;
}
```

## Nested if with Logical Operators Alternative

Sometimes logical operators can replace nested if:

```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 25;
    bool hasLicense = true;
    bool hasInsurance = true;
    
    // Nested if version
    cout << "Nested if version:" << endl;
    if (age >= 18) {
        if (hasLicense) {
            if (hasInsurance) {
                cout << "You can drive!" << endl;
            }
        }
    }
    
    // Logical operator version (cleaner)
    cout << "\nLogical operator version:" << endl;
    if (age >= 18 && hasLicense && hasInsurance) {
        cout << "You can drive!" << endl;
    }
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Missing Braces
```cpp
int x = 10, y = 5;

// Wrong - only first line is in inner if
if (x > 0)
    if (y > 0)
        cout << "Both positive" << endl;
    cout << "This always runs!" << endl;  // Not in inner if!

// Correct
if (x > 0) {
    if (y > 0) {
        cout << "Both positive" << endl;
    }
    cout << "This runs only when x > 0" << endl;
}
```

### Mistake 2: Dangling Else
```cpp
int x = 10, y = 5;

// Which if does this else belong to?
if (x > 0)
    if (y > 0)
        cout << "Both positive" << endl;
else
    cout << "x is not positive" << endl;  // Else belongs to inner if!

// Correct - use braces to clarify
if (x > 0) {
    if (y > 0) {
        cout << "Both positive" << endl;
    }
} else {
    cout << "x is not positive" << endl;
}
```

### Mistake 3: Too Deep Nesting
```cpp
// Hard to read and maintain
if (a == 1) {
    if (b == 2) {
        if (c == 3) {
            if (d == 4) {
                if (e == 5) {
                    // Too deep!
                }
            }
        }
    }
}

// Better - combine conditions
if (a == 1 && b == 2 && c == 3 && d == 4 && e == 5) {
    // Much cleaner
}
```

### Mistake 4: Redundant Checks
```cpp
int x = 10;

// Redundant - outer if already checks x > 0
if (x > 0) {
    if (x > 5) {
        cout << "x > 5" << endl;
    }
}

// Better
if (x > 5) {
    cout << "x > 5" << endl;
} else if (x > 0) {
    cout << "x is positive but ≤ 5" << endl;
}
```

### Mistake 5: Forgetting else Cases
```cpp
int x = 5;

if (x > 0) {
    cout << "Positive" << endl;
    
    if (x > 10) {
        cout << "> 10" << endl;
    }
    // Missing else for x ≤ 10 but > 0
}

// Better
if (x > 0) {
    cout << "Positive" << endl;
    
    if (x > 10) {
        cout << "> 10" << endl;
    } else {
        cout << "≤ 10" << endl;
    }
}
```

## Best Practices

### ✅ Do This
```cpp
// Use braces even for single statements
if (condition) {
    if (innerCondition) {
        statement;
    }
}

// Limit nesting depth (max 3-4 levels)
if (condition1) {
    if (condition2) {
        if (condition3) {
            // OK
        }
    }
}

// Consider combining with logical operators
if (condition1 && condition2 && condition3) {
    // Cleaner than nested ifs
}

// Always handle else cases
if (condition) {
    // true case
} else {
    // false case (even if empty)
}
```

### ❌ Avoid This
```cpp
// Don't skip braces
if (condition)
    if (inner) 
        statement;

// Don't nest too deep
if (a)
    if (b)
        if (c)
            if (d)
                // Too deep!

// Don't forget else cases
if (a) {
    if (b) {
        // Missing else for b
    }
}
// Missing else for a
```

## vs else-if Ladder

```cpp
#include <iostream>
using namespace std;

int main() {
    int score = 85;
    
    // Nested if approach
    cout << "Nested if approach:" << endl;
    if (score >= 60) {
        cout << "Passed" << endl;
        
        if (score >= 90) {
            cout << "Grade A" << endl;
        } else if (score >= 80) {
            cout << "Grade B" << endl;
        } else if (score >= 70) {
            cout << "Grade C" << endl;
        } else {
            cout << "Grade D" << endl;
        }
    } else {
        cout << "Failed" << endl;
    }
    
    // else-if ladder approach (cleaner for this case)
    cout << "\nelse-if ladder approach:" << endl;
    if (score >= 90) {
        cout << "Grade A" << endl;
    } else if (score >= 80) {
        cout << "Grade B" << endl;
    } else if (score >= 70) {
        cout << "Grade C" << endl;
    } else if (score >= 60) {
        cout << "Grade D" << endl;
    } else {
        cout << "Failed" << endl;
    }
    
    return 0;
}
```

## Quick Reference

| Pattern | Description |
|---------|-------------|
| `if (c1) { if (c2) { } }` | Check c2 only if c1 true |
| `if (c1) { if (c2) { } else { } }` | Inner if-else |
| `if (c1) { } else { if (c2) { } }` | Else with nested if |
| `if (c1 && c2) { }` | Logical alternative to nested if |

## Summary

- **Nested if** means if inside another if
- Use for multi-level decision making
- Inner if only checked if outer condition is true
- Can nest if inside if, else, or else-if
- Braces `{}` are essential for clarity
- Avoid too many nesting levels (max 3-4)
- Consider logical operators as cleaner alternative
- Watch out for dangling else problem
- Always handle both true and false cases
- Indent properly to show structure

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    int condition1, condition2;
    
    cout << "Enter two values: ";
    cin >> condition1 >> condition2;
    
    if (condition1 > 0) {
        cout << "First condition met." << endl;
        
        if (condition2 > 0) {
            cout << "Both conditions met!" << endl;
        } else {
            cout << "Only first condition met." << endl;
        }
    } else {
        cout << "First condition not met." << endl;
        
        if (condition2 > 0) {
            cout << "Only second condition met." << endl;
        } else {
            cout << "No conditions met." << endl;
        }
    }
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*