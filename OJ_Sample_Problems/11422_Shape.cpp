#include <iostream>
#include <string>
#include<cmath>
//#include "function.h"
using namespace std;
//#ifndef SHAPE_H
#define SHAPE_H

namespace oj
{
	class Shape 
	{	
	public:
		double getArea();
		double getPerimeter();
	
	protected:
		void setArea(double a);
		void setPerimeter(double p);
			
	private:
		double area;
		double perimeter;
	};

	class Triangle : public Shape
	{
	public:
		Triangle(double edge1, double edge2, double edge3);
		
	private:
		double edge1;
		double edge2;
		double edge3;
		
	};
    Triangle::Triangle(double a,double b, double c){
        edge1 = a;
        edge2 = b;
        edge3 = c;
        if(a+b>c && b+c>a && c+a>b && a>0 && b>0 && c>0){
            double s = (a+b+c)/2;
            setPerimeter(2*s);
            setArea(sqrt(s* (s-a) * (s-b) * (s-c) ));
        }
        else{
            setPerimeter(0);
            setArea(0);
        }
    }

	class Rectangle : public Shape
	{
	public:
		Rectangle(double width, double height);
		
	private:
		double width;
		double height;
	};
    Rectangle::Rectangle(double w,double h){
        width =w;
        height = h;
        if(w>0 && h>0){
            setArea(w*h);
            setPerimeter((w+h) *2); 
        }
        else{
            setPerimeter(0);
            setArea(0);
        }
    }

	class Circle : public Shape
	{
	public:
		Circle(double radius, double pi);
		
	private:
		double radius;
		double pi;
	};
    Circle::Circle(double r, double p){
        radius = r;
        pi = p;
        if(r>0 && p>0){
            setArea(p*r*r);
            setPerimeter(2*p*r);
        }
        else{
            setArea(0);
            setPerimeter(0);
        }
    }
}

