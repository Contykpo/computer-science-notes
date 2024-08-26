
2024-08-26 13:09

Status: #In-Production 

Tags: #Memory-Layout

# Memory Layout

- Each field is aligned to its size. **Padding** is inserted to meet the alignment requirements. E.g. A char takes 1 byte and has 3 bytes of padding in 8 bytes (a row).
- A structure is always aligned to the **largest** of its fields' alignment requirements.
- The size of a structure is such that the address following the structure has the alignment of the same structure. Padding is inserted if necessary.
- **COMMON MISTAKE**: Do not confuse the size of a structure (sizeof) with its alignment requirement.
- **IMPORTANT**: Always pay attention to the alignment requirements of a structure. So that the structure members get packed (As close as possible to avoid wasting space in memory due to padding) in memory. That is why structure members should be declared in order by its alignment requirement.
- Padding is allocated at the end of structure in memory, but if there is an other structure of the same type, then they get aligned.

# References

- [[Memory Layout.canvas|Memory Layout]].
