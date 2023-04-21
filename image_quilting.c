#include "image_quilting.h"
#include "helpers.h"

// Quilt a new texture by randomly choosing new blocks
void quilt_random_blocks(RGBImage* input, RGBImage* output, int blockSizeX, int blockSizeY, int numBlocksX, int numBlocksY)
{
    // Seed the random number generator
    seed_random_number_generator();

    // Initialize the output image
    init_rgb_image(output, numBlocksX * blockSizeX, numBlocksY * blockSizeY);

    // Iterate over each block
    for (int blockX = 0; blockX < numBlocksX; blockX++){
        for (int blockY = 0; blockY < numBlocksY; blockY++){

            // Top-left corner of the current block
            int x = blockSizeX * blockX;
            int y = CHANNEL_NUM * blockSizeY * blockY;

            // Randomly choose a new block
            int offsetX = get_random_int(0, input->cols - blockSizeX);
            int offsetY = get_random_int(0, input->rows - blockSizeY);

            // Write the randomly chosen block to the output
            for (int i = 0; i < blockSizeX; i++){
                for (int j = 0; j < blockSizeY; j++){
                    for (int k = 0; k < CHANNEL_NUM; k++){
                        output->image[x+i][y+CHANNEL_NUM*j+k] = input->image[offsetX+i][CHANNEL_NUM*(offsetY+j)+k];
                    }
                }
            }
        }
    }
}