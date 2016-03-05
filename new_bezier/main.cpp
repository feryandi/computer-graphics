#include <iostream>
#include "Polygon.class.h"
#include "FrameBuffer.class.h"
#include "Input.class.h"
using namespace std;

int head[] = {
	2, 0, 0, 8, 0, 0,
	8, 0, 0, 9, 2, 0,
	9, 2, 0, 10, 1, 0,
	10, 1, 0, 9, 5, 0,
	9, 5, 0, 9, 7, 0,
	9, 7, 0, 8, 10, 0,
	8, 10, 0, 2, 10, 0,
	2, 10, 0, 1, 7, 0,
	1, 7, 0, 1, 5, 0,
	1, 5, 0, 0, 1, 0,
	0, 1, 0, 1, 2, 0,
	1, 2, 0, 2, 0, 0
};

int RightEyeTimid[] = {
	6, 2, 0, 8, 3, 0,
	8, 3, 0, 8, 4, 0,
	8, 4, 0, 6, 4, 0,
	6, 4, 0, 6, 2, 0
};

int LeftEyeTimid[] = {
	2, 3, 0, 4, 2, 0,
	4, 2, 0, 4, 4, 0,
	4, 4, 0, 2, 4, 0,
	2, 4, 0, 2, 3, 0
};

int RightEyeConfidence[] = {
	6, 3, 0, 8, 2, 0,
	8, 2, 0, 8, 4, 0,
	8, 4, 0, 6, 4, 0,
	6, 4, 0, 6, 3, 0
};

int LeftEyeConfidence[] = {
	2, 2, 0, 4, 3, 0,
	4, 3, 0, 4, 4, 0,
	4, 4, 0, 2, 4, 0,
	2, 4, 0, 2, 2, 0
};

float CPMouthSmileUp[] = {
	2, 6, 0,
	5, 8, 0,
	8, 6, 0
};

float CPMouthSmileDown[] = {
	2, 6, 0,
	5, 9, 0,
	8, 6, 0
};

float CPRightEyes[] = {
	6, 4, 0,
	6, 2, 0,
	8, 4, 0
};

float CPMouthSadUp[] = {
	2, 9, 0,
	5, 6, 0,
	8, 9, 0
};

float CPMouthSadDown[] = {
	2, 9, 0,
	5, 7, 0,
	8, 9, 0
};

float CPMouthGaspUp[] = {
	2, 8, 0,
	5, 5, 0,
	8, 8, 0
};

float CPMouthGaspDown[] = {
	2, 8, 0,
	5, 10, 0,
	8, 8, 0
};

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
	simpler_picture[0] = points[0]; 
	simpler_picture[1] = points[1]; 
	simpler_picture[2] = points[2]; 

	simpler_picture[simpler_picture_length-3] = points[points_length-3]; 
	simpler_picture[simpler_picture_length-2] = points[points_length-2]; 
	simpler_picture[simpler_picture_length-1] = points[points_length-1]; 
	for(int i = 1; i < nt; i++){
		drawCurveRecursive(points, points_length, (1/nt)*i, &simpler_picture, simpler_picture_length, i);	
	}
	
	(* picture) = (float*)malloc(((simpler_picture_length-3) * 2)*sizeof(float)); 

	int picture_length = (simpler_picture_length-3) * 2;
	printf("picture_length: %d", picture_length);

	// titik pertama di awal
	(*picture)[0] = simpler_picture[0];
	(*picture)[1] = simpler_picture[1];
	(*picture)[2] = simpler_picture[2];

	//titik di antaranya kalo ada
	if(picture_length > 6){
		int j=3;
		for(int i = 3; i < simpler_picture_length-3; i+=3){
			(*picture)[j] = simpler_picture[i]; 
			(*picture)[j+1] = simpler_picture[i+1];
			(*picture)[j+2] = simpler_picture[i+2];
			(*picture)[j+3] = simpler_picture[i];
			(*picture)[j+4] = simpler_picture[i+1];
			(*picture)[j+5] = simpler_picture[i+2];
			j+=6;
		}
	}
	(*picture)[picture_length - 3] = simpler_picture[simpler_picture_length - 3];
	(*picture)[picture_length - 2] = simpler_picture[simpler_picture_length - 2];
	(*picture)[picture_length - 1] = simpler_picture[simpler_picture_length - 1];

}

int main() {
	printf("start of program\n");

	FrameBuffer FB;
	FB.initAvailable();

	float* picture;
	float t = 10;
	drawCurve(CPMouthSmileDown, 9, t, &picture);
	

	//float to int he he he amfun bismillah
	int * integer_picture = (int*)malloc(60*sizeof(int));
	for(int i = 0; i < 60; i++){
		integer_picture[i] = (int) (picture[i]*20);
	}
	

	Polygon tp(0, 0, 0, integer_picture, 60);
	tp.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	tp.setMultiplication(1);
	tp.setCenter(15, 15, 10);
	tp.setFillColor(135, 206, 250);

	Polygon headz(0,0,0, head, 72);
	headz.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	headz.setMultiplication(20);
	headz.setCenter(0, 0, 0);
	headz.setFillColor(135, 206, 250);

	Polygon rightEyeConfidence(0,0,0, RightEyeConfidence, 24);
	rightEyeConfidence.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	rightEyeConfidence.setMultiplication(20);
	rightEyeConfidence.setCenter(0, 0, 0);
	rightEyeConfidence.setFillColor(135, 206, 250);

	Polygon leftEyeConfidence(0,0,0, LeftEyeConfidence, 24);
	leftEyeConfidence.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2, 0);
	leftEyeConfidence.setMultiplication(20);
	leftEyeConfidence.setCenter(0, 0, 0);
	leftEyeConfidence.setFillColor(135, 206, 250);




	static Polygon* arrStar[] = {
		&tp, &headz, &rightEyeConfidence, &leftEyeConfidence
	};
	vector<Polygon*> star(arrStar, arrStar + sizeof(arrStar) / sizeof(arrStar[0]) );

	FB.canvas();

	FB.draw(star);

	FB.render();




	return 0;
}

//void pointsForBresenham(float )



