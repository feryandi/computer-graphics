#ifndef FrameBuffer_Class_H
#define FrameBuffer_Class_H
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
#include <time.h>
#include "Polygon.class.h"

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

		// Private Methods
	
	public:
		FrameBuffer();
		~FrameBuffer();

		int getVInfoY();
		int getVInfoX();

		void addPolygon(Polygon*);
		void addObject(); // To Be Implemented

		void canvas();
		void render();
};

#endif