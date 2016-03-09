#include "frame_buffer.hpp"
#include <vector>
#define MAX_ORDER 50
#define STEP 1000


FrameBuffer::FrameBuffer() {

    //Generate Polynom table
    for (int i=0; i<MAX_ORDER-1; i++){
      std::vector<int> v;
      v.push_back(1);
      for (int j=1;j<=i-1;j++){
        v.push_back(lookup_table.at(i-1).at(j-1)+lookup_table.at(i-1).at(j));
      }
      if (i > 0){
        v.push_back(1);
      }
      lookup_table.push_back(v);
    }

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

std::vector<std::vector<int> > FrameBuffer::getPolynomLookupTable() {
  return lookup_table;
}

int FrameBuffer::iabs(int n){
  int const mask = n >> (sizeof(int) * 8 - 1);
  return ((n + mask) ^ mask);
}

int FrameBuffer::F(int X, int Y, int Z) {//Z BUKAN UNTUK 3D
  int retval = 0;
  if (X & Z) {
    retval = 0;
  } else if (Y & (! Z)) {
    retval = 1;
  } else if ((! X) & Z) {
    retval = 2;
  } else if ((! Y) & (! Z)) {
    retval = 3;
  }
  return retval;
}

int FrameBuffer::G(int X, int Y) {
  int retval = 0;
  if (X & Y) {
    retval = 0;
  } else if ((! X) & Y) {
    retval = 1;
  } else if ((! X) & (! Y)) {
    retval = 2;
  } else if (X & (! Y)) {
    retval = 3;
  }
  return retval;
}

void FrameBuffer::bresenham(int x1, int y1, int x2, int y2, int red, int green, int blue, int line) {
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

  int D = 2 * db - da;

  plot(x1, y1, red, green, blue);

  int x = x1;
  int y = y1;

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

    plot(x, y, red, green, blue);

  }
}

void FrameBuffer::drawCurve(BezierCurve curve){
  float x=0,y=0; // Where to plot
  float a,b;
  int order = curve.getOrder();
  // printf("Order: %d\n", order);

  std::vector<int> polynom = lookup_table.at(order);
  for (int t=0;t<STEP;t++){
    // Step loop
    a = 1 - ((float)t/STEP);
    b = (float)t/STEP;
    x = 0; y = 0;

    // Polynom sum
    for (int i=0;i<=order;i++){

      // printf("Xb: %d\n", curve.getPoints().at(i).getX());
      // printf("Yb: %d\n", curve.getPoints().at(i).getY());
      // printf("PolynomAt_i: %d\n", polynom.at(i));
      // printf("A: %f\n", a);
      // printf("B: %f\n", b);

      float tempX = curve.getPoints().at(i).getX() * polynom.at(i);
      float tempY = curve.getPoints().at(i).getY() * polynom.at(i);

      for (int k=0;k<order-i;k++){
        tempX = tempX * a;
        tempY = tempY * a;
      }

      for (int k=0;k<i;k++){
        tempX = tempX * b;
        tempY = tempY * b;
      }

      x += tempX;
      y += tempY;
    }

    // printf("t: %d\n", t);
    // printf("X: %f\n", x);
    // printf("Y: %f\n", y);
    // printf("____________\n");
    plot((int)x,(int)y,200,200,200);
  }
}

void FrameBuffer::drawControlPoint(BezierCurve curve, unsigned int selected){
  for (unsigned int i=0;i<curve.getPoints().size();i++){
    // Draw selected Point
    if (i == selected){
      for (int j=2;j<4;j++){
        plot(curve.getPoints().at(i).getX()+j,curve.getPoints().at(i).getY(),255,0,0);
        plot(curve.getPoints().at(i).getX()-j,curve.getPoints().at(i).getY(),255,0,0);
        plot(curve.getPoints().at(i).getX(),curve.getPoints().at(i).getY()+j,255,0,0);
        plot(curve.getPoints().at(i).getX(),curve.getPoints().at(i).getY()-j,255,0,0);
      }
    }
    else{
      for (int j=2;j<4;j++){
        plot(curve.getPoints().at(i).getX()+j,curve.getPoints().at(i).getY(),0,0,255);
        plot(curve.getPoints().at(i).getX()-j,curve.getPoints().at(i).getY(),0,0,255);
        plot(curve.getPoints().at(i).getX(),curve.getPoints().at(i).getY()+j,0,0,255);
        plot(curve.getPoints().at(i).getX(),curve.getPoints().at(i).getY()-j,0,0,255);
      }
    }
    if (i < curve.getPoints().size()-1){
      bresenham(curve.getPoints().at(i).getX(),
                curve.getPoints().at(i).getY(),
                curve.getPoints().at(i+1).getX(),
                curve.getPoints().at(i+1).getY(),
                0,0,255,1);
    }
  }
}

void FrameBuffer::render() {
    memcpy(fbp, buffer, screensize);
}

void FrameBuffer::plot(unsigned int x, unsigned int y, int red, int green, int blue) {

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

void FrameBuffer::clearScreen(){
  for (unsigned int j = 0; j < vinfo.yres; j++) {
      for (unsigned int i = 0; i < vinfo.xres; i++) {
        plot(i,j,0,0,0);
      }
  }
}
