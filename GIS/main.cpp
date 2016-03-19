#include "reader.hpp"

int main() {
  // Initialization
  FrameBuffer fb;
  Reader a;

  BezierCurve::generateLookupTable();
  fb.clearScreen();

  // Read File
  Shape c = a.read("31-45.txt");
  c.draw(fb);

  fb.render();

}
