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





Level l0, l1, l2;

int main()
{
    txCreateWindow(800, 600);
    txBegin();

    createLevel(l0, "Levels\\level0.txt");
    playLevel(l0);
    destroyLevel(l0);

    createLevel(l1, "Levels\\level1.txt");
    playLevel(l1);
    destroyLevel(l1);

    createLevel(l2, "Levels\\level2.txt");
    playLevel(l2);
    destroyLevel(l2);

}
