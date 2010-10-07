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
vector<int> kmp_table(string &P){
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
  
  return f;
}

void kmp(string &T, string &P){
  vector<int> pi = kmp_table(P);
  int n = T.size(), m = P.size();
  int q = 0;
  for(int i = 0; i<n;++i){
    while(q > 0 and P[q+1] != T[i]){
      q = pi[q];
    }
    if(P[q+1] == T[i]){
      q++;
    }
    if(q + 1 == m){
      if( i - m + 1 != -1)
        printf("Match at %d\n", i - m + 1);
      q = pi[q - 1];
    }
  }
}

int main(){
  string T,P;
  while(cin >> T >> P){
    printf("Searching for %s \t in %s\n", P.c_str(), T.c_str());
    kmp(T,P);
    puts("***");
  }
  return 0;
}
