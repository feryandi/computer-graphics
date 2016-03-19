  #include "line.hpp"
  #include <iostream>
  Line::Line(){
    r = 255;
    g = 255;
    b = 255;
  }
  Line::Line(std::vector<Point> _points){
    points = _points;
    r = 255;
    g = 255;
    b = 255;
  }

  Line::~Line(){}

  // getter & setter
  std::vector<Point> Line::getPoints() const{
    return points;
  }
  double Line::getX() const{
    return x;
  }
  double Line::getY() const{
    return y;
  }
  double Line::getZ() const{
    return z;
  }

  int Line::getR() const{
    return r;
  }
  int Line::getG() const{
    return g;
  }
  int Line::getB() const{
    return b;
  }

  void Line::setX(double _x){
    x=_x;
  }
  void Line::setY(double _y){
    y=_y;
  }
  void Line::setZ(double _z){
    z=_z;
  }

  void Line::setR(double _r){
    r = _r;
  }
  void Line::setG(double _g){
    g = _g;
  }
  void Line::setB(double _b){
    b = _b;
  }

  // methods
  void Line::addPoint(Point p){
    points.push_back(p);
  }
  void Line::deletePoint(int i){
    points.erase(points.begin()+i);
  }
  void Line::movePointX(int i, int movement){
    points.at(i).moveX(movement);
  }
  void Line::movePointY(int i, int movement){
    points.at(i).moveY(movement);
  }
  void Line::movePointZ(int i, int movement){
    points.at(i).moveZ(movement);
  }
  void Line::moveX(int movement){
    for (int i = 0; i < (int)points.size(); ++i)
    {
      points.at(i).moveX(movement);
    }
  }
  void Line::moveY(int movement){
    for (int i = 0; i < (int)points.size(); ++i)
    {
      points.at(i).moveY(movement);
    }
  }
  void Line::moveZ(int movement){
    for (int i = 0; i < (int)points.size(); ++i)
    {
      points.at(i).moveZ(movement);
    }
  }

  void Line::draw(FrameBuffer &fb){
    bresenham(fb, points[0].getX(), points[0].getY(), points[1].getX(), points[1].getY(),r,g,b,1);
  }

  void Line::rotate(int degree, int cx, int cy){
    for (int i=0;i < (int)points.size();i++){
      points[i].rotate(degree,cx,cy);
    }
  }

  int Line::iabs(int n){
    int const mask = n >> (sizeof(int) * 8 - 1);
    return ((n + mask) ^ mask);
  }
  int Line::F(int X, int Y, int Z){
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
  int Line::G(int X, int Y){
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

  void Line::bresenham(FrameBuffer &fb, int x1, int y1, int x2, int y2, int red, int green, int blue, int line){
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

    //std::cout << this->r << "," << this->g << "," << this->b << std::endl;
    fb.plot(x1, y1, red, green, blue);

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

      fb.plot(x, y, red, green, blue);

    }
  }
