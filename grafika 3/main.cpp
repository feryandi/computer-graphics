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

#include "frameBuffer.class.h"
#include "polygon.class.h"

int main() {
	frameBuffer f;
	f.solidBackground();

	polygon p;
	// 11
	int fontA[] = { 6, 0, 10, 0,
					10, 0, 16, 20,
					16, 20, 12, 20,
					12, 20, 10, 14,
					10, 14, 6, 14,
					6, 14, 4, 20,
					4, 20, 0, 20,
					0, 20, 6, 0,
					8, 7, 9, 10,
					9, 10, 7, 10,
					7, 10, 8, 7};	
	// 25
	int fontB[] = { 0, 0, 12, 0,
					12, 0, 14, 1,
					14, 1, 15, 2,
					15, 2, 16, 5,
					16, 5, 15, 8,
					15, 8, 13, 10,
					13, 10, 15, 12,
					15, 12, 16, 15,
					16, 15, 15, 18,
					15, 18, 14, 19,
					14, 19, 12, 20,
					12, 20, 0, 20,
					0, 20, 0, 0,
					4, 4, 10, 4,
					10, 4, 11, 5,
					11, 5, 11, 7,
					11, 7, 9, 8,
					9, 8, 4, 8,
					4, 8, 4, 4,
					4, 12, 9, 12,
					9, 12, 11, 13,
					11, 13, 11, 15,
					11, 15, 10, 16,
					10, 16, 4, 16,
					4, 16, 4, 12 };
	// 30		
	int fontC[] = { 6, 0, 10, 0,
					10, 0, 13, 1,
					13, 1, 15, 3,
					15, 3, 16, 6, 
					16, 6, 16, 8,
					16, 8, 12, 8,
					12, 8, 11, 5,
					11, 5, 10, 4,
					10, 4, 6, 4,
					6, 4, 5, 5,
					5, 5, 4, 8,
					4, 8, 4, 12,
					4, 12, 5, 15,
					5, 15, 6, 16,
					6, 16, 10, 16,
					10, 16, 11, 15,
					11, 15, 12, 12,
					12, 12, 16, 12,
					16, 12, 16, 14,
					16, 14, 15, 17,
					15, 17, 13, 19,
					13, 19, 10, 20,
					10, 20, 6, 20,
					6, 20, 3, 19,
					3, 19, 1, 17,
					1, 17, 0, 14,
					0, 14, 0, 6,
					0, 6, 1, 3,
					1, 3, 3, 1,
					3, 1, 6, 0};	
	// 18
	int fontD[] = { 0, 0, 8, 0,
					8, 0, 12, 1,
					12, 1, 15, 3,
					15, 3, 16, 6,
					16, 6, 16, 14,
					16, 14, 15, 17,
					15, 17, 12, 19,
					12, 19, 8, 20,
					8, 20, 0, 20,
					0, 20, 0, 0,
					4, 4, 8, 4,
					8, 4, 11, 5,
					11, 5, 12, 8,
					12, 8, 12, 12,
					12, 12, 11, 15,
					11, 15, 8, 16,
					8, 16, 4, 16,
					4, 16, 4, 4 };		
	// 12
	int fontE[] = { 0, 0, 16, 0,
					16, 0, 16, 4,
					16, 4, 4, 4,
					4, 4, 4, 8,
					4, 8, 12, 8,
					12, 8, 12, 12,
					12, 12, 4, 12,
					4, 12, 4, 16,
					4, 16, 16, 16,
					16, 16, 16, 20,
					16, 20, 0, 20,
					0, 20, 0, 0 };
	// 10
	int fontF[] = { 0, 0, 16, 0,
					16, 0, 16, 4,
					16, 4, 4, 4,
					4, 4, 4, 8,
					4, 8, 12, 8,
					12, 8, 12, 12,
					12, 12, 4, 12,
					4, 12, 4, 20,
					4, 20, 0, 20,
					0, 20, 0, 0};
	// 12
	int fontM[] = { 0, 0, 4, 0,
					4, 0, 12, 12,
					12, 12, 20, 0,
					20, 0, 24, 0,
					24, 0, 24, 20,
					24, 20, 20, 20,
					20, 20, 20, 8,
					20, 8, 12, 20,
					12, 20, 4, 8,
					4, 8, 4, 20,
					4, 20, 0, 20,
					0, 20, 0, 0 };
	// 10
	int fontN[] = { 0, 0, 4, 0,
					4, 0, 12, 12,
					12, 12, 12, 0,
					12, 0, 16, 0,
					16, 0, 16, 20,
					16, 20, 12, 20,
					12, 20, 4, 8,
					4, 8, 4, 20,
					4, 20, 0, 20,
					0, 20, 0, 0 };
	// 12
	int fontH[] = {	0, 0, 4, 0,
					4, 0, 4, 8,
					4, 8, 12, 8,
					12, 8, 12, 0,
					12, 0, 16, 0,
					16, 0, 16, 20,
					16, 20, 12, 20,
					12, 20, 12, 12,
					12, 12, 4, 12,
					4, 12, 4, 20,
					4, 20, 0, 20,
					0, 20, 0, 0};
	// 9
	int fontL[] = { 0, 0, 4, 0,
					4, 0, 4, 4,
					4, 4, 4, 8,
					4, 8, 4, 12,
					4, 12, 4, 16,
					4, 16, 16, 16,
					16, 16, 16, 20,
					16, 20, 0, 20,
					0, 20, 0, 0 };
	// 16
	int fontJ[] = { 0, 12, 4, 12,
					4, 12, 4, 15,
					4, 15, 5, 16,
					5, 16, 11, 16,
					11, 16, 12, 15,
					12, 15, 12, 0,
					12, 0, 16, 0,
					16, 0, 16, 16,
					16, 16, 15, 18,
					15, 18, 14, 19,
					14, 19, 12, 20,
					12, 20, 4, 20,
					4, 20, 2, 19,
					2, 19, 1, 18,
					1, 18, 0, 16,
					0, 16, 0, 12 };
	// 30	
	int fontO[] = { 6, 0, 10, 0,
					10, 0, 13, 1,
					13, 1, 15, 3,
					15, 3, 16, 6, 
					16, 6, 16, 8,
					16, 8, 16, 12,
					12, 8, 11, 5,
					11, 5, 10, 4,
					10, 4, 6, 4,
					6, 4, 5, 5,
					5, 5, 4, 8,
					4, 8, 4, 12,
					4, 12, 5, 15,
					5, 15, 6, 16,
					6, 16, 10, 16,
					10, 16, 11, 15,
					11, 15, 12, 12,
					12, 12, 12, 8,
					16, 12, 16, 14,
					16, 14, 15, 17,
					15, 17, 13, 19,
					13, 19, 10, 20,
					10, 20, 6, 20,
					6, 20, 3, 19,
					3, 19, 1, 17,
					1, 17, 0, 14,
					0, 14, 0, 6,
					0, 6, 1, 3,
					1, 3, 3, 1,
					3, 1, 6, 0};	
	// 20
	int fontR[] = { 0, 0, 12, 0,
					12, 0, 14, 1,
					14, 1, 15, 2,
					15, 2, 16, 5,
					16, 5, 15, 8,
					15, 8, 13, 10,
					13, 10, 12, 11,
					12, 11, 17, 20,
					17, 20, 12, 20,
					12, 20, 8, 12,
					8, 12, 4, 12,
					4, 12, 4, 20,
					4, 20, 0, 20,
					0, 20, 0, 0,
					4, 4, 10, 4,
					10, 4, 11, 5,
					11, 5, 11, 7,
					11, 7, 9, 8,
					9, 8, 4, 8,
					4, 8, 4, 4 };
	// 16
	int fontU[] = { 0, 0, 4, 0,
					4, 0, 4, 15,
					4, 15, 5, 16,
					5, 16, 11, 16,
					11, 16, 12, 15,
					12, 15, 12, 0,
					12, 0, 16, 0,
					16, 0, 16, 16,
					16, 16, 15, 18,
					15, 18, 14, 19,
					14, 19, 12, 20,
					12, 20, 4, 20,
					4, 20, 2, 19,
					2, 19, 1, 18,
					1, 18, 0, 16,
					0, 16, 0, 0 };
	// 13
	int fontW[] = { 0, 0, 5, 0, 
					5, 0, 8, 10,
					8, 10, 11, 0,
					11, 0, 17, 0,
					17, 0, 20, 10,
					20, 10, 23, 0,
					23, 0, 28, 0,
					28, 0, 22, 20,
					22, 20, 18, 20,
					18, 20, 14, 7,
					14, 7, 10, 20,
					10, 20, 6, 20,
					6, 20, 0, 0 };
	// 9
	int fontY[] = { 0, 0, 4, 0,
					4, 0, 8, 8,
					8, 8, 12, 0,
					12, 0, 16, 0,
					16, 0, 10, 12,
					10, 12, 10, 20,
					10, 20, 6, 20,
					6, 20, 6, 12,
					6, 12, 0, 0};


	
	p.setMultiplication(5);
	p.setPolyline(fontY, 9);
	p.setPosition(0,0);
	p.draw(&f);

	polygon p2;
	p2.setMultiplication(5);
	p2.setPolyline(fontY, 9);
	p2.setPosition(100,0);				
	p2.draw(&f);

	polygon p3;
	p3.setMultiplication(5);
	p3.setPolyline(fontY, 9);
	p3.setPosition(200,0);				
	p3.draw(&f);

	polygon p4;
	p4.setMultiplication(5);
	p4.setPolyline(fontY, 9);
	p4.setPosition(300,0);				
	p4.draw(&f);


	// f.floodFill(100,100);
	f.render_buffer();
}