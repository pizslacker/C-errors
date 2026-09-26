CC = gcc

# -fno-stack-protector: Disables stack canaries (allows buffer overflow to overwrite return address)
# -z execstack: Marks the stack as executable (classic exploitation requirement)
# -w: Suppresses all compiler warnings so the bad code builds silently
# -O0: Disables optimization so the compiler doesn't optimize away our deliberate bugs
CFLAGS_VULN = -fno-stack-protector -z execstack -O0 -w

# -Wall -Wextra: Enables comprehensive warnings
# -D_FORTIFY_SOURCE=2: Adds lightweight bounds checking to functions like strcpy
# -O2: Required for FORTIFY_SOURCE to work
CFLAGS_STRICT = -Wall -Wextra -D_FORTIFY_SOURCE=2 -O2

all: vulnerable strict

vulnerable: c-errors.c
	$(CC) $(CFLAGS_VULN) c-errors.c -o c-errors-vulnerable
	@echo "Built c-errors-vuln (Protections disabled)"

strict: c-errors.c
	@echo "\n--- Attempting strict build (Expect warnings/errors) ---"
	-$(CC) $(CFLAGS_STRICT) c-errors.c -o c-errors-strict
	@echo "Built c-errors-strict (Protections enabled)"

clean:
	rm -f c-errors-vuln c-errors-strict