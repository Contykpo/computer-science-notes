
2025-08-19 16:33

Status: #Complete

Tags: #General-Concepts #Security-Policy #Security-Mechanism

# Security Policy:

A #Security-Policy is a statement of what is allowed and what is not.
In general, policies require some procedures that technology alone cannot enforce.

A security policy is a statement that partitions a system into two sets of states:

- **Authorized** (safe): these are the states the system is allowed to enter.
- **Unauthorized** (unsafe): if the system enters one of these states, a security violation will occur.
## Some Definitions:

**Secure system**: It is a system that starts in an authorized state and never enters an unauthorized state.  
A system that is secure under one policy may not be secure under another.

**Security problem**:  When a system enters an unauthorized state, then we have a security problem.

## Types of Policies:

- **Confidentiality policy**: Developed mainly to protect confidentiality.
- **Integrity policy**: Developed mainly to protect integrity.
- **Hybrid policy**.

## Some Security Policy Models:

- [[Bell-Lapadula Security Model]].
- [[Covert Channel]].
	- [[BIBA Model]].
	- [[Clark-Wilson Model]]
- [[Hybrid Policy Models]].

# Security Mechanism:

A #Security-Mechanism is a **method**, **tool**, or **procedure** used to *enforce* a #Security-Policy (or a certain part of a policy).
**Mechanisms** can be non-technical. For example: Requiring a student ID before changing a student’s password.

For example:
- **Access control** (assigning permissions to resources)  
- Not allowing people to insert CDs or USB storage devices into a computer in order to control what enters the systems

# An Operational View:

Any useful #Security-Policy and #Security-Mechanism must **balance** the **benefits of protection** with the **cost** of designing, implementing, and using the mechanism.

This balance can be determined by analyzing the risks and the probability of occurrence. 
For example: A database provides employee salary information and is used to print paychecks. If this information is altered, the company could suffer significant financial losses. Therefore, it is clear that mechanisms must be used to ensure the integrity of the information. However, if there is a second system that daily copies this database to each branch so they have reference values when hiring new staff (the decision is made by the headquarters), the need to maintain integrity at each branch is not as critical.

# References

- [[Bell-Lapadula Security Model]].
- [[Covert Channel]].
