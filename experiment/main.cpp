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

void createLeftEye(Polygon *p) {	
	(*p).addPoint(0, 24, 0, 0);
	(*p).addPoint(16, 0, 0, 0);
	(*p).addPoint(44, 5, 0, 0);
	(*p).addPoint(70, 9, 0, 0);
	(*p).addPoint(72, 18, 0, 3);

	(*p).addPoint(72, 18, 0, 0);
	(*p).addPoint(68, 36, 0, 0);
	(*p).addPoint(42, 36, 0, 0);
	(*p).addPoint(16, 36, 0, 0);
	(*p).addPoint(0, 24, 0, 3);
}

void createLeftEyebrow(Polygon *p) {	
	(*p).addPoint(0, 18, 0, 0);
	(*p).addPoint(7, 3, 0, 0);
	(*p).addPoint(18, 2, 0, 0);
	(*p).addPoint(29, 1, 0, 0);
	(*p).addPoint(48, 9, 0, 0);
	(*p).addPoint(46, 14, 0, 3);
	(*p).addPoint(46, 14, 0, 0);
	(*p).addPoint(46, 16, 0, 0);
	(*p).addPoint(40, 14, 0, 0);
	(*p).addPoint(34, 12, 0, 0);
	(*p).addPoint(28, 3, 0, 0);
	(*p).addPoint(16, 5, 0, 0);
	(*p).addPoint(7, 7, 0, 0);
	(*p).addPoint(0, 18, 0, 3);
}

void createRightEyebrow(Polygon *p) {	
}

void createRightEye(Polygon *p) {
	(*p).addPoint(0, 18, 0, 0);
	(*p).addPoint(2, 9, 0, 0);
	(*p).addPoint(28, 5, 0, 0);
	(*p).addPoint(56, 0, 0, 0);
	(*p).addPoint(72, 24, 0, 3);

	(*p).addPoint(72, 24, 0, 0);
	(*p).addPoint(56, 36, 0, 0);
	(*p).addPoint(30, 36, 0, 0);
	(*p).addPoint(4, 36, 0, 0);
	(*p).addPoint(0, 18, 0, 3);
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

	Polygon left_eye;
	createLeftEye(&left_eye);
	left_eye.setPosition((FB.getVInfoX()/2)-200, (FB.getVInfoY()/2)-85, 0);
	left_eye.setMultiplication(1.5);

	Polygon left_eyebrow;
	createLeftEyebrow(&left_eyebrow);
	left_eyebrow.setPosition((FB.getVInfoX()/2)-220, (FB.getVInfoY()/2)-135, 0);
	left_eyebrow.setMultiplication(3);

	Polygon right_eye;
	createRightEye(&right_eye);
	right_eye.setPosition((FB.getVInfoX()/2)+20, (FB.getVInfoY()/2)-85, 0);
	right_eye.setMultiplication(1.5);

	FB.canvas();

	static Polygon* arrStar[] = {
		&face, &mouth, &left_eye, &right_eye, &left_eyebrow
	};
	vector<Polygon*> star(arrStar, arrStar + sizeof(arrStar) / sizeof(arrStar[0]) );

	//while (1) {
		FB.canvas();

		FB.draw(star);
		FB.render();

		int f;

		// Cemberut
/*		f = 0;
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

				mouth.movePoint(11, 0, c*(3-i), 0);
				mouth.movePoint(12, 0, c*(5-i), 0);
				mouth.movePoint(13, 0, c*(3-i), 0);

				mouth.movePoint(21, 0, c*(5-i), 0);
				++f;

				usleep(10000);
			}
		}*/

		// Kaget
/*		f = 0;
		while ( f < 20 ) {
			FB.canvas();

			FB.draw(star);
			FB.render();

			mouth.movePoint(11, 0, 4, 0);
			mouth.movePoint(12, 0, 7, 0);
			mouth.movePoint(13, 0, 4, 0);

			mouth.movePoint(21, 0, 7, 0);

			mouth.movePoint(8, 0, 1, 0);
			mouth.movePoint(9, -1, 1, 0);
			mouth.movePoint(19, -1, 1, 0);
			mouth.movePoint(22, -1, 1, 0);

			mouth.movePoint(15, 1, 1, 0);
			mouth.movePoint(17, 1, 1, 0);
			mouth.movePoint(20, 1, 1, 0);
			mouth.movePoint(16, 0, 1, 0);
			mouth.movePoint(0, 0, 1, 0);
			++f;

			usleep(10000);
		}*/

		// Imut
		f = 0;
		while ( f < 15 ) {
			FB.canvas();

			FB.draw(star);
			FB.render();

			mouth.movePoint(2, 0, -1, 0);
			mouth.movePoint(3, 0, -1, 0);
			mouth.movePoint(4, 0, -1, 0);
			mouth.movePoint(5, 0, -1, 0);
			mouth.movePoint(6, 0, -1, 0);

			mouth.movePoint(8, -2, 0, 0);
			mouth.movePoint(9, -2, 0, 0);
			mouth.movePoint(19, -2, 0, 0);
			mouth.movePoint(22, -2, 0, 0);

			mouth.movePoint(10, -3, 1, 0);
			mouth.movePoint(11, -3, 1, 0);
			mouth.movePoint(12, 0, 2, 0);
			mouth.movePoint(13, 3, 1, 0);
			mouth.movePoint(14, 3, 1, 0);

			mouth.movePoint(15, 2, 0, 0);
			mouth.movePoint(17, 2, 0, 0);
			mouth.movePoint(20, 2, 0, 0);
			mouth.movePoint(16, 2, 0, 0);
			mouth.movePoint(0, 2, 0, 0);

			mouth.movePoint(18, 0, 1, 0);
			mouth.movePoint(21, 0, 1, 0);
			++f;

			usleep(10000);
		}

		f = 0;
		while ( f < 5 ) {
			FB.canvas();

			FB.draw(star);
			FB.render();

			left_eye.movePoint(1, 0, 8, 0);
			left_eye.movePoint(2, 0, 10, 0);
			left_eye.movePoint(3, 0, 8, 0);

			++f;
			usleep(10000);
		}

	//}
	return 0;
}