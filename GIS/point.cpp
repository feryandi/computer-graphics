#include "point.hpp"
#include <iostream>

Point::Point(){
  x = 0;
  y = 0;
  z = 0;
}

Point::Point(int _x, int _y){
  x = _x;
  y = _y;
  z = 0;
}

int Point::getX() const {
  return x;
}

int Point::getY() const {
  return y;
}

void Point::setX(int _x){
  x = _x;
}

void Point::setY(int _y){
  y = _y;
}

void Point::setZ(int _z){
  z = _z;
}

void Point::moveX(int _x){
  x += _x;
}

void Point::moveY(int _y){
  y += _y;
}

void Point::moveZ(int _z){
  z += _z;
}

void Point::rotate(float degree, int center_x, int center_y, int posX, int posY){
      double val = PI/180.0;
      int absX = x + posX;
      int absY = y + posY;
      // std::cout<<"before: "<<"x= "<<x<<" y= "<<y<<std::endl;
      int newX = ( cos(degree * val) * (absX-center_x) - sin(degree * val) * (absY-center_y) + center_x );
      int newY = ( sin(degree * val) * (absX-center_x) + cos(degree * val) * (absY-center_y) + center_y );
      // std::cout<<"after: "<<"x= "<<x<<" y= "<<y<<std::endl;
      int newPosX = ( cos(degree * val) * (posX-center_x) - sin(degree * val) * (posY-center_y) + center_x );
      int newPosY = ( sin(degree * val) * (posX-center_x) + cos(degree * val) * (posY-center_y) + center_y );
      x = newX - newPosX;
      y = newY - newPosY;
}