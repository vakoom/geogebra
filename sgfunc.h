#include "sg.h"

#ifndef __SGFUNC__
#define __SGFUNC__

void drawLine(int x1, int y1, int x2, int y2);
void drawCircle(int x, int y, int r);
void drawRectangle(int x1, int y1, int x2, int y2);
void drawEllipse(int x, int y, int a, int b);
//-------------------------------------------
void selectPen(int r, int g, int b, int thickness);
void selectBrush(int r, int g, int b);
void selectNullPen();
void selectNullBrush();

//===========================================

void drawLine(int x1, int y1, int x2, int y2)
{
    MoveToEx(SGDC, x1, y1, 0);
    LineTo(SGDC, x2, y2);
}

void drawCircle(int x, int y, int r)
{
    Ellipse(SGDC, x - r, y - r, x + r, y + r);
}

void drawEllipse(int x, int y, int a, int b)
{
    Ellipse(SGDC, x - a, y - b, x + a, y + b);
}

void drawRectangle(int x1, int y1, int x2, int y2)
{
    Rectangle(SGDC, x1, y1, x2, y2);
}

void selectNullBrush()
{
    sgSelectTool(SGDC, GetStockObject(NULL_BRUSH));
}

void selectNullPen()
{
    sgSelectTool(SGDC, CreatePen(PS_NULL, 0, RGB(0, 0, 0)));
}

void selectPen(int a, int b, int c, int thickness)
{
    sgSelectTool(SGDC, CreatePen(PS_SOLID, thickness, RGB(a, b, c)));
}

void selectBrush(int r, int g, int b)
{
    sgSelectTool(SGDC, CreateSolidBrush(RGB(r, g, b)));
}
#endif
