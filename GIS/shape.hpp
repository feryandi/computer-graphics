#ifndef SHAPE_H
#define SHAPE_H
#include "bezier_curve.h"
#include "line.h"
#include "text.h"


class Shape{
public:

  // ctor & dtor
  Shape();
  ~Shape();

  // getter & setter
  std::vector<BezierCurve> getCurves();
  std::vector<Polygon> getPolygons();
  std::vector<Text> getTexts();
  double getFirePoint();
  void setFirePoint(double fp);
  double getX();
  double getY();
  double getZ();
  
  // methods
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void draw(char* buffer);

private:
  std::vector<BezierCurve> curves;
  std::vector<Line> lines;
  std::vector<Text> texts;
  double firePoint,x,y,z;
};

#endif
