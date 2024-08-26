
2024-08-26 12:15

Status: #In-Production 

Tags: #Object-Oriented-Paradigm #Smalltalk 

# Foundational Object-Oriented Programming

Everything is an object in the context of the #Object-Oriented-Paradigm.

## Program:

In the #Object-Oriented-Paradigm, a program is basically objects cooperating by sending messages to each other.

#### Circularity: Object = ~~Code + Data~~ Message

Circularity means that everything in the #Object-Oriented-Paradigm is essentially an **object**, that is because there wouldn't be any circularity within the language if an **object** (in Smalltalk e.g.) would be made of other thing that is not an object.

#### Object = The essential representation of an entity in the #Problem-Domain.
#### Message = Object. It is the 'what'.
#### Method = The 'how' of the 'what'.

## Collaboration:

It is the whole **set** of sending a message to an object and the object replying to that message (in Smalltalk, the receiver object doesn't know who is the sender object) and getting a result from that reply message.

Sender Object -> Send Message -> Receiver Object
Sender Object <- Reply Message  <- Receiver Object
-> Result Object.

#### Characteristics of Communication within Objects:

1. **Synchronized**: When an object sends a message, it awaits a reply. (Humans aren't necessary synchronous, but **objects** actually are).
2. **Directed**: An **object must know** an other object by its name to send a message (but not a reply, it works different).
3. **There always exists a result**: Every time a message is sent, there would be a **result**. Even '**nothingness**' is represented by an object.
4. **The receiver object doesn't know the sender object**:

# References

- (Link Source material) with [[]]
