// In this implementation, the tree is represented by a vector<int>.
// Elements are numbered by 0, 1, ..., n-1.
// tree[i] is sum of elements with indexes i&(i+1)..i, inclusive.
// (Note: this is a bit different from what is proposed in Fenwick's article.
// To see why it makes sense, think about the trailing 1's in binary
// representation of indexes.)

// Creates a zero-initialized Fenwick tree for n elements.
vector<int> create(int n) { return vector<int>(n, 0); }

// Returns sum of elements with indexes a..b, inclusive
int query(const vector<int> &tree, int a, int b) {
  if (a == 0) {
    int sum = 0;
    for (; b >= 0; b = (b & (b + 1)) - 1)
      sum += tree[b];
    return sum; 
  } else {
    return query(tree, 0, b) - query(tree, 0, a-1);
  }
}

// Increases value of k-th element by inc.
void increase(vector<int> &tree, int k, int inc) {
  for (; k < (int)tree.size(); k |= k + 1)
    tree[k] += inc;
}

int main(){
  vector<int> f = create(100000);
  for(int i = 0 ; i < 100000; ++i)
    increase(f, i, i);
  for(int i = 0; i < 100; ++i){
    //In this case it will return the sum = (i)(i+1)/2
    D(query(f,0,i));
  }
  return 0;
}