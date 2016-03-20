#include "reader.hpp"
#include "group.hpp"

int main() {
  // Initialization
  FrameBuffer fb;
  Reader a;
  Group itb;
  Group text;

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
  itb.setMultiplication(1.2);
  itb.draw(fb);

  text.addList(a.read("text.txt"));
  text.setMultiplication(1.2);
  text.draw(fb);

/*
  test.setText("TEST");
  test.setSize(2);
  test.setX(10);
  test.setY(10);
  test.draw(fb);
*/
  fb.render();

}
