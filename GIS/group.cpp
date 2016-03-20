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


void Group::moveX(int movement){
  x += movement;
  for (uint i = 0; i < shapes.size(); ++i)
	{
		shapes[i].moveX(movement);
	}
}
void Group::moveY(int movement){
  y += movement;
  for (uint i = 0; i < shapes.size(); ++i)
	{
		shapes[i].moveY(movement);
	}
}
void Group::moveZ(int movement){
  z += movement;
  for (uint i = 0; i < shapes.size(); ++i)
	{
		shapes[i].moveZ(movement);
	}
}
void Group::draw(FrameBuffer &fb){
  for (uint i = 0; i < shapes.size(); ++i)
	{
		shapes[i].draw(fb);
	}
}
