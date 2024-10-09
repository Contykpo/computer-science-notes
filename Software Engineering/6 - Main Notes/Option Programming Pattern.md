
2024-09-14 10:39

Status: #In-Production

Tags: #Option-Pattern #Builder-Pattern #Design-Pattern 

# Option Pattern

The #Option-Pattern is a design pattern used in programming to represent the presence or absence of a value, helping avoid null references. Typically, it's implemented using two distinct types:

- `Some(value)`: represents a valid value.
- `None`: represents the absence of a value.

#### Key Advantages of the Option Pattern:

- **Null Safety**: It avoids the risk of null pointer exceptions by explicitly representing absent values with `None`, making the absence of a value intentional and safer to handle.
- **Clearer Code**: It forces developers to handle both cases (value or absence), reducing errors that might arise from null mismanagement.
- **Chaining and Functional Programming**: Many languages (e.g., Scala, Rust) allow easy chaining of operations on `Option` values without worrying about null checks.

#### Implementations in Popular Languages:

In **C++**, the #Option-Pattern is implemented using `std::optional` (introduced in C++17). `std::optional` allows values to either hold a valid value or indicate the absence of one.

```
#include <optional>
#include <iostream>

std::optional<int> getValue(bool returnValue)
{
    if (returnValue)
        return 42; // returning a valid value
    else
        return std::nullopt; // no value
}

int main()
{
    std::optional<int> optValue = getValue(true);
    
    if (optValue)
    {
        std::cout << "Value is: " << *optValue << std::endl;
    } else
    {
        std::cout << "No value." << std::endl;
    }
}
```

- `std::optional` allows you to avoid null pointers.
- It forces the user to check if the value exists before using it, promoting safer code.

In **C#**, **Nullable Types** (`Nullable<T>`) serve a similar purpose to the **Option Pattern**, especially for ***value types***. For ***reference types***, **nullable reference types** introduced in C# 8.0 also offer some safety.
**Nullable Value Types**:
```
int? GetValue(bool returnValue)
{
    if (returnValue)
        return 42;
    else
        return null; // no value
}

var value = GetValue(true);

if (value.HasValue)
	Console.WriteLine($"Value is: {value.Value}");    
else
	Console.WriteLine("No value.");
```
**Nullable Reference Types (C# 8.0+):**
```
#nullable enable
string? GetString(bool returnString)
{
    if (returnString)
        return "Hello, World!";
    else
        return null;
}

var result = GetString(false);

if (result != null)
    Console.WriteLine($"String is: {result}");
else
    Console.WriteLine("No string returned.");
```

- **Nullable value types** (`T?`) and **nullable reference types** (`string?`) help eliminate null pointer exceptions.
- Nullable types enforce checks before accessing values.

**Rust** provides the most canonical form of the **Option Pattern** using its built-in `Option` enum. This pattern is deeply ingrained in Rust, where `null` does not exist by design.

```
fn get_value(return_value: bool) -> Option<i32>
{
    if return_value
        Some(42) // returning a valid value
	else
        None // no value
}

fn main()
{
    let opt_value = get_value(true);
    // Pattern matching:
    match opt_value
    {
        Some(val) => println!("Value is: {}", val),
        None => println!("No value."),
    }
}
```

- `Option<T>` is part of the standard library and is heavily used in Rust for nullable types.
- Rust enforces safe handling of optional values through exhaustive ***pattern matching*** (e.g., using `match`).

# Avoid Nulls: Option Pattern vs. Builder Pattern

**Option Pattern**: Primarily used to represent missing or optional values, especially in cases where a value might not always be present, like when dealing with nullable fields. It’s focused on reducing the use of nulls by providing explicit handling of absence.

**Builder Pattern**: Focused on constructing complex objects step-by-step, often used when there are many optional or required parameters. It prevents the problem of constructor overloads but doesn’t inherently handle null values unless designed explicitly for that.


# References

- (Link Source material) with [[]].
