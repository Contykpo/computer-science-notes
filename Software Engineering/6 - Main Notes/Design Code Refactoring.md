
2024-09-14 10:29

Status: #In-Production

Tags: #Software-Development #Design #Problem-Domain #Code-Repetition #Abstraction #If-conditional

# Elimination of Code Repetition

It must be understood that **repeated code goes beyond repeated text**, but must be rather considered as patterns of repeated collaborations.
Having repeated code means that an #Abstraction is missing, this means that an object that deals with said abstraction is missing in the OOP solution.

These are steps to deal with #Code-Repetition:

1. **Move the repeated code** to a new **abstraction**.
2. **Parameterize** the changes.
3. **Name the new abstraction**. The most important part, because it involves giving meaning and semantic to the abstraction.
4. **Replace** the repeated code with the new abstraction.

# Elimination of Ifs / Conditionals

1. **Create a polymorphic hierarchy** with an abstraction for if condition (optional).
2. **Move** the body of each if to **each corresponding abstraction** using the same message.
3. **Name** the **abstractions** in 1.
4. **Name** the **message** in 2.
5. **Replace** the **if/conditional** with the sending of the polymorphic message.
6. **Find** the polymorphic object (optional).

#### Which are the limits on whether to eliminate an If or not?

- System instances / objects.
- When in the collaborators within the If condition, there are objects that are not in the same #Problem-Domain. (Removing an If on such case could be questionable).


# References

- [[Automated Refactoring]].
