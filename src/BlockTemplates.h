#ifndef BLOCK_TEMPLATES_H
#define BLOCK_TEMPLATES_H

#include <vector>
#include <random>
#include <iterator>

#include "Block.h"

namespace blocks
{
    const BlockTemplate L{
        {
            {0, 0, 1},
            {1, 1, 1},
        },
        glm::vec3(0.9373f, 0.4745f, 0.1294f)
    };

    const BlockTemplate J{
        {
            {1, 0, 0},
            {1, 1, 1},
        },
        glm::vec3(0.3530f, 0.3961f, 0.6784f)
    };

    const BlockTemplate Z{
        {
            {1, 1, 0},
            {0, 1, 1},
        },
        glm::vec3(0.9373f, 0.1255f, 0.1608f)
    };

    const BlockTemplate S{
        {
            {0, 1, 1},
            {1, 1, 0},
        },
        glm::vec3(0.2588f, 0.7137f, 0.2588f)
    };

    const BlockTemplate T{
        {
            {0, 1, 0},
            {1, 1, 1},
        },
        glm::vec3(0.6784f, 0.3020f, 0.6118f)
    };

    const BlockTemplate O{
        {
            {1, 1},
            {1, 1},
        },
        glm::vec3(0.9686f, 0.8275f, 0.0314f)
    };

    const BlockTemplate I{
        {
            {1, 1, 1, 1},
        },
        glm::vec3(0.1922f, 0.7804f, 0.9373f)
    };

    const std::array<BlockTemplate, 7> arr{ L, J, Z, S, T, O, I };

    const BlockTemplate& selectRandomBlock()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        auto start(arr.begin());
        auto end(arr.end());
        std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
        std::advance(start, dis(gen));
        return *start;
    }
}

#endif