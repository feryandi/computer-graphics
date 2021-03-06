#include "shape.hpp"
#include <vector>
#include <queue>

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
	text = shape.text;

	r = shape.r;
	g = shape.g;
	b = shape.b;

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
	text = shape.text;

	r = shape.r;
	g = shape.g;
	b = shape.b;
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

void Shape::addText(Text t) {
	text = t;
}

void Shape::draw(FrameBuffer &fb) {
	for (uint i = 0; i < curves.size(); ++i)
	{
		curves[i].drawWM(fb, k, centrePoint->getX(), centrePoint->getY());
		//curves[i].draw(fb);
	}

	for (uint i = 0; i < lines.size(); ++i)
	{
		lines[i].drawWM(fb, k, centrePoint->getX(), centrePoint->getY());
	}

	fill(fb);

	if (text.isTextSet()) {
		text.drawWM(fb, k, centrePoint->getX(), centrePoint->getY());
	}
}

void Shape::moveLineX(int i, int movement){
  lines.at(i).moveX(movement);
}

void Shape::moveLineY(int i, int movement){
  lines.at(i).moveY(movement);
}

void Shape::moveLineZ(int i, int movement){
  lines.at(i).moveZ(movement);
}

void Shape::moveCurveX(int i, int movement){
  curves.at(i).moveX(movement);
}

void Shape::moveCurveY(int i, int movement){
  curves.at(i).moveY(movement);
}

void Shape::moveCurveZ(int i, int movement){
  curves.at(i).moveZ(movement);
}

void Shape::moveX(int movement){
	firePoint->moveX(movement);
  for (uint i = 0; i < lines.size(); ++i)
  {
    lines.at(i).moveX(movement);
  }

  for (uint i = 0; i < curves.size(); ++i)
  {
    curves.at(i).moveX(movement);
  }

	if (text.isTextSet()) {
		text.moveX(movement);
	}
}

void Shape::moveY(int movement){
	firePoint->moveY(movement);
  for (uint i = 0; i < lines.size(); ++i)
  {
    lines.at(i).moveY(movement);
  }

  for (uint i = 0; i < curves.size(); ++i)
  {
    curves.at(i).moveY(movement);
  }

	if (text.isTextSet()) {
		text.moveY(movement);
	}
}

void Shape::moveZ(int movement){
	firePoint->moveZ(movement);
  for (uint i = 0; i < lines.size(); ++i)
  {
    lines.at(i).moveZ(movement);
  }

  for (uint i = 0; i < curves.size(); ++i)
  {
    curves.at(i).moveZ(movement);
  }
  
	if (text.isTextSet()) {
		text.moveZ(movement);
	}
}

void Shape::rotate(int degree, int cx, int cy){
	for (uint i=0;i<lines.size();i++){
		lines[i].rotate(degree,cx,cy, positionPoint->getX(), positionPoint->getY());
	}

	for (uint i=0;i<curves.size();i++){
		curves[i].rotate(degree,cx,cy, positionPoint->getX(), positionPoint->getY());
	}

	firePoint->rotate(degree, cx, cy, positionPoint->getX(), positionPoint->getY());
	//centrePoint->rotate(degree, cx, cy, 0, 0);
	positionPoint->rotate(degree,cx,cy, 0, 0);
}

int Shape::isPointValid(FrameBuffer &fb, int x, int y) {
	if ( ( x >= 0 ) &&
		 ( y >= 0 ) &&
		 ( x < fb.getVInfoX() - 1 ) &&
		 ( y < fb.getVInfoY() - 1 ) ) {
		return 1;
	} else {
		return 0;
	}
}

void Shape::fill(FrameBuffer &fb){
	std::queue <Point> qpoints;


	Point newFP;
	newFP.setX((firePoint->getX()-centrePoint->getX())*k+centrePoint->getX());
	newFP.setY((firePoint->getY()-centrePoint->getX())*k+centrePoint->getX());

	qpoints.push(newFP);

	while (qpoints.size() > 0){
		Point current = qpoints.front();
		fb.plot(current.getX(), current.getY(), r,g,b);
		qpoints.pop();

		// TO-DO !!
		//std::cout << current.getY() << " " << current.getX() << std::endl;

		if (isPointValid(fb, current.getX()+1, current.getY())) {
			if (fb.zbuffer[current.getY()][current.getX()+1] == 0){
				qpoints.push(Point(current.getX()+1, current.getY()));
				fb.zbuffer[current.getY()][current.getX()+1] = 1;
			}
		}
		if (isPointValid(fb, current.getX(), current.getY()+1)) {
			if (fb.zbuffer[current.getY()+1][current.getX()] == 0){
				qpoints.push(Point(current.getX(), current.getY()+1));
				fb.zbuffer[current.getY()+1][current.getX()] = 1;
			}
		}

		if (isPointValid(fb, current.getX(), current.getY()-1)) {
			if (fb.zbuffer[current.getY()-1][current.getX()] == 0){
				qpoints.push(Point(current.getX(), current.getY()-1));
				fb.zbuffer[current.getY()-1][current.getX()] = 1;
			}
		}

		if (isPointValid(fb, current.getX()-1, current.getY())) {
			if (fb.zbuffer[current.getY()][current.getX()-1] == 0){
				qpoints.push(Point(current.getX()-1, current.getY()));
				fb.zbuffer[current.getY()][current.getX()-1] = 1;
			}
		}
	}
}
