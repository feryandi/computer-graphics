#ifndef POLYGON_H
#define POLYGON_H

#include "point.hpp"
#include <vector>

class Polygon {
public:
  // ctor & dtor
  Polygon();
  Polygon(std::vector<Point> _points);
  ~Polygon();

  // methods
  std::vector<Point> getPoints();
  std::vector<Point> getPointNumbers();
  void addPoint(Point p);
  void deletePoint(int i);
  void movePointX(int i, int movement);
  void movePointY(int i, int movement);
  void movePointZ(int i, int movement);


private:
  std::vector<Point> points;
};
#endif
