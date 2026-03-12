# 19 - Increment and Decrement Operators (++, --) in C++

## What are Increment/Decrement Operators?
These operators provide a convenient way to add 1 to (increment) or subtract 1 from (decrement) a variable.

## The Two Operators

| Operator | Name | Effect |
|----------|------|--------|
| `++` | Increment | Adds 1 to the variable |
| `--` | Decrement | Subtracts 1 from the variable |

## Basic Syntax

```cpp
int x = 5;
x++;  // x becomes 6
x--;  // x becomes 5 again
```

## Simple Examples

```cpp
#include <iostream>
using namespace std;

int main() {
    int count = 10;
    
    cout << "Initial count: " << count << endl;
    
    count++;  // Increment
    cout << "After count++: " << count << endl;  // 11
    
    count--;  // Decrement
    cout << "After count--: " << count << endl;  // 10
    
    return 0;
}
```

## Prefix vs Postfix

There are two ways to use these operators: **prefix** and **postfix**.

### Prefix (++x, --x)
- Increments/decrements first, then returns the new value

### Postfix (x++, x--)
- Returns the old value first, then increments/decrements

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5;
    int b = 5;
    
    // Prefix increment
    cout << "Prefix ++a:" << endl;
    cout << "Before: a = " << a << endl;
    cout << "++a returns: " << ++a << endl;  // Returns 6
    cout << "After: a = " << a << endl;      // a is 6
    
    cout << "\n";
    
    // Postfix increment
    cout << "Postfix b++:" << endl;
    cout << "Before: b = " << b << endl;
    cout << "b++ returns: " << b++ << endl;  // Returns 5 (old value)
    cout << "After: b = " << b << endl;      // b is now 6
    
    return 0;
}
```

## Prefix vs Postfix Comparison Table

| Operation | What it does | Returns |
|-----------|--------------|---------|
| `++x` | Increment x, then use new value | New value |
| `x++` | Use current value, then increment | Old value |
| `--x` | Decrement x, then use new value | New value |
| `x--` | Use current value, then decrement | Old value |

## More Examples of Prefix vs Postfix

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5;
    int y = 5;
    
    // Using in expressions
    int result1 = ++x * 2;  // x becomes 6, then 6 * 2 = 12
    int result2 = y++ * 2;  // 5 * 2 = 10, then y becomes 6
    
    cout << "++x * 2 = " << result1 << ", x = " << x << endl;
    cout << "y++ * 2 = " << result2 << ", y = " << y << endl;
    
    return 0;
}
```

## Using in Loops

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Counting up with postfix:" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    
    cout << "\n\nCounting down with prefix:" << endl;
    for (int i = 5; i >= 1; --i) {
        cout << i << " ";
    }
    
    return 0;
}
```

## Practical Examples

### Example 1: Counter Program
```cpp
#include <iostream>
using namespace std;

int main() {
    int counter = 0;
    char choice;
    
    do {
        cout << "\nCurrent count: " << counter << endl;
        cout << "1. Increment" << endl;
        cout << "2. Decrement" << endl;
        cout << "3. Reset" << endl;
        cout << "4. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case '1':
                counter++;  // Increment
                cout << "Count increased!" << endl;
                break;
            case '2':
                counter--;  // Decrement
                cout << "Count decreased!" << endl;
                break;
            case '3':
                counter = 0;
                cout << "Count reset!" << endl;
                break;
        }
    } while (choice != '4');
    
    return 0;
}
```

### Example 2: Array Element Access
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int index = 0;
    
    cout << "Accessing array elements:" << endl;
    
    // Postfix - use current index, then move to next
    cout << "numbers[index++] = " << numbers[index++] << endl;  // 10
    cout << "numbers[index++] = " << numbers[index++] << endl;  // 20
    cout << "numbers[index++] = " << numbers[index++] << endl;  // 30
    
    cout << "Final index: " << index << endl;  // 3
    
    // Reset
    index = 4;
    cout << "\nGoing backwards:" << endl;
    cout << "numbers[index--] = " << numbers[index--] << endl;  // 50
    cout << "numbers[index--] = " << numbers[index--] << endl;  // 40
    cout << "numbers[index--] = " << numbers[index--] << endl;  // 30
    
    return 0;
}
```

### Example 3: String Character Counter
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text;
    cout << "Enter some text: ";
    getline(cin, text);
    
    int vowelCount = 0;
    int consonantCount = 0;
    int otherCount = 0;
    int i = 0;
    
    while (i < text.length()) {
        char ch = tolower(text[i]);
        
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            vowelCount++;  // Found a vowel
        } else if (ch >= 'a' && ch <= 'z') {
            consonantCount++;  // Found a consonant
        } else if (ch != ' ') {
            otherCount++;  // Found other character
        }
        
        i++;  // Move to next character
    }
    
    cout << "Vowels: " << vowelCount << endl;
    cout << "Consonants: " << consonantCount << endl;
    cout << "Other: " << otherCount << endl;
    
    return 0;
}
```

### Example 4: Simple ATM Withdrawal Counter
```cpp
#include <iostream>
using namespace std;

int main() {
    int balance = 1000;
    int withdrawals = 0;
    int amount;
    char choice;
    
    do {
        cout << "\nBalance: $" << balance << endl;
        cout << "Withdrawals today: " << withdrawals << endl;
        cout << "Enter amount to withdraw: $";
        cin >> amount;
        
        if (amount <= balance && amount > 0) {
            balance -= amount;
            withdrawals++;  // Count this withdrawal
            
            cout << "Withdrawn: $" << amount << endl;
            cout << "Remaining: $" << balance << endl;
        } else {
            cout << "Invalid amount!" << endl;
        }
        
        cout << "Another withdrawal? (y/n): ";
        cin >> choice;
        
    } while (choice == 'y' || choice == 'Y');
    
    cout << "\nTotal withdrawals today: " << withdrawals << endl;
    
    return 0;
}
```

### Example 5: Game Score Tracker
```cpp
#include <iostream>
using namespace std;

int main() {
    int score = 0;
    int level = 1;
    int lives = 3;
    
    cout << "Game Started!" << endl;
    cout << "Level: " << level << ", Score: " << score << ", Lives: " << lives << endl;
    
    // Level 1 completed
    score += 100;
    level++;  // Move to next level
    cout << "\nLevel 1 completed!" << endl;
    cout << "Level: " << level << ", Score: " << score << endl;
    
    // Level 2 completed with bonus
    score += 150;
    level++;
    cout << "\nLevel 2 completed with bonus!" << endl;
    cout << "Level: " << level << ", Score: " << score << endl;
    
    // Hit by enemy
    lives--;  // Lose a life
    cout << "\nHit by enemy!" << endl;
    cout << "Lives remaining: " << lives << endl;
    
    // Game over when lives reach 0
    if (--lives == 0) {  // Prefix decrement in condition
        cout << "\nGame Over!" << endl;
    }
    
    return 0;
}
```

## Using in Expressions

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 5, c = 5, d = 5;
    
    // Complex expressions
    int result1 = ++a + b++;  // (++a) + (b++) = 6 + 5 = 11
    int result2 = --c + d--;  // (--c) + (d--) = 4 + 5 = 9
    
    cout << "++a + b++ = " << result1 << endl;
    cout << "a = " << a << ", b = " << b << endl;  // a=6, b=6
    
    cout << "\n--c + d-- = " << result2 << endl;
    cout << "c = " << c << ", d = " << d << endl;  // c=4, d=4
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Using on Constants
```cpp
// Wrong
// 5++;  // ❌ Error! Can't increment constant

// Correct
int x = 5;
x++;
```

### Mistake 2: Multiple Increments in One Statement
```cpp
int x = 5;

// Wrong - undefined behavior
int y = ++x + x++;  // Don't do this!

// Correct
x++;
int y = x + x;
```

### Mistake 3: Confusing Prefix and Postfix
```cpp
int x = 5;
int y = 5;

cout << x++ << endl;  // Prints 5 (then x becomes 6)
cout << ++y << endl;  // Prints 6

// If you just want to increment, either works:
x++;  // or ++x;
```

### Mistake 4: Using on Expressions
```cpp
// Wrong
// (x + y)++;  // ❌ Error! Can't increment expression

// Correct
int result = x + y;
result++;
```

### Mistake 5: Forgetting They Modify the Variable
```cpp
int x = 5;
int y = x++;  // y = 5, x = 6

// If you didn't want to modify x:
int z = x + 1;  // z = 6, x still 5
```

## Performance Considerations

```cpp
// For simple integers, prefix and postfix are similar
int x = 5;
++x;  // Same as x++ for simple increment

// For complex objects (like iterators), prefix can be faster
// ++it;  // Usually faster than it++;
```

## Using with Pointers

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;  // Point to first element
    
    cout << "*ptr++ = " << *ptr++ << endl;  // Gets 10, then moves to next
    cout << "*ptr = " << *ptr << endl;      // 20
    
    cout << "\n*++ptr = " << *++ptr << endl;  // Moves first, then gets 30
    cout << "*ptr = " << *ptr << endl;        // 30
    
    return 0;
}
```

## Quick Reference Table

| Operation | What it does | Example (x=5) | Result |
|-----------|--------------|---------------|--------|
| `x++` | Use x, then increment | `y = x++` | y=5, x=6 |
| `++x` | Increment x, then use | `y = ++x` | y=6, x=6 |
| `x--` | Use x, then decrement | `y = x--` | y=5, x=4 |
| `--x` | Decrement x, then use | `y = --x` | y=4, x=4 |

## Summary

- **++** increments a variable by 1
- **--** decrements a variable by 1
- **Prefix (++x)** increments first, then returns new value
- **Postfix (x++)** returns old value, then increments
- Use in loops for counting
- Use in array/pointer navigation
- Can't increment constants or expressions
- Avoid multiple increments in same expression
- Both operators modify the original variable
- Essential for many programming patterns

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    int counter = 0;
    
    // Simple increment/decrement
    cout << "Initial: " << counter << endl;
    
    counter++;
    cout << "After counter++: " << counter << endl;
    
    counter--;
    cout << "After counter--: " << counter << endl;
    
    // Prefix vs Postfix demo
    int a = 5, b = 5;
    
    cout << "\nPrefix ++a: " << ++a << ", a is now: " << a << endl;
    cout << "Postfix b++: " << b++ << ", b is now: " << b << endl;
    
    // Loop example
    cout << "\nCounting to 5:" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    
    return 0;
}
```
  *This documentation belongs to https://github.com/InterCentury*