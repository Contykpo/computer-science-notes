
2024-09-02 08:34

Status: #In-Production 

Tags: #Variables #Object-Oriented-Paradigm #Smalltalk

# What is a variable in foundational OOP?

In the foundational object paradigm, a variable is a reference to an object, and is represented as a name given to that object at a particular time.

# What is a pseudo-variable in OOP?

Pseudo-variables in the foundational OOP, are variables that doesn't need to be defined, nor initialized, these variables are known as:

- **Self**: Its the reference that an object has to itself, that is how an object can send messages to itself.
- **This Context**: In general, the area which holds the local variables of a particular method or block is called a #Stack-Frame. In #Smalltalk or the foundational OOP in general, these are **accessible to the program as objects** an are called **contexts**.

# Equality and Identity:

It is important to consider the difference between these two concepts, since it is possible to have several objects that represent the same **entity** of reality ( #Problem-Domain ), but they are non-identical, they are equal objects.

- The identity of objects is verified by the == message. If the result is true, the two objects are identical.
- The '**=**' message verifies whether two objects are equal, whether they are identical or not.
- If two **objects are identical**, it means they share the **same memory address**.


# References

- [[]].


