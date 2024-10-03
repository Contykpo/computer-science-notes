
2024-10-03 07:46

Status: #In-Production 

Tags: #Software-Development #Design #Long-Methods #Refactoring #MethodObject

# Replace Method with Method Object

#### Why Replace a Method with Method Object?

We want to **extract a method** when we have a long method in which the local variables are so intertwined that we can’t apply _Extract Method_.

A method is too long and you can’t separate it due to tangled masses of local variables that are hard to isolate from each other.
The first step is to isolate the entire method into a separate class and turn its local variables into fields of the class.
Firstly, this allows isolating the problem at the class level. Secondly, it paves the way for splitting a large and unwieldy method into smaller ones that wouldn’t fit with the purpose of the original class anyway.  For instance:

```
class Order
{
  // ...
  public double price()
  {
    double primaryBasePrice;
    double secondaryBasePrice;
    double tertiaryBasePrice;
    // Perform long computation.
  }
}
```
```
class Order
{
  // ...
  public double price()
  {
    return new PriceCalculator(this).compute();
  }
}

class PriceCalculator
{
  private double primaryBasePrice;
  private double secondaryBasePrice;
  private double tertiaryBasePrice;
  
  public PriceCalculator(Order order)
  {
    // Copy relevant information from the
    // order object.
  }
  
  public double compute()
  {
    // Perform long computation.
  }
}
```

#### Benefits and Drawbacks:

- Isolating a long method in its own class allows stopping a method from ballooning in size. This also allows splitting it into sub-methods within the class, without polluting the original class with utility methods.
- However, another class is added, increasing the overall complexity of the program.

#### Structured Steps:

1. Create a new class. Name it based on the purpose of the method that you’re refactoring.
    
2. In the new class, create a private field for storing a reference to an instance of the class in which the method was previously located. It could be used to get some required data from the original class if needed.
    
3. Create a separate private field for each local variable of the method.
    
4. Create a constructor that accepts as parameters the values of all local variables of the method and also initializes the corresponding private fields.
    
5. Declare the main method and copy the code of the original method to it, replacing the local variables with private fields.
    
6. Replace the body of the original method in the original class by creating a method object and calling its main method.


# References

- This technique might be useful when working on Step 2 in #Test-driven-Development[[Test-driven Development]].
- [[Design Code Refactoring]].
- [[Design Heuristics]].
