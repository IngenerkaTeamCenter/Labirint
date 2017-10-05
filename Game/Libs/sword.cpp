struct Sword
{
    double x, y;
    int has;
    HDC texture;
};

void drawSword(Sword s)
{
    /*   txSetColor(TX_WHITE);
       txSetFillColor(TX_WHITE);
       txCircle(s.x, s.y, 20);*/
    if(s.has == 0)
        txTransparentBlt(txDC(), s.x - 20, s.y - 20, 40, 40, s.texture, 0, 0, RGB(255, 255, 255));
}

void actSword(Sword &s, Corvo &c)
{
    double dx = c.x - s.x;
    double dy = c.y - s.y;
    double distance = sqrt(dx * dx + dy * dy); //теорема Пифагора
    if (distance < 20)
    {
        c.hasSword = 1;
        s.has = 1;
    }
}

