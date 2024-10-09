
2024-09-11 14:00

Status: #In-Production

Tags: #Programming-Pattern #Adapter-Pattern #Design-Pattern

# Adapter Pattern

The #Adapter-Pattern converts the interface of a class into another interface that clients expect. This design pattern lets classes work together that couldn't otherwise because of incompatible interface.
It acts as a bridge between two incompatible interfaces, enabling objects with different interfaces to collaborate. The Adapter pattern wraps an existing class with a new interface, making it compatible with the client's expectations.

- **Compatibility**: Allows classes with incompatible interfaces to work together.
- **Wrapper**: The Adapter pattern wraps an existing class to provide a new interface.
- **Reusability**: Promotes code reusability by allowing the integration of existing components without modifying their source code.
- **Single Responsibility Principle**: Separates the interface or data conversion code from the actual business logic.

#### When to use the Adapter Pattern:

- **Integrating Legacy Code**: When you have to use existing classes whose interfaces are not compatible with the rest of your system.
- **Third-Party Library Integration**: When you want to use a third-party library but its interface does not match what your application expects.
- **Reusable Components**: When you want to create reusable components that work with various unrelated classes.

#### Benefits:

- **Single Responsibility Principle**: Separates the interface or data conversion code from the actual business logic.
- **Open/Closed Principle**: New adapters can be introduced without modifying existing code.
- **Flexibility**: Object adapters can work with multiple adaptees.

#### Drawbacks:

- **Increased Complexity**: Introducing additional classes can add complexity to the codebase.
- **All Classes Must Follow the Target Interface**: If many classes need to be adapted, creating numerous adapters may become cumbersome.

# Types of Adapters

#### Class Adapter using inheritance:

The Adapter inherits from both the **Adaptee** (the class with the existing interface) and the **Target** (the class with the desired interface). This method requires multiple inheritance, which is not supported in some languages like Java, but is possible in languages like C++, C#.

```
// Target interface
interface Target
{
    void request();
}

// Adaptee: Existing class with a different interface
class Adaptee
{
    void specificRequest()
    {
        System.out.println("Called specificRequest()");
    }
}

// Adapter class
class Adapter extends Adaptee implements Target
{
    @Override
    public void request()
    {
        specificRequest(); // Adapts Adaptee's method to Target's method
    }
}
```

#### Object Adapter using composition:

The Adapter contains an instance of the **Adaptee** and implements the **Target** interface. It translates requests to the Adaptee by delegation. This method does not require multiple inheritance and is more flexible because it allows changing the Adaptee dynamically.

```
// Target interface
interface Target
{
    void request();
}

// Existing class with a different interface (Adaptee)
class Adaptee {
    void specificRequest()
    {
        System.out.println("Called specificRequest()");
    }
}

// Adapter class
class Adapter implements Target
{
    private Adaptee adaptee;

    public Adapter(Adaptee adaptee)
    {
        this.adaptee = adaptee;
    }

    @Override
    public void request()
    {
        adaptee.specificRequest(); // Adapts Adaptee's method to Target's method
    }
}
```


# References

- (Link Source material) with [[]].
