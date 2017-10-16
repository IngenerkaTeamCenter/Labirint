#include "TXLib.h"
#include "lib\\Corvo.txt"

//==============================================================================================


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


//==============================================================================================

struct Guard
{
    double x, y;
    double angle;
    int moveMode; //0 - стоит, 1 - ходит по горизонтали, 2 - ходит по вертикали
    double v, coord1, coord2; //скорость и границы движения
    int isDead; //0 - жив, 1 - мёртв
};

void drawGuard(Guard g)
{
    if (g.isDead == 0)
    {
        txSetColor(TX_ORANGE);
        txSetFillColor(TX_ORANGE);
        txCircle (g.x, g.y, 20);

        txSetColor(TX_YELLOW);
        txSetFillColor(TX_YELLOW);
        txPie(g.x - 100, g.y - 100, g.x + 100, g.y + 100, g.angle - 30, 60);
    }
}

void actGuard(Guard &g, Corvo &c)
{
    if (g.moveMode == 0)
    {
        g.angle = g.angle + 0.5;
        if (g.angle > 360)
            g.angle = g.angle - 360;
    }
    if (g.moveMode == 1)
    {
        g.x = g.x + g.v;
        if (g.x == g.coord1 || g.x == g.coord2)
        {
            g.v = -g.v;
        }
        if (g.v < 0)
        {
            g.angle = 180;
        }
        else
        {
            g.angle = 0;
        }
    }
    if (g.moveMode == 2)
    {
        g.y = g.y + g.v;
        if (g.y == g.coord1 || g.y == g.coord2)
        {
            g.v = -g.v;
        }
        if (g.v < 0)
        {
            g.angle = 90;
        }
        else
        {
            g.angle = 270;
        }
    }

    double dx = g.x - c.x;
    double dy = g.y - c.y;
    double dist = sqrt(dx * dx + dy * dy);
    if (g.isDead == 0 && dist < 15 && c.hasSword == 1)
    {
        g.isDead = 1;
        c.killguard ++;
    }
}


//==============================================================================================

struct Trap
{
    double x, y;
    double toX, toY;
    HDC texture;
};

void drawTrap(Trap t)
{
    txTransparentBlt(txDC(), t.x - 20, t.y - 20, 40, 40, t.texture, 0, 0, RGB(255, 255, 255));
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


//==============================================================================================

struct Ventilation
{
    double x, y;
    int isOpened; //1 - открыта, 0 - закрыта
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
    double distance = sqrt(dx * dx + dy * dy); //теорема Пифагора
    if (distance < 20 && c.hasSword == 1)
    {
        v.isOpened = 1;
    }
    if (distance < 10 && v.isOpened == 1)
    {
        c.levelComplete = 1;
    }
}


//==============================================================================================

struct Barrel
{
    double x, y;
    int taken;
    HDC texture;
};

void drawBarrel(Barrel b)
{
    if (b.taken == 0)
        txTransparentBlt(txDC(), b.x - 20, b.y - 20, 40, 68, b.texture, 0, 0, RGB(255, 255, 255));

}

void actBarrel (Barrel &b, Corvo &c)
{
    double dx = c.x - b.x;
    double dy = c.y - b.y;
    double distance = sqrt(dx * dx + dy * dy); //теорема Пифагора
    if (distance < 20)
    {
        c.hasBarrel = 1;
        b.taken = 1;
    }
}


//==============================================================================================

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


//==============================================================================================

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
        txTransparentBlt(txDC(), b.x - 20, b.y - 20, 40, 40, b.textureOff, 0, 0, RGB(255, 255, 255));
        txSetColor(RGB(128, 128, 128));
        txSetFillColor(RGB(128, 128, 128));
        txRectangle(b.barrierX - 22, b.barrierY - 22, b.barrierX + 22, b.barrierY + 22);
    }
    else
    {
        txTransparentBlt(txDC(), b.x - 20, b.y - 20, 40, 40, b.textureOn, 0, 0, RGB(255, 255, 255));
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


//==============================================================================================

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

//==============================================================================================

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

//==============================================================================================

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
        txTransparentBlt(txDC(), v.x - 20, v.y - 20, 40, 40, v.textureActive, 0, 0, RGB(255, 255, 255));
    }
    else
    {
        txTransparentBlt(txDC(), v.x - 20, v.y - 20, 40, 40, v.textureDesactive, 0, 0, RGB(255, 255, 255));
    }
}
void actVoidzone(Voidzone &v, Corvo &c)
{
    if (v.voidactive == 1)
    {

        double dx = c.x - v.x;
        double dy = c.y - v.y;
        double distance = sqrt(dx * dx + dy * dy); //теорема Пифагора
        if (distance < 20)
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

//==============================================================================================

struct Level
{
    Corvo c;
    Road roads[300];
    int roadsCount;
    Wall walls[300];
    int wallsCount;
    Sword swords[30];
    int swordsCount;
    Ventilation vents[30];
    int ventsCount;
    Barrel barrels[30];
    int barrelsCount;
    Trap traps[30];
    int trapsCount;
    Button buttons[30];
    int buttonsCount;
    Guard guards[30];
    int guardsCount;
    Voidzone voids[30];
    int voidsCount;
};

void createLevel(Level &l, string filename)
{
    l.c.texture = txLoadImage("CorvoTexture.bmp");
    l.c.hasSword = 0;
    l.c.hasBarrel = 0;
    l.c.levelComplete = 0;

    l.roadsCount = 0;
    l.wallsCount = 0;
    l.swordsCount = 0;
    l.ventsCount = 0;
    l.barrelsCount = 0;
    l.trapsCount = 0;
    l.buttonsCount = 0;
    l.guardsCount = 0;
    l.voidsCount = 0;

    FILE *file = fopen(filename.c_str(), "r");

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            char symbol;
            fscanf(file, " %c", &symbol);

            if (symbol == '#')
            {
                l.walls[l.wallsCount].y = 40 * i + 20;
                l.walls[l.wallsCount].x = 40 * j + 20;
                l.wallsCount++;
            }
            else
            {
                l.roads[l.roadsCount].y = 40 * i + 20;
                l.roads[l.roadsCount].x = 40 * j + 20;
                l.roadsCount++;

                if (symbol == 's')
                {
                    l.swords[l.swordsCount].y = 40 * i + 20;
                    l.swords[l.swordsCount].x = 40 * j + 20;
                    l.swords[l.swordsCount].has = 0;
                    l.swords[l.swordsCount].texture = txLoadImage("SwordTexture.bmp");
                    l.swordsCount++;
                }
                if (symbol == 'h')
                {
                    l.c.y = 40 * i + 20;
                    l.c.x = 40 * j + 20;
                    l.c.respY = 40 * i + 20;
                    l.c.respX = 40 * j + 20;
                }
                if (symbol == 'v')
                {
                    l.vents[l.ventsCount].y = 40 * i + 20;
                    l.vents[l.ventsCount].x = 40 * j + 20;
                    l.vents[l.ventsCount].texture = txLoadImage("VentTexture.bmp");
                    l.vents[l.ventsCount].textureOpened = txLoadImage("VentBrokenTexture.bmp");
                    l.vents[l.ventsCount].isOpened = 0;
                    l.ventsCount++;
                }
                if (symbol == 'b')
                {
                    l.barrels[l.barrelsCount].y = 40 * i + 20;
                    l.barrels[l.barrelsCount].x = 40 * j + 20;
                    l.barrels[l.barrelsCount].texture = txLoadImage("Pic\\BarrelTexture.bmp");
                    l.barrels[l.barrelsCount].taken = 0;
                    l.barrelsCount++;
                }
                if (symbol == 't')
                {
                    l.traps[l.trapsCount].y = 40 * i + 20;
                    l.traps[l.trapsCount].x = 40 * j + 20;
                    l.traps[l.trapsCount].texture = txLoadImage("TrapTexture.bmp");
                    l.trapsCount++;
                }
                if (symbol == 'B')
                {
                    l.buttons[l.buttonsCount].y = 40 * i + 20;
                    l.buttons[l.buttonsCount].x = 40 * j + 20;
                    l.buttons[l.buttonsCount].textureOff = txLoadImage("ButtonOffTexture.bmp");
                    l.buttons[l.buttonsCount].textureOn = txLoadImage("ButtonOnTexture.bmp");
                    l.buttons[l.buttonsCount].on = 0;
                    l.buttonsCount++;
                }
                if (symbol == 'g')
                {
                    l.guards[l.guardsCount].y = 40 * i + 20;
                    l.guards[l.guardsCount].x = 40 * j + 20;
                    l.guards[l.guardsCount].isDead = 0;
                    l.guardsCount++;
                }
                if (symbol == '@')
                {
                    l.voids[l.voidsCount].y = 40 * i + 20;
                    l.voids[l.voidsCount].x = 40 * j + 20;
                    l.voids[l.voidsCount].textureActive = txLoadImage("VoidOn.bmp");
                    l.voids[l.voidsCount].textureDesactive = txLoadImage("VoidOff.bmp");
                    l.voids[l.voidsCount].voidactive = 0;
                    l.voids[l.voidsCount].timer = 0;
                    l.voidsCount++;
                }
            }
        }
    }

    for (int i = 0; i < l.trapsCount; i++)
    {
        int y, x;
        fscanf(file, "%d%d", &y, &x);
        l.traps[i].toY = 40 * y + 20;
        l.traps[i].toX = 40 * x + 20;
    }

    for (int i = 0; i < l.buttonsCount; i++)
    {
        int y, x;
        fscanf(file, "%d%d", &y, &x);
        l.buttons[i].barrierY = 40 * y + 20;
        l.buttons[i].barrierX = 40 * x + 20;
    }

    for (int i = 0; i < l.guardsCount; i++)
    {
        int mode, v, coord1, coord2, angle;
        fscanf(file, "%d", &mode);
        l.guards[i].moveMode = mode;
        if (mode == 0)
        {
            fscanf(file, "%d", &angle);
            l.guards[i].angle = angle;
        }
        else
        {
            fscanf(file, "%d%d%d", &v, &coord1, &coord2);
            l.guards[i].v = v;
            l.guards[i].coord1 = 40 * coord1 + 20;
            l.guards[i].coord2 = 40 * coord2 + 20;
            l.guards[i].angle = 0;
        }
    }

    fclose(file);
}

void destroyLevel(Level &l)
{
    txDeleteDC(l.c.texture);
    for (int i = 0; i < l.swordsCount; i++)
    {
        txDeleteDC(l.swords[i].texture);
    }
    for (int i = 0; i < l.ventsCount; i++)
    {
        txDeleteDC(l.vents[i].texture);
        txDeleteDC(l.vents[i].textureOpened);
    }
    for (int i = 0; i < l.barrelsCount; i++)
    {
        txDeleteDC(l.barrels[i].texture);
    }
    for (int i = 0; i < l.trapsCount; i++)
    {
        txDeleteDC(l.traps[i].texture);
    }
    for (int i = 0; i < l.buttonsCount; i++)
    {
        txDeleteDC(l.buttons[i].textureOff);
        txDeleteDC(l.buttons[i].textureOn);
    }
    for (int i = 0; i < l.voidsCount; i++)
    {
        txDeleteDC(l.voids[i].textureActive);
        txDeleteDC(l.voids[i].textureDesactive);
    }
}

void drawLevel(Level l)
{
    for (int i = 0; i < l.roadsCount; i++)
        drawRoad(l.roads[i]);
    for (int i = 0; i < l.wallsCount; i++)
        drawWall(l.walls[i]);
    for (int i = 0; i < l.swordsCount; i++)
        drawSword(l.swords[i]);
    for (int i = 0; i < l.ventsCount; i++)
        drawVentilation(l.vents[i]);
    for (int i = 0; i < l.barrelsCount; i++)
        drawBarrel(l.barrels[i]);
    for (int i = 0; i < l.trapsCount; i++)
        drawTrap(l.traps[i]);
    for (int i = 0; i < l.buttonsCount; i++)
        drawButton(l.buttons[i]);
    for (int i = 0; i < l.guardsCount; i++)
        drawGuard(l.guards[i]);
    for (int i = 0; i < l.voidsCount; i++)
        drawVoidzone(l.voids[i]);
}


void playLevel(Level l)
{
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        drawLevel(l);

        for (int i = 0; i < l.swordsCount; i++)
            actSword(l.swords[i], l.c);
        for (int i = 0; i < l.ventsCount; i++)
            actVentilation(l.vents[i], l.c);
        for (int i = 0; i < l.barrelsCount; i++)
            actBarrel(l.barrels[i], l.c);
        for (int i = 0; i < l.trapsCount; i++)
            actTrap(l.traps[i], l.c);
        for (int i = 0; i < l.buttonsCount; i++)
            actButton(l.buttons[i], l.c);
        for (int i = 0; i < l.guardsCount; i++)
            actGuard(l.guards[i], l.c);
        for (int i = 0; i < l.voidsCount; i++)
            actVoidzone(l.voids[i], l.c);

        actCorvo(l.c);
        drawCorvo(l.c);

        if (l.c.levelComplete == 1)
            break;

        txSleep(0);
    }
}



//==============================================================================================
//==============================================================================================
//==============================================================================================

Level l0, l1, l2;

int main()
{
    txCreateWindow(800, 600);
    txBegin();

    createLevel(l0, "level0.txt");
    playLevel(l0);
    destroyLevel(l0);

    createLevel(l1, "level1.txt");
    playLevel(l1);
    destroyLevel(l1);

    createLevel(l2, "level2.txt");
    playLevel(l2);
    destroyLevel(l2);

}
