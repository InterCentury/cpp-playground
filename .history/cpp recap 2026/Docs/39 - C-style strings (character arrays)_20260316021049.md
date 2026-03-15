# 39 - C-style Strings (Character Arrays) in C++

## What are C-style Strings?
C-style strings are arrays of characters terminated by a null character (`\0`). They come from the C language and are still used in C++ for low-level string operations.

## Basic Syntax

```cpp
// Declaration as character array
char str1[10];  // Can hold up to 9 characters + null terminator

// Declaration with initialization
char str2[] = "Hello";           // Size automatically 6 (H e l l o \0)
char str3[10] = "Hello";         // Fixed size, uses first 6 positions
char str4[10] = {'H','e','l','l','o','\0'};  // Character by character
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

int main() {
    char greeting[] = "Hello World";
    
    cout << "String: " << greeting << endl;
    cout << "Size of array: " << sizeof(greeting) << " bytes" << endl;
    cout << "Characters: ";
    
    for (int i = 0; greeting[i] != '\0'; i++) {
        cout << greeting[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Different Ways to Initialize

### Method 1: String Literal
```cpp
char str1[] = "Hello";           // Most common
char str2[10] = "Hello";         // With specified size
```

### Method 2: Character Array
```cpp
char str3[] = {'H', 'e', 'l', 'l', 'o', '\0'};  // Explicit null terminator
```

### Method 3: With Specified Size
```cpp
char str4[10] = "Hello";  // Remaining positions set to '\0'
```

### Method 4: Empty String
```cpp
char empty1[] = "";        // Contains only '\0'
char empty2[10] = "";      // All 10 chars set to '\0'
```

## Null Terminator Importance

```cpp
#include <iostream>
using namespace std;

int main() {
    // With null terminator (proper string)
    char proper[] = "Hello";
    
    // Without null terminator (just character array)
    char improper[5] = {'H', 'e', 'l', 'l', 'o'};
    
    cout << "Proper string: " << proper << endl;      // Hello
    cout << "Improper array: " << improper << endl;    // Hello + garbage
    
    return 0;
}
```

## String Input

### Using cin (stops at space)
```cpp
#include <iostream>
using namespace std;

int main() {
    char name[50];
    
    cout << "Enter your name: ";
    cin >> name;  // Reads only first word
    
    cout << "Hello, " << name << endl;
    
    return 0;
}
```

### Using cin.getline() (reads full line)
```cpp
#include <iostream>
using namespace std;

int main() {
    char name[50];
    
    cout << "Enter your full name: ";
    cin.getline(name, 50);  // Reads up to 49 characters
    
    cout << "Hello, " << name << endl;
    
    return 0;
}
```

### Using cin.get()
```cpp
#include <iostream>
using namespace std;

int main() {
    char ch;
    char str[100];
    int i = 0;
    
    cout << "Enter a string (end with Enter): ";
    
    // Read character by character
    cin.get(ch);
    while (ch != '\n' && i < 99) {
        str[i] = ch;
        i++;
        cin.get(ch);
    }
    str[i] = '\0';  // Add null terminator
    
    cout << "You entered: " << str << endl;
    
    return 0;
}
```

## String Output

### Using cout
```cpp
char message[] = "Hello World";
cout << message << endl;                    // Hello World
cout << "Character at index 1: " << message[1] << endl;  // e
```

### Character by Character
```cpp
char str[] = "Hello";

for (int i = 0; str[i] != '\0'; i++) {
    cout << str[i] << " ";
}
cout << endl;  // H e l l o
```

## Practical Examples

### Example 1: String Length (without strlen)
```cpp
#include <iostream>
using namespace std;

int main() {
    char str[] = "Hello World";
    int length = 0;
    
    while (str[length] != '\0') {
        length++;
    }
    
    cout << "String: \"" << str << "\"" << endl;
    cout << "Length: " << length << endl;
    
    return 0;
}
```

### Example 2: String Copy (without strcpy)
```cpp
#include <iostream>
using namespace std;

int main() {
    char source[] = "Copy me!";
    char destination[20];
    int i = 0;
    
    // Copy until null terminator
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';  // Add null terminator
    
    cout << "Source: " << source << endl;
    cout << "Destination: " << destination << endl;
    
    return 0;
}
```

### Example 3: String Concatenation (without strcat)
```cpp
#include <iostream>
using namespace std;

int main() {
    char str1[50] = "Hello ";
    char str2[] = "World";
    int i = 0, j = 0;
    
    // Find end of first string
    while (str1[i] != '\0') {
        i++;
    }
    
    // Append second string
    while (str2[j] != '\0') {
        str1[i] = str2[j];
        i++;
        j++;
    }
    str1[i] = '\0';
    
    cout << "Concatenated: " << str1 << endl;
    
    return 0;
}
```

### Example 4: String Comparison (without strcmp)
```cpp
#include <iostream>
using namespace std;

int main() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";
    
    bool equal = true;
    int i = 0;
    
    // Compare str1 and str2
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            equal = false;
            break;
        }
        i++;
    }
    
    // Check if both ended at same time
    if (str1[i] != '\0' || str2[i] != '\0') {
        equal = false;
    }
    
    cout << "\"" << str1 << "\" and \"" << str2 << "\" are ";
    cout << (equal ? "equal" : "not equal") << endl;
    
    return 0;
}
```

### Example 5: String Reversal
```cpp
#include <iostream>
using namespace std;

int main() {
    char str[] = "Hello";
    int length = 0;
    
    // Find length
    while (str[length] != '\0') {
        length++;
    }
    
    cout << "Original: " << str << endl;
    
    // Reverse string
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
    
    cout << "Reversed: " << str << endl;
    
    return 0;
}
```

## Using C-string Functions (from <cstring>)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char str1[50] = "Hello";
    char str2[] = " World";
    char str3[50];
    
    // String length
    cout << "Length of str1: " << strlen(str1) << endl;
    
    // String copy
    strcpy(str3, str1);
    cout << "Copied string: " << str3 << endl;
    
    // String concatenation
    strcat(str1, str2);
    cout << "Concatenated: " << str1 << endl;
    
    // String comparison
    int result = strcmp(str1, str3);
    cout << "Comparison result: " << result << endl;
    
    // String searching
    char* pos = strchr(str1, 'o');
    if (pos) {
        cout << "Found 'o' at position: " << pos - str1 << endl;
    }
    
    return 0;
}
```

## Common C-string Functions

| Function | Description | Example |
|----------|-------------|---------|
| `strlen(s)` | Returns length of s | `len = strlen(str);` |
| `strcpy(dest, src)` | Copies src to dest | `strcpy(dest, src);` |
| `strncpy(dest, src, n)` | Copies n characters | `strncpy(dest, src, 5);` |
| `strcat(dest, src)` | Appends src to dest | `strcat(str, "!");` |
| `strncat(dest, src, n)` | Appends n characters | `strncat(str, src, 3);` |
| `strcmp(s1, s2)` | Compares strings | `if (strcmp(s1, s2) == 0)` |
| `strncmp(s1, s2, n)` | Compares first n chars | `strncmp(s1, s2, 3);` |
| `strchr(s, c)` | Finds first c in s | `char* p = strchr(str, 'a');` |
| `strstr(s1, s2)` | Finds s2 in s1 | `char* p = strstr(str, "lo");` |

## String Arrays (Array of C-strings)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    // Array of C-strings
    char names[5][20] = {
        "Alice",
        "Bob",
        "Charlie",
        "Diana",
        "Edward"
    };
    
    cout << "Names list:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << names[i] << endl;
    }
    
    // Find longest name
    int maxLen = 0;
    int maxIndex = 0;
    
    for (int i = 0; i < 5; i++) {
        int len = strlen(names[i]);
        if (len > maxLen) {
            maxLen = len;
            maxIndex = i;
        }
    }
    
    cout << "\nLongest name: " << names[maxIndex] 
         << " (" << maxLen << " characters)" << endl;
    
    return 0;
}
```

## Input with Buffer Overflow Protection

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char buffer[10];
    
    cout << "Enter text (max 9 characters): ";
    cin.getline(buffer, 10);
    
    cout << "You entered: " << buffer << endl;
    
    // Check if input was truncated
    if (cin.gcount() == 10 && buffer[9] != '\0') {
        cout << "Input was truncated!" << endl;
        cin.clear();
    }
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Forgetting Null Terminator
```cpp
// Wrong - no null terminator
char str[5] = {'H', 'e', 'l', 'l', 'o'};

// Correct
char str[] = "Hello";
// or
char str[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
```

### Mistake 2: Buffer Overflow
```cpp
char buffer[10];

// Wrong - writing beyond bounds
strcpy(buffer, "This is a very long string that exceeds buffer size");

// Correct
strncpy(buffer, "This is a very long string", 9);
buffer[9] = '\0';  // Ensure null termination
```

### Mistake 3: Using = to Copy Strings
```cpp
char str1[] = "Hello";
char str2[10];

// Wrong - doesn't copy content
str2 = str1;  // Error!

// Correct
strcpy(str2, str1);
```

### Mistake 4: Comparing with ==
```cpp
char str1[] = "Hello";
char str2[] = "Hello";

// Wrong - compares addresses, not content
if (str1 == str2) { }

// Correct - compares content
if (strcmp(str1, str2) == 0) { }
```

### Mistake 5: Not Checking Array Bounds
```cpp
char name[20];

cout << "Enter name: ";
cin >> name;  // If user enters more than 19 chars, buffer overflow!

// Better
cin.getline(name, 20);
```

## C-style vs C++ Strings

| Feature | C-style Strings | C++ Strings |
|---------|-----------------|-------------|
| Type | `char[]` | `string` |
| Header | `<cstring>` | `<string>` |
| Assignment | `strcpy()` | `=` operator |
| Comparison | `strcmp()` | `==`, `<`, etc. |
| Concatenation | `strcat()` | `+` operator |
| Length | `strlen()` | `.length()` |
| Bounds checking | No | Yes |
| Memory management | Manual | Automatic |

## Quick Reference

| Operation | C-style | C++ string |
|-----------|---------|------------|
| Declare | `char s[100];` | `string s;` |
| Initialize | `char s[] = "Hi";` | `string s = "Hi";` |
| Input | `cin.getline(s, 100);` | `getline(cin, s);` |
| Output | `cout << s;` | `cout << s;` |
| Length | `strlen(s)` | `s.length()` |
| Copy | `strcpy(dest, src)` | `dest = src;` |
| Compare | `strcmp(s1, s2) == 0` | `s1 == s2` |
| Concatenate | `strcat(s1, s2)` | `s1 + s2` |

## Summary

- **C-style strings** are character arrays terminated by `\0`
- Must have space for null terminator
- Use `<cstring>` functions for operations
- No bounds checking - be careful!
- Input with `cin.getline()` to prevent overflow
- Cannot use `=` for copying or `==` for comparison
- Still used in legacy code and low-level operations
- More error-prone but sometimes more efficient
- C++ strings are safer and easier to use
- Important to understand for system programming

## Basic Template
```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char str1[50];
    char str2[50];
    
    // Input with bounds checking
    cout << "Enter first string: ";
    cin.getline(str1, 50);
    
    cout << "Enter second string: ";
    cin.getline(str2, 50);
    
    // Operations
    cout << "\nFirst string: " << str1 << endl;
    cout << "Second string: " << str2 << endl;
    cout << "Length of first: " << strlen(str1) << endl;
    
    // Comparison
    if (strcmp(str1, str2) == 0) {
        cout << "Strings are equal" << endl;
    } else {
        cout << "Strings are different" << endl;
    }
    
    // Concatenation (if enough space)
    if (strlen(str1) + strlen(str2) + 1 < 50) {
        strcat(str1, str2);
        cout << "Concatenated: " << str1 << endl;
    } else {
        cout << "Not enough space to concatenate" << endl;
    }
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*