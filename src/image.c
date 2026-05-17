#include <stdio.h>
#include <stdlib.h>
#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image *image_load(const char *path) {
    Image *img = malloc(sizeof(Image));
    if (!img) {
        fprintf(stderr, "error: out of memory\n");
        return NULL;
    }

    img->pixels = stbi_load(path, &img->width, &img->height, &img->channels, 3);
    if (!img->pixels) {
        fprintf(stderr, "error: could not load image '%s'\n", path);
        free(img);
        return NULL;
    }

    img->channels = 3;
    return img;
}

void image_free(Image *img) {
    if (!img) return;
    stbi_image_free(img->pixels);
    free(img);
}