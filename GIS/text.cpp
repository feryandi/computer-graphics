#include "text.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int Text::textCount = 0;
char Text::alphabet[650] = {0};

Text::Text(){

  x = 0;
  y = 0;
  text = "";

  if ( textCount == 0 ) { 
    for (int i = 0; i < 26; i++) {
      char filename[11] = { 'f', 'o', 'n', 't', '/', (char)(i + 97), '.', 't', 'x', 't', '\0'};

      std::fstream inputFile;
      inputFile.open(filename);

      int line = 0;
      while (!inputFile.eof()){
        inputFile >> alphabet[(i * 25) + (line * 5) + 0]
                  >> alphabet[(i * 25) + (line * 5) + 1]
                  >> alphabet[(i * 25) + (line * 5) + 2]
                  >> alphabet[(i * 25) + (line * 5) + 3]
                  >> alphabet[(i * 25) + (line * 5) + 4];
        ++line;
      }
    }
  }

  ++textCount;
  size = 5;

}

Text::~Text(){}

Text::Text(const Text &text) {
  x = text.x;
  y = text.y;
  z = text.z;
  size = text.size;
  this->text = text.text;
}

Text& Text::operator=(const Text &text) {
  x = text.x;
  y = text.y;
  z = text.z;
  size = text.size;
  this->text = text.text;

  return *this;
}

std::string Text::getText() const {
  return text;
}

void Text::setText(std::string _text){
  text = _text;
}

double Text::getX() const {
  return x;
}

double Text::getY() const {
  return y;
}

double Text::getZ() const {
  return z;
}

void Text::setSize(int _s) {
  size = _s;
}

void Text::setX(double _x) {
  x = _x;
}

void Text::setY(double _y) {
  y = _y;
}

void Text::setZ(double _z) {
  z = _z;
}

void Text::moveX(int movement){
  x += movement;
}

void Text::moveY(int movement){
  y += movement;
}

void Text::moveZ(int movement){
  z += movement;
}

int Text::isTextSet() {
  return (text.compare(""));
}

void Text::draw(FrameBuffer& buffer){
  const char* str = text.c_str();

  for (int i = 0; i < (int)strlen(str); i++) {
    //std::cout << "c: " << str[i] << std::endl;
    int sc = ((int)str[i] - 65) * 25;
    plotter(buffer, sc, sc + 24, x + (i*(5*size)) + (i*(size)), y);
  }
}

void Text::plotter(FrameBuffer& buffer, int start, int end, int sx, int sy) {
  int m = 0;
  int n = 0;
  for (int i = start; i <= end; i++) {
    if (alphabet[i] == '1') { 
      buffer.plotWS(sx + (n*size), sy + (m*size), 0, 0, 0, size); 
    }
    ++n;
    if (((i+1) % 5) == 0) { ++m; n = 0; }
  }
}