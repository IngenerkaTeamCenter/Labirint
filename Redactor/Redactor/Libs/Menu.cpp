#include "TXLib.h"
#include "const.cpp"

struct Button {
    int x,y;
    const char* text;
};

Button b[KOLICHESTVO_KNOPOK];

void dButton(Button b)
{
    txSetColor(RGB(0, 0, 0), 1);
    txSetFillColor(RGB(255, 255, 255));
    txSelectFont("Times New Roman", 25);
    txRectangle(b.x, b.y, b.x + SHIRINA_KNOPKI , b.y + 50);
    txTextOut(b.x + 10, b.y + 15, b.text);
}

void massButt()
{
    b[0] = {0, 0,   "stena"};
    b[1] = {0, 50,  "doroga"};
    b[2] = {0, 100, "glavny geroi"};
    b[3] = {0, 150, "dfg"};
    b[4] = {0, 200, "dfg"};
    b[5] = {0, 250, "dfg"};
    b[6] = {0, 300, "dfgdf"};
    b[7] = {0, 350, "dfg"};
    b[8] = {0, 400, "dfgdfsg"};
}
