#include "shape.h"

#include <vector>
#include <iostream>

using namespace std;
const unsigned char
    red[]   = { 255,0,0 };
const unsigned char
    green[]   = { 0,255,0 };
int main()
{
    std::vector<Shape *> shapes;
    int forme = -1;
    int ShapeSurvoled =-1;
    bool select_forme = false;
    int x = 0, y = 0;
  // Shape *t = new Rectangle(50,50,200, 100,red);
   //shapes.push_back(t);
    //Shape *t1 = new Triangle(50,50,50,180,110,90, red);
    //shapes.push_back(t1);
   /* Shape *c = new Circle(120,120, 80,red);
    shapes.push_back(c);*/
    CImgDisplay main_disp(700, 400, "Main Display", 0);




    bool button_status = false;
    
    while (!main_disp.is_closed()) {
        CImg<unsigned char> img(main_disp.width(),main_disp.height(), 1, 3, 0);
        main_disp.wait(); 
        x = main_disp.mouse_x();    // get the x position of the mouse, relative to the window
        y = main_disp.mouse_y();    // get the x position of the mouse, relative to the window
        bool click = main_disp.button();
        if(main_disp.is_keyR ()){
            shapes.push_back(new Rectangle(main_disp.width()/2,main_disp.height()/2,100, 50,red));
        }else if(main_disp.is_keyC ()){ 
            shapes.push_back(new Circle(main_disp.width()/2,main_disp.height()/2, 40,green));
        }else if(main_disp.is_keyT ()){
            shapes.push_back(new Triangle(main_disp.width()/2,main_disp.height()/2,50,180,110,90, red));
        }else if(main_disp.is_keyM()  && select_forme){
            shapes.at(forme)->move(x,y);
            shapes.at(forme)->select(false);

        }else if(main_disp.is_keyD()  && select_forme){
            shapes.at(forme)->select(false);
            shapes.erase(shapes.begin()+forme);
           
        }else if(main_disp.is_keyG()  && select_forme){
            ShapeGroup *SG = new ShapeGroup(main_disp.width()/2, main_disp.height()/2, red);
            main_disp.wait();
            Shape *s(shapes.at(forme));
            shapes.erase(shapes.begin()+forme);

            SG->addShape(s);
            for (int i=0; i< shapes.size(); i++){
                if(shapes.at(i)->isInside(x,y)){
                  ShapeSurvoled = i;
                 }
            }
            Shape *s1(shapes.at(ShapeSurvoled));
            shapes.erase(shapes.begin()+ShapeSurvoled);

            SG->addShape(s1);
            SG->select(true);
            shapes.push_back(SG);
        }else if(main_disp.is_keyU()  && select_forme){
            Shape *g = shapes.at(forme);
            ShapeGroup * sg = dynamic_cast<ShapeGroup *>( g );
            for(int j=0; j<sg->getShapes().size();j++){
                sg->getShapes().at(j)->select(false);
                shapes.push_back(sg->getShapes().at(j));
            }
            shapes.erase(shapes.begin()+forme);
        }
        for (Shape *p : shapes){
            p->draw(&img, red);
        }
        button_status = button_status xor click;
        if(main_disp.button()){
            int i = -1;
            for (Shape *p : shapes){
                i++;
                if(p->isInside(x,y)){
                    if(!p->isSelected()){
                        p->select(true);
                        select_forme = true;
                        forme = i;
                    }else{
                        p->select(false);
                        select_forme = false;
                    }
                   
                }
                
            }
        }
       img.display(main_disp);
       main_disp. wait(50);

    }
}