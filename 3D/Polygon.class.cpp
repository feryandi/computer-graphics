#include "Polygon.class.h"

using namespace std;

Polygon::Polygon(int cx, int cy, int cz, int* w, int len) {
	x = 0;
	y = 0;
	z = 0;
	k = 1;

  wireRed = 255;
  wireGreen = 255;
  wireBlue = 255;

  fillRed = 255;
  fillGreen = 255;
  fillBlue = 255;

	setCenter(cx, cy, cz);
	original = intdup(w, len);
	setWireframe(original, len);
}

Polygon::~Polygon() {
	delete [] original;
	delete [] wireframe;
}

int Polygon::getX() {
	return x;
}

int Polygon::getY() {
	return y;
}

int Polygon::getZ() {
	return z;
}

void Polygon::setPosition(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

int Polygon::getCX() {
	return cx;
}

int Polygon::getCY() {
	return cy;
}

int Polygon::getCZ() {
	return cz;
}

void Polygon::setCenter(int cx, int cy, int cz) {
	this->cx = cx;
	this->cy = cy;
	this->cz = cz;
}

void Polygon::setMultiplication(float k) {
  this->k = k;
}

float Polygon::getMultiplication() {
  return k;
}

void Polygon::setDegree(float degree, int axis) {
  this->d = degree;

  //int *temp = (int*)malloc(len * sizeof(int));
  if(len % 3 == 0){
    double val = PI/180.0;
    for (int i = 0; i < len; i++){
      /*if(i % 3 == 0){
        wireframe[i] = (int) ( cos(d * val) * (original[i] - cx) - ( sin(d*val) * ((original)[i+1] - cy) ) + cx );
        printf("x[%d]: %d, ", i, wireframe[i]);
      } else if ( i % 3 == 1){
        wireframe[i] = (int) ( sin(d * val) * (original[i-1] - cx) + cos(d * val) * (original[i] - cy) + cy ) ;
        printf("y[%d]: %d, ", i, wireframe[i]);
      } else{
      	wireframe[i] = wireframe[i];
      	printf("z[%d]: %d\n", i, wireframe[i]);
      	//do nothing yet, this is for z
      }*/
      /* do based on axis (x=0, y=1, z=2) */
      if (axis == 0)
      {
        if(i % 3 == 0){
          // do nothing
        } else if ( i % 3 == 1){
          wireframe[i] = (float) ( cos(d * val) * (original[i] - cy) - ( sin(d*val) * ((original)[i+1] - cz) ) + cy );
        } else {
          wireframe[i] = (float) ( sin(d * val) * (original[i-1] - cy) + cos(d * val) * (original[i] - cz) + cz );
        }
      }
      else if (axis == 1){
        if(i % 3 == 0){
          wireframe[i] = (float) ( cos(d * val) * (original[i] - cx) - ( sin(d*val) * ((original)[i+2] - cz) ) + cx );
        } else if ( i % 3 == 1){
          // do nothing
        } else {
          wireframe[i] = (float) ( sin(d * val) * (original[i-2] - cx) + cos(d * val) * (original[i] - cz) + cz );
        }
      }
      else { // axis == 2
        if(i % 3 == 0){
          wireframe[i] = (float) ( cos(d * val) * (original[i] - cx) - ( sin(d*val) * ((original)[i+1] - cy) ) + cx );
        } else if ( i % 3 == 1){
          wireframe[i] = (float) ( sin(d * val) * (original[i-1] - cx) + cos(d * val) * (original[i] - cy) + cy );
        } else {
          // do nothing
        }
      }
    }

    computeMiddle();

  } else {
    printf("Error: NOT A 3D POLYGON");
  }

}

float Polygon::getDegree() {
  return d;
}

void Polygon::computeMiddle() {
  int xmax, ymax, zmax, xmin, ymin, zmin;

  if(nLine>=1){
    xmax = wireframe[0]; ymax = wireframe[1]; zmax = wireframe[2];
    xmin = wireframe[0]; ymin = wireframe[1]; zmin = wireframe[2];

    for (int e = 0; e < nLine; ++e) {
      xmax = max(xmax,max(getLineX1(e),getLineX2(e)));
      ymax = max(ymax,max(getLineY1(e),getLineY2(e)));
      zmax = max(zmax,max(getLineZ1(e),getLineZ2(e)));

      xmin = min(xmin,min(getLineX1(e),getLineX2(e)));
      ymin = min(ymin,min(getLineY1(e),getLineY2(e)));
      zmin = min(zmin,min(getLineZ1(e),getLineZ2(e)));
    }

    mx = float(xmax+xmin);
    my = float(ymax+ymin);
    mz = float(zmax+zmin);
  }
}

void Polygon::setWireframe(int* w, int len) {
  wireframe = new float[len];

  for (int i=0; i<len; i++)
    wireframe[i] = w[i];



	this->len = len;
  nLine = len / 6; // 2D = 4, 3D = 6
  computeMiddle();

  //printf("print wireframe:\n");
  //for (int i = 0; i < this->len; i++){
  	//printf("%d, ", wireframe[i]);
  //}
  //printf("\n");
  //oosMap = (int**) malloc(nLine*sizeof(int*));
}

void Polygon::setWireColor(int r, int g, int b) {
  wireRed = r;
  wireGreen = g;
  wireBlue = b;
}

void Polygon::setFillColor(int r, int g, int b) {
  fillRed = r;
  fillGreen = g;
  fillBlue = b;
}

// Private Methods

int* Polygon::intdup(int const * src, size_t len) {
	int* p = (int*) malloc(len * sizeof(int));
	memcpy(p, src, len * sizeof(int));
	return p;
}


int Polygon::getLineX1(int e) {
  return (*(wireframe + (e*6) + 0) - cx) * k + x;
}

int Polygon::getLineY1(int e) {
  return (*(wireframe + (e*6) + 1) - cy) * k + y;
}

int Polygon::getLineZ1(int e) {
  return (*(wireframe + (e*6) + 2) - cy) * k - z;
}

int Polygon::getLineX2(int e) {
  return (*(wireframe + (e*6) + 3) - cx) * k + x;
}

int Polygon::getLineY2(int e) {
  return (*(wireframe + (e*6) + 4) - cy) * k + y;
}

int Polygon::getLineZ2(int e) {
  return (*(wireframe + (e*6) + 5) - cz) * k + z;
}

int Polygon::getNLine() {
  return nLine;
}


int Polygon::getFillRed(){
  return fillRed;
}
int Polygon::getFillGreen(){
  return fillGreen;
}
int Polygon::getFillBlue(){
  return fillBlue;
}
bool Polygon::isBehind(Polygon* a, Polygon* b){
  return (a->mz > b->mz);
}

bool Polygon::isFront(Polygon* a, Polygon* b){
  return (a->mz < b->mz);
}
