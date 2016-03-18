#include "object.hpp"

Object::Object() {

}

Object::~Object() {

}

// getter & setter
std::vector<BezierCurve> Object::getCurves() {
	return curves;
}

std::vector<Line> Object::getLines() {
	return lines;
}

std::vector<Text> Object::getTexts() {
	return texts;
}

std::vector<Shape> Object::getShapes() {
	return shapes;
}

double Object::getX() {
	return x;
}

double Object::getY() {
	return y;
}

double Object::getZ() {
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

void Object::draw(char* buffer) {

}
