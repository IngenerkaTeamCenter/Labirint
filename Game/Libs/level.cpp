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
    l.c.texture = txLoadImage("Pictures\\CorvoTexture.bmp");
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
                    l.swords[l.swordsCount].texture = txLoadImage("Pictures\\SwordTexture.bmp");
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
                    l.vents[l.ventsCount].texture = txLoadImage("Pictures\\VentTexture.bmp");
                    l.vents[l.ventsCount].textureOpened = txLoadImage("Pictures\\VentBrokenTexture.bmp");
                    l.vents[l.ventsCount].isOpened = 0;
                    l.ventsCount++;
                }
                if (symbol == 'b')
                {
                    l.barrels[l.barrelsCount].y = 40 * i + 20;
                    l.barrels[l.barrelsCount].x = 40 * j + 20;
                    l.barrels[l.barrelsCount].texture = txLoadImage("Pictures\\BarrelTexture.bmp");
                    l.barrels[l.barrelsCount].taken = 0;
                    l.barrelsCount++;
                }
                if (symbol == 't')
                {
                    l.traps[l.trapsCount].y = 40 * i + 20;
                    l.traps[l.trapsCount].x = 40 * j + 20;
                    l.traps[l.trapsCount].texture = txLoadImage("Pictures\\TrapTexture.bmp");
                    l.trapsCount++;
                }
                if (symbol == 'B')
                {
                    l.buttons[l.buttonsCount].y = 40 * i + 20;
                    l.buttons[l.buttonsCount].x = 40 * j + 20;
                    l.buttons[l.buttonsCount].textureOff = txLoadImage("Pictures\\ButtonOffTexture.bmp");
                    l.buttons[l.buttonsCount].textureOn = txLoadImage("Pictures\\ButtonOnTexture.bmp");
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
                    l.voids[l.voidsCount].textureActive = txLoadImage("Pictures\\VoidOn.bmp");
                    l.voids[l.voidsCount].textureDesactive = txLoadImage("Pictures\\VoidOff.bmp");
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

