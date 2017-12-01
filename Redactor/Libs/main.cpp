#include <iostream>
#include <math.h>
#include "TXLib.h"
#include "wall.cpp"
#include "Menu.cpp"
#include "road.cpp"
#include "massivs.cpp"
#include "const.cpp"

void drawMouseWall(int x, int y)
{
    txSetColor(RGB(128, 128, 128));
    txSetFillColor(RGB(128, 128, 128));
    txRectangle(x - SHIRINA_OBJ, y - SHIRINA_OBJ, x + SHIRINA_OBJ, y + SHIRINA_OBJ);
}

void drawMouseRoad(int x, int y)
{
    txSetColor(RGB (100, 0, 0));
    txSetFillColor(RGB (100, 0, 0));
    txRectangle(x - SHIRINA_OBJ, y - SHIRINA_OBJ, x + SHIRINA_OBJ, y + SHIRINA_OBJ);
}

int main()
{
    txCreateWindow(800, 600);
    int nomer_kartinki = 1;
    double pictureX;
    double pictureY;

    int picsNumber = 240;

    kartinka pics[picsNumber];
    for (int nomer = 0; nomer < picsNumber; nomer++)
    {
        pics[nomer].picture = NULL;
        pics[nomer].risovat = false;
    }

    pics[0] = {200, 200, 40, 40, txLoadImage("stenka.bmp"), true};


    massButt();

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_BLACK);
        txClear();

        txSetColour(RGB(0, 0, 0), 1);
        txSetFillColour(RGB(255, 255, 255));
        txSelectFont("Times New Roman", 25);
        for (int Button_number = 0; Button_number < KOLICHESTVO_KNOPOK; Button_number++)
        {
            dButton(b[Button_number]);
            if (txMouseButtons() & 1
            && txMouseX() >= b[Button_number].x
            && txMouseX() <= b[Button_number].x + SHIRINA_KNOPKI
            && txMouseY() >= b[Button_number].y
            && txMouseY() <= b[Button_number].y + VISOTA_KNOPKI)
            {
                if (Button_number == 0)
                {
                    for (int nomer = nomer_kartinki; nomer < picsNumber; nomer++)
                    {
                        pics[nomer].picture = txLoadImage("stenka.bmp");
                    }
                }
                else if (Button_number == 1)
                {
                    for (int nomer = nomer_kartinki; nomer < picsNumber; nomer++)
                    {
                        pics[nomer].picture = txLoadImage("doroga.bmp");
                    }
                }
            }
        }


        if(txMouseButtons() & 1
           && txMouseX() > SHIRINA_KNOPKI/* && txGetPixel(txMouseX(), txMouseY()) == TX_BLACK*/)
        {
            pictureX = txMouseX();
            pictureY = txMouseY();

            while (!(floor(pictureX/40)==pictureX/40))
            {
                pictureX--;
            }

            while (!(floor(pictureY/40)==pictureY/40))
            {
                pictureY--;
            }

            pics[nomer_kartinki].risovat = true;
            pics[nomer_kartinki].x = pictureX;
            pics[nomer_kartinki].y = pictureY;
            pics[nomer_kartinki].height = 40;
            pics[nomer_kartinki].width = 40;

            nomer_kartinki++;
            txSleep (10);
        }
        for (int nomer = 0; nomer < picsNumber; nomer++)
        {
            if (pics[nomer].risovat)
            {
                txBitBlt(txDC(), pics[nomer].x, pics[nomer].y, pics[nomer].width, pics[nomer].height, pics[nomer].picture, 0, 0);
            }
        }

        txSleep (10);
        txEnd();
    }

    for (int nomer = 0; nomer < picsNumber; nomer++)
    {
        txDeleteDC (pics[nomer].picture);
    }
    return 0;
}
