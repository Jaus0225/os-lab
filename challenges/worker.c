#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Print passed command-line arguments
    for (int i = 1; i < argc; i++) {
        printf("worker: argv[%d] = %s\n", i, argv[i]);
    }

    // Print environment variable MYVAR if present
    char *val = getenv("MYVAR");
    if (val != NULL) {
        printf("worker: MYVAR=%s\n", val);
    }

    return 0;
}
