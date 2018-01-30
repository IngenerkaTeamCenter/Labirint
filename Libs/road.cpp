struct Road
{
    double x, y;
};

void drawRoad (Road r)
{
    txSetColor(RGB (100, 0, 0));
    txSetFillColor(RGB (100, 0, 0));
    txRectangle(r.x - SHIRINA_OBJ, r.y - SHIRINA_OBJ, r.x + SHIRINA_OBJ, r.y + SHIRINA_OBJ);
}
