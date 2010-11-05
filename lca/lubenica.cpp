#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

#define sz(A) (int)(A).size()
#define vs vector<string>
#define vi vector<int>
#define ll long long
#define FOR(A,B) for(int A=0; A < (int) (B);A++)
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define all(x) x.begin() , x.end()

#define N 100000
#define inf 10000001

int dist[N];
int pai[N];
int pp[N][20];
int mini[N][20];
int maxi[N][20];
int n;

struct X {
  int v,c;
};

X no(int a, int b) {
  X x;
  x.v = a;
  x.c = b;
  return x;
}

vector< X > adj[N];

void dfs(int v, int p, int f, int c) {
  pai[v] = f;
  dist[v] = p;
  mini[v][0] = c;
  maxi[v][0] = c;
  FOR(i,sz(adj[v])) {
    if(adj[v][i].v == f) continue;
    dfs(adj[v][i].v, p+1, v, adj[v][i].c);
  }
}

void pre() {
  memset(pai,-1,sizeof(pai));

  FOR(i,n) for(int j=0; (1<<j) < n; j++) {
    pp[i][j] = -1;
    mini[i][j] = inf;
    maxi[i][j] = -inf;
  }

  dfs(0,0,-1,0);
  pai[0] = 0;
  maxi[0][0] = -inf;
  mini[0][0] = inf;

  FOR(i,n) pp[i][0] = pai[i];

  for(int j=1; (1<<j) < n; j++) {
    for(int i=0; i < n; i++) {
      if(pp[i][j-1] == -1) continue;
      pp[i][j] = pp[ pp[i][j-1] ] [j-1];
      mini[i][j] = min(mini[pp[i][j-1]][j-1], mini[i][j-1] );
      maxi[i][j] = max(maxi[pp[i][j-1]][j-1], maxi[i][j-1] );
    }
  }

}

int resolve(int a, int b) {
  int rmini = inf;
  int rmaxi = -inf;

  if(dist[a] < dist[b]) swap(a,b);
  int log;
  for(log = 1; (1<<log) <= dist[a]; log++);
  log--;
  for(int i=log; i >= 0; i--) 
  if(dist[a] - (1<<i) >= dist[b]) {
    rmini = min(rmini, mini[a][i]);
    rmaxi = max(rmaxi, maxi[a][i]);
    a = pp[a][i];
  }

  if(a == b) {
    printf("%d %d\n", rmini, rmaxi);
    return a;
  }

  for(int i=log; i>=0; i--) {
    if(pp[a][i] != -1 && pp[a][i] != pp[b][i]) {
      rmini = min(rmini, mini[a][i]);
      rmini = min(rmini, mini[b][i]);
      rmaxi = max(rmaxi, maxi[a][i]);
      rmaxi = max(rmaxi, maxi[b][i]);
      a = pp[a][i]; b = pp[b][i];
    }
  }

  rmini = min(rmini, mini[a][0]);
  rmini = min(rmini, mini[b][0]);
  rmaxi = max(rmaxi, maxi[a][0]);
  rmaxi = max(rmaxi, maxi[b][0]);
  printf("%d %d\n", rmini, rmaxi);
  return pai[a];
}

void res(int a, int b) {
  int px = resolve(a,b); // LCA
}

int main() {
  int a , b ,c,k;
  scanf("%d", &n);
  FOR(i,n) adj[i].clear();

  FOR(i,n-1) {
    scanf("%d %d %d", &a,&b,&c);
    a--;b--;
    adj[a].pb( no(b,c));
    adj[b].pb(no(a,c));
  }

  pre();

  scanf("%d", &k);
  FOR(i,k) {
    scanf("%d %d", &a,&b);
    a--;b--;
    res(a,b);
  }
  return 0;
}

