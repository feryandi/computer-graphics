#ifndef frameBuffer_Class_H
#define frameBuffer_Class_H

class frameBuffer {
	private:
		struct fb_var_screeninfo vinfo;
		struct fb_fix_screeninfo finfo;

		int fbfd;
		long int screensize;
		char *fbp;
		char *buffer;
		long int location;

		int iabs(int n);
		int F(int X, int Y, int Z);
		int G(int X, int Y);
	
	public:
		frameBuffer();
		~frameBuffer();
		int getVInfoY();
		int getVInfoX();
		void create_buffer();
		void render_buffer();
		void blockBuilder(int x, int y, int block_size, int blue, int green, int red);
		void solidBackground();
		void bresenham(int x1, int y1, int x2, int y2, int pixel, int red, int green, int blue);
		int checkColor(int x, int y);
		void floodFill(int x, int y);
};

#endif