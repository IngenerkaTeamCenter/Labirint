struct Ventilation
{
    double x, y;
    int isOpened; //1 - �������, 0 - �������
    HDC texture;
    HDC textureOpened;
};

void drawVentilation(Ventilation v)
{
    if (v.isOpened == 0)
    {
        txTransparentBlt(txDC(), v.x - 20, v.y - 20, 40, 40, v.texture, 0, 0, RGB(255, 255, 255));
    }
    else
    {
        txTransparentBlt(txDC(), v.x - 20, v.y - 20, 40, 40, v.textureOpened, 0, 0, RGB(255, 255, 255));
    }
}

void actVentilation(Ventilation &v, Corvo &c)
{
    double dx = c.x - v.x;
    double dy = c.y - v.y;
    double distance = sqrt(dx * dx + dy * dy); //������� ��������
    if (distance < 20 && c.hasSword == 1)
    {
        v.isOpened = 1;
    }
    if (distance < 10 && v.isOpened == 1)
    {
        c.levelComplete = 1;
    }
}
