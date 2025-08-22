
2025-08-22 14:56

Status: #Complete

Tags: #Access-Control #Role-Based-Access-Control #Discretionary-Access-Control #Mandatory-Access-Control

# Role-Based Access Control

RBAC ( #Role-Based-Access-Control ) emerged in the late 1980s and gained strong momentum in the 1990s. It combines aspects of #Discretionary-Access-Control and #Mandatory-Access-Control but with a vision more oriented toward organizational structure.

Basically, it consists of creating roles for the jobs or functions carried out within the organization. Staff members are assigned to roles, and through these roles, they acquire permissions to perform system functions.

Subjects access objects based on the activities they perform in the system, that is, considering the roles they hold within the system.

**Role**: the set of actions and responsibilities associated with a particular activity.

To implement #Role-Based-Access-Control, mechanisms are needed that allow:

- Identifying the roles in a system and assigning subjects to the defined roles.  
- Establishing access permissions to objects for each role.  
- Establishing permissions for subjects so that they can assume roles.

## Features of RBAC

#### Authorization management:

The assignment of permissions to users has two parts:

- Associate users with roles.
- Assign permissions for objects to roles.

If a user changes tasks, it is enough to change their role.

#### Role hierarchy:

Roles also have hierarchical relationships.  

They can inherit privileges and permissions from other lower-level roles, simplifying the management of authorizations.

#### Least Privilege:

Allows implementing the policy of least privilege.

If a task will not be performed by a user, then their role will not have the permissions to do it, thereby minimizing the risk of damage.

#### Separation of Duties:

It is based on the principle that no user should have enough privileges to use the system for their own benefit.

For example, a person responsible for authorizing a payment should not be the beneficiary of that payment.

It can be enforced in two ways:

- **Statically**: by defining mutually exclusive roles for the same user.
- **Dynamically**: by performing the control at the time of access.

## Disadvantages of RBAC:

Difficulty in establishing roles and defining their scopes.

## Some Standards of RBAC:

- INCITS 359-2012
- eXtensible Access Control Markup Language (XACML).
- XACML RBAC Profile

# References

- [[Types of Access Control]].