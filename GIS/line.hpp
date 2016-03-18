#ifndef LINE_H
#define LINE_H

#include "point.hpp"
#include <vector>
#include "frame_buffer.hpp"

class Line {
public:
  // ctor & dtor
  Line();
  Line(std::vector<Point> _points);
  ~Line();

  // getter & setter
  std::vector<Point> getPoints();
  double getX();
  double getY();
  double getZ();
  void setX(double _x);
  void setY(double _y);
  void setZ(double _z);

  // methods
  void addPoint(Point p);
  void deletePoint(int i);
  void movePointX(int i, int movement);
  void movePointY(int i, int movement);
  void movePointZ(int i, int movement);
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void draw(FrameBuffer fb);
  int iabs(int n);
  int F(int X, int Y, int Z);
  int G(int X, int Y);
  void bresenham(FrameBuffer fb, int x1, int y1, int x2, int y2, int red, int green, int blue, int line);


private:
  std::vector<Point> points;
  double x,y,z;
};
#endif
