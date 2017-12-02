#include <cmath>
#include "Libs/TXLib.h"
#include "Libs/wall.h"
#include "Libs/Menu.h"
#include "Libs/massivs.h"


//const HDC buttonofftexture = tx
//&buttonofftexture





int main() {
    txCreateWindow(800, 600);
    int nomer_kartinki = 1;

    //Init
    image pics[PICS_NUMBER];
    for (auto &pic : pics) {
        pic.picture = nullptr;
        pic.draw = false;
    }

    massButt();

    while (!GetAsyncKeyState(VK_ESCAPE)) {
        txBegin();
        txSetFillColor(TX_BLACK);
        txClear();

        txSetColour(RGB(0, 0, 0), 1);
        txSetFillColour(RGB(255, 255, 255));
        txSelectFont("Times New Roman", 25);
        for (auto &Button_number : knopki) {
            dButton(Button_number);

            //Saving pic into buffer
            if (txMouseButtons() & 1
                && txMouseX() >= Button_number.x
                && txMouseX() <= Button_number.x + SHIRINA_KNOPKI
                && txMouseY() >= Button_number.y
                && txMouseY() <= Button_number.y + VISOTA_KNOPKI) {
                for (int nomer = nomer_kartinki; nomer < PICS_NUMBER; nomer++) {
                    pics[nomer].picture = Button_number.kartinka;
                }
            }
        }


        if (txMouseButtons() & 1 && txMouseX() > SHIRINA_KNOPKI) {
            pics[nomer_kartinki].x = static_cast<int>(round(txMouseX() / 40) * 40);
            pics[nomer_kartinki].y = static_cast<int>(round(txMouseY() / 40) * 40);
            pics[nomer_kartinki].height = 40;
            pics[nomer_kartinki].width = 40;

            //Checking if here exists another picture
            bool many = false;
            for (int nomer = 0; nomer < nomer_kartinki; nomer++) {
                if ((pics[nomer_kartinki].x == pics[nomer].x &&
                     pics[nomer_kartinki].y == pics[nomer].y)) {
                    many = true;
                }
            }

            if (!many) {
                pics[nomer_kartinki].draw = true;
            }

            //txSleep (10);
        }

        for (auto nomer = 0; nomer < PICS_NUMBER; nomer++) {
            if (pics[nomer].draw) {
                txBitBlt(txDC(), pics[nomer].x, pics[nomer].y, pics[nomer].width, pics[nomer].height,
                         reinterpret_cast<HDC>(pics[nomer].picture), 0, 0);
                nomer_kartinki = nomer + 1;
            }
        }

        if (txMouseButtons() & 2) {
            for (int nomer = 0; nomer < nomer_kartinki; nomer++) {
                if (pics[nomer].x >= txMouseX() - SHIRINA_OBJ &&
                    pics[nomer].x <= txMouseX() + SHIRINA_OBJ &&
                    pics[nomer].y >= txMouseY() - SHIRINA_OBJ &&
                    pics[nomer].y <= txMouseY() + SHIRINA_OBJ) {
                    pics[nomer].draw = false;
                    pics[nomer].picture = nullptr;
                    //nomer_kartinki = nomer - 1;
                    txSleep(5);
                }
            }
        }

        txSleep(10);
        txEnd();
    }

    for (auto &pic : pics) {
        txDeleteDC(pic.picture);
    }

    for (auto &nomer : knopki) {
        txDeleteDC(nomer.kartinka);
    }
    return 0;
}
