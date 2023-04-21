#pragma once

#include "helpers.h"

// Quilt a new texture by randomly choosing new blocks
void quilt_random_blocks(RGBImage* input, RGBImage* output, int blockSizeX, int blockSizeY, int numBlocksX, int numBlocksY);