/*
  Point function
  This is an C++ example shown by Dr. Pohl
*/

#include <iostream>
using namespace std;

class point{
public:
	double x, y;
};


// A better way for class
/*  
class point{
public:
	double getx(){ return x; }
	void setx(double v){ x = v; }
 
 private:
 	double x, y;
};
*/


point operator+ (point& p1, point &p2){
	point sum = {p1.x + p2.x, p1.y + p2.y};
	return sum;
}


// a form of operator overloading, binary operator (IO operation)
ostream & operator<< (ostream& out, const point & p){
	out << "(" << p.x << "," << p.y << ")";
	return out;
}

// usual signature for overloading 
//ostream & operator<< (ostream& out, const my_type &v)
// both arguments are passed by reference


int main()
{
	point a = {3.5, 2.5}, b = {2.5, 4.5};

	cout << "a = " << a << "\tb =" << b << endl;
	cout << "sum = " << a + b <<endl;
}
