#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <termios.h>
#include <time.h>
#include "polygon.class.h"
#include "transformation.h"
#include "frameBuffer.class.h"
#include <iostream>
using namespace std;

int leftWing[] = {
				0, 24, 1, 22,
				1, 22, 4, 20,
				4, 20, 12, 18,
				12, 18, 20, 17,
				20, 17, 24, 17,
				24, 17, 31, 18,
				31, 18, 30, 24,
				30, 24, 31, 30,
				31, 30, 24, 31,
				24, 31, 20, 31,
				20, 31, 12, 30,
				12, 30, 4, 28,
				4, 28, 1, 26,
				1, 26, 0, 24};

int rightWing[] = {
				45, 18, 48, 17,
				48, 17, 52, 17,
				52, 17, 60, 18,
				60, 18, 68, 20,
				68, 20, 71, 22,
				71, 22, 72, 24,
				72, 24, 71, 26,
				71, 26, 68, 28,
				68, 28, 60, 30,
				60, 30, 52, 31,
				52, 31, 48, 31,
				48, 31, 45, 30,
				45, 30, 46, 24,
				46, 24, 45, 18
};

//harus digambar terakhir
int frontBody[] = {
				38, 18, 42, 20,
				42, 20, 44, 24,
				44, 24, 42, 28,
				42, 28, 38, 30,
				38, 30, 34, 28,
				34, 28, 32, 24,
				32, 24, 34, 20,
				34, 20, 38, 18
};

//harus digambar sebelum frontBody
int secondFrontBody[] = {
				38, 16, 42, 17,
				42, 17, 45, 20,
				45, 20, 46, 24,
				46, 24, 45, 28,
				45, 28, 42, 31,
				42, 31, 38, 32,
				38, 32, 34, 31,
				34, 31, 31, 28,
				31, 28, 30, 24,
				30, 24, 31, 20,
				31, 20, 34, 17,
				34, 17, 38, 16
};

//harus digambar sebelum second front body
int body[] = {
				30, 24, 31, 18,
				31, 18, 32, 16,
				32, 16, 34, 13,
				34, 13, 36, 12,
				36, 12, 40, 12,
				40, 12, 42, 13,
				42, 13, 44, 16,
				44, 16, 45, 18,
				45, 18, 46, 24,
				46, 24, 45, 30,
				45, 30, 44, 34,
				44, 34, 46, 38,
				46, 38, 44, 39,
				44, 39, 42, 35,
				42, 35, 34, 35,
				34, 35, 32, 39,
				32, 39, 30, 38,
				30, 38, 32, 34,
				32, 34, 31, 30,
				31, 30, 30, 24
};

int leftTyre[] = {
				30, 38, 32, 39,
				32, 39, 32, 41,
				32, 41, 30, 45,
				30, 45, 28, 46,
				28, 46, 26, 45,
				26, 45, 26, 43,
				26, 43, 28, 39,
				28, 39, 30, 38
};

int rightTyre[] = {
				46, 38, 48, 39,
				48, 39, 50, 43,
				50, 43, 50, 45,
				50, 45, 48, 46,
				48, 46, 46, 45,
				46, 45, 44, 41,
				44, 41, 44, 39,
				44, 39, 46, 38
};

int tail[] = {
				26, 14, 36, 14,
				36, 14, 37, 2,
				37, 2, 38, 1,
				38, 1, 39, 2,
				39, 2, 40, 14,
				40, 14, 50, 14,
				50, 14, 48, 16,
				48, 16, 28, 16,
				28, 16, 26,  14
};


// Paling akhir
int propeller[] = {
				12, 0, 37, 12,
				37, 12, 37, 25,
				37, 25, 50, 38,
				50, 38, 62, 50,
				62, 50, 37, 38,
				37, 38, 37, 25,
				37, 25, 12, 0
};

//22
int parachute1[]{
	0, 46, 1, 36, 
	1, 36, 3, 28, 
	3, 28, 5, 22, 
	5, 22, 7,  18,
	7, 18, 10, 14,
	10, 14, 14, 10, 
	14, 10, 18, 6, 
	18, 6, 22, 4, 
	22, 4, 28, 2, 
	28, 2, 35, 1, 
	35, 1, 36, 1,
	36, 1, 34, 2, 
	34, 2, 30, 5, 
	30, 5, 24, 10,
	24, 10, 20, 16, 
	20, 16, 16, 24, 
	16, 24, 14, 30, 
	14, 30, 12, 38, 
	12, 38, 11, 50,
	11, 50, 6, 47, 
	6, 47, 2, 46, 
	2, 46, 0, 46
};

//17
int parachute2[]{
	36, 1, 34, 2, 
	34, 2, 30, 5, 
	30, 5, 24, 10,
	24, 10, 20, 16, 
	20, 16, 16, 24, 
	16, 24, 14, 30, 
	14, 30, 12, 38, 
	12, 38, 11, 50,
	11, 50, 14, 50, 
	14, 50, 20, 52, 
	20, 52, 26, 56,
	26, 56, 26, 42, 
	26, 42, 27, 34, 
	27, 34, 28, 26, 
	28, 26, 30, 18,
	30, 18, 32, 12, 
	32, 12, 36, 1
	

};

//17
int parachute3[]{
	26, 56, 26, 42, 
	26, 42, 27, 34, 
	27, 34, 28, 26, 
	28, 26, 30, 18,
	30, 18, 32, 12, 
	32, 12, 36, 1,
	36, 1, 40, 12, 
	40, 12, 42, 18,
	42, 18, 44, 26, 
	44, 26, 45, 34, 
	45, 34, 46, 42,
	46, 42, 46, 56,
	46, 56, 42, 55, 
	42, 55, 37, 54, 
	37, 54, 35, 54,
	35, 54, 30, 55, 
	30, 55, 26, 56
};


//17
int parachute4[]{
	36, 1, 40, 12, 
	40, 12, 42, 18,
	42, 18, 44, 26, 
	44, 26, 45, 34, 
	45, 34, 46, 42,
	46, 42, 46, 56,
	46, 56, 52, 52, 
	52, 52, 58, 50, 
	58, 50, 61, 50,
	61, 50, 60, 38, 
	60, 38, 58, 30, 
	58, 30, 56, 24, 
	56, 24, 52, 16, 
	52, 16, 48, 10, 
	48, 10, 42, 5, 
	42, 5, 38, 2, 
	38, 2, 36, 1
	
};

//22
int parachute5[]{
	61, 50, 60, 38, 
	60, 38, 58, 30, 
	58, 30, 56, 24, 
	56, 24, 52, 16, 
	52, 16, 48, 10, 
	48, 10, 42, 5, 
	42, 5, 38, 2, 
	38, 2, 36, 1,
	36, 1, 37, 1, 
	37, 1, 44, 2, 
	44, 2, 49, 4, 
	49, 4, 53, 6, 
	53, 6, 58, 10, 
	58, 10, 62, 14, 
	62, 14, 65, 18,
	65, 18, 67, 22, 
	67, 22, 69, 28, 
	69, 28, 71, 36, 
	71, 36, 72, 46,
	72, 46, 70, 46, 
	70, 46, 66, 47,
	66, 47, 61, 50	
};

//5
int parachuteString1[]{
	11, 50, 6, 47, 
	6, 47, 2, 46, 
	2, 46, 0, 46,
	0, 46, 36, 120,
	36, 120, 11, 50
};


//5
int parachuteString2[]{
	
	61, 50, 36, 120,
	11, 50, 14, 50, 
	14, 50, 20, 52, 
	20, 52, 26, 56,	
	26, 56, 36, 120
};

//5
int parachuteString3[]{
	46, 56, 42, 55, 
	42, 55, 37, 54, 
	37, 54, 35, 54,
	35, 54, 30, 55, 
	30, 55, 26, 56,
	26, 56, 36, 120,
	36, 120, 46, 56		
};


//5
int parachuteString4[]{
	61, 50, 36, 120,
	36, 120, 46, 56,
	46, 56, 52, 52, 
	52, 52, 58, 50, 
	58, 50, 61, 50
};

//5
int parachuteString5[]{
	72, 46, 70, 46, 
	70, 46, 66, 47,
	66, 47, 61, 50,
	61, 50, 36, 120,
	36, 120, 72, 46	
};

int rightPropeller[] = {
	38, 24, 52, 20, 
	52, 20, 52, 24, 
	52, 24, 38, 24
};

int leftPropeller[] = {
	38, 24, 24, 24, 
	24, 24, 24, 28, 
	24, 28, 38, 24
};



int degree = 0;
polygon p1,p2,p3,p4,p5,p6,p7,p8,p9, p10, p11, p12, p13, p14, p15, p16, p17, p18;

void drawPlane(int positionX, int positionY, float multiply, frameBuffer *f) {

	p1.setMultiplication(multiply);
	p1.setCenterX(38);
	p1.setCenterY(24);
	p1.setPolyline(leftWing, 14);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(2, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setCenterX(38);
	p2.setCenterY(24);
	p2.setPolyline(rightWing, 14);
	p2.setPosition(positionX, positionY);
	p2.setFloodPosition(2, 2);
	p2.draw(f);

	p3.setMultiplication(multiply);
	p3.setCenterX(38);
	p3.setCenterY(24);
	p3.setPolyline(leftTyre, 8);
	p3.setPosition(positionX,positionY);
	p3.setFloodPosition(2, 2);
	p3.draw(f);

	p4.setMultiplication(multiply);
	p4.setCenterX(38);
	p4.setCenterY(24);
	p4.setPolyline(rightTyre, 8);
	p4.setPosition(positionX,positionY);
	p4.setFloodPosition(2, 2);
	p4.draw(f);

	p5.setMultiplication(multiply);
	p5.setCenterX(38);
	p5.setCenterY(24);
	p5.setPolyline(tail, 9);
	p5.setPosition(positionX,positionY);
	p5.setFloodPosition(2, 2);
	p5.draw(f);

	p6.setMultiplication(multiply);
	p6.setCenterX(38);
	p6.setCenterY(24);
	p6.setPolyline(body, 20);
	p6.setPosition(positionX,positionY);
	p6.setFloodPosition(2, 2);
	p6.draw(f);

	p7.setMultiplication(multiply);
	p7.setCenterX(38);
	p7.setCenterY(24);
	p7.setPolyline(secondFrontBody, 12);
	p7.setPosition(positionX,positionY);
	p7.setFloodPosition(2, 2);
	p7.draw(f);

	p8.setMultiplication(multiply);
	p8.setCenterX(38);
	p8.setCenterY(24);
	p8.setPolyline(frontBody, 8);
	p8.setPosition(positionX,positionY);
	p8.setFloodPosition(2, 2);
	p8.draw(f);

}

void drawParachute(int positionX, int positionY, float multiply, frameBuffer *f) {
	polygon p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;

	p1.setMultiplication(multiply);
	p1.setCenterX(26);
	p1.setCenterY(20);
	p1.setPolyline(parachute1, 22);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(2, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setCenterX(26);
	p2.setCenterY(20);
	p2.setPolyline(parachute2, 17);
	p2.setPosition(positionX,positionY);
	p2.setFloodPosition(2, 2);
	p2.draw(f);

	p3.setMultiplication(multiply);
	p3.setCenterX(26);
	p3.setCenterY(20);
	p3.setPolyline(parachute3, 17);
	p3.setPosition(positionX,positionY);
	p3.setFloodPosition(2, 2);
	p3.draw(f);

	p4.setMultiplication(multiply);
	p4.setCenterX(26);
	p4.setCenterY(20);
	p4.setPolyline(parachute4, 17);
	p4.setPosition(positionX,positionY);
	p4.setFloodPosition(2, 2);
	p4.draw(f);

	p5.setMultiplication(multiply);
	p5.setCenterX(26);
	p5.setCenterY(20);
	p5.setPolyline(parachute5, 22);
	p5.setPosition(positionX,positionY);
	p5.setFloodPosition(2, 2);
	p5.draw(f);

	p6.setMultiplication(multiply);
	p6.setCenterX(26);
	p6.setCenterY(20);
	p6.setPolyline(parachuteString1, 5);
	p6.setPosition(positionX,positionY);
	p6.setFloodPosition(2, 2);
	p6.draw(f);

	p7.setMultiplication(multiply);
	p7.setCenterX(26);
	p7.setCenterY(20);
	p7.setPolyline(parachuteString2, 5);
	p7.setPosition(positionX,positionY);
	p7.setFloodPosition(2, 2);
	p7.draw(f);

	p8.setMultiplication(multiply);
	p8.setCenterX(26);
	p8.setCenterY(20);
	p8.setPolyline(parachuteString3, 5);
	p8.setPosition(positionX,positionY);
	p8.setFloodPosition(2, 2);
	p8.draw(f);

	p9.setMultiplication(multiply);
	p9.setCenterX(26);
	p9.setCenterY(20);
	p9.setPolyline(parachuteString4, 5);
	p9.setPosition(positionX,positionY);
	p9.setFloodPosition(2, 2);
	p9.draw(f);

	p10.setMultiplication(multiply);
	p10.setCenterX(26);
	p10.setCenterY(20);
	p10.setPolyline(parachuteString5, 5);
	p10.setPosition(positionX,positionY);
	p10.setFloodPosition(2, 2);
	p10.draw(f);


}

//4
int shipCannon[]{
	15, 1, 18, 2,
	18, 2, 16, 6,
	16, 6, 12, 6,
	12, 6, 15, 1	
};

//4
int shipCabin[]{
	8, 6, 20, 6,
	20, 6, 20, 10,
	20, 10, 8, 10,
	8, 10, 8, 6
};


//4
int shipDeck[]{
	0, 10, 28, 10,
	28, 10, 24, 18,
	24, 18, 4, 18,
	4, 18, 0, 10
};


//8
int head[]{
	18, 0, 30, 0,
	30, 0, 32, 4,
	32, 4, 32, 8,
	32, 8, 29, 15,
	29, 15, 26, 16, 
	26, 16, 22, 16, 
	22, 16, 19, 15,
	19, 15, 16, 8,
	16, 8, 16, 4,
	16, 4, 18, 0
};

//4
int humanBody[]{
	14, 14, 34, 14,
	34, 14, 34, 34,
	34, 34, 14, 34,
	14, 34, 14, 14	
};

//3
int leftHand[]{
	0, 18, 14, 18,
	14, 18, 14, 14,
	14, 14, 0, 18
};

//3
int rightHand[]{
	34, 14, 34, 18,
	34, 18, 48, 18,
	48, 18, 34, 14
};

//3
int leftFoot[]{
	14, 34, 24, 34,
	24, 34, 14, 60,
	14, 60, 14, 34
};

//3
int rightFoot[]{
	24, 34, 34, 34,
	34, 34, 34, 60,
	34, 60, 24, 34
};

int *intdup(int const * src, size_t len)
{
   int * p = (int*)malloc(len * sizeof(int));
   memcpy(p, src, len * sizeof(int));
   return p;
}

void printArray(int array[], int len){
	for (int i =0; i < len; i++){
		printf("%d, ", array[i]);
	}
	printf("\n");

}

void drawPropeller(int degree, int positionX, int positionY, float multiply, frameBuffer *f){
	polygon p1, p2;

	p1.setMultiplication(multiply);
	p1.setCenterX(38);
	p1.setCenterY(24);
	int * newRightPropeller = rotateList(degree, 38, 24, rightPropeller, 12);
	p1.setPolyline(newRightPropeller, 3);
	p1.setPosition(positionX,positionY);
	p1.setFloodPosition(2, 2);
	p1.draw(f);

	p2.setMultiplication(multiply);
	p2.setCenterX(38);
	p2.setCenterY(24);
	int* newLeftPropeller = rotateList(degree, 38, 24, leftPropeller, 12);
	p2.setPolyline(newLeftPropeller, 3);
	p2.setPosition(positionX,positionY);
	p2.setFloodPosition(2, 2);
	p2.draw(f);	
}

void drawShip(int positionX, int positionY, float multiply, frameBuffer *f){
	p10.setMultiplication(multiply);
	p10.setPolyline(shipCannon, 4);
	p10.setPosition(positionX,positionY);
	p10.setFloodPosition(2, 2);
	p10.draw(f);

	p11.setMultiplication(multiply);
	p11.setPolyline(shipCabin, 4);
	p11.setPosition(positionX,positionY);
	p11.setFloodPosition(2, 2);
	p11.draw(f);

	p12.setMultiplication(multiply);
	p12.setPolyline(shipDeck, 4);
	p12.setPosition(positionX,positionY);
	p12.setFloodPosition(2, 2);
	p12.draw(f);
}


void drawHuman(int positionX, int positionY, float multiply, frameBuffer *f){
	p13.setMultiplication(multiply);
	p13.setCenterX(24);
	p13.setPolyline(head, 10);
	p13.setPosition(positionX,positionY);
	p13.setFloodPosition(2, 2);
	p13.draw(f);

	p14.setMultiplication(multiply);
	p14.setCenterX(24);
	p14.setPolyline(humanBody, 4);
	p14.setPosition(positionX,positionY);
	p14.setFloodPosition(2, 2);
	p14.draw(f);

	p15.setMultiplication(multiply);
	p15.setCenterX(24);
	p15.setPolyline(leftHand, 3);
	p15.setPosition(positionX,positionY);
	p15.setFloodPosition(2, 2);
	p15.draw(f);

	p16.setMultiplication(multiply);
	p16.setCenterX(24);
	p16.setPolyline(rightHand, 3);
	p16.setPosition(positionX,positionY);
	p16.setFloodPosition(2, 2);
	p16.draw(f);

	p17.setMultiplication(multiply);
	p17.setCenterX(24);
	p17.setPolyline(leftFoot, 3);
	p17.setPosition(positionX,positionY);
	p17.setFloodPosition(2, 2);
	p17.draw(f);

	p18.setMultiplication(multiply);
	p18.setCenterX(24);
	p18.setPolyline(rightFoot, 3);
	p18.setPosition(positionX,positionY);
	p18.setFloodPosition(2, 2);
	p18.draw(f);
}

void destroy(frameBuffer *f){
	
	float gravity = 0.5;
	int reductor = 0;

	int reductorFall = 1;
	int reductorParachute = 1;
	float vY = 1;

	int XtireLeft  = p3.getPositionX();
	int XtireRight = p4.getPositionX();
	int Ytire      = p3.getPositionY();
	float vXTire = -2;
	float vYTire = 10;

	while (reductor < 1000) {

		p1.setMultiplication(p1.getMultiplication());
		p1.setCenterX(38);
		p1.setCenterY(24);
		p1.setPolyline(leftWing, 14);
		p1.setPosition(p1.getPositionX()-reductor, p1.getPositionY());
		p1.setFloodPosition(2, 2);
		p1.draw(f);

		p2.setMultiplication(p2.getMultiplication());
		p2.setCenterX(38);
		p2.setCenterY(24);
		p2.setPolyline(rightWing, 14);
		p2.setPosition(p2.getPositionX()+reductor, p2.getPositionY());
		p2.setFloodPosition(2, 2);
		p2.draw(f);

		XtireLeft  += vXTire;
		XtireRight += vXTire;

		//printf("%d %d\n", Ytire, vYTire);

		if (Ytire > 400) {
			Ytire = 350;
			vYTire = -0.7*vYTire;
		} else {
			vYTire += gravity;
		}
		
		Ytire += vYTire;

		p3.setMultiplication(p3.getMultiplication());
		p3.setCenterX(38);
		p3.setCenterY(24);
		p3.setPolyline(leftTyre, 8);
		p3.setPosition(XtireLeft,Ytire);
		p3.setFloodPosition(2, 2);
		p3.draw(f);

		p4.setMultiplication(p4.getMultiplication());
		p4.setCenterX(38);
		p4.setCenterY(24);
		p4.setPolyline(rightTyre, 8);
		p4.setPosition(XtireRight,Ytire);
		p4.setFloodPosition(2, 2);
		p4.draw(f);

		p5.setMultiplication(p5.getMultiplication());
		p5.setCenterX(38);
		p5.setCenterY(24);
		p5.setPolyline(tail, 9);
		p5.setPosition(p5.getPositionX()+reductor,p5.getPositionY()+reductor);
		p5.setFloodPosition(2, 2);
		p5.draw(f);

		p6.setMultiplication(p6.getMultiplication());
		p6.setCenterX(38);
		p6.setCenterY(24);
		p6.setPolyline(body, 20);
		p6.setPosition(p6.getPositionX()-reductor,p6.getPositionY()-reductor);
		p6.setFloodPosition(2, 2);
		p6.draw(f);

		p7.setMultiplication(p7.getMultiplication());
		p7.setCenterX(38);
		p7.setCenterY(24);
		p7.setPolyline(secondFrontBody, 12);
		p7.setPosition(p7.getPositionX()+reductor,p7.getPositionY()-reductor);
		p7.setFloodPosition(2, 2);
		p7.draw(f);

		p8.setMultiplication(p8.getMultiplication());
		p8.setCenterX(38);
		p8.setCenterY(24);
		p8.setPolyline(frontBody, 8);
		p8.setPosition(p8.getPositionX()-reductor,p8.getPositionY()-reductor);
		p8.setFloodPosition(2, 2);
		p8.draw(f);

		f->render_buffer();
		degree = (degree + 5) % 360;
		f->solidBackground();
		reductor = (reductor+8)/2;
	
		drawPropeller(degree,500,100+reductorFall,p8.getMultiplication(),f);
		drawParachute(500,200+reductorParachute,1.5,f);
		drawHuman(518,350+reductorParachute,1.5,f);

		// ship
		p10.setMultiplication(p10.getMultiplication());
		p10.setPolyline(shipCannon, 4);
		p10.setPosition(p10.getPositionX() + 0.2 * reductor ,p10.getPositionY());
		p10.setFloodPosition(2, 2);
		p10.draw(f);

		p11.setMultiplication(p11.getMultiplication());
		p11.setPolyline(shipCabin, 4);
		p11.setPosition(p11.getPositionX() + 0.2 * reductor,p11.getPositionY());
		p11.setFloodPosition(2, 2);
		p11.draw(f);

		p12.setMultiplication(p12.getMultiplication());
		p12.setPolyline(shipDeck, 4);
		p12.setPosition(p12.getPositionX() + 0.2 * reductor,p12.getPositionY());
		p12.setFloodPosition(2, 2);
		p12.draw(f);
		// ship end

		reductorFall += vY;
		reductorParachute += 0.1*vY;
		vY += gravity;
	}
}

int main() {
	frameBuffer f;
	f.solidBackground();

	int reductor = 0;
	int reductorFall = 0;
	int i = 1;
	int isPlus = 0;
	int degree = 0;
	float scale = 1;
	int penambah = 1;

	int propellerX;
	int propellerY;

	while (reductor < 500) {
		drawPlane(f.getVInfoX()-(reductor*2),f.getVInfoY()-400-reductor/2,(float)reductor/(float)50.0,&f);
		drawPropeller(degree,f.getVInfoX()-(reductor*2),f.getVInfoY()-400-reductor/2,(float)reductor/(float)50,&f);
		drawShip(0, f.getVInfoY()-300, 10, &f); 
		f.render_buffer();
		degree = (degree + 5) % 360;
		scale = scale + 0.005;
		++reductor;

	 	f.solidBackground();
	}
	destroy(&f);
}
