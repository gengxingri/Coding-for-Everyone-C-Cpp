/*
  Use of template

  This is an C++ example shown by Dr. Pohl
*/

#include <iostream>
#include <complex>
using namespace std;


template <class T> // T is generic type
inline T sum( const T data[], int size, T s=0)  
{
	for (int i = 0; i < size; ++i){
		s += data[i];
	}
	return s;
}


int main()
{
	cout << "template for sum() :" << endl;
	int a[] = { 1, 2, 3};
	double b[] = {2.1, 2.2, 2.3};

	cout << "\noutput:" << sum(a,3) << endl;

	cout << "\ndouble output:" << sum(b, 3) << endl;
	

}
