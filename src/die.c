#include <mysort/die.h>
#include <mysort/types.h>
#include <mysort/config.h>
#include <stdio.h>
#include <stdlib.h>

NORETURN void die(string_t reason) {
    if (reason == NULL) {
        fprintf(stderr, "Fatal error\n");
    } else {
        fprintf(stderr, "Fatal error: %s\n", reason);
    }
#ifdef ABORT_ON_DIE
    abort();
#else
    exit(DIE_EXIT_CODE);
#endif
}
