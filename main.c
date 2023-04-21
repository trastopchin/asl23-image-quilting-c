#include <stdio.h>

#define CHANNEL_NUM 3

#include "helpers.h"
#include "image_quilting.h"

int main() {
    RGBImage input, output;
    // Load the input image
    load_rgb_image(&input, "data/input0.png");

    // Image quilting
    quilt_random_blocks(&input, &output, input.rows/3, input.cols/3, 6, 6);

    // Write the output image
    write_rgb_image(&output, "output.png");

    // Cleanup
    free_rgb_image(&input);
    free_rgb_image(&output);
    return 0;
}