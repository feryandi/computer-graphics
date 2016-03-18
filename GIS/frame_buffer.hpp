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

	public:
		// ctor & dtor
		FrameBuffer();
		~FrameBuffer();

		//getter & setter
		int getVInfoY();
		int getVInfoX();

		//Copy to framebuffer
		void clearScreen();
		void render();

		void plot(unsigned int x, unsigned int y, int red, int green, int blue);
	};
