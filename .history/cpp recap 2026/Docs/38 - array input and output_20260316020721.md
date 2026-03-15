# 38 - Array Input and Output in C++

## What is Array Input/Output?
Array input and output refers to reading values into an array from the user (or file) and displaying array contents to the console.

## Basic 1D Array Input/Output

### Simple Input and Output
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5];
    
    // Input
    cout << "Enter 5 numbers:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Number " << i + 1 << ": ";
        cin >> numbers[i];
    }
    
    // Output
    cout << "\nYou entered: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Input with Size from User
```cpp
#include <iostream>
using namespace std;

int main() {
    int size;
    
    cout << "Enter array size: ";
    cin >> size;
    
    int numbers[size];  // VLA - works in some compilers
    
    cout << "Enter " << size << " numbers:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "numbers[" << i << "]: ";
        cin >> numbers[i];
    }
    
    cout << "\nArray contents: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Better Approach with Fixed Maximum Size
```cpp
#include <iostream>
using namespace std;

int main() {
    const int MAX_SIZE = 100;
    int numbers[MAX_SIZE];
    int size;
    
    cout << "Enter number of elements (max " << MAX_SIZE << "): ";
    cin >> size;
    
    if (size > MAX_SIZE) {
        cout << "Size too large! Using " << MAX_SIZE << endl;
        size = MAX_SIZE;
    }
    
    cout << "Enter " << size << " numbers:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "numbers[" << i << "]: ";
        cin >> numbers[i];
    }
    
    cout << "\nArray contents: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Formatted Output

### Basic Formatting
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int numbers[] = {5, 15, 150, 1500, 15000};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    cout << "Default output:" << endl;
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    cout << "\nFormatted with setw:" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(8) << numbers[i];
    }
    cout << endl;
    
    cout << "\nWith indices:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "numbers[" << i << "] = " << setw(5) << numbers[i] << endl;
    }
    
    return 0;
}
```

### Table Format
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int ids[] = {101, 102, 103, 104, 105};
    string names[] = {"John", "Jane", "Bob", "Alice", "Charlie"};
    double scores[] = {85.5, 92.0, 78.5, 95.5, 88.0};
    int size = 5;
    
    // Table header
    cout << left << setw(10) << "ID" 
         << setw(15) << "Name" 
         << setw(10) << "Score" << endl;
    cout << string(35, '-') << endl;
    
    // Table body
    cout << fixed << setprecision(1);
    for (int i = 0; i < size; i++) {
        cout << left << setw(10) << ids[i]
             << setw(15) << names[i]
             << right << setw(8) << scores[i] << endl;
    }
    
    return 0;
}
```

## 2D Array Input/Output

### Basic 2D Input/Output
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int rows, cols;
    
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
    
    int matrix[10][10];  // Fixed max size
    
    // Input
    cout << "Enter " << rows * cols << " elements:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "matrix[" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
    
    // Output as grid
    cout << "\nMatrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
    
    return 0;
}
```

### Pretty Print 2D Array
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    cout << "Matrix display:" << endl;
    cout << "+";
    for (int j = 0; j < 4; j++) {
        cout << "-----+";
    }
    cout << endl;
    
    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < 4; j++) {
            cout << setw(4) << matrix[i][j] << " |";
        }
        cout << endl;
        
        cout << "+";
        for (int j = 0; j < 4; j++) {
            cout << "-----+";
        }
        cout << endl;
    }
    
    return 0;
}
```

## 3D Array Input/Output

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int depth = 2, rows = 3, cols = 2;
    int cube[2][3][2] = {
        {
            {1, 2},
            {3, 4},
            {5, 6}
        },
        {
            {7, 8},
            {9, 10},
            {11, 12}
        }
    };
    
    cout << "3D Array (Depth x Rows x Columns):" << endl;
    for (int d = 0; d < depth; d++) {
        cout << "\nDepth " << d << ":" << endl;
        cout << "    ";
        for (int c = 0; c < cols; c++) {
            cout << "Col" << c << "   ";
        }
        cout << endl;
        
        for (int r = 0; r < rows; r++) {
            cout << "Row" << r << ": ";
            for (int c = 0; c < cols; c++) {
                cout << setw(5) << cube[d][r][c] << " ";
            }
            cout << endl;
        }
    }
    
    return 0;
}
```

## Input Validation for Arrays

### Validate Each Input
```cpp
#include <iostream>
using namespace std;

int main() {
    int numbers[5];
    int i = 0;
    
    cout << "Enter 5 positive numbers:" << endl;
    
    while (i < 5) {
        cout << "Number " << i + 1 << ": ";
        cin >> numbers[i];
        
        if (numbers[i] > 0) {
            i++;  // Only increment if valid
        } else {
            cout << "Invalid! Enter positive number." << endl;
        }
    }
    
    cout << "\nValid numbers entered: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Input with Range Checking
```cpp
#include <iostream>
using namespace std;

int main() {
    int scores[5];
    
    cout << "Enter 5 test scores (0-100):" << endl;
    
    for (int i = 0; i < 5; i++) {
        do {
            cout << "Score " << i + 1 << ": ";
            cin >> scores[i];
            
            if (scores[i] < 0 || scores[i] > 100) {
                cout << "Invalid! Score must be 0-100." << endl;
            }
        } while (scores[i] < 0 || scores[i] > 100);
    }
    
    cout << "\nScores: ";
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Reading Multiple Values in One Line

```cpp
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    int numbers[5];
    string line;
    
    cout << "Enter 5 numbers separated by spaces: ";
    getline(cin, line);
    
    stringstream ss(line);
    int count = 0;
    
    while (ss >> numbers[count] && count < 5) {
        count++;
    }
    
    if (count != 5) {
        cout << "Only " << count << " numbers entered." << endl;
    }
    
    cout << "You entered: ";
    for (int i = 0; i < count; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Student Grades System
```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const int STUDENTS = 5;
    const int SUBJECTS = 3;
    string names[STUDENTS];
    int grades[STUDENTS][SUBJECTS];
    
    // Input student names and grades
    for (int i = 0; i < STUDENTS; i++) {
        cout << "\nStudent " << i + 1 << " name: ";
        cin >> names[i];
        
        cout << "Enter grades for Math, Science, English: ";
        for (int j = 0; j < SUBJECTS; j++) {
            cin >> grades[i][j];
        }
    }
    
    // Output grade report
    cout << "\n" << string(60, '=') << endl;
    cout << left << setw(15) << "Student"
         << setw(10) << "Math"
         << setw(10) << "Science"
         << setw(10) << "English"
         << setw(10) << "Average" << endl;
    cout << string(60, '-') << endl;
    
    for (int i = 0; i < STUDENTS; i++) {
        int sum = 0;
        cout << left << setw(15) << names[i];
        
        for (int j = 0; j < SUBJECTS; j++) {
            cout << setw(10) << grades[i][j];
            sum += grades[i][j];
        }
        
        double avg = (double)sum / SUBJECTS;
        cout << fixed << setprecision(2) << setw(10) << avg << endl;
    }
    
    return 0;
}
```

### Example 2: Matrix Input with Validation
```cpp
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    int matrix[3][3];
    
    cout << "Enter 9 integers for 3x3 matrix:" << endl;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Enter element [" << i << "][" << j << "]: ";
            
            // Validate input is integer
            while (!(cin >> matrix[i][j])) {
                cout << "Invalid input! Enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    
    // Output matrix with borders
    cout << "\nMatrix:" << endl;
    cout << "+-------------+" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < 3; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << " |" << endl;
    }
    cout << "+-------------+" << endl;
    
    return 0;
}
```

### Example 3: Dynamic Array Input with Statistics
```cpp
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    const int MAX_SIZE = 100;
    int numbers[MAX_SIZE];
    int size;
    
    // Get array size with validation
    do {
        cout << "Enter number of elements (1-" << MAX_SIZE << "): ";
        cin >> size;
        if (size < 1 || size > MAX_SIZE) {
            cout << "Invalid size! Try again." << endl;
        }
    } while (size < 1 || size > MAX_SIZE);
    
    // Input elements with validation
    cout << "Enter " << size << " integers:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Element " << i + 1 << ": ";
        while (!(cin >> numbers[i])) {
            cout << "Invalid! Enter an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    // Calculate statistics
    int sum = 0, min = numbers[0], max = numbers[0];
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
        if (numbers[i] < min) min = numbers[i];
        if (numbers[i] > max) max = numbers[i];
    }
    double avg = (double)sum / size;
    
    // Output results
    cout << "\n" << string(40, '=') << endl;
    cout << "Array Analysis Report" << endl;
    cout << string(40, '=') << endl;
    
    cout << "Elements: ";
    for (int i = 0; i < size; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    cout << fixed << setprecision(2);
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Minimum: " << min << endl;
    cout << "Maximum: " << max << endl;
    
    return 0;
}
```

## File Input/Output for Arrays

### Writing Array to File
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    ofstream outFile("array.txt");
    
    if (outFile.is_open()) {
        outFile << size << endl;  // Write size first
        for (int i = 0; i < size; i++) {
            outFile << numbers[i] << " ";
        }
        outFile.close();
        cout << "Array written to file successfully." << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
    
    return 0;
}
```

### Reading Array from File
```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    const int MAX_SIZE = 100;
    int numbers[MAX_SIZE];
    int size;
    
    ifstream inFile("array.txt");
    
    if (inFile.is_open()) {
        inFile >> size;  // Read size first
        
        if (size > MAX_SIZE) {
            cout << "File too large!" << endl;
            return 1;
        }
        
        for (int i = 0; i < size; i++) {
            inFile >> numbers[i];
        }
        inFile.close();
        
        cout << "Array read from file:" << endl;
        for (int i = 0; i < size; i++) {
            cout << numbers[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
    
    return 0;
}
```

## Common Input/Output Formats

### CSV Format Output
```cpp
#include <iostream>
using namespace std;

int main() {
    int data[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    cout << "CSV Format:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << data[i][j];
            if (j < 3) cout << ",";
        }
        cout << endl;
    }
    
    return 0;
}
```

### JSON-like Format
```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    cout << "JSON-like format:" << endl;
    cout << "{\n  \"array\": [";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]\n}" << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Not Using & with cin for Simple Variables
```cpp
int arr[5];

// Correct - & not needed for array elements
cin >> arr[0];  // arr[0] is already an lvalue

// But for simple variables, & is needed
int x;
cin >> x;  // Not &x
```

### Mistake 2: Forgetting Array Bounds
```cpp
int arr[5];

// Wrong - no bounds checking
for (int i = 0; i < 10; i++) {  // Too many inputs
    cin >> arr[i];
}

// Correct
for (int i = 0; i < 5; i++) {
    cin >> arr[i];
}
```

### Mistake 3: Not Handling Invalid Input
```cpp
int arr[5];

// Wrong - no validation
for (int i = 0; i < 5; i++) {
    cin >> arr[i];  // If user enters "abc", program breaks
}

// Better - with validation
for (int i = 0; i < 5; i++) {
    while (!(cin >> arr[i])) {
        cout << "Invalid input! Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}
```

### Mistake 4: Missing Newlines in Output
```cpp
// Wrong - everything on one line
for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}
// No endl at the end

// Correct
for (int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}
cout << endl;
```

### Mistake 5: Not Using setw for Alignment
```cpp
// Wrong - misaligned columns
cout << "Name Score" << endl;
cout << "John 85" << endl;
cout << "Alexander 92" << endl;

// Correct - using setw
cout << left << setw(10) << "Name" << "Score" << endl;
cout << left << setw(10) << "John" << 85 << endl;
cout << left << setw(10) << "Alexander" << 92 << endl;
```

## Quick Reference

| Operation | Syntax | Example |
|-----------|--------|---------|
| 1D input | `cin >> arr[i];` | `for(i=0; i<n; i++) cin >> arr[i];` |
| 1D output | `cout << arr[i];` | `for(i=0; i<n; i++) cout << arr[i] << " ";` |
| 2D input | `cin >> mat[i][j];` | Nested loops |
| 2D output | `cout << mat[i][j];` | Nested loops with endl |
| With setw | `cout << setw(w) << val;` | Align columns |
| With precision | `cout << fixed << setprecision(p);` | Decimal places |
| Input validation | `while(!(cin >> val))` | Handle errors |
| File output | `outFile << val;` | Write to file |
| File input | `inFile >> val;` | Read from file |

## Summary

- Use **loops** for array input/output
- Always know array size before input
- Validate user input to prevent errors
- Use **setw** for formatted output
- Use **fixed** and **setprecision** for decimals
- Handle invalid input with cin.clear() and cin.ignore()
- Consider file I/O for persistent storage
- Format output for readability (tables, borders)
- Watch for array bounds in input loops
- Use appropriate format for data presentation

## Basic Template
```cpp
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    const int SIZE = 5;
    int arr[SIZE];
    
    // Input with validation
    cout << "Enter " << SIZE << " integers:" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "]: ";
        while (!(cin >> arr[i])) {
            cout << "Invalid! Enter integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    // Formatted output
    cout << "\nArray contents:" << endl;
    cout << "+";
    for (int i = 0; i < SIZE; i++) {
        cout << "-----+";
    }
    cout << endl;
    
    cout << "|";
    for (int i = 0; i < SIZE; i++) {
        cout << setw(4) << arr[i] << " |";
    }
    cout << endl;
    
    cout << "+";
    for (int i = 0; i < SIZE; i++) {
        cout << "-----+";
    }
    cout << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*