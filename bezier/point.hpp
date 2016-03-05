class Point{
public:
  // ctor
  Point();
  Point(int _x, int _y);

  // getter & setter
  int getX();
  int getY();
  void setX(int _x);
  void setY(int _x);

  // methods
  void moveX(int _x);
  void moveY(int _y);

private:
  // point coordinates
  int x;
  int y;
};
