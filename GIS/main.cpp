#include "reader.hpp"

int main() {
  // Initialization
  FrameBuffer fb;
  Reader a;

  BezierCurve::generateLookupTable();
  fb.clearScreen();
  fb.clearZBuffer();
  // Read File
  Shape c = a.read("31-45.txt");
  std::cout << fb.getCX() << "," << fb.getCY() << std::endl;
  c.setFirePoint(Point(100,100));
  c.rotate(0, fb.getCX(), fb.getCY());
  c.draw(fb);
  c.fill(fb);

  fb.render();

}
