#include "reader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Shape& Reader::read(const char* filename) {

  std::fstream inputFile;
  inputFile.open(filename);

  std::vector<Line> lines;
  std::vector<BezierCurve> curves;
  int r,g,b;

  while (!inputFile.eof()){
    char command;
    inputFile >> command;

    if (!inputFile.eof()){

      std::string data;
      getline(inputFile, data);

      std::stringstream data_stream(data);

      if (command == 'c') {

        BezierCurve s = parseBezierCurve(data_stream);
        curves.push_back(s);


      } else if (command == 'l') {

        Line l = parseLine(data_stream);
        lines.push_back(l);

      } else if (command == 'w') {

        data_stream >> r >> g >> b;
        std::cout << r << std::endl;
        std::cout << g << std::endl;
        std::cout << b << std::endl;


      }

    }

  }

  inputFile.close();

  Shape *s = new Shape();

  for (int i=0;i<curves.size();i++){
    curves[i].setR(r);
    curves[i].setG(g);
    curves[i].setB(b);
  }

  for (int i=0;i<lines.size();i++){
    lines[i].setR(r);
    lines[i].setG(g);
    lines[i].setB(b);
  }

  s->setCurves(curves);
  s->setLines(lines);
  
  // Biar jadi relative
  //s->moveX(-1* s->positionPoint.getX());
  //s->moveY(-1* s->positionPoint.getY());
  //s->moveZ(-1* s->positionPoint.getZ());

  return *s;
}

BezierCurve& Reader::parseBezierCurve(std::stringstream& input){
  BezierCurve *s = new BezierCurve();

  int x,y;

  while (!input.eof()) {
    input >> x >> y;
    s->addControlPoint(Point(x,y));
  }

  return *s;
}

Line& Reader::parseLine(std::stringstream& input){
  Line *s = new Line();

  int x1,x2,y1,y2;
  input >> x1 >> y1 >> x2 >> y2;

  s->addPoint(Point(x1,y1));
  s->addPoint(Point(x2,y2));

  return *s;
}
