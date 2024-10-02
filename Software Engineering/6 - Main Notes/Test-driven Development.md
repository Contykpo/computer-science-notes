
2024-10-02 09:10

Status: #In-Production

Tags: #Software-Development #Design #Test-driven-Development

# The TDD Technique

**Test-driven Development** is an interactive incremental learning technique, based on immediate feedback.
As a **side-effect**, you will **remember everything learned** during the development process and it allows as to ensure never **unlearning** the design. 

#### Steps:

1. **Write a test**:
	1. It must be the simplest and most basic test possible.
	2. It must fail when run before implementing our solution.
2. **Run all the tests**:
	1. Implement the simplest solution that could enable us to pass all the tests.
	2. GOTO 2 again, until all the tests run correctly.
3. **Reflect on the solution - How can we improve this code?**
	1. If the code can be improved, GOTO 2.
	2. If we can't improve the code, GOTO 1.

#### Some Clarifications:

The test should be as simple as possible to gather all the feedback we can in order to make out design errors present on the solution.

If the test doesn't fail, we may have a repeated test, or have gotten ahead of ourselves in the previous step by adding unnecessary functionality. That's why we need to make sure the test fails so I don't have to test anything already implemented.

We **reflect** to assess whether my solution is adequate, regardless of whether the tests run or not.

#### Structure of the Tests:

- **Setup**: Sets the initial context for test execution. Can be checked in a setup message or method.
- **Exercise**: Exercise the specified functionality we are currently testing.
- **Assert**: Check the results.


# References

- [[Testing]].
- [[Design Code Refactoring]].
- [[Design Heuristics]].
- [[Design Modeling]].
