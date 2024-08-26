
2024-08-11 18:47

Status: #In-Production

Tags: #Memory-Alignment

# Alignment

+ A word (not to be mistaken with Intel-word 2 bytes), is the amount of bits that the processor (CPU) can manage per operation.
+ The memory can be directed at byte-level, but access to memory can be more efficient if it is done counting words.
+ Data alignment is important for the best performance of the system.
+ Alignment works with #Little-Endian, which is an order in which the "little end" (least significant byte) is stored first. [[Little Endian.canvas|Little Endian]].
+ A block of **data** **is N-byte aligned** if its memory address is a multiple of N. Each data type has its own alignment requirement, for example, a 32-bit (4-byte) integer must be 4-byte aligned.
+ 



# References

- [[Little Endian.canvas|Little Endian]].