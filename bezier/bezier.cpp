#include "bezier.hpp"

BezierCurve::BezierCurve(){
  points = new std::vector<Point>;
}

BezierCurve::BezierCurve(std::vector<Point> *_p){
  points = _p;
}

BezierCurve::~BezierCurve(){
  delete points;
}

std::vector<Point>* BezierCurve::getPoints(){
  return points;
}

void BezierCurve::setPoint(std::vector<Point>* _p){
  points = _p;
}

void BezierCurve::addControlPoint(Point p){
  points->push_back(p);
}

void BezierCurve::deleteControlPoint(int i){
  points->erase(points->begin()+(i-1));
}

void BezierCurve::moveControlPointX(int i, int movement){
  points->at(i).moveX(movement);
}

void BezierCurve::moveControlPointY(int i, int movement){
  points->at(i).moveY(movement);
}
