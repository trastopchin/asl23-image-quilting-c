#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "helpers.h"

// Random number generator
// https://stackoverflow.com/questions/1190870/i-need-to-generate-random-numbers-in-c
void seed_random_number_generator()
{
    srand(time(0));
}

// Get random integer in range
// https://stackoverflow.com/questions/1190870/i-need-to-generate-random-numbers-in-c
int get_random_int(int min, int max)
{
    return rand() % (max - min) + min;
}

// Initialize the RGBImage, allocating space for the 2D image
void init_rgb_image(RGBImage* rgbImage, int rows, int cols)
{
    rgbImage->rows = rows;
    rgbImage->cols = cols;
    rgbImage->image = malloc(rows * sizeof(uint8_t*));
    for (int i = 0; i < rows; i++)
        rgbImage->image[i] = malloc(cols * CHANNEL_NUM * sizeof(uint8_t));
}

// Free the RGBImage, freeing the 2D image
void free_rgb_image(RGBImage* rgbImage)
{
    for (int i = 0; i < rgbImage->rows; i++)
        free(rgbImage->image[i]);
    free(rgbImage->image);
}

// Load an RGBImage using stb
void load_rgb_image(RGBImage* rgbImage, char* filename)
{
    // Load the image using stb
    int rows, cols, comp;
    uint8_t* rgb_image = stbi_load(filename, &cols, &rows, &comp, CHANNEL_NUM);
    if (cols == 0 || rows == 0 || comp == 0) {
        fprintf(stderr, "Error reading file: \"%s\"\n", filename);
        return;
    }

    // Initialize rgbImage
    init_rgb_image(rgbImage, rows, cols);

    // Convert the 1d array into a 2d array
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            int index = CHANNEL_NUM * (cols * i + j);
            for (int k = 0; k < CHANNEL_NUM; k++)
                rgbImage->image[i][CHANNEL_NUM * j + k] = rgb_image[index + k];
        }
    }
}

// Write an RGBImage using stb
void write_rgb_image(RGBImage* rgbImage, char* filename)
{
    // Convert the 2d array into a 1d array
    uint8_t* rgb_image = malloc(CHANNEL_NUM * rgbImage->rows * rgbImage->cols * sizeof(uint8_t));
    for (int i = 0; i < rgbImage->rows; i++){
        for (int j = 0; j < rgbImage->cols; j++){
            for (int k = 0; k < CHANNEL_NUM; k++){
                rgb_image[i * (CHANNEL_NUM * rgbImage->cols) + CHANNEL_NUM * j + k] = rgbImage->image[i][CHANNEL_NUM * j + k];
            }
        }
    }

    // Write the image using stb
    stbi_write_png(filename, rgbImage->cols, rgbImage->rows, CHANNEL_NUM, rgb_image, CHANNEL_NUM * rgbImage->cols);

    // Clean up
    free(rgb_image);
}