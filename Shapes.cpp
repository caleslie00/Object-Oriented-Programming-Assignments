#include "Shapes.h"
#include <cmath>
#include <iostream>
using namespace std;

std::string colorArray[9] = {"BLACK", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", "WHITE", "INVALID"};

//--------------------All Shape functions--------------------
Shape::~Shape() {} //default destructor
Color Shape::colorAtPoint(Shape** A, int numShapes, double xCoord, double yCoord) //returns the color of the first shape encountered in the array
{
	for(int i = 0; i < numShapes; i++)
	{
		if(A[i]->inside(xCoord, yCoord))
			return A[i]->color();
	}
	return INVALID;
}
//--------------------All Box functions--------------------
double Box::perimeter() const //finds the perimeter of a box given it's t,b,r,l
{
	return ((t-b)*2)+((r-l)*2);
}
double Box::area() const //finds the area of a box given it's t,b,r,l
{
	return (t-b)*(r-l);
}
void Box::move(double xChange, double yChange) //moves a box xChange in the x direction and yChange in the y direction
{
	r += xChange;
	l += xChange;
	t += yChange;
	b += yChange;
}
void Box::render(ostream& os) const //draws a box acccording to the prompt
{
	os << "Box(" << colorArray[color()] << "," << l << "," << t << "," << r << "," << b << ")";
}
bool Box::inside(double xCoord, double yCoord) const //returns if the point is inside the box or not
{
	return l < xCoord && xCoord < r && b < yCoord && yCoord < t;
}
//--------------------All Circle functions--------------------
double Circle::perimeter() const //finds the perimeter of a circle given it's r
{
	return 2*M_PI*r;
}
double Circle::area() const //finds the area of a circle given it's r
{
	return M_PI*r*r;
}
void Circle::move(double xChange, double yChange) //moves a circle xChange in the x direction and yChange in the y direction
{
	x += xChange;
	y += yChange;
}
void Circle::render(ostream& os) const //draws a circle according to the prompt
{
	os << "Circle(" << colorArray[color()] << "," << x << "," << y << "," << r << ")";
}
bool Circle::inside(double xCoord, double yCoord) const //returns if the point is inside the circle or not
{
	return (sqrt((xCoord-x)*(xCoord-x)+(yCoord-y)*(yCoord-y))) < r;
}
//--------------------All Triangle functions--------------------
double Triangle::perimeter() const //finds the perimeter of a triangle given it's x1, x2, x3, y1, y2, and y3
{
	double a = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	double b = sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
	double c = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
	return a+b+c;
}
double Triangle::area() const //finds the area of a triangle given it's x1, x2, x3, y1, y2, and y3
{
	// S is perimeter/2
	double s = perimeter()/2;
	double a = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	double b = sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
	double c = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
	return sqrt(s*(s-a)*(s-b)*(s-c));
}
void Triangle::move(double xChange, double yChange) //moves a triangle xChange in the x direction and yChange in the y direction
{
	x1 += xChange;
	x2 += xChange;
	x3 += xChange;
	y1 += yChange;
	y2 += yChange;
	y3 += yChange;
}
void Triangle::render(ostream& os) const //draws a triangle according to the prompt
{
	os << "Triangle(" << colorArray[color()] << "," << x1 << "," << y1 << "," << x2 << "," << y2 << "," << x3 << "," << y3 << ")";
}
bool Triangle::inside(double xCoord, double yCoord) const //returns if the point is inside the triangle or not
{
	Triangle  first(BLACK, xCoord, yCoord, x2, y2, x3, y3);
	Triangle second(BLACK, xCoord, yCoord, x1, y1, x3, y3);
	Triangle  third(BLACK, xCoord, yCoord, x1, y1, x2, y2);
	return first.area()+second.area()+third.area() <= area();
		
}
//--------------------All Polygon functions--------------------
Polygon::Polygon(Color c, double* data, int verticies) : Shape(c) //initializes a polygon
{
	corners = verticies;
	arr = new double[verticies*2];
	for(int i=0; i < verticies*2; i++)
		arr[i] = data[i];
}
Polygon::~Polygon() //deletes a polygon
{
	delete [] arr;
}
double Polygon::perimeter() const //finds the perimeter of a polygon given it's points in array arr and corners, the number of verticies
{
	double sum = 0;
	for(int i = 0; i < corners*2-3; i += 2)
	{
		sum += sqrt((arr[i+2]-arr[i])*(arr[i+2]-arr[i]) + (arr[i+3]-arr[i+1])*(arr[i+3]-arr[i+1]));
	}
	return sum + sqrt((arr[0]-arr[corners*2-2])*(arr[0]-arr[corners*2-2]) + (arr[1]-arr[corners*2-1])*(arr[1]-arr[corners*2-1]));
}
double Polygon::area() const //finds the area of a polygon given it's points in array arr and corners, the number of verticies
{
	double sum = 0.0;
	for(int i = 0; i < corners-1; i++)
	{
		sum += (vertexX(i)*vertexY(i+1)) - (vertexX(i+1)*vertexY(i));
	}
	sum += (vertexX(corners-1)*vertexY(0)) - (vertexX(0)*vertexY(corners-1));
	return sum / 2;
}
void Polygon::move(double xChange, double yChange) //moves a polygon xChange in the x direction and yChange in the y direction
{
	for(int i = 0; i < corners*2; i += 2)
	{
		arr[i] += xChange;
		arr[i+1] += yChange;
	}
}
void Polygon::render(ostream& os) const //draws a polygon according to the prompt
{
	os << "Polygon(" << colorArray[color()] << "," << corners;
	for(int i = 0; i < corners*2; i++)
	{
		os << "," << arr[i];
	}
	os << ")";
}
bool Polygon::inside(double xCoord, double yCoord) const //returns if the point is inside the polygon or not
{
	int i, j; 
	bool c = false;
  	for (i = 0, j = corners-1; i < corners; j = i++) 
  	{
    	if ( ((vertexY(i)>yCoord) != (vertexY(j)>yCoord)) && (xCoord < (vertexX(j)-vertexX(i)) * (yCoord-vertexY(i)) / (vertexY(j)-vertexY(i)) + vertexX(i)) )
       		c = !c;
    }
  	return c;
}
//--------------------All RoundBox functions--------------------
double RoundBox::perimeter() const //finds the perimeter of a round box given it's t,b,r,l
{
	return ((t-b)*2)+((r-l)*2)+(2*M_PI*radi)-(8*radi);
}
double RoundBox::area() const //finds the area of a round box given it's t,b,r,l
{
	return (t-b)*(r-l)-(2*radi*2*radi - radi*radi*M_PI);
}
void RoundBox::move(double xChange, double yChange) //moves a round box xChange in the x direction and yChange in the y direction
{
	r += xChange;
	l += xChange;
	t += yChange;
	b += yChange;
}
void RoundBox::render(ostream& os) const //draws a round box acccording to the prompt
{
	os << "RoundBox(" << colorArray[color()] << "," << l << "," << t << "," << r << "," << b << "," << radi << ")";
}
bool RoundBox::inside(double x, double y) const //returns if the point is inside the round box or not
{
	Box newX(BLACK, l+radi, t, r-radi, b);
	Box newY(BLACK, l, t-radi, r, b+radi);
	Circle tl(BLACK, l, t, radi);
	Circle tr(BLACK, r, t, radi);
	Circle bl(BLACK, l, b, radi);
	Circle br(BLACK, r, b, radi);
	return newX.inside(x, y) || newY.inside(x, y) || tl.inside(x, y) || tr.inside(x, y) || bl.inside(x, y) || br.inside(x, y);
}
//--------------------All Line functions--------------------
double Line::perimeter() const
{
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}
void Line::move(double xChange, double yChange)
{
	x1 += xChange;
	x2 += xChange;
	y1 += yChange;
	y2 += yChange;
}
void Line::render(ostream& os) const //draws a line acccording to the prompt
{
	os << "Line(" << colorArray[color()] << "," << x1 << "," << y1 << "," << x2 << "," << y2 << ")";
}
bool Line::inside(double xCoord, double yCoord) const //returns if the point is on the line or not
{
	return sqrt((xCoord-x1)*(xCoord-x1)+(yCoord-y1)*(yCoord-y1))+sqrt((xCoord-x2)*(xCoord-x2)+(yCoord-y2)*(yCoord-y2)) == perimeter();
}
//--------------------All Group functions--------------------
Group::~Group() //deletes all shapes in the array
{
	for(int i = 0; i < groupSize; i++)
	{
		delete groupData[i];
	}
}
void Group::color(Color c) //sets the color of a group and all it's members
{
	col = c;
	for(int i = 0; i < groupSize; i++)
	{
		groupData[i]->color(c);
	}
}
double Group::perimeter() const //returns the perimeter of all members of shapes combined
{
	double totalPeri = 0;
	for(int i = 0; i < groupSize; i++)
	{
		totalPeri += groupData[i]->perimeter();
	}
	return totalPeri;
}
double Group::area() const //returns the area of all members of shape combined
{
	double totalArea = 0;
	for(int i = 0; i < groupSize; i++)
	{
		totalArea += groupData[i]->area();
	}
	return totalArea;
}
void Group::move(double xChange, double yChange) //moves all members of the group
{
	for(int i = 0; i < groupSize; i++)
	{
		groupData[i]->move(xChange, yChange);
	}	
}
void Group::render(ostream& os) const //renders the group of shapes
{
	os << "Group(" << colorArray[col] << "," << groupSize;
	for(int i = 0; i < groupSize; i++)
	{
		os << ","; 
		groupData[i]->render(os);
	}
	os << ")";
}
bool Group::inside(double xCoord, double yCoord) const //returns true if the passed point is inside any of the shapes in the group
{
	bool in = false;
	for(int i = 0; i < groupSize && !in; i++)
	{
		if(groupData[i]->inside(xCoord, yCoord))
			in = true;
	}
	return in;
}
void Group::shapes(int newSize, Shape** newData) //passes a new array of shapes and the size of that new array and changes the group to
{												 //this new array of shape pointers
	for(int i = 0; i < groupSize; i++)
	{
		delete groupData[i];
	}
	groupSize = newSize;
	groupData = newData;
}