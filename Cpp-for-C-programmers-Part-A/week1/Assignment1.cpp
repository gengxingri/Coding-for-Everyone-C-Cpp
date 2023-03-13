/*   
    Assignment 1 - by Bruce Geng

*   Convert this program to C++
    
*   change to C++ io

*   change to one line comments

*   change defines of constants to const

*   change array to vector<>

*   inline any short function

*/

// replace <stdio.h>
#include <iostream>
#include <vector>
//#include <numeric>


// need to add this to print 
using namespace std;

// replace #define
const int N = 40;

// inline the short function 
inline int sum(vector< int > data)
{ 
  int s = 0;
  for (int i = 1; i < N; i++){
    s += data[i];
  }
  //accumulate(data.begin(), data.end(), 0);
  return s;
}

int main(void)
{
  int accum = 0;
  
  // vector 
  vector <int> data(N); 

  for(int i = 0; i < N; ++i){
    data[i] = i;
  }

  accum = sum(data);
  
  // print the result
  cout <<"sum is: " << accum << endl;
  return 0;
}
