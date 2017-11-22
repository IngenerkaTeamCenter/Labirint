#include "TXLib.h"
//#include "corvo.cpp"

struct Barrel
{
    double x, y;
    int taken;
    HDC texture;
};

void drawBarrel(Barrel b)
{
    if (b.taken == 0)
        txTransparentBlt(txDC(), b.x - 20, b.y - 20, 40, 68, b.texture, 0, 0, RGB(255, 255, 255));

}

void actBarrel (Barrel &b, Corvo &c)
{
    double dx = c.x - b.x;
    double dy = c.y - b.y;
    double distance = sqrt(dx * dx + dy * dy); //теорема Пифагора
    if (distance < 20)
    {
        c.hasBarrel = 1;
        b.taken = 1;
    }
}
