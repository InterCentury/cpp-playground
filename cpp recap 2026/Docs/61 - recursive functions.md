# 61 - Recursive Functions in C++

## What is Recursion?
Recursion is a programming technique where a function calls itself to solve a problem by breaking it down into smaller, similar subproblems. Each recursive call works on a smaller instance until reaching a base case that stops the recursion.

## Basic Structure of Recursion

```cpp
return_type function_name(parameters) {
    // Base case - stops recursion
    if (condition) {
        return base_value;
    }
    
    // Recursive case - function calls itself
    return function_name(modified_parameters);
}
```

## Simple Example - Factorial

```cpp
#include <iostream>
using namespace std;

int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

int main() {
    cout << "5! = " << factorial(5) << endl;  // 5 * 4 * 3 * 2 * 1 = 120
    cout << "10! = " << factorial(10) << endl;
    
    return 0;
}
```

## How Recursion Works (Call Stack)

```cpp
#include <iostream>
using namespace std;

int factorial(int n) {
    cout << "Entering factorial(" << n << ")" << endl;
    
    if (n <= 1) {
        cout << "Base case: factorial(1) = 1" << endl;
        return 1;
    }
    
    int result = n * factorial(n - 1);
    cout << "factorial(" << n << ") = " << result << endl;
    return result;
}

int main() {
    factorial(5);
    return 0;
}
```

## Common Recursive Examples

### Example 1: Fibonacci Sequence
```cpp
#include <iostream>
using namespace std;

int fibonacci(int n) {
    // Base cases
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    cout << "Fibonacci numbers:" << endl;
    for (int i = 0; i <= 10; i++) {
        cout << "F(" << i << ") = " << fibonacci(i) << endl;
    }
    
    return 0;
}
```

### Example 2: Sum of Numbers
```cpp
#include <iostream>
using namespace std;

int sum(int n) {
    // Base case
    if (n <= 0) return 0;
    
    // Recursive case
    return n + sum(n - 1);
}

int main() {
    cout << "Sum of 1 to 10: " << sum(10) << endl;
    cout << "Sum of 1 to 100: " << sum(100) << endl;
    
    return 0;
}
```

### Example 3: Power Function
```cpp
#include <iostream>
using namespace std;

double power(double base, int exponent) {
    // Base cases
    if (exponent == 0) return 1;
    if (exponent == 1) return base;
    
    // Recursive case
    if (exponent > 0) {
        return base * power(base, exponent - 1);
    } else {
        return 1 / power(base, -exponent);
    }
}

int main() {
    cout << "2^5 = " << power(2, 5) << endl;
    cout << "2^-2 = " << power(2, -2) << endl;
    cout << "10^0 = " << power(10, 0) << endl;
    
    return 0;
}
```

## Practical Examples

### Example 1: String Palindrome
```cpp
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string& str, int start, int end) {
    // Base case - single character or empty
    if (start >= end) {
        return true;
    }
    
    // Check first and last characters
    if (str[start] != str[end]) {
        return false;
    }
    
    // Recursive case - check inner substring
    return isPalindrome(str, start + 1, end - 1);
}

int main() {
    string words[] = {"racecar", "hello", "madam", "world", "level"};
    
    for (const string& word : words) {
        if (isPalindrome(word, 0, word.length() - 1)) {
            cout << word << " is a palindrome" << endl;
        } else {
            cout << word << " is not a palindrome" << endl;
        }
    }
    
    return 0;
}
```

### Example 2: Binary Search
```cpp
#include <iostream>
using namespace std;

int binarySearch(int arr[], int left, int right, int target) {
    // Base case - not found
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    // Found
    if (arr[mid] == target) {
        return mid;
    }
    
    // Recursive case - search left or right half
    if (arr[mid] > target) {
        return binarySearch(arr, left, mid - 1, target);
    } else {
        return binarySearch(arr, mid + 1, right, target);
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int targets[] = {7, 12, 1, 19, 20};
    
    for (int target : targets) {
        int index = binarySearch(arr, 0, size - 1, target);
        if (index != -1) {
            cout << target << " found at index " << index << endl;
        } else {
            cout << target << " not found" << endl;
        }
    }
    
    return 0;
}
```

### Example 3: Tower of Hanoi
```cpp
#include <iostream>
using namespace std;

void towerOfHanoi(int n, char source, char auxiliary, char destination) {
    // Base case
    if (n == 1) {
        cout << "Move disk 1 from " << source << " to " << destination << endl;
        return;
    }
    
    // Move n-1 disks from source to auxiliary
    towerOfHanoi(n - 1, source, destination, auxiliary);
    
    // Move largest disk from source to destination
    cout << "Move disk " << n << " from " << source << " to " << destination << endl;
    
    // Move n-1 disks from auxiliary to destination
    towerOfHanoi(n - 1, auxiliary, source, destination);
}

int main() {
    int disks = 3;
    cout << "Tower of Hanoi with " << disks << " disks:" << endl;
    towerOfHanoi(disks, 'A', 'B', 'C');
    
    return 0;
}
```

### Example 4: GCD (Greatest Common Divisor)
```cpp
#include <iostream>
using namespace std;

int gcd(int a, int b) {
    // Base case
    if (b == 0) {
        return a;
    }
    
    // Recursive case - Euclidean algorithm
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    cout << "GCD of 48 and 18: " << gcd(48, 18) << endl;
    cout << "GCD of 100 and 35: " << gcd(100, 35) << endl;
    cout << "GCD of 17 and 19: " << gcd(17, 19) << endl;
    cout << "LCM of 12 and 18: " << lcm(12, 18) << endl;
    
    return 0;
}
```

### Example 5: Reverse String
```cpp
#include <iostream>
#include <string>
using namespace std;

void reverseString(string& str, int left, int right) {
    // Base case
    if (left >= right) {
        return;
    }
    
    // Swap characters
    swap(str[left], str[right]);
    
    // Recursive case
    reverseString(str, left + 1, right - 1);
}

string reverseStringCopy(const string& str, int index) {
    // Base case
    if (index < 0) {
        return "";
    }
    
    // Recursive case
    return str[index] + reverseStringCopy(str, index - 1);
}

int main() {
    string text = "Hello World";
    
    cout << "Original: " << text << endl;
    
    // In-place reversal
    reverseString(text, 0, text.length() - 1);
    cout << "Reversed (in-place): " << text << endl;
    
    // Copy reversal
    string reversed = reverseStringCopy(text, text.length() - 1);
    cout << "Reversed (copy): " << reversed << endl;
    
    return 0;
}
```

## Tail Recursion

```cpp
#include <iostream>
using namespace std;

// Non-tail recursive factorial
int factorialNonTail(int n) {
    if (n <= 1) return 1;
    return n * factorialNonTail(n - 1);  // Multiplication after recursive call
}

// Tail recursive factorial
int factorialTail(int n, int accumulator = 1) {
    if (n <= 1) return accumulator;
    return factorialTail(n - 1, n * accumulator);  // Recursive call is last operation
}

int main() {
    cout << "Non-tail: " << factorialNonTail(5) << endl;
    cout << "Tail: " << factorialTail(5) << endl;
    
    return 0;
}
```

## Recursion vs Iteration

```cpp
#include <iostream>
#include <chrono>
using namespace std;

// Recursive Fibonacci
int fibRecursive(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// Iterative Fibonacci
int fibIterative(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n = 40;
    
    auto start = chrono::high_resolution_clock::now();
    int result1 = fibRecursive(n);
    auto end = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    start = chrono::high_resolution_clock::now();
    int result2 = fibIterative(n);
    end = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Fibonacci(" << n << ") = " << result1 << endl;
    cout << "Recursive time: " << time1.count() << " ms" << endl;
    cout << "Iterative time: " << time2.count() << " ms" << endl;
    
    return 0;
}
```

## Common Recursive Patterns

### Pattern 1: Linear Recursion
```cpp
void linearRecursion(int n) {
    if (n <= 0) return;
    cout << n << " ";
    linearRecursion(n - 1);
}
// Output: 5 4 3 2 1
```

### Pattern 2: Binary Recursion (Two Calls)
```cpp
int binaryRecursion(int n) {
    if (n <= 1) return n;
    return binaryRecursion(n - 1) + binaryRecursion(n - 2);
}
```

### Pattern 3: Tree Recursion
```cpp
void treeRecursion(int n) {
    if (n <= 0) return;
    cout << n << " ";
    treeRecursion(n - 1);
    treeRecursion(n - 1);
}
// For n=3: 3 2 1 1 2 1 1
```

### Pattern 4: Nested Recursion
```cpp
int nestedRecursion(int n) {
    if (n > 100) return n - 10;
    return nestedRecursion(nestedRecursion(n + 11));
}
```

## Common Mistakes

### Mistake 1: Missing Base Case
```cpp
// WRONG - no base case
int infiniteRecursion(int n) {
    return infiniteRecursion(n - 1);  // Infinite loop!
}

// CORRECT
int factorial(int n) {
    if (n <= 1) return 1;  // Base case
    return n * factorial(n - 1);
}
```

### Mistake 2: Incorrect Base Case
```cpp
// WRONG - base case condition wrong
int sum(int n) {
    if (n == 0) return 0;  // OK
    if (n < 0) return 0;   // Handle negative
    return n + sum(n - 2);  // Wrong - skips numbers
}

// CORRECT
int sum(int n) {
    if (n <= 0) return 0;
    return n + sum(n - 1);
}
```

### Mistake 3: Not Modifying Parameters
```cpp
// WRONG - parameter never changes
int countdown(int n) {
    if (n <= 0) return 0;
    cout << n << " ";
    return countdown(n);  // Infinite recursion!
}

// CORRECT
int countdown(int n) {
    if (n <= 0) return 0;
    cout << n << " ";
    return countdown(n - 1);  // Decrement parameter
}
```

### Mistake 4: Stack Overflow
```cpp
// WRONG - too deep recursion
int deepRecursion(int n) {
    if (n <= 0) return 0;
    return 1 + deepRecursion(n - 1);
}

int main() {
    deepRecursion(1000000);  // Stack overflow!
    return 0;
}
```

## Recursion vs Iteration Comparison

| Aspect | Recursion | Iteration |
|--------|-----------|-----------|
| Code clarity | Clean for tree structures | Clean for linear problems |
| Memory usage | Uses stack for each call | Constant memory |
| Performance | Overhead of function calls | Usually faster |
| Risk | Stack overflow | Infinite loop |
| Best for | Tree traversal, divide & conquer | Simple loops, linear algorithms |

## When to Use Recursion

### ✅ Good Candidates
- Tree/Graph traversal
- Divide and conquer algorithms
- Backtracking problems
- Mathematical definitions (factorial, Fibonacci)
- Problems with recursive structure

### ❌ Poor Candidates
- Simple loops (sum of numbers)
- Performance-critical code
- Large depth problems (risk of stack overflow)
- When iterative solution is simpler

## Quick Reference

| Pattern | Description |
|---------|-------------|
| Base case | Stops recursion |
| Recursive case | Function calls itself |
| Linear recursion | One recursive call |
| Binary recursion | Two recursive calls |
| Tail recursion | Recursive call is last operation |
| Mutual recursion | Functions call each other |

## Summary

- **Recursion** is a function calling itself
- Must have a **base case** to stop recursion
- Each call works on **smaller** subproblem
- Uses **call stack** to track recursive calls
- **Stack overflow** risk for deep recursion
- **Elegant** for tree structures and divide & conquer
- Often **slower** and uses more memory than iteration
- **Tail recursion** can be optimized by compiler
- **Memoization** can optimize repeated calculations

## Basic Template
```cpp
#include <iostream>
using namespace std;

// Recursive function structure
int recursiveFunction(int n) {
    // Base case - stop condition
    if (n <= 0) {
        return 0;
    }
    
    // Processing (optional)
    cout << "Processing: " << n << endl;
    
    // Recursive case - call with smaller parameter
    return n + recursiveFunction(n - 1);
}

// Classic recursion examples
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void printCountdown(int n) {
    if (n <= 0) {
        cout << "Blast off!" << endl;
        return;
    }
    cout << n << "... ";
    printCountdown(n - 1);
}

int main() {
    cout << "Sum of 1-5: " << recursiveFunction(5) << endl;
    cout << "Factorial of 5: " << factorial(5) << endl;
    cout << "Fibonacci(10): " << fibonacci(10) << endl;
    
    cout << "Countdown: ";
    printCountdown(5);
    
    return 0;
}
```

---
*This documentation belongs to https://github.com/InterCentury*