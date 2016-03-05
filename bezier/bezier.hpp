#include "point.hpp"
#include <vector>

class BezierCurve{
public:
  // ctor
  BezierCurve();
  BezierCurve(std::vector<Point>* _p);

  // dtor
  ~BezierCurve();

  // getter & setter
  std::vector<Point>* getPoints();
  void setPoint(std::vector<Point>* _p);

  // methods
  void addControlPoint(Point p);
  void deleteControlPoint(int i);
  void moveControlPointX(int i, int movement);
  void moveControlPointY(int i, int movement);

private:
  // vector of control points
  std::vector<Point>* points;
};
