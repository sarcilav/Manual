// RMQ will find the POSITION of the
// smallest integer inside an array A
// between A[i] and A[j] (inclusive)

// <f(x), g(x)>
// f is the construction
// g is the query

// First implementation. <O(n^2), O(1)>
const int MAXN = 11;
int M[MAXN][MAXN], A[MAXN], N = 10;
// DP approach: M[i][j] = position of the RQM from i to j
// if A[ M[i][j-1] ] < A[j] then the RQM(i,j) is the same
// else A[j] is smaller than the last smaller so RQM(i,j) = j
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