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

  // methods
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void draw(FrameBuffer &fb);


private:
    std::vector<Shape> shapes;
    double x,y,z;
};

#endif
