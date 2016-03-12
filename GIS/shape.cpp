#include "shape.hpp"
#include <vector>

Shape::Shape(){

}

Shape::~Shape() {

}

std::vector<BezierCurve> Shape::getCurves() {

}

std::vector<Polygon> Shape::getPolygons() {
	
}

std::vector<Text> Shape::getTexts() {
	
}

double Shape::getFirePoint() {
	return firePoint;
}

void Shape::setFirePoint(double fp) {
	firePoint = fp;
}

double Shape::getX() {
	return x;
}

double Shape::getY() {
	return y;
}

double Shape::getZ() {
	return z;
}

void Shape::moveX(int movement) {
	x += movement;
}

void Shape::moveY(int movement) {
	y += movement;
}

void Shape::moveZ(int movement) {
	z += movement;	
}

void Shape::draw(char* buffer) {
	
}