#include <iostream>
#include "FrameBuffer.class.h"
using namespace std;

int main () {
	FrameBuffer FB;

	Polygon p;
	p.addPoint(50, 50, 0, 0);
	p.addPoint(100, 100, 0, 0);
	p.addPoint(150, 50, 0, 0);
	p.addPoint(150, 50, 0, 1);
	p.addPoint(150, 150, 0, 1);

	FB.canvas();

	static Polygon* arrStar[] = {
		&p
	};
	vector<Polygon*> star(arrStar, arrStar + sizeof(arrStar) / sizeof(arrStar[0]) );

	//while (1 == 1) {
		FB.canvas();

		FB.draw(star);
		FB.render();
/*
		p.movePoint(0, 0, 1, 0);
		p.movePoint(2, 0, 1, 0);*/
	//}

	return 0;
}