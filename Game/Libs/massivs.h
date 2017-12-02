#pragma once

#include "TXLib.h"

struct image {
    int x;
    int y;
    int height;
    int width;
    HDC picture;
    bool draw;
};
