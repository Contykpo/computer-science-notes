
2025-08-22 14:59

Status: #Complete

Tags: #Access-Control #Discretionary-Access-Control

# Discretionary Access Control

#Discretionary-Access-Control (DAC) is an access control policy determined by the owner of a resource (a file, a printer).

It is discretionary because the resource owner arbitrarily decides who is allowed to access it and with what permissions.

## Some Key Concepts:

**Property**: Each object in the system must have an owner. The access policy is determined by the resource owner. In theory, an object without an owner is not protected. Normally, the owner of a resource is the user who creates it.

**Permissions**: access rights that the resource owner assigns to individual users or groups of users.

**Subjects**: users or groups of users  

**Objects**: system resources  

**Permissions**: access rights for the ordered pair (S_i, O_j)

This means that subject S_i can access object O_j according to the rights (read, write, execute, etc.) granted.

## Advantages

Flexible and adaptable to many systems and applications.  
Widely used, especially in commercial and industrial environments.

## Main Problem

Discretion in granting rights.

# References

- [[Types of Access Control]].
