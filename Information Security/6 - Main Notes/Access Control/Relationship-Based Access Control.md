
2025-08-22 14:39

Status: #Complete

Tags: #Access-Control #Relationship-Based-Access-Control

# Relationship-based Access Control

Unlike traditional role-based models (RBAC), Zanzibar models permissions as relationships between objects. For example, instead of assigning an "editor" role to a user, it defines a relationship tuple: (user, "editor", document). This approach offers much greater flexibility for defining complex and granular access policies.

#### Relationship Tuples:

The core of Zanzibar is the "tuples," which represent a direct relationship between a user (or a group of users) and an object. These tuples are stored in a globally distributed database (Spanner) to ensure consistency.

# Google Zanzivar

Zanzibar is Google’s globally distributed and centralized authorization system. It functions as a unified service to manage large-scale permissions across Google’s various applications, such as Google Drive, YouTube, and Google Cloud.

# References

- [[Types of Access Control]].
