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


  BezierCurve::generateLookupTable();


  // Read File
  // std::cout << fb.getCX() << "," << fb.getCY() << std::endl;
  groups.push_back(Group());
  groups[0].addList(a.read("jalan_angka.txt"));
  groups[0].setMultiplication(1);
  groups.push_back(Group());
  groups[1].addList(a.read("jalan_huruf.txt"));
  groups[1].setMultiplication(1);
  groups.push_back(Group());
  groups[2].addList(a.read("31-45.txt"));
  groups[2].setMultiplication(1);
  groups.push_back(Group());
  groups[3].addList(a.read("nama_jalan.txt"));
  groups[3].setMultiplication(1);

  // Initialize input
  input.initTermios();

  // Initial screen
  fb.clearScreen();
  fb.clearZBuffer();
  draw(fb, groups);
  fb.render();

  // Main loop
  char c;
  while (1){
    if (input.kbhit()){
      c = input.getch();
      switch (c){
        case '1' : {
          groups[2].toggle();
          break;
        }
        case '2' : {
          groups[1].toggle();
          groups[0].toggle();
          break;
        }
        case '3' : {
          break;
        }
        case '0' : {
          groups[3].toggle();
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
          break;
				}
				case 'e':{
					// Rotate right
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
				default:{
					break;
        }
      }
      // Draw to FrameBuffer
      fb.clearZBuffer();
      fb.clearScreen();
      fb.clearZBuffer();
      draw(fb, groups);
      fb.render();

      usleep(10000);
    }
      usleep(5000);
  }

  // Reset input
  input.resetTermios();

  return 0;

}
