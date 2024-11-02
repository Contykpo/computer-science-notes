
2024-08-28 11:41

Status: #In-Production

Tags: #Development-Process #Compiler #GCC

# Compiler

It is a program capable of syntactically analyzing a text file containing a source program.

If it is written correctly, respecting the semantics of the language for which it compiles, it generates a binary code suitable to be executed by the Microprocessor that acts as the CPU in the system.

In addition to analyzing operations, it replaces the logical names that we adopt in our program for variables or functions with the memory addresses where they are located.

It cannot resolve references to functions outside the source file it analyzes. For example, it cannot resolve what numeric value to replace the printf() label with, since it has no visibility of it. We will have to wait for the next phase to resolve this issue.

Before the Compiler does its job, it calls a program called a #Pre-processor, which is responsible for removing comments, including other files (the line # include<stdio.h> is replaced by content from the file stdio.h), and replacing macros (the statement for the **Preprocessor** in this case is # define).

If it generates errors, the program is poorly written and needs to be revised.

If it doesn't generate errors, it just means that the program is correctly written. Whether it works correctly is another question...

```
// To generate a program object with the GNU Compiler Collection #GCC:

gcc -c hello.c -hello.o -Wall

// -Wall parameter means the file won't compile if the compiler detects any warnings during the Pre-processor stage.
```

Once it is compiled, its product is an object program. This is a binary, but it is not yet ready to be executed.


# References

- [[Development Process.canvas|Development Process]].
