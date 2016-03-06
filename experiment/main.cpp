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
	(*p).addPoint(48, 18, 0, 0);
	(*p).addPoint(41, 3, 0, 0);
	(*p).addPoint(30, 2, 0, 0);
	(*p).addPoint(19, 1, 0, 0);
	(*p).addPoint(2, 9, 0, 0);
	(*p).addPoint(0, 14, 0, 3);
	(*p).addPoint(0, 14, 0, 0);
	(*p).addPoint(2, 16, 0, 0);
	(*p).addPoint(8, 14, 0, 0);
	(*p).addPoint(14, 12, 0, 0);
	(*p).addPoint(26, 3, 0, 0);
	(*p).addPoint(35, 5, 0, 0);
	(*p).addPoint(41, 7, 0, 0);
	(*p).addPoint(48, 18, 0, 3);	
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

void createNose(Polygon *p) {
	(*p).addPoint(2, 0, 0, 0);	
	(*p).addPoint(0, 8, 0, 0);	
	(*p).addPoint(2, 16, 0, 0);	
	(*p).addPoint(12, 8, 0, 0);	
	(*p).addPoint(16, 10, 0, 0);	
	(*p).addPoint(20, 20, 0, 0);	
	(*p).addPoint(28, 22, 0, 0);	
	(*p).addPoint(36, 20, 0, 0);	
	(*p).addPoint(40, 10, 0, 0);	
	(*p).addPoint(44, 8, 0, 0);	
	(*p).addPoint(54, 16, 0, 0);	
	(*p).addPoint(56, 8, 0, 0);	
	(*p).addPoint(54, 0, 0, 0);	
}

void createLeftEar(Polygon *p) {	
	(*p).addPoint(27, 14, 0, 0);
	(*p).addPoint(17, 0, 0, 0);
	(*p).addPoint(9, 7, 0, 0);
	(*p).addPoint(0, 14, 0, 0);
	(*p).addPoint(5, 42, 0, 0);
	(*p).addPoint(10, 42, 0, 0);
	(*p).addPoint(16, 53, 0, 0);
	(*p).addPoint(12, 55, 0, 0);
	(*p).addPoint(11, 62, 0, 0);
	(*p).addPoint(30, 68, 0, 0);
	(*p).addPoint(34, 64, 0, 0);
}

void createRightEar(Polygon *p) {	
	(*p).addPoint(7, 14, 0, 0);
	(*p).addPoint(17, 0, 0, 0);
	(*p).addPoint(25, 7, 0, 0);
	(*p).addPoint(34, 14, 0, 0);
	(*p).addPoint(29, 42, 0, 0);
	(*p).addPoint(24, 42, 0, 0);
	(*p).addPoint(18, 53, 0, 0);
	(*p).addPoint(22, 55, 0, 0);
	(*p).addPoint(13, 62, 0, 0);
	(*p).addPoint(4, 68, 0, 0);
	(*p).addPoint(0, 64, 0, 0);
}

void doCemberut(FrameBuffer *FB, vector<Polygon*> *polies, Polygon *mouth , int r) {
	// Cemberut
	int f = 0;
	while ( f < 10 ) {
		(*FB).canvas();

		(*FB).draw(*polies);
		(*FB).render();

		(*mouth).movePoint(8, 0, 2*r, 0);
		(*mouth).movePoint(9, 0, 3*r, 0);
		(*mouth).movePoint(19, 0, 3*r, 0);
		(*mouth).movePoint(22, 0, 3*r, 0);

		(*mouth).movePoint(11, 0, 2*r, 0);
		(*mouth).movePoint(12, 0, -3*r, 0);
		(*mouth).movePoint(13, 0, 2*r, 0);

		(*mouth).movePoint(15, 0, 3*r, 0);
		(*mouth).movePoint(17, 0, 3*r, 0);
		(*mouth).movePoint(20, 0, 3*r, 0);
		(*mouth).movePoint(16, 0, 2*r, 0);
		(*mouth).movePoint(0, 0, 2*r, 0);

		(*mouth).movePoint(18, 0, -3*r, 0);
		(*mouth).movePoint(21, 0, -3*r, 0);
		++f;

		usleep(10000);
	}
}

void doSenyum(FrameBuffer *FB, vector<Polygon*> *polies, Polygon *mouth, int r) {
	// Senyum
	int f = 0;
	while ( f < 5 ) {
		(*FB).canvas();

		(*FB).draw(*polies);
		(*FB).render();

		(*mouth).movePoint(8, 0, -2*r, 0);
		(*mouth).movePoint(9, 0, -3*r, 0);
		(*mouth).movePoint(19, 0, -3*r, 0);
		(*mouth).movePoint(22, 0, -3*r, 0);

		(*mouth).movePoint(11, 0, -2*r, 0);
		(*mouth).movePoint(12, 0, 3*r, 0);
		(*mouth).movePoint(13, 0, -2*r, 0);

		(*mouth).movePoint(15, 0, -3*r, 0);
		(*mouth).movePoint(17, 0, -3*r, 0);
		(*mouth).movePoint(20, 0, -3*r, 0);
		(*mouth).movePoint(16, 0, -2*r, 0);
		(*mouth).movePoint(0, 0, -2*r, 0);

		(*mouth).movePoint(18, 0, 3*r, 0);
		(*mouth).movePoint(21, 0, 3*r, 0);
		++f;

		usleep(10000);
	}
}

void doTertawa(FrameBuffer *FB, vector<Polygon*> *polies, Polygon *mouth, int r) {
	// Tertawa
	for (int i = 0; i < 5; i++) {
		int c = 1;
		if ( (i % 2) == 0 ) {
			c = 1;
		} else {
			c = -1;
		}

		int f = 0;
		while ( f < 10 ) {
			(*FB).canvas();

			(*FB).draw(*polies);
			(*FB).render();

			(*mouth).movePoint(11, 0, c*(3-i)*r, 0);
			(*mouth).movePoint(12, 0, c*(5-i)*r, 0);
			(*mouth).movePoint(13, 0, c*(3-i)*r, 0);

			(*mouth).movePoint(21, 0, c*(5-i)*r, 0);
			++f;

			usleep(10000);
		}
	}
}

void doKaget(FrameBuffer *FB, vector<Polygon*> *polies, Polygon *mouth, Polygon *left_eyebrow, int r) {
	// Kaget
	int f = 0;
	while ( f < 10 ) {
		(*FB).canvas();

		(*FB).draw(*polies);
		(*FB).render();

		(*mouth).movePoint(11, 0, 8*r, 0);
		(*mouth).movePoint(12, 0, 14*r, 0);
		(*mouth).movePoint(13, 0, 8*r, 0);

		(*mouth).movePoint(21, 0, 14*r, 0);

		(*mouth).movePoint(8, 0, 2*r, 0);
		(*mouth).movePoint(9, -2*r, 2*r, 0);
		(*mouth).movePoint(19, -2*r, 2*r, 0);
		(*mouth).movePoint(22, -2*r, 2*r, 0);

		(*mouth).movePoint(15, 2*r, 2*r, 0);
		(*mouth).movePoint(17, 2*r, 2*r, 0);
		(*mouth).movePoint(20, 2*r, 2*r, 0);
		(*mouth).movePoint(16, 0, 2*r, 0);
		(*mouth).movePoint(0, 0, 2*r, 0);

		(*left_eyebrow).movePosition(0, -5*r, 0);

		++f;

		usleep(10000);
	}
}

void doImut(FrameBuffer *FB, vector<Polygon*> *polies, Polygon *mouth, Polygon *left_eye, Polygon *left_eyebrow, int r) {
	// Imut
	int f = 0;
	while ( f < 15 ) {
		(*FB).canvas();

		(*FB).draw(*polies);
		(*FB).render();

		(*mouth).movePoint(2, 0, -1*r, 0);
		(*mouth).movePoint(3, 0, -1*r, 0);
		(*mouth).movePoint(4, 0, -1*r, 0);
		(*mouth).movePoint(5, 0, -1*r, 0);
		(*mouth).movePoint(6, 0, -1*r, 0);

		(*mouth).movePoint(8, -2*r, 0, 0);
		(*mouth).movePoint(9, -2*r, 0, 0);
		(*mouth).movePoint(19, -2*r, 0, 0);
		(*mouth).movePoint(22, -2*r, 0, 0);

		(*mouth).movePoint(10, -3*r, 1*r, 0);
		(*mouth).movePoint(11, -3*r, 1*r, 0);
		(*mouth).movePoint(12, 0, 2*r, 0);
		(*mouth).movePoint(13, 3*r, 1*r, 0);
		(*mouth).movePoint(14, 3*r, 1*r, 0);

		(*mouth).movePoint(15, 2*r, 0, 0);
		(*mouth).movePoint(17, 2*r, 0, 0);
		(*mouth).movePoint(20, 2*r, 0, 0);
		(*mouth).movePoint(16, 2*r, 0, 0);
		(*mouth).movePoint(0, 2*r, 0, 0);

		(*mouth).movePoint(18, 0, 1*r, 0);
		(*mouth).movePoint(21, 0, 1*r, 0);
		++f;

		usleep(10000);
	}

	f = 0;
	while ( f < 5 ) {
		(*FB).canvas();

		(*FB).draw(*polies);
		(*FB).render();

		(*left_eye).movePoint(1, 0, 8*r, 0);
		(*left_eye).movePoint(2, 0, 15*r, 0);
		(*left_eye).movePoint(3, 0, 8*r, 0);

		(*left_eyebrow).movePosition(0, 2*r, 0);

		++f;
		usleep(10000);
	}
}

void doMenangis(FrameBuffer *FB, vector<Polygon*> *polies, Polygon *mouth, 
				Polygon *left_eye, Polygon *left_eyebrow, Polygon *right_eye, Polygon *right_eyebrow, int r) {
	// Menangis
	int f = 0;
	while ( f < 10 ) {
		(*FB).canvas();

		(*FB).draw(*polies);
		(*FB).render();

		(*mouth).movePoint(8, 0, 2*r, 0);
		(*mouth).movePoint(9, 0, 3*r, 0);
		(*mouth).movePoint(19, 0, 3*r, 0);
		(*mouth).movePoint(22, 0, 3*r, 0);

		(*mouth).movePoint(11, 0, 2*r, 0);
		(*mouth).movePoint(12, 0, 3*r, 0);
		(*mouth).movePoint(13, 0, 2*r, 0);

		(*mouth).movePoint(15, 0, 3*r, 0);
		(*mouth).movePoint(17, 0, 3*r, 0);
		(*mouth).movePoint(20, 0, 3*r, 0);
		(*mouth).movePoint(16, 0, 2*r, 0);
		(*mouth).movePoint(0, 0, 2*r, 0);

		(*mouth).movePoint(18, 0, -3*r, 0);
		(*mouth).movePoint(21, 0, 7*r, 0);

		(*left_eye).movePoint(1, 0, 4*r, 0);
		(*left_eye).movePoint(2, 0, 7*r, 0);
		(*left_eye).movePoint(3, 0, 4*r, 0);

		(*right_eye).movePoint(1, 0, 4*r, 0);
		(*right_eye).movePoint(2, 0, 7*r, 0);
		(*right_eye).movePoint(3, 0, 4*r, 0);

		(*left_eyebrow).movePoint(1, 0, 2*r, 0);
		(*left_eyebrow).movePoint(2, 0, 3*r, 0);
		(*left_eyebrow).movePoint(3, 0, 3*r, 0);
		(*left_eyebrow).movePoint(4, 0, 4*r, 0);
		(*left_eyebrow).movePoint(8, 0, 3*r, 0);
		(*left_eyebrow).movePoint(9, 0, 4*r, 0);
		(*left_eyebrow).movePoint(11, 0, 4*r, 0);
		(*left_eyebrow).movePoint(12, 0, 4*r, 0);

		(*right_eyebrow).movePoint(1, 0, 2*r, 0);
		(*right_eyebrow).movePoint(2, 0, 3*r, 0);
		(*right_eyebrow).movePoint(3, 0, 3*r, 0);
		(*right_eyebrow).movePoint(4, 0, 4*r, 0);
		(*right_eyebrow).movePoint(8, 0, 3*r, 0);
		(*right_eyebrow).movePoint(9, 0, 4*r, 0);
		(*right_eyebrow).movePoint(11, 0, 4*r, 0);
		(*right_eyebrow).movePoint(12, 0, 4*r, 0);
		++f;

		usleep(10000);
	}
}

void doHah(FrameBuffer *FB, vector<Polygon*> *polies, Polygon *left_eyebrow, Polygon *right_eyebrow, int r)  {
	int f = 0;
	while ( f < 5 ) {
		(*FB).canvas();

		(*FB).draw(*polies);
		(*FB).render();


		(*left_eyebrow).movePosition(0, -6*r, 0);
		(*right_eyebrow).movePosition(0, -6*r, 0);
		++f;

		usleep(10000);
	}
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

	Polygon right_eyebrow;
	createRightEyebrow(&right_eyebrow);
	right_eyebrow.setPosition((FB.getVInfoX()/2)+15, (FB.getVInfoY()/2)-135, 0);
	right_eyebrow.setMultiplication(3);

	Polygon nose;
	createNose(&nose);
	nose.setPosition((FB.getVInfoX()/2)-90, (FB.getVInfoY()/2)+80, 0);
	nose.setMultiplication(2.25);
	
	Polygon right_ear;
	createRightEar(&right_ear);
	right_ear.setPosition((FB.getVInfoX()/2)+190, (FB.getVInfoY()/2)-135, 0);
	right_ear.setMultiplication(3);

	Polygon left_ear;
	createLeftEar(&left_ear);
	left_ear.setPosition((FB.getVInfoX()/2)-352, (FB.getVInfoY()/2)-135, 0);
	left_ear.setMultiplication(3);

	static Polygon* arrStar[] = {
		&face, &mouth, &left_eye, &left_eyebrow, &right_eye, &right_eyebrow, &nose, &right_ear, &left_ear
	};
	vector<Polygon*> star(arrStar, arrStar + sizeof(arrStar) / sizeof(arrStar[0]) );

	FB.canvas();

	FB.draw(star);
	FB.render();

	doCemberut(&FB, &star, &mouth, 1);
	sleep(2);
	doCemberut(&FB, &star, &mouth, -1);

	doSenyum(&FB, &star, &mouth, 1);
	sleep(2);
	doSenyum(&FB, &star, &mouth, -1);

	doTertawa(&FB, &star, &mouth, 1);
	sleep(2);
	doTertawa(&FB, &star, &mouth, -1);

	doKaget(&FB, &star, &mouth, &left_eyebrow, 1);
	sleep(2);
	doKaget(&FB, &star, &mouth, &left_eyebrow, -1);

	doImut(&FB, &star, &mouth, &left_eye, &left_eyebrow, 1);
	sleep(2);
	doImut(&FB, &star, &mouth, &left_eye, &left_eyebrow, -1);

	doMenangis(&FB, &star, &mouth, &left_eye, &left_eyebrow, &right_eye, &right_eyebrow, 1);
	sleep(2);
	doMenangis(&FB, &star, &mouth, &left_eye, &left_eyebrow, &right_eye, &right_eyebrow, -1);

	doHah(&FB, &star, &left_eyebrow, &right_eyebrow, 1);
	sleep(2);
	doHah(&FB, &star, &left_eyebrow, &right_eyebrow, -1);


	return 0;
}