#include <iostream>
#include <math.h>
#include "Libs\\TXLib.h"
#include "Libs\\wall.cpp"
#include "Libs\\Menu.cpp"
#include "Libs\\road.cpp"
#include "Libs\\massivs.cpp"
#include "Libs\\const.cpp"


//const HDC buttonofftexture = tx
//&buttonofftexture


void pictur (kartinka* pics, int* nomer_kartinki)
{
    pics[0] = {280, 120, 40, 40, txLoadImage("Pictures\\barrel.bmp"), true};
    pics[1] = {280, 80, 40, 40, txLoadImage("Pictures\\GuardText.bmp"), true};
    pics[2] = {320, 80, 40, 40, txLoadImage("Pictures\\stenka.bmp"), true};
    pics[3] = {360, 80, 40, 40, txLoadImage("Pictures\\corvo.bmp"), true};
    pics[4] = {320, 120, 40, 40, txLoadImage("Pictures\\TrapTexture.bmp"), true};
    *nomer_kartinki = 5;
}

int main()
{
    txCreateWindow(800, 600);
    double pictureX;
    double pictureY;
    int nomer_kartinki = 0;

    //Init
    kartinka pics[PICS_NUMBER];
    for (int nomer = 0; nomer < PICS_NUMBER; nomer++)
    {
        pics[nomer].picture = NULL;
        pics[nomer].risovat = false;
    }

    pictur (pics, &nomer_kartinki);

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
            dButton(knopki[Button_number]);

            //Saving pic into buffer
            if (txMouseButtons() & 1
            && txMouseX() >= knopki[Button_number].x
            && txMouseX() <= knopki[Button_number].x + SHIRINA_KNOPKI
            && txMouseY() >= knopki[Button_number].y
            && txMouseY() <= knopki[Button_number].y + VISOTA_KNOPKI)
            {
                for (int nomer = nomer_kartinki; nomer < PICS_NUMBER; nomer++)
                {
                    pics[nomer].picture = knopki[Button_number].kartinka;
                }
            }
        }


        if(txMouseButtons() & 1  && txMouseX() > SHIRINA_KNOPKI)
        {
            pics[nomer_kartinki].x = round (txMouseX() / 40) * 40;
            pics[nomer_kartinki].y = round (txMouseY() / 40) * 40;
            pics[nomer_kartinki].height = 40;
            pics[nomer_kartinki].width = 40;

            //Checking if here exists another picture
            bool many = false;
            for (int nomer = 0; nomer < nomer_kartinki; nomer++)
            {
                if ((pics[nomer_kartinki].x == pics[nomer].x &&
                     pics[nomer_kartinki].y == pics[nomer].y))
                {
                    many = true;
                }
            }

            if (!many)
            {
                pics[nomer_kartinki].risovat = true;
            }

            //txSleep (10);
        }

        for (int nomer = 0; nomer < PICS_NUMBER; nomer++)
        {
            if (pics[nomer].risovat)
            {
                txBitBlt(txDC(), pics[nomer].x, pics[nomer].y, pics[nomer].width, pics[nomer].height, pics[nomer].picture, 0, 0);
                nomer_kartinki = nomer + 1;
            }
        }

        if (txMouseButtons() &2)
        {
            for (int nomer = 0; nomer < nomer_kartinki; nomer++)
            {
                if (pics[nomer].x >= txMouseX() - SHIRINA_OBJ &&
                    pics[nomer].x <= txMouseX() + SHIRINA_OBJ &&
                    pics[nomer].y >= txMouseY() - SHIRINA_OBJ &&
                    pics[nomer].y <= txMouseY() + SHIRINA_OBJ)
                {
                  pics[nomer].risovat = false;
                  pics[nomer].picture = NULL;
                  //nomer_kartinki = nomer - 1;
                  txSleep (5);
                }
            }
        }

        txSleep (10);
        txEnd();
    }

    for (int nomer = 0; nomer < PICS_NUMBER; nomer++)
    {
        txDeleteDC (pics[nomer].picture);
    }

    for (int nomer = 0; nomer < KOLICHESTVO_KNOPOK; nomer++)
    {
          txDeleteDC(knopki[nomer].kartinka);
    }
    return 0;
}
