#include "TXLib.h"
#include "const.cpp"


struct Guard
{
    double x, y;
    double angle;
    int moveMode; //0 - стоит, 1 - ходит по горизонтали, 2 - ходит по вертикали
    double v, coord1, coord2; //скорость и границы движения
    int isDead; //0 - жив, 1 - мёртв
    HDC texture;
};

void drawGuard(Guard g)
{
    if (g.isDead == 0)
    {
        txSetColor(TX_ORANGE);
        txSetFillColor(TX_ORANGE);
        txCircle (g.x, g.y, SHIRINA_OBJ);
        txTransparentBlt(txDC(), g.x - SHIRINA_OBJ, g.y - SHIRINA_OBJ, 2 * SHIRINA_OBJ, 2 * SHIRINA_OBJ, g.texture, 0, 0, RGB(255, 255, 255));

        txSetColor(TX_YELLOW);
        txSetFillColor(TX_YELLOW);
        txPie(g.x - 100, g.y - 100, g.x + 100, g.y + 100, g.angle - 30, 60);
    }
}

void actGuard(Guard &g, Corvo &c)
{
    if (g.moveMode == 0)
    {
        g.angle = g.angle + 0.5;
        if (g.angle > 360)
            g.angle = g.angle - 360;
    }
    if (g.moveMode == 1)
    {
        g.x = g.x + g.v;
        if (g.x == g.coord1 || g.x == g.coord2)
        {
            g.v = -g.v;
        }
        if (g.v < 0)
        {
            g.angle = 180;
        }
        else
        {
            g.angle = 0;
        }
    }
    if (g.moveMode == 2)
    {
        g.y = g.y + g.v;
        if (g.y == g.coord1 || g.y == g.coord2)
        {
            g.v = -g.v;
        }
        if (g.v < 0)
        {
            g.angle = 90;
        }
        else
        {
            g.angle = 270;
        }
    }

    double dx = g.x - c.x;
    double dy = g.y - c.y;
    double dist = sqrt(dx * dx + dy * dy);
    if (g.isDead == 0 && dist < 15 && c.hasSword == 1)
    {
        g.isDead = 1;
        c.killguard ++;
    }
}
