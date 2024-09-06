
The paper introduces **Self**, an object-oriented programming language that emphasizes simplicity and uniformity in its design.

# Prototypes instead of Classes

In **Self**, there are no classes. Instead, **every object is a prototype** that can be cloned to create new objects. This means objects can serve as templates (prototypes) for creating other objects. Cloning an object means copying its slots (properties or methods), thereby creating a new object that retains the original object's state and behavior.

#### Slots and Messages:

Each object in **Self** is essentially a collection of **slots**. A **slot** can contain either:

- **Data Slots**: These hold values (e.g., numbers, strings).
- **Method Slots**: These hold executable code (methods).

To access a slot, an object sends a **message** to itself or another object. This messaging system serves as the foundation for both data access and method invocation.

When an object is cloned, it creates a new object with the same slots as the original. Modifications to the clone do not affect the original object or vice versa, providing a simple and intuitive way to manage state and behavior in objects.

#### Creation of New Objects:

To create a new object, you typically clone an existing prototype. For instance, if you want to create a new "point" object, you might clone a generic "point" prototype. This new point object would then have all the slots (data and behavior) of the original point, which can be modified as needed.

#### Benefits of the #Prototype-Pattern:

- **No Class/Object Dichotomy:** Since **Self** has no classes, there's no distinction between a class and an instance. This reduces the cognitive load for programmers.
- **Direct Manipulation:** Objects can be directly modified or extended without the need to modify a class or define a subclass. This leads to a more flexible and dynamic system.

# Inheritance through Delegation

#### Delegation Instead of Inheritance:

In **Self**, inheritance is achieved via **delegation**. Instead of an object being an instance of a class, objects have **parent slots** that point to other objects (their **parents**). When a message is sent to an object and it doesn't have a corresponding slot to handle that message, it delegates the message to its parent(s).

#### Message Lookup and Parent Slots:

When a message is sent to an object:

1. The runtime first looks for a slot in the receiving object that matches the message.
2. If no matching slot is found, the message is **delegated** to one of the object's parents (if a parent exists).
3. This process continues recursively until the message is either handled or an error is thrown (if no matching slot is found in any parent).

#### Multiple Parents (Multiple Delegation):

An object in **Self** can have multiple parents. This allows for a form of **multiple inheritance** where an object can inherit behavior from multiple other objects. When a message is delegated, the runtime searches through all parent slots in the order they are defined.

#### Dynamic Changes to the Delegation Chain:

The delegation chain (i.e., parent relationships) can be modified at runtime, allowing for **dynamic inheritance**. This is a powerful feature because it means that an object's behavior can change on the fly by modifying its delegation structure.

#### Benefits of Delegation:

- **Flexible Inheritance:** Delegation allows objects to dynamically share behavior without the rigidity of class hierarchies.
- **Dynamic Composition:** Objects can easily change their behavior by altering their delegation chain, enabling powerful dynamic behaviors that would be more cumbersome in class-based languages.

# Dynamic Typing and Flexibility

**Self** is dynamically typed, meaning that type checking is done at runtime rather than compile-time. This flexibility allows for rapid prototyping and dynamic modifications to object structures, aligning with the language's goal of simplicity.

# Uniformity and Simplicity

The design of **Self** focuses on having a minimal set of powerful concepts that can express complex behaviors. By unifying state and behavior under the same model (slots and messages), the language avoids special cases and maintains uniformity.

# Reflection and Self-Modification

#### Reflection in Self:

**Self** supports a high degree of **reflection**, meaning objects can introspect (examine) and modify their own structure and behavior at runtime. This is made possible because everything in **Self** is treated uniformly as objects with slots.
For example, an object can list its slots, add new slots, or remove existing ones. This is done using the same message-passing mechanism that is used for other operations.

#### Self-Modification:

Objects in **Self** can modify themselves or other objects. This means an object can change its own slots (both data and methods), modify its parents, or even change the behavior of its own methods.
For instance, if an object wishes to change the behavior of one of its methods, it can directly modify the method slot to point to a new method.

#### Meta-level Programming:

Because **Self** objects can modify themselves, it supports **meta-level programming**, where the language itself can be extended or modified from within the language. This is possible because both objects and the environment that manages objects are built on the same principles.

#### Uniformity of Operations:

Since reflection and self-modification use the same slot-based message-passing mechanism, there is no special case or additional syntax required for these advanced behaviors. This uniformity simplifies both the language and the programmer's mental model.

#### Benefits of Reflection and Self-Modification:

- **Dynamic Flexibility:** Reflection and self-modification allow **Self** programs to be highly dynamic, adapting to new requirements at runtime.
- **Simplifies Meta-programming:** Since the same operations apply uniformly to both application-level and meta-level tasks, developers do not need to learn different sets of rules for introspection or modification.

# Performance and Optimization

#### Dynamic Deoptimization:

Dynamic deoptimization is an optimization technique that allows a runtime system to switch from an optimized version of code back to a simpler, unoptimized version when necessary.

This approach is especially useful in the Self language, where runtime flexibility such as dynamic typing, reflection, and self-modification often conflicts with the need for efficient execution.

#### Adaptive Compilation:

Adaptive compilation, also known as **just-in-time compilation**, refers to the strategy of dynamically compiling code during program execution based on its observed behavior.
This approach is essential in the Self language, where the cost of interpreting or executing code can vary significantly depending on usage patterns.