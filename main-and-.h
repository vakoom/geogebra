#include <iostream>
#include <math.h>
#include "vector"
#include "sg.h"
#include "sgfunc.h"
using namespace std;
class Point{
public:
    double x = 0, y = 0;
    bool polar = false;
    Point(double xn, double yn, bool polarn);
    double dist();
    double dist(Point &p);
    double dist(double xn, double yn);
    double abs();
    double abs(Point &p);
    double abs(double xn, double yn);
    double getPolarAngl();
    Point Turn(double phi);
    Point();
};
Point::Point(double xn, double yn, bool polarn = false){
    if (polarn == true){
        double ty = xn * sin(yn), tx = xn * cos(yn);
        xn = tx;
        yn = ty;
    }
    x = xn;
    y = yn;
    polar = polarn;
}
Point::Point(){
}
double Point::dist(Point &p) {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}
double Point::dist() {
    return sqrt(x * x + y * y);
}
double Point::dist(double xn, double yn) {
    return sqrt((x - xn) * (x - xn) + (y - yn) * (y - yn));
}
double Point::getPolarAngl(){
    if (y < 0){
        return  -acos(x / dist()) + 2 * M_PI;
    } else {
        return acos(x / dist());
    }
}


class Vector : public Point{
public:
    Vector();
    Vector(Point p);
    Vector(double xn, double yn);
    Vector(Point p1, Point p2);
    Vector(double xn1, double yn1, double xn2, double yn2);
    double dot_product(Vector v);
    double cross_product(Vector v);
    Vector mul(double n);
};
Vector::Vector(){
}
Vector::Vector(Point p) {
    x = p.x;
    y = p.y;
}
Vector::Vector(Point p1, Point p2) {
    x = p2.x - p1.x;
    y = p2.y - p1.y;
}
Vector::Vector(double xn, double yn) {
    x = xn;
    y = yn;
}
Vector::Vector(double xn1, double yn1, double xn2, double yn2) {
    x = xn2 - xn1;
    y = yn2 - yn1;
}
double Vector :: dot_product(Vector v){
    return x * v.x + y * v.y;
}
double Vector :: cross_product(Vector v) {
    return x * v.y - y * v.x;
}
Vector Vector :: mul(double n){
    x *= n;
    y *= n;
    return *this;
}
double operator*(Vector &v1, Vector &v2){
    return v1.dot_product(v2);
}
double operator^(Vector &v1, Vector &v2){
    return v1.cross_product(v2);
}
double operator*(Vector &v, double n){
    v.mul(n);
}
Vector operator*(double n, Vector &v){
    return v.mul(n);
}
double getAnglC(Vector &v1, Vector &v2){
    return acos(round(v1 *  v2 / (v1.dist() * v2.dist()) * 1e5) / 1e5);
}
double AnsForE(Vector &v1, Vector &v2){
    double angl = getAnglC(v1, v2);
    if ((v1^v2) == 0){
        return 1;
    } else if ((v1*v2) == 0) {
        return 2;
    }
    return 0;
}

class Circle{
public:
    double a, b, r;
    Circle(double an, double bn, double rn);
    double ViewAngl(const Point p);
    Circle();
};
Circle::Circle() {}

class Line{
public:
    double a = 0, b = 0, c = 0;
    Line(double a, double b, double c);
    Line();
    Line(Point p1, Point p2);
    Line(Circle c1, Circle c2);
    bool contains(Point p);
    Line parallel(double d);
    Line perpendicular(Point p);
    bool is_parallel(Line line);
    bool is_perpendicular(Line line);
    bool is_same(Line line);
    bool one_side_points(Point p1, Point p2);
};
void print(const Line line){
    cout << line.a << " " << line.b << " " << line.c;
}
Line::Line(double an, double bn, double cn) {
    a = an;
    b = bn;
    c = cn;
}
Line::Line(Circle c1, Circle c2) {
    Point p1(c1.a, c1.b), p2(c2.a, c2.b);
    Line(p1, p2);
}
Line::Line(){}
Line::Line(Point p1, Point p2) {
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = (p1.y - p2.y) * p1.x + (p2.x - p1.x) * p1.y;
}
bool Line::contains(const Point p){
    return a * p.x + b * p.y == - c;
}
Circle::Circle(double an, double bn, double rn) {
    a = an;
    b = bn;
    r = rn;
}
double Circle::ViewAngl(const Point p){
    Point c(a, b);
    return 2 * asin(r / c.dist(p.x, p.y));
}
Point Point::Turn(double phi){
    Point p(x * cos(phi) - y * sin(phi), x * sin(phi) + y * cos(phi));
    return p;
}
Line Line::parallel(double d) {
    if (b == 0){
        Line line(a, b, c + d);
        return line;
    } else {
        return Line();
    }
}
Line Line::perpendicular(Point p){
    Line ans(b, -a, 0);
    ans.c = -b * p.x + a * p.y;
    if (fabs(ans.c) < 1e-5){
        ans.c = 0;
    }
    return ans;
}
bool Line::is_parallel(Line line) {
    return b == 0 || a / b == line.a / line.b;
}
bool Line::is_perpendicular(Line line) {
    if (line.a == b && b == 0){
        return true;
    } else if (line.b == a && a == 0){
        return true;
    }
    return -line.b / a == line.a / b;
}
bool Line::is_same(Line line){
    if (b != 0 && a / b != line.a / line.b){
        return false;
    }
    if (a == 0 && c / b == line.c / line.b){
        return true;
    }
    if (b == 0 && c / a == line.c / line.a){
        return true;
    }
    if (a != 0 && b != 0 && line.a / line.c == a / c){
        return true;
    }
    return false;
}
bool operator==(Line line1, Line line2){
    return line1.is_parallel(line2);
}
int classification(Line line, Line line1){
    if (line.is_perpendicular(line1)){
        return 3;
    } else if (line.is_same(line1)){
        return 1;
    } else if (line.is_parallel(line1)){
        return 2;
    } else{
        return 0;
    }
}
bool Line::one_side_points(Point p1, Point p2) {
    if (b == 0){
        return (p1.x + c / a) * (p2.x + c / a) > 0;
    }
    Point p(1, -(c + a) / b);
    Point pn(2, -(c + 2 * a) / b);
    Vector v(p, pn), v1(p, p1), v2(p, p2);
    return (v^v1) * (v^v2) > 0;
}
Point cross(Line line1, Line line2){
    double a1 = line1.a, b1 = line1.b, c1 = line1.c;
    double a2 = line2.a, b2 = line2.b, c2 = line2.c;
    double x = (- b2 * c1 + b1 * c2) / (a1 * b2 - a2 * b1);
    double y = (- a1 * c2 + a2 * c1) / (a1 * b2 - a2 * b1);
    Point p(x, y);
    return p;
}
Point half(Point a, Point b, double x, double y){
    double X = a.x + (b.x - a.x) * x / (x + y);
    double Y = a.y + (b.y - a.y) * x / (x + y);
    Point ph(X, Y);
    return ph;
}


class Triangle{
public:
    Point O, A, B;
    Triangle(Point ON, Point AN, Point BN);
    Point mean();
    Point bisector();
};
Triangle::Triangle(Point ON, Point AN, Point BN) {
    O = ON;
    A = AN;
    B = BN;
}
Point Triangle::mean() {
    Point po(half(A, B, 1, 1)), pb(half(O, A, 1, 1));
    Line lo(O, po), lb(B, pb);
    return cross(lo, lb);
}
Point Triangle::bisector() {
    Point po(half(A, B, O.dist(A), O.dist(B))),
            pb(half(O, A, B.dist(O), B.dist(A)));
    Line lo(O, po), lb(B, pb);
    return cross(lo, lb);
}

double CircleDist(double x, double y, double r, double a, double b, double c) {
    Line line(a, b, c);
    if (b == 0){
        return fabs(-c / a - x) - r;
    } else {
        Point p1(1, (-c - a) / b), p2(2, (-c - 2 * a) / b);
        Vector v1(p1, Point(x, y)), v2(p1, p2);
        double d = fabs(v1.dist() * (v1 ^ v2) / (v1.dist() * v2.dist()));
        return d - r;
    }
}

class VisPoint : public Circle{
public:
    bool selected;
    VisPoint(double x, double y);
    bool inside(VisPoint p);
};
VisPoint::VisPoint(double x, double y) : Circle(x, y, 8) {
    a = x;
    b = y;
    r = 8;
}
Point footOfPerpendicular(Point p, Line l1){
    Line l2 = l1.perpendicular(p);
    return cross(l1, l2);
}
bool VisPoint::inside(VisPoint p) {
    return abs(a - p.a) <= r && abs(b - p.b) <= r;
}

class VisLine : public Line{
public:
    bool selected;
    int xUp, xDown, yUp, yDown;
    VisLine(Point p1, Point p2);
    VisLine(VisPoint vp1, VisPoint vp2);
};
VisLine::VisLine(Point p1, Point p2) {
    Line l(p1, p2);
    a = l.a;
    b = l.b;
    c = l.c;
    selected = false;
}
VisLine::VisLine(VisPoint p1, VisPoint p2) {
    Line l(p1, p2);
    a = l.a;
    b = l.b;
    c = l.c;
    selected = false;
}

class Rectangle3{
public:
    double x1, y1, x2, y2;
    int cr = 0, cg = 0, cb = 0;
    Rectangle3();
    Rectangle3(double x1n, double y1n, double x2n, double y2n);
    Rectangle3(Point p1, Point p2);
    bool insideRect(VisPoint p);
    void drawRect();
};
void Rectangle3::drawRect() {
    selectPen(cr, cg, cb, 3);
    drawRectangle(x1, y1, x2, y2);
}
Rectangle3::Rectangle3(){
}
Rectangle3::Rectangle3(double x1n, double y1n, double x2n, double y2n) {
    x1 = x1n;
    y1 = y1n;
    x2 = x2n;
    y2 = y2n;
}
Rectangle3::Rectangle3(Point p1, Point p2) {
    x1 = p1.x;
    y1 = p1.y;
    x2 = p2.x;
    y2 = p2.y;
}
bool Rectangle3::insideRect(VisPoint p) {
    return p.a >= x1 && p.b >= y1 && p.a <= x2 && p.b <= y2;
}

class VisCircle : public Circle{
public:
    bool selected;
    VisCircle(Point centre, Point p);
};
VisCircle::VisCircle(Point centre, Point p) {
    a = centre.x;
    b = centre.y;
    r = p.dist(centre);
}

void getNewVisLine(int h, vector<VisLine> &visLines, VisPoint last, VisPoint last1){
    Point plast(last.a, last.b), plast1(last1.a, last1.b);
    Line l(plast, plast1);
    Line l1(0, 1, 0), l2(0, 1, -h);
    Point p1 = cross(l, l1), p2 = cross(l, l2);
    VisLine lv(p1, p2);
    lv.xUp = p1.x; lv.yUp = p1.y;
    lv.xDown = p2.x; lv.yDown = p2.y;
    lv.selected = false;
    visLines.push_back(lv);
}

void getNewVisCircle(vector<VisCircle> &visCircles, VisPoint last, VisPoint last1){
    Point plast(last.a, last.b), plast1(last1.a, last1.b);
    VisCircle c(plast, plast1);
    c.selected = false;
    visCircles.push_back(c);
}

void getNewCrossPoint(vector<VisPoint> &visPoints, VisLine lastl, VisLine lastl1){
    Line l(lastl.a, lastl.b, lastl.c), l1(lastl1.a, lastl1.b, lastl1.c);
    Point p = cross(l, l1);
    VisPoint pv(p.x, p.y);
    pv.selected = false;
    visPoints.push_back(pv);
}

void getFootPerpPoint(int h, vector<VisLine> &visLines, vector<VisPoint> &visPoints, VisLine lastl, VisPoint last){
    Line l(lastl.a, lastl.b, lastl.c);
    Point p(last.a, last.b);
    Point foot = footOfPerpendicular(p, l);
    VisPoint pv(foot.x, foot.y);
    visPoints.push_back(pv);
    getNewVisLine(h, visLines, last, pv);
}

void getCrossLC(vector<VisPoint> &visPoints, VisLine lastl, VisCircle lastC){
    Line l(lastl.a, lastl.b, lastl.c);
    Circle c(lastC.a, lastC.b, lastC.r);
    Point p(lastC.a, lastC.b);
    Point perp(footOfPerpendicular(p, l));
    double d = p.dist(perp), r = lastC.r, a = l.a, b = l.b;
    double k = sqrt((r * r - d * d) / (a * a + b * b));
    VisPoint pv1(k * b + perp.x, k * (-a) + perp.y);
    pv1.selected = false;
    VisPoint pv2(-1 * k * b + perp.x, -1 * k * (-a) + perp.y);
    pv2.selected = false;
    visPoints.push_back(pv1);
    visPoints.push_back(pv2);
}

/*
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
*/
