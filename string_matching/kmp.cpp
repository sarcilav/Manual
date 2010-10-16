#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)

string text, p;
bool any = false;
// Computes the jumping function
vector<int> kmp_table(string &P){
  int i = 0, j = -1;
  int m = P.size();
  vector<int> f(m+1);
  f[0] = -1;
  while( i < m ){
    while(j>=0 and P[i] != P[j]) j = f[j];
    f[++i] = ++j;
  }
  return f;
}

void kmp(string &T, string &P){
  vector<int> pi = kmp_table(P);
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
  int T, C=1;
  string s,t;
  while(scanf("%d", &T)){
    if(T==0) break;
    printf("Test case #%d\n", C++);
    cin >> s;
    vector<int>pi = kmp_table(s);
    for(int i=1;i<=T;++i)
      if(pi[i] > 0)
        if(i % (i-pi[i]) == 0)
          printf("%d %d\n", i, i/(i-pi[i]));
    puts("");
  }  
  return 0;
}
