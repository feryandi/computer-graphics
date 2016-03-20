#ifndef POINT_H
#define POINT_H

#include "frame_buffer.hpp"
#include <math.h>
#define PI 3.14159265

class Point{
public:
  // ctor
  Point();
  Point(int _x, int _y);

  // getter & setter
  int getX() const;
  int getY() const;
  int getZ() const;

  void setX(int _x);
  void setY(int _y);
  void setZ(int _z);

  // methods
  void moveX(int _x);
  void moveY(int _y);
  void moveZ(int _z);
  void rotate(float degree, int center_x, int center_y, int posX, int posY);
  void draw(char* buffer);

private:
  // point coordinates
  int x;
  int y;
  int z;
};

#endif
