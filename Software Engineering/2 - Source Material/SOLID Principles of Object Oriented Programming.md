The SOLID principle helps in reducing tight coupling. Tight coupling means a group of classes are highly dependent on one another which you should avoid in your code.

- Opposite of tight coupling is loose coupling and your code is considered as a good code when it has loosely-coupled classes.
- Loosely coupled classes minimize changes in your code, helps in making code more reusable, maintainable, flexible and stable.

#### 1. Single Responsibility Principle:

**A class should have only one reason to change**, which means every class should have a single responsibility or single job or single purpose. In other words, a class should have only one job or purpose within the software system.

#### 2. Open / Closed Principle:

**Software entities** (classes, modules, functions, etc.) **should be open for extension**, but **closed for modification** which means you should be able to extend a class behavior, without modifying it.

#### 3. Liskov’s Substitution Principle:

**Derived or child classes must be substitutable for their base or parent classes**. This principle ensures that any class that is the child of a parent class should be usable in place of its parent without any unexpected behavior.

#### 4. Interface Segregation Principle:

The first principle that **applies to Interfaces instead of classes** in SOLID, similar to the **single responsibility principle**. It states:
**Do not force any client to implement an interface which is irrelevant to them**. Here your main goal is to focus on avoiding fat interface and give preference to many **small client-specific interfaces**. You should prefer many client interfaces rather than one general interface and each interface should have a specific responsibility.

#### 5. Dependency Inversion Principle:

**High-level modules should not depend on low-level modules. Both should depend on abstractions**. Additionally, abstractions should not depend on details. Details should depend on abstractions.

- In simpler terms, the **DIP** suggests that classes should rely on abstractions (e.g., interfaces or abstract classes) rather than concrete implementations.
- This allows for more flexible and decoupled code, making it easier to change implementations without affecting other parts of the codebase.


# References

- [SOLID Principles in OOP](https://www.geeksforgeeks.org/solid-principle-in-programming-understand-with-real-life-examples/).