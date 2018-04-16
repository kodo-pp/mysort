#include <stdio.h>
#include <mysort/types.h>
#include <mysort/usage.h>
#include <mysort/args.h>
#include <mysort/die.h>
#include <stdlib.h>
#include <mysort/config.h>
#include <mysort/sort.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

static void random_init() {
    bool good_random = true;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        good_random = false;
    }
    int state = 0;
    if (good_random) {
        char buf[sizeof(state)];
        if (read(fd, buf, sizeof(buf)) == -1) {
            close(fd);
            goto bad_random;
        }
        memcpy(&state, buf, sizeof(state));
    } else {
    bad_random:
        state = time(NULL);
    }
    srand(state);
}

int main(int argc, char **argv) {
    random_init();
    memset(&opts, 0, sizeof(opts));

    parse_args(argc, argv);
    if (opts.invalid_flag) {
        show_usage_and_exit(1);
    }

    switch (opts.output_type) {
    case OT_USAGE:
        show_usage_and_exit(2);
        break;
    case OT_VERSION:
        fprintf(stderr, "mysort v %s\n", VERSION_STRING);
        exit(2);
        break;
    case OT_SORT:
        sort_process();
        break;
    case OT_IMMEDIATE_SORT:
        immediate_sort_process();
        break;
    default:
        die("unknown output type (at main)");
        break;
    }
}
