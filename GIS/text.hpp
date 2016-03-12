#ifndef TEXT_H
#define TEXT_H

class Text {
public:
  // ctor & dtor
  Text();
  ~Text();

  //getter & setter
  char* getText();
  void setText(char* _text);
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
  void draw(char* buffer);

private:
  double x,y,z;
  char* text;
};

#endif
