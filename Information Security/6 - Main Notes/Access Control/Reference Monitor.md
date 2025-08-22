
2025-08-22 12:29

Status: #Complete

Tags: #Reference-Monitor #Access-Control-Matrix #Subject #Access-Request #Object #Access-Control

# Reference Monitor

Mechanism responsible for “mediating” when subjects attempt to perform operations on objects according to an access policy.

#Subject ---- #Access-Request ----> [ #Reference-Monitor ] ----> #Object

### Properties of the Reference Monitor (RM):

- **Mandatory mediation**: It must intervene in all accesses.
- **Isolation**: Both the #Reference-Monitor (RM) and its data must be **incorruptible**, with no possibility of unauthorized modifications.
- **Verifiability**: It must be possible to demonstrate that its operation is correct.

# Access Control Matrix

It is a conceptual model that describes the protection state precisely.  
A matrix that describes the **permissions of subjects** (users or processes) over **objects**.


|              |     | objects + subjects |     |     |     |     |     |
| ------------ | --- | :----------------: | --- | --- | --- | --- | --- |
|              |     |         o1         | ... | o_m | s1  | ... | s_m |
|              | s1  |                    |     |     |     |     |     |
| **subjects** | s2  |                    |     |     |     |     |     |
|              | ... |                    |     |     |     |     |     |
|              | s_n |                    |     |     |     |     |     |
- Subjects: S = {s1, …, s_n}.
- Objects: O = {o1, ..., o_m}.
- Permissions: R = {r1, ..., r_k}.
- Entries: A[s_i, s_j] ⊆ R. 

#### Some Examples:

- Processes: proc1, proc2
- Files: arch1, arch2
- Permissions: r = read, w = write, x = execute, o = own.

|       | arch1 | arch2 | proc1 | proc2 |
| ----- | ----- | ----- | ----- | ----- |
| proc1 | rwo   | r     | rwxo  | w     |
| proc2 | w     | ro    | r     | rwxo  |
- Users: alice, bob
- Files: memo.doc, demo.exe, backup.pl
- Permissions: r = read, w = write, x = execute.

|       | momo.doc | demo.exe | backup.pl |
| ----- | -------- | -------- | --------- |
| alice | ---      | x        | rx        |
| bob   | rw       | x        | rwx       |
## Implementation:

There are two ways to implement the access control matrix:

#### Access Control List:

There is a list per object. It indicates the permissions that each subject has over the object.

It consists of storing the access control matrix by **columns**.

Given an object, we have the following advantages:
- It is **easy to see the permissions** it has for all subjects.
- It is **easy to revoke all its accesses** by replacing its ACL with an empty one.
- It is **easy to remove it** by deleting its ACL.

**Problems**: How can we check what a subject can access?

#### Capacity List:

There is a list per subject. It indicates the permissions that the subject has over each object.

It consists of storing the access control matrix by **rows**.

Given a subject, we have the following advantages:
- It is easy to check all the permissions it has.
- It is easy to revoke its permissions by replacing its capability list with an empty one.
- It is easy to remove it by deleting its capability list.

**Problems**: How can we check who can access an object?

# References

- (Link Source material) with [[]].
