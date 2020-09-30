#include <iostream>

enum Color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, INVALID };

class Shape
{
	private:
		Shape(const Shape& s); //makes sure you can't copy a shape
		const Shape& operator=(const Shape& s); //makes sure you can't copy a shape
	protected:
		Color col; //the color of the shape
	public:
		Shape(Color c) {color(c);} //initializes shape with color c
		virtual ~Shape() = 0; //pure virtual shape destructor
		Color color() const {return col;} //returns the color of the shape
		virtual void color(Color c) {col = c;} //sets the color of a shape to c
		virtual double perimeter() const = 0;
		virtual double area() const = 0;
		virtual void move(double xChange, double yChange) = 0;
		virtual void render(std::ostream& os) const = 0;
		double thickness() { return area() / perimeter();}
		virtual bool inside(double xCoord, double yCoord) const = 0;
		static Color colorAtPoint(Shape** A, int numShapes, double xCoord, double yCoord);
};

class Box : public Shape
{
	private:
		double l,t,r,b; //the coordinates of the left side of the box, the coordinates of the top side of the box, the coordinates of the right side of the box, the coordinates of the bottom side of the box
	public:
		Box(Color c, double le, double to, double ri, double bo): Shape(c), l(le), t(to), r(ri), b(bo) {} //initializes a box
		void left(double c) {l = c;} //changes the l value of a box to c
		void top(double c) {t = c;} //changes the t value of a box to c
		void right(double c) {r = c;} //changes the r value of a box to c
		void bottom(double c) {b = c;} //changes the b value of a box to c
		double left() const {return l;} //returns the l value of the box
		double top() const {return t;} //returns the t value of the box
		double right() const {return r;} //returns the r value of the box
		double bottom() const {return b;} //returns the b value of the box
		double perimeter() const;
		double area() const;
		void move(double xChange, double yChange);
		void render(std::ostream& os) const;
		bool inside(double xCoord, double yCoord) const;
};

class Circle : public Shape
{
	private:
		double x, y, r; //the x coordinate value of the center, the y coordinate value of the center, and radius of the circle
	public:
		Circle(Color c, double xc, double yc, double rd): Shape(c), x(xc), y(yc), r(rd) {} //initializes a circle
		void centerX(double c) {x = c;} //sets the r value of a circle to c
		void centerY(double c) {y = c;} //sets the r value of a circle to c
		void radius(double c) {r = c;} //sets the r value of a circle to c
		double centerX() const {return x;} //returns the x value of the circle
		double centerY() const {return y;} //returns the y value of the circle
		double radius() const {return r;} //returns the r value of the circle
		double perimeter() const;
		double area() const;
		void move(double xChange, double yChange);
		void render(std::ostream& os) const;
		bool inside(double xCoord, double yCoord) const;
};

class Triangle : public Shape
{
	private:
		double x1, y1, x2, y2, x3, y3; //the corresponding x1, x2, x3, y1, y2, and y3 coordinate values
	public:
		Triangle(Color c, double xOne, double yOne, double xTwo, double yTwo, double xThree, double yThree): Shape(c), x1(xOne), y1(yOne), x2(xTwo), y2(yTwo), x3(xThree), y3(yThree) {} //initializes a triangle
		void cornerX1(double c) {x1 = c;} //sets the x1 coordinate to c
		void cornerY1(double c) {y1 = c;} //sets the y1 coordinate to c
		void cornerX2(double c) {x2 = c;} //sets the x2 coordinate to c
		void cornerY2(double c) {y2 = c;} //sets the y2 coordinate to c
		void cornerX3(double c) {x3 = c;} //sets the x3 coordinate to c
		void cornerY3(double c) {y3 = c;} //sets the y3 coordinate to c
		double cornerX1() const {return x1;} //return the x1 coordinate
		double cornerY1() const {return y1;} //return the y1 coordinate
		double cornerX2() const {return x2;} //return the x2 coordinate
		double cornerY2() const {return y2;} //return the y2 coordinate
		double cornerX3() const {return x3;} //return the x3 coordinate
		double cornerY3() const {return y3;} //return the y3 coordinate
		double perimeter() const;
		double area() const;
		void move(double xChange, double yChange);
		void render(std::ostream& os) const;
		bool inside(double xCoord, double yCoord) const;
};

class Polygon : public Shape
{
	private:
		double* arr; //the array of the points of the polygon, alternating x1, y1, x2, y2...
		int corners; //the number of verticies(or corners)
	public:
		Polygon(Color c, double* data, int verticies);
		~Polygon();
		int points() const {return corners;} //returns the number of points in the polygon
		void vertexX(int v, double c) {arr[v*2] = c;} //sets x of vertex v to c
		double vertexX(int v) const {return arr[v*2];} //returns the x of vertex v
		void vertexY(int v, double c) {arr[(v*2)+1] = c;} //sets y of vertex v to c
		double vertexY(int v) const {return arr[v*2+1];} //returns the y of vertex v
		double perimeter() const;
		double area() const;
		void move(double xChange, double yChange);
		void render(std::ostream& os) const;
		bool inside(double xCoord, double yCoord) const;
};

class RoundBox : public Shape
{
	private:
		double l,t,r,b,radi; //the coordinates of the left side of the box, the coordinates of the top side of the box, the coordinates of the right side of the box, the coordinates of the bottom side of the box
	public:
		RoundBox(Color c, double le, double to, double ri, double bo, double ra): Shape(c), l(le), t(to), r(ri), b(bo), radi(ra) {} //initializes a round box
		void left(double c) {l = c;} //changes the l value of a rounded box to c
		void top(double c) {t = c;} //changes the t value of a rounded box to c
		void right(double c) {r = c;} //changes the r value of a rounded box to c
		void bottom(double c) {b = c;} //changes the b value of a rounded box to c
		void radius(double c) {radi = c;} //changes radi value of a rounded box c
		double left() const {return l;} //returns the l value of the rounded box
		double top() const {return t;} //returns the t value of the rounded box
		double right() const {return r;} //returns the r value of the rounded box
		double bottom() const {return b;} //returns the b value of the rounded box
		double radius() const {return radi;} //returns the radi value of the rounded box
		double perimeter() const;
		double area() const;
		void move(double x, double y);
		void render(std::ostream& os) const;
		bool inside(double xCoord, double yCoord) const;
};

class Line : public Shape
{
	private:
		double x1, x2, y1, y2;
		double area() const {return 0;} //there is no area of a line so this returns 0
	public:
		Line(Color c, double xOne, double yOne, double xTwo, double yTwo): Shape(c), x1(xOne), x2(xTwo), y1(yOne), y2(yTwo) {} //initializes a line
		void end1X(double c) {x1 = c;} //changes the x1 value to c
		void end2X(double c) {x2 = c;} //changes the x2 value to c
		void end1Y(double c) {y1 = c;} //changes the y1 value to c
		void end2Y(double c) {y2 = c;} //changes the y2 value to c
		double end1X() const {return x1;} //returns the x1 value
		double end2X() const {return x2;} //returns the x2 value
		double end1Y() const {return y1;} //returns the y1 value
		double end2Y() const {return y2;} //returns the y2 value
		double perimeter() const;
		void move(double xChange, double yChange);
		void render(std::ostream& os) const;
		bool inside(double xCoord, double yCoord) const;
};

class Group : public Shape
{
	private:
		int groupSize; //size of th array of shape pointers
		Shape** groupData; //holds the array of shape pointers
	public:
		Group(Color c, int gSize, Shape** data): Shape(c), groupSize(gSize), groupData(data) {color(c);} //initializes a group
		~Group(); //group destructor
		void color(Color c); 
		int shapes() const {return groupSize;} ///return the number of shapes
		void setSize(int newSize) {groupSize = newSize;} //sets the size of the group to newSize
		Shape* shape(int shape) const {return groupData[shape];} //returns the pointer to shape shape
		double perimeter() const; //returns the perimeter of all members of shapes combined
		double area() const; //returns the area of all members of shape combined
		void move(double xChange, double yChange); //moves all members of the group
		void render(std::ostream& os) const; //renders the group of shapes
		bool inside(double xCoord, double yCoord) const; //returns true if the passed point is inside any of the shapes in the group
		void shapes(int newSize, Shape** newData); //passes a new array of shapes and the size of that new array and changes the group to
												   //this new array of shape pointers
};