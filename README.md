# C errors

Demonstration of six distinct memory and logic errors that can be made in C.

Modern compilers actively block these vulnerabilities.

The Makefile in this project creates two distinct builds: a vulnerable version that deliberately strips away security features to let the crashes happen, and a strict version that demonstrates how the compiler identifies the errors, and sometimes mitigates them.
