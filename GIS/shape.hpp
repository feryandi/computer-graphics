#ifndef SHAPE_H
#define SHAPE_H

#include "bezier_curve.hpp"
#include "line.hpp"
#include "frame_buffer.hpp"


class Shape{
public:

  // ctor & dtor
  Shape();
  Shape(const std::vector<BezierCurve> &crs, const std::vector<Line> &lns);
  ~Shape();
  Shape(const Shape &shape);

  Shape& operator=(const Shape &shape);

  // getter & setter
  std::vector<BezierCurve> getCurves() const;
  void setCurves(const std::vector<BezierCurve> &crs);

  std::vector<Line> getLines() const;
  void setLines(const std::vector<Line> &lns);

  Point getFirePoint() const;
  void setFirePoint(Point fp);

  Point getCentrePoint() const;
  void setCentrePoint(Point fp);

  Point getPositionPoint() const;
  void setPositionPoint(Point fp);

  void setR(int _r);
  void setG(int _g);
  void setB(int _b);

  int getR();
  int getG();
  int getB();

  float getMultiplication();
  void setMultiplication(float _k);

  float getDegree();
  void setDegree(float _degree);

  // Method
  void addCurve(BezierCurve bc);
  void addLine(Line l);
  void draw (FrameBuffer &fb);

  void moveLineX(int i, int movement);
  void moveLineY(int i, int movement);
  void moveLineZ(int i, int movement);

  void moveCurveX(int i, int movement);
  void moveCurveY(int i, int movement);
  void moveCurveZ(int i, int movement);

  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);

  void rotate(int degree, int cx, int cy);
  void fill(FrameBuffer &fb);

private:
  int isPointValid(FrameBuffer &fb, int x, int y);

  std::vector<BezierCurve> curves;
  std::vector<Line> lines;
  Point *firePoint;
  Point *centrePoint;
  Point *positionPoint;
  int r,g,b;
  float k;
  float degree;
};

#endif
