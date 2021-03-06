#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>
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
#include <vector>
#include <time.h>

class FrameBuffer {
	private:
		// Default Things
		struct fb_var_screeninfo vinfo;
		struct fb_fix_screeninfo finfo;

		int fbfd;
		long int screensize;
		char *fbp;
		long int location;

		// Making Render Smoother
		char *buffer;

		// Center point
		int center_x;
		int center_y;

	public:
		int zbuffer[768][1366];
		// ctor & dtor
		FrameBuffer();
		~FrameBuffer();

		//getter & setter
		int getVInfoY();
		int getVInfoX();
		int getCX();
		int getCY();
		char* getBuffer();

		//Copy to framebuffer
		int getLocation(int x, int y);
		void clearScreen();
		void infoScreen();
		void clearZBuffer();
		void render();

		void plot(unsigned int x, unsigned int y, int red, int green, int blue);
		void plotWS(unsigned int x, unsigned int y, int red, int green, int blue, int size);
	};

#endif
