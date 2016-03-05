#include <iostream>
#include "frame_buffer.hpp"
using namespace std;

int head[] = {
	2, 0, 0, 8, 0, 0,
	8, 0, 0, 9, 2, 0,
	9, 2, 0, 10, 1, 0,
	10, 1, 0, 9, 5, 0,
	9, 5, 0, 9, 7, 0,
	9, 7, 0, 8, 10, 0,
	8, 10, 0, 2, 11, 0,
	2, 11, 0, 1, 7, 0,
	1, 7, 0, 1, 5, 0,
	1, 5, 0, 0, 1, 0,
	0, 1, 0, 1, 2, 0,
	1, 2, 0, 2, 0, 0
};

int RightEyeTimid[] = {
	6, 2, 0, 8, 3, 0,
	8, 3, 0, 8, 4, 0,
	8, 4, 0, 6, 4, 0,
	6, 4, 0, 6, 2, 0
};

int LeftEyeTimid[] = {
	2, 3, 0, 4, 2, 0,
	4, 2, 0, 4, 4, 0,
	4, 4, 0, 2, 4, 0,
	2, 4, 0, 2, 3, 0
};

int RightEyeConfidence[] = {
	6, 3, 0, 8, 2, 0,
	8, 2, 0, 8, 4, 0,
	8, 4, 0, 6, 4, 0,
	6, 4, 0, 6, 3, 0
};

int LeftEyeConfidence[] = {
	2, 2, 0, 4, 3, 0,
	4, 3, 0, 4, 4, 0,
	4, 4, 0, 2, 4, 0,
	2, 4, 0, 2, 2, 0
};

int CPMouthSmileUp[] = {
	2, 6, 0,
	5, 8, 0,
	8, 6, 0
};

int CPMouthSmileDown[] = {
	2, 6, 0,
	5, 9, 0,
	8, 6, 0
};

int CPRightEyes[] = {
	6, 4, 0,
	6, 2, 0,
	8, 4, 0
};

int CPMouthSadUp[] = {
	2, 9, 0,
	5, 6, 0,
	8, 9, 0
};

int CPMouthSadDown[] = {
	2, 9, 0,
	5, 7, 0,
	8, 9, 0
};

int CPMouthGaspUp[] = {
	2, 8, 0,
	5, 5, 0,
	8, 8, 0
};

int CPMouthGaspDown[] = {
	2, 8, 0,
	5, 10, 0,
	8, 8, 0
};

int main() {
	printf("start of program\n");

	FrameBuffer FB;

	FB.canvas();
	FB.render();

	// Manual Control
	// Simpan buat nanti
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
	return 0;
}
