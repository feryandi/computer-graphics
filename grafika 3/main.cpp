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
	
int plane[] = { // Wing (2)
					0, 2, 40, 2,
					0, 3, 40, 3,
					// Wing Holder - Diagonal (4)
					5, 3, 16, 10,
					6, 3, 16, 9,
					33, 3, 24, 9,
					34, 3, 24, 10,
					// Wing Holder - Horizontal (5)
					17, 3, 17, 7, 
					18, 3, 18, 7,
					22, 3, 22, 7, 
					23, 3, 23, 7,
					20, 3, 20, 7,
					// Main Engine (4)
					16, 7, 24, 7,
					24, 7, 24, 14,
					24, 14, 16, 14,
					16, 14, 16, 7,
					// Left Foot (6)
					16, 14, 14, 18,
					17, 14, 14, 19,
					14, 18, 12, 18,
					12, 18, 12, 19,
					12, 19, 14, 19,
					14, 19, 14, 18,
					// Right Foot (6)
					23, 14, 26, 19, 
					24, 14, 26, 18,
					26, 18, 26, 19,
					26, 19, 28, 19,
					28, 19, 28, 18,
					28, 18, 26, 18
					};	

int propeler[] = { };

void makeBoim(int positionX, int positionY, int multiply, frameBuffer *f) {
	polygon p1;
	p1.setMultiplication(multiply);
	p1.setPolyline(plane, 27);
	p1.setPosition(positionX,positionY);
	p1.draw(f);
};

int abs(int n) {
	if (n < 0) {
		n *= -1;
	}
	return n;
}

int main() {
	frameBuffer f;
	f.solidBackground();

	int reductor = 0;
	int i = 1;
	int isPlus = 0;
		makeBoim(0, 0, 10, &f);
		f.render_buffer();

		++reductor;
		//usleep(10000);
		f.solidBackground();
}
