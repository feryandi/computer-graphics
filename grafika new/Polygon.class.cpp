#include "Polygon.class.h"

using namespace std;

Polygon::Polygon(int cx, int cy, int* w, int len) {
	x = 0;
	y = 0;
	k = 1;
	setCenter(cx, cy);
	setWireframe(w, len);
}

Polygon::~Polygon() {
	delete [] wireframe;
}

int Polygon::getX() {
	return x;
}

int Polygon::getY() {
	return y;
}

void Polygon::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

int Polygon::getCX() {
	return cx;
}

int Polygon::getCY() {
	return cy;
}

void Polygon::setCenter(int cx, int cy) {
	this->cx = cx;
	this->cy = cy;
}

int Polygon::getWidth() {
	return width;
}

int Polygon::getHeight() {
	return height;
}

void Polygon::setWireframe(int* w, int len) {
    wireframe = new int[len];
	wireframe = intdup(w, len);

	this->len = len;

	// Get Width and Height (maximum thingy) for bitmap
	int maxH = 0;
	int maxW = 0;

	int minH = ((wireframe[1] - cx) * k + x);
	int minW = ((wireframe[0] - cx) * k + x);

    for (int i = 0; i < len; i++) {
    	if ( i % 2 == 0 ) {
    		if ( maxW < ((wireframe[i] - cx) * k + x) ) maxW = ((wireframe[i] - cx) * k + x);
    		if ( minW > ((wireframe[i] - cx) * k + x) ) minW = ((wireframe[i] - cx) * k + x);
    	} else {
    		if ( maxH < ((wireframe[i] - cx) * k + x) ) maxH = ((wireframe[i] - cx) * k + x);
    		if ( minH > ((wireframe[i] - cx) * k + x) ) minH = ((wireframe[i] - cx) * k + x);
    	}
    }

    if (minH > 0) { 
    	minH = 0; 
   	} else {
   		--minH;
   	}

    if (minW > 0) { 
    	minW = 0; 
   	} else {
   		--minW;
   	}

    cout << "minh: " << minH << " | maxh: " << maxH << endl;
    cout << "minw: " << minW << " | maxw: " << maxW << endl;

    this->height = (maxH - minH) + 1;
    this->width = (maxW - minW) + 1; 

    cout << "h: " << this->height << " | w: " << this->width << endl;

    generateBitmap(minW, minH);
}

void Polygon::setMultiplication(float k) {
	this->k = k;
}

float Polygon::getMultiplication() {
	return k;
}

int* Polygon::getBitmap() {
	return bitmap;
}

void Polygon::setDegree(float degree){
    int *temp = (int*) malloc(len * sizeof(int));
	if(len%2==0){
		double val = PI/180.0;

		cout << endl;

		for (int i=0; i<len; i++){
			if (i%2==0){
				temp[i] = (int) ( cos(degree * val) * (wireframe[i] - cx) - ( sin(degree * val) * (wireframe[i+1] - cy) ) + cx );
				cout << "(" << wireframe[i] << ") -> " << temp[i] << ",";
			} else {
				temp[i] = (int) ( sin(degree * val) * (wireframe[i-1] - cx) + cos(degree * val) * (wireframe[i] - cy) + cy );
				cout << "(" << wireframe[i] << ") -> " << temp[i] << endl;
			}
		}

	} else {
		printf("Odd list");
	}

	setWireframe(temp, len);
}


// Private Methods

void Polygon::generateBitmap(int minW, int minH) {
	bitmap = new int[(height) * (width)];

	int i = 0;
	while (i < len) {

		int a, b, c, d;
		a = (int) ((wireframe[(++i) - 1] - cx) * k + x) - minW;
		b = (int) ((wireframe[(++i) - 1] - cx) * k + y) - minH;
		c = (int) ((wireframe[(++i) - 1] - cx) * k + x) - minW;
		d = (int) ((wireframe[(++i) - 1] - cx) * k + y) - minH;

		bresenham(a, b, c, d, bitmap);

	}

	// DRIVER
	
	for (int n = 0; n < ((height) * (width)); n++) {
    	if ( n % (width) == 0 ) {
    		cout << endl;
    	}
    	cout << bitmap[n] << " ";
    }
    
}

int* Polygon::intdup(int const * src, size_t len) {
	int* p = (int*) malloc(len * sizeof(int));
	memcpy(p, src, len * sizeof(int));
	return p;
}

int Polygon::iabs(int n){
  int const mask = n >> (sizeof(int) * 8 - 1);
  return ((n + mask) ^ mask);
}

int Polygon::F(int X, int Y, int Z) {
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

int Polygon::G(int X, int Y) {
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

void Polygon::bresenham(int x1, int y1, int x2, int y2, int *bitmap) {
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

  *(bitmap + (y1*width) + x1) = 1;

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

  	*(bitmap + (y*width) + x) = 1;
  }
}
