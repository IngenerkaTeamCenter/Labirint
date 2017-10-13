struct Wall
{
    double x, y;
};

void drawWall(Wall w)
{
    txSetColor(RGB(128, 128, 128));
    txSetFillColor(RGB(128, 128, 128));
    txRectangle(w.x - 22, w.y - 22, w.x + 22, w.y + 22);
}
