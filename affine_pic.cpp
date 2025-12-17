#include "affine_pic.h"
#include "main.h"
#include "pic8.h"

// Create a picture that may be rotated and stretched.
// Provide either a filename or a pic8.
affine_pic::affine_pic(const char* filename, pic8* pic) {
    if (!pic) {
        pic = new pic8(filename);
    }

    // Transparency is hard-coded to the topleft
    transparency = pic->gpixel(0, 0);

    // We pad each row to a length of 256 for faster rendering,
    // so the max width is 255
    width = pic->get_width();
    height = pic->get_height();
    if (width > 255 || height > 255) {
        internal_error("affine_pic size > 255!");
    }

    int length = height * 256;
    pixels = new unsigned char[length];
    if (!pixels) {
        external_error("affine_pic out of memory!");
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixels[y * 256 + x] = pic->gpixel(x, y);
        }
    }

    delete pic;
}

affine_pic::affine_pic(int w, int h) {
    width = w;
    height = h;
    if (width > 255 || height > 255) {
        internal_error("affine_pic size > 255!");
    }
    int length = height * 256;
    pixels = new unsigned char[length];
    if (!pixels) {
        external_error("affine_pic out of memory!");
    }
}

#define BMP_HEADER_SIZE 1078
#define BMP_WIDTH_EOLMAX 256
#define BMP_WIDTH 149
#define BMP_WIDTH_PADDED 152
#define BMP_EOL_ARRAY_SIZE (BMP_WIDTH_EOLMAX * BMP_HEIGHT)
#define BMP_HEIGHT 101
#define BMP_PIXEL_ARRAY_SIZE (BMP_WIDTH_PADDED * BMP_HEIGHT)

affine_pic* affine_pic::from_bmp(const char* filename) {
    unsigned char data[BMP_PIXEL_ARRAY_SIZE] = {0};
    FILE* f = fopen(filename, "rb");
    if (!f) {
        return nullptr;
    }

    fseek(f, BMP_HEADER_SIZE, SEEK_SET);
    fread(data, BMP_PIXEL_ARRAY_SIZE, 1, f);
    affine_pic* k = new affine_pic(149, 101);

    /*
        k->lyuk = 0;
        for (int y = 0; y < k->ysize; y++) {
            for (int x = 0; x < k->xsize; x++) {
                k->tomb[y * 256 + x] = x % 256;
            }
        }*/
    k->transparency = data[0];
    for (int i = 0; i < BMP_EOL_ARRAY_SIZE; i++) {
        if ((i % BMP_WIDTH_EOLMAX < BMP_WIDTH) && (i / BMP_WIDTH_EOLMAX < BMP_HEIGHT)) {
            k->pixels[i] = data[BMP_WIDTH_PADDED * ((BMP_HEIGHT - 1) - i / BMP_WIDTH_EOLMAX) +
                                (i % BMP_WIDTH_EOLMAX)];
        }
    }

    return k;
}

affine_pic::~affine_pic() {
    if (pixels) {
        delete pixels;
    }
}
