#include "TXLib.h"

struct kartinka
{
    int x;
    int y;
    int height;
    int width;
    HDC picture;
    bool risovat;
    const char* znak;
};
char* karta[20][15];
