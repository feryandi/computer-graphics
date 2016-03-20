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

void Point::rotate(float degree, int center_x, int center_y, int posX, int posY ){
      double val = PI/180.0;
      int absX = x + posX;
      int absY = y + posY;
      // std::cout<<"before: "<<"x= "<<x<<" y= "<<y<<std::endl;
      newX = ( cos(degree * val) * (x-center_x) - sin(degree * val) * (y-center_y) + center_x );
      newY = ( sin(degree * val) * (x-center_x) + cos(degree * val) * (y-center_y) + center_y );
      // std::cout<<"after: "<<"x= "<<x<<" y= "<<y<<std::endl;
      x = absX - posX;
      y = absY - posY;
}