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

void Polygon::setWireframe(int* w, int len) {
    wireframe = new int[len];
	wireframe = intdup(w, len);

	this->len = len;

	yMax = 0;
	yMin = wireframe[1];

	for (int i = 0; i < len; i++) {
		if ( i % 2 != 0 ) {
			if ( wireframe[i] > yMax ) yMax = wireframe[i];
			if ( wireframe[i] < yMin ) yMin = wireframe[i];
		}
	}
}

void Polygon::draw(FrameBuffer *fb) {
	int i = 0;
	while (i < len) {

		int a, b, c, d;
		a = (int) ((wireframe[(++i) - 1] - cx) * k + x);
		b = (int) ((wireframe[(++i) - 1] - cx) * k + y);
		c = (int) ((wireframe[(++i) - 1] - cx) * k + x);
		d = (int) ((wireframe[(++i) - 1] - cx) * k + y);

		bresenham(a, b, c, d, fb);

	}

	for (i = (yMin - cx) * k + y; i <= (yMax - cx) * k + y; i++) {
		cout << i << " > ";
		for (vector<int>::const_iterator c = (dots[i]).begin(); c != (dots[i]).end(); ++c)
    		cout << *c << " | ";
    	cout << "." << endl;
	}
}

void Polygon::setMultiplication(float k) {
	this->k = k;
}

float Polygon::getMultiplication() {
	return k;
}


// Private Methods

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

void Polygon::bresenham(int x1, int y1, int x2, int y2, FrameBuffer *fb) {
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

/*  (dots[y1]).push_back(x1);
  sort((dots[y1]).begin(), (dots[y1]).end());
  fb->plot(x1, y1);*/

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
  
  	//if ( ((x != x1) && (y != y1)) && ((x != x2) && (y != y2)) ) {
    (dots[y]).push_back(x);
    // (dots[y]).push_back(x);
    sort((dots[y]).begin(), (dots[y]).end());
    fb->plot(x, y);
	//}

  }
}
