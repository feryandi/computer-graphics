#include "reader.hpp"
#include "group.hpp"
#include "input.hpp"

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
  itb.setMultiplication(1.5);
  itb.draw(fb);

  text.addList(a.read("jalan.txt"));
  text.setMultiplication(1.5);
  text.draw(fb);

/*
  test.setText("TEST");
  test.setSize(2);
  test.setX(10);
  test.setY(10);
  test.draw(fb);
*/
  fb.render();

  char input;
  Input::initTermios();

  while (1) {
    if (Input::kbhit()){
      input = Input::getch();
      switch (input) {
        case '1' : {
          text.toggle();
          break;
        }
        case '2' : {
          itb.toggle();
          break;
        }
        case ' ':{
          Input::resetTermios();
          printf("End of program\n");
          exit(0);
          break;
        }
        default:{
          break;
        }
      }
      fb.clearScreen();
      fb.clearZBuffer();
      itb.draw(fb);
      text.draw(fb);
      fb.render();      
    }
  }

  return 0;

}
