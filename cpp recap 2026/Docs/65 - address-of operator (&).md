# 65 - Address-of Operator (&) in C++

## What is the Address-of Operator?
The address-of operator `&` returns the memory address of a variable. It tells you where in memory the variable is stored.

## Basic Syntax

```cpp
&variable_name
```

## Simple Example

```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 25;
    
    cout << "Value: " << age << endl;
    cout << "Address: " << &age << endl;
    
    return 0;
}
```

## The Confusing Part: `&` in Different Contexts

The ampersand `&` has different meanings in different contexts:

| Context | Meaning | Example |
|---------|---------|---------|
| Address-of | Get memory address | `&variable` |
| Reference declaration | Declare reference | `int& ref = var;` |
| Bitwise AND | Bitwise operation | `a & b` |
| Logical AND | Logical operation | `a && b` |

## Address-of in Action

### Getting Address of Different Data Types

```cpp
#include <iostream>
using namespace std;

int main() {
    int intVar = 10;
    double doubleVar = 3.14;
    char charVar = 'A';
    bool boolVar = true;
    
    cout << "Address of int: " << &intVar << endl;
    cout << "Address of double: " << &doubleVar << endl;
    cout << "Address of char: " << (void*)&charVar << endl;  // Cast needed for char*
    cout << "Address of bool: " << &boolVar << endl;
    
    return 0;
}
```

### Storing Address in a Pointer

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* ptr = &value;  // Store address of value in pointer
    
    cout << "Value: " << value << endl;
    cout << "Address: " << &value << endl;
    cout << "Pointer holds: " << ptr << endl;
    cout << "Pointer dereferenced: " << *ptr << endl;
    
    return 0;
}
```

## Address-of with Different Variable Types

### Local Variables
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int b = 20;
    
    cout << "Address of a: " << &a << endl;
    cout << "Address of b: " << &b << endl;
    
    // Local variables are stored on the stack
    // Addresses are typically close together
    
    return 0;
}
```

### Global Variables
```cpp
#include <iostream>
using namespace std;

int globalVar = 100;
const double PI = 3.14159;

int main() {
    cout << "Address of globalVar: " << &globalVar << endl;
    cout << "Address of PI: " << &PI << endl;
    
    return 0;
}
```

### Static Variables
```cpp
#include <iostream>
using namespace std;

void function() {
    static int staticVar = 0;
    staticVar++;
    
    cout << "Static var value: " << staticVar << endl;
    cout << "Static var address: " << &staticVar << endl;
}

int main() {
    function();
    function();
    function();
    
    // Notice the address stays the same
    // Static variables have fixed address
    
    return 0;
}
```

## Address-of with Arrays

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    
    cout << "Address of array: " << arr << endl;
    cout << "Address of arr[0]: " << &arr[0] << endl;
    cout << "Address of arr[1]: " << &arr[1] << endl;
    cout << "Address of arr[2]: " << &arr[2] << endl;
    
    // arr and &arr[0] are the same
    // Each element is 4 bytes apart (on 32-bit system)
    
    cout << "\nSize difference: " << (&arr[1] - &arr[0]) << " elements" << endl;
    
    return 0;
}
```

## Address-of with String Literals

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "Hello";
    const char* cstr = "World";
    
    cout << "Address of string object: " << &str << endl;
    cout << "Address of string data: " << (void*)str.c_str() << endl;
    cout << "Address of C-string: " << (void*)cstr << endl;
    
    return 0;
}
```

## Address-of with Functions

```cpp
#include <iostream>
using namespace std;

void sayHello() {
    cout << "Hello!" << endl;
}

int add(int a, int b) {
    return a + b;
}

int main() {
    // Get address of functions
    void (*funcPtr1)() = &sayHello;
    int (*funcPtr2)(int, int) = &add;
    
    cout << "Address of sayHello: " << (void*)&sayHello << endl;
    cout << "Address of add: " << (void*)&add << endl;
    
    // Function names also act as addresses
    cout << "sayHello (without &): " << (void*)sayHello << endl;
    cout << "add (without &): " << (void*)add << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: Swapping Values Using Pointers
```cpp
#include <iostream>
using namespace std;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    cout << "Address of x: " << &x << endl;
    cout << "Address of y: " << &y << endl;
    
    swap(&x, &y);  // Pass addresses
    
    cout << "After swap: x = " << x << ", y = " << y << endl;
    
    return 0;
}
```

### Example 2: Finding Address Differences
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    
    cout << "Address of a: " << &a << endl;
    cout << "Address of b: " << &b << endl;
    cout << "Address of c: " << &c << endl;
    
    // Calculate offset
    cout << "\nOffset between a and b: " 
         << (long)&b - (long)&a << " bytes" << endl;
    cout << "Offset between b and c: " 
         << (long)&c - (long)&b << " bytes" << endl;
    
    return 0;
}
```

### Example 3: Pointer to Pointer (Double Pointer)
```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* ptr = &value;
    int** doublePtr = &ptr;  // Address of pointer
    
    cout << "Value: " << value << endl;
    cout << "Address of value: " << &value << endl;
    cout << "ptr holds: " << ptr << endl;
    cout << "Address of ptr: " << &ptr << endl;
    cout << "doublePtr holds: " << doublePtr << endl;
    cout << "**doublePtr: " << **doublePtr << endl;
    
    return 0;
}
```

### Example 4: Array of Pointers
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20, c = 30;
    int* ptrs[3];  // Array of pointers
    
    ptrs[0] = &a;
    ptrs[1] = &b;
    ptrs[2] = &c;
    
    for (int i = 0; i < 3; i++) {
        cout << "ptrs[" << i << "] points to value: " << *ptrs[i] << endl;
        cout << "Address stored: " << ptrs[i] << endl;
    }
    
    return 0;
}
```

### Example 5: Returning Address from Function (Careful!)
```cpp
#include <iostream>
using namespace std;

// DANGEROUS! Never return address of local variable
int* dangerous() {
    int x = 10;
    return &x;  // x destroyed when function ends!
}

// Safe: return address of static variable
int* safe() {
    static int x = 10;
    return &x;  // Static persists
}

int main() {
    int* ptr1 = safe();
    cout << "Safe pointer: " << *ptr1 << endl;
    
    // int* ptr2 = dangerous();  // Don't do this!
    
    return 0;
}
```

## Address-of with References vs Pointers

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 42;
    
    // Reference
    int& ref = value;
    
    // Pointer
    int* ptr = &value;
    
    cout << "Value: " << value << endl;
    cout << "Address of value: " << &value << endl;
    cout << "Address stored in ptr: " << ptr << endl;
    cout << "Address of ref: " << &ref << endl;  // &ref gives address of value
    
    // &ref returns address of referenced variable
    // &ptr returns address of pointer itself
    
    cout << "Address of pointer variable: " << &ptr << endl;
    
    return 0;
}
```

## Address-of with const

```cpp
#include <iostream>
using namespace std;

int main() {
    const int constVar = 100;
    int normalVar = 50;
    
    // Can take address of const variable
    const int* ptrToConst = &constVar;
    
    // Can also take address of normal variable
    int* ptrToNormal = &normalVar;
    
    cout << "Address of const: " << &constVar << endl;
    cout << "Address of normal: " << &normalVar << endl;
    
    return 0;
}
```

## Common Mistakes

### Mistake 1: Confusing & with Reference Declaration
```cpp
int x = 10;
int& ref = x;  // & here means reference, NOT address-of

cout << &ref << endl;  // & here means address-of (address of x)
```

### Mistake 2: Taking Address of Temporary
```cpp
// WRONG - taking address of temporary
int* ptr = &(10);  // Error! Cannot take address of literal

// CORRECT
int value = 10;
int* ptr = &value;
```

### Mistake 3: Using & Instead of &&
```cpp
// & (address-of) vs && (logical AND)
if (x & y) { }  // Bitwise AND
if (x && y) { } // Logical AND
```

### Mistake 4: Forgetting to Dereference
```cpp
int x = 10;
int* ptr = &x;

// WRONG
cout << ptr << endl;  // Prints address, not value

// CORRECT
cout << *ptr << endl; // Prints value
```

### Mistake 5: Returning Address of Local
```cpp
int* badFunction() {
    int x = 10;
    return &x;  // DANGEROUS! x destroyed after return
}
```

## Address-of vs Reference: Key Differences

| Aspect | Address-of (&) | Reference (&) |
|--------|----------------|---------------|
| Purpose | Get memory address | Create alias to variable |
| Syntax | `&variable` | `Type& ref = var;` |
| Result | Pointer | Reference (alias) |
| Nullable | Yes (nullptr) | No |
| Reassign | Can change | Cannot rebind |
| Dereference | Need `*` | Automatic |

## Visual Memory Diagram

```
Memory Layout:

Variable 'x':
┌─────────────┐
│   Address   │ 0x1000
├─────────────┤
│   Value     │ 42
└─────────────┘

Pointer 'ptr':
┌─────────────┐
│   Address   │ 0x2000
├─────────────┤
│   Value     │ 0x1000  (stores address of x)
└─────────────┘

Expression &x = 0x1000
Expression ptr = 0x2000
Expression *ptr = 42
```

## When to Use Address-of Operator

### ✅ Good Uses
```cpp
// Initializing pointers
int* ptr = &value;

// Passing to functions that need address
swap(&a, &b);

// Dynamic memory management
int* arr = new int[10];
delete[] arr;

// Working with arrays
int* ptr = &arr[0];

// Creating pointer to pointer
int** doublePtr = &ptr;
```

### ❌ Avoid
```cpp
// Taking address of literal
int* ptr = &42;  // Not allowed

// Returning address of local
int* bad() {
    int x;
    return &x;  // Never!
}

// Confusing with reference
int& ref = x;  // & here is reference, not address
```

## Quick Reference

| Expression | Meaning |
|------------|---------|
| `&var` | Address of var |
| `int* ptr = &var;` | Store address in pointer |
| `int& ref = var;` | Reference to var (different meaning) |
| `&arr[0]` | Address of first array element |
| `&ptr` | Address of pointer variable |
| `func(&a, &b);` | Pass addresses to function |

## Summary

- **Address-of operator** `&` returns memory address of variable
- Used to **initialize pointers**: `int* ptr = &value;`
- Used to **pass addresses** to functions: `swap(&a, &b);`
- Can be used with any variable (local, global, static)
- Cannot take address of **literals** or **temporaries**
- Do not confuse with **reference declaration** (also uses `&`)
- Do not confuse with **logical AND** (`&&`) or **bitwise AND** (`&`)
- Addresses are **different each run** (ASLR)
- Pointers store addresses obtained with `&`

## Basic Template
```cpp
#include <iostream>
using namespace std;

int main() {
    // Basic address-of
    int value = 42;
    cout << "Value: " << value << endl;
    cout << "Address: " << &value << endl;
    
    // Store address in pointer
    int* ptr = &value;
    cout << "Pointer holds: " << ptr << endl;
    cout << "Pointer dereferenced: " << *ptr << endl;
    
    // Multiple variables
    int a = 10, b = 20;
    cout << "\nAddress of a: " << &a << endl;
    cout << "Address of b: " << &b << endl;
    
    // Address difference
    cout << "Difference: " << (&b - &a) << " elements" << endl;
    
    // Array addresses
    int arr[3] = {1, 2, 3};
    cout << "\nAddress of arr[0]: " << &arr[0] << endl;
    cout << "Address of arr[1]: " << &arr[1] << endl;
    cout << "Address of arr[2]: " << &arr[2] << endl;
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*