#include "stdio.h"
#include "dirent.h"
#include "TXLib.h"
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

Level l0;

int main()
{
    txCreateWindow(800, 600);
    txBegin();


    DIR *mydir;
    struct dirent *filename;
    char *dirname = "D:\\CodeBlocks\\projects\\2017-2018\\lab ver1\\Labirint-master\\Game\\Levels\\";
    printf("%s\n", dirname);

    if ((mydir = opendir (dirname)) != NULL)
    {
        while ((filename = readdir (mydir)) != NULL)
        {
            printf("%s\n", filename->d_name);
            if
           // createLevel(l0, filename->d_name);
            //playLevel(l0);
            //destroyLevel(l0);
        }
        closedir (mydir);
    }
    else
    {
          perror ("no directory");
    }




}
