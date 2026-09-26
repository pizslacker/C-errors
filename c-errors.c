#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trigger_buffer_overflow() {
    char buffer[16];
    printf("[*] Triggering Stack Buffer Overflow...\n");
    // strcpy performs no bounds checking. Writing 44 bytes into a 16-byte array 
    // overwrites adjacent stack memory, including the return address.
    strcpy(buffer, "This string is significantly longer than 16 bytes!");
    printf("Buffer contains: %s\n", buffer);
}

void trigger_memory_leak() {
    printf("[*] Triggering Memory Leak...\n");
    char *leaky_ptr = (char *)malloc(1024);
    strcpy(leaky_ptr, "This memory is allocated but never freed.");
    printf("Allocated 1024 bytes at %p\n", (void*)leaky_ptr);
    // Exiting the function without calling free(leaky_ptr) orphans the memory.
}

void trigger_use_after_free() {
    printf("[*] Triggering Use-After-Free...\n");
    char *ptr = (char *)malloc(32);
    strcpy(ptr, "Valid data");
    free(ptr);
    
    // Accessing memory after it has been returned to the heap allocator.
    // This may crash, print garbage, or be exploited if reallocated.
    printf("Data after free: %s\n", ptr);
}

void trigger_uninitialized_variable() {
    printf("[*] Triggering Uninitialized Variable Access...\n");
    int uninit_val;
    // Reading a local variable before assigning a value results in undefined behavior,
    // often printing whatever garbage value was left on the stack.
    printf("Uninitialized value: %d\n", uninit_val);
}

int* return_local_pointer() {
    int local_var = 42;
    // Returning the memory address of a stack variable that will be destroyed 
    // as soon as this function's stack frame pops.
    return &local_var;
}

void trigger_dangling_pointer() {
    printf("[*] Triggering Dangling Pointer...\n");
    int *ptr = return_local_pointer();
    printf("Dangling pointer points to: %d\n", *ptr);
}

void trigger_format_string(char *user_input) {
    printf("[*] Triggering Format String Vulnerability...\n");
    // Passing raw user input directly to printf allows format string injection 
    // (e.g., passing "%x %x %x" will leak stack memory).
    printf(user_input);
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <error_code> [extra_args]\n", argv[0]);
        printf("1: Buffer Overflow\n");
        printf("2: Memory Leak\n");
        printf("3: Use-After-Free\n");
        printf("4: Uninitialized Variable\n");
        printf("5: Dangling Pointer\n");
        printf("6: Format String Bug (requires a second string argument)\n");
        return 1;
    }

    int choice = atoi(argv[1]);

    switch (choice) {
        case 1: trigger_buffer_overflow(); break;
        case 2: trigger_memory_leak(); break;
        case 3: trigger_use_after_free(); break;
        case 4: trigger_uninitialized_variable(); break;
        case 5: trigger_dangling_pointer(); break;
        case 6: 
            if (argc > 2) trigger_format_string(argv[2]);
            else printf("Provide a string for the format bug (e.g., './vuln 6 \"%%x %%x %%x\"')\n");
            break;
        default:
            printf("Invalid choice.\n");
    }

    printf("[*] Execution completed gracefully.\n");
    return 0;
}