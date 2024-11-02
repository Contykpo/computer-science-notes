
2024-08-26 13:57

Status: #In-Production

Tags: #Global-Memory #Static-Memory #Automatic-Memory #Dynamic-Memory #Memory-Segments #Stack #Heap #BSS-Segment #DATA-Segment #TEXT-Segment

# Types of Memory

|            | Scope                                                  | Lifetime                        |
| ---------- | ------------------------------------------------------ | ------------------------------- |
| Global:    | The whole file.                                        | The application lifetime.       |
| Static:    | The function or block where it was declared.           | The application lifetime.       |
| Automatic: | The function or block where it was declared.           | The function or block lifetime. |
| Dynamic:   | Determined by pointers referencing that memory region. | Until the memory is freed.      |
## Dynamic Memory:

#### A memory region assigned on run-time:

- Most of the **power of pointers** relies on assigning memory on run-time.
- **Basic steps** for working with #Dynamic-Memory:
	- Use 'malloc', 'calloc', 'realloc' to allocate memory.
	- Use allocated memory for what it is needed.
	- Use 'free' to free / deallocate memory. 

#### Problems of Dynamic Memory:

- **Memory Leak**: It is the loss of memory that is never freed / deallocated.
- **Dangling Pointer**: It is a pointer variable that points to a direction of memory that is no longer valid.
- **Double Free**: It is the repeated liberation of a same direction of memory.
- **Use After Free**: Access a direction of memory that has already been freed.

# Memory Segments / Image of Memory

|  High Directions   |               |                                                      |
| :----------------: | ------------- | ---------------------------------------------------- |
|      Variable      | Stack Segment | Return directions, parameters, local variables.      |
|        Size        | Heap Segment  | Dynamic variables managed by malloc and free.        |
|                    | BSS Segment   | Uninitialized global variables and static variables. |
|       Fixed        | DATA Segment  | Initialized global variables and static variables.   |
|        Size        | TEXT Segment  | Machine code / compiled code.                        |
| **Low Directions** |               |                                                      |

# References

- [[Memory Segments.canvas|Memory Segments]].
