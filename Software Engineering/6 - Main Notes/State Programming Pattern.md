
2024-10-16 09:52

Status: #In-Production

Tags: #State-Pattern #Design-Pattern #Code-Repetition #If-conditional

# State Pattern

**State** is a behavioral design pattern that lets an object alter its behavior when its internal state changes. It appears as if the object changed its class.

## Problem

The State pattern is closely related to the concept of a ***Finite-State Machine***.
The main idea is that, at any given moment, there’s a _finite_ number of _states_ which a program can be in. Within any unique state, the program behaves differently, and the program can be switched from one state to another instantaneously. However, depending on a current state, the program may or may not switch to certain other states. These switching rules, called _transitions_, are also finite and predetermined.

You can also apply this approach to objects. Imagine that we have a `Document` class. A document can be in one of three states: `Draft`, `Moderation` and `Published`. The `publish` method of the document works a little bit differently in each state:

- In `Draft`, it moves the document to moderation.
- In `Moderation`, it makes the document public, but only if the current user is an administrator.
- In `Published`, it doesn’t do anything at all.

The biggest weakness of a state machine based on conditionals reveals itself once we start adding more and more states and state-dependent behaviors to the `Document` class. Most methods will contain monstrous conditionals that pick the proper behavior of a method according to the current state, making the code very difficult to maintain.

## Solution

The #State-Pattern suggests that you create new classes for all possible states of an object and extract all state-specific behaviors into these classes.

Instead of implementing all behaviors on its own, the original object, called _context_, stores a reference to one of the state objects that represents its current state, and delegates all the state-related work to that object.

To transition the context into another state, replace the active state object with another object that represents that new state. This is possible only if all state classes follow the same interface and the context itself works with these objects through that interface.

## Applicability of the State Pattern

- Use the #State-Pattern when you have an object that behaves differently depending on its current state, the number of states is enormous, and the state-specific code changes frequently.
- Use the pattern when you have a **class polluted with massive conditionals that alter how the class behaves** according to the current values of the class’s fields.
- Use State when you have a lot of **duplicate code** across similar states and transitions of a condition-based state machine.

## State Pattern Structure

**Context**: stores a reference to one of the concrete state objects and delegates to it all state-specific work. The context communicates with the state object via the state interface. The context exposes a setter for passing it a new state object.

**State** interface declares the state-specific methods. These methods should make sense for all concrete states because you don’t want some of your states to have useless methods that will never be called.

**Concrete States** provide their own implementations for the state-specific methods. To avoid duplication of similar code across multiple states, you may provide intermediate abstract classes that encapsulate some common behavior.

State objects may store a backreference to the context object. Through this reference, the state can fetch any required info from the context object, as well as initiate state transitions.

Both **context** and **concrete states** can set the next state of the context and perform the actual state transition by replacing the state object linked to the context.

## Example Code

Lets suppose a **State** pattern that lets the same controls of the media player behave differently, depending on the current playback state.

The main object of the player is always linked to a state object that performs most of the work for the player. Some actions replace the current state object of the player with another, which changes the way the player reacts to user interactions.

```
// The Context defines the interface of interest to clients. It also
// maintains a reference to an instance of a State subclass, which
// represents the current state of the Context.
class Context
{
	// A reference to the current state of the Context.
	private State _state = null;

	public Context(State state)
	{
		this.TransitionTo(state);
	}

	// The Context allows changing the State object at runtime.
	public void TransitionTo(State state)
	{
		Console.WriteLine($"Context: Transition to {state.GetType().Name}.");
		this._state = state;
		this._state.SetContext(this);
	}

	// The Context delegates part of its behavior to the current State
	// object.
	public void Request1()
	{
		this._state.Handle1();
	}

	public void Request2()
	{
		this._state.Handle2();
	}
}

// The base State class declares methods that all Concrete State should
// implement and also provides a backreference to the Context object,
// associated with the State. This backreference can be used by States to
// transition the Context to another State.
abstract class State
{
	protected Context _context;

	public void SetContext(Context context)
	{
		this._context = context;
	}

	public abstract void Handle1();

	public abstract void Handle2();
}

// Concrete States implement various behaviors, associated with a state of
// the Context.
class ConcreteStateA : State
{
	public override void Handle1()
	{
		Console.WriteLine("ConcreteStateA handles request1.");
		Console.WriteLine("ConcreteStateA wants to change the state of the context.");
		this._context.TransitionTo(new ConcreteStateB());
	}

	public override void Handle2()
	{
		Console.WriteLine("ConcreteStateA handles request2.");
	}
}

class ConcreteStateB : State
{
	public override void Handle1()
	{
		Console.Write("ConcreteStateB handles request1.");
	}

	public override void Handle2()
	{
		Console.WriteLine("ConcreteStateB handles request2.");
		Console.WriteLine("ConcreteStateB wants to change the state of the context.");
		this._context.TransitionTo(new ConcreteStateA());
	}
}

class Program
{
	static void Main(string[] args)
	{
		// The client code.
		var context = new Context(new ConcreteStateA());
		context.Request1();
		context.Request2();
	}
}
```
Execution result:
```
Context: Transition to ConcreteStateA.
ConcreteStateA handles request1.
ConcreteStateA wants to change the state of the context.
Context: Transition to ConcreteStateB.
ConcreteStateB handles request2.
ConcreteStateB wants to change the state of the context.
Context: Transition to ConcreteStateA.
```


# References

- [Further information on the State Pattern](https://refactoring.guru/design-patterns/state).
