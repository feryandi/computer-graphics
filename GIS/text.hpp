#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "frame_buffer.hpp"

class Text {
public:
  // ctor & dtor
  Text();
  ~Text();

  //getter & setter
  std::string getText() const;
  void setText(std::string &_text);
  double getX() const;
  double getY() const;
  double getZ() const;
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
