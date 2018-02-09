#include "stdio.h"
#include "dirent.h"
#include "Libs\\TXLib.h"
#include <cstring>
#include "Libs\\corvo.cpp"
#include "Libs\\guard.cpp"
#include "Libs\\trap.cpp"
#include "Libs\\ventilation.cpp"
#include "Libs\\barrel.cpp"
#include "Libs\\sword.cpp"
#include "Libs\\button.cpp"
#include "Libs\\road.cpp"
#include "Libs\\wall.cpp"
#include "Libs\\voidzone.cpp"
#include "Libs\\level.cpp"
#include "Libs\\const.cpp"
#include "Libs\\BuildLevel.cpp"

Level l0;

int main()
{
    int screenSizeX = 800;
    txCreateWindow(screenSizeX, 600);
    txBegin();


    DIR *mydir;
    struct dirent *filename;
    char *dirname = "Levels\\";
    int nomer = 0;
    int otstup = 20;
    int X_knopki = 100;//800 / sqrt(nomer) - otstup;
    int Y_knopki = 100;//600 / sqrt(nomer) - otstup;
    int x = otstup;
    int y = otstup;
    int time;

    if ((mydir = opendir (dirname)) != NULL)
    {
        while ((filename = readdir (mydir)) != NULL)
        {
            if ((strcmp(".", filename->d_name) !=0) and (strcmp("..", filename->d_name) != 0))
            {
                if (x >= screenSizeX - X_knopki)
                {
                    x = otstup;
                    y += Y_knopki + otstup;
                }

                char* levelmaker = new char[100];
                strcpy(levelmaker, filename->d_name);

                files[nomer] = {x, y, X_knopki, Y_knopki, levelmaker};

                nomer++;
                x = x + X_knopki + otstup + 10;
            }
        }
        closedir (mydir);


//        Всего уровней nomer штук (15 например)
        x = otstup;
        y = otstup;
        for (int i = 0; i < nomer; i++)
        {
            files[i].width =  800 / trunc(sqrt(nomer) + 0.999) - 2 * otstup;
            files[i].height = 600 / trunc(sqrt(nomer) + 0.999) - 2 * otstup;
            if (x >= screenSizeX - files[i].width)
            {
                x = otstup;
                y += files[i].height + otstup;
            }
            files[i].x = x;
            files[i].y = y;
            x = x + files[i].width + otstup;
        }


        while (!GetAsyncKeyState(VK_ESCAPE))
        {
            txSetFillColor(TX_BLACK);
            txClear();

            if (gamemode == "levelchooser")
            {
                for (int i = 0; i < nomer; i++)
                {
                    txSetColor(TX_BLACK);
                    txSetFillColor(TX_WHITE);
                    txRectangle(files[i].x, files[i].y, files[i].x + files[i].width, files[i].y + files[i].height);
                    txTextOut(files[i].x + 15, files[i].y + 15, files[i].text);
                }

                for (int i = 0; i < nomer; i++)
                {
                    if ( txMouseX() >= files[i].x
                    && txMouseX() <= files[i].x + files[i].width
                    && txMouseY() >= files[i].y
                    && txMouseY() <= files[i].y + files[i].height)
                    {
                        txSetColor(RGB(0, 255, 0));
                        txTextOut(txMouseX(), txMouseY(), files[i].text);
                    }

                    if (txMouseButtons() & 1
                    && txMouseX() >= files[i].x
                    && txMouseX() <= files[i].x + files[i].width
                    && txMouseY() >= files[i].y
                    && txMouseY() <= files[i].y + files[i].height)
                    {
                        createLevel(l0, files[i].text);
                        playLevel(l0);
                        destroyLevel(l0);
                    }
                }
            }
            else if (gamemode == "story")
            {
                for (int i = 0; i < nomer; i++)
                {
                    createLevel(l0, files[i].text);
                    playLevel(l0);
                    destroyLevel(l0);
                    txSleep(3000);
                }
            }

            txSleep(100);
        }
    }
    else
    {
          perror ("no directory");
    }
}
  /*                  createLevel(l0, files[i].text);
                    playLevel(l0);
                    destroyLevel(l0); */
