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
	int c[] = { 00, 00,
				10, 00,
				10, 05,
				07, 05,
				07, 25,
				10, 25,
				10, 30,
				00, 30,
				00, 25,
				03, 25,
				03, 05,
				00, 05,
				00, 00 };
	p.setPolyline(c, 12);
	p.setPosition(0,0);
	p.setMultiplication(3);
	p.draw(&f);
	// f.floodFill(100,100);
	f.render_buffer();
}