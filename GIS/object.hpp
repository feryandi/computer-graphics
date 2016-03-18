#ifndef OBJECT_H
#define OBJECT_H
#include "shape.h"
#include "bezier_curve.h"
#include "line.h"
#include "text.h"
#include "frame_buffer.hpp"

class Object{
public:
  // ctor & dtor
  Object();
  ~Object();

  // getter & setter
  std::vector<BezierCurve> getCurves();
  std::vector<Line> getLines();
  std::vector<Text> getTexts();
  std::vector<Shape> getShapes();
  double getX();
  double getY();
  double getZ();
  void setX(double _x);
  void setY(double _y);
  void setZ(double _z);

  // methods
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void draw(FrameBuffer &fb);

private:
  std::vector<Shape> shapes;
  std::vector<BezierCurve> curves;
  std::vector<Line> lines;
  std::vector<Text> texts;
  double x,y,z;
};

#endif
