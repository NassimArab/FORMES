#include "CImg.h"
using namespace cimg_library;

#include "shape.h"
#include <iostream>
#include <cmath>
#include <vector>
 unsigned char
    red[]   = { 255,0,0 };

unsigned char
    white[]   = { 255,255,255 };


Shape::Shape()
{
    is_selected = false;
    tabs = 0;
    tord = 0;
    for (int i = 0; i<3;i++)
        color[i] = red[i];
}

Shape::Shape(int abs, int ord, unsigned char clr[])
{
    is_selected = false;
    tabs = abs;
    tord = ord;
    for (int i = 0; i<3;i++)
        color[i] = clr[i];
}

Shape::~Shape()
{   
    tabs = 0;
    tord = 0;
    delete [] color;
}

Shape::Shape(const Shape &s)
{
    tabs = s.tabs;
    tord = s.tord;
    for (int i = 0; i<3;i++)
        color[i] = s.color[i];
 
}



bool Shape::isSelected(){
    return is_selected;

}

void Shape::select(bool value){
    is_selected = value;
}

int Shape::getTabs(){
    return tabs;
}

int Shape::getTord(){
    return tord;
}

Rectangle::Rectangle(int x, int y, int width, int height,const unsigned char color[]) : Shape(x,y,red), theight(height) , twidth(width) {
 
}

void Rectangle::draw(CImg<unsigned char>*img, const unsigned char *col){
  if(isSelected()){
    img->draw_rectangle(tabs, tord, tabs+twidth, tord+theight, col,1);
    img->draw_rectangle(tabs, tord, tabs+twidth, tord+theight, white,2.0f,0x55555555);

  }else{
    img->draw_rectangle(tabs, tord, tabs+twidth, tord+theight, col,1);
  }
}

bool Rectangle::isInside(int px, int py){
    if((px <= (tabs + twidth)) && (px >= tabs) && (py <= (tord + theight)) && (py >= tord)){
        return true;
    }return false;

}

void Rectangle::move(int x, int y){
    if(isSelected()){
        int cx=(tabs+(tabs+twidth)+tabs+(tabs+twidth))/4;
        int cy=(tord+(tord+theight)+tord+(tord+theight))/4;
        tabs=tabs+(x-cx);
        tord=tord+(y-cy);

    }
}

Triangle::Triangle(int x0,int y0,int x1,int y1,int x2,int y2, const unsigned char clr[]):Shape(x0,y0,red), tx1(x1),tx2(x2), ty1(y1), ty2(y2){
}

void Triangle::draw(CImg<unsigned char>* img, const unsigned char *col)
{  
    if(isSelected()){
        img->draw_triangle ( tabs, tord, tx1, ty1, tx2, ty2,col,1);    
        img->draw_triangle(tabs, tord, tx1, ty1, tx2, ty2, white,2.0f,0x55555555);

    }else{
        img->draw_triangle ( tabs, tord, tx1, ty1, tx2, ty2,col,1);    
  }
  
}




void Triangle::move(int x, int y){
    if(isSelected()){
        int cx=(tabs+tx1+tx2)/3;
        int cy=(tord+ty1+ty2)/3;
        tabs=tabs+(x-cx);
        tord=tord+(y-cy);
        tx1=tx1+(x-cx);
        ty1=ty1+(y-cy);
        tx2=tx2+(x-cx);
        ty2=ty2+(y-cx);
    }
}

float Triangle::surface(int x, int y, int x1, int y1,int x2, int y2)
{
 return abs((x*y1 + x1*y2 + x2*y - x*y2 - x1*y - x2*y1)/2.0);
}

bool Triangle::isInside (int px,int py)
{

    float a= surface(tabs,tord,tx1,ty1,tx2,ty2);


    float a1 = surface(tabs,tord,px,py,tx2,ty2);

    float a2 = surface(tabs,tord,tx1,ty1,px,py);

    float a3 = surface(px,py,tx1,ty1,tx2,ty2);

 return ((a1+a2+a3)==a);
}

	
	
	


Circle::Circle(int x, int y, int radius,const unsigned char clr[]):Shape(x,y,red), tradius(radius)
{
}

bool Circle::isInside (int px,int py)
{
    double distance;
    distance = sqrt( pow((px - tabs), 2 ) + pow( (py - tord), 2 ));
    if(distance <= tradius){
        return true;
    } return false;
}

void Circle::draw(CImg<unsigned char>* img, const unsigned char *col)
{
    if(isSelected()){
        img->draw_circle(tabs, tord, tradius, col , 1);
           img->draw_circle(tabs, tord, tradius, white,2.0f,0x55555555);
    }else{
   img->draw_circle(tabs, tord, tradius, col , 1);
  }

}

void Circle::move(int x, int y){
    if(isSelected()){
     
        tabs = x;
        tord = y;
    }
}

ShapeGroup::ShapeGroup(int x, int y, const unsigned char clr[]):Shape(x,y,red){
 
}

void ShapeGroup::addShape(Shape *p){
    shapes.push_back(p);
}

void ShapeGroup::draw(CImg<unsigned char>* img, const unsigned char *col){
    for(Shape *p : shapes){
        if(isSelected()){
            p->select(true);
            p->draw(img, col);
        }else{
            p->select(false);
            p->draw(img, col);
        }
    }
}
bool ShapeGroup::isInside(int x, int y){
    for(Shape *p : shapes){
        if(p->isInside(x,y)){
            return true;
        }
    }
    return false;
}

void ShapeGroup::move(int x, int y){
    int  i = 0;
    int prx = 0;
    int pry = 0;
    for(Shape *p : shapes){
        if(i==0){
            /*
                Calculer la différence x et y entre la premiere forme et le cursor
            */
            prx = p->getTabs() - x;
            pry = p->getTord() - y;
            p->move(x,y);

        }else{
            /*
                déplacer le reste des formes par le même déplacement que celui de la premiere forme 
            */
            p->move(p->getTabs()-prx,p->getTord()-pry);
        }
        i++;

    }
}


std::vector<Shape *> ShapeGroup::getShapes(){
    return shapes;
}



