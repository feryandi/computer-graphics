#include <iostream>
#include "FrameBuffer.class.h"
using namespace std;

int main () {
	FrameBuffer FB;

	Polygon p;
	p.addPoint(50, 50, 0, 0);
	p.addPoint(50, 40, 0, 0);
	p.addPoint(60, 40, 0, 1);
	p.addPoint(150, 40, 0, 0);
	p.addPoint(160, 40, 0, 0);
	p.addPoint(160, 50, 0, 1);
	p.addPoint(160, 150, 0, 0);
	p.addPoint(160, 160, 0, 0);
	p.addPoint(150, 160, 0, 1);//8
	p.addPoint(60, 160, 0, 0);
	p.addPoint(50, 160, 0, 0);
	p.addPoint(50, 150, 0, 1);
	p.addPoint(50, 50, 0, 0);

	FB.canvas();

	static Polygon* arrStar[] = {
		&p
	};
	vector<Polygon*> star(arrStar, arrStar + sizeof(arrStar) / sizeof(arrStar[0]) );

	/*while (1 == 1) {
		FB.canvas();

		FB.draw(star);
		FB.render();*/

/*		p.movePoint(6, 1, 1, 0);
		p.movePoint(7, 1, 1, 0);
		p.movePoint(8, 1, 1, 0);*/

		//cout << (p.getPoint(0))->getX() << endl;

		/*usleep(60000);
	}*/
		FB.canvas();

		FB.draw(star);
		FB.render();

		FB.canvas();

		FB.draw(star);
		FB.render();
	return 0;
}