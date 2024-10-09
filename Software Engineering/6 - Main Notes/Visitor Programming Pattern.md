
2024-09-14 16:14

Status: #In-Production

Tags: #Visitor-Pattern #Double-Dispatch #Composite-Pattern #Design-Pattern 

# Visitor Pattern

**Visitor** is a behavioral design pattern that lets you separate algorithms from the objects on which they operate.
The #Visitor-Pattern allows you to add new operations to a class hierarchy without changing the classes themselves. It achieves this by separating the algorithm from the objects on which it operates. The key idea is to externalize the operations that can be performed on elements of a structure, allowing different behaviors to be defined independently from the structure itself.

It is worth noting that **the client must create visitor objects** and pass them into elements via “**acceptance**” methods, that is because the **Visitor Pattern** uses #Double-Dispatch, meaning both the element and the visitor decide which method (polymorphic) to execute. This allows for more dynamic behavior compared to **single dispatch**.

```
class Visitor is
    method visit(s: Shape) is
        print("Visited shape")
    method visit(d: Dot)
        print("Visited dot")

interface Graphic is
    method accept(v: Visitor)

class Shape implements Graphic is
    method accept(v: Visitor)
        // Compiler knows for sure that `this` is a `Shape`.
        // Which means that the `visit(s: Shape)` can be safely called.
        v.visit(this)

class Dot extends Shape is
    method accept(v: Visitor)
        // Compiler knows that `this` is a `Dot`.
        // Which means that the `visit(s: Dot)` can be safely called.
        v.visit(this)

Visitor v = new Visitor();
Graphic g = new Dot();

// The `accept` method is overriden, not overloaded. Compiler binds it
// dynamically. Therefore the `accept` will be executed on a class that
// corresponds to an object calling a method (in our case, the `Dot` class).
g.accept(v);

// Output: "Visited dot"
```

#### Pros:

-  **_Single Responsibility Principle_**: You can move multiple versions of the same behavior into the same class.
-  A visitor object can accumulate some useful information while working with various objects. This might be handy when you want to traverse some complex object structure, such as an object tree, and apply the visitor to each object of this structure.

#### Cons:

-  **Violation of the Open / Closed Principle**: Since the Visitor Pattern uses #Double-Dispatch, you need to update all visitors each time a class gets added to or removed from the element hierarchy.
- **Breaks Encapsulation**: The pattern forces the visitor to know details about each class it visits, which can break encapsulation.
-  Visitors might lack the necessary access to the private fields and methods of the elements that they’re supposed to work with.

# Visitor Pattern Structure

#### Visitor:

The **Visitor** interface declares a set of visiting methods that can take concrete elements of an object structure as arguments. These methods may have the same names if the program is written in a language that supports overloading, but the type of their parameters must be different.

#### Concrete-Visitor:

Each **Concrete Visitor** implements several versions of the same behaviors, tailored for different concrete element classes.

#### Element:

The **Element** interface declares a method for “accepting” visitors. This method should have one parameter declared with the type of the visitor interface.

#### Concrete Element:

Each **Concrete Element** must implement the acceptance method. The purpose of this method is to redirect the call to the proper visitor’s method corresponding to the current element class. Be aware that even if a base element class implements this method, all subclasses must still override this method in their own classes and call the appropriate method on the visitor object.

#### Client / Object Structure:

The **Client** usually represents a collection or some other complex object (for example, a #Composite-Pattern tree). Usually, clients aren’t aware of all the concrete element classes because they work with objects from that collection via some abstract interface.

# Applicability of the Visitor Pattern

- When the elements are known in advance, but the operation can be extended. (e.g. planets are known in advance, whereas explorers are extendable).
- When the type and name of the operation are unknown during runtime, but the correct method needs to be invoked. (e.g. the both types of planets and explorers are not known during runtime).
-  Use the Visitor when you need to perform an operation on all elements of a complex object structure (for example, an object tree).
	- The Visitor pattern lets you execute an operation over a set of objects with different classes by having a visitor object implement several variants of the same operation, which correspond to all target classes.
- Use the Visitor to clean up the business logic of auxiliary behaviors.
	-  The pattern lets you make the primary classes of your app more focused on their main jobs by extracting all other behaviors into a set of visitor classes.
- Use the pattern when a behavior makes sense only in some classes of a class hierarchy, but not in others.
	- You can extract this behavior into a separate visitor class and implement only those visiting methods that accept objects of relevant classes, leaving the rest empty.

# Relations with Other Patterns

- You can use [Visitor](https://refactoring.guru/design-patterns/visitor) to execute an operation over an entire [Composite](https://refactoring.guru/design-patterns/composite) tree.


# References

- [Visitor Pattern](https://refactoring.guru/design-patterns/visitor).
- [Visitor and Double Dispatch](https://refactoring.guru/design-patterns/visitor-double-dispatch).
- [[Composite Programming Pattern]].