#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include "Libs\\TXLib.h"
#include "Libs\\wall.cpp"
#include "Libs\\Menu.cpp"
#include "Libs\\road.cpp"
#include "Libs\\massivs.cpp"
#include "Libs\\const.cpp"


using namespace std;


void saveMassive(kartinka* KART1, int nomer_kartinki)
{
    ofstream save("save.txt");

    for(int stroka = 0; stroka < 20; stroka++)
    {
        for (int stolbec = 0; stolbec < 15; stolbec++)
        {
             karta[stroka][stolbec] = "#";
        }
    }

    for(int stroka = 0; stroka < 20; stroka++)
    {
        for (int stolbec = 0; stolbec < 15; stolbec++)
        {
             save << karta[stroka][stolbec];

        }
    }
    for(int i = 0; i< nomer_kartinki; i++)
    {
        if (KART1[i].risovat)
        {
            save << KART1[i].znak;
        }
    }

    save.close();
}


int main()
{
    txCreateWindow(800 + SHIRINA_KNOPKI, 600);
    double pictureX;
    double pictureY;
    int nomer_kartinki = 0;


    kartinka pics[PICS_NUMBER];
    for (int nomer = 0; nomer < PICS_NUMBER; nomer++)
    {
        pics[nomer].picture = NULL;
        pics[nomer].risovat = false;
    }


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
                    pics[nomer].znak = knopki[Button_number].znak;
                }
            }
        }


        if(txMouseButtons() & 1  && txMouseX() > SHIRINA_KNOPKI
                            && pics[nomer_kartinki].picture != NULL)
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
                //two heroes
                if ((pics[nomer_kartinki].znak == "h" &&
                     pics[nomer].znak == "h"))
                {
                    many = true;
                }
                 //two knifes
                if ((pics[nomer_kartinki].znak == "s" &&
                     pics[nomer].znak == "s"))
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

    saveMassive(pics, nomer_kartinki);
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
