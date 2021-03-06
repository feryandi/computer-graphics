#include <iostream>
#include <vector>
#include "Point.class.hpp"

using namespace std;

class Polygon {
	private:
		int x, y, z;
		float k;

		int r, g, b;

		vector< pair<Point, int> > points; 

	public:
		Polygon();
		~Polygon();

		int getX();
		int getY();
		int getZ();
		void setPosition(int, int, int);
		void movePosition(int, int, int);

		void setMultiplication(float);

		void setColor(int, int, int);
		int getColorRed();
		int getColorBlue();
		int getColorGreen();

		void addPoint(Point, int);
		void addPoint(int, int, int, int);

		void movePoint(int, int, int, int);

		Point* getPoint(int);
		int getPointX(int n);
		int getPointY(int n);
		int getPointZ(int n);

		int getPointType(int);
		int getPointCount();
};