#ifndef POINT_H
#define POINT_H

class Point{
public:
  // ctor
  Point();
  Point(int _x, int _y);

  // getter & setter
  int getX();
  int getY();
  int getZ();

  void setX(int _x);
  void setY(int _x);
  void setZ(int _z);

  // methods
  void moveX(int _x);
  void moveY(int _y);
  void moveZ(int _z);
  void rotate(float degree, Point center);
  void draw(char* buffer);

private:
  // point coordinates
  double x;
  double y;
  double z;
};

#endif
