/* 
  Simple STL vector program
*/

#include <iostream>
#include <vector>

using namespace std;


int main()
{
	vector<int> v(100); //allocate space
    
    // C idiom
	for (int i = 0; i < 100; ++i){
		v[i] = i;
	}
    

    // C++ idiom
	// for (vector<int> ::iterator p = v.begin(); p!= v.end(); ++p){
	// 	cout << *p << '\t';
	// 	cout << endl;
	// }
  
  // auto type specifier
	  for (auto p = v.begin(); p!= v.end(); ++p){
		  cout << *p << '\t';
		  cout << endl;
    }
	return 0;
}
