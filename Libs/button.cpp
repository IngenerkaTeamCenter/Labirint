struct Button
{
    double x, y;
    HDC textureOff;
    HDC textureOn;
    int on;
    double barrierX, barrierY;
};

void drawButton(Button b)
{
    if (b.on == 0)
    {
        txTransparentBlt(txDC(), b.x - SHIRINA_OBJ, b.y - SHIRINA_OBJ, 40, 40, b.textureOff, 0, 0, RGB(255, 255, 255));
        txSetColor(RGB(128, 128, 128));
        txSetFillColor(RGB(128, 128, 128));
        txRectangle(b.barrierX - 22, b.barrierY - 22, b.barrierX + 22, b.barrierY + 22);
    }
    else
    {
        txTransparentBlt(txDC(), b.x - SHIRINA_OBJ, b.y - SHIRINA_OBJ, 40, 40, b.textureOn, 0, 0, RGB(255, 255, 255));
    }
}

void actButton(Button &b, Corvo &c)
{
    double dx = c.x - b.x;
    double dy = c.y - b.y;
    double distance = sqrt(dx * dx + dy * dy); //теорема Пифагора
    if (distance < 20 && c.hasBarrel)
    {
        c.hasBarrel = 0;
        b.on = 1;
    }
}
