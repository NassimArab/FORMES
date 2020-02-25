#include "CImg.h"
using namespace cimg_library;
#include <iostream>
#include <vector>

#ifndef __SHAPE_H__
#define __SHAPE_H__

class EmptyExc {};

class Shape{
protected:
  int tabs;
  int tord;
  unsigned char color[3];
  bool is_selected;
public:
  Shape();
  Shape(int abs, int ord, unsigned char clr[]);
  ~Shape();
  Shape(const Shape &s);

  virtual void move(int x, int y) =0;
  virtual void draw(CImg<unsigned char>* img, const unsigned char *col) =0;
  virtual bool isInside(int x, int y)=0;
  bool isSelected();
  void select(bool value);
  int getTabs();
  int getTord();
};

class Rectangle: public Shape{
  int twidth;
  int theight;
public:
  Rectangle(int x, int y, int width, int height,const unsigned char clr[]);
  virtual void draw(CImg<unsigned char>* img, const unsigned char *col);
  virtual bool isInside(int x, int y);
  virtual void move(int x, int y);
};


class Circle: public Shape{
  int tradius;
public:
  Circle(int x, int y, int radius,const unsigned char clr[]);
  virtual void draw(CImg<unsigned char>* img, const unsigned char *col);
  virtual bool isInside(int x, int y);
  virtual void move(int x, int y);
};

class Triangle: public Shape{
  int tx1,tx2;
  int ty1,ty2;
public:
  Triangle(int x0,int y0,int x1,int y1,int x2,int y2, const unsigned char clr[]);
  virtual void draw(CImg<unsigned char>* img, const unsigned char *col);
  virtual bool isInside(int x, int y);
  virtual void move(int x, int y);
  float surface(int x, int y, int x1, int y1,int x2, int y2);
};

class ShapeGroup : public Shape {
  std::vector<Shape *> shapes;
public:
  ShapeGroup(int x, int y,const unsigned char clr[]);
  virtual void draw(CImg<unsigned char>* img, const unsigned char *col);
  virtual bool isInside(int x, int y);
  virtual void move(int x, int y);
  void addShape(Shape *p);
  std::vector<Shape *> getShapes();
};


#endif
