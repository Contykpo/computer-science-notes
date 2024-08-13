
## What is Software?

- <u>Classic Definition</u>: Sequence of instructions that given an input, it generates an output.
- <u>Engineering Definition</u>: (Representation of knowledge by means of a) #Computable-Model <b>Computable Model</b> of a #Problem-Domain <b>Problem Domain</b> from <b>Reality</b>.

### [[Definition of Software.canvas|Definition of Software]]

<b>Reality</b>: Everything that we can perceive, touch, talk about, etc.
<b>Problem Domain</b>: A cut from reality that interests us for the business we are modeling.
<b>Model</b>: Representation of what is being modeled.
<b>Computability</b>: Can run on a Turing machine -> Formal to contextual.
	<b>Essential feature</b>: It not only specifies the **what** but also implements the **how**.

## What is a good model?

- <b>Functional Axis</b>: How good the representation of the domain is.
- <b>Description Axis</b>: How good is the model described, how understandable it is.
- <b>Implementation Axis</b>: How it "runs" on a technical environment.

#### Implementation Axis:

A model is good when it executes in the expected time using the resources defined as necessary.

- Performance.
- Space.
- Scalability.
- Everything related to **Non-functional Requirements**.
- "**Meticulous**" side of development.

#### Description Axis:

A model is good when it can be “**understood**” and therefore “**changed**”.

- It is **very important** to use good, representative names.
- It is **very important** to use the same language as the **Problem Domain**.
- Good, clean code.
- Artistic side of development.

#### Functional Axis:

A model is good when it can correctly represent every observation of what it models.

- If something new appears in the **domain**, something new should appear in the model (not modify it).
- If something in the **domain** is modified, only its representation in the model should be modified.
- **Isomorphism**: One-to-One relationship. Domain-Model.
- Observational side of development.

## [[Definition of Software.canvas|Best relationship Domain-Model]]
