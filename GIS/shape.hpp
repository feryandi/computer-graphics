#ifndef SHAPE_H
#define SHAPE_H
#include "bezier_curve.h"
#include "line.h"
#include "frame_buffer.hpp"

class Shape{
public:

  // ctor & dtor
  Shape();
  ~Shape();

  // getter & setter
  std::vector<BezierCurve> getCurves();
  void setCurves(std::vector<BezierCurve> crs);

  std::vector<Line> getLines();
  void setLines(std::vector<Line> lns);

  Point getFirePoint();
  void setFirePoint(Point fp);

  Point getCentrePoint();
  void setCentrePoint(Point fp);

  Point getPositionPoint();
  void setPositionPoint(Point fp);

  float getMultiplication();
  void setMultiplication(float _k);

  float getDegree();
  void setDegree(float _degree);

  // Method
  void addCurve(BezierCurve bc);
  void addLine(Line l);
  void draw (FrameBuffer &fb);
  
private:
  std::vector<BezierCurve> curves;
  std::vector<Line> lines;
  Point firePoint;
  Point centrePoint;
  Point positionPoint;
  float k;
  float degree;
};

#endif
