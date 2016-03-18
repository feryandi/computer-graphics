#include "line.hpp"
#include "bezier_curve.hpp"
#include "frame_buffer.hpp"
#include <vector>

int main(){

  // Initialization
  FrameBuffer fb;
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
  line.draw(fb);
  bezier.draw(fb);

  // fb.plot(100,100,200,0,0);
  fb.render();

  return 0;
}
