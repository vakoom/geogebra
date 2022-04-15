#include "fraction.h"
using namespace std;

class R1 : public Rectangle3{

};
class R2 : public Rectangle3{

};
int main() {

    vector<Rectangle3*> v;
    v.push_back(new R1());

    int h = 600, w = 600;
    sgCreateWindow(w, h);
    Rectangle3 U(0, 0, w, h);
    int minih = 20, miniw = 40, gaph = 10, gapw = 10, x0 = 10, y0 = 10;
    Rectangle3 drawVisLine(x0, y0, x0 + miniw, y0 + minih);
    Rectangle3 drawVisCircle(x0 + gapw + miniw, y0, x0 + gapw + miniw*2, y0 + minih);
    Rectangle3 drawCross2Lines(x0, y0 + gaph + minih, x0 + miniw, y0 + gaph + minih*2);
    Rectangle3 drawCrossLC(x0 + gapw + miniw, y0 + gaph + minih, x0 + gapw + miniw*2, y0 + gaph + minih*2);
    Rectangle3 drawPerp(x0 + gapw*2 + miniw*2, y0 + gaph + minih, x0 + gapw*2 + miniw*3, y0 + gaph + minih*2);



    drawVisLine.drawRect();
    drawVisCircle.drawRect();
    drawCross2Lines.drawRect();
    drawCrossLC.drawRect();
    drawPerp.drawRect();
    selectPen(0, 0, 0, 2);
    drawLine(x0+5, y0+5, x0 + miniw - 5, y0 + minih - 5);
    drawCircle(x0 + gapw + miniw * 1.5, y0 + minih*0.5, min(miniw/2 - 5, minih/2 - 5));
    drawLine(x0+5, y0 + gaph + minih + 5, x0 + miniw - 5, y0 + gaph + minih*2 - 5);
    drawLine(x0+miniw-5, y0 + gaph + minih + 5, x0 + 5, y0 + gaph + minih*2 - 5);
    drawLine(x0 + gapw + miniw + 5, y0 + gaph + minih + 5, x0 + gapw + miniw*2 - 5, y0 + gaph + minih*2 - 5);
    drawCircle(x0 + gapw + miniw*1.5, y0 + gaph + minih*1.5, min(miniw/2 - 5, minih/2 - 5));
    drawLine(x0 + gapw*2 + miniw*2 + 5, y0 + gaph + minih*2 - 5, x0 + gapw*2 + miniw*3 - 5, y0 + gaph + minih*2 - 5);
    drawLine(x0 + gapw*2 + miniw*2.5, y0 + gaph + minih + 5, x0 + gapw*2 + miniw*2.5, y0 + gaph + minih*2 - 5);
    selectNullPen();
    vector<VisPoint> visPoints;
    vector<VisLine> visLines;
    vector<VisCircle> visCircles;

    bool isNew = true, pressed = false, oldPoint = false, oldLine = false, oldCirle = false;
    int oldPointNumber = 0, oldCircleNumber = 0, oldLineNumber = 0;
    VisPoint last1(0, 0), last(1, 0);
    VisCircle lastC(Point(0, 0), Point(0, 1));
    VisLine lastl1(Point(0, 0), Point(0, 1)), lastl(Point(0, 0), Point(0, 1));
    while (!GetAsyncKeyState(VK_ESCAPE) && sgGetMouseButtons() != 2) {
        if (sgGetMouseButtons() == 1 && !pressed) {
            pressed = true;

            int x = sgGetMouseX(), y = sgGetMouseY(); // new click
            VisPoint newVisPoint(x, y);
            Point newPoint(x, y);

            if (drawVisLine.insideRect(newVisPoint)){    // buttons
                getNewVisLine(h, visLines, last, last1);
                cout << "new line" << endl;
                isNew = false;
            } else if (drawVisCircle.insideRect(newVisPoint)){
                getNewVisCircle(visCircles, last1, last);
                cout << "new circle" << endl;
                isNew = false;
            } else if (drawCross2Lines.insideRect(newVisPoint)){
                getNewCrossPoint(visPoints, lastl, lastl1);
                cout << "line cross" << endl;
                isNew = false;
            } else if (drawPerp.insideRect(newVisPoint)){
                getFootPerpPoint(h, visLines, visPoints, lastl, last);
                cout << "foot" << endl;
                isNew = false;
            } else if (drawCrossLC.insideRect(newVisPoint)){
                getCrossLC(visPoints, lastl, lastC);
                cout << "l and c cross" << endl;
                isNew = false;
            }

            for (int i = 0; i < visPoints.size(); ++i){ // old point?
                if (newVisPoint.inside(visPoints[i])){
                    cout << "sel" << endl;
                    oldPoint = true;
                    oldPointNumber = i;
                    isNew = false;
                    break;
                }
            }
            for (int i = 0; i < visCircles.size(); ++i){
                if (abs(newPoint.dist(visCircles[i].a, visCircles[i].b) - visCircles[i].r) <= 4){
                    cout << "sel circle" << endl;
                    oldCirle = true;
                    oldCircleNumber = i;
                    isNew = false;
                    break;
                }
            }
            for (int i = 0; i < visLines.size(); ++i){ // old line?
                if (abs(-(visLines[i].b * newPoint.y + visLines[i].c) / visLines[i].a - newPoint.x) <= 5 ||
                    abs(-(visLines[i].a * newPoint.x + visLines[i].c) / visLines[i].b - newPoint.y) <= 5){
                    cout << "sel line" << endl;
                    oldLine = true;
                    oldLineNumber = i;
                    isNew = false;
                    break;
                }
            }
            if (isNew){ // new point
                visPoints.push_back(newVisPoint);
                visPoints[visPoints.size() - 1].selected = false;
                cout << "new" << endl;
            } else {

                // old point/line/circle
                isNew = true;
                if (oldPoint) {
                    // point
                    visPoints[oldPointNumber].selected = !visPoints[oldPointNumber].selected;
                    last1.a = last.a; last1.b = last.b;
                    last.a = visPoints[oldPointNumber].a; last.b = visPoints[oldPointNumber].b;
                } else if (oldCirle) {
                    // circle
                    visCircles[oldCircleNumber].selected = !visCircles[oldCircleNumber].selected;
                    lastC.a = visCircles[oldCircleNumber].a; lastC.b = visCircles[oldCircleNumber].b;
                    lastC.r = visCircles[oldCircleNumber].r;
                } else if (oldLine) {
                    // line
                    visLines[oldLineNumber].selected = !visLines[oldLineNumber].selected;
                    lastl1 = lastl;
                    lastl = visLines[oldLineNumber];
                } else {
                    // new point
                }
                oldPoint = false; oldLine = false; oldCirle = false;
            }
        } else if (sgGetMouseButtons() == 0 && pressed){
            pressed = false;
        }
        for (int i = 0; i < visLines.size(); ++i){
            if (visLines[i].selected){
                selectPen(200, 20, 209, 3);
                drawLine(visLines[i].xUp, visLines[i].yUp,
                         visLines[i].xDown, visLines[i].yDown);
            }else {
                selectPen(0, 0, 8, 3);
                drawLine(visLines[i].xUp, visLines[i].yUp,
                         visLines[i].xDown, visLines[i].yDown);
            }
        }
        for (int i = 0; i < visCircles.size(); ++i){
            if (visCircles[i].selected){
                selectPen(20, 20, 209, 3);
                drawCircle(visCircles[i].a, visCircles[i].b, visCircles[i].r);
            }else {
                selectPen(0, 100, 8, 3);
                drawCircle(visCircles[i].a, visCircles[i].b, visCircles[i].r);
            }
        }
        for (int i = 0; i < visPoints.size(); ++i){ // drawing all objects
            if (visPoints[i].selected){
                selectPen(200, 20, 200, 3);
                drawCircle(visPoints[i].a, visPoints[i].b, visPoints[i].r);
            }else {
                selectPen(0, 0, 8, 3);
                drawCircle(visPoints[i].a, visPoints[i].b, visPoints[i].r);
            }
        }
        Sleep(80);
    }
}
