#include "group.hpp"

Group::Group(){
	visible = 1;
}

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

/*void Group::setX(double _x){
  x = _x;
  for (uint i = 0; i < shapes.size(); ++i)
	{
		shapes[i].setX(_x);
	}
}
void Group::setY(double _y){
  y = _y;
  for (uint i = 0; i < shapes.size(); ++i)
	{
		shapes[i].setY(_y);
	}
}
void Group::setZ(double _z){
  z= _z;
  for (uint i = 0; i < shapes.size(); ++i)
	{
		shapes[i].setZ(_z);
	}
}*/

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

	if (visible) {
	  for (uint i = 0; i < shapes.size(); ++i)
		{
			shapes[i].draw(fb);
	  		shapes[i].fill(fb);
		}
	}
}

void Group::hide() {
	visible = 0;
}

void Group::show() {
	visible = 1;
}

void Group::add(const Shape &s) {
	shapes.push_back(s);
}

void Group::addList(const std::vector<Shape> &s) {
	shapes = s;
}
