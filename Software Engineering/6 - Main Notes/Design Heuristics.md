
2024-09-14 09:40

Status: #In-Production

Tags: #Heuristics #Whole-Objects #Valid-Objects #Immutable-Object #null #Getters #Setters #Atomic-Modification #Builder-Pattern #Option-Pattern #Problem-Domain

# Design Heuristics / Principles

#### 1. Create Whole Objects:

Create #Whole-Objects, which represent their equivalents in reality. We must ensure that when an **object exists**, it only represents an entity in reality.

#### 2. Create Valid Objects:

Create #Valid-Objects, with validations to ensure that it uniquely represents the concept of its equivalent entity within the #Problem-Domain.

#### 3. Promote the Use of Immutable Objects:

Favor the use of #Immutable-Object s. An object should be immutable when the **entity** it represents is also **immutable**. For example, a date is immutable.

#### 4. Don't Use Nulls / Nills:

Having a #null is having an object that is not self-contained.

**What would be an alternative for null?**

Since **null** is often used to represent the existence and absence of something, you can directly use a class (enum, std::optional, class) to represent the existence or non-existence of that something in another object, than would be a #Builder-Pattern approach. An other approach is the #Option-Pattern.

#### 5. Avoid having Getters and Setters:

Avoid using #Getters and #Setters to avoid breaking encapsulation. If mutable objects are returned through a getter, these objects may be altered.
For instance, a credit card can have an expiration date and a getter that returns that date, but it would be better to have a method that returns a copy of the date or whether the card has already expired.

#### 6. Make Atomic Modifications:

Making #Atomic-Modification s. Instead of modifying the object directly, you can copy it because you already know the the object elements are valid (heuristic 2), so you just add and validate the changed element. That is why the **modification** is **atomic**, there is only one message that allows you to modify the object.


# References

- [[Builder Programming Pattern]].
- [[Option Programming Pattern]].
- [SOLID Principles of OOP](https://www.geeksforgeeks.org/solid-principle-in-programming-understand-with-real-life-examples/).
- [[Modeling Rules (Heuristic).canvas|Modeling Rules (Heuristic)]].