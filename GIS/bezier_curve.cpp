#include "bezier_curve.hpp"

BezierCurve::BezierCurve(){
  order = -1;
}

BezierCurve::BezierCurve(std::vector<Point> _p){
  points = _p;
  order = points.size()-1;
}

BezierCurve::~BezierCurve(){
}

std::vector<Point> BezierCurve::getPoints(){
  return points;
}

void BezierCurve::setPoint(std::vector<Point> _p){
  points = _p;
}

int BezierCurve::getOrder(){
  return order;
}

void BezierCurve::setOrder(int _order){
  order = _order;
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

void BezierCurve::drawControlPoint(unsigned int selected){
  for (unsigned int i=0;i<points.size();i++){
    // Draw selected Point
    if (i == selected){
      for (int j=2;j<4;j++){
        /*plot(curve.getPoints().at(i).getX()+j,curve.getPoints().at(i).getY(),255,0,0);
        plot(curve.getPoints().at(i).getX()-j,curve.getPoints().at(i).getY(),255,0,0);
        plot(curve.getPoints().at(i).getX(),curve.getPoints().at(i).getY()+j,255,0,0);
        plot(curve.getPoints().at(i).getX(),curve.getPoints().at(i).getY()-j,255,0,0);*/
      }
    }
    else{
      for (int j=2;j<4;j++){
       /* plot(curve.getPoints().at(i).getX()+j,curve.getPoints().at(i).getY(),0,0,255);
        plot(curve.getPoints().at(i).getX()-j,curve.getPoints().at(i).getY(),0,0,255);
        plot(curve.getPoints().at(i).getX(),curve.getPoints().at(i).getY()+j,0,0,255);
        plot(curve.getPoints().at(i).getX(),curve.getPoints().at(i).getY()-j,0,0,255);*/
      }
    }
    if (i < points.size()-1){
      /*bresenham(curve.getPoints().at(i).getX(),
                curve.getPoints().at(i).getY(),
                curve.getPoints().at(i+1).getX(),
                curve.getPoints().at(i+1).getY(),
                0,0,255,1);*/
    }
  }

}

void BezierCurve::moveX(int movement){

}
void BezierCurve::moveY(int movement){

}
void BezierCurve::moveZ(int movement){

}
void BezierCurve::draw(char* buffer){

float x=0,y=0; // Where to plot
float a,b;
// printf("Order: %d\n", order);

std::vector<int> polynom = lookup_table.at(order);
for (int t=0;t<STEP;t++){
  // Step loop
  a = 1 - ((float)t/STEP);
  b = (float)t/STEP;
  x = 0; y = 0;

  // Polynom sum
  for (int i=0;i<=order;i++){

    // printf("Xb: %d\n", curve.getPoints().at(i).getX());
    // printf("Yb: %d\n", curve.getPoints().at(i).getY());
    // printf("PolynomAt_i: %d\n", polynom.at(i));
    // printf("A: %f\n", a);
    // printf("B: %f\n", b);

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

  // printf("t: %d\n", t);
  // printf("X: %f\n", x);
  // printf("Y: %f\n", y);
  // printf("____________\n");
  plot((int)x,(int)y,200,200,200);
}
