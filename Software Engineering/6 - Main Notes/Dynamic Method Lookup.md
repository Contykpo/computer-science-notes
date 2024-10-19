
2024-10-19 12:48

Status: #In-Production

Tags: #Dynamic-Method-Lookup #Interfaces #Abstract-classes #Concrete-classes #Methods #Lookup-Method

# Dynamic Method Lookup

It is the process of determining which method definition a method signature denotes during runtime, based on the type of the owner object. However, it is worth mentioning that a call to a **private instance method** is not polymorphic, so we won't get such effect.

## Lookup Method

#Lookup-Method is the term for methods that don't have any implementation or require any dependencies. For instance, all methods in an interface are considered **lookup methods**.
Moreover, this concept can be found on #Interfaces, #Abstract-classes and #Concrete-classes.


# References

- **Concrete classes:** are classes that fully implement an **interface** or **abstract class**, this means that they have a definition for all the methods declared on the implemented interface.
