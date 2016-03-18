#ifndef TEXT_H
#define TEXT_H

#include <string>

class Text {
public:
  // ctor & dtor
  Text();
  ~Text();

  //getter & setter
  std::string getText();
  void setText(std::string _text);
  double getX();
  double getY();
  double getZ();
  void setX(double _x);
  void setY(double _y);
  void setZ(double _z);
  
  // methods
  void moveX(int movement);
  void moveY(int movement);
  void moveZ(int movement);
  void draw(FrameBuffer& buffer);

private:
  double x,y,z;
  std::string text;
};

#endif
