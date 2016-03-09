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
