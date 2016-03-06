#include "Polygon.class.hpp"

using namespace std;

Polygon::Polygon() {
	x = 0;
	y = 0;
	z = 0;
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
int Polygon::getPointType(int n) { return (points.at(n)).second; }
int Polygon::getPointCount() { return points.size(); }

void Polygon::movePoint(int n, int x, int y, int z) {
	getPoint(n)->moveX(x);
	getPoint(n)->moveY(y);
	getPoint(n)->moveZ(z);
}