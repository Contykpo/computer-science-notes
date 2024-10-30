
2024-10-30 00:37

Status: #In-Production

Tags: #Exceptions #Object-Contracts

# Exceptions

Exceptions indicate the breach of a contract. 

#### How are Exceptions Handled?

- The handler is only executed if the handling condition is met.
- The next handler is passed on if the handling condition is not met.
- If the root of the **execution tree** is reached, and there is no handler, it means that an "unhandled exception" was raised.

An **exception** can never go unnoticed, it can be handled manually by the programmer, or handled by the system handler.
#### When is an Exception Raised?

An **exception** is **raised** when an object contract is breached, more specifically, when the contract's **pre-condition** is not met and exits with an error. For example passing a parameter to a function that is outside of it's domain.

#### How do we Verify that the Contract is Fulfilled?

There are two schools regarding contract fulfillment:

- **C School**: The object that sends the message or called function must ensure the **conditions** of the contract.
- **Lisp School**: The object that receives the message or called function must ensure the **pre-conditions** are met.

#### Who Reports the Exceptions in the Execution Tree?

**Exceptions** are **raised** by objects that are generally at the **bottom of the execution tree**.
***And who generally handles them?*** The **highest objects** in the **execution tree**, since they are the most general abstractions of what is being executed.

#### What Exceptions Should be Reported?

1. One type of exception for every **error condition**.
2. Always the same exception type, no matter what **error condition** triggers it.
3. A mixture between the above mentioned.


# References

- [[Object Contracts]].
