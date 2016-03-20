#include "reader.hpp"
#include "group.hpp"
#include "input.hpp"

#include <vector>

void draw(FrameBuffer &fb, std::vector<Group> groups){
  for (uint i=0;i<groups.size();i++){
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
  groups[0].addList(a.read("31-45.txt"));
  groups[0].setMultiplication(1.5);
  groups.push_back(Group());
  groups[1].addList(a.read("jalan.txt"));
  groups[1].setMultiplication(1.5);

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
					break;
				}
        case 'k':{
					// Zoom out
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
    }
  }

  // Reset input
  input.resetTermios();

  return 0;

}
