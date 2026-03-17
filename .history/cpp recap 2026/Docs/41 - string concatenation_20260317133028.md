# 41 - String Concatenation in C++

## What is String Concatenation?
String concatenation means joining two or more strings together to form a new string. In C++, there are multiple ways to concatenate strings, especially with the `string` class.

## Basic Concatenation with + Operator

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string firstName = "John";
    string lastName = "Doe";
    
    // Simple concatenation
    string fullName = firstName + " " + lastName;
    
    cout << "Full name: " << fullName << endl;
    
    return 0;
}
```

## Different Concatenation Methods

### Method 1: Using + Operator
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1 = "Hello";
    string s2 = "World";
    
    string result = s1 + " " + s2;
    cout << "Result: " << result << endl;  // Hello World
    
    // Can mix string literals and string objects
    string message = "Welcome" + string(" to") + " C++";
    cout << message << endl;  // Welcome to C++
    
    return 0;
}
```

### Method 2: Using += Operator
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello";
    
    str += " ";      // Append space
    str += "World";  // Append string
    str += '!';      // Append character
    
    cout << str << endl;  // Hello World!
    
    return 0;
}
```

### Method 3: Using append()
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello";
    
    str.append(" ");           // Append string literal
    str.append("World");       // Append string
    str.append(3, '!');        // Append 3 exclamation marks
    
    cout << str << endl;       // Hello World!!!
    
    // Append part of a string
    string source = "Programming";
    str.append(source, 0, 4);  // Append first 4 chars: "Prog"
    cout << str << endl;       // Hello World!!!Prog
    
    return 0;
}
```

### Method 4: Using insert()
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello World";
    
    // Insert at specific position
    str.insert(5, " Beautiful");
    cout << str << endl;  // Hello Beautiful World
    
    return 0;
}
```

## Concatenating Different Types

### String + String
```cpp
string s1 = "Hello";
string s2 = "World";
string result = s1 + " " + s2;  // Works fine
```

### String + C-string
```cpp
string s = "Hello";
const char* cstr = "World";
string result = s + " " + cstr;  // Works fine
cout << result << endl;  // Hello World
```

### String + Character
```cpp
string s = "Hello";
char ch = '!';
string result = s + ch;  // Works fine
cout << result << endl;  // Hello!
```

### String + Number (Need Conversion)
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "Number: ";
    int num = 42;
    
    // Wrong - doesn't work
    // string result = s + num;  // Error!
    
    // Correct - convert number to string
    string result = s + to_string(num);
    cout << result << endl;  // Number: 42
    
    // With double
    double pi = 3.14159;
    result = "Pi = " + to_string(pi);
    cout << result << endl;  // Pi = 3.141590
    
    return 0;
}
```

## Practical Examples

### Example 1: Building a Sentence
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string subject = "The cat";
    string verb = "sat";
    string preposition = "on";
    string object = "the mat";
    
    // Build sentence step by step
    string sentence = subject;
    sentence += " " + verb;
    sentence += " " + preposition;
    sentence += " " + object;
    sentence += ".";
    
    cout << sentence << endl;  // The cat sat on the mat.
    
    // One-liner
    string sentence2 = subject + " " + verb + " " + preposition + " " + object + ".";
    cout << sentence2 << endl;
    
    return 0;
}
```

### Example 2: Creating a Greeting
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string title = "Mr.";
    string firstName = "John";
    string lastName = "Doe";
    int age = 30;
    
    // Build greeting
    string greeting = "Hello, " + title + " " + firstName + " " + lastName;
    greeting += "! You are " + to_string(age) + " years old.";
    
    cout << greeting << endl;
    // Hello, Mr. John Doe! You are 30 years old.
    
    return 0;
}
```

### Example 3: CSV Line Builder
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector<string> fields = {"John", "Doe", "30", "New York"};
    string csvLine;
    
    // Build CSV line
    for (size_t i = 0; i < fields.size(); i++) {
        csvLine += fields[i];
        if (i < fields.size() - 1) {
            csvLine += ",";  // Add comma between fields
        }
    }
    
    cout << "CSV Line: " << csvLine << endl;
    // CSV Line: John,Doe,30,New York
    
    return 0;
}
```

### Example 4: URL Builder
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string protocol = "https";
    string domain = "example.com";
    string path = "api";
    string endpoint = "users";
    int id = 123;
    
    // Build URL
    string url = protocol + "://" + domain;
    url += "/" + path;
    url += "/" + endpoint;
    url += "/" + to_string(id);
    
    cout << "URL: " << url << endl;
    // URL: https://example.com/api/users/123
    
    // With query parameters
    url += "?format=json&limit=10";
    cout << "Full URL: " << url << endl;
    
    return 0;
}
```

### Example 5: Progress Bar Builder
```cpp
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    int progress = 65;
    int width = 20;
    
    // Build progress bar
    string bar = "[";
    
    int filled = (progress * width) / 100;
    for (int i = 0; i < width; i++) {
        if (i < filled) {
            bar += "=";
        } else if (i == filled) {
            bar += ">";
        } else {
            bar += " ";
        }
    }
    
    bar += "] " + to_string(progress) + "%";
    
    cout << bar << endl;
    // [=============>      ] 65%
    
    return 0;
}
```

## Performance Considerations

### Inefficient Concatenation
```cpp
#include <iostream>
#include <string>
#include <chrono>
using namespace std;

int main() {
    string result;
    
    // Inefficient - creates new string each time
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 10000; i++) {
        result = result + "x";  // Creates temporary strings
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Inefficient time: " << duration.count() << " ms" << endl;
    
    return 0;
}
```

### Efficient Concatenation
```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;

int main() {
    // Method 1: Using += (efficient)
    string result1;
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 10000; i++) {
        result1 += "x";  // Appends without creating new strings
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "+= time: " << duration.count() << " ms" << endl;
    
    // Method 2: Using stringstream (good for many concatenations)
    stringstream ss;
    start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 10000; i++) {
        ss << "x";
    }
    string result2 = ss.str();
    
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "stringstream time: " << duration.count() << " ms" << endl;
    
    return 0;
}
```

## Concatenation with Different Data Types

### Using to_string()
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Value: ";
    
    // Convert different types to string
    text += to_string(42);           // int
    text += ", " + to_string(3.14);  // double
    text += ", " + to_string(true);  // bool (1 or 0)
    
    cout << text << endl;
    // Value: 42, 3.140000, 1
    
    return 0;
}
```

### Using stringstream (for complex formatting)
```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

int main() {
    stringstream ss;
    
    // Build complex string with formatting
    ss << "Name: " << setw(10) << "John" << endl;
    ss << "Age: " << setw(10) << 30 << endl;
    ss << "Score: " << fixed << setprecision(2) << 95.5 << endl;
    
    string result = ss.str();
    cout << result;
    
    return 0;
}
```

## C-style String Concatenation

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char str1[50] = "Hello";
    char str2[] = " World";
    char str3[] = "!";
    
    // Using strcat
    strcat(str1, str2);  // Append str2 to str1
    strcat(str1, str3);  // Append str3 to str1
    
    cout << "Result: " << str1 << endl;  // Hello World!
    
    // Using strncat (safer, with size limit)
    char buffer[50] = "Hello";
    strncat(buffer, " Beautiful World", 10);  // Only add 10 chars
    cout << "Limited: " << buffer << endl;     // Hello Beautiful
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Adding String and Number Directly
```cpp
string s = "Number: ";
int num = 42;

// Wrong
// string result = s + num;  // Error!

// Correct
string result = s + to_string(num);
```

### Mistake 2: Forgetting to Include <string>
```cpp
// Wrong
string s1 = "Hello";
string s2 = "World";
string s3 = s1 + s2;  // Error if <string> not included

// Correct
#include <string>
```

### Mistake 3: Using + with C-string Literals Only
```cpp
// Wrong - can't concatenate two string literals
string result = "Hello" + "World";  // Error!

// Correct - at least one must be string object
string result = string("Hello") + "World";
// or
string result = "Hello" + string("World");
```

### Mistake 4: Modifying String During Range-based Loop
```cpp
string s = "Hello";

// Wrong - can't modify while iterating with range-based for
for (char c : s) {
    s += c;  // Dangerous! May invalidate iterators
}

// Correct
for (int i = 0; i < s.length(); i++) {
    s += s[i];  // Still be careful with infinite loops
}
```

### Mistake 5: Not Reserving Space
```cpp
string result;

// Inefficient for many concatenations
for (int i = 0; i < 1000; i++) {
    result += "x";  // Repeated reallocations
}

// Better - reserve space first
string result;
result.reserve(1000);  // Pre-allocate space
for (int i = 0; i < 1000; i++) {
    result += "x";  // No reallocations
}
```

## Quick Reference

| Operation | Syntax | Example |
|-----------|--------|---------|
| + operator | `s1 + s2` | `"Hello " + "World"` |
| += operator | `s1 += s2` | `str += "!"` |
| append() | `s.append(str)` | `s.append("World")` |
| append(n, c) | `s.append(3, '!')` | Add 3 ! marks |
| append(str, pos, n) | `s.append("Hello", 1, 3)` | Append "ell" |
| insert() | `s.insert(pos, str)` | `s.insert(5, "Hi")` |
| stringstream | `ss << s1 << s2` | Build with formatting |
| to_string() | `to_string(num)` | Convert number to string |

## Summary

- **+ operator** for simple concatenation
- **+= operator** for appending
- **append()** method for advanced concatenation
- **stringstream** for complex builds with formatting
- **to_string()** to convert numbers before concatenation
- Use `reserve()` for many concatenations (performance)
- Can mix string objects, C-strings, and characters
- Be careful with string literals (at least one must be string object)
- C-style strings use `strcat()` (dangerous - buffer overflow risk)
- **stringstream** is efficient for building complex strings

## Basic Template
```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    // Method 1: + operator
    string s1 = "Hello";
    string s2 = "World";
    string result1 = s1 + " " + s2;
    cout << "+ operator: " << result1 << endl;
    
    // Method 2: += operator
    string result2 = "Start";
    result2 += " ";
    result2 += "Middle";
    result2 += " ";
    result2 += "End";
    cout << "+= operator: " << result2 << endl;
    
    // Method 3: append()
    string result3 = "Hello";
    result3.append(" ").append("World").append("!");
    cout << "append(): " << result3 << endl;
    
    // Method 4: stringstream (for complex strings)
    stringstream ss;
    ss << "Hello" << " " << "World" << "!";
    ss << " The number is " << 42;
    string result4 = ss.str();
    cout << "stringstream: " << result4 << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*