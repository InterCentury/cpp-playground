# 10 - Character Type (char) in C++

## What is char?
`char` is a data type used to store single characters like letters, digits, or symbols. Examples: 'A', 'b', '5', '@', '\n'

## Basic Syntax

```cpp
char letter = 'A';
char digit = '7';
char symbol = '$';
char newline = '\n';
```

## Important: Single Quotes vs Double Quotes

```cpp
// ✅ Correct - single quotes for char
char grade = 'A';

// ❌ Wrong - double quotes are for strings
char grade = "A";  // Error!

// ✅ Correct for strings
string name = "John";
```

## Declaring and Initializing char

### Different Ways
```cpp
#include <iostream>
using namespace std;

int main() {
    // Direct initialization
    char c1 = 'X';
    char c2('Y');           // Constructor style
    char c3{'Z'};           // Uniform initialization (C++11)
    char c4 = {};           // Zero initialization (null character)
    
    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    cout << "c3: " << c3 << endl;
    cout << "c4: [" << c4 << "]" << endl;  // Empty
    
    return 0;
}
```

## Characters are Actually Numbers

Every character has a numeric value (ASCII code).

```cpp
#include <iostream>
using namespace std;

int main() {
    char ch = 'A';
    
    cout << "Character: " << ch << endl;
    cout << "ASCII value: " << (int)ch << endl;  // 65
    
    // You can do math with characters!
    ch = ch + 1;
    cout << "Next character: " << ch << endl;     // 'B'
    cout << "ASCII value: " << (int)ch << endl;   // 66
    
    return 0;
}
```

## ASCII Table (Common Values)

| Character | ASCII Value |
|-----------|-------------|
| 'A' - 'Z' | 65 - 90 |
| 'a' - 'z' | 97 - 122 |
| '0' - '9' | 48 - 57 |
| Space | 32 |
| Newline (\n) | 10 |
| Tab (\t) | 9 |
| Null (\0) | 0 |

## Working with ASCII Values

```cpp
#include <iostream>
using namespace std;

int main() {
    // Using ASCII values directly
    char ch1 = 65;     // 'A'
    char ch2 = 97;     // 'a'
    char ch3 = 48;     // '0'
    
    cout << "ch1 (65): " << ch1 << endl;
    cout << "ch2 (97): " << ch2 << endl;
    cout << "ch3 (48): " << ch3 << endl;
    
    // Converting case
    char upper = 'B';
    char lower = upper + 32;  // 'b'
    cout << "Upper: " << upper << ", Lower: " << lower << endl;
    
    return 0;
}
```

## Character Operations

### Checking Character Types
```cpp
#include <iostream>
#include <cctype>  // for character functions
using namespace std;

int main() {
    char ch = '5';
    
    cout << "is digit? " << isdigit(ch) << endl;      // 1 (true)
    cout << "is letter? " << isalpha(ch) << endl;     // 0 (false)
    cout << "is alnum? " << isalnum(ch) << endl;      // 1 (true)
    
    ch = 'A';
    cout << "is upper? " << isupper(ch) << endl;      // 1 (true)
    cout << "is lower? " << islower(ch) << endl;      // 0 (false)
    cout << "to lower: " << (char)tolower(ch) << endl; // 'a'
    
    ch = 'z';
    cout << "to upper: " << (char)toupper(ch) << endl; // 'Z'
    
    return 0;
}
```

### Character Arithmetic
```cpp
char ch = 'C';

ch--;                    // 'B'
ch++;                    // 'C' again
ch = ch + 5;            // 'H'
ch = ch - 2;            // 'F'

cout << "Result: " << ch << endl;
```

## Escape Sequences as Characters

```cpp
char newline = '\n';
char tab = '\t';
char backslash = '\\';
char singleQuote = '\'';
char doubleQuote = '\"';
char null = '\0';

cout << "First line" << newline << "Second line" << endl;
cout << "Column1" << tab << "Column2" << endl;
```

## Practical Examples

### Example 1: Vowel Checker
```cpp
#include <iostream>
using namespace std;

int main() {
    char ch;
    
    cout << "Enter a letter: ";
    cin >> ch;
    
    // Convert to uppercase for easier checking
    ch = toupper(ch);
    
    if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
        cout << ch << " is a vowel" << endl;
    } else {
        cout << ch << " is a consonant" << endl;
    }
    
    return 0;
}
```

### Example 2: Case Converter
```cpp
#include <iostream>
using namespace std;

int main() {
    char ch;
    
    cout << "Enter a character: ";
    cin >> ch;
    
    if (isupper(ch)) {
        cout << ch << " → " << (char)tolower(ch) << endl;
    } else if (islower(ch)) {
        cout << ch << " → " << (char)toupper(ch) << endl;
    } else {
        cout << "Not a letter" << endl;
    }
    
    return 0;
}
```

### Example 3: Digit to Number
```cpp
#include <iostream>
using namespace std;

int main() {
    char digitChar;
    
    cout << "Enter a digit (0-9): ";
    cin >> digitChar;
    
    if (isdigit(digitChar)) {
        int number = digitChar - '0';  // Convert char to int
        cout << "As character: " << digitChar << endl;
        cout << "As number: " << number << endl;
        cout << "Double: " << number * 2 << endl;
    } else {
        cout << "Not a digit" << endl;
    }
    
    return 0;
}
```

### Example 4: Simple Password Check
```cpp
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char firstLetter;
    
    cout << "Enter first letter of password: ";
    cin >> firstLetter;
    
    if (isupper(firstLetter)) {
        cout << "✓ Good: starts with uppercase" << endl;
    } else {
        cout << "✗ Should start with uppercase" << endl;
    }
    
    return 0;
}
```

### Example 5: Alphabet Loop
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Uppercase letters: ";
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        cout << ch << " ";
    }
    
    cout << "\nLowercase letters: ";
    for (char ch = 'a'; ch <= 'z'; ch++) {
        cout << ch << " ";
    }
    
    cout << "\nDigits: ";
    for (char ch = '0'; ch <= '9'; ch++) {
        cout << ch << " ";
    }
    
    return 0;
}
```

## Char Arrays vs Strings

```cpp
// Char array (C-style string)
char name1[] = "John";        // Array of 5 chars: J o h n \0
char name2[5] = "John";       // Explicit size

// C++ string (easier)
string name3 = "John";

// Char array access
cout << "First letter: " << name1[0] << endl;  // 'J'

// Modify char array
name1[0] = 'M';  // Now "Mohn"
```

## Common Character Functions (from <cctype>)

| Function | Description | Example |
|----------|-------------|---------|
| `isalpha(c)` | Checks if letter | `isalpha('A')` → true |
| `isdigit(c)` | Checks if digit | `isdigit('5')` → true |
| `isalnum(c)` | Checks if letter or digit | `isalnum('@')` → false |
| `islower(c)` | Checks if lowercase | `islower('a')` → true |
| `isupper(c)` | Checks if uppercase | `isupper('A')` → true |
| `isspace(c)` | Checks if whitespace | `isspace(' ')` → true |
| `tolower(c)` | Converts to lowercase | `tolower('Z')` → 'z' |
| `toupper(c)` | Converts to uppercase | `toupper('z')` → 'Z' |

## Char Input/Output

### Single Character Input
```cpp
char ch;
cout << "Enter a character: ";
cin >> ch;                    // Reads one character
cout << "You entered: " << ch;
```

### Problem with cin and characters
```cpp
char ch1, ch2;
cout << "Enter two characters: ";
cin >> ch1 >> ch2;  // Works fine if user types "A B"
```

### Using cin.get() for characters including whitespace
```cpp
char ch;
cout << "Enter a character (including space): ";
ch = cin.get();               // Reads ANY character
cout << "You entered: [" << ch << "]";
```

## Common Mistakes

### Mistake 1: Using Double Quotes
```cpp
// Wrong
char grade = "A";

// Correct
char grade = 'A';
```

### Mistake 2: Multiple Characters
```cpp
// Wrong
char word = 'Hello';  // Too many characters

// Correct
char letter = 'H';
string word = "Hello";
```

### Mistake 3: Forgetting Single Quotes
```cpp
// Wrong - treats as variable name
char ch = A;  // What is A?

// Correct
char ch = 'A';
```

### Mistake 4: Wrong ASCII Assumptions
```cpp
// Wrong - assumes 'A' is 1
char ch = 1;  // This is SOH (control char), not 'A'

// Correct
char ch = 'A';
```

### Mistake 5: Not Handling Case
```cpp
// Wrong - only works for uppercase
if (ch >= 'A' && ch <= 'Z') { }

// Better
if (isalpha(ch)) { }
```

## Best Practices

### ✅ Do This
```cpp
// Use meaningful names
char grade = 'A';
char userChoice = 'Y';

// Use cctype functions
if (isalpha(ch)) { }

// Convert case properly
char upper = toupper(ch);

// Convert digit char to int
int num = digitChar - '0';

// Initialize properly
char ch = '\0';  // Null character
```

### ❌ Avoid This
```cpp
// Don't use magic numbers
if (ch == 65) { }  // What's 65?

// Don't assume ASCII ordering for non-letters
if (ch >= 'a' && ch <= 'z') { }  // Works but isalpha is better

// Don't forget to cast
cout << (char)65;  // Need cast to print as character
```

## Quick Reference Table

| Operation | Code | Result |
|-----------|------|--------|
| Declare char | `char c = 'A';` | c = 'A' |
| Get ASCII | `(int)c` | 65 |
| Next letter | `c + 1` | 66 ('B') |
| Check digit | `isdigit(c)` | false |
| Check letter | `isalpha(c)` | true |
| To uppercase | `toupper('a')` | 'A' |
| To lowercase | `tolower('Z')` | 'z' |
| Char to int | `digit - '0'` | 0-9 |
| Int to char | `'0' + num` | '0'-'9' |

## Summary

- **char** stores single characters using single quotes: `'A'`
- Characters have ASCII numeric values (65 for 'A')
- Use `<cctype>` functions for character testing/conversion
- Char arithmetic works: `'A' + 1 = 'B'`
- Escape sequences like `'\n'` are also chars
- Convert digit char to int: `digit - '0'`
- Convert int to digit char: `'0' + num`
- Use `cin.get()` to read whitespace characters
- Never use double quotes for single characters
- Char arrays are C-style strings (end with `'\0'`)

## Basic Template
```cpp
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    // Declare and initialize
    char ch = 'A';
    
    // Input
    cout << "Enter a character: ";
    cin >> ch;
    
    // Check type
    if (isalpha(ch)) {
        cout << ch << " is a letter" << endl;
        cout << "Uppercase: " << (char)toupper(ch) << endl;
        cout << "Lowercase: " << (char)tolower(ch) << endl;
    } else if (isdigit(ch)) {
        cout << ch << " is a digit" << endl;
        cout << "As number: " << (ch - '0') << endl;
    } else {
        cout << ch << " is a special character" << endl;
    }
    
    return 0;
}
```

*This documentation belongs to https://github.com/InterCentury*