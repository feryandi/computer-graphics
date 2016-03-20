#include "reader.hpp"
#include "group.hpp"
#include "input.hpp"

#include <vector>

void draw(FrameBuffer &fb, std::vector<Group> groups){
  for (uint i=0;i<groups.size();i++){
    fb.clearZBuffer();
    groups[i].draw(fb);
  }
}


int main() {

  // Initialization
  FrameBuffer fb; // FrameBuffer
  Input input; // Input
  Reader a; // File Reader
  std::vector<Group> groups; // Group of map objects

  // Selection
  int selectedgroup=0, r=0,g=0,b=255;

  BezierCurve::generateLookupTable();


  // Read File
  // std::cout << fb.getCX() << "," << fb.getCY() << std::endl;
  groups.push_back(Group());
  groups[0].addList(a.read("layers/models/jalan_angka.txt"));
  groups[0].setMultiplication(1);
  groups.push_back(Group());
  groups[1].addList(a.read("layers/models/jalan_huruf.txt"));
  groups[1].setMultiplication(1);
  groups.push_back(Group());
  groups[2].addList(a.read("layers/models/depan.txt"));
  groups[2].setMultiplication(1);
  groups.push_back(Group());
  groups[3].addList(a.read("layers/models/barat.txt"));
  groups[3].setMultiplication(1);
  groups.push_back(Group());
  groups[4].addList(a.read("layers/models/timur.txt"));
  groups[4].setMultiplication(1);
  groups.push_back(Group());
  groups[5].addList(a.read("layers/models/labtek_kembar.txt"));
  groups[5].setMultiplication(1);
  groups.push_back(Group());
  groups[6].addList(a.read("layers/models/gedung_kembar.txt"));
  groups[6].setMultiplication(1);
  groups.push_back(Group());
  groups[7].addList(a.read("layers/models/sunken.txt"));
  groups[7].setMultiplication(1);
  groups.push_back(Group());
  groups[8].addList(a.read("layers/models/luar.txt"));
  groups[8].setMultiplication(1);
  groups.push_back(Group());
  groups[9].addList(a.read("layers/texts/nama_jalan.txt"));
  groups[9].setMultiplication(1);

  groups.push_back(Group());
  groups[10].addList(a.read("layers/texts/depan.txt"));
  groups[10].setMultiplication(1);
  groups[10].hide();
  
  groups.push_back(Group());
  groups[11].addList(a.read("layers/texts/barat.txt"));
  groups[11].setMultiplication(1);
  groups[11].hide();
  
  groups.push_back(Group());
  groups[12].addList(a.read("layers/texts/timur.txt"));
  groups[12].setMultiplication(1);
  groups[12].hide();
  
  groups.push_back(Group());
  groups[13].addList(a.read("layers/texts/labtek_kembar.txt"));
  groups[13].setMultiplication(1);
  groups[13].hide();
  
  groups.push_back(Group());
  groups[14].addList(a.read("layers/texts/gedung_kembar.txt"));
  groups[14].setMultiplication(1);
  groups[14].hide();
  
  groups.push_back(Group());
  groups[15].addList(a.read("layers/texts/sunken.txt"));
  groups[15].setMultiplication(1);
  groups[15].hide();
  
  groups.push_back(Group());
  groups[16].addList(a.read("layers/texts/luar.txt"));
  groups[16].setMultiplication(1);
  groups[16].hide();

  // Initialize input
  input.initTermios();

  // Initialize Selection
/*  r = groups[selectedgroup].getShapes()->at(0).getR();
  g = groups[selectedgroup].getShapes()->at(0).getG();
  b = groups[selectedgroup].getShapes()->at(0).getB();

  for (uint i=0;i<groups[selectedgroup].getShapes()->size();i++){
    groups[selectedgroup].getShapes()->at(i).setR(0);
    groups[selectedgroup].getShapes()->at(i).setG(0);
    groups[selectedgroup].getShapes()->at(i).setB(255);
  }*/


  // Initial screen
  fb.clearScreen();
  fb.infoScreen();
  fb.clearZBuffer();
  draw(fb, groups);
  fb.render();

  // Main loop
  char c;
  while (1){
    if (input.kbhit()){
      c = input.getch();
/*      for (uint i=0;i<groups[selectedgroup].getShapes()->size();i++){
        groups[selectedgroup].getShapes()->at(i).setR(r);
        groups[selectedgroup].getShapes()->at(i).setG(g);
        groups[selectedgroup].getShapes()->at(i).setB(b);
      }*/
      switch (c){
        case '1' : {
          groups[1].toggle();
          groups[0].toggle();
          break;
        }
        case '2' : {
          selectedgroup = 2;
          groups[2].setRGB(246, 101, 56);
          // groups[2].toggle();
          break;
        }
        case '3' : {
          selectedgroup = 3;
          groups[3].setRGB(193, 0, 15);
          // groups[3].toggle();
          break;
        }
        case '4' : {
          selectedgroup = 4;
          groups[4].setRGB(254, 197, 53);
          // groups[4].toggle();
          break;
        }
        case '5' : {
          selectedgroup = 5;
          groups[5].setRGB(27, 129, 44);
          // groups[5].toggle();
          break;
        }
        case '6' : {
          selectedgroup = 6;
          groups[6].setRGB(247, 47, 99);
          // groups[6].toggle();
          break;
        }
        case '7' : {
          selectedgroup = 7;
          groups[7].setRGB(25, 187, 3);
          // groups[7].toggle();
          break;
        }
        case '8' : {
          selectedgroup = 8;
          groups[8].setRGB(80, 65, 137);
          // groups[8].toggle();
          break;
        }
        case '9' : {
          for (uint i=0;i<7;i++){
            groups[10+i].toggle();
          }
          break;
        }
        case '0' : {
          groups[9].toggle();
          break;
        }
        case 'w':{
					// Move up
          for (uint i=0;i<groups.size();i++){
            groups[i].moveY(-5);
          }
          break;
				}
				case 's':{
					// Move down
          for (uint i=0;i<groups.size();i++){
            groups[i].moveY(5);
          }
          break;
        }
				case 'a':{
					// Move left
          for (uint i=0;i<groups.size();i++){
            groups[i].moveX(-5);
          }
          break;
				}
				case 'd':{
					// Move right
          for (uint i=0;i<groups.size();i++){
            groups[i].moveX(5);
          }
          break;
				}
				case 'q':{
					// Rotate left
          for (uint i=0;i<groups.size();i++){
            //groups[i].rotate(-10, fb.getCX(), fb.getCY());
          }
          break;
				}
				case 'e':{
					// Rotate right
          for (uint i=0;i<groups.size();i++){
            //groups[i].rotate(10, fb.getCX(), fb.getCY());
          }
          break;
        }
				case ' ':{
					// Reset view
					break;
				}
        case 'i':{
					// Zoom in
          for (uint i=0;i<groups.size();i++){
            groups[i].setMultiplication(groups[i].getMultiplication()+0.1);
          }
					break;
				}
        case 'k':{
					// Zoom out
          if (groups[0].getMultiplication() > 1) {
            for (uint i=0;i<groups.size();i++){
              groups[i].setMultiplication(groups[i].getMultiplication()-0.1);
            }
          }
					break;
				}

/*        case '.':{
					// Select next group
          selectedgroup = (selectedgroup + 1) % groups.size();
          break;
				}
        case ',':{
					// Select prev group
          selectedgroup = (selectedgroup - 1) % groups.size();
					break;
				}*/
				default:{
					break;
        }
      }

      // Change Color
/*      r = groups[selectedgroup].getShapes()->at(0).getR();
      g = groups[selectedgroup].getShapes()->at(0).getG();
      b = groups[selectedgroup].getShapes()->at(0).getB();
      for (uint i=0;i<groups[selectedgroup].getShapes()->size();i++){
        groups[selectedgroup].getShapes()->at(i).setR(0);
        groups[selectedgroup].getShapes()->at(i).setG(0);
        groups[selectedgroup].getShapes()->at(i).setB(255);
      }*/

      for (uint i=2;i<=8;i++) {
        if ( (int)i != selectedgroup ) {
          groups[i].setRGB(237, 232, 223);
        }
      }

      // Draw to FrameBuffer
      fb.clearZBuffer();
      fb.clearScreen();
      fb.clearZBuffer();
      draw(fb, groups);
      fb.infoScreen();
      fb.render();

      usleep(10000);
    }
      usleep(5000);
  }

  // Reset input
  input.resetTermios();

  return 0;

}
