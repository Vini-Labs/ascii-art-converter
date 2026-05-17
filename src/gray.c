#include <stdio.h>
#include <stdlib.h>
#include "gray.h"

unsigned char *gray_convert(Image *img) {
    int total_pixels = img->width * img->height;

    unsigned char *brightness = malloc(total_pixels * sizeof(unsigned char));
    if (!brightness) {
        fprintf(stderr, "error: out of memory\n");
        return NULL;
    }

    for (int i = 0; i < total_pixels; i++) {
        unsigned char r = img->pixels[i * 3];
        unsigned char g = img->pixels[i * 3 + 1];
        unsigned char b = img->pixels[i * 3 + 2];

        brightness[i] = (unsigned char)(0.299*r + 0.587*g + 0.114*b);
    }

    return brightness;
}