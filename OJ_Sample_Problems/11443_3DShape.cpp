#include <iostream>
#include <string>
//#include "function.h"
using namespace std;
//#ifndef SHAPE_H
#define SHAPE_H

namespace oj
{
	class Shape3D
	{	
		double volume;

	public:
		double getVolume();
	
	protected:
		void setVolume(double volume);
	};



	class Sphere : public Shape3D
	{
		double radius;
		double pi;
	
	public:
		Sphere(double, double);
	};

    Sphere::Sphere(double r,double p){
        radius = r;
        pi = p;
        if(r>0 && p>0){
            double v = 4.0 / 3.0 * p *r *r *r;
            setVolume(v);
        }else{
            setVolume(0);
        }
    }


	class Cone : public Shape3D
	{
		double radius;
		double height;
		double pi;

	public:
		Cone(double, double, double);
	};
    
    Cone::Cone(double r , double h, double p){
        radius =r;
        height = h;
        pi = p;
        if(r>0 && h>0 && p>0){
            setVolume(p*h*r*r/3.0);
        }else{
            setVolume(0);
        }
    }




	class Cuboid : public Shape3D
	{
		double length;
		double width;
		double height;
	
	public:
		Cuboid(double, double, double);
	};
	class Cube : public Cuboid
	{
	public:
		Cube(double);
	};
    Cuboid::Cuboid(double l, double w, double h){
        length = l;
        width = w;
        height = h;
        if(w>0 && l>0 && h>0){
            setVolume(l*w*h);
        }else{
            setVolume(0);
        }
    }
    Cube::Cube(double a): Cuboid(a,a,a){}
}
