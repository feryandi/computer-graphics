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

int frameBuffer::iabs(int n){
  int const mask = n >> (sizeof(int) * 8 - 1);
  return ((n + mask) ^ mask);
}

int frameBuffer::F(int X, int Y, int Z) {
  if (X & Z) {
    return 0;
  } else if (Y & (! Z)) {
    return 1;
  } else if ((! X) & Z) {
    return 2;
  } else if ((! Y) & (! Z)) {
    return 3;
  }
}

int frameBuffer::G(int X, int Y) {
  if (X & Y) {
    return 0;
  } else if ((! X) & Y) {
    return 1;
  } else if ((! X) & (! Y)) {
    return 2;
  } else if (X & (! Y)) {
    return 3;
  }
}
	
frameBuffer::frameBuffer() {
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
    //printf("The framebuffer device was mapped to memory successfully.\n");

	create_buffer();
}

frameBuffer::~frameBuffer() {		
    munmap(fbp, screensize);
    close(fbfd);
}

void frameBuffer::create_buffer() {
    buffer = (char*)malloc(screensize);
    memcpy(buffer, fbp, screensize);
}

void frameBuffer::render_buffer() {
    memcpy(fbp, buffer, screensize);
}

int frameBuffer::getVInfoY() {
    return vinfo.yres;
}

void frameBuffer::blockBuilder(int x, int y, int block_size, int blue, int green, int red) {
    int i, j;
    // Figure out where in memory to put the pixel
    for (j = y; j < y + block_size ; j++) {
        for (i = x; i < x + block_size; i++) {

            if ( i >= 0 && j >= 0 && i < vinfo.xres - 50 && j < vinfo.yres - 50 ) {
                location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (j+vinfo.yoffset) * finfo.line_length;

                if (vinfo.bits_per_pixel == 32) {
                    *(buffer + location) = 255 - blue;        // Blue
                    *(buffer + location + 1) = 255 - green;    // Green
                    *(buffer + location + 2) = 255 - red;    // Red
                    *(buffer + location + 3) = 0;      // Alpha
            //location += 6;
                } else  { //assume 16bpp
                    int b = 255 - blue;
                    int g = 255 - green;     // A little green
                    int r = 255 - red;    // A lot of red
                    unsigned short int t = r<<11 | g << 5 | b;
                    *((unsigned short int*)(buffer + location)) = t;
                }
            }

        }
    }
}

int frameBuffer::checkColor(int x, int y) {
  if (( x > 0 && y > 0 && x < vinfo.xres - 60 && y < vinfo.yres - 60 )) {
    location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
               (y+vinfo.yoffset) * finfo.line_length;

    if (vinfo.bits_per_pixel == 32) {
      if ((*(buffer + location) == 0 && *(buffer + location + 1) == 0 && *(buffer + location + 2) == 0 && *(buffer + location + 3) == 0)){
        return 0;
      } else {
        return 1;
      }
    } else {
        if (*((unsigned short int*)(buffer + location)) == 0){
         return 0;
        } else {
          return 1;
        }
    }
  } else {
    return 1;
  }
  
}

void frameBuffer::floodFill(int x, int y){
  if (checkColor(x,y)){}
   //if (checkColor(x,y)){}
    else {
      // printf("%d\n", x);
      // printf("%d\n", y);
      if (( x > 0 && y > 0 && x < vinfo.xres - 60 && y < vinfo.yres - 60 )) {
        blockBuilder(x,y,1,0,0,0);
      }

      floodFill(x+1,y);
      floodFill(x-1,y);
      floodFill(x,y+1);
      floodFill(x,y-1);
    }
}

void frameBuffer::solidBackground() {
    int i, j;
    // Figure out where in memory to put the pixel
    for (j = 0; j < vinfo.yres - 50; j++) {
        for (i = 0; i < vinfo.xres - 50; i++) {

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

void frameBuffer::bresenham(int x1, int y1, int x2, int y2, int pixel, int red, int green, int blue, int** oosElement) {
  int Fx[] = { 1,  0, -1,  0};
  int Fy[] = { 0,  1,  0, -1};

  int Gx[] = { 1, -1, -1,  1};
  int Gy[] = { 1,  1, -1, -1};

  int dx = x2 - x1;
  int dy = y2 - y1;

  int X = dx > 0;
  int Y = dy > 0;
  int Z = (iabs(dx) - iabs(dy)) > 0;

  int f = F(X, Y, Z);
  int g = G(X, Y);

  int m1x = Fx[f];
  int m1y = Fy[f];
  int m2x = Gx[g];
  int m2y = Gy[g];

  int da, db;

  if (Z) {
    da = iabs(dx); db = iabs(dy);
  } else {
    da = iabs(dy); db = iabs(dx);
  }

  int D = 2*db - da;
  
  blockBuilder(x1, y1, pixel, red, green, blue);

  int x = x1;
  int y = y1;

  // allocate oos map
  *oosElement = (int*) malloc((iabs(y2-y1)+2)*sizeof(int));
  //printf("(%d,%d) ->  (%d,%d) allocate %d\n", x1,y1,x2,y2, (iabs(y2-y1)+2));

  // mapping line y to x
  (*oosElement)[0] = x1;

  while ((Z && (x != x2)) || (!Z && (y != y2))) {

    D = D + 2*db;

    if (D >= 0) {
      x += m2x;
      y += m2y;
      D = D - 2*da;
    } else {
      x += m1x;
      y += m1y;
    }

    // mapping line y to x
    printf("y:%d x:%d [%d]\n",y,x, iabs(y - y1));
    (*oosElement)[iabs(y - y1)] = x;

    blockBuilder(x, y, pixel, red, green, blue);
  }

  //free(*oosElement);
}
