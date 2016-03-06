#include <iostream>
#include "Polygon.class.h"
#include "FrameBuffer.class.h"
#include "Input.class.h"
using namespace std;

int mouth[] = {
	0, 0, 0,	0, 0, 0,
	6, 0, 0,	0, 0, 0,
	3, 6, 0, 	0, 0, 0
};

int main() {
	printf("start of program\n");

	FrameBuffer FB;
	FB.initAvailable();

	Polygon pmouth(0, 0, 0, mouth, 18);
	pmouth.setPosition(0, 0, 0);
	pmouth.setMultiplication(10);
	pmouth.setCenter(0, 0, 0);
	pmouth.setFillColor(135, 206, 250);


	static Polygon* arrStar[] = {
		&pmouth
	};
	vector<Polygon*> star(arrStar, arrStar + sizeof(arrStar) / sizeof(arrStar[0]) );


	FB.canvas();
	FB.draw(star);
	//FB.drawBeizer(star);

	FB.render();


	return 0;
}
