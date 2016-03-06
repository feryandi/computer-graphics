#include <iostream>
#include "FrameBuffer.class.h"
using namespace std;

void createMouth(Polygon *p) {
	//Left Upper Lips (0)
	(*p).addPoint(1, 1, 0, 0);
	(*p).addPoint(2, 1, 0, 0);
	(*p).addPoint(4, 0, 0, 0);
	(*p).addPoint(7, 0, 0, 1);
	(*p).addPoint(10, 1, 0, 1);

	//Right Upper Lips (5)
	(*p).addPoint(13, 0, 0, 0);
	(*p).addPoint(16, 0, 0, 0);
	(*p).addPoint(18, 1, 0, 0);
	(*p).addPoint(19, 1, 0, 1);
	(*p).addPoint(20, 1, 0, 0); // Titik Geser (9)

	//Right Lower Lips (10)
	(*p).addPoint(19, 2, 0, 0);
	(*p).addPoint(14, 3, 0, 0);
	(*p).addPoint(10, 4, 0, 0);

	//Left Lower Lips (13)
	(*p).addPoint(6, 3, 0, 0);
	(*p).addPoint(1, 2, 0, 0);
	(*p).addPoint(0, 1, 0, 1); // Titik Geser (15)
	(*p).addPoint(1, 1, 0, 3); 

	//Top Mouth (17)
	(*p).addPoint(0, 1, 0, 0);
	(*p).addPoint(10, 2, 0, 0);
	(*p).addPoint(20, 1, 0, 3);

	//Bottom Mouth (20)
	(*p).addPoint(0, 1, 0, 0);
	(*p).addPoint(10, 2, 0, 0);
	(*p).addPoint(20, 1, 0, 3);	
}

void createFace(Polygon *p) {	
	(*p).addPoint(18, 0, 0, 0);
	(*p).addPoint(36, 0, 0, 0);
	(*p).addPoint(34, 18, 0, 3);

	(*p).addPoint(34, 18, 0, 0);
	(*p).addPoint(31, 37, 0, 0);
	(*p).addPoint(30, 39, 0, 0);
	(*p).addPoint(23, 47, 0, 0);
	(*p).addPoint(18, 47, 0, 0);
	(*p).addPoint(15, 47, 0, 0);
	(*p).addPoint(6, 39, 0, 0);
	(*p).addPoint(5, 37, 0, 0);
	(*p).addPoint(2, 18, 0, 3);

	(*p).addPoint(2, 18, 0, 0);
	(*p).addPoint(0, 0, 0, 0);
	(*p).addPoint(18, 0, 0, 3);
}

int main () {
	FrameBuffer FB;

	Polygon mouth;
	createMouth(&mouth);
	mouth.setPosition((FB.getVInfoX()/2)-125, (FB.getVInfoY()/2)+165, 0);
	mouth.setMultiplication(10);

	Polygon face;
	createFace(&face);
	face.setPosition((FB.getVInfoX()/2)-300, 55, 0);
	face.setMultiplication(15);

	FB.canvas();

	static Polygon* arrStar[] = {
		&face, &mouth
	};
	vector<Polygon*> star(arrStar, arrStar + sizeof(arrStar) / sizeof(arrStar[0]) );

	//while (1) {
		FB.canvas();

		FB.draw(star);
		FB.render();

		int f;

		// Cemberut
		/*f = 0;
		while ( f < 10 ) {
			FB.canvas();

			FB.draw(star);
			FB.render();

			mouth.movePoint(8, 0, 2, 0);
			mouth.movePoint(9, 0, 3, 0);
			mouth.movePoint(19, 0, 3, 0);
			mouth.movePoint(22, 0, 3, 0);

			mouth.movePoint(11, 0, 2, 0);
			mouth.movePoint(12, 0, -3, 0);
			mouth.movePoint(13, 0, 2, 0);

			mouth.movePoint(15, 0, 3, 0);
			mouth.movePoint(17, 0, 3, 0);
			mouth.movePoint(20, 0, 3, 0);
			mouth.movePoint(16, 0, 2, 0);
			mouth.movePoint(0, 0, 2, 0);

			mouth.movePoint(18, 0, -3, 0);
			mouth.movePoint(21, 0, -3, 0);
			++f;

			usleep(10000);
		}*/

		// Senyum
		f = 0;
		while ( f < 5 ) {
			FB.canvas();

			FB.draw(star);
			FB.render();

			mouth.movePoint(8, 0, -2, 0);
			mouth.movePoint(9, 0, -3, 0);
			mouth.movePoint(19, 0, -3, 0);
			mouth.movePoint(22, 0, -3, 0);

			mouth.movePoint(11, 0, -2, 0);
			mouth.movePoint(12, 0, 3, 0);
			mouth.movePoint(13, 0, -2, 0);

			mouth.movePoint(15, 0, -3, 0);
			mouth.movePoint(17, 0, -3, 0);
			mouth.movePoint(20, 0, -3, 0);
			mouth.movePoint(16, 0, -2, 0);
			mouth.movePoint(0, 0, -2, 0);

			mouth.movePoint(18, 0, 3, 0);
			mouth.movePoint(21, 0, 3, 0);
			++f;

			usleep(10000);
		}

		// Tertawa
		/*for (int i = 0; i < 5; i++) {
			int c = 1;
			if ( (i % 2) == 0 ) {
				c = 1;
			} else {
				c = -1;
			}

			f = 0;
			while ( f < 10 ) {
				FB.canvas();

				FB.draw(star);
				FB.render();

				mouth.movePoint(11, 0, c*(3-i), 0);
				mouth.movePoint(12, 0, c*(5-i), 0);
				mouth.movePoint(13, 0, c*(3-i), 0);

				mouth.movePoint(21, 0, c*(5-i), 0);
				++f;

				usleep(10000);
			}
		}*/

	//}
	return 0;
}