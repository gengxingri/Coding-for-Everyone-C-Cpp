/*
  This is an C++ example shown by Dr. Pohl
*/

#include <iostream>

using namespace std;

inline void swap(int &i, int &j){
	int temp = i;
	i = j;
	j = temp;
}

// C++ has overloading and call by reference. 
//Use the same name here 
inline void swap(double &i, double &j){
	double temp = i;
	i = j;
	j = temp;
}

int main()
{
	int m = 5, n = 10;
	double x = 5.3, y = 10.6;
	cout << "input:" << m << ", " << n << endl;
	swap(m,n);
	cout << "output:" << m << ", " << n << endl;
    cout << "\n"<< endl;
	cout << "double input:" << x << ", " << y << endl;
	swap(x,y);
	cout << "double output:" << x << ", " << y << endl;
}
