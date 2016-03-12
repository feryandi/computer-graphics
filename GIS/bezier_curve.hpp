#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include "point.hpp"
#include <stdlib.h>
#include <vector>

class BezierCurve{
public:
  // ctor
  BezierCurve();
  BezierCurve(std::vector<Point> _p);

  // dtor
  ~BezierCurve();

  // getter & setter
  std::vector<Point> getPoints();
  void setPoint(std::vector<Point> _p);
  int getOrder();
  void setOrder(int _order);
  double getX();
  double getY();
  double getZ();

  // methods
  void addControlPoint(Point p);
  void deleteControlPoint(int i);
  void moveControlPointX(int i, int movement);
  void moveControlPointY(int i, int movement);
  void moveControlPointZ(int i, int movement);
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void draw(char* buffer);
  void drawControlPoint(BezierCurve curve, unsigned int selected);

private:
  // vector of control points
  std::vector<Point> points;
  int order;
  double x,y,z;
};
#endif
