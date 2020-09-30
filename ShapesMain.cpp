#include "Shapes.cpp"
#include <sstream>
using namespace std;

int main()
{
	Shape * list[2];
	list[0] = new Box(GREEN, 0, 1, 1, 0);
	list[1] = new Circle(YELLOW, 2, 2, 2);
	Group g(BLUE, 2, list);
		
	cout << "Group area: " << g.area() << "\n";
	cout << "Group perimeter: " << g.perimeter() << "\n";
		
	g.move(1,1);
	g.render(cout); cout << "\n";
	g.color(RED);
	g.render(cout); cout << "\n";

	cout << "Count: " << g.shapes() << "\n";
	g.shape(1)->render(cout); cout << "\n";

	Shape * list2[3];
	list2[0] = new Circle(WHITE,5,5,1);
	list2[1] = new Box(GREEN,7,1,9,-10);
	list2[2] = new RoundBox(BLACK,5,5,8.5,4.5,0.1);
	g.shapes(3,list2);
	g.render(cout); cout << "\n";
}