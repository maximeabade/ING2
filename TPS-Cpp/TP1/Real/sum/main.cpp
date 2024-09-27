/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////AUTHOR: Maxime Abade <https://github.com/maximeabade>          /////
/////VERSION: 1.0                                                   /////
/////DATE OF CREATE: 26/01/2024                                     /////
/////DATE OF LAST MODIF: 26/01/2024                                 /////
/////NAME: SUM -> void                                              /////
/////INPUTS: int* p, int n, int array[]                             /////
/////OUTPUTS: NULL                                                  /////
/////BRIEF: la fonction effectue la somme des entiers allant de     /////                                                               
/////       0 à N-1                                                 /////
/////                                                               /////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

void sum(int* p, int n, int array[]) {
  int i;
  *p = 0;
  for (i = 0; i < n; ++i) {
    *p += array[i];
  }
}

int main() {
  const int N = 40;
  int i;
  int accum = 0;
  int data[N];
  for (i = 0; i < N; ++i) {
    data[i] = i;
    //cout << data[i] << endl;  //control display of data
  }
  sum(&accum, N, data);
  cout << "sum is " << accum << " and goes from 0 to "<< N-1 << endl;
  return 0;
}
