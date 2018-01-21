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
//const HDC buttonofftexture = tx
//&buttonofftexture

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


void readMassive(kartinka* KART1, int* nomer_kartinki)
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

            stroka_s_kartinkoi = stroka_s_kartinkoi.substr(pos_y + 1);
            string symbol = stroka_s_kartinkoi;
   /*
            HDC pic = txLoadImage(adress.c_str());
            HBITMAP hbm=(HBITMAP)Win32::GetCurrentObject(pic, OBJ_BITMAP);
            BITMAP bm;
            Win32::GetObject(hbm,sizeof(bm), (LPVOID)&bm);
*/
            //txBitBlt (txDC(), atoi(x.c_str()), atoi(y.c_str()), bm.bmWidth, bm.bmHeight, pic, 0, 0);
            KART1[nomer] = {atoi(x.c_str()), atoi(y.c_str()), 40, 40, NULL, true, symbol.c_str()};

            nomer++;
        }
    }

    *nomer_kartinki = nomer;

    map_file.close();
}


/*void pictur (kartinka* pics, int* nomer_kartinki)
{
    pics[0] = {280, 120, 40, 40, txLoadImage("Pictures\\barrel.bmp"), true, "b"};
    pics[1] = {280, 80, 40, 40, txLoadImage("Pictures\\GuardText.bmp"), true, "1"};
    pics[2] = {320, 80, 40, 40, txLoadImage("Pictures\\stenka.bmp"), true, "1"};
    pics[3] = {360, 80, 40, 40, txLoadImage("Pictures\\corvo.bmp"), true, "1"};
    pics[4] = {320, 120, 40, 40, txLoadImage("Pictures\\TrapTexture.bmp"), true, "1"};
    *nomer_kartinki = 5;
} */

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
    //pictur (pics, &nomer_kartinki);
    readMassive(pics, &nomer_kartinki);
    for (int nomer = 0; nomer < nomer_kartinki; nomer++)
    {
        if (strcmp (pics[nomer].znak, "b") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\barrel.bmp");

        }
        if (strcmp (pics[nomer].znak, "#") == 0)
        {
            pics[nomer].picture = txLoadImage("Pictures\\stenka.bmp");

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
