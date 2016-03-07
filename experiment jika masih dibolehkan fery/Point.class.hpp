class Point{
public:
  // ctor
  Point();
  Point(float _x, float _y, float _z);

  // getter & setter
  float getX();
  float getY();
  float getZ();
  void setX(float _x);
  void setY(float _y);
  void setZ(float _z);

  // methods
  void moveX(float _x);
  void moveY(float _y);
  void moveZ(float _z);

private:
  // point coordinates
  float x;
  float y;
  float z;
};
