#include "Polygon.class.hpp"

using namespace std;

Polygon::Polygon() {
	x = 0;
	y = 0;
	z = 0;
	k = 1;

	r = 0;
	g = 0;
	b = 0;
}

Polygon::~Polygon() {

}

int Polygon::getX() { return x; }
int Polygon::getY() { return y; }
int Polygon::getZ() { return z; }
void Polygon::setPosition(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Polygon::movePosition(int x, int y, int z) {
	this->x += x;
	this->y += y;
	this->z += z;
}

void Polygon::setMultiplication(float k) {
	this->k = k;
}

void Polygon::setColor(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

int Polygon::getColorRed() { return r; }
int Polygon::getColorBlue() { return g; }
int Polygon::getColorGreen() { return b; }

void Polygon::addPoint(Point P, int t) {
	/* t adalah penanda
	   0 = titik berdiri sendiri 
	   1 = titik berhubungan dengan titik selanjutnya pada vector */
	points.push_back(make_pair(P, t));
}

void Polygon::addPoint(int x, int y, int z, int t) {
	Point P = Point(x, y, z);
	points.push_back(make_pair(P, t));
}

Point* Polygon::getPoint(int n) { return &((points.at(n)).first); }
int Polygon::getPointX(int n) { return ( getPoint(n)->getX() * k + x ); }
int Polygon::getPointY(int n) { return ( getPoint(n)->getY() * k + y ); }
int Polygon::getPointZ(int n) { return ( getPoint(n)->getZ() * k + z ); }
int Polygon::getPointType(int n) { return (points.at(n)).second; }
int Polygon::getPointCount() { return points.size(); }

void Polygon::movePoint(int n, int x, int y, int z) {
	getPoint(n)->moveX(x/k);
	getPoint(n)->moveY(y/k);
	getPoint(n)->moveZ(z/k);
}