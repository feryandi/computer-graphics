#include <iostream>
#include "Polygon.class.h"
#include "FrameBuffer.class.h"
using namespace std;

/*
// 40
int jakartaUtara[] = {
	16, 3, 18, 2,
	18, 2, 28, 7,
	28, 7, 38, 8,
	38, 8, 46, 11,
	46, 11, 51, 10,
	51, 10, 56, 15,
	56, 15, 70, 15,
	70, 15, 82, 6,
	82, 6, 94, 8,
	94, 8, 98, 8,
	98, 8, 100, 6,
	100, 6, 110, 4,
	110, 4, 114, 4,
	114, 4, 116, 2,
	116, 2, 124, 0,
	124, 0, 124, 30,
	124, 30, 116, 30,
	116, 30, 114, 32,
	114, 32, 112, 31,
	112, 31, 108, 34,
	108, 34, 104, 34,
	104, 34, 103, 30,
	103, 30, 99, 30,
	99, 30, 101, 33,
	101, 33, 101, 39,
	101, 39, 94, 40,
	94, 40, 82, 35,
	82, 35, 64, 29,
	64, 29, 58, 24,
	58, 24, 55, 22,
	55, 22, 54, 20,
	54, 20, 52, 20,
	52, 20, 50, 22,
	50, 22, 50, 24,
	50, 24, 38, 24,
	38, 24, 38, 22,
	38, 22, 28, 18,
	28, 18, 20, 12,
	20, 12, 16, 6,
	16,	6, 16, 3
};

// 40
int jakartaBarat[] = {
	16, 3, 12, 4,
	12, 4, 4, 4,
	4, 4, 2, 5,
	2, 5, 0, 5,
	0, 5, 0, 8,
	0, 8, 2, 11,
	2, 11, 0, 16,
	0, 16, 1, 20,
	1, 20, 2, 38,
	2, 38, 14, 43,
	14, 43, 14, 45,
	14, 45, 16, 45,
	16, 45, 16, 52,
	16, 52, 14, 54,
	14, 54, 13, 56,
	13, 56, 14, 58,
	14, 58, 21, 59,
	21, 59, 38, 59,
	38, 59, 38, 54,
	38, 54, 40, 54,
	40, 54, 40, 52,
	40, 52, 46, 52,
	46, 52, 50, 44,
	50, 44, 52, 44,
	52, 44, 52, 39,
	52, 39, 48, 32,
	48, 32, 51, 30,
	51, 30, 60, 30,
	60, 30, 58, 24,
	58, 24, 55, 22,
	55, 22, 54, 20,
	54, 20, 52, 20,
	52, 20, 50, 22,
	50, 22, 50, 24,
	50, 24, 38, 24,
	38, 24, 38, 22,
	38, 22, 28, 18,
	28, 18, 20, 12,
	20, 12, 16, 6,
	16, 6, 16, 3
};

// 41
int jakartaSelatan[] = {
	21, 59, 38, 59,
	38, 59, 38, 54,
	38, 54, 40, 54,
	40, 54, 40, 52,
	40, 52, 46, 52,
	46, 52, 46, 61,
	46, 61, 57, 54,
	57, 54, 58, 50,
	58, 50, 70, 50,
	70, 50, 74, 58,
	74, 58, 74, 70,
	74, 70, 72, 76,
	72, 76, 67, 82,
	67, 82, 68, 88,
	68, 88, 72, 94,
	72, 94, 68, 98,
	68, 98, 68, 94,
	68, 94, 63, 98,
	63, 98, 64, 104,
	64, 104, 62, 112,
	62, 112, 56, 113,
	56, 113, 54, 116,
	54, 116, 46, 117,
	46, 117, 44, 116,
	44, 116, 44, 110,
	44, 110, 46, 108,
	46, 108, 48, 104,
	48, 104, 48, 101,
	48, 101, 50, 98,
	50, 98, 50, 96,
	50, 96, 38, 96,
	38, 96, 37, 94,
	37, 94, 37, 90,
	37, 90, 25, 78,
	25, 78, 26, 75,
	26, 75, 29, 74,
	29, 74, 30, 70,
	30, 70, 26, 70,
	26, 70, 25, 66,
	25, 66, 22, 65,
	22, 65, 21, 59
};

// 49
int jakartaTimur[] = {
	124, 30, 116, 30,
	116, 30, 114, 32,
	114, 32, 112, 31,
	112, 31, 108, 34,
	108, 34, 104, 34,
	104, 34, 103, 30,
	103, 30, 99, 30,
	99, 30, 101, 33,
	101, 33, 101, 39,
	101, 39, 94, 40,
	94, 40, 82, 35,
	82, 35, 82, 35,
	82, 35, 78, 44,
	78, 44, 76, 44,
	76, 44, 70, 46,
	70, 46, 70, 50,
	70, 50, 74, 58,
	74, 58, 74, 70,
	74, 70, 72, 76,
	72, 76, 67, 82,
	67, 82, 68, 88,
	68, 88, 72, 94,
	72, 94, 68, 98,
	68, 98, 68, 94,
	68, 94, 63, 98,
	63, 98, 64, 104,
	64, 104, 68, 102,
	68, 102, 68, 104,
	68, 104, 74, 112,
	74, 112, 77, 111,
	77, 111, 79, 113,
	79, 113, 77, 116,
	77, 116, 79, 117,
	79, 117, 81, 117,
	81, 117, 85, 120,
	85, 120, 91, 119,
	91, 119, 90, 121,
	90, 121, 93, 121,
	93, 121, 98, 108,
	98, 108, 98, 90,
	98, 90, 95, 88,
	95, 88, 94, 79,
	94, 79, 99, 79,
	99, 79, 99, 70,
	99, 70, 108, 70,
	108, 70, 110, 58,
	110, 58, 120, 52,
	120, 52, 124, 46,
	124, 46, 124, 30
};

// 17
int jakartaPusat[] = {
	46, 52, 50, 44,
	50, 44, 52, 44,
	52, 44, 52, 39,
	52, 39, 48, 32,
	48, 32, 51, 30,
	51, 30, 60, 30,
	60, 30, 58, 24,
	58, 24, 64, 29,
	64, 29, 82, 35,
	82, 35, 78, 44,
	78, 44, 76, 44,
	76, 44, 70, 46,
	70, 46, 70, 50,
	70, 50, 58, 50,
	58, 50, 57, 54,
	57, 54, 46, 61,
	46, 61, 46, 52
};*/


// 3
int triangle[] = {
	0, 0, 0,	6, 0, 0,
	6, 0, 0,	3, 6, 0, 
	3, 6, 0, 	0, 0, 0

	//1, 2, 3,	4, 5, 6,
	//7, 8, 9,	10, 11, 12, 
	//13, 14, 15, 	16, 17, 18
};


int backBody1[] = {
	16, 19, 0,  	20, 12, 0, 
	20, 12, 0,  	12, 12, 0, 
	12, 12, 0,  	16, 19, 0
};

int backBody2[] = {
	20, 12, 0, 		16, 19, 0, 
	16, 19, 0, 		23, 21, 0, 
	23, 21, 0, 		20, 12, 0
};

int backBody3[] = {
	23, 21, 0, 		16, 19, 0, 
	16, 19, 0, 		16, 27, 0, 
	16, 27, 0, 		23, 21, 0
};

int backBody4[] = {
	16, 27, 0, 		16, 19, 0, 
	16, 19, 0, 		9, 21, 0, 
	9, 21, 0, 		16, 27, 0
};

int backBody5[] = {
	9, 21, 0, 		16, 19, 0, 
	16, 19, 0, 		12, 12, 0, 
	12, 12, 0, 		9, 21, 0		
};



int backArm1[] = {
	16, 0, 2,  		20, 12, 0, 
	20, 12, 0,  	12, 12, 0, 
	12, 12, 0,  	16, 0, 2
};

int backArm2[] = {
	20, 12, 0, 		32, 12, 2, 
	32, 12, 2, 		23, 21, 0, 
	23, 21, 0, 		20, 12, 0
};

int backArm3[] = {
	23, 21, 0, 		28, 35, 2, 
	28, 35, 2, 		16, 27, 0, 
	16, 27, 0, 		23, 21, 0
};

int backArm4[] = {
	16, 27, 0, 		4, 35, 2, 
	4, 35, 2, 		9, 21, 0, 
	9, 21, 0, 		16, 27, 0
};

int backArm5[] = {
	9, 21, 0, 		0, 12, 2, 
	0, 12, 2, 		12, 12, 0, 
	12, 12, 0, 		9, 21, 0		
};


int frontBody1[] = {
	16, 19, 4,  	20, 12, 4, 
	20, 12, 4,  	12, 12, 4, 
	12, 12, 4,  	16, 19, 4
};

int frontBody2[] = {
	20, 12, 4, 		16, 19, 4, 
	16, 19, 4, 		23, 21, 4, 
	23, 21, 4, 		20, 12, 4
};

int frontBody3[] = {
	23, 21, 4, 		16, 19, 4, 
	16, 19, 4, 		16, 27, 4, 
	16, 27, 4, 		23, 21, 4
};

int frontBody4[] = {
	16, 27, 4, 		16, 19, 4, 
	16, 19, 4, 		9, 21, 4, 
	9, 21, 4, 		16, 27, 4
};

int frontBody5[] = {
	9, 21, 4, 		16, 19, 4, 
	16, 19, 4, 		12, 12, 4, 
	12, 12, 4, 		9, 21, 4		
};


int frontArm1[] = {
	16, 0, 2,  		20, 12, 4, 
	20, 12, 4,  	12, 12, 4, 
	12, 12, 4,  	16, 0, 2
};

int frontArm2[] = {
	20, 12, 4, 		32, 12, 2, 
	32, 12, 2, 		23, 21, 4, 
	23, 21, 4, 		20, 12, 4
};

int frontArm3[] = {
	23, 21, 4, 		28, 35, 2, 
	28, 35, 2, 		16, 27, 4, 
	16, 27, 4, 		23, 21, 4
};

int frontArm4[] = {
	16, 27, 4, 		4, 35, 2, 
	4, 35, 2, 		9, 21, 4, 
	9, 21, 4, 		16, 27, 4
};

int frontArm5[] = {
	9, 21, 4, 		0, 12, 2, 
	0, 12, 2, 		12, 12, 4, 
	12, 12, 4, 		9, 21, 4		
};


int side1a[] = {
	16, 0, 2,  		20, 12, 0, 
	20, 12, 0,  	20, 12, 4, 
	20, 12, 4,  	16, 0, 2
};

int side2a[] = {
	23, 21, 4, 		32, 12, 2, 
	32, 12, 2, 		23, 21, 0, 
	23, 21, 0, 		23, 21, 4
};

int side3a[] = {
	16, 27, 4, 		28, 35, 2, 
	28, 35, 2, 		16, 27, 0, 
	16, 27, 0, 		16, 27, 4
};

int side4a[] = {
	9, 21, 4, 		4, 35, 2, 
	4, 35, 2, 		9, 21, 0, 
	9, 21, 0, 		9, 21, 4
};

int side5a[] = {
	12, 12, 4, 		0, 12, 2, 
	0, 12, 2, 		12, 12, 0, 
	12, 12, 0, 		12, 12, 4		
};


int side1b[] = {
	12, 12, 4, 		16, 0, 2, 
	16, 0, 2, 		12, 12, 0, 
	12, 12, 0, 		12, 12, 4		
};

int side2b[] = {
	32, 12, 2,  	20, 12, 0, 
	20, 12, 0,  	20, 12, 4, 
	20, 12, 4,  	32, 12, 2
};

int side3b[] = {
	23, 21, 4, 		28, 35, 2, 
	28, 35, 2, 		23, 21, 0, 
	23, 21, 0, 		23, 21, 4
};

int side4b[] = {
	16, 27, 4, 		4, 35, 2, 
	4, 35, 2, 		16, 27, 0, 
	16, 27, 0, 		16, 27, 4
};

int side5b[] = {
	9, 21, 4, 		0, 12, 2, 
	0, 12, 2, 		9, 21, 0, 
	9, 21, 0, 		9, 21, 4
};


int main() {
	printf("start of program\n");

	FrameBuffer FB;

	/*Polygon jakpus(62, 60,jakartaPusat, 68);
	jakpus.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);
	jakpus.setMultiplication(5);
	jakpus.setWireColor(255,0,0);
	jakpus.setFillColor(0, 0, 255);
	jakpus.setDegree(45);

	Polygon jaktim(62, 60,jakartaTimur, 196);
	jaktim.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);
	jaktim.setMultiplication(5);

	Polygon jaksel(62, 60,jakartaSelatan, 164);
	jaksel.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);
	jaksel.setMultiplication(5);

	Polygon jakbar(62, 60,jakartaBarat, 160);
	jakbar.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);
	jakbar.setMultiplication(5);

	Polygon jakut(62, 60,jakartaUtara, 160);
	jakut.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);
	jakut.setMultiplication(5);*/

	Polygon tri(0, 0, 0, triangle, 18);
	tri.setPosition(100,100, 0);
	tri.setMultiplication(10);


	Polygon bb1(0, 0, 0, backBody1, 18);
	bb1.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb1.setMultiplication(10);

	Polygon bb2(0, 0, 0, backBody2, 18);
	bb2.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb2.setMultiplication(10);

	Polygon bb3(0, 0, 0, backBody3, 18);
	bb3.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb3.setMultiplication(10);

	Polygon bb4(0, 0, 0, backBody4, 18);
	bb4.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb4.setMultiplication(10);

	Polygon bb5(0, 0, 0, backBody5, 18);
	bb5.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb5.setMultiplication(10);


	Polygon ba1(0, 0, 0, backArm1, 18);
	ba1.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba1.setMultiplication(10);

	Polygon ba2(0, 0, 0, backArm2, 18);
	ba2.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba2.setMultiplication(10);

	Polygon ba3(0, 0, 0, backArm3, 18);
	ba3.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba3.setMultiplication(10);

	Polygon ba4(0, 0, 0, backArm4, 18);
	ba4.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba4.setMultiplication(10);

	Polygon ba5(0, 0, 0, backArm5, 18);
	ba5.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba5.setMultiplication(10);

	//front body
	Polygon fb1(0, 0, 0, frontBody1, 18);
	fb1.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb1.setMultiplication(10);

	Polygon fb2(0, 0, 0, frontBody2, 18);
	fb2.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb2.setMultiplication(10);

	Polygon fb3(0, 0, 0, frontBody3, 18);
	fb3.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb3.setMultiplication(10);

	Polygon fb4(0, 0, 0, frontBody4, 18);
	fb4.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb4.setMultiplication(10);

	Polygon fb5(0, 0, 0, frontBody5, 18);
	fb5.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb5.setMultiplication(10);


	Polygon fa1(0, 0, 0, frontArm1, 18);
	fa1.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa1.setMultiplication(10);

	Polygon fa2(0, 0, 0, frontArm2, 18);
	fa2.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa2.setMultiplication(10);

	Polygon fa3(0, 0, 0, frontArm3, 18);
	fa3.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa3.setMultiplication(10);

	Polygon fa4(0, 0, 0, frontArm4, 18);
	fa4.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa4.setMultiplication(10);

	Polygon fa5(0, 0, 0, frontArm5, 18);
	fa5.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa5.setMultiplication(10);


	Polygon s1a(0, 0, 0, side1a, 18);
	s1a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s1a.setMultiplication(10);

	Polygon s2a(0, 0, 0, side2a, 18);
	s2a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s2a.setMultiplication(10);

	Polygon s3a(0, 0, 0, side3a, 18);
	s3a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s3a.setMultiplication(10);

	Polygon s4a(0, 0, 0, side4a, 18);
	s4a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s4a.setMultiplication(10);

	Polygon s5a(0, 0, 0, side5a, 18);
	s5a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s5a.setMultiplication(10);	


	Polygon s1b(0, 0, 0, side1b, 18);
	s1b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s1b.setMultiplication(10);

	Polygon s2b(0, 0, 0, side2b, 18);
	s2b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s2b.setMultiplication(10);

	Polygon s3b(0, 0, 0, side3b, 18);
	s3b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s3b.setMultiplication(10);

	Polygon s4b(0, 0, 0, side4b, 18);
	s4b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s4b.setMultiplication(10);

	Polygon s5b(0, 0, 0, side5b, 18);
	s5b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s5b.setMultiplication(10);	

	FB.canvas();

	tri.draw(&FB);

	bb1.draw(&FB);
	bb2.draw(&FB);
	bb3.draw(&FB);
	bb4.draw(&FB);
	bb5.draw(&FB);
	
	ba1.draw(&FB);
	ba2.draw(&FB);
	ba3.draw(&FB);
	ba4.draw(&FB);
	ba5.draw(&FB);

	fb1.draw(&FB);
	fb2.draw(&FB);
	fb3.draw(&FB);
	fb4.draw(&FB);
	fb5.draw(&FB);
	
	fa1.draw(&FB);
	fa2.draw(&FB);
	fa3.draw(&FB);
	fa4.draw(&FB);
	fa5.draw(&FB);

	s1a.draw(&FB);
	s2a.draw(&FB);
	s3a.draw(&FB);
	s4a.draw(&FB);
	s5a.draw(&FB);
	
	s1b.draw(&FB);
	s2b.draw(&FB);
	s3b.draw(&FB);
	s4b.draw(&FB);
	s5b.draw(&FB);

	FB.render();

	//the real deal
	for (int i = 0; i <= 360; i++){
		tri.setDegree(i*1);

		bb1.setDegree(i*1);
		bb2.setDegree(i*1);
		bb3.setDegree(i*1);
		bb4.setDegree(i*1);
		bb5.setDegree(i*1);

		ba1.setDegree(i*1);
		ba2.setDegree(i*1);
		ba3.setDegree(i*1);
		ba4.setDegree(i*1);
		ba5.setDegree(i*1);

		fb1.setDegree(i*1);
		fb2.setDegree(i*1);
		fb3.setDegree(i*1);
		fb4.setDegree(i*1);
		fb5.setDegree(i*1);

		fa1.setDegree(i*1);
		fa2.setDegree(i*1);
		fa3.setDegree(i*1);
		fa4.setDegree(i*1);
		fa5.setDegree(i*1);

		s1a.setDegree(i*1);
		s2a.setDegree(i*1);
		s3a.setDegree(i*1);
		s4a.setDegree(i*1);
		s5a.setDegree(i*1);

		s1b.setDegree(i*1);
		s2b.setDegree(i*1);
		s3b.setDegree(i*1);
		s4b.setDegree(i*1);
		s5b.setDegree(i*1);

		FB.canvas();

		tri.draw(&FB);

		bb1.draw(&FB);
		bb2.draw(&FB);
		bb3.draw(&FB);
		bb4.draw(&FB);
		bb5.draw(&FB);
		
		ba1.draw(&FB);
		ba2.draw(&FB);
		ba3.draw(&FB);
		ba4.draw(&FB);
		ba5.draw(&FB);

		fb1.draw(&FB);
		fb2.draw(&FB);
		fb3.draw(&FB);
		fb4.draw(&FB);
		fb5.draw(&FB);
		
		fa1.draw(&FB);
		fa2.draw(&FB);
		fa3.draw(&FB);
		fa4.draw(&FB);
		fa5.draw(&FB);

		s1a.draw(&FB);
		s2a.draw(&FB);
		s3a.draw(&FB);
		s4a.draw(&FB);
		s5a.draw(&FB);
		
		s1b.draw(&FB);
		s2b.draw(&FB);
		s3b.draw(&FB);
		s4b.draw(&FB);
		s5b.draw(&FB);

		FB.render();
		usleep(10000);
	}

	
	printf("end of program\n");

	return 0;
}