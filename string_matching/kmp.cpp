#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)

// Computes the jumping function
int kmp_table(string &P){
  int i = 1, j = 0;
  int m = P.size();
  vector<int> f(m);
  f[0] = 0;
  while( i < m ){
    if(P[j] == P[i])
      f[i++] = ++j;
    else if(j>0)
      j = f[j-1];
    else
      f[i++] = 0;
  }
  return f.back();
}

int main(){
  string P;
  int k;
  while(scanf("%d", &k) == 1){
    if(k < 1) break;
    cin >> P;
    int N = P.size();
    if( N > k) puts("0");
    else if(N == k) puts("1");
    else if(N == 1) printf("%d\n", k);
    else{
      int overlap = kmp_table(P);
      int ans = 0;
      if(overlap > 0){
        ans++;
        k-=N;
      }
      ans += ( k / (N-overlap) );
      cout << ans << endl;
    }
  }
  return 0;
}
