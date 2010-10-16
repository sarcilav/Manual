struct node {
  int weight;
  int index;
};
bool visited[MAXNODES];
bool can_go(node n);//retorna true si se puede visitar ese nodo
node best;
int dfs(node root)
{
  memset(visited, false, sizeof visited);
  stack<node> s;
  s.push(root);
  int ans = 0;
  while(s.size())
  {
    node actual = s.top();
    visited[actual.index] = true;
    s.pop();
    int weight = actual.weight;
    if(weight > ans)
    {
      ans = weight;
      best = actual;
    }
      //for para cada vecino)
    if(can_go(vecino))
      s.push(vecino);
  }
  return ans;
}
int max_path_dag()
{
  node root;
  root.weight = 0;
  root.index = 0; // cualquier node del dag funciona
  int t = dfs(root);
  best.weight = 0;
  int ans = dfs(best);
  return ans;
}
