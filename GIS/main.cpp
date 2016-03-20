#include "reader.hpp"
#include "group.hpp"

int main() {
  // Initialization
  FrameBuffer fb;
  Reader a;
  Group itb;
  Text test;

  BezierCurve::generateLookupTable();
  fb.clearScreen();
  fb.clearZBuffer();
  // Read File
  std::cout << fb.getCX() << "," << fb.getCY() << std::endl;
  //c.setFirePoint(Point(50,50));
/*  c.rotate(0, fb.getCX(), fb.getCY());
  c.draw(fb);
  c.fill(fb);*/

  itb.addList(a.read("31-45.txt"));
  //itb.rotate(45, fb.getCX(), fb.getCY());
  itb.draw(fb);

  std::string g = "TEST";
  test.setText(g);
  test.draw(fb);

  fb.render();

}
