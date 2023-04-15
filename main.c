#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNEL_NUM 3

int main() {
    // Read the image
    int width, height, comp;
    uint8_t* rgb_image = stbi_load("data/input0.png", &width, &height, &comp, CHANNEL_NUM);
    printf("width: %d, height: %d, comp: %d\n", width, height, comp);

    // Convert the image to grayscale
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = CHANNEL_NUM * (width * i + j);
            double value = 0;
            for (int k = 0; k < CHANNEL_NUM; k++) value += (int) rgb_image[index+k];
            value /= 3;
            rgb_image[index] = (uint8_t) value;
            rgb_image[index+1] = (uint8_t) value;
            rgb_image[index+2] = (uint8_t) value;
        }
    }

    // Write the image
    stbi_write_png("./output.png", width, height, CHANNEL_NUM, rgb_image, width*CHANNEL_NUM);

    // Free the image
    stbi_image_free(rgb_image);

    return 0;
}
