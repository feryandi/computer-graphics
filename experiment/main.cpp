#include <iostream>
#include "FrameBuffer.class.h"
using namespace std;

int main () {
	FrameBuffer FB;

	Polygon mouth;
	//Left Upper Lips (0)
	mouth.addPoint(10, 10, 0, 0);
	mouth.addPoint(20, 10, 0, 0);
	mouth.addPoint(40, 0, 0, 0);
	mouth.addPoint(70, 0, 0, 1);
	mouth.addPoint(100, 10, 0, 1);

	//Right Upper Lips (5)
	mouth.addPoint(130, 0, 0, 0);
	mouth.addPoint(160, 0, 0, 0);
	mouth.addPoint(180, 10, 0, 0);
	mouth.addPoint(190, 10, 0, 1);
	mouth.addPoint(200, 10, 0, 0); // Titik Geser (9)

	//Right Lower Lips (10)
	mouth.addPoint(190, 20, 0, 0);
	mouth.addPoint(140, 30, 0, 0);
	mouth.addPoint(100, 40, 0, 0);

	//Left Lower Lips (13)
	mouth.addPoint(60, 30, 0, 0);
	mouth.addPoint(10, 20, 0, 0);
	mouth.addPoint(0, 10, 0, 1); // Titik Geser (15)
	mouth.addPoint(10, 10, 0, 3); 

	//Top Mouth (17)
	mouth.addPoint(0, 10, 0, 0);
	mouth.addPoint(100, 20, 0, 0);
	mouth.addPoint(200, 10, 0, 3);

	//Bottom Mouth (20)
	mouth.addPoint(0, 10, 0, 0);
	mouth.addPoint(100, 20, 0, 0);
	mouth.addPoint(200, 10, 0, 3);

	FB.canvas();

	static Polygon* arrStar[] = {
		&mouth
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
/*		f = 0;
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
		}*/

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

				mouth.movePoint(11, 0, c*3, 0);
				mouth.movePoint(12, 0, c*5, 0);
				mouth.movePoint(13, 0, c*3, 0);

				mouth.movePoint(21, 0, c*5, 0);
				++f;

				usleep(10000);
			}
		}*/

	//}
	return 0;
}