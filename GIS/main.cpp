#include "reader.hpp"

int main() {
  // Initialization
  FrameBuffer fb;
  Reader a;

  BezierCurve::generateLookupTable();
  fb.clearScreen();

  // Test
  std::vector<Point> points;
  points.push_back(Point(500,200));
  points.push_back(Point(100,50));
  Line line(points);
  points.push_back(Point(600,200));
  BezierCurve bezier(points);
  //
  Shape c = a.read("31-45.txt");
  
  line.draw(fb);
  bezier.draw(fb);
  c.draw(fb);

  // fb.plot(100,100,200,0,0);
  fb.render();

}