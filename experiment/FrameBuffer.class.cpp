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
     ( y < vinfo.yres - 1 ) ) {

            location = ((x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       ((y + vinfo.yoffset) * finfo.line_length));

            if (vinfo.bits_per_pixel == 32) {
                *(buffer + location) = blue;    // Blue
                *(buffer + location + 1) = green; // Green
                *(buffer + location + 2) = red; // Red
                *(buffer + location + 3) = 0;     // Alpha
            } else  { 
              // Assuming 16bpp
                int b = blue;   // Blue
                int g = green;  // Green
                int r = red;    // Red
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
    int yMax = (polygon->getPointY(0));
    int yMin = (polygon->getPointY(0));
    int nPoint = polygon->getPointCount();

    while (point < nPoint) {
        if (polygon->getPointType(point) == 1) {
          int x1, y1, x2, y2;
          x1 = (polygon->getPointX(point));
          y1 = (polygon->getPointY(point));
          x2 = (polygon->getPointX(point+1));
          y2 = (polygon->getPointY(point+1));

          if (yMax < std::max(y1,y2)) yMax = std::max(y1,y2);
          if (yMin > std::min(y1,y2)) yMin = std::min(y1,y2);

          bresenham(x1, y1, x2, y2, 255, 255, 255, point);

        } else {
          int startN = point;
          int total = 0;
          int endN = point;

          int stop = 1;

          if (polygon->getPointType(point) == 3) {
            ++point;
            ++startN;
          }

          while ( stop && ( point < nPoint ) ) {
            if ( polygon->getPointType(point) != 0 ) {
              stop = 0;
              --point;
            }
            ++point;
            ++total;
          }

          endN = point;
          --point;

          if (total > 1) {
            float to = 0.001;
            float t = 0;

            Point lastPoint = Point((polygon->getPointX(startN)), (polygon->getPointY(startN)), 0);

            Point** bezierArray = (Point **) malloc(sizeof(Point) * total);

            for ( int i = 0; i < total; i++ ) {
              if ( (bezierArray[i] = (Point *) malloc((i + 1) * sizeof(Point))) == NULL ) {
                /* Error */
              } else {
                bezierArray[i][0] = Point((polygon->getPointX(i + startN)), (polygon->getPointY(i + startN)), 0);
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
                      
                      int y1 = (int)lastPoint.getY();
                      int y2 = (int)bezierArray[i][j].getY();
                      lastPoint = Point(bezierArray[i][j].getX(), bezierArray[i][j].getY(), 0);

                      if (yMax < std::max(y1,y2)) yMax = std::max(y1,y2);
                      if (yMin > std::min(y1,y2)) yMin = std::min(y1,y2);
                    }
                  }
                } 
              }
              t += to;
            }
          } else {
            plot((polygon->getPointX(point)), (polygon->getPointY(point)), 255, 255, 255);
          }

        }

        ++point;
    }
    //fillPolygon(polygon, yMin, yMax);

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

/*  int** oosElement = &oosMap[line];
  *oosElement = (int*) malloc((iabs(y2-y1)+2)*sizeof(int));
  (*oosElement)[0] = x1;*/

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

    //(*oosElement)[iabs(y - y1)] = x;
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

void FrameBuffer::clearMap(Polygon* polygon) {
    int nLine = polygon->getPointCount();
    for (int i = 0; i < nLine; ++i)
        free(oosMap[i]);
    free(oosMap);
}

int FrameBuffer::isIntersect(Polygon* polygon, int e, int yScanline) {
    int y1E = (polygon->getPointY(e));
    int y2E = (polygon->getPointY(e+1));

    return ((y1E - yScanline)*(y2E - yScanline)) <= 0;
}

int FrameBuffer::isHorizontalLine(Polygon* polygon, int e){
    int y1E = (polygon->getPointY(e));
    int y2E = (polygon->getPointY(e+1));

    return (y1E == y2E);
}

int FrameBuffer::getMiddleX(Polygon* polygon, int e){
    int x1E = (polygon->getPointX(e));
    int x2E = (polygon->getPointX(e+1));

    return (x1E + x2E) >> 1;
}

int FrameBuffer::isCriticalPoint(Polygon* polygon, int e1, int e2, int yScanline){
    int y1E1 = (polygon->getPointY(e1));
    int y2E1 = (polygon->getPointY(e1+1));
    int y1E2 = (polygon->getPointY(e2));
    int y2E2 = (polygon->getPointY(e2+1));

    int yOuterE1 = y1E1 + y2E1 - yScanline;
    int yOuterE2 = y1E2 + y2E2 - yScanline;

    return ((yOuterE1 - yScanline)*(yOuterE2 - yScanline)) >= 0;
}

int FrameBuffer::xIntersect(Polygon* polygon, int e, int yScanline){
    int y1E = (polygon->getPointY(e));

    return oosMap[e][iabs(yScanline - y1E)];
}

void FrameBuffer::fillPolygon(Polygon* polygon, int yMin, int yMax){
  
  int nLine = polygon->getPointCount();
  for (int yScanline = yMin; yScanline <= yMax; ++yScanline) {

    // printf("y: %d\n", yScanline);    
    // fflush(stdout);

    std::vector<intersection> intersectEdge; 
    for (int e = 0; e < nLine; ++e) {
      if (isIntersect(polygon, e, yScanline)) {
        int type = isHorizontalLine(polygon, e);
        int x;
        if (type) {
          x = getMiddleX(polygon, e);
        } else {
          x = xIntersect(polygon, e, yScanline);
        }
        intersectEdge.push_back(intersection(e, x, type));
      }
    }

    std::sort(intersectEdge.begin(), intersectEdge.end());

    std::vector<intersection>::iterator i = intersectEdge.begin(), j;

    if (i!=intersectEdge.end()) {
      while ((i+1) != intersectEdge.end()) {
        if ((((i+1)->x - i->x) < 5) &&
          (!isCriticalPoint(polygon, (*i).edge,(*(i+1)).edge, yScanline))) {
          
          i = intersectEdge.erase(i);

        } else {
          if ((i+1)->type == 1) {

            // warning: this conditional maybe cause a bug
            if ((i+2) != intersectEdge.end()) {
              if (isCriticalPoint(polygon, (*i).edge,(*(i+2)).edge, yScanline)) {
                i++;
                i = intersectEdge.erase(i);
              } else {
                i++;
                i->x = (i+1)->x;
                i++;
              }
            } else {
              i++;
            }

          } else {
            i++;
          }
        }
      }
    }


    int fillRed = polygon->getColorRed();
    int fillGreen = polygon->getColorGreen();
    int fillBlue = polygon->getColorBlue();

    for (int i = 0; i+1 < intersectEdge.size(); i+=2) {
      int e = intersectEdge[i].edge;
      for (int x = intersectEdge[i].x; x < intersectEdge[i+1].x; x++) {
        plot(x, yScanline, fillRed, fillGreen, fillBlue);
      }
    }

  }
}