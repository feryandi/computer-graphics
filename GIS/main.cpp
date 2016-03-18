#include "line.hpp"
#include "bezier_curve.hpp"
#include "frame_buffer.hpp"
#include <vector>

int main(){

  // Initialization
  FrameBuffer fb;
  BezierCurve::generateLookupTable();

  // Test
  std::vector<Point> points;
  points.push_back(Point(5,2));
  points.push_back(Point(1,0));
  Line line(points);
  points.push_back(Point(6,0));
  BezierCurve bezier(points);

  line.draw(fb);
  bezier.draw(fb);

  fb.clearScreen();
  fb.render();

  return 0;
}
