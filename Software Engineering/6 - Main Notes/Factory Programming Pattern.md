
2024-09-14 12:19

Status: #In-Production

Tags: #Factory-Method-Pattern 

# Factory Method

**Factory Method** is a creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created. Instead of instantiating objects directly, the pattern delegates the instantiation to subclasses, promoting loose coupling and flexibility.
The #Factory-Method-Pattern suggests that you replace direct object construction calls (using the `new` operator) with calls to a special _factory_ method.

#### Pros and Cons:

-  You avoid tight coupling between the creator and the concrete products.
-  **_Single Responsibility Principle_**. You can move the product creation code into one place in the program, making the code easier to support.
-  **_Open/Closed Principle_**. You can introduce new types of products into the program without breaking existing client code.

- The **code may become more complicated** since you need to introduce a lot of new subclasses to implement the pattern. The best case scenario is when you’re introducing the pattern into an existing hierarchy of creator classes.

# Factory Method Structure

#### Product:

The **Product** declares the interface, which is common to all objects that can be produced by the creator and its subclasses.

#### Concrete-Product:

**Concrete Products** are different implementations of the product interface.

#### Creator:

The **Creator** class declares the factory method that returns new product objects. It’s important that the return type of this method matches the product interface.
You can declare the factory method as `abstract` to force all subclasses to implement their own versions of the method. As an alternative, the base factory method can return some default product type.

#### Concrete-Creator:

**Concrete Creators** override the base factory method so it returns a different type of product.

# Applicability of the Factory Method

- Use the Factory Method when you don’t know beforehand the exact types and dependencies of the objects your code should work with.
- Use the Factory Method when you want to provide users of your library or framework with a way to extend its internal components.
- Use the Factory Method when you want to save system resources by reusing existing objects instead of rebuilding them each time.
- When a class can't anticipate the type of objects it needs to create.
- When the creation process needs to be delegated to subclasses.
- When you want to avoid tightly coupling the code to specific classes.

# Relations with Other Patterns

- Many designs start by using [Factory Method](https://refactoring.guru/design-patterns/factory-method) (less complicated and more customizable via subclasses) and evolve toward [Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory), [Prototype](https://refactoring.guru/design-patterns/prototype), or [Builder](https://refactoring.guru/design-patterns/builder) (more flexible, but more complicated).
	- **Factory Method**: Focuses on creating one type of product (object).
	- **Abstract Factory**: Focuses on creating families of related products.


# References

- [Factory Method](https://refactoring.guru/design-patterns/factory-method).
- [Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory).
