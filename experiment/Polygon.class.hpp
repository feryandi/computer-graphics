#include <iostream>
#include <vector>
#include "Point.class.hpp"

using namespace std;

class Polygon {
	private:
		int x, y, z;

		vector< pair<Point, int> > points; 

	public:
		Polygon();
		~Polygon();

		int getX();
		int getY();
		int getZ();
		void setPosition(int, int, int);

		void addPoint(Point, int);
		void addPoint(int, int, int, int);

		void movePoint(int, int, int, int);

		Point* getPoint(int);
		int getPointType(int);
		int getPointCount();
};