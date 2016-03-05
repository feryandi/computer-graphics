#include "Polygon.class.h"

using namespace std;

Polygon::Polygon(int cx, int cy, int cz, int* w, int len) {
	x = 0;
	y = 0;
	z = 0;
	k = 1;
  degreeX = 0;
  degreeY = 0;
  degreeZ = 0;

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
  if (axis == 0) {
    degreeX = degreeX + degree;
  }else if (axis == 1){
    degreeY = degreeY + degree;
  }
  else if (axis == 2){
   degreeZ = degreeZ + degree;
  }

  if(len % 3 == 0){
    double val = PI/180.0;

    for (int i = 0; i < len; i=i+3){
      float ox = original[i], oy = original[i+1], oz = original[i+2];
      
      /*if (axis == 0) {
        degreeX = degreeX + degree;
        printf("degreeX: %f\n", degreeX);
      }else if (axis == 1){
        degreeY = degreeY + degree;
        printf("degreeY: %f\n", degreeY);
      }
      else if (axis == 2){
        degreeZ = degreeZ + degree;
        printf("degreeZ: %f\n", degreeZ);
      }*/      

      wireframe[i+1] = (float) ( cos(degreeX * val) * (oy-cy) - sin(degreeX*val) * (oz-cz) + cy );
      wireframe[i+2] = (float) ( sin(degreeX * val) * (oy-cy) + cos(degreeX * val) * (oz-cz) + cz );
      oy = wireframe[i+1]; oz = wireframe[i+2];

      wireframe[i] = (float) ( cos(degreeY * val) * (ox-cx) - sin(degreeY*val) * (oz-cz) + cx );
      wireframe[i+2] = (float) ( sin(degreeY * val) * (ox-cx) + cos(degreeY * val) * (oz-cz) + cz );
      ox = wireframe[i]; oz = wireframe[i+2];

      wireframe[i] = (float) ( cos(degreeZ * val) * (ox-cx) - sin(degreeZ*val) * (oy-cy) + cx );
      wireframe[i+1] = (float) ( sin(degreeZ * val) * (ox-cx) + cos(degreeZ * val) * (oy-cy) + cy );
      //ox = wireframe[i]; oy = wireframe[i+1];
    }

    computeMiddle();

  } else {
    printf("Error: NOT A 3D POLYGON");
  }

}

float Polygon::getDegreeX() {
  return degreeX;
}

float Polygon::getDegreeY() {
  return degreeY;
}

float Polygon::getDegreeZ() {
  return degreeZ;
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
