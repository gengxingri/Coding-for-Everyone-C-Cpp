/*

  This is an C++ example shown by Dr. Pohl
*/

#include <iostream>

using namespace std;


typedef enum days{SUN, MON, TUE, WED, THU, FRI, SAT}days;

/*The prefix auto-increment is being overloaded. The expection is
the argument is changed to be one greater and its value returned
*/
inline days operator++(days d)
{
	/*A Cast operator forces one data type 
	to be converted into another data type */

	return static_cast<days>((static_cast<int>(d) + 1) % 7); //overloading
}

//binary operator

// write data as a class because << only returns int and flout data
ostream & operator<<(ostream& out, const days& d){
	switch (d){
	case SUN: out << "SUN"; break;
	case MON: out << "MON"; break;
	case TUE: out << "TUE"; break;
	case WED: out << "WED"; break;
	case THU: out << "THU"; break;
	case FRI: out << "FRI"; break;
	case SAT: out << "SAT"; break;
	}
	return out;
}



int main()
{
	days d = MON, e;
	e = ++d;

	cout << d << "\t" << e << endl;
}
