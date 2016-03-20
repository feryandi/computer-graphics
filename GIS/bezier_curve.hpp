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
  BezierCurve(std::vector<Point> &_p);

  // dtor
  ~BezierCurve();

  // getter & setter
  std::vector<Point> getPoints() const;
  void setPoint(std::vector<Point> _p);
  int getOrder() const;
  void setOrder(int _order);
  int getR() const;
  int getG() const;
  int getB() const;
  double getX() const;
  double getY() const;
  double getZ() const;
  void setR(double _r);
  void setG(double _g);
  void setB(double _b);

  // methods
  void addControlPoint(Point p);
  void deleteControlPoint(int i);
  void moveControlPointX(int i, int movement);
  void moveControlPointY(int i, int movement);
  void moveControlPointZ(int i, int movement);
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void rotate(int degree, int cx, int cy);
  
  void draw(FrameBuffer &fb);
  void drawControlPoint(unsigned int selected);
  void drawWM(FrameBuffer &fb, double k, int cx, int cy);

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
  int r,g,b;
};
#endif
