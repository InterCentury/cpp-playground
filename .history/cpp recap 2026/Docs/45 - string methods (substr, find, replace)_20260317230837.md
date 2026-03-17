# 45 - String Methods (substr, find, replace) in C++

## What are String Methods?
String methods are functions that belong to the `string` class and allow you to manipulate and query strings. The most commonly used are `substr()`, `find()`, and `replace()`.

## substr() - Extract Substring

### Basic substr() Usage
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Hello World";
    
    // Extract from position, default length to end
    string sub1 = text.substr(6);     // From index 6 to end
    string sub2 = text.substr(0, 5);   // From index 0, length 5
    string sub3 = text.substr(6, 5);   // From index 6, length 5
    
    cout << "Original: " << text << endl;
    cout << "substr(6): " << sub1 << endl;      // "World"
    cout << "substr(0,5): " << sub2 << endl;    // "Hello"
    cout << "substr(6,5): " << sub3 << endl;    // "World"
    
    return 0;
}
```

### substr() with Different Positions
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "C++ Programming";
    
    cout << "Full string: " << text << endl;
    cout << "First 3 chars: " << text.substr(0, 3) << endl;        // "C++"
    cout << "Last 7 chars: " << text.substr(4, 7) << endl;        // "Program"
    cout << "From index 4: " << text.substr(4) << endl;           // "Programming"
    
    // Get last character
    cout << "Last char: " << text.substr(text.length() - 1) << endl;  // "g"
    
    return 0;
}
```

### Error Handling with substr()
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Hello";
    
    // Valid substr
    cout << text.substr(1, 3) << endl;  // "ell"
    
    // These will throw out_of_range exception
    try {
        cout << text.substr(10) << endl;  // Position beyond length
    } catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // Safe way - check bounds
    int pos = 2;
    int len = 5;
    if (pos < text.length()) {
        string safe = text.substr(pos, min(len, (int)text.length() - pos));
        cout << "Safe substr: " << safe << endl;
    }
    
    return 0;
}
```

## find() - Search in String

### Basic find() Usage
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Hello world, welcome to C++";
    
    // Find first occurrence
    size_t pos = text.find("world");
    if (pos != string::npos) {
        cout << "'world' found at position: " << pos << endl;
    }
    
    // Find character
    pos = text.find('w');
    cout << "First 'w' at: " << pos << endl;
    
    // Find from specific position
    pos = text.find("o", 5);  // Start search from index 5
    cout << "Next 'o' after position 5 at: " << pos << endl;
    
    return 0;
}
```

### Finding All Occurrences
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "The cat sat on the mat";
    string search = "at";
    
    cout << "Text: " << text << endl;
    cout << "Searching for: \"" << search << "\"" << endl;
    
    size_t pos = 0;
    int count = 0;
    
    while ((pos = text.find(search, pos)) != string::npos) {
        cout << "Found at position: " << pos << endl;
        pos += search.length();
        count++;
    }
    
    cout << "Total occurrences: " << count << endl;
    
    return 0;
}
```

### find() Variants
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Hello world, welcome to C++ world";
    
    // find_first_of - any of the characters
    size_t pos = text.find_first_of("aeiou");  // First vowel
    cout << "First vowel at: " << pos << " ('" << text[pos] << "')" << endl;
    
    // find_last_of - last occurrence of any character
    pos = text.find_last_of("aeiou");
    cout << "Last vowel at: " << pos << " ('" << text[pos] << "')" << endl;
    
    // find_first_not_of
    pos = text.find_first_not_of("Helo ");  // First character not in set
    cout << "First char not in 'Helo ' at: " << pos << " ('" << text[pos] << "')" << endl;
    
    // rfind - reverse find (from end)
    pos = text.rfind("world");
    cout << "Last 'world' at: " << pos << endl;
    
    return 0;
}
```

## replace() - Replace Substring

### Basic replace() Usage
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Hello World";
    
    cout << "Original: " << text << endl;
    
    // Replace with another string
    text.replace(6, 5, "C++");  // Replace 5 chars at position 6 with "C++"
    cout << "After replace: " << text << endl;  // "Hello C++"
    
    // Replace with substring
    text = "I like apples";
    text.replace(7, 6, "oranges");  // Replace "apples" with "oranges"
    cout << text << endl;  // "I like oranges"
    
    return 0;
}
```

### Different replace() Overloads
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Hello World";
    
    // Replace with repeated character
    text.replace(6, 5, 3, '!');  // Replace with "!!!"
    cout << "With !!!: " << text << endl;  // "Hello !!!"
    
    // Replace with part of another string
    text = "Hello World";
    string source = "Beautiful";
    text.replace(6, 5, source, 0, 4);  // Replace with "Beau"
    cout << "With part: " << text << endl;  // "Hello Beau"
    
    // Using iterators
    text = "Hello World";
    text.replace(text.begin() + 6, text.begin() + 11, "C++");
    cout << "With iterators: " << text << endl;  // "Hello C++"
    
    return 0;
}
```

## Practical Examples

### Example 1: Extract Domain from Email
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string email = "user@example.com";
    
    // Find @ position
    size_t atPos = email.find('@');
    
    if (atPos != string::npos) {
        string username = email.substr(0, atPos);
        string domain = email.substr(atPos + 1);
        
        cout << "Email: " << email << endl;
        cout << "Username: " << username << endl;
        cout << "Domain: " << domain << endl;
        
        // Extract top-level domain
        size_t dotPos = domain.find_last_of('.');
        if (dotPos != string::npos) {
            string tld = domain.substr(dotPos + 1);
            cout << "TLD: " << tld << endl;
        }
    }
    
    return 0;
}
```

### Example 2: Replace All Occurrences
```cpp
#include <iostream>
#include <string>
using namespace std;

string replaceAll(string text, const string& from, const string& to) {
    size_t pos = 0;
    while ((pos = text.find(from, pos)) != string::npos) {
        text.replace(pos, from.length(), to);
        pos += to.length();
    }
    return text;
}

int main() {
    string text = "The cat sat on the mat. The cat was happy.";
    
    cout << "Original: " << text << endl;
    
    // Replace all "cat" with "dog"
    string result = replaceAll(text, "cat", "dog");
    cout << "After replace: " << result << endl;
    
    // Replace all spaces with dashes
    result = replaceAll(text, " ", "-");
    cout << "With dashes: " << result << endl;
    
    return 0;
}
```

### Example 3: Extract File Information
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string filePath = "/home/user/documents/report.txt";
    
    // Find last slash
    size_t slashPos = filePath.find_last_of('/');
    
    if (slashPos != string::npos) {
        string directory = filePath.substr(0, slashPos);
        string filename = filePath.substr(slashPos + 1);
        
        cout << "Full path: " << filePath << endl;
        cout << "Directory: " << directory << endl;
        cout << "Filename: " << filename << endl;
        
        // Extract name and extension
        size_t dotPos = filename.find_last_of('.');
        if (dotPos != string::npos) {
            string name = filename.substr(0, dotPos);
            string ext = filename.substr(dotPos + 1);
            cout << "File name: " << name << endl;
            cout << "Extension: " << ext << endl;
        }
    }
    
    return 0;
}
```

### Example 4: Censor Bad Words
```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string censorText(string text, const vector<string>& badWords) {
    for (const string& word : badWords) {
        size_t pos = 0;
        while ((pos = text.find(word, pos)) != string::npos) {
            text.replace(pos, word.length(), string(word.length(), '*'));
            pos += word.length();
        }
    }
    return text;
}

int main() {
    string text = "This is a bad word and another bad word here";
    vector<string> badWords = {"bad", "word"};
    
    cout << "Original: " << text << endl;
    string censored = censorText(text, badWords);
    cout << "Censored: " << censored << endl;
    
    return 0;
}
```

### Example 5: Parse Query String
```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    string query = "name=John&age=25&city=New+York";
    map<string, string> params;
    
    size_t start = 0;
    size_t end;
    
    while ((end = query.find('&', start)) != string::npos) {
        string pair = query.substr(start, end - start);
        size_t eqPos = pair.find('=');
        
        if (eqPos != string::npos) {
            string key = pair.substr(0, eqPos);
            string value = pair.substr(eqPos + 1);
            
            // Replace + with space
            size_t plusPos;
            while ((plusPos = value.find('+')) != string::npos) {
                value.replace(plusPos, 1, " ");
            }
            
            params[key] = value;
        }
        
        start = end + 1;
    }
    
    // Handle last parameter
    string last = query.substr(start);
    size_t eqPos = last.find('=');
    if (eqPos != string::npos) {
        string key = last.substr(0, eqPos);
        string value = last.substr(eqPos + 1);
        
        // Replace + with space
        size_t plusPos;
        while ((plusPos = value.find('+')) != string::npos) {
            value.replace(plusPos, 1, " ");
        }
        
        params[key] = value;
    }
    
    cout << "Parsed parameters:" << endl;
    for (const auto& p : params) {
        cout << "  " << p.first << " = " << p.second << endl;
    }
    
    return 0;
}
```

## Combining Methods

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "The quick brown fox jumps over the lazy dog";
    
    // Find and replace
    size_t pos = text.find("fox");
    if (pos != string::npos) {
        text.replace(pos, 3, "cat");
        cout << "After replace: " << text << endl;
    }
    
    // Extract using find and substr
    pos = text.find("jumps");
    if (pos != string::npos) {
        string before = text.substr(0, pos);
        string after = text.substr(pos + 5);
        cout << "Before jumps: " << before << endl;
        cout << "After jumps: " << after << endl;
    }
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Not Checking for npos
```cpp
string text = "Hello";
size_t pos = text.find("xyz");

// Wrong - assuming found
cout << "Found at: " << pos << endl;  // Prints huge number

// Correct
if (pos != string::npos) {
    cout << "Found at: " << pos << endl;
}
```

### Mistake 2: Off-by-One in substr
```cpp
string text = "Hello";

// Wrong - length too long
string sub = text.substr(1, 10);  // Throws exception

// Correct
string sub = text.substr(1, min(10, (int)text.length() - 1));
```

### Mistake 3: Modifying String During Search
```cpp
string text = "abcabc";

// Wrong - infinite loop
for (size_t pos = 0; pos < text.length(); pos++) {
    if (text.find("a", pos) != string::npos) {
        text.replace(pos, 1, "x");  // Modifies length
    }
}

// Correct - use while loop with position tracking
size_t pos = 0;
while ((pos = text.find("a", pos)) != string::npos) {
    text.replace(pos, 1, "x");
    pos += 1;
}
```

### Mistake 4: Using find with Wrong Type
```cpp
string text = "Hello";

// Wrong - searching for number
size_t pos = text.find(101);  // Treats 101 as character 'e'?

// Correct
size_t pos = text.find('e');
```

### Mistake 5: Forgetting that find returns size_t
```cpp
string text = "Hello";

// Wrong - comparing with int
if (text.find('e') == -1) { }  // Works but not portable

// Correct
if (text.find('e') == string::npos) { }
```

## Quick Reference

| Method | Description | Example |
|--------|-------------|---------|
| `substr(pos)` | Substring from pos to end | `s.substr(5)` |
| `substr(pos, len)` | Substring with length | `s.substr(0, 3)` |
| `find(str)` | Find first occurrence | `s.find("lo")` |
| `find(str, pos)` | Find from position | `s.find("o", 5)` |
| `rfind(str)` | Find from end | `s.rfind("o")` |
| `find_first_of(chars)` | Find any char from set | `s.find_first_of("aeiou")` |
| `find_last_of(chars)` | Find last from set | `s.find_last_of("aeiou")` |
| `replace(pos, len, str)` | Replace with string | `s.replace(0, 2, "new")` |
| `replace(pos, len, n, ch)` | Replace with repeated char | `s.replace(0, 2, 3, '!')` |

## Summary

- **substr()** extracts part of a string
- **find()** searches for substrings or characters
- **replace()** replaces parts of a string
- Always check for `string::npos` when using find()
- Be careful with bounds in substr() and replace()
- find() variants allow complex searches
- Can combine methods for powerful string manipulation
- Watch for infinite loops when modifying during search
- Use while loops for finding all occurrences
- string methods are efficient and easy to use

## Basic Template
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string text;
    
    cout << "Enter a sentence: ";
    getline(cin, text);
    
    // substr examples
    if (text.length() >= 5) {
        cout << "First 5 chars: " << text.substr(0, 5) << endl;
        cout << "Last 5 chars: " << text.substr(text.length() - 5) << endl;
    }
    
    // find examples
    size_t pos = text.find(' ');
    if (pos != string::npos) {
        cout << "First space at: " << pos << endl;
        cout << "First word: " << text.substr(0, pos) << endl;
    }
    
    // replace example
    string search, replace;
    cout << "Enter word to replace: ";
    cin >> search;
    cout << "Enter replacement: ";
    cin >> replace;
    
    pos = text.find(search);
    if (pos != string::npos) {
        text.replace(pos, search.length(), replace);
        cout << "Modified: " << text << endl;
    }
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*