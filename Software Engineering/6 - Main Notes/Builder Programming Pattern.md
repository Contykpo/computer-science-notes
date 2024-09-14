
2024-09-14 10:39

Status: #In-Production

Tags: #Builder-Pattern #Whole-Objects #Valid-Objects #Factory-Method-Pattern#Singleton-Pattern

# Builder Pattern

The #Builder-Pattern is a creational design pattern used to construct complex objects step by step, allowing more control over the construction process.
The **builder pattern** separates the creation of an object from its representation, making it easier to create different representations or configurations of the same object.

#### Advantages of the Builder Pattern:

1. **Readable Code**: By providing a fluent API, the builder makes it clear what’s being set. No need for complex constructors with multiple parameters.
2. **Object Customization**: Builders offer flexibility in creating objects. Instead of passing all arguments upfront, you can set optional or required fields incrementally.
3. **Handling Optional Parameters**: The builder pattern provides an excellent alternative to telescoping constructors (constructors with numerous parameters), avoiding the need for null values or default parameters.
4. ***Single Responsibility Principle***: **Encapsulation of Construction Logic**: The logic for constructing the object is encapsulated in the builder, keeping the code clean and separate from the object's functionality.
5. **Prevents Inconsistent Objects**: Since the object is constructed through controlled steps, you can ensure that it’s always in a valid state ( #Valid-Objects ) by validating required fields in the builder.

# Components of the Builder Design Pattern

#### Product:

The Product is the complex object that the Builder pattern is responsible for constructing.

- It may consist of multiple components or parts, and its structure can vary based on the implementation.
- The Product is typically a class with attributes representing the different parts that the Builder constructs.

#### Builder:

The Builder is an interface or an abstract class that declares the construction steps for building a complex object.

- It typically includes methods for constructing individual parts of the product.
- By defining an interface, the Builder allows for the creation of different concrete builders that can produce variations of the product.

#### Concrete-Builder:

Concrete-Builder classes implement the Builder interface, providing specific implementations for building each part of the product.

- Each Concrete-Builder is tailored to create a specific variation of the product.
- It keeps track of the product being constructed and provides methods for setting or constructing each part.

#### Director:

The Director is responsible for managing the construction process of the complex object.

- It collaborates with a Builder, but it doesn’t know the specific details about how each part of the object is constructed.
- It provides a high-level interface for constructing the product and managing the steps needed to create the complex object.

#### Client:

The Client is the code that initiates the construction of the complex object.

- It creates a Builder object and passes it to the Director to initiate the construction process.
- The Client may retrieve the final product from the Builder after construction is complete.

# Applicability of the Builder Pattern

- Use the Builder pattern to get rid of a “telescoping constructor”.
- Use the Builder pattern when you want your code to be able to create different representations of some product (for example, stone and wooden houses).
- Use the Builder to construct [Composite](https://refactoring.guru/design-patterns/composite) trees or other complex objects.

# Relations with Other Patterns

- Many designs start by using [Factory Method](https://refactoring.guru/design-patterns/factory-method) (less complicated and more customizable via subclasses) and evolve toward [Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory), [Prototype](https://refactoring.guru/design-patterns/prototype), or [Builder](https://refactoring.guru/design-patterns/builder) (more flexible, but more complicated).
- [Builder](https://refactoring.guru/design-patterns/builder) focuses on constructing complex objects step by step. [Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory) specializes in creating families of related objects. _Abstract Factory_ returns the product immediately, whereas _Builder_ lets you run some additional construction steps before fetching the product.
- You can use [Builder](https://refactoring.guru/design-patterns/builder) when creating complex [Composite](https://refactoring.guru/design-patterns/composite) trees because you can program its construction steps to work recursively.
- You can combine [Builder](https://refactoring.guru/design-patterns/builder) with [Bridge](https://refactoring.guru/design-patterns/bridge): the director class plays the role of the abstraction, while different builders act as implementations.
- [Abstract Factories](https://refactoring.guru/design-patterns/abstract-factory), [Builders](https://refactoring.guru/design-patterns/builder) and [Prototypes](https://refactoring.guru/design-patterns/prototype) can all be implemented as [Singletons](https://refactoring.guru/design-patterns/singleton).

# References

Further information on the Builder Pattern, as well as interesting **code examples** and **models**: 

- [Builder](https://refactoring.guru/design-patterns/builder).
- [The Builder Design Pattern](https://www.geeksforgeeks.org/builder-design-pattern/).
- [[SOLID Principles of Object Oriented Programming]].
