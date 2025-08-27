
2025-08-26 14:31

Status: #Complete

Tags: #Security-Policy #Security-Mechanism #Covert-Channel #BIBA-Model #Clark-Wilson-Model

# The Role of Trust

Integrity policies deal with the issue of trust.

- The #BIBA-Model is based on **multilevel integrity**.
- The #Clark-Wilson-Model focuses on **transactions** and **separation of duties**.

For example, suppose a vulnerability appears in the operating system we use on our PC:

- We obtain the corresponding security patch.
- We install it.
- We raise the security level of our PC.
- We trust that it is no longer vulnerable.

But we also **implicitly trust**:

- That the patch comes from the operating system vendor and was not tampered with.
- That the vendor properly tested the patch before releasing it.
- That the vendor’s test environment corresponds to ours.
- That the patch was installed correctly.

Any #Security-Policy, #Security-Mechanism, or procedure is based on assuming certain facts which, if incorrect, can undermine everything that has been built.

This must be kept in mind, because if we do not understand the basis of the policy, mechanism, or security procedure, invalid assumptions may be made, leading to incorrect conclusions

# References

- [[Covert Channel]].
- [[BIBA Model]].
- [[Clark-Wilson Model]].
