#include <cstdio>
#include "dirent.h"
#include "Libs/TXLib.h"
#include "Libs/level.h"

Level l0;

int main() {
    txCreateWindow(800, 600);
    txBegin();


    DIR *mydir;
    struct dirent *filename;
    auto *dirname = const_cast<char *>("Levels\\");
    printf("%s\n", dirname);
    int x = 0;

    if ((mydir = opendir(dirname)) != nullptr) {
        while ((filename = readdir(mydir)) != nullptr) {
            if ((strcmp(".", filename->d_name) != 0) and (strcmp("..", filename->d_name) != 0)) {
                txSetColor(TX_BLACK);
                txRectangle(x, 0, x + 200, 100);
                txTextOut(x, 0, filename->d_name);
                x = x + 200;
                //printf("%s\n", filename->d_name);
                /*createLevel(l0, filename->d_name);
                playLevel(l0);
                destroyLevel(l0);*/
            }
        }
        closedir(mydir);

        while (!GetAsyncKeyState(VK_ESCAPE)) {
            if (txMouseButtons() & 1
                && txMouseX() >= 0
                && txMouseX() <= 200
                && txMouseY() >= 0
                && txMouseY() <= 100) {
                createLevel(l0, (string &) "level0.txt");
                playLevel(l0);
                destroyLevel(l0);
            }

            if (txMouseButtons() & 1
                && txMouseX() >= 200
                && txMouseX() <= 400
                && txMouseY() >= 0
                && txMouseY() <= 100) {
                createLevel(l0, (string &) "level1.txt");
                playLevel(l0);
                destroyLevel(l0);
            }
            if (txMouseButtons() & 1
                && txMouseX() >= 400
                && txMouseX() <= 600
                && txMouseY() >= 0
                && txMouseY() <= 100) {
                createLevel(l0, (string &) "level2.txt");
                playLevel(l0);
                destroyLevel(l0);
            }
            txSleep(100);
        }
    } else {
        perror("no directory");
    }
}
