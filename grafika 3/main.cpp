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

int main() {
	frameBuffer f;
	f.solidBackground();
	f.bresenham(50, 50, 250, 250, 0, 0, 0);
	f.render_buffer();
}