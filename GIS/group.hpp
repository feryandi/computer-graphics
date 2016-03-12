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
  
  // methods
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void draw(char* buffer);


private:
    std::vector<Object> objects
    double x,y,z;
};

#endif