#ifndef __READER_H__
#define __READER_H__

#include "shape.hpp"
#include <string>

class Reader {
public:
	Reader(){};

	Shape& read(const char*);
private:
	BezierCurve& parseBezierCurve(std::stringstream&);
	Line& parseLine(std::stringstream&);
};

#endif