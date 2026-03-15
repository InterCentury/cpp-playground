# 34 - Accessing Array Elements in C++

## What is Array Access?
Accessing array elements means reading or modifying values at specific positions in an array using their indices. Think of it like opening specific numbered boxes in a row.

## Basic Syntax

```cpp
// Read element
dataType value = arrayName[index];

// Write element
arrayName[index] = newValue;
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};
    
    // Reading elements
    cout << "Reading array elements:" << endl;
    cout << "numbers[0] = " << numbers[0] << endl;
    cout << "numbers[1] = " << numbers[1] << endl;
    cout << "numbers[2] = " << numbers[2] << endl;
    cout << "numbers[3] = " << numbers[3] << endl;
    cout << "numbers[4] = " << numbers[4] << endl;
    
    // Modifying elements
    cout << "\nModifying elements:" << endl;
    cout << "Original numbers[2] = " << numbers[2] << endl;
    numbers[2] = 100;
    cout << "After numbers[2] = 100: " << numbers[2] << endl;
    
    return 0;
}
```

## Accessing with Loops

### Using for Loop
```cpp
#include <iostream>
using namespace std;

int main() {
    int scores[] = {85, 92, 78, 90, 88};
    int size = sizeof(scores) / sizeof(scores[0]);
    
    cout << "All scores: ";
    for (int i = 0; i < size; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;
    
    // Modify all elements
    for (int i = 0; i < size; i++) {
        scores[i] += 5;  // Add 5 bonus points
    }
    
    cout << "After bonus: ";
    for (int i = 0; i < size; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Using while Loop
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {2, 4, 6, 8, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int i = 0;
    
    cout << "Numbers: ";
    while (i < size) {
        cout << numbers[i] << " ";
        i++;
    }
    cout << endl;
    
    return 0;
}
```

### Using Range-based for Loop (C++11)
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    
    cout << "Read-only access: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Modify using reference
    cout << "Modifying: ";
    for (int& num : numbers) {
        num *= 2;  // Double each value
    }
    
    cout << "After doubling: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Find Maximum Element
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {45, 23, 78, 12, 89, 34, 67};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    // Assume first element is maximum
    int max = numbers[0];
    int maxIndex = 0;
    
    // Search through array
    for (int i = 1; i < size; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
            maxIndex = i;
        }
    }
    
    cout << "Maximum value: " << max << endl;
    cout << "Found at index: " << maxIndex << endl;
    
    return 0;
}
```

### Example 2: Calculate Average
```cpp
#include <iostream>
using namespace std;

int main() {
    int grades[] = {85, 92, 78, 90, 88, 95, 76};
    int size = sizeof(grades) / sizeof(grades[0]);
    int sum = 0;
    
    // Sum all elements
    for (int i = 0; i < size; i++) {
        sum += grades[i];
    }
    
    double average = (double)sum / size;
    
    cout << "Grades: ";
    for (int i = 0; i < size; i++) {
        cout << grades[i] << " ";
    }
    cout << endl;
    
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    
    return 0;
}
```

### Example 3: Search for Value
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {23, 45, 12, 67, 34, 89, 56};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int searchFor;
    bool found = false;
    
    cout << "Enter number to search: ";
    cin >> searchFor;
    
    // Linear search
    for (int i = 0; i < size; i++) {
        if (numbers[i] == searchFor) {
            cout << searchFor << " found at index " << i << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << searchFor << " not found in array" << endl;
    }
    
    return 0;
}
```

### Example 4: Reverse Array
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Original array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Reverse array
    for (int i = 0; i < size / 2; i++) {
        // Swap elements
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
    
    cout << "Reversed array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Example 5: Count Occurrences
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {2, 5, 3, 2, 8, 2, 6, 2, 9, 2};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int target;
    int count = 0;
    
    cout << "Enter number to count: ";
    cin >> target;
    
    // Count occurrences
    for (int i = 0; i < size; i++) {
        if (numbers[i] == target) {
            count++;
        }
    }
    
    cout << target << " appears " << count << " times in array" << endl;
    
    // Show positions
    cout << "Positions: ";
    for (int i = 0; i < size; i++) {
        if (numbers[i] == target) {
            cout << i << " ";
        }
    }
    cout << endl;
    
    return 0;
}
```

## Access Patterns

### Forward Access
```cpp
int arr[5] = {10, 20, 30, 40, 50};

for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";  // 10 20 30 40 50
}
```

### Backward Access
```cpp
int arr[5] = {10, 20, 30, 40, 50};

for (int i = 4; i >= 0; i--) {
    cout << arr[i] << " ";  // 50 40 30 20 10
}
```

### Step Access
```cpp
int arr[10] = {0,1,2,3,4,5,6,7,8,9};

// Every 2nd element
for (int i = 0; i < 10; i += 2) {
    cout << arr[i] << " ";  // 0 2 4 6 8
}
```

### Conditional Access
```cpp
int arr[10] = {1,2,3,4,5,6,7,8,9,10};

// Access only even numbers
for (int i = 0; i < 10; i++) {
    if (arr[i] % 2 == 0) {
        cout << arr[i] << " ";  // 2 4 6 8 10
    }
}
```

## Access with Different Data Types

### Character Array
```cpp
#include <iostream>
using namespace std;

int main() {
    char letters[] = {'H', 'e', 'l', 'l', 'o'};
    int size = sizeof(letters) / sizeof(letters[0]);
    
    cout << "Characters: ";
    for (int i = 0; i < size; i++) {
        cout << letters[i] << " ";
    }
    cout << endl;
    
    // Convert to uppercase
    for (int i = 0; i < size; i++) {
        letters[i] = toupper(letters[i]);
    }
    
    cout << "Uppercase: ";
    for (int i = 0; i < size; i++) {
        cout << letters[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### String Array
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string fruits[] = {"apple", "banana", "orange", "grape"};
    int size = sizeof(fruits) / sizeof(fruits[0]);
    
    cout << "Fruits:" << endl;
    for (int i = 0; i < size; i++) {
        cout << i << ": " << fruits[i] << endl;
    }
    
    // Modify an element
    fruits[2] = "kiwi";
    cout << "\nAfter change:" << endl;
    for (int i = 0; i < size; i++) {
        cout << i << ": " << fruits[i] << endl;
    }
    
    return 0;
}
```

### Double Array
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double prices[] = {9.99, 19.99, 29.99, 39.99, 49.99};
    int size = sizeof(prices) / sizeof(prices[0]);
    
    cout << fixed << setprecision(2);
    cout << "Prices:" << endl;
    
    double total = 0;
    for (int i = 0; i < size; i++) {
        cout << "$" << prices[i] << endl;
        total += prices[i];
    }
    
    cout << "Total: $" << total << endl;
    cout << "Average: $" << total / size << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Index Out of Bounds
```cpp
int arr[5] = {1, 2, 3, 4, 5};

// Wrong - accessing beyond array
cout << arr[5];  // Index 5 doesn't exist (0-4 only)

// Correct
for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}
```

### Mistake 2: Off-by-One Errors
```cpp
int arr[5] = {10, 20, 30, 40, 50};

// Wrong - skips last element
for (int i = 0; i < 4; i++) {  // Should be i < 5
    cout << arr[i] << " ";  // Prints 10 20 30 40 only
}

// Correct
for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}
```

### Mistake 3: Using Uninitialized Elements
```cpp
int arr[5];  // Contains garbage

// Wrong - reading garbage
cout << arr[0];  // Prints random value

// Correct - initialize first
arr[0] = 10;
cout << arr[0];
```

### Mistake 4: Wrong Index Variable
```cpp
int arr[5] = {1, 2, 3, 4, 5};

// Wrong - using wrong variable
for (int i = 0; i < 5; j++) {  // j not declared
    cout << arr[i] << " ";
}

// Correct
for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}
```

### Mistake 5: Array Decay in Functions
```cpp
void printArray(int arr[]) {
    // Wrong - sizeof doesn't work here
    int size = sizeof(arr) / sizeof(arr[0]);  // Wrong!
    
    // Correct - pass size as parameter
}

int main() {
    int arr[5] = {1,2,3,4,5};
    // Always pass size along with array
}
```

## Access with Pointers

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    
    // Array name is pointer to first element
    cout << "Using array indexing:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    
    cout << "\nUsing pointer arithmetic:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "*(arr + " << i << ") = " << *(arr + i) << endl;
    }
    
    return 0;
}
```

## Quick Reference

| Access Pattern | Code | Result |
|----------------|------|--------|
| First element | `arr[0]` | First value |
| Last element | `arr[size-1]` | Last value |
| All elements | `for(i=0; i<size; i++)` | Loop through |
| Range-based | `for(int x : arr)` | C++11 style |
| Pointer access | `*(arr + i)` | Same as arr[i] |

## Summary

- **Array elements** accessed using index in brackets `[]`
- Index starts at **0**, ends at **size-1**
- Can **read** values: `x = arr[i]`
- Can **write** values: `arr[i] = x`
- Use loops for bulk access
- **Range-based for** loops for simple iteration
- Watch for **index out of bounds** errors
- Arrays are **0-indexed** (first element at position 0)
- Can access forward, backward, or with steps
- Always know your array size

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    // Reading all elements
    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Modifying elements
    cout << "Doubling elements..." << endl;
    for (int i = 0; i < size; i++) {
        numbers[i] *= 2;
    }
    
    // Reading after modification
    cout << "After doubling: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Access specific element
    int index;
    cout << "Enter index to access (0-" << size-1 << "): ";
    cin >> index;
    
    if (index >= 0 && index < size) {
        cout << "Element at index " << index << " = " << numbers[index] << endl;
    } else {
        cout << "Invalid index!" << endl;
    }
    
    return 0;
}
```

---
* This documentation belongs to https://github.com/InterCentury*