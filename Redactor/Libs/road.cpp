struct Road
{
    double x, y;
};

void drawRoad (Road r)
{
    txSetColor(RGB (100, 0, 0));
    txSetFillColor(RGB (100, 0, 0));
    txRectangle(r.x - 20, r.y - 20, r.x + 20, r.y + 20);
}
