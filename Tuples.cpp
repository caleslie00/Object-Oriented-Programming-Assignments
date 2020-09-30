#include <iostream>
#include "Tuple.h"

using namespace std;

Tuple<int> add(Tuple<int> a,Tuple<int> b,Tuple<int> c)
{
   return a+b+c;     // allocation for 2 anonymous objects, deallocation for 1 of them
}

int main()
{
   Tuple<int> x(3);  // allocation of 3 ints
   Tuple<int> y(5);  // allocation of 5 ints
   x[0] = 2;         // no allocation, only one "user" of data
   cout << x[0] << endl;
   x[1] = 3;
   cout << x[1] << endl;
   x[2] = 7;
   cout << x[2] << endl;
   y = x;           // deallocation of 5 ints, share 3 ints
   Tuple<int> z(x);  // no allocation, another shared copy
   z[3] = 9;     // no allocation, z[3] is undefined so its a no-op
   z[1] = 5;       // copy/split occurs before write to element 1
   z += x;          // no allocation, z has its own copy
   x = add(x,y,x); // no memory allocation should occur due to copy construction
   x * y;
   y * 3;
   3 * y;
   y *= 3;
   for(int i = 0; i < 3; i++)
   {
      cout << y[i] << " ";
   }
   cout << endl;
   for(int i = 0; i < 3; i++)
   {
      cout << x[i] << " ";
   }
   cout << endl;
   cout << (y == x ? "True" : "False") << endl;
   cout << (y != x ? "True" : "False") << endl;
   Tuple<int> a(5);
   Tuple<int> b(a);
   Tuple<int> c(b);
   a[3] = 7;
   Tuple<int> d(a);
   cout << (a == b ? "True" : "False") << endl;
   cout << (a != b ? "True" : "False") << endl;
}