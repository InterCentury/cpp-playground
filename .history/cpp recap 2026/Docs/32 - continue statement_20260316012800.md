# 32 - continue Statement in C++

## What is continue Statement?
The `continue` statement skips the rest of the current loop iteration and jumps to the next iteration. Unlike `break`, it doesn't exit the loop—it just skips to the next cycle.

## Basic Syntax

```cpp
continue;
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 5; i++) {
        if (i == 3) {
            cout << "Skipping " << i << endl;
            continue;  // Skip rest of loop when i is 3
        }
        cout << "i = " << i << endl;
    }
    
    cout << "Loop finished!" << endl;
    
    return 0;
}
```
Output:
```
i = 1
i = 2
Skipping 3
i = 4
i = 5
Loop finished!
```

## continue in Different Loops

### continue in for Loop
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "continue in for loop:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        cout << i << " ";  // Only prints odd numbers
    }
    cout << "\nLoop ended" << endl;
    
    return 0;
}
```

### continue in while Loop
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "continue in while loop:" << endl;
    int i = 0;
    
    while (i < 10) {
        i++;
        if (i % 3 == 0) {
            continue;  // Skip multiples of 3
        }
        cout << i << " ";
    }
    cout << "\nLoop ended" << endl;
    
    return 0;
}
```

### continue in do-while Loop
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "continue in do-while loop:" << endl;
    int i = 0;
    
    do {
        i++;
        if (i == 5 || i == 7) {
            cout << "Skipping " << i << endl;
            continue;
        }
        cout << i << " ";
    } while (i < 10);
    cout << "\nLoop ended" << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Print Even Numbers
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Even numbers from 1 to 20:" << endl;
    
    for (int i = 1; i <= 20; i++) {
        if (i % 2 != 0) {
            continue;  // Skip odd numbers
        }
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 2: Skip Multiples of 3 and 5
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Numbers 1-30 not divisible by 3 or 5:" << endl;
    
    for (int i = 1; i <= 30; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            continue;  // Skip multiples of 3 or 5
        }
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 3: Input Validation with Continue
```cpp
#include <iostream>
using namespace std;

int main() {
    int number;
    int sum = 0;
    int count = 0;
    
    cout << "Enter 5 positive numbers:" << endl;
    
    while (count < 5) {
        cout << "Number " << count + 1 << ": ";
        cin >> number;
        
        if (number <= 0) {
            cout << "Invalid! Enter positive number only." << endl;
            continue;  // Skip to next iteration without counting
        }
        
        sum += number;
        count++;  // Only increments when valid
    }
    
    cout << "Sum of valid numbers: " << sum << endl;
    
    return 0;
}
```

### Example 4: Process Only Alphabetic Characters
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string text;
    
    cout << "Enter a string: ";
    getline(cin, text);
    
    cout << "Alphabetic characters only: ";
    for (int i = 0; i < text.length(); i++) {
        if (!isalpha(text[i])) {
            continue;  // Skip non-alphabetic characters
        }
        cout << text[i];
    }
    cout << endl;
    
    // Count vowels using continue
    int vowelCount = 0;
    for (int i = 0; i < text.length(); i++) {
        char ch = tolower(text[i]);
        if (ch != 'a' && ch != 'e' && ch != 'i' && ch != 'o' && ch != 'u') {
            continue;  // Skip consonants
        }
        vowelCount++;
    }
    cout << "Vowel count: " << vowelCount << endl;
    
    return 0;
}
```

### Example 5: Skip Invalid Array Elements
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, -5, 20, -8, 30, -2, 40, -1, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int sum = 0;
    int validCount = 0;
    
    cout << "Processing array:" << endl;
    
    for (int i = 0; i < size; i++) {
        if (numbers[i] < 0) {
            cout << "Skipping negative: " << numbers[i] << endl;
            continue;  // Skip negative numbers
        }
        
        sum += numbers[i];
        validCount++;
        cout << "Added: " << numbers[i] << " (Running sum: " << sum << ")" << endl;
    }
    
    cout << "\nSum of positive numbers: " << sum << endl;
    cout << "Count of positive numbers: " << validCount << endl;
    
    return 0;
}
```

## continue in Nested Loops

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "continue in nested loops:" << endl;
    
    for (int i = 1; i <= 3; i++) {
        cout << "Outer i = " << i << ": ";
        
        for (int j = 1; j <= 5; j++) {
            if (j == 3) {
                cout << "skip ";
                continue;  // Skip j=3, continue inner loop
            }
            cout << j << " ";
        }
        
        cout << endl;
    }
    
    return 0;
}
```
Output:
```
Outer i = 1: 1 2 skip 4 5 
Outer i = 2: 1 2 skip 4 5 
Outer i = 3: 1 2 skip 4 5 
```

### Continue in Outer Loop (using flag)
```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 5; i++) {
        if (i == 3) {
            cout << "Skipping outer iteration " << i << endl;
            continue;  // Skip rest of outer loop when i=3
        }
        
        for (int j = 1; j <= 3; j++) {
            cout << "(" << i << "," << j << ") ";
        }
        cout << endl;
    }
    
    return 0;
}
```

## continue vs break

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Using continue (skip 3):" << endl;
    for (int i = 1; i <= 5; i++) {
        if (i == 3) {
            cout << "Skipping..." << endl;
            continue;  // Skip iteration
        }
        cout << i << " ";
    }
    
    cout << "\n\nUsing break (stop at 3):" << endl;
    for (int i = 1; i <= 5; i++) {
        if (i == 3) {
            cout << "Breaking..." << endl;
            break;  // Exit loop
        }
        cout << i << " ";
    }
    
    return 0;
}
```
Output:
```
Using continue (skip 3):
1 2 Skipping...
4 5 

Using break (stop at 3):
1 2 Breaking...
```

## Common Mistakes

### Mistake 1: Continue Outside Loop
```cpp
// Wrong
if (x > 5) {
    continue;  // Error! continue not in loop
}

// Correct
while (condition) {
    if (x > 5) {
        continue;  // OK
    }
}
```

### Mistake 2: Forgetting Increment in while
```cpp
int i = 1;

// Wrong - infinite loop
while (i <= 10) {
    if (i % 2 == 0) {
        continue;  // Skip even numbers
    }
    cout << i << " ";
    i++;  // This never runs for even numbers!
}

// Correct
while (i <= 10) {
    if (i % 2 == 0) {
        i++;  // Increment before continue
        continue;
    }
    cout << i << " ";
    i++;
}
```

### Mistake 3: Continue in switch (Not Allowed)
```cpp
int x = 2;

// Wrong
switch (x) {
    case 1:
        cout << "One" << endl;
        continue;  // Error! continue not in loop
    case 2:
        cout << "Two" << endl;
        break;
}

// continue only works in loops, not switch
```

### Mistake 4: Unreachable Code After Continue
```cpp
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        continue;
        cout << "This never prints!" << endl;  // Unreachable
    }
    cout << i << " ";
}
```

### Mistake 5: Continue in do-while Without Care
```cpp
int i = 0;

do {
    i++;
    if (i == 3) {
        continue;  // OK, but make sure condition still checked
    }
    cout << i << " ";
} while (i < 5);
// Works fine because i still increments
```

## continue with Different Loop Types

### In for Loop (Update still happens)
```cpp
for (int i = 1; i <= 5; i++) {
    if (i == 3) continue;  // i still becomes 4 after this
    cout << i << " ";
}
// Output: 1 2 4 5
```

### In while Loop (Must update manually)
```cpp
int i = 1;
while (i <= 5) {
    if (i == 3) {
        i++;  // Must increment before continue
        continue;
    }
    cout << i << " ";
    i++;
}
```

### In do-while Loop
```cpp
int i = 1;
do {
    if (i == 3) {
        i++;  // Increment before continue
        continue;
    }
    cout << i << " ";
    i++;
} while (i <= 5);
```

## Practical Use Cases

### Use Case 1: Filtering Data
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> data = {10, 0, 25, 0, 30, 0, 45};
    int sum = 0;
    
    for (int value : data) {
        if (value == 0) {
            continue;  // Skip zeros
        }
        sum += value;
        cout << "Processing: " << value << endl;
    }
    
    cout << "Sum (excluding zeros): " << sum << endl;
    
    return 0;
}
```

### Use Case 2: Skip Weekends in Date Processing
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Business days in January (first 15 days):" << endl;
    
    for (int day = 1; day <= 15; day++) {
        // Assume day 1 is Monday (1=Mon, 6=Sat, 7=Sun)
        int dayOfWeek = (day % 7);
        
        if (dayOfWeek == 6 || dayOfWeek == 0) {
            cout << "Day " << day << " is weekend - skipping" << endl;
            continue;  // Skip weekends
        }
        
        cout << "Day " << day << " - work day" << endl;
    }
    
    return 0;
}
```

### Use Case 3: Skip Invalid Input in Processing
```cpp
#include <iostream>
using namespace std;

int main() {
    int scores[5];
    int validCount = 0;
    
    cout << "Enter 5 scores (0-100):" << endl;
    
    for (int i = 0; i < 5; i++) {
        cout << "Score " << i+1 << ": ";
        cin >> scores[i];
        
        if (scores[i] < 0 || scores[i] > 100) {
            cout << "Invalid score, try again!" << endl;
            i--;  // Redo this iteration
            continue;
        }
        
        validCount++;
    }
    
    cout << "Valid scores entered: " << validCount << endl;
    
    return 0;
}
```

## continue vs break vs return

| Statement | Effect |
|-----------|--------|
| `continue` | Skips to next iteration |
| `break` | Exits current loop |
| `return` | Exits entire function |

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 5; i++) {
        if (i == 2) {
            cout << "Continue at 2" << endl;
            continue;  // Skip rest, go to next iteration
        }
        if (i == 4) {
            cout << "Break at 4" << endl;
            break;     // Exit loop
        }
        cout << "Processing " << i << endl;
    }
    cout << "Loop ended" << endl;
    
    return 0;  // Exit function
}
```

## Quick Reference

| Context | Effect of continue |
|---------|-------------------|
| `for` loop | Skips to update expression, then condition |
| `while` loop | Skips to condition check |
| `do-while` loop | Skips to condition check |
| Nested loops | Only affects innermost loop |

## Summary

- **continue** skips the rest of current iteration
- Moves to next iteration without exiting loop
- In for loops, update expression still runs
- In while loops, must update variables before continue
- Useful for filtering and skipping unwanted cases
- Cannot be used outside loops
- Makes code cleaner than nested ifs
- Different from break (exit) and return (exit function)
- Watch for infinite loops in while/do-while
- Essential for input validation patterns

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    // Skip even numbers
    cout << "Odd numbers from 1 to 10:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        cout << i << " ";
    }
    cout << endl;
    
    // Skip vowels in string
    string text = "Hello World";
    cout << "\nConsonants in \"" << text << "\": ";
    for (char ch : text) {
        ch = tolower(ch);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            continue;  // Skip vowels
        }
        cout << ch;
    }
    cout << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*