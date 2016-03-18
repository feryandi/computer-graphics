#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include "point.hpp"
#include <stdlib.h>
#include <vector>
#include "frame_buffer.hpp"

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
  void draw(FrameBuffer fb);
  void drawControlPoint(unsigned int selected);

  // static method
  static std::vector<std::vector<int> > getPolynomLookupTable();
  static void generateLookupTable();

private:
  // vector of control points
  // Pre-generated table for polynoms
  static std::vector<std::vector<int> > lookup_table;
  std::vector<Point> points;
  int order;
  double x,y,z;
};
#endif
