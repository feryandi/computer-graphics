#include "Polygon.class.h"
#include "FrameBuffer.class.h"

FrameBuffer::FrameBuffer() {
	// Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (atoi(fbp) == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

    // Making buffer, smoother framerate
    buffer = (char*)malloc(screensize);
    memcpy(buffer, fbp, screensize);
}

FrameBuffer::~FrameBuffer() {
    munmap(fbp, screensize);
    close(fbfd);
}

int FrameBuffer::getVInfoY() {
    return vinfo.yres;
}

int FrameBuffer::getVInfoX() {
    return vinfo.xres;
}

void FrameBuffer::plot(int x, int y, int red, int green, int blue) {
	int i, j;

	if ( ( x >= 0 ) && 
		 ( y >= 0 ) && 
		 ( x < vinfo.xres - 1 ) && 
		 ( y < vinfo.yres - 1 ) ) {

            location = ((x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       ((y + vinfo.yoffset) * finfo.line_length));

            if (vinfo.bits_per_pixel == 32) {
                *(buffer + location) = blue;		// Blue
                *(buffer + location + 1) = green;	// Green
                *(buffer + location + 2) = red;	// Red
                *(buffer + location + 3) = 0;			// Alpha
            } else  { 
            	// Assuming 16bpp
                int b = blue;		// Blue
                int g = green;	// Green
                int r = red;		// Red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(buffer + location)) = t;
            }

    }
}

void FrameBuffer::render() {
    memcpy(fbp, buffer, screensize);
}

void FrameBuffer::canvas() {
    int i, j;
    // Figure out where in memory to put the pixel
    for (j = 0; j < vinfo.yres; j++) {
        for (i = 0; i < vinfo.xres; i++) {

            location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (j+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(buffer + location) = 0;        // Blue
                *(buffer + location + 1) = 0;    // Green
                *(buffer + location + 2) = 0;    // Red
                *(buffer + location + 3) = 0;      // Alpha
        //location += 4;
            } else  { //assume 16bpp
                int b = 0;
                int g = 0;     // A little green
                int r = 0;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(buffer + location)) = t;
            }

        }
    }
}