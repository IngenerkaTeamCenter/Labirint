#include "const.cpp"
struct Wall
{
    double x, y;
};

void drawWall(Wall w)
{
    txSetColor(RGB(128, 128, 128));
    txSetFillColor(RGB(128, 128, 128));
    txRectangle(w.x - SHIRINA_OBJ, w.y - SHIRINA_OBJ, w.x + SHIRINA_OBJ, w.y + SHIRINA_OBJ);
}
