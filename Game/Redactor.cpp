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

    for(int i = 0; i< nomer_kartinki; i++)
    {
        if (KART1[i].risovat)
        {
            save << KART1[i].x - SHIRINA_KNOPKI << "," << KART1[i].y << "," << KART1[i].znak << endl;
        }
    }

    save.close();
}


int readMassive(kartinka* KART1)
{
    ifstream map_file;
    string stroka_s_kartinkoi = "1";
    map_file.open("save.txt");
    int nomer = 0;

    while (map_file.good() && strlen(stroka_s_kartinkoi.c_str()) > 0) {

        getline (map_file, stroka_s_kartinkoi);

        if (strlen(stroka_s_kartinkoi.c_str()) > 0)
        {
            int pos_x = stroka_s_kartinkoi.find(',');
            string x = stroka_s_kartinkoi.substr(0, pos_x);

            stroka_s_kartinkoi = stroka_s_kartinkoi.substr(pos_x + 1);
            int pos_y = stroka_s_kartinkoi.find(',');
            string y = stroka_s_kartinkoi.substr(0, pos_y);

            string symbol = stroka_s_kartinkoi.substr(pos_y + 1);

            char* symbol2 = new char[1];
            strcpy(symbol2, symbol.c_str());

            KART1[nomer] = {atoi(x.c_str()) + SHIRINA_KNOPKI, atoi(y.c_str()), 40, 40, NULL, true, symbol2};
            nomer++;
        }
    }

    map_file.close();

    return nomer;
}

int main()
{
    txCreateWindow(800 + SHIRINA_KNOPKI, 600);
    double pictureX;
    double pictureY;
    int nomer_kartinki = 0;

    //Init
    kartinka pics[PICS_NUMBER];
    for (int nomer = 0; nomer < PICS_NUMBER; nomer++)
    {
        pics[nomer].znak = NULL;
        pics[nomer].picture = NULL;
        pics[nomer].risovat = false;
    }

    massButt();

    nomer_kartinki = readMassive(pics);
    for (int nomer = 0; nomer < nomer_kartinki; nomer++)
    {
        if (strcmp (pics[nomer].znak, "b") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\barrel.bmp");
        }
        else if (strcmp (pics[nomer].znak, "#") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\stenka.bmp");
        }
        else if (strcmp (pics[nomer].znak, ".") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\doroga.bmp");
        }
        else if (strcmp (pics[nomer].znak, "s") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\noj.bmp");
        }
        else if (strcmp (pics[nomer].znak, "h") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\corvo.bmp");
        }
        else if (strcmp (pics[nomer].znak, "v") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\vint.bmp");
        }
        else if (strcmp (pics[nomer].znak, "t") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\trap.bmp");
        }
        else if (strcmp (pics[nomer].znak, "B") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\button.bmp");
        }
        else if (strcmp (pics[nomer].znak, "g") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\guard.bmp");
        }
        else if (strcmp (pics[nomer].znak, "@") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\void.bmp");
        }

        else
        {
            pics[nomer].risovat = false;
        }
    }



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
