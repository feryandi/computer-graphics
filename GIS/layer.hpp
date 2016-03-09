#ifndef LAYER_H
#define LAYER_H
#include "bezier_curve.hpp"
#include "polygon.hpp"
#include "text.hpp"
#include <vector>

class Layer{
public:
  // ctor
  Layer();

  // dtor
  ~Layer();

  // getter & setter
  std::vector<BezierCurve> getCurves();
  std::vector<Polygon> getPolygons();
  std::vector<Text> getTexts();

  // Drawing methods
  int iabs(int n);
  int F(int X, int Y, int Z);
  int G(int X, int Y);
  void bresenham(int x1, int y1, int x2, int y2, int red, int green, int blue, int line);
  void drawControlPoint(BezierCurve curve, unsigned int selected);
  void draw(BezierCurve curve);
  void draw(Polygon p);
  void draw(Text t);
  void plot(unsigned int x, unsigned int y, int red, int green, int blue);

private:
  char* buffer;
  std::vector<BezierCurve> curves;
  std::vector<Polygon> polygons;
  std::vector<Text> texts;
};

#endif
