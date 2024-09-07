
2024-09-02 09:10

Status: #In-Production

Tags: #Software-Development #Design #Problem-Domain #Computable-Model
#Code-Repetition #Abstraction

# Design

#### Modeling:
It is highly important to model all aspects of the **entities** in the #Problem-Domain, including units of measurement and non-exactly countable concepts.

Breaking object encapsulation is about taking a part of an object and sending it directly to a part of the original object, this increases coupling.
That is, you **MUST NOT break the encapsulation**.

**All objects in a set are polymorphic** with respect to a set of messages if the objects in the first set respond semantically the same to the messages in the second. 
The current modeling theory being used for creating #Computable-Model s is the 
#Aristotle-Model:

- The implementation of the messages is in the class, but it is not the class that defines how the objects/instances behave.
- By having static methods, we avoid seeing the class as an object, since they are seen as data structures, and static methods are functions that are housed in a code block.
- **Aristotelian logic**, an object knows how to answer to all the messages that its class hierarchy responds to. (Example in the canvas).
- **A problem with the Aristotelian model** is having to **name all the objects explicitly** to classify them, since it may be the case that they are later changed when expanding the concept or category of the class. 

#### Elimination of Code Repetition:
It must be understood that **repeated code goes beyond repeated text**, but must be rather considered as patterns of repeated collaborations.
Having repeated code means that an #Abstraction is missing, this means that an object that deals with said abstraction is missing in the OOP solution.

These are steps to deal with #Code-Repetition:

1. **Move the repeated code** to a new **abstraction**.
2. **Parameterize** the changes.
3. **Name the new abstraction**. The most important part, because it involves giving meaning and semantic to the abstraction.
4. **Replace** the repeated code with the new abstraction.

#### Elimination of Ifs / Conditionals

1. **Create a polymorphic hierarchy** with an abstraction for if condition (optional).
2. **Move** the body of each if to **each corresponding abstraction** using the same message.
3. **Name** the **abstractions** in 1.
4. **Name** the **message** in 2.
5. **Replace** the **if/conditional** with the sending of the polymorphic message.
6. **Find** the polymorphic object (optional).

#### Naming:

Message names should not only be self-explanatory, but should make sense in the #Problem-Domain. For example, when modeling a traffic light, a message blinkYellowLightHundredTimes does not tell you what happens, but rather what it does; a better name would be OnPowerWarning for an unary method of a message that executes the power-on process.


# References

- [[Automated Refactoring]].
- [[Modeling Rules (Heuristic).canvas|Modeling Rules (Heuristic)]].
- [[Aristotle Model.canvas|Aristotle Model]].
