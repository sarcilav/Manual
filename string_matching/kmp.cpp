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
    int n = P.size();
    vector<int> T(n+1);
    T[0] = -1; T[1] = 0;
    for(int pos = 2, cnd = 0; pos < n; ++pos){
	if(P[pos -1] == P[cnd]){ T[pos] = ++cnd;}
	else if(cnd > 0) { cnd = T[cnd]; --pos; }
	else T[pos] = 0;
    }
    return T;
}

// Looking for W in S
void kmp_search(string &S, string &W){
    //printf("Looking for  %s  in  %s\n", W.c_str(), S.c_str());
    set<int>s;
    int m = 0, i = 0, n = S.size(), w = W.size();
    vector<int> T = kmp_table(W);
    while( m + i < n){
	if(W[i] == S[m+i]){
	    if(++i == w){s.insert(m); m--; }//printf("There's a match at %d\n", m); m--;}
	}
	else{
	    m += i - T[i];
	    i = (T[i] > -1) ? T[i] : 0;
	}
    }
    printf("%d\n", s.size());
    foreach(i,s){ printf("%d ", *(i)); }
    puts("");
    return ;
}

int main(){
    //string T = "CABBCABABABA";
    //string P = "ABA";
    //string P = "ababababca";
    string T,P;
    cin >> P >> T;
    kmp_search(T, P);
    return 0;
}
