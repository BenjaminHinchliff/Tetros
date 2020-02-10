#ifndef BLOCK_TEMPLATES_H
#define BLOCK_TEMPLATES_H

#include <vector>

#include "Block.h"

namespace blocks
{
    const BlockTemplate L{
        {
            {0, 0, 1},
            {1, 1, 1},
        },
        glm::vec3(1.0f, 0.8431f, 0.0f)
    };
    //const blocks_t L{
    //    {0, 0, 1},
    //    {1, 1, 1},
    //};

    //const blocks_t J{
    //    {1, 0, 0},
    //    {1, 1, 1}
    //};

    //const blocks_t Z{
    //    {1, 1, 0},
    //    {0, 1, 1},
    //};

    //const blocks_t S{
    //    {0, 1, 1},
    //    {1, 1, 0},
    //};

    //const blocks_t T{
    //    {0, 1, 0},
    //    {1, 1, 1},
    //};

    //const blocks_t O{
    //    {1, 1},
    //    {1, 1},
    //};

    //const blocks_t I{
    //    {1, 1, 1, 1},
    //};
}

#endif