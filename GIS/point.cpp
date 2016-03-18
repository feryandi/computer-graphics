#include "point.hpp"

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

void Point::rotate(float degree, Point center){

}
