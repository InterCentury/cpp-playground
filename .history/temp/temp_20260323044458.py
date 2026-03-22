import os

# Target directory (your custom path)
base_path = r"H:\programming\git_and_github\cpp-playground\temp"

# Create folder if it doesn't exist
os.makedirs(base_path, exist_ok=True)

# List of filenames
files = [
    "110 - overloading binary operators.md",
    "111 - overloading unary operators.md",
    "112 - overloading assignment operator.md",
    "113 - overloading stream operators (<<, >>).md",
    "114 - overloading comparison operators.md",
    "115 - overloading subscript operator [].md",
    "116 - new and delete for objects.md",
    "117 - new and delete for arrays.md",
    "118 - shallow copy.md",
    "119 - deep copy.md",
    "120 - Rule of Three.md",
    "121 - copy constructor implementation.md",
    "122 - assignment operator implementation.md",
    "123 - destructor implementation.md",
    "124 - static member variables.md",
    "125 - static member functions.md",
    "126 - static objects.md",
    "127 - nested classes.md",
    "128 - local classes.md",
    "129 - composition (has-a relationship).md",
    "130 - aggregation.md",
    "131 - namespaces.md",
    "132 - const objects.md",
    "133 - mutable members.md",
    "134 - explicit keyword.md"
]

# Create files
for file_name in files:
    file_path = os.path.join(base_path, file_name)
    
    with open(file_path, "w", encoding="utf-8") as f:
        f.write(f"# {file_name.replace('.md', '')}\n\n")
    
    print(f"Created: {file_name}")

print("\nAll files created successfully! 🎉")