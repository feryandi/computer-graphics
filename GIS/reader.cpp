#include "reader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<Shape>& Reader::read(const char* filename) {

  std::fstream inputFile;
  inputFile.open(filename);

  std::vector<Shape> *shapes = new std::vector<Shape>();
  std::vector<Line> lines;
  std::vector<BezierCurve> curves;
  int is_p;
  int r,g,b, px, py, xx, xy;
  int fill_r, fill_g, fill_b;

  while (!inputFile.eof()){
    char command;
    inputFile >> command;

    if (!inputFile.eof()){

      std::string data;
      getline(inputFile, data);

      std::stringstream data_stream(data);

      if (command == '{') {

        r = 0;
        g = 0;
        b = 0;

        px = 0;
        py = 0;
        is_p = 0;

        xx = 0;
        xy = 0;
        fill_r = 255;
        fill_g = 0;
        fill_b = 255;

      } else if (command == 'c') {

        BezierCurve s = parseBezierCurve(data_stream);
        curves.push_back(s);


      } else if (command == 'l') {

        Line l = parseLine(data_stream);
        lines.push_back(l);

      } else if (command == 'w') {

        data_stream >> r >> g >> b;

      } else if (command == 'f') {

        data_stream >> fill_r >> fill_g >> fill_b;

      } else if (command == 'p') {

        data_stream >> px >> py;
        is_p = 1;

      } else if (command == 'x') {

        data_stream >> xx >> xy;

      } else if (command == '}') {

        shapes->push_back(createShape(lines, curves, r, g, b, px, py, is_p, xx, xy, fill_r, fill_g, fill_b));

      }

    }

  }

  inputFile.close();

  return *shapes;
}


Shape& Reader::createShape(std::vector<Line> lines, std::vector<BezierCurve> curves,
                           int r, int g, int b,
                           int px, int py, int is_p,
                           int xx, int xy,
                           int fill_r, int fill_g, int fill_b) {
  Shape *s = new Shape();

  for (uint i=0;i<curves.size();i++){
    curves[i].setR(r);
    curves[i].setG(g);
    curves[i].setB(b);
  }


  for (uint i=0;i<lines.size();i++){
    lines[i].setR(r);
    lines[i].setG(g);
    lines[i].setB(b);
  }

  Point min(10000,10000);
  Point max(-1,-1);

  for (uint i=0;i<lines.size();i++){
    for (uint j=0;j<lines.at(i).getPoints().size();j++){
      if (lines.at(i).getPoints().at(j).getX()<min.getX()){
        min.setX(lines.at(i).getPoints().at(j).getX());
      }
      if (lines.at(i).getPoints().at(j).getY()<min.getY()){
        min.setY(lines.at(i).getPoints().at(j).getY());
      }
    }
  }


  for (uint i=0;i<curves.size();i++){
    for (uint j=0;j<curves.at(i).getPoints().size();j++){
      if (curves.at(i).getPoints().at(j).getX()<min.getX()){
        min.setX(curves.at(i).getPoints().at(j).getX());
      }
      if (curves.at(i).getPoints().at(j).getY()<min.getY()){
        min.setY(curves.at(i).getPoints().at(j).getY());
      }
    }
  }


  s->setCurves(curves);
  s->setLines(lines);

  if ( !is_p ) {
      px = min.getX();
      py = min.getY();
  }

  s->setPositionPoint(Point(px, py));

/*  printf("X nya adalah = %d\n", s->getLines().at(0).getPoints().at(0).getX());
  printf("Y nya adalah = %d\n", s->getLines().at(0).getPoints().at(0).getY());*/

  // Pindahin biar relative
  s->moveX((-1 * min.getX()) + px);
  s->moveY((-1 * min.getY()) + py);

  s->setFirePoint(Point(xx - min.getX() + px, xy - min.getY() + py));

/*  printf("X nya adalah = %d\n", s->getLines().at(0).getPoints().at(0).getX());
  printf("Y nya adalah = %d\n", s->getLines().at(0).getPoints().at(0).getY());*/

  printf("Firepoint = %d, %d\n", s->getFirePoint().getX(), s->getFirePoint().getY());

  // Color Filling
  s->setR(fill_r);
  s->setG(fill_g);
  s->setB(fill_b);

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
