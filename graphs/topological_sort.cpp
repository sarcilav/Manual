/** Creates an edge from u to v. This represents that task u comes before task v **/
void add_edge(int u, int v){
    g[u].push_back(v);
    d[v]++;
}

int d[MAXN]; //d[i] is the number dependencies

vector<int> top_sort(graph &g, int *d){
    vector<int> order;
    int n = g.size();
    queue<int> q;
    set <int> inside;
    for(int i=0; i<n; ++i)
        if(d[i]==0){
            q.push(i);
            inside.insert(i);
            order.push_back(i);
        }
    while(q.size()){
        int actual = q.front();
        q.pop();
        inside.erase (actual);
        for(int i=0;i<g[actual].size();++i){
            int next = g[actual][i];
            d[next]--;
            if(d[next]==0){
                if(inside.count(next)) {
                    return vector<int>(1,INT_MAX); // There's a cycle. And no topsort can be made!
                }
                q.push(next); inside.insert(next); order.push_back(next);
            }
        }
    }
    return order;
}
