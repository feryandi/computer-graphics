#include <iostream>
#include "Polygon.class.h"
#include "FrameBuffer.class.h"
using namespace std;

int main() {
	FrameBuffer FB;

	int leftWing[] = {
					0, 24, 1, 22,
					1, 22, 4, 20,
					4, 20, 12, 18,
					12, 18, 20, 17,
					20, 17, 24, 17,
					24, 17, 31, 18,
					31, 18, 30, 24,
					30, 24, 31, 30,
					31, 30, 24, 31,
					24, 31, 20, 31,
					20, 31, 12, 30,
					12, 30, 4, 28,
					4, 28, 1, 26,
					1, 26, 0, 24};

	int box[] = {
		1, 1, 5, 1,
		5, 1, 5, 6,
		5, 6, 1, 6,
		1, 6, 1, 1
	};


	int *a = (int*) malloc(56 * sizeof(int));
	*a = *leftWing;

	/*Polygon test(0, 0, leftWing, 56);*/
	Polygon test(0, 0, box, 16);
	test.setPosition(0,0);
	test.setMultiplication(1);

	float d = 0;
	int i = 0;
	while ( i < 4 ) {
		test.setDegree(90);
		FB.canvas();
		FB.addPolygon(&test);
		FB.render();
		++d;
		++i;
		cout << endl << endl;
		//sleep(1);
	}

	return 0;
}