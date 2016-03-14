  #include "line.hpp"

  Line::Line();
  Line::Line(std::vector<Point> _points);
  Line::~Line();

  // getter & setter
  std::vector<Point> Line::getPoints(){
    return points;
  }
  double Line::getX(){
    return x;
  }
  double Line::getY(){
    return y;
  }
  double Line::getZ(){
    return z;
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

  }
  void Line::moveY(int movement){

  }
  void Line::moveZ(int movement){

  }
  void Line::draw(char* buffer){

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
  void Line::bresenham(int x1, int y1, int x2, int y2, int red, int green, int blue, int line){
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

      frame_buffer::plot(x, y, red, green, blue);

    }
  }