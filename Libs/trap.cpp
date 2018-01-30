struct Trap
{
    double x, y;
    double toX, toY;
    HDC texture;
};

void drawTrap(Trap t)
{
    txTransparentBlt(txDC(), t.x - SHIRINA_OBJ, t.y - SHIRINA_OBJ, 40, 40, t.texture, 0, 0, RGB(255, 255, 255));
}

void actTrap(Trap &t, Corvo &c)
{
    double dx = c.x - t.x;
    double dy = c.y - t.y;
    double distance = sqrt(dx * dx + dy * dy); //теорема Пифагора
    if (distance < 20)
    {
        c.x = t.toX;
        c.y = t.toY;
    }
}
