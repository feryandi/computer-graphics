#include "bezier_curve.hpp"
#define MAX_ORDER 50
#define STEP 1000


BezierCurve::BezierCurve(){
  order = -1;
  r = 255;
  g = 255;
  b = 255;
}

BezierCurve::BezierCurve(std::vector<Point> &_p){
  points = _p;
  order = points.size()-1;
  r = 255;
  g = 255;
  b = 255;
}

BezierCurve::~BezierCurve(){
}

std::vector<Point> BezierCurve::getPoints() const{
  return points;
}

void BezierCurve::setPoint(std::vector<Point> _p){
  points = _p;
}

int BezierCurve::getR() const{
  return r;
}
int BezierCurve::getG() const{
  return g;
}
int BezierCurve::getB() const{
  return b;
}

int BezierCurve::getOrder() const{
  return order;
}

void BezierCurve::setOrder(int _order){
  order = _order;
}

void BezierCurve::setR(double _r){
  r = _r;
}
void BezierCurve::setG(double _g){
  g = _g;
}
void BezierCurve::setB(double _b){
  b = _b;
}

void BezierCurve::addControlPoint(Point p){
  points.push_back(p);
  order++;
}

void BezierCurve::deleteControlPoint(int i){
  points.erase(points.begin()+(i));
  order--;
}

void BezierCurve::moveControlPointX(int i, int movement){
  points.at(i).moveX(movement);
}

void BezierCurve::moveControlPointY(int i, int movement){
  points.at(i).moveY(movement);
}

void BezierCurve::moveControlPointZ(int i, int movement){
  points.at(i).moveZ(movement);
}

std::vector<std::vector<int> > BezierCurve::getPolynomLookupTable() {
  return lookup_table;
}

void BezierCurve::generateLookupTable(){
  //Generate Polynom table
  for (int i=0; i<MAX_ORDER-1; i++){
    std::vector<int> v;
    v.push_back(1);
    for (int j=1;j<=i-1;j++){
      v.push_back(lookup_table.at(i-1).at(j-1)+lookup_table.at(i-1).at(j));
    }
    if (i > 0){
      v.push_back(1);
    }
    lookup_table.push_back(v);
  }
}

void BezierCurve::moveX(int movement){
  for (uint i = 0; i < points.size(); ++i)
  {
    points.at(i).moveX(movement);
  }
}

void BezierCurve::moveY(int movement){
  for (uint i = 0; i < points.size(); ++i)
  {
    points.at(i).moveY(movement);
  }
}

void BezierCurve::moveZ(int movement){
  for (uint i = 0; i < points.size(); ++i)
  {
    points.at(i).moveZ(movement);
  }
}

void BezierCurve::rotate(int degree, int cx, int cy){
  for (uint i=0;i<points.size();i++){
    points[i].rotate(degree,cx,cy);
  }
}

void BezierCurve::draw(FrameBuffer &fb){
  float x=0,y=0; // Where to plot
  float a,b;

  std::vector<int> polynom = lookup_table.at(order);
  for (int t=0;t<STEP;t++){

    // Step loop
    a = 1 - ((float)t/STEP);
    b = (float)t/STEP;
    x = 0; y = 0;

    // Polynom sum
    for (int i=0;i<=order;i++){
      float tempX = points.at(i).getX() * polynom.at(i);
      float tempY = points.at(i).getY() * polynom.at(i);

      for (int k=0;k<order-i;k++){
        tempX = tempX * a;
        tempY = tempY * a;
      }

      for (int k=0;k<i;k++){
        tempX = tempX * b;
        tempY = tempY * b;
      }

      x += tempX;
      y += tempY;
    }

    fb.plot((int)x,(int)y,this->r,this->g,this->b);
  }
}

void BezierCurve::drawWM(FrameBuffer &fb, double k, int cx, int cy) {
  float x=0,y=0; // Where to plot
  float a,b;

  std::vector<int> polynom = lookup_table.at(order);
  for (int t=0;t<STEP;t++){

    // Step loop
    a = 1 - ((float)t/STEP);
    b = (float)t/STEP;
    x = 0; y = 0;

    // Polynom sum
    for (int i=0;i<=order;i++){
      float tempX = (((points.at(i).getX() * polynom.at(i))-cx)*k)+cx;
      float tempY = (((points.at(i).getY() * polynom.at(i))-cy)*k)+cy;

      for (int k=0;k<order-i;k++){
        tempX = tempX * a;
        tempY = tempY * a;
      }

      for (int k=0;k<i;k++){
        tempX = tempX * b;
        tempY = tempY * b;
      }

      x += tempX;
      y += tempY;
    }

    fb.plot((int)x,(int)y,this->r,this->g,this->b);
  }
}

std::vector<std::vector<int> > BezierCurve::lookup_table;
