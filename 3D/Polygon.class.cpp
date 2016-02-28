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
          wireframe[i] = (int) ( cos(d * val) * (original[i] - cy) - ( sin(d*val) * ((original)[i+1] - cz) ) + cy );
        } else {
          wireframe[i] = (int) ( sin(d * val) * (original[i-1] - cy) + cos(d * val) * (original[i] - cz) + cz );
        }
      }
      else if (axis == 1){
        if(i % 3 == 0){
          wireframe[i] = (int) ( cos(d * val) * (original[i] - cx) - ( sin(d*val) * ((original)[i+2] - cz) ) + cx );
        } else if ( i % 3 == 1){ 
          // do nothing
        } else {
          wireframe[i] = (int) ( sin(d * val) * (original[i-2] - cx) + cos(d * val) * (original[i] - cz) + cz );
        } 
      }
      else { // axis == 2
        if(i % 3 == 0){
          wireframe[i] = (int) ( cos(d * val) * (original[i] - cx) - ( sin(d*val) * ((original)[i+1] - cy) ) + cx );
        } else if ( i % 3 == 1){ 
          wireframe[i] = (int) ( sin(d * val) * (original[i-1] - cx) + cos(d * val) * (original[i] - cy) + cy );
        } else {
          // do nothing
        } 
      }
    }   
  } else {
    printf("Error: NOT A 3D POLYGON");
  }

}

float Polygon::getDegree() {
  return d;
}

void Polygon::setWireframe(int* w, int len) {
  wireframe = new int[len];
	wireframe = intdup(w, len);

	this->len = len;
  nLine = len / 6; // 2D = 4, 3D = 6

  //printf("print wireframe:\n");
  //for (int i = 0; i < this->len; i++){
  	//printf("%d, ", wireframe[i]);
  //}  
  //printf("\n");
  oosMap = (int**) malloc(nLine*sizeof(int*));
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

void Polygon::draw(FrameBuffer *fb) {
  int line = 0;

  int yMax = *(wireframe + 1);
  int yMin = *(wireframe + 1);

  while (line < nLine) {
  	//printf("line ke: %d\n",line);

    int x1, y1, x2, y2;
    int dummyz1, dummyz2;
		x1 = (int) ((wireframe[(line*6 + 0)] - cx) * k + x); //printf("x1: %d\n",x1);
		y1= (int) ((wireframe[(line*6 + 1)] - cy) * k + y); //printf("y1: %d\n",y1);
		//z1= (int) ((wireframe[(line*6 + 2)] - cz) * k + z); printf("dummyz1: %d\n",dummyz1);
		x2 = (int) ((wireframe[(line*6 + 3)] - cx) * k + x); //printf("x2: %d\n",x2);
		y2 = (int) ((wireframe[(line*6 + 4)] - cy) * k + y); //printf("y2: %d\n",y2);
		//z2= (int) ((wireframe[(line*6 + 5)] - cz) * k + z); printf("dummyz2: %d\n",dummyz2);

    if (yMax < std::max(y1,y2)) yMax = std::max(y1,y2);
    if (yMin > std::min(y1,y2)) yMin = std::min(y1,y2);

		bresenham(x1, y1, x2, y2, wireRed, wireGreen, wireBlue, line, fb);

    line++;
	}

  fill(yMin, yMax, fb); //ini jadi wireframe kalo dicomment gini
  clearMap();

}


// Private Methods

int* Polygon::intdup(int const * src, size_t len) {
	int* p = (int*) malloc(len * sizeof(int));
	memcpy(p, src, len * sizeof(int));
	return p;
}

// // Bresenham

int Polygon::iabs(int n){
  int const mask = n >> (sizeof(int) * 8 - 1);
  return ((n + mask) ^ mask);
}

int Polygon::F(int X, int Y, int Z) {//Z BUKAN UNTUK 3D
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

void Polygon::bresenham(int x1, int y1, int x2, int y2, int red, int green, int blue, int line, FrameBuffer *fb) {
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

  fb->plot(x1, y1, red, green, blue);

  int x = x1;
  int y = y1;
  
  int** oosElement = &oosMap[line];
  *oosElement = (int*) malloc((iabs(y2-y1)+2)*sizeof(int));
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
  
    (*oosElement)[iabs(y - y1)] = x;
    fb->plot(x, y, red, green, blue);	

  }
}

int Polygon::getLineX1(int e) {
  return (*(wireframe + (e*6) + 0) - cx) * k + x;
}

int Polygon::getLineY1(int e) {
  return (*(wireframe + (e*6) + 1) - cy) * k + y;
}

//int Polygon::getLineZ1(int e) {
//  return (*(wireframe + (e*6) + 2) - cy) * k - z;
//}

int Polygon::getLineX2(int e) {
  return (*(wireframe + (e*6) + 3) - cx) * k + x;
}

int Polygon::getLineY2(int e) {
  return (*(wireframe + (e*6) + 4) - cy) * k + y;
}

//int Polygon::getLineZ2(int e) {
//  return (*(wireframe + (e*6) + 5) - cz) * k + z;
//}

// // Scanline
void Polygon::clearMap(){
  for (int i = 0; i < nLine; ++i)
    free(oosMap[i]);
}

int Polygon::isIntersect(int e, int yScanline){
  int y1E = getLineY1(e);
  int y2E = getLineY2(e);

  return ((y1E - yScanline)*(y2E - yScanline)) <= 0;
}

int Polygon::isHorizontalLine(int e){
  int y1E = getLineY1(e);
  int y2E = getLineY2(e);

  return (y1E == y2E);
}

int Polygon::getMiddleX(int e){
  int x1E = getLineX1(e);
  int x2E = getLineX2(e);

  return (x1E + x2E) >> 1;
}

int Polygon::isCriticalPoint(int e1, int e2, int yScanline){
  int y1E1 = getLineY1(e1);
  int y2E1 = getLineY2(e1);
  int y1E2 = getLineY1(e2);
  int y2E2 = getLineY2(e2);

  int yOuterE1 = y1E1 + y2E1 - yScanline;
  int yOuterE2 = y1E2 + y2E2 - yScanline;

  return ((yOuterE1 - yScanline)*(yOuterE2 - yScanline)) >= 0;
}

int Polygon::xIntersect(int e, int yScanline){
  int y1E = getLineY1(e);

  return oosMap[e][iabs(yScanline - y1E)];
}

void Polygon::fill(int yMin, int yMax, FrameBuffer *fb){
  
  for (int yScanline = yMin; yScanline <= yMax; ++yScanline) {

    // printf("y: %d\n", yScanline);    
    // fflush(stdout);

    std::vector<intersection> intersectEdge; 
    for (int e = 0; e < nLine; ++e) {
      if (isIntersect(e, yScanline)) {
        int type = isHorizontalLine(e);
        int x;
        if (type) {
          x = getMiddleX(e);
        } else {
          x = xIntersect(e, yScanline);
        }
        intersectEdge.push_back(intersection(e, x, type));
      }
    }

    std::sort(intersectEdge.begin(), intersectEdge.end());

    std::vector<intersection>::iterator i = intersectEdge.begin(), j;

    if (i!=intersectEdge.end()) {
      while ((i+1) != intersectEdge.end()) {
        if ((((i+1)->x - i->x) < 5) &&
          (!isCriticalPoint((*i).edge,(*(i+1)).edge, yScanline))) {
          
          i = intersectEdge.erase(i);

        } else {
          if ((i+1)->type == 1) {

            // warning: this conditional maybe cause a bug
            if ((i+2) != intersectEdge.end()) {
              if (isCriticalPoint((*i).edge,(*(i+2)).edge, yScanline)) {
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

    for (int i = 0; i+1 < intersectEdge.size(); i+=2) {
      int e = intersectEdge[i].edge;
      for (int x = intersectEdge[i].x; x < intersectEdge[i+1].x; x++) {
        fb->plot(x, yScanline, fillRed, fillGreen, fillBlue);
      }
    }

  }
}
