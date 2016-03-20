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
  std::vector<Point> getPoints() const;
  double getX() const;
  double getY() const;
  double getZ() const;
  int getR() const;
  int getG() const;
  int getB() const;
  void setX(double _x);
  void setY(double _y);
  void setZ(double _z);
  void setR(double _r);
  void setG(double _g);
  void setB(double _b);

  // public methods
  void addPoint(Point p);
  void deletePoint(int i);
  void movePointX(int i, int movement);
  void movePointY(int i, int movement);
  void movePointZ(int i, int movement);
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void rotate(int degree, int cx, int cy);
  void draw(FrameBuffer &fb);
  void drawWM(FrameBuffer &fb, double k, int cx, int cy);

private:
  std::vector<Point> points;
  double x,y,z;
  int r,g,b;

  // private methods
  int iabs(int n);
  int F(int X, int Y, int Z);
  int G(int X, int Y);
  void bresenham(FrameBuffer &fb, int x1, int y1, int x2, int y2, int red, int green, int blue, int line);
};
#endif
