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
#include "bezier_curve.hpp"
#include "layer.hpp"

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

		// Pre-generated table for polynoms
		std::vector<std::vector<int> > lookup_table;



	public:
		// ctor & dtor
		FrameBuffer();
		~FrameBuffer();

		//getter & setter
		int getVInfoY();
		int getVInfoX();
		std::vector<std::vector<int> > getPolynomLookupTable();

		//Copy to framebuffer
		void clearScreen();
		void render();

		// static methods
		static void plot(char* buffer, unsigned int x, unsigned int y, int red, int green, int blue);
	};
