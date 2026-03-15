# 33 - 1D Array Declaration and Initialization in C++

## What is an Array?
An array is a collection of elements of the same type stored in contiguous memory locations. Think of it as a row of boxes, each containing a value and identified by an index.

## Basic Syntax

```cpp
// Declaration
dataType arrayName[arraySize];

// Declaration with initialization
dataType arrayName[arraySize] = {value1, value2, ..., valueN};
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

int main() {
    // Declare and initialize an array
    int numbers[5] = {10, 20, 30, 40, 50};
    
    // Access and print array elements
    cout << "First element: " << numbers[0] << endl;
    cout << "Second element: " << numbers[1] << endl;
    cout << "Third element: " << numbers[2] << endl;
    cout << "Fourth element: " << numbers[3] << endl;
    cout << "Fifth element: " << numbers[4] << endl;
    
    return 0;
}
```
Output:
```
First element: 10
Second element: 20
Third element: 30
Fourth element: 40
Fifth element: 50
```

## Array Indexing

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {100, 200, 300, 400, 500};
    
    cout << "Array indices and values:" << endl;
    cout << "arr[0] = " << arr[0] << "  // First element" << endl;
    cout << "arr[1] = " << arr[1] << "  // Second element" << endl;
    cout << "arr[2] = " << arr[2] << "  // Third element" << endl;
    cout << "arr[3] = " << arr[3] << "  // Fourth element" << endl;
    cout << "arr[4] = " << arr[4] << "  // Fifth element" << endl;
    
    // Index always starts at 0, last index is size-1
    
    return 0;
}
```

## Different Ways to Declare and Initialize

### Method 1: Declare then Initialize
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5];  // Declaration only
    
    // Initialize each element individually
    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;
    numbers[3] = 40;
    numbers[4] = 50;
    
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Method 2: Declare and Initialize Together
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};  // Full initialization
    
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Method 3: Partial Initialization
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {10, 20};  // First two initialized, rest set to 0
    
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << "numbers[" << i << "] = " << numbers[i] << endl;
    }
    
    return 0;
}
```
Output:
```
numbers[0] = 10
numbers[1] = 20
numbers[2] = 0
numbers[3] = 0
numbers[4] = 0
```

### Method 4: Size Deduced from Initializer
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};  // Size automatically 5
    
    int size = sizeof(numbers) / sizeof(numbers[0]);
    cout << "Array size: " << size << endl;
    
    cout << "Elements: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Method 5: Zero Initialization
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {};  // All elements initialized to 0
    
    cout << "Zero-initialized array:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "numbers[" << i << "] = " << numbers[i] << endl;
    }
    
    return 0;
}
```

## Arrays of Different Types

### Integer Array
```cpp
#include <iostream>
using namespace std;

int main() {
    int ages[5] = {18, 22, 25, 30, 35};
    
    cout << "Ages: ";
    for (int i = 0; i < 5; i++) {
        cout << ages[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Double Array
```cpp
#include <iostream>
using namespace std;

int main() {
    double prices[4] = {9.99, 19.99, 29.99, 39.99};
    
    cout << "Prices: $";
    for (int i = 0; i < 4; i++) {
        cout << prices[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Char Array (C-string)
```cpp
#include <iostream>
using namespace std;

int main() {
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    char name[6] = "John";  // +1 for null terminator
    
    cout << "Vowels: ";
    for (int i = 0; i < 5; i++) {
        cout << vowels[i] << " ";
    }
    cout << endl;
    
    cout << "Name: " << name << endl;
    
    return 0;
}
```

### String Array (C++ strings)
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string fruits[4] = {"apple", "banana", "orange", "grape"};
    
    cout << "Fruits: ";
    for (int i = 0; i < 4; i++) {
        cout << fruits[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Boolean Array
```cpp
#include <iostream>
using namespace std;

int main() {
    bool flags[5] = {true, false, true, false, true};
    
    cout << boolalpha;  // Print true/false instead of 1/0
    cout << "Flags: ";
    for (int i = 0; i < 5; i++) {
        cout << flags[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Student Grades
```cpp
#include <iostream>
using namespace std;

int main() {
    // Array of student grades
    int grades[6] = {85, 92, 78, 90, 88, 95};
    int sum = 0;
    
    cout << "Student grades: ";
    for (int i = 0; i < 6; i++) {
        cout << grades[i] << " ";
        sum += grades[i];
    }
    cout << endl;
    
    double average = (double)sum / 6;
    cout << "Average grade: " << average << endl;
    
    return 0;
}
```

### Example 2: Days in Month
```cpp
#include <iostream>
using namespace std;

int main() {
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 
                           31, 31, 30, 31, 30, 31};
    string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                         "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    cout << "Days in each month:" << endl;
    for (int i = 0; i < 12; i++) {
        cout << months[i] << ": " << daysInMonth[i] << " days" << endl;
    }
    
    return 0;
}
```

### Example 3: Temperature Readings
```cpp
#include <iostream>
using namespace std;

int main() {
    double temperatures[7] = {23.5, 24.0, 22.5, 25.5, 26.0, 24.5, 23.0};
    
    cout << "Weekly temperatures:" << endl;
    cout << "Day\tTemp(°C)" << endl;
    cout << "---\t--------" << endl;
    
    for (int i = 0; i < 7; i++) {
        cout << i + 1 << "\t" << temperatures[i] << endl;
    }
    
    return 0;
}
```

### Example 4: Initializing with Loop
```cpp
#include <iostream>
using namespace std;

int main() {
    int squares[10];
    
    // Initialize array with squares
    for (int i = 0; i < 10; i++) {
        squares[i] = (i + 1) * (i + 1);
    }
    
    cout << "Squares of numbers 1-10:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << (i + 1) << "² = " << squares[i] << endl;
    }
    
    return 0;
}
```

### Example 5: Fibonacci Sequence
```cpp
#include <iostream>
using namespace std;

int main() {
    int fib[10];
    
    // Initialize first two elements
    fib[0] = 0;
    fib[1] = 1;
    
    // Generate Fibonacci sequence
    for (int i = 2; i < 10; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    cout << "Fibonacci sequence (first 10):" << endl;
    for (int i = 0; i < 10; i++) {
        cout << fib[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Array Size and Memory

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    
    // Get array size
    int arraySize = sizeof(numbers);           // Total bytes
    int elementSize = sizeof(numbers[0]);      // Bytes per element
    int length = sizeof(numbers) / sizeof(numbers[0]);  // Number of elements
    
    cout << "Total array size: " << arraySize << " bytes" << endl;
    cout << "Each element size: " << elementSize << " bytes" << endl;
    cout << "Number of elements: " << length << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Index Out of Bounds
```cpp
int arr[5] = {1, 2, 3, 4, 5};

// Wrong - index out of bounds
cout << arr[5];  // Index 5 doesn't exist (0-4 only)

// Correct - valid indices 0-4
for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}
```

### Mistake 2: Using Uninitialized Array
```cpp
int arr[5];  // Contains garbage values

// Wrong - using uninitialized values
cout << arr[0];  // Prints garbage

// Correct - initialize before use
int arr[5] = {0};  // All zeros
```

### Mistake 3: Wrong Array Size
```cpp
// Wrong - size too small
int arr[3] = {1, 2, 3, 4, 5};  // Too many initializers

// Correct
int arr[5] = {1, 2, 3, 4, 5};

// Or let compiler deduce size
int arr[] = {1, 2, 3, 4, 5};
```

### Mistake 4: Forgetting Null Terminator in C-strings
```cpp
// Wrong - no space for null terminator
char name[4] = "John";  // Needs 5 chars: J o h n \0

// Correct
char name[5] = "John";
// or
char name[] = "John";  // Size automatically includes null
```

### Mistake 5: Assigning After Declaration Wrongly
```cpp
int arr[5];

// Wrong - can't assign all at once after declaration
arr = {1, 2, 3, 4, 5};  // Error!

// Correct - assign individually
arr[0] = 1;
arr[1] = 2;
arr[2] = 3;
arr[3] = 4;
arr[4] = 5;

// Or use loop
for (int i = 0; i < 5; i++) {
    arr[i] = i + 1;
}
```

## Array Initialization Summary

| Initialization Method | Code | Result |
|----------------------|------|--------|
| Full initialization | `int arr[5] = {1,2,3,4,5};` | All elements set |
| Partial initialization | `int arr[5] = {1,2};` | Rest set to 0 |
| Zero initialization | `int arr[5] = {};` | All elements 0 |
| No initialization | `int arr[5];` | Garbage values |
| Size deduced | `int arr[] = {1,2,3};` | Size = 3 |
| Individual assignment | `arr[0] = 1; arr[1] = 2;` | Set individually |

## Quick Reference

| Operation | Syntax | Example |
|-----------|--------|---------|
| Declare | `type name[size];` | `int nums[10];` |
| Initialize | `type name[size] = {vals};` | `int nums[3] = {1,2,3};` |
| Access | `name[index]` | `nums[0] = 5;` |
| First index | `name[0]` | Always 0 |
| Last index | `name[size-1]` | `nums[4]` for size 5 |
| Get size | `sizeof(arr)/sizeof(arr[0])` | Number of elements |

## Summary

- **Array** stores multiple values of same type
- Index starts at **0**, last index is **size-1**
- Must declare with size or initialize
- Partial initialization zeros remaining elements
- Use `sizeof` to get array size in bytes/elements
- Access elements with `arrayName[index]`
- Can't assign all elements at once after declaration
- Watch for **index out of bounds** errors
- Different types: int, double, char, string, bool
- Great for lists, sequences, and collections

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    // Different ways to declare and initialize
    int arr1[5] = {10, 20, 30, 40, 50};      // Full initialization
    int arr2[5] = {1, 2};                    // Partial (rest 0)
    int arr3[] = {5, 10, 15, 20};            // Size deduced
    int arr4[5] = {};                         // All zeros
    
    // Display array
    cout << "Array 1: ";
    for (int i = 0; i < 5; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    // Array size
    int size = sizeof(arr3) / sizeof(arr3[0]);
    cout << "Array 3 size: " << size << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*