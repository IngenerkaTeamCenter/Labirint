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
    txCreateWindow(800, 600);
    txBegin();


    DIR *mydir;
    struct dirent *filename;
    char *dirname = "Levels\\";
    int x = 0;
    int nomer = 0;

    if ((mydir = opendir (dirname)) != NULL)
    {
        while ((filename = readdir (mydir)) != NULL)
        {
            if ((strcmp(".", filename->d_name) !=0) and (strcmp("..", filename->d_name) != 0))
            {
                char* levelmaker = new char[100];
                strcpy(levelmaker, filename->d_name);

                txSetColor(TX_BLACK);
                txRectangle(x, 0, x + 200, 100);
                txTextOut(x, 0, levelmaker);

                files[nomer] = {x,0,200,100, levelmaker};


                nomer++;
                x = x + 200;
            }
        }
        closedir (mydir);

        while (!GetAsyncKeyState(VK_ESCAPE))
        {
            if (gamemode == "levelchooser")
            {
                for (int i = 0; i < nomer; i++)
                {
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
