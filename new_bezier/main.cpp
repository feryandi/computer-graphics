#include <iostream>
#include "Polygon.class.h"
#include "FrameBuffer.class.h"
#include "Input.class.h"
using namespace std;

/*
// 3
int triangle[] = {
	0, 0, 0,	6, 0, 0,
	6, 0, 0,	3, 6, 0,
	3, 6, 0, 	0, 0, 0
};


int backBody1[] = {
	16, 19, -1,  	20, 12, 0,
	20, 12, 0,  	12, 12, 0,
	12, 12, 0,  	16, 19, -1
};

int backBody2[] = {
	20, 12, 0, 		16, 19, -1,
	16, 19, -1, 	23, 21, 0,
	23, 21, 0, 		20, 12, 0
};

int backBody3[] = {
	23, 21, 0, 		16, 19, -1,
	16, 19, -1, 	16, 27, 0,
	16, 27, 0, 		23, 21, 0
};

int backBody4[] = {
	16, 27, 0, 		16, 19, -1,
	16, 19, -1, 	9, 21, 0,
	9, 21, 0, 		16, 27, 0
};

int backBody5[] = {
	9, 21, 0, 		16, 19, -1,
	16, 19, -1, 	12, 12, 0,
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
	16, 19, 5,  	20, 12, 4,
	20, 12, 4,  	12, 12, 4,
	12, 12, 4,  	16, 19, 5
};

int frontBody2[] = {
	20, 12, 4, 		16, 19, 5,
	16, 19, 5, 		23, 21, 4,
	23, 21, 4, 		20, 12, 4
};

int frontBody3[] = {
	23, 21, 4, 		16, 19, 5,
	16, 19, 5, 		16, 27, 4,
	16, 27, 4, 		23, 21, 4
};

int frontBody4[] = {
	16, 27, 4, 		16, 19, 5,
	16, 19, 5, 		9, 21, 4,
	9, 21, 4, 		16, 27, 4
};

int frontBody5[] = {
	9, 21, 4, 		16, 19, 5,
	16, 19, 5, 		12, 12, 4,
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
};*/

float three_points[] = {
	10, 10, 10,
	20, 10, 10, 
	20, 20, 10
};

void drawCurveRecursive(float *points, int points_length,  float t, float **picture, int picture_length, int num_filled){
	if(points_length==3){
		//draw(points[0]);
		(*picture)[num_filled*3] = points[0];
		(*picture)[num_filled*3 + 1] = points[1];
		(*picture)[num_filled*3 + 2] = points[2];
		num_filled++;
	}
	else{
		float * newpoints = (float*)malloc((points_length-3)*sizeof(float));
		int newpoints_length = points_length-3;
		for (int i = 0; i < newpoints_length; i+=3){
			float x = (1-t) * points[i] + t * points[i+3];
			float y = (1-t) * points[i+1] + t * points[i+4];
			float z = (1-t) * points[i+2] + t * points[i+5];
			newpoints[i] = x;
			newpoints[i+1] = y;
			newpoints[i+2] = z;
		}
		drawCurveRecursive(newpoints, newpoints_length, t, &(*picture), picture_length ,num_filled);
	}
}

void drawCurve(float *points, int points_length, float nt, float **picture){
	float * simpler_picture = (float*)malloc((nt + 1) * 3 * sizeof(float));
	int simpler_picture_length = (nt + 1) * 3;
	simpler_picture[0] = points[0]; //printf("simpler_picture[%d]: %f\n", 0, simpler_picture[0]);
	simpler_picture[1] = points[1]; //printf("simpler_picture[%d]: %f\n", 1, simpler_picture[1]);
	simpler_picture[2] = points[2]; //printf("simpler_picture[%d]: %f\n", 2, simpler_picture[2]);

	simpler_picture[simpler_picture_length-3] = points[points_length-3]; //printf("simpler_picture[%d]: %f\n", simpler_picture_length-3, simpler_picture[simpler_picture_length-3]);
	simpler_picture[simpler_picture_length-2] = points[points_length-2]; //printf("simpler_picture[%d]: %f\n", simpler_picture_length-2, simpler_picture[simpler_picture_length-2]);
	simpler_picture[simpler_picture_length-1] = points[points_length-1]; //printf("simpler_picture[%d]: %f\n", simpler_picture_length-1, simpler_picture[simpler_picture_length-1]);
	for(int i = 1; i < nt; i++){
		drawCurveRecursive(points, points_length, (1/nt)*i, &simpler_picture, simpler_picture_length, i);	
	}
	
	(* picture) = (float*)malloc(((simpler_picture_length-3) * 2)*sizeof(float)); 

	int picture_length = (simpler_picture_length-3) * 2;
	printf("picture_length: %d", picture_length);

	// titik pertama di awal
	(*picture)[0] = simpler_picture[0]; //printf("(*picture)[%d]: %f\n", 0, simpler_picture[0]);
	(*picture)[1] = simpler_picture[1]; //printf("(*picture)[%d]: %f\n", 1, simpler_picture[1]);
	(*picture)[2] = simpler_picture[2]; //printf("(*picture)[%d]: %f\n", 2, simpler_picture[2]);
	// titik pertama di akhir --> jadinya ga ada
	/*(*picture)[picture_length - 3] = simpler_picture[0]; //printf("(*picture)[%d]: %f\n", picture_length - 3, simpler_picture[0]);
	(*picture)[picture_length - 2] = simpler_picture[1]; //printf("(*picture)[%d]: %f\n", picture_length - 2, simpler_picture[1]);
	(*picture)[picture_length - 1] = simpler_picture[2]; //printf("(*picture)[%d]: %f\n", picture_length - 1, simpler_picture[2]);*/
	//titik di antaranya kalo ada
	if(picture_length > 6){
		int j=3;
		for(int i = 3; i < simpler_picture_length-3; i+=3){
			(*picture)[j] = simpler_picture[i]; //printf("(*picture)[%d]: %f\n", j, simpler_picture[i]);
			(*picture)[j+1] = simpler_picture[i+1]; //printf("(*picture)[%d]: %f\n", j+1, simpler_picture[i+1]);
			(*picture)[j+2] = simpler_picture[i+2]; //printf("(*picture)[%d]: %f\n", j+2, simpler_picture[i+2]);
			(*picture)[j+3] = simpler_picture[i]; //printf("(*picture)[%d]: %f\n", j+3, simpler_picture[i]);
			(*picture)[j+4] = simpler_picture[i+1]; //printf("(*picture)[%d]: %f\n", j+4, simpler_picture[i+1]);
			(*picture)[j+5] = simpler_picture[i+2]; //printf("(*picture)[%d]: %f\n", j+5, simpler_picture[i+2]);
			j+=6;
		}
	}
	(*picture)[picture_length - 3] = simpler_picture[simpler_picture_length - 3]; //printf("(*picture)[%d]: %f\n", picture_length - 3, simpler_picture[0]);
	(*picture)[picture_length - 2] = simpler_picture[simpler_picture_length - 2]; //printf("(*picture)[%d]: %f\n", picture_length - 2, simpler_picture[1]);
	(*picture)[picture_length - 1] = simpler_picture[simpler_picture_length - 1]; //printf("(*picture)[%d]: %f\n", picture_length - 1, simpler_picture[2]);


	printf("simpler_picture\n");
	for (int i = 0; i < 33; i+=3){
		printf("%f ", simpler_picture[i]);
		printf("%f ", simpler_picture[i+1]);
		printf("%f ", simpler_picture[i+2]);
		printf("\n");
	}
	printf("\n");

}

int main() {
	printf("start of program\n");

	FrameBuffer FB;
	FB.initAvailable();

	float* picture;
	float t = 10;
	drawCurve(three_points, 9, t, &picture);
	printf("three_points\n");
	for (int i = 0; i < 9; i+=3){
		printf("%f ", three_points[i]);
		printf("%f ", three_points[i+1]);
		printf("%f ", three_points[i+2]);
		printf("\n");
	}
	printf("\n");

	printf("picture\n");
	for (int i = 0; i < 60; i+=6){
		printf("%f ", picture[i]);
		printf("%f ", picture[i+1]);
		printf("%f    ", picture[i+2]);
		printf("%f ", picture[i+3]);
		printf("%f ", picture[i+4]);
		printf("%f ", picture[i+5]);
		printf("\n");
	}
	printf("\n");

	//float to int he he he amfun bismillah
	int * integer_picture = (int*)malloc(60*sizeof(int));
	for(int i = 0; i < 60; i++){
		integer_picture[i] = (int) (picture[i]*20);
	}
	printf("integer_picture\n");
	for (int i = 0; i < 60; i+=6){
		printf("%d ", integer_picture[i]);
		printf("%d ", integer_picture[i+1]);
		printf("%d    ", integer_picture[i+2]);
		printf("%d ", integer_picture[i+3]);
		printf("%d ", integer_picture[i+4]);
		printf("%d ", integer_picture[i+5]);
		printf("\n");	
	}
	printf("\n");

	Polygon tp(0, 0, 0, integer_picture, 60);
	tp.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	tp.setMultiplication(1);
	tp.setCenter(15, 15, 10);
	tp.setFillColor(135, 206, 250);

	static Polygon* arrStar[] = {
		&tp
	};
	vector<Polygon*> star(arrStar, arrStar + sizeof(arrStar) / sizeof(arrStar[0]) );

	FB.canvas();

	FB.draw(star);

	FB.render();


	/*Polygon bb1(0, 0, 0, backBody1, 18);
	bb1.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb1.setMultiplication(10);
	bb1.setCenter(16, 16, 2);
	bb1.setFillColor(135, 206, 250);

	Polygon bb2(0, 0, 0, backBody2, 18);
	bb2.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb2.setMultiplication(10);
	bb2.setCenter(16, 16, 2);
	bb2.setFillColor(135, 206, 250);

	Polygon bb3(0, 0, 0, backBody3, 18);
	bb3.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb3.setMultiplication(10);
	bb3.setCenter(16, 16, 2);
	bb3.setFillColor(135, 206, 250);

	Polygon bb4(0, 0, 0, backBody4, 18);
	bb4.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb4.setMultiplication(10);
	bb4.setCenter(16, 16, 2);
	bb4.setFillColor(135, 206, 250);

	Polygon bb5(0, 0, 0, backBody5, 18);
	bb5.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	bb5.setMultiplication(10);
	bb5.setCenter(16, 16, 2);
	bb5.setFillColor(135, 206, 250);


	Polygon ba1(0, 0, 0, backArm1, 18);
	ba1.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba1.setMultiplication(10);
	ba1.setCenter(16, 16, 2);
	ba1.setFillColor(135, 206, 250);

	Polygon ba2(0, 0, 0, backArm2, 18);
	ba2.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba2.setMultiplication(10);
	ba2.setCenter(16, 16, 2);
	ba2.setFillColor(135, 206, 250);

	Polygon ba3(0, 0, 0, backArm3, 18);
	ba3.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba3.setMultiplication(10);
	ba3.setCenter(16, 16, 2);
	ba3.setFillColor(135, 206, 250);

	Polygon ba4(0, 0, 0, backArm4, 18);
	ba4.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba4.setMultiplication(10);
	ba4.setCenter(16, 16, 2);
	ba4.setFillColor(135, 206, 250);

	Polygon ba5(0, 0, 0, backArm5, 18);
	ba5.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	ba5.setMultiplication(10);
	ba5.setCenter(16, 16, 2);
	ba5.setFillColor(135, 206, 250);

	//front body
	Polygon fb1(0, 0, 0, frontBody1, 18);
	fb1.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb1.setMultiplication(10);
	fb1.setCenter(16, 16, 2);
	fb1.setFillColor(255, 215, 0);

	Polygon fb2(0, 0, 0, frontBody2, 18);
	fb2.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb2.setMultiplication(10);
	fb2.setCenter(16, 16, 2);
	fb2.setFillColor(255, 215, 0);

	Polygon fb3(0, 0, 0, frontBody3, 18);
	fb3.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb3.setMultiplication(10);
	fb3.setCenter(16, 16, 2);
	fb3.setFillColor(255, 215, 0);

	Polygon fb4(0, 0, 0, frontBody4, 18);
	fb4.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb4.setMultiplication(10);
	fb4.setCenter(16, 16, 2);
	fb4.setFillColor(255, 215, 0);

	Polygon fb5(0, 0, 0, frontBody5, 18);
	fb5.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fb5.setMultiplication(10);
	fb5.setCenter(16, 16, 2);
	fb5.setFillColor(255, 215, 0);


	Polygon fa1(0, 0, 0, frontArm1, 18);
	fa1.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa1.setMultiplication(10);
	fa1.setCenter(16, 16, 2);
	fa1.setFillColor(255, 215, 0);

	Polygon fa2(0, 0, 0, frontArm2, 18);
	fa2.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa2.setMultiplication(10);
	fa2.setCenter(16, 16, 2);
	fa2.setFillColor(255, 215, 0);

	Polygon fa3(0, 0, 0, frontArm3, 18);
	fa3.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa3.setMultiplication(10);
	fa3.setCenter(16, 16, 2);
	fa3.setFillColor(255, 215, 0);

	Polygon fa4(0, 0, 0, frontArm4, 18);
	fa4.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa4.setMultiplication(10);
	fa4.setCenter(16, 16, 2);
	fa4.setFillColor(255, 215, 0);

	Polygon fa5(0, 0, 0, frontArm5, 18);
	fa5.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	fa5.setMultiplication(10);
	fa5.setCenter(16, 16, 2);
	fa5.setFillColor(255, 215, 0);


	Polygon s1a(0, 0, 0, side1a, 18);
	s1a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s1a.setMultiplication(10);
	s1a.setCenter(16, 16, 2);
	s1a.setFillColor(192,192,192);

	Polygon s2a(0, 0, 0, side2a, 18);
	s2a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s2a.setMultiplication(10);
	s2a.setCenter(16, 16, 2);
	s2a.setFillColor(192,192,192);

	Polygon s3a(0, 0, 0, side3a, 18);
	s3a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s3a.setMultiplication(10);
	s3a.setCenter(16, 16, 2);
	s3a.setFillColor(192,192,192);

	Polygon s4a(0, 0, 0, side4a, 18);
	s4a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s4a.setMultiplication(10);
	s4a.setCenter(16, 16, 2);
	s4a.setFillColor(192,192,192);

	Polygon s5a(0, 0, 0, side5a, 18);
	s5a.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s5a.setMultiplication(10);
	s5a.setCenter(16, 16, 2);
	s5a.setFillColor(192,192,192);


	Polygon s1b(0, 0, 0, side1b, 18);
	s1b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s1b.setMultiplication(10);
	s1b.setCenter(16, 16, 2);
	s1b.setFillColor(192,192,192);

	Polygon s2b(0, 0, 0, side2b, 18);
	s2b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s2b.setMultiplication(10);
	s2b.setCenter(16, 16, 2);
	s2b.setFillColor(192,192,192);

	Polygon s3b(0, 0, 0, side3b, 18);
	s3b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s3b.setMultiplication(10);
	s3b.setCenter(16, 16, 2);
	s3b.setFillColor(192,192,192);

	Polygon s4b(0, 0, 0, side4b, 18);
	s4b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s4b.setMultiplication(10);
	s4b.setCenter(16, 16, 2);
	s4b.setFillColor(192,192,192);

	Polygon s5b(0, 0, 0, side5b, 18);
	s5b.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	s5b.setMultiplication(10);
	s5b.setCenter(16, 16, 2);
	s5b.setFillColor(192,192,192);

	static Polygon* arrStar[] = {
			&bb1, &bb2, &bb3, &bb4, &bb5,
			&ba1, &ba2, &ba3, &ba4, &ba5,
			&fb1, &fb2, &fb3, &fb4, &fb5,
			&fa1, &fa2, &fa3, &fa4, &fa5,
			&s1a, &s2a, &s3a, &s4a, &s5a,
			&s1b, &s2b, &s3b, &s4b, &s5b
		};
	vector<Polygon*> star(arrStar, arrStar + sizeof(arrStar) / sizeof(arrStar[0]) );

	FB.canvas();

	FB.draw(star);

	FB.render();

	// Manual Control
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
					//the real deal*/
					/*for (int i = 0; i <= 360; i++){
						float n = 1;
						tri.setDegree(n*1, 1);

						bb1.setDegree(n*i, 1);
						bb2.setDegree(n*i, 1);
						bb3.setDegree(n*i, 1);
						bb4.setDegree(n*i, 1);
						bb5.setDegree(n*i, 1);

						ba1.setDegree(n*i, 1);
						ba2.setDegree(n*i, 1);
						ba3.setDegree(n*i, 1);
						ba4.setDegree(n*i, 1);
						ba5.setDegree(n*i, 1);

						fb1.setDegree(n*i, 1);
						fb2.setDegree(n*i, 1);
						fb3.setDegree(n*i, 1);
						fb4.setDegree(n*i, 1);
						fb5.setDegree(n*i, 1);

						fa1.setDegree(n*i, 1);
						fa2.setDegree(n*i, 1);
						fa3.setDegree(n*i, 1);
						fa4.setDegree(n*i, 1);
						fa5.setDegree(n*i, 1);

						s1a.setDegree(n*i, 1);
						s2a.setDegree(n*i, 1);
						s3a.setDegree(n*i, 1);
						s4a.setDegree(n*i, 1);
						s5a.setDegree(n*i, 1);

						s1b.setDegree(n*i, 1);
						s2b.setDegree(n*i, 1);
						s3b.setDegree(n*i, 1);
						s4b.setDegree(n*i, 1);
						s5b.setDegree(n*i, 1);

						FB.canvas();

						FB.draw(star);

						FB.render();
						usleep(100);
					}

					for (int i = 0; i <= 360; i++){
						int n = 1;
						tri.setDegree(i*n, 0);

						bb1.setDegree(i*n, 0);
						bb2.setDegree(i*n, 0);
						bb3.setDegree(i*n, 0);
						bb4.setDegree(i*n, 0);
						bb5.setDegree(i*n, 0);

						ba1.setDegree(i*n, 0);
						ba2.setDegree(i*n, 0);
						ba3.setDegree(i*n, 0);
						ba4.setDegree(i*n, 0);
						ba5.setDegree(i*n, 0);

						fb1.setDegree(i*n, 0);
						fb2.setDegree(i*n, 0);
						fb3.setDegree(i*n, 0);
						fb4.setDegree(i*n, 0);
						fb5.setDegree(i*n, 0);

						fa1.setDegree(i*n, 0);
						fa2.setDegree(i*n, 0);
						fa3.setDegree(i*n, 0);
						fa4.setDegree(i*n, 0);
						fa5.setDegree(i*n, 0);

						s1a.setDegree(i*n, 0);
						s2a.setDegree(i*n, 0);
						s3a.setDegree(i*n, 0);
						s4a.setDegree(i*n, 0);
						s5a.setDegree(i*n, 0);

						s1b.setDegree(i*n, 0);
						s2b.setDegree(i*n, 0);
						s3b.setDegree(i*n, 0);
						s4b.setDegree(i*n, 0);
						s5b.setDegree(i*n, 0);

						FB.canvas();

						FB.draw(star);

						FB.render();
						usleep(100);
					}

					for (int i = 0; i <= 360; i++){
						tri.setDegree(i*1, 2);

						bb1.setDegree(i*1, 2);
						bb2.setDegree(i*1, 2);
						bb3.setDegree(i*1, 2);
						bb4.setDegree(i*1, 2);
						bb5.setDegree(i*1, 2);

						ba1.setDegree(i*1, 2);
						ba2.setDegree(i*1, 2);
						ba3.setDegree(i*1, 2);
						ba4.setDegree(i*1, 2);
						ba5.setDegree(i*1, 2);

						fb1.setDegree(i*1, 2);
						fb2.setDegree(i*1, 2);
						fb3.setDegree(i*1, 2);
						fb4.setDegree(i*1, 2);
						fb5.setDegree(i*1, 2);

						fa1.setDegree(i*1, 2);
						fa2.setDegree(i*1, 2);
						fa3.setDegree(i*1, 2);
						fa4.setDegree(i*1, 2);
						fa5.setDegree(i*1, 2);

						s1a.setDegree(i*1, 2);
						s2a.setDegree(i*1, 2);
						s3a.setDegree(i*1, 2);
						s4a.setDegree(i*1, 2);
						s5a.setDegree(i*1, 2);

						s1b.setDegree(i*1, 2);
						s2b.setDegree(i*1, 2);
						s3b.setDegree(i*1, 2);
						s4b.setDegree(i*1, 2);
						s5b.setDegree(i*1, 2);

						FB.canvas();

						FB.draw(star);

						FB.render();
						usleep(100);
					}

					printf("End of program\n");
					exit(0);*/ /*
				}
			}

			bb1.setDegree(n*rotation, axis);
			bb2.setDegree(n*rotation, axis);
			bb3.setDegree(n*rotation, axis);
			bb4.setDegree(n*rotation, axis);
			bb5.setDegree(n*rotation, axis);

			ba1.setDegree(n*rotation, axis);
			ba2.setDegree(n*rotation, axis);
			ba3.setDegree(n*rotation, axis);
			ba4.setDegree(n*rotation, axis);
			ba5.setDegree(n*rotation, axis);

			fb1.setDegree(n*rotation, axis);
			fb2.setDegree(n*rotation, axis);
			fb3.setDegree(n*rotation, axis);
			fb4.setDegree(n*rotation, axis);
			fb5.setDegree(n*rotation, axis);

			fa1.setDegree(n*rotation, axis);
			fa2.setDegree(n*rotation, axis);
			fa3.setDegree(n*rotation, axis);
			fa4.setDegree(n*rotation, axis);
			fa5.setDegree(n*rotation, axis);

			s1a.setDegree(n*rotation, axis);
			s2a.setDegree(n*rotation, axis);
			s3a.setDegree(n*rotation, axis);
			s4a.setDegree(n*rotation, axis);
			s5a.setDegree(n*rotation, axis);

			s1b.setDegree(n*rotation, axis);
			s2b.setDegree(n*rotation, axis);
			s3b.setDegree(n*rotation, axis);
			s4b.setDegree(n*rotation, axis);
			s5b.setDegree(n*rotation, axis);

			FB.canvas();
			FB.draw(star);
			FB.render();
		}
	}*/




	return 0;
}

//void pointsForBresenham(float )



