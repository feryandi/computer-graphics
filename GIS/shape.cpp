#include "shape.hpp"
#include <vector>

Shape::Shape(){
	k = 1;
    degree = 0;
    firePoint = new Point();
    centrePoint = new Point();
    positionPoint = new Point();
}

Shape::~Shape() {

}

std::vector<BezierCurve> Shape::getCurves() {
	return curves;
}

void Shape::setCurves(std::vector<BezierCurve> crs) {
	curves = crs;
}

std::vector<Line> Shape::getLines() {
	return lines;
}

void Shape::setLines(std::vector<Line> lns) {
	lines = lns;
}

Point Shape::getFirePoint() {
	return *firePoint;
}

void Shape::setFirePoint(Point fp) {
	*firePoint = fp;
}

Point Shape::getCentrePoint() {
	return *centrePoint;
}

void Shape::setCentrePoint(Point cp) {
	delete centrePoint;
	centrePoint = new Point(cp);
}

Point Shape::getPositionPoint() {
	return *positionPoint;
}

void Shape::setPositionPoint(Point pp) {
	delete positionPoint;
	positionPoint = new Point(pp);
}

float Shape::getMultiplication() {
	return k;
}

void Shape::setMultiplication(float _k) {
	k = _k;
}

float Shape::getDegree() {
	return degree;
}

void Shape::setDegree(float _degree) {
	degree = _degree;
}

void Shape::addCurve(BezierCurve bc) {
	curves.push_back(bc);
}

void Shape::addLine(Line l) {
	lines.push_back(l);
}

void Shape::draw(FrameBuffer &fb) {
	for (unsigned int i = 0; i < curves.size(); ++i)
	{
		curves[i].draw(fb);
	}

	for (unsigned int i = 0; i < lines.size(); ++i)
	{
		lines[i].draw(fb);
	}
}