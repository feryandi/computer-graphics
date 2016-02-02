#include <stdio.h>
#include <string.h>

using namespace std;

char map[255][255];

void plot(int x, int y) {
  map[y][x] = '#';
}

int iabs(int n){
  int const mask = n >> (sizeof(int) * 8 - 1);
  return ((n + mask) ^ mask);
}

int Fx[] = { 1,  0, -1, 0};
int Fy[] = { 0,  1,  0,-1};

int Gx[] = { 1, -1, -1, 1};
int Gy[] = { 1,  1, -1,-1};

int F(bool X, bool Y, bool Z) {
  if (X & Z) {
    return 0;
  } else if (Y & (not Z)) {
    return 1;
  } else if ((not X) & Z) {
    return 2;
  } else if ((not Y) & (not Z)) {
    return 3;
  }
}

int G(bool X, bool Y) {
  if (X & Y) {
    return 0;
  } else if ((not X) & Y) {
    return 1;
  } else if ((not X) & (not Y)) {
    return 2;
  } else if (X & (not Y)) {
    return 3;
  }
}

void bresenham(int x1, int y1, int x2, int y2) {
  int dx = x2 - x1;
  int dy = y2 - y1;

  bool X = dx > 0;
  bool Y = dy > 0;
  bool Z = (iabs(dx) - iabs(dy)) > 0;

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
  
  plot(x1,y1);

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

    plot(x,y);
  }
}

int main(){
  memset(map, ' ', sizeof(map));

  bresenham(0,0,2,7);

  for (int y = 0; y < 10; ++y) {
    for (int x = 0; x < 10; ++x) {
      printf("%c", map[y][x]);
    }
    printf("\n");
  }

}