#include "Point.class.hpp"

Point::Point(){
  x = 0;
  y = 0;
  z = 0;
}

Point::Point(float _x, float _y, float _z){
  x = _x;
  y = _y;
  z = _z;
}

float Point::getX(){
  return x;
}

float Point::getY(){
  return y;
}

float Point::getZ(){
  return z;
}

void Point::setX(float _x){
  x = _x;
}

void Point::setY(float _y){
  y = _y;
}

void Point::setZ(float _z){
  z = _z;
}

void Point::moveX(float _x){
  x += _x;
}

void Point::moveY(float _y){
  y += _y;
}

void Point::moveZ(float _z){
  z += _z;
}
