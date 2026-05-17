#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    unsigned char *pixels;
    int width;
    int height;
    int channels;
} Image;

Image *image_load(const char *path);
void image_free(Image *img);

#endif