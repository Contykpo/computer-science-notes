
2024-09-11 13:01

Status: #In-Production

Tags: #Programming-Pattern #Singleton-Pattern #Design-Pattern 

# Singleton Pattern

The #Singleton-Pattern is a design pattern in object-oriented programming that ensures a class has only one instance and provides a global point of access to that instance. This pattern is particularly useful when exactly one object is needed to coordinate actions across the system.

- **Single Instance**: Ensures that a class has only one instance throughout the application's lifecycle.
- **Global Access**: Provides a global point of access to that instance.
- **Controlled Access**: Manages the creation of the instance to ensure that no more than one instance is created.

# Implementation Methods of the Singleton Pattern

#### Classic Singleton / Eager Initialization:

This implementation creates the instance at the time of class loading. It is the simplest form and does not require synchronization. Simple but creates the instance eagerly.

```
public class Singleton
{
    private static final Singleton instance = new Singleton();

    private Singleton()
    {
        // private constructor to prevent instantiation
    }

    public static Singleton getInstance()
    {
        return instance;
    }
}
```

- Easy to implement and understand.
- **Thread Safety**: Always thread-safe due to instance being created at class loading.
- **Performance**: Instance is created even if it’s never used, which might be unnecessary if instantiation is costly.

#### Thread-safe Singleton / Lazy Initialization with Synchronization:

This approach defers the creation of the instance until it's actually needed. It is thread-safe by using synchronization to ensure only one thread can create the instance at a time.
Can be inefficient.

```
public class Singleton
{
    private static Singleton instance;

    private Singleton()
    {
        // private constructor to prevent instantiation
    }

    public static synchronized Singleton getInstance()
    {
        if (instance == null)
        {
            instance = new Singleton();
        }
        return instance;
    }
}
```

- **Thread Safety**: Ensures only one instance is created even in a multi-threaded environment.
- **Performance**: Synchronization can be costly if `getInstance()` is called frequently.

#### Lazy Singleton with Double-Checked Locking:

This method combines lazy initialization with double-checked locking to reduce the overhead of synchronization. It checks if the instance is `null` twice—once without synchronization and once with synchronization. Balances performance and thread safety but can be complex.

```
public class Singleton
{
    private static volatile Singleton instance;

    private Singleton()
    {
        // private constructor to prevent instantiation
    }

    public static Singleton getInstance()
    {
        if (instance == null)
        {
            synchronized (Singleton.class)
            {
                if (instance == null)
                {
                    instance = new Singleton();
                }
            }
        }
        
        return instance;
    }
}
```

- **Thread Safety**: Uses `volatile` and double-checked locking to ensure only one instance is created.
- **Performance**: Reduces the synchronization overhead by checking the instance outside of the synchronized block.

#### Bill Pugh Singleton / Initialization-on-demand:

This implementation leverages the class loader mechanism to ensure that the instance is created only when needed and is thread-safe without explicit synchronization.
Modern and efficient, leveraging class loading for thread safety.

```
public class Singleton
{
    private Singleton()
    {
        // private constructor to prevent instantiation
    }

    private static class Holder
    {
        private static final Singleton INSTANCE = new Singleton();
    }

    public static Singleton getInstance()
    {
        return Holder.INSTANCE;
    }
}
```

- **Thread Safety**: Class loading mechanism guarantees thread safety.
- **Performance**: Efficient as it creates the instance only when it’s first requested.


# References

- (Link Source material) with [[]].
