
struct Corvo
{
    double x, y;
    double respX, respY;
    int hasSword; // 1 - с оружием, 0 - без
    int hasBarrel; // 1 - с бочкой, 0 - без
    int levelComplete; //1/0
    int killguard;
    HDC texture;
};

void drawCorvo(Corvo c)
{
    txSetColor(TX_BLACK);
    txSetFillColor(TX_BLACK);
    txCircle(c.x, c.y, 20);
    txTransparentBlt(txDC(), c.x - 20, c.y - 20, 50, 50, c.texture, 0, 0, RGB(255, 255, 255));
    if (c.hasSword)
    {
        txRectangle(0, 0, 10, 10);
    }
}

void actCorvo(Corvo &c)
{
    int predX = c.x;
    int predY = c.y;

    if (GetAsyncKeyState(VK_DOWN))
        c.y = c.y + 1;
    if (GetAsyncKeyState(VK_UP))
        c.y = c.y - 1;
    if (GetAsyncKeyState(VK_LEFT))
        c.x = c.x - 1;
    if (GetAsyncKeyState(VK_RIGHT))
        c.x = c.x + 1;

    if (txGetPixel(c.x, c.y) == RGB(128, 128, 128))
    {
        c.x = predX;
        c.y = predY;
    }

    if (txGetPixel(c.x, c.y) == TX_YELLOW)
    {
        c.x = c.respX;
        c.y = c.respY;
    }

    if (c.x < 0 or c.x > 800)
        c.levelComplete = 1;
    if (c.y < 0 or c.y > 600)
        c.levelComplete = 1;
    if (txGetPixel(c.x, c.y) == TX_GREEN)
        c.levelComplete = 1;
}

