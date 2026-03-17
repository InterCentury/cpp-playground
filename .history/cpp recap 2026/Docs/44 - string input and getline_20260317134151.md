# 44 - String Input and getline() in C++

## What is String Input?
String input means reading text from the user. C++ provides several ways to read strings, each with different behaviors regarding spaces and newlines.

## Basic Input Methods

### Using cin (stops at whitespace)
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string firstName, lastName;
    
    cout << "Enter first name: ";
    cin >> firstName;  // Reads until space or newline
    
    cout << "Enter last name: ";
    cin >> lastName;
    
    cout << "Hello, " << firstName << " " << lastName << "!" << endl;
    
    return 0;
}
```

### Problem with cin and spaces
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string fullName;
    
    cout << "Enter your full name: ";
    cin >> fullName;  // Only reads first word!
    
    cout << "You entered: " << fullName << endl;  // Only first name
    
    return 0;
}
```

## Using getline() for Full Lines

### Basic getline()
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string fullName;
    
    cout << "Enter your full name: ";
    getline(cin, fullName);  // Reads entire line including spaces
    
    cout << "You entered: " << fullName << endl;
    
    return 0;
}
```

### getline() with Delimiter
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string data;
    
    cout << "Enter data (stop at comma): ";
    getline(cin, data, ',');  // Reads until comma
    
    cout << "Data before comma: " << data << endl;
    
    // Read remaining
    getline(cin, data);  // Reads rest of line
    cout << "Remaining: " << data << endl;
    
    return 0;
}
```

## The cin.ignore() Problem

### The Mixing Issue
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int age;
    string name;
    
    cout << "Enter age: ";
    cin >> age;  // Leaves newline in buffer
    
    cout << "Enter name: ";
    getline(cin, name);  // Reads the leftover newline!
    
    cout << "Age: " << age << endl;
    cout << "Name: \"" << name << "\"" << endl;  // Empty!
    
    return 0;
}
```

### Solution: Using cin.ignore()
```cpp
#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main() {
    int age;
    string name;
    
    cout << "Enter age: ";
    cin >> age;
    
    // Clear the newline from buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Enter name: ";
    getline(cin, name);
    
    cout << "Age: " << age << endl;
    cout << "Name: " << name << endl;
    
    return 0;
}
```

## Multiple Inputs with getline()

### Reading Multiple Lines
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string line;
    int lineNum = 1;
    
    cout << "Enter multiple lines (empty line to stop):" << endl;
    
    while (true) {
        cout << "Line " << lineNum << ": ";
        getline(cin, line);
        
        if (line.empty()) {
            break;
        }
        
        cout << "You entered: " << line << endl;
        lineNum++;
    }
    
    cout << "Total lines: " << lineNum - 1 << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Reading Paragraphs
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string paragraph;
    string line;
    
    cout << "Enter a paragraph (empty line to finish):" << endl;
    
    while (true) {
        getline(cin, line);
        if (line.empty()) {
            break;
        }
        paragraph += line + "\n";
    }
    
    cout << "\n--- Your Paragraph ---" << endl;
    cout << paragraph;
    cout << "----------------------" << endl;
    cout << "Total characters: " << paragraph.length() << endl;
    
    return 0;
}
```

### Example 2: CSV Data Input
```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    string line;
    
    cout << "Enter CSV data (name,age,city):" << endl;
    getline(cin, line);
    
    // Parse CSV line
    stringstream ss(line);
    string item;
    vector<string> fields;
    
    while (getline(ss, item, ',')) {
        fields.push_back(item);
    }
    
    cout << "\nParsed fields:" << endl;
    for (size_t i = 0; i < fields.size(); i++) {
        cout << "Field " << i+1 << ": \"" << fields[i] << "\"" << endl;
    }
    
    return 0;
}
```

### Example 3: Menu System with Input Validation
```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string choice;
    
    do {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Load Game" << endl;
        cout << "3. Settings" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice (1-4): ";
        
        getline(cin, choice);
        
        // Validate input
        if (choice.length() == 1 && isdigit(choice[0])) {
            int opt = stoi(choice);
            switch (opt) {
                case 1:
                    cout << "Starting game..." << endl;
                    break;
                case 2:
                    cout << "Loading game..." << endl;
                    break;
                case 3:
                    cout << "Settings opened..." << endl;
                    break;
                case 4:
                    cout << "Goodbye!" << endl;
                    return 0;
                default:
                    cout << "Invalid option!" << endl;
            }
        } else {
            cout << "Invalid input! Please enter a number (1-4)." << endl;
        }
    } while (true);
    
    return 0;
}
```

### Example 4: Reading Formatted Input
```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string input;
    
    cout << "Enter data in format: name age score" << endl;
    cout << "Example: John 25 85.5" << endl;
    cout << "> ";
    
    getline(cin, input);
    
    // Parse using stringstream
    stringstream ss(input);
    string name;
    int age;
    double score;
    
    if (ss >> name >> age >> score) {
        cout << "\nParsed data:" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Score: " << score << endl;
    } else {
        cout << "Invalid format!" << endl;
    }
    
    return 0;
}
```

### Example 5: Password Input (Hidden)
```cpp
#include <iostream>
#include <string>
#include <conio.h>  // For _getch() on Windows
using namespace std;

string getPassword() {
    string password;
    char ch;
    
    cout << "Enter password: ";
    
    while (true) {
        ch = _getch();  // Get character without echo
        
        if (ch == '\r') {  // Enter key
            break;
        } else if (ch == '\b') {  // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";  // Erase asterisk
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    
    cout << endl;
    return password;
}

int main() {
    string password = getPassword();
    
    cout << "Password entered (" << password.length() << " chars)" << endl;
    
    return 0;
}
```

## Reading from String Streams

```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string data = "apple,banana,orange,grape";
    stringstream ss(data);
    string fruit;
    
    cout << "Fruits:" << endl;
    while (getline(ss, fruit, ',')) {
        cout << " - " << fruit << endl;
    }
    
    return 0;
}
```

## Handling Different Input Formats

### Reading Numbers and Strings Mixed
```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string line;
    
    cout << "Enter: name age (e.g., John 25): ";
    getline(cin, line);
    
    stringstream ss(line);
    string name;
    int age;
    
    if (ss >> name >> age) {
        cout << "Name: " << name << ", Age: " << age << endl;
    } else {
        cout << "Invalid input format!" << endl;
    }
    
    return 0;
}
```

### Reading Until Delimiter
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string email;
    
    cout << "Enter email address: ";
    getline(cin, email);
    
    // Extract username (part before @)
    stringstream ss(email);
    string username;
    getline(ss, username, '@');
    
    cout << "Username: " << username << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Mixing cin and getline Without ignore()
```cpp
int age;
string name;

cout << "Enter age: ";
cin >> age;
// Missing cin.ignore() here!
cout << "Enter name: ";
getline(cin, name);  // Reads leftover newline

// Correct
cin >> age;
cin.ignore();
getline(cin, name);
```

### Mistake 2: Not Checking for Empty Input
```cpp
string input;

cout << "Enter something: ";
getline(cin, input);

if (input.empty()) {
    cout << "No input provided!" << endl;
}
```

### Mistake 3: Using cin for Multi-word Input
```cpp
string city;

cout << "Enter city name: ";
cin >> city;  // Won't work for "New York"

// Correct
getline(cin, city);
```

### Mistake 4: Forgetting to Clear Error State
```cpp
int num;
string input;

cout << "Enter number: ";
cin >> num;

if (cin.fail()) {
    cin.clear();  // Clear error flag
    cin.ignore(10000, '\n');  // Clear buffer
}

cout << "Enter text: ";
getline(cin, input);  // Now it works
```

### Mistake 5: Not Handling getline Failures
```cpp
string line;

while (getline(cin, line)) {
    if (cin.eof()) {
        cout << "End of file reached" << endl;
        break;
    }
    // Process line
}
```

## Quick Reference

| Method | Description | Stops at |
|--------|-------------|----------|
| `cin >> str` | Reads word | Whitespace |
| `getline(cin, str)` | Reads line | Newline |
| `getline(cin, str, delim)` | Reads until delimiter | Delimiter character |
| `cin.getline(char*, size)` | C-style line input | Newline or size |

## Summary

- **cin >>** reads until whitespace (good for single words)
- **getline()** reads entire lines including spaces
- Always use **cin.ignore()** after cin before getline
- Check for **empty()** input to validate
- Use **stringstream** to parse formatted input
- Delimiter version of getline() for CSV parsing
- Handle input failures with cin.fail() and cin.clear()
- Consider platform-specific solutions for hidden input
- EOF handling with while(getline(...))

## Basic Template
```cpp
#include <iostream>
#include <string>
#include <limits>
using namespace std;

int main() {
    string name;
    int age;
    
    // Single word input
    cout << "Enter first name: ";
    cin >> name;
    
    // Clear buffer before getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Full line input
    cout << "Enter full address: ";
    string address;
    getline(cin, address);
    
    // Mixed input with validation
    cout << "Enter age and city (e.g., 25 New York): ";
    string line;
    getline(cin, line);
    
    stringstream ss(line);
    string city;
    if (ss >> age >> city) {
        cout << "\n--- Information ---" << endl;
        cout << "First name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "City: " << city << endl;
        cout << "Address: " << address << endl;
    }
    
    return 0;
}
```

---
* This documentation belongs to https://github.com/InterCentury*