#include <stdio.h>
#include <stdlib.h>
#include "ascii.h"

static const char *CHARS = "@#S%?*+;:,. ";
static const int   NCHARS = 12;

char *ascii_convert(unsigned char *brightness, int width, int height, int out_width) {
    int step_x  = width / out_width;
    if (step_x < 1) step_x = 1;
    int step_y  = step_x * 2;

    int out_height = height / step_y;
    int out_cols   = out_width + 1;  /* +1 pra '\n' em cada linha */

    char *canvas = malloc(out_height * out_cols + 1);  /* +1 pro '\0' final */
    if (!canvas) {
        fprintf(stderr, "error: out of memory\n");
        return NULL;
    }

    for (int row = 0; row < out_height; row++) {
        for (int col = 0; col < out_width; col++) {
            int px = (row * step_y) * width + (col * step_x);
            int index = brightness[px] * (NCHARS - 1) / 255;
            canvas[row * out_cols + col] = CHARS[index];
        }
        canvas[row * out_cols + out_width] = '\n';
    }

    canvas[out_height * out_cols] = '\0';
    return canvas;
}