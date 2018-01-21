#include "TXLib.h"
#include "corvo.cpp"

struct Barrel
{
    double x, y;
    int taken;
    HDC texture;
};

void drawBarrel(Barrel b)
{
    if (b.taken == 0)
        txTransparentBlt(txDC(), b.x - SHIRINA_OBJ, b.y - SHIRINA_OBJ, 40, 40, b.texture, 0, 0, RGB(255, 255, 255));

}

void actBarrel (Barrel &b, Corvo &c)
{
    double dx = c.x - b.x;
    double dy = c.y - b.y;
    double distance = sqrt(dx * dx + dy * dy); //òåîðåìà Ïèôàãîðà
    if (distance < 20)
    {
        c.hasBarrel = 1;
        b.taken = 1;
    }
}
