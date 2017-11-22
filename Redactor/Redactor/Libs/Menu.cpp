#include "TXLib.h"
#include "const.cpp"

struct Button {
    int x,y;
    const char* text;
    const char* znak;
    HDC kartinka;
};

Button b[KOLICHESTVO_KNOPOK];

void dButton(Button b)
{
    txSetColor(RGB(0, 0, 0), 1);
    txSetFillColor(RGB(255, 255, 255));
    txSelectFont("Times New Roman", 25);
    txRectangle(b.x, b.y, b.x + SHIRINA_KNOPKI , b.y + VISOTA_KNOPKI);
    txTextOut(b.x + 10, b.y + 15, b.text);
}

void massButt()
{
    b[0] = {0, 0,   "wall", "#", txLoadImage("stenka.bmp")};
    b[1] = {0, 50,  "road", ".", txLoadImage("doroga.bmp")};
    b[2] = {0, 100, "hero", "h", txLoadImage("corvo.bmp")};
    b[3] = {0, 150, "knife", "s", txLoadImage("noj.bmp")};
    b[4] = {0, 200, "ventilation", "v", txLoadImage("vint.bmp")};
    b[5] = {0, 250, "barrel", "b", txLoadImage("barrel.bmp")};
    b[6] = {0, 300, "trap", "t", txLoadImage("trap.bmp")};
    b[7] = {0, 350, "button", "B", txLoadImage("button.bmp")};
    b[8] = {0, 400, "guard", "g", txLoadImage("guard.bmp")};
    b[9] = {0, 400, "void", "@", txLoadImage("void.bmp")};
}
