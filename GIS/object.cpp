#include "object.hpp"

Object::Object() {

}

Object::~Object() {

}

// getter & setter
std::vector<BezierCurve> Object::getCurves() const {
	return curves;
}

std::vector<Line> Object::getLines() const {
	return lines;
}

std::vector<Text> Object::getTexts() const {
	return texts;
}

std::vector<Shape> Object::getShapes() const {
	return shapes;
}

double Object::getX() const {
	return x;
}

double Object::getY() const {
	return y;
}

double Object::getZ() const {
	return z;
}

void Object::setX(double _x) {
	x = _x;
}

void Object::setY(double _y) {
	y = _y;
}

void Object::setZ(double _z) {
	z = _z;
}

// methods
void Object::moveX(double movement) {
	x += movement;
}

void Object::moveY(double movement) {
	y += movement;
}

void Object::moveZ(double movement) {
	z += movement;
}

void Object::draw(FrameBuffer &fb) {
  for (int i = 0; i < curves.size(); ++i)
	{
		curves[i].draw(fb);
	}

	for (int i = 0; i < lines.size(); ++i)
	{
		lines[i].draw(fb);
	}

  for (int i = 0; i < shapes.size(); ++i)
	{
		shapes[i].draw(fb);
	}

  // TODO draw text lopp
}
