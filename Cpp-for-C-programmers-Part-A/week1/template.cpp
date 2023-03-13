/*
  Use of template

  This is an C++ example shown by Dr. Pohl
*/

#include <iostream>
#include <complex>
using namespace std;

// swap leads to ambiguous errors due to using std functions as general functions
// here use swap2 to avoid, but another way is to remove "using namespace std;",
// use "std::cout" and "std::endl" to replace the original ones
template <class T> 
inline T swap2(T &d, T &s)  
{
	T temp = d;
	d = s;
	s = temp;
}


int main()
{
	int m = 5, n = 10;
	double x = 5.3, y = 10.6;
	complex <double> r(2.4, 3.5), s(3.4, 6.7);

	cout << "input:" << m << ", " << n << endl;
	swap(m,n);
	cout << "\noutput:" << m << ", " << n << endl;

	cout << "\ndouble input:" << x << ", " << y << endl;
	swap(x,y);
	cout << "\ndouble output:" << x << ", " << y << endl;
  
  cout << "\ncomplex input:" << r << ", " << s << endl;
	swap(r,s);
	cout << "\ndouble output:" << r << ", " << s << endl;

}
