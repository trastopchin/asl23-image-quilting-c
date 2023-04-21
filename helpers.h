#pragma once

#include <stdint.h>

// Random number generator
void seed_random_number_generator();
int get_random_int(int min, int max);

#define CHANNEL_NUM 3

// Simple RGB image struct
typedef struct RGBImage RGBImage;
struct RGBImage
{
    int rows, cols;
    uint8_t** image;
};

// Initialize the RGBImage, allocating space for the 2D image
void init_rgb_image(RGBImage* rgbImage, int rows, int cols);
// Free the RGBImage, freeing the 2D image
void free_rgb_image(RGBImage* rgbImage);

// Load an RGBImage using stb
void load_rgb_image(RGBImage* rgbImage, char* filename);
// Write an RGBImage using stb
void write_rgb_image(RGBImage* rgbImage, char* filename);