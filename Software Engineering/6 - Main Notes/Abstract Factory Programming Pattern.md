
2024-09-14 15:47

Status: #In-Production

Tags: #Abstract-Factory-Pattern #Factory-Method-Pattern #Builder-Pattern

# Abstract Factory Pattern

**Abstract Factory** is a creational design pattern that lets you produce families of related objects without specifying their concrete classes.

#### Pros and Cons:

-  You can be sure that the products you’re getting from a factory are compatible with each other.
-  You avoid tight coupling between concrete products and client code.
-  **_Single Responsibility Principle_**: You can extract the product creation code into one place, making the code easier to support.
-  **_Open/Closed Principle_**: You can introduce new variants of products without breaking existing client code.

- The code may become more complicated than it should be, since a lot of new interfaces and classes are introduced along with the pattern.

# Abstract Factory Structure

#### Abstract Products:

**Abstract products** declare interfaces for a set of distinct but related products which make up a product family.

#### Concrete Products:

**Concrete Products** are various implementations of abstract products, grouped by variants. Each abstract product (chair/sofa) must be implemented in all given variants (Victorian/Modern).

#### Abstract Factory:

The **Abstract Factory** interface declares a set of methods for creating each of the abstract products.

#### Concrete Factories:

**Concrete Factories** implement creation methods of the abstract factory. Each concrete factory corresponds to a specific variant of products and creates only those product variants.

#### Client:

Although concrete factories instantiate concrete products, signatures of their creation methods must return corresponding _abstract_ products. This way **the client code** that uses a factory doesn’t get coupled to the specific variant of the product it gets from a factory.
The **Client** can work with any concrete factory/product variant, as long as it communicates with their objects via abstract interfaces.

# Applicability of the Abstract Factory Pattern

- Use the Abstract Factory when your code needs to work with various families of related products, but you don’t want it to depend on the concrete classes of those products—they might be unknown beforehand or you simply want to allow for future extensibility.
- Consider implementing the Abstract Factory when you have a class with a set of [Factory Methods](https://refactoring.guru/design-patterns/factory-method) that blur its primary responsibility.
- When you need to create related products that work together.
- When the system needs to be independent of how its objects are created.
- When you need to provide multiple families of products but want to ensure that products from the same family are used together.

# Relations with Other Patterns

- Many designs start by using [Factory Method](https://refactoring.guru/design-patterns/factory-method) (less complicated and more customizable via subclasses) and evolve toward [Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory), [Prototype](https://refactoring.guru/design-patterns/prototype), or [Builder](https://refactoring.guru/design-patterns/builder) (more flexible, but more complicated).
	-  **Factory Method**: Focuses on creating one type of product (object).
	- **Abstract Factory**: Focuses on creating families of related products.
- [Builder](https://refactoring.guru/design-patterns/builder) focuses on constructing complex objects step by step. [Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory) specializes in creating families of related objects. _Abstract Factory_ returns the product immediately, whereas _Builder_ lets you run some additional construction steps before fetching the product.


# References

- [Abstract Factory](https://refactoring.guru/design-patterns/abstract-factory).
