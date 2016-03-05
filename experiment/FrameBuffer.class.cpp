#include "FrameBuffer.class.h"
#include <vector>

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
		 ( y < vinfo.yres - 1 ) &&
     (this->available[y][x] == 0))
     {
          this->available[y][x] = 1;
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
    for (j = 0; j < vinfo.yres; j++) {
        for (i = 0; i < vinfo.xres; i++) {

            location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (j+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(buffer + location) = 0;        // Blue
                *(buffer + location + 1) = 0;    // Green
                *(buffer + location + 2) = 0;    // Red
                *(buffer + location + 3) = 0;      // Alpha
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


void FrameBuffer::draw(std::vector<Polygon*> &polygons){
    std::vector<Polygon*>::iterator it;

    for (it = polygons.begin(); it != polygons.end(); it++) {
        drawPolygon(*it);
    }
}

void FrameBuffer::drawPolygon(Polygon *polygon) {
    int point = 0;
    int nPoint = polygon->getPointCount();

    while (point < nPoint) {
        if (polygon->getPointType(point) == 1) {

          int x1, y1, x2, y2;
          x1 = (polygon->getPoint(point))->getX();
          y1 = (polygon->getPoint(point))->getY();
          x2 = (polygon->getPoint(point+1))->getY();
          y2 = (polygon->getPoint(point+1))->getY();

          bresenham(x1, y1, x2, y2, 255, 255, 255, point);

        } else {
          int startN = point;
          int total = 0;

          int stop = 1;

          while ( stop && ( point < nPoint ) ) {
            if ( polygon->getPointType(point) == 0 ) {
              ++point;
              ++total;
            } else {
              stop = 0;
            }
          }
          --point;
          printf("p: %d", point);

          float to = 0.001;
          float t = 0;

          Point lastPoint = Point((polygon->getPoint(startN))->getX(), (polygon->getPoint(startN))->getY(), 0);

          Point** bezierArray = (Point **) malloc(sizeof(Point) * total);

          for ( int i = 0; i < total; i++ ) {
            if ( (bezierArray[i] = (Point *) malloc((i + 1) * sizeof(Point))) == NULL ) {
              /* Error */
            } else {
              bezierArray[i][0] = Point((polygon->getPoint(i))->getX(), (polygon->getPoint(i))->getY(), 0);
            }
          }
          
          while ( t <= 1) {
            for ( int j = 1; j < total; j++ ) {
              for ( int i = 1; i < total; i++ ) {
                if ( j < i + 1 ) {
                  float x = (((float)(1 - t) * bezierArray[i-1][j-1].getX()) + (float)(t * bezierArray[i][j-1].getX()));
                  float y = (((float)(1 - t) * bezierArray[i-1][j-1].getY()) + (float)(t * bezierArray[i][j-1].getY()));

                  bezierArray[i][j] = Point(x, y, 0);
                  
                  if ( ( i == total-1 ) && ( j == total-1 ) ) {
                    bresenham((int)lastPoint.getX(), (int)lastPoint.getY(), (int)bezierArray[i][j].getX(), (int)bezierArray[i][j].getY(), 255, 255, 255, 1);
                    lastPoint = Point(bezierArray[i][j].getX(), bezierArray[i][j].getY(), 0);
                  }
                }
              } 
            }
            t += to;
          }

        }

        ++point;
    }

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

int FrameBuffer::iabs(int n){
  int const mask = n >> (sizeof(int) * 8 - 1);
  return ((n + mask) ^ mask);
}

int FrameBuffer::F(int X, int Y, int Z) {//Z BUKAN UNTUK 3D
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

int FrameBuffer::G(int X, int Y) {
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
