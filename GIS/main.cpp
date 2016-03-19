#include "reader.hpp"
#include "group.hpp"

int main() {
  // Initialization
  FrameBuffer fb;
  Reader a;
  Group sabuga;

  BezierCurve::generateLookupTable();
  fb.clearScreen();
  fb.clearZBuffer();
  // Read File
  Shape c = a.read("31-45.txt");
  std::cout << fb.getCX() << "," << fb.getCY() << std::endl;
  //c.setFirePoint(Point(50,50));
/*  c.rotate(0, fb.getCX(), fb.getCY());
  c.draw(fb);
  c.fill(fb);*/

  sabuga.add(c);
  sabuga.draw(fb);

  fb.render();

}
