
2025-08-26 12:25

Status: #Complete

Tags: #Security-Policy #Mandatory-Access-Control #Discretionary-Access-Control #Dominance

# Bell-Lapadula Security Model

**Objective**: Prevent unauthorized access to information. Unauthorized modifications are secondary. 

It controls the **flow of information**.  

Multilevel security models are the most common examples.  

The **Bell-LaPadula Model** (1970s) is the foundation for most of these models.

Combines #Mandatory-Access-Control and #Discretionary-Access-Control.

Ordered security classification levels:

- **Top Secret**: highest level  
- **Secret**  
- **Confidential**  
- **Unclassified**: lowest level

Subjects have security clearances **L(s)**  
Objects have security classifications **L(o)**

When referring to both, we speak of classifications.

For Example:

| Security Clearance | Subject | Object          |
| ------------------ | ------- | --------------- |
| High Secret        | Tamara  | Personnel files |
| Secret             | Samuel  | E-mails         |
| Confidential       | Claire  | Activity logs   |
| Unclasified        | UIaley  | Telephone guide |

When a request is made, the system accepts or rejects it by considering the clearance of the subject making the request and the security classification of the requested object.

For this, two principles are applied:

- **Read down**
- **Write up**

## Read Access to Information:

Simple Security Condition, preliminary version

- Subject **s** can read object **o** **if and only if** **L(o) ≤ L(s)** and **s** has permission to read the object **o**.
- Note: the model combines **mandatory access control** (relationships between security levels) and **discretionary control** (the required permission).

Known as the **“Read Down” Rule**.

## Information Writing:

**Property * (Star Property), preliminary version:**

- Subject **s** can write to object **o** **if and only if** **L(s) ≤ L(o)** and **s** has write permission for **o**.
- **Note**: the model combines **mandatory access control** (relationships between security levels) and #Discretionary-Access-Control (the required permission).
- Known as the **“Write Up” Rule**.

# Extended Bell-Lapadula Security Model

The concept is expanded by adding **categories**.  

Categories represent different areas of information within the same level and do not follow a hierarchical scheme.  

The security level is **(clearance, set of categories)**.

Examples:

- (Top Secret, {NATO, MERCOSUR, NOFORN})    
- (Confidential, {MERCOSUR, NOFORN})
- (Secret, {NATO, NOFORN})

## Levels and Dominance

#Dominance: (A, C) dominates (A', C') <-> A' ≤ A y C' ⊆ C
Examples:

- (Top Secret, {NATO, NOFORN}) dominates (Secret, {NATO})
- (Secret, {NATO, MERCOSUR}) dominates (Confidential, {NATO, MERCOSUR})
- (Top Secret, {NATO}) does **not** dominate (Confidential, {MERCOSUR})

## Read Access to Information:

Simple Security Condition, Extended Version:

- Subject **s** can read object **o** **if and only if** **L(s) dominates L(o)** and **s** has permission to read **o**.
- Note: the model combines **mandatory access control** (relationships between security levels) and **discretionary control** (the required permission).
- Known as the **“Read Down” Rule**.

## Information Writing:

**Property * (Star Property), Extended Version**

- Subject **s** can write to object **o** **if and only if** **L(o) dominates L(s)** and **s** has permission to write to **o**.
- Note: the model combines **mandatory access control** (relationships between security levels) and #Discretionary-Access-Control (the required permission).
- Known as the **“Write Up” Rule**.

# References

- [[Security Policies and Security Mechanisms]].
