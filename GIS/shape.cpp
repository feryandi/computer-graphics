#include "shape.hpp"
#include <vector>

Shape::Shape(){
	k = 1;
  degree = 0;
  firePoint = new Point();
  centrePoint = new Point();
  positionPoint = new Point();
}

Shape::Shape(const std::vector<BezierCurve> &crs, const std::vector<Line> &lns){
	k = 1;
	degree = 0;
	firePoint = new Point();
  centrePoint = new Point();
  positionPoint = new Point();
	curves = crs;
	lines = lns;

}


Shape::~Shape() {
	delete firePoint;
	delete centrePoint;
	delete positionPoint;
}

Shape& Shape::operator=(const Shape &shape) {
	delete firePoint;
	delete centrePoint;
	delete positionPoint;
	k = shape.k;
	degree = shape.degree;
	firePoint = new Point(shape.getFirePoint().getX(), shape.getFirePoint().getY());
	centrePoint = new Point(shape.getCentrePoint().getX(), shape.getCentrePoint().getY());
	positionPoint = new Point(shape.getPositionPoint().getX(), shape.getPositionPoint().getY());
	curves = shape.curves;
	lines = shape.lines;

	return *this;
}

Shape::Shape(const Shape &shape){
	k = shape.k;
	degree = shape.degree;
	firePoint = new Point(shape.getFirePoint().getX(), shape.getFirePoint().getY());
	centrePoint = new Point(shape.getCentrePoint().getX(), shape.getCentrePoint().getY());
	positionPoint = new Point(shape.getPositionPoint().getX(), shape.getPositionPoint().getY());
	curves = shape.curves;
	lines = shape.lines;
}

std::vector<BezierCurve> Shape::getCurves() const{
	return curves;
}

void Shape::setCurves(const std::vector<BezierCurve> &crs) {
	curves = crs;
}

std::vector<Line> Shape::getLines() const{
	return lines;
}

void Shape::setLines(const std::vector<Line> &lns) {
	lines = lns;
}

Point Shape::getFirePoint() const{
	return *firePoint;
}

void Shape::setFirePoint(Point fp) {
	*firePoint = fp;
}

Point Shape::getCentrePoint() const{
	return *centrePoint;
}

void Shape::setCentrePoint(Point cp) {
	*centrePoint = cp;
}

Point Shape::getPositionPoint() const{
	return *positionPoint;
}

void Shape::setPositionPoint(Point pp) {
	*positionPoint = pp;
}

void Shape::setR(int _r) {
	r = _r;
}

void Shape::setG(int _g) {
	g = _g;
}

void Shape::setB(int _b) {
	b = _b;
}
  
int Shape::getR() {
	return r;
}

int Shape::getG() {
	return g;
}

int Shape::getB() {
	return b;
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
	for (uint i = 0; i < curves.size(); ++i)
	{
		curves[i].draw(fb);
	}

	for (uint i = 0; i < lines.size(); ++i)
	{
		lines[i].draw(fb);
	}
}

void Shape::setAbsoluteToRelative(){

}