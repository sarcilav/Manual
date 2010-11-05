int c, l, h, n;
pair<int, pair<int, int> > edges[100000];
int p[3000], r[3000];
vector<int> E[3000], W[3000];

//Implement union find and add this to make_set(int u)
//E[u].resize(0);   W[u].resize(0);

//pai[i] = papá del nodo i
//dist[i] = costo desde la raiz hasta i
//maxi[a][b] = máxima arista entre a y los papás de a hasta una distancia de 2^b 
//pp[u][b] = es el papá de u en distancia 2^b
int maxi[3000][20], pai[3000], inf = 1 << 30, dist[3000], pp[3000][20];

// nodo, profundidad, papa, costo
void dfs(int v, int p, int f, int c){
  pai[v] = f;
  dist[v] = p;
  maxi[v][0] = c;
  for(int i = 0; i < E[v].size(); i++){
    if(E[v][i] == f) continue;
    dfs(E[v][i], p + 1, v, W[v][i]);
  }
}

// Idea principal:
// maxi[i][j] es un camino de tamaño 2^j. Entonces lo partimos en dos.
// ambos de tamaño 2^(j - 1)
// maxi[i][j] = max(maxi[pp[i][j - 1]][j - 1], maxi[i][j - 1]);
// el primer argumento es la primera parte del camino (lo más arriba)
// y el seguno argumento es la segunda parte (lo más abajo. Más cerca del nodo i)
// maxi[i][0] = peso para llegar a i desde el papá (2^0 = 1, papá a 1 de distancia)
void pre(){
  memset(pai, -1, sizeof pai);

  for(int i = 0; i < n; i++) for(int j = 0; (1 << j) < n; j++){
    pp[i][j] = -1;
    maxi[i][j] = -inf;
  }
  dfs(0, 0, -1, 0);
  pai[0] = 0;
  maxi[0][0] = inf;

  for(int i = 0; i < n; i++) pp[i][0] = pai[i];

  for(int j = 1; (1 << j) < n; j++){
    for(int i = 0; i < n; i++){
      if(pp[i][j - 1] == -1) continue;
      pp[i][j] = pp[pp[i][j - 1]][j - 1];
      maxi[i][j] = max(maxi[pp[i][j - 1]][j - 1], maxi[i][j - 1]);
    }
  }
}

int resolve(int a, int b){
  int rmaxi = -inf;
  if(dist[a] < dist[b]) swap(a, b);
  int log;
  for(log = 1; (1 << log) <= dist[a]; log++);
  log--;
  for(int i = log; i >= 0; i--)
  if(dist[a] - (1 << i) >= dist[b]){
    rmaxi = max(rmaxi, maxi[a][i]);
    a = pp[a][i];
  }

  if(a == b)
    return rmaxi;


  for(int i = log; i >= 0; i--){
    if(pp[a][i] != -1 && pp[a][i] != pp[b][i]){
      rmaxi = max(rmaxi, maxi[a][i]);
      rmaxi = max(rmaxi, maxi[b][i]);
      a = pp[a][i]; b = pp[b][i];
    }
  }
  rmaxi = max(rmaxi, maxi[a][0]);
  rmaxi = max(rmaxi, maxi[b][0]);
  return rmaxi;
}


int main(){
  while(scanf("%d %d %d", &c, &l, &h) && c != -1){
    int edg = 0;
    while(l--){
      int a, b, w;
      scanf("%d %d %d", &a, &b, &w);
      edges[edg++] = make_pair(w, make_pair(a - 1, b - 1));
    }
    sort(edges, edges + edg);
    for(int i = 0; i < c; i++) makeSet(i);

    for(int i = 0; i < edg; i++){
      int w = edges[i].first, u = edges[i].second.first, v = edges[i].second.second;
      if(find(u) != find(v)){
        Union(u, v);
        E[u].push_back(v); E[v].push_back(u);
        W[u].push_back(w); W[v].push_back(w);
      }
    }

    n = c;
    pre();

    for(int i = 0; i < h; i++){
      if(i) printf(" ");
      int a, b; scanf("%d %d", &a, &b); a--; b--;
      printf("%d", resolve(a, b));
    }
    printf("\n");

  }            
}