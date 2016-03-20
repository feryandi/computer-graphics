#ifndef GROUP_H
#define GROUP_H
#include "bezier_curve.hpp"
#include "object.hpp"
#include <vector>

class Group{
public:
  // ctor
  Group();

  // dtor
  ~Group();

  // getter & setter
  double getX();
  double getY();
  double getZ();
  void setX(double _x);
  void setY(double _y);
  void setZ(double _z);

  float getMultiplication();
  void setMultiplication(float _k);

  // methods
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void rotate(float degree, int cx, int cy);

  void draw(FrameBuffer &fb);

  void hide();
  void show();
  void toggle();

  void add(const Shape &s);
  void addList(const std::vector<Shape> &s);

private:
    std::vector<Shape> shapes;
    double x,y,z;
    Point *positionPoint;
    int visible;
    float k;
};

#endif
