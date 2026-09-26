# C errors

Demonstration program (in `C`) that uses a command-line argument to isolate and trigger six distinct memory and logic errors, allowing you to observe their behaviors individually.

Modern compilers actively block these vulnerabilities.

The Makefile in this project creates two distinct builds: a vulnerable version that deliberately strips away security features to let the crashes happen, and a strict version that demonstrates how the compiler identifies the errors, and sometimes mitigates them.

The six errors:
 1. Buffer Overflow
 2. Memory Leak
 3. Use-After-Free
 4. Uninitialized Variable
 5. Dangling Pointer
 6. Format String Bug
