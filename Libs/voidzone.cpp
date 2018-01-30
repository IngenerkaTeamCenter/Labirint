struct Voidzone
{
    double x, y;
    int voidactive;
    HDC textureActive;
    HDC textureDesactive;
    int timer;
};

void drawVoidzone(Voidzone v)
{
    if (v.voidactive == 1)
    {
        txTransparentBlt(txDC(), v.x - SHIRINA_OBJ, v.y - SHIRINA_OBJ, 40, 40, v.textureActive, 0, 0, RGB(255, 255, 255));
    }
    else
    {
        txTransparentBlt(txDC(), v.x - SHIRINA_OBJ, v.y - SHIRINA_OBJ, 40, 40, v.textureDesactive, 0, 0, RGB(255, 255, 255));
    }
}
void actVoidzone(Voidzone &v, Corvo &c)
{
    if (v.voidactive == 1)
    {

        double dx = c.x - v.x;
        double dy = c.y - v.y;
        double distance = sqrt(dx * dx + dy * dy); //теорема Пифагора
        if (distance < SHIRINA_OBJ)
        {
            c.x = c.respX;
            c.y = c.respY;
        }
    }
    v.timer++;
    if (v.timer > 200) {
        v.timer = 0;
        v.voidactive = 1 - v.voidactive;
    }
}
