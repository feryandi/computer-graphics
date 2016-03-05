#include <iostream>
#include "frame_buffer.hpp"
using namespace std;

int main() {
	printf("start of program\n");

	FrameBuffer FB;

	FB.canvas();
	FB.render();

	// Manual Control
	/* Simpan buat nanti
	char input;
	float rotation = 0;
	int axis = 0;
	int n = 1;
	Input::initTermios();
	while (1) {
		if (Input::kbhit()){
			input = Input::getch();
			FB.resetAvailable();
			switch (input) {
				case 'w':{
					axis = 0;
					//rotX++;
					rotation = 1;
					break;
				}
				case 's':{
					axis = 0;
					//rotX--;
					rotation = -1;
					break;
				}
				case 'a':{
					axis = 1;
					//rotY--;
					rotation = -1;
					break;
				}
				case 'd':{
					axis = 1;
					//rotY++;
					rotation = 1;
					break;
				}
				case 'q':{
					axis = 2;
					//rotZ++;
					rotation = 1;
					break;
				}
				case 'e':{
					axis = 2;
					//rotZ--;
					rotation = -1;
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


			FB.canvas();
			FB.render();
		}
	}
*/
	return 0;
}
