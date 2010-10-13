#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)

typedef long long ll;

string text, p;
bool any = false;
// Computes the jumping function
vector<long long> kmp_table(string &P){
  int i = 0, j = -1;
  int m = P.size();
  vector<long long> f(m+1);
  f[0] = -1;
  while( i < m ){
    while(j>=0 and P[i] != P[j]) j = f[j];
    f[++i] = ++j;
  }
  // puts("Failure function");
  // for(int i=0;i<f.size();++i) printf("%d ", f[i]);
  // puts("");
  return f;
}

void kmp(string &T, string &P){
  vector<long long> pi = kmp_table(P);
  int n = T.size(), m = P.size();
  int q = 0;
  for(int i = 0; i<n; ){
    while(q > -1 and P[q] != T[i])  q = pi[q];
    i++; q++;
    if(q >= m ){
      any = true;
      printf("%d\n", i - q);
      q = pi[q];
    }
  }
}

int main(){
  ll len;
  while( scanf("%lli",&len) != EOF ){
    any = false;
    cin >> p >> text;
    if( p.size() <= text.size() ){
      kmp( text, p );
      if(any) puts("");
    }
  }
  return 0;
}
