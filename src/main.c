#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"                                                    
#include "gray.h"
#include "ascii.h"
#include "output.h"

static void print_usage(const char *program) {
    printf("usage: %s <image> [options]\n\n", program);
    printf("options:\n");
    printf("  -w <width>   output width in characters (default: 100)\n");
    printf("  -o <file>    save output to file (e.g. result.txt)\n");
    printf("  -h           show this help\n\n");
    printf("example:\n");
    printf("  %s photo.jpg -w 120 -o result.txt\n", program);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    const char *image_path = argv[1];
    int         out_width  = 100;
    const char *out_file   = NULL;

    /* lê os argumentos opcionais */
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
            out_width = atoi(argv[++i]);
            if (out_width <= 0 || out_width > 500) {
                fprintf(stderr, "error: width must be between 1 and 500\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            out_file = argv[++i];
        } else if (strcmp(argv[i], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else {
            fprintf(stderr, "error: unknown option '%s'\n", argv[i]);
            return 1;
        }
    }

    /* etapa 1 - carrega a imagem */
    Image *img = image_load(image_path);
    if (!img) return 1;

    /* etapa 2 - converte pra brilho */
    unsigned char *brightness = gray_convert(img);
    if (!brightness) {
        image_free(img);
        return 1;
    }

    /* etapa 3 - mapeia brilho pra caracteres */
    char *canvas = ascii_convert(brightness, img->width, img->height, out_width);
    if (!canvas) {
        free(brightness);
        image_free(img);
        return 1;
    }

    /* etapa 4 - exibe e salva */
    output_print(canvas);
    if (out_file) {
        if (output_save(canvas, out_file) == 0)
            printf("saved to: %s\n", out_file);
    }

    /* libera tudo */
    free(canvas);
    free(brightness);
    image_free(img);

    return 0;
}