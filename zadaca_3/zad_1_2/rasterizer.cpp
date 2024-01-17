#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "tgaimage.h"
using namespace std;

const int width  = 512;
const int height = 512;

const TGAColor green = TGAColor(0, 255, 0, 1);
const TGAColor red   = TGAColor(255, 0, 0, 1);
const TGAColor blue  = TGAColor(0, 0, 255, 1);

float func(float xa,float ya,float xc,float yc,float x,float y){
    return((ya-yc)*x+(xc-xa)*y+xa*yc-xc*ya);
}

void draw_triangle_2d(float x0, float y0, float x1, float y1, float x2, float y2 ,TGAImage &image,TGAColor color)
{   
    int najx = ceil (max(max(x0,x1),x2));
    int najmx = floor (min(min(x0,x1),x2));
    int najy = ceil (max(max(y0,y1),y2));
    int najmy = floor(min(min(y0,y1),y2));
   
    float alfa,beta,gama;
    for (int j =najmy; j<=najy ; j++){
        for (int i= najmx;i<=najx;i++){
            
            alfa=func(x1,y1,x2,y2,i,j)/func(x1,y1,x2,y2,x0,y0); //fbc
            beta=func(x2,y2,x0,y0,i,j)/func(x2,y2,x0,y0,x1,y1);  //fca
            gama=func(x0,y0,x1,y1,i,j)/func(x0,y0,x1,y1,x2,y2);  //fab
               
            
            if ((alfa>=0 && beta>=0 && gama>=0) && (alfa<=1 &&beta<=1 &&gama<=1) ) { 
                
                if(( alfa>0 ||((func(x1,y1,x2,y2,x0,y0))*(func(x1,y1,x2,y2,-1,-1))) >=0)
                 &&( beta>0 || ((func(x2,y2,x0,y0,x1,y1))*(func(x2,y2,x0,y0,-1,-1))) >=0)
                 &&( gama>0 || (func(x0,y0,x1,y1,x2,y2))*(func(x0,y0,x1,y1,-1,-1))) >=0){
                        image.set(j, i, color);
                }  
            }
        }
    } 
}


void draw_triangle_2d_gouraurd (float x0, float y0, float x1, float y1, float x2, float y2 ,TGAImage &image,TGAColor c0,TGAColor c1,TGAColor c2){
    int najx = ceil (max(max(x0,x1),x2));
    int najmx = floor (min(min(x0,x1),x2));
    int najy = ceil (max(max(y0,y1),y2));
    int najmy = floor(min(min(y0,y1),y2));
   
    float alpha,beta,gamma;
    TGAColor color;
    for (int j =najmy; j<=najy ; j++){
        for (int i= najmx;i<=najx;i++){
            
            alpha=func(x1,y1,x2,y2,i,j)/func(x1,y1,x2,y2,x0,y0); //fbc
            beta=func(x2,y2,x0,y0,i,j)/func(x2,y2,x0,y0,x1,y1);  //fca
            gamma=func(x0,y0,x1,y1,i,j)/func(x0,y0,x1,y1,x2,y2);  //fab
               
            
            if ((alpha>=0 && beta>=0 && gamma>=0) && (alpha<=1 &&beta<=1 &&gamma<=1) ) { 
                
                if(( alpha>0 ||((func(x1,y1,x2,y2,x0,y0))*(func(x1,y1,x2,y2,-1,-1))) >=0)
                 &&( beta>0 || ((func(x2,y2,x0,y0,x1,y1))*(func(x2,y2,x0,y0,-1,-1))) >=0)
                 &&( gamma>0 || (func(x0,y0,x1,y1,x2,y2))*(func(x0,y0,x1,y1,-1,-1))) >=0){
                        color.b=alpha*c0.b+beta*c1.b+gamma*c2.b;
                        color.g=alpha*c0.g+beta*c1.g+gamma*c2.g;
                        color.r=alpha*c0.r+beta*c1.r+gamma*c2.r;
                        image.set(j, i, color);
                }  
            }
        }
    } 
}

int main()
{
    TGAImage image(width, height, TGAImage::RGB);
    
    draw_triangle_2d(10, 110, 180, 150, 50,240,image, red);
    draw_triangle_2d(300, 200, 400, 150, 350,240,image, blue);
    draw_triangle_2d_gouraurd(300, 200, 200, 100, 100,300,image, blue,red,green);
    
    image.flip_vertically();
    image.write_tga_file("triangle.tga");
}