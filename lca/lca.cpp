#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;


// RMQ will find the POSITION of the
// smallest integer inside an array A
// between A[i] and A[j] (inclusive)

// <f(x), g(x)>
// f is the construction
// g is the query

// First implementation. <O(n^2), O(1)>
int M[MAXN][MAXN], int A[MAXN], int N;
void preprocess1(){
  int i,j;
  for(i = 0; i<N; ++i) M[i][i] = i;
  for(i = 0; i<N; ++i)
    for(j = i+1; j<N; ++j)
      // Leave the <= if you want the leftmost position
      if(A[M[i][j-1]] <= A[j]) 
        M[i][j] = M[i][j] = M[i][j-1];
      else
        M[i][j] = j;
}

int main(){
  return 0;
}
