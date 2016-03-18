#include "group.hpp"

Group::Group(){}
Group::~Group(){}

double Group::getX(){
  return x;
}
double Group::getY(){
  return y;
}
double Group::getZ(){
  return z;
}
void Group::setX(double _x){
  x = _x;
  for (uint i = 0; i < objects.size(); ++i)
	{
		objects[i].setX(_x);
	}
}
void Group::setY(double _y){
  y = _y;
  for (uint i = 0; i < objects.size(); ++i)
	{
		objects[i].setY(_y);
	}
}
void Group::setZ(double _z){
  z= _z;
  for (uint i = 0; i < objects.size(); ++i)
	{
		objects[i].setZ(_z);
	}
}

void Group::moveX(int movement){
  x += movement;
  for (uint i = 0; i < objects.size(); ++i)
	{
		objects[i].moveX(movement);
	}
}
void Group::moveY(int movement){
  y += movement;
  for (uint i = 0; i < objects.size(); ++i)
	{
		objects[i].moveY(movement);
	}
}
void Group::moveZ(int movement){
  z += movement;
  for (uint i = 0; i < objects.size(); ++i)
	{
		objects[i].moveZ(movement);
	}
}
void Group::draw(FrameBuffer &fb){
  for (uint i = 0; i < objects.size(); ++i)
	{
		objects[i].draw(fb);
	}
}
