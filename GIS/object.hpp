#ifndef OBJECT_H
#define OBJECT_H
#include "shape.hpp"
#include "bezier_curve.hpp"
#include "line.hpp"
#include "text.hpp"
#include "frame_buffer.hpp"

class Object{
public:
  // ctor & dtor
  Object();
  ~Object();

  // getter & setter
  std::vector<BezierCurve> getCurves() const;
  std::vector<Line> getLines() const;
  std::vector<Text> getTexts() const;
  std::vector<Shape> getShapes() const;
  double getX() const;
  double getY() const;
  double getZ() const;
  void setX(double _x);
  void setY(double _y);
  void setZ(double _z);

  // methods
  void moveX(double movement);
  void moveY(double movement);
  void moveZ(double movement);
  void draw(FrameBuffer &fb);

private:
  std::vector<Shape> shapes;
  std::vector<BezierCurve> curves;
  std::vector<Line> lines;
  std::vector<Text> texts;
  double x,y,z;
};

#endif
