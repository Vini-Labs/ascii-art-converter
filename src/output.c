#include <stdio.h>
#include "output.h"

void output_print(const char *canvas) {
    printf("%s", canvas);
}

int output_save(const char *canvas, const char *path) {
    FILE *f = fopen(path, "w");
    if (!f) {
        fprintf(stderr, "error: could not open '%s' for writing\n", path);
        return -1;
    }

    fprintf(f, "%s", canvas);
    fclose(f);
    return 0;
}