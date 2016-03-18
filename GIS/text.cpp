#include "text.hpp"

Text::Text(){}
Text::~Text(){}

std::string Text::getText() const {
  return text;
}
void Text::setText(std::string &_text){}
double Text::getX() const {
  return x;
}
double Text::getY() const {
  return y;
}
double Text::getZ() const {
  return z;
}
void Text::setX(double _x) {
  x = _x;
}
void Text::setY(double _y) {
  y = _y;
}
void Text::setZ(double _z) {
  z = _z;
}

void Text::moveX(int movement){
  x += movement;
}
void Text::moveY(int movement){
  y += movement;
}
void Text::moveZ(int movement){
  z += movement;
}
void Text::draw(FrameBuffer& buffer){}
