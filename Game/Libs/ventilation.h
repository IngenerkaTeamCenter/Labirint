#pragma once

#include <cmath>
#include "TXLib.h"
#include "corvo.h"

struct Ventilation {
    double x, y;
    int isOpened;
    HDC texture;
    HDC textureOpened;
};

void drawVentilation(Ventilation v) {
    if (v.isOpened == 0) {
        txTransparentBlt(txDC(), v.x - SHIRINA_OBJ, v.y - SHIRINA_OBJ, 40, 40, v.texture, 0, 0, RGB(255, 255, 255));
    } else {
        txTransparentBlt(txDC(), v.x - SHIRINA_OBJ, v.y - SHIRINA_OBJ, 40, 40, v.textureOpened, 0, 0,
                         RGB(255, 255, 255));
    }
}

void actVentilation(Ventilation &v, Corvo &c) {
    double dx = c.x - v.x;
    double dy = c.y - v.y;
    double distance = sqrt(dx * dx + dy * dy);
    if (distance < SHIRINA_OBJ && c.hasSword == 1) {
        v.isOpened = 1;
    }
    if (distance < 10 && v.isOpened == 1) {
        c.levelComplete = 1;
    }
}
