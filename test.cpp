#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include <vector>

#include "shape.h"
#include <iostream>
using namespace std;

const unsigned char
red[] = {255,0,0},
white[] = {255,255,255};

TEST_CASE("Test is_inside() Cercle", "[Shape]")
{

    Shape *c = new Circle(0,0,60,red);
    REQUIRE(c->isInside(0,0)==true);
    REQUIRE(c->isInside(100,100)==false);

}

TEST_CASE("Test is_inside() Rectangle", "[Shape]")
{

    Shape *r = new Rectangle(0,0,40,40,red);
    REQUIRE(r->isInside(0,10)==true);
    REQUIRE(r->isInside(2,100)==false);

}

TEST_CASE("Test is_inside() Triangle", "[Shape]")
{

   Shape *t =  new Triangle(0,0,10,50,100,200, red);
    REQUIRE(t->isInside(0,0)==true);
    REQUIRE(t->isInside(0,-1)==false);

}

TEST_CASE("Test is_inside() ShapeGroup", "[Shape]")
{
    Shape *c = new Circle(0,0,60,red);
    Shape *t =  new Triangle(0,0,10,50,100,200, red);
    ShapeGroup *g =  new ShapeGroup(0,0, red);
    g->addShape(c);
    g->addShape(t);
    REQUIRE(t->isInside(0,0)==true);
    REQUIRE(t->isInside(0,-1)==false);

}


TEST_CASE("Test move() Cercle", "[Shape]")
{

    Shape *c = new Circle(0,0,60,red);
    c->select(true);
    c->move(1,1);
    REQUIRE(c->getTabs()==1);
    REQUIRE(c->getTord()==1);

}

TEST_CASE("Test move() Rectangle", "[Shape]")
{

    Shape *r = new Rectangle(0,0,40,40,red);
    int xcentre = (40+40)/4;
    int ycentre = (40+40)/4;
    r->select(true);
    r->move(50,50);
    REQUIRE(r->getTabs()==(50-xcentre));
    REQUIRE(r->getTord()==(50-ycentre));

}

TEST_CASE("Test move() Triangle", "[Shape]")
{

   Shape *t =  new Triangle(0,0,10,50,100,200, red);
    int xcentre = (10+100)/3;
    int ycentre = (50+200)/3;
    t->select(true);
    t->move(50,50);
    REQUIRE(t->getTabs()==(50-xcentre));
    REQUIRE(t->getTord()==(50-ycentre));

}

TEST_CASE("Test move() ShapeGroup", "[Shape]")
{

    Shape *c = new Circle(0,0,60,red);
    Shape *t =  new Triangle(0,0,10,50,100,200, red);
    ShapeGroup *g =  new ShapeGroup(0,0, red);
    g->addShape(c);
    g->addShape(t);
    g->getShapes().at(0)->select(true);
    g->move(50,50);
    REQUIRE(g->getShapes().at(0)->getTabs()==(50));
    REQUIRE(g->getShapes().at(0)->getTord()==50);

}

/*=========================================================iSelect()==============================================*/

TEST_CASE("Test select() Circle", "[Shape]")
{

    Shape *c = new Circle(0,0,60,red);
    REQUIRE(c->isSelected()==false);
    c->select(true);
    REQUIRE(c->isSelected()==true);
    

}

TEST_CASE("Test select() Triangle", "[Shape]")
{

    Shape *t =  new Triangle(0,0,10,50,100,200, red);
    REQUIRE(t->isSelected()==false);
    t->select(true);
    REQUIRE(t->isSelected()==true);
    

}

TEST_CASE("Test select() Rectangle", "[Shape]")
{

    Shape *r = new Rectangle(0,0,40,40,red);
    REQUIRE(r->isSelected()==false);
    r->select(true);
    REQUIRE(r->isSelected()==true);
}


