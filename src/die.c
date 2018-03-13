#include <mysort/die.h>
#include <mysort/types.h>
#include <stdio.h>
#include <stdlib.h>

NORETURN void die(string_t reason) {
    if (reason == NULL) {
        fprintf(stderr, "Fatal error\n");
        exit(DIE_EXIT_CODE);
    } else {
        fprintf(stderr, "Fatal error: %s\n", reason);
        exit(DIE_EXIT_CODE);
    }
}
