
2024-10-09 09:02

Status: #In-Production

Tags: #Idiom #Framework #Design-Pattern #Programming-Pattern

# IDIOM vs Framework vs Design Pattern

## IDIOM

An IDIOM is a specific solution to a specific program, and in a particular language. That is why each IDIOM depends on the language in which it is implemented.

## Framework

**Frameworks** are similar to IDIOMS, but apply to a particular domain. For example, a web development framework, or an ORM (Object Relational Mapping).

#### Inversion of Control:

For a **framework** to be a **framework**, it maintains a relationship between a controller object that sends messages to objects in the framework, the framework performs the operations and returns the result through a message to said controller object.

#### Stages of a Framework:

- **Code Generation** (most immature framework): The code is generic and uses templates to generate specific code for each type.
- **White Box**: Breaks encapsulation in relation to its instance. That is because these frameworks use **sub-classification**, the mother of encapsulation breaking.
- **Black Box**: Keeps encapsulation and stablishes a single instance.

## Design Pattern

It is not a concrete solution since it implements proprietary code. It is a way of organizing proprietary code and NOT in a particular domain.
#Design-Pattern s are abstract solutions, that is, they must be implemented every time they are to be used, and they do NOT depend on a programming language, nor are they related to a #Problem-Domain. **Design patterns** maintain the same or similar structure, what changes is the **intention** of how the **pattern is applied.**

|                                       | Concrete Solution | Depends on the Language | Relationship with the Business Domain         |
| ------------------------------------- | ----------------- | ----------------------- | --------------------------------------------- |
| **IDIOM**                             | YES               | YES                     | NO                                            |
| **Design Pattern**                    | NO                | NO                      | NO                                            |
| **Frameworks** (Inversion of Control) | YES               | YES                     | YES. Frameworks solve technological problems. |


# References

- [[Builder Programming Pattern]].
- [[Decorator Pattern]].
- etc.
