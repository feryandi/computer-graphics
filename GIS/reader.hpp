#ifndef __READER_H__
#define __READER_H__

#include "shape.hpp"
#include <string>

class Reader {
public:
	Reader(){};

	std::vector<Shape>& read(const char*);
private:
	BezierCurve& parseBezierCurve(std::stringstream&);
	Line& parseLine(std::stringstream&);
	Shape& createShape(std::vector<Line>, std::vector<BezierCurve>,
                           int, int, int, 
                           int, int, int,
                           int, int,
                           int, int, int);
};

#endif