const int MAXN = 22;

int cube[MAXN][MAXN][MAXN];
int mat[MAXN][MAXN];
int arr[MAXN];

int n;

// Returns the maximum sum inside an array
// The sum best = Sum i in [from, to]
int kadane(){
  int best=1<<31,current=0,from=0,to=0,aa=0;
  for(int i=0;i<MAXN;++i){
    current += arr[i];
    if ( current > best ){ best=current; from=aa; to=i;}
    if ( current < 0 ){ current = 0; aa = i+1;}
  }
  return best;
}
// Returns the submatrix with maximum sum
// The sum is inside the matrix (xi,y1) - (x2, y2)
// A is the matrix, N the size
int kadane2D () { 
  vector<int>pr(102,0);
  int S = 1<<31, s=0, k,l,x1=0,x2=0,y1=0,y2=0,j,t;
  for(int z=0;z < N;++z){
    pr = vector<int>(MAXN,0);
    for(int x=z;x<N;++x){
      t=0;s = 1<<31;j=k=l=0;
      for(int i=0;i<N;++i) {
        pr[i]=pr[i]+a[x][i]; t=t+pr[i];
        if (t>s){ s = t; k = i; l = j;}
        if(t<0){ t=0; j=i+1;}
      }
      if (s > S) { S = s; x1 = x; y1 = k; x2 = z;  y2 = l;}
    }
  }
  return S;
}

// Easier to implement. Less information
int best2D(){
  int ans = 0;
  for(int i=0; i<n; ++i){
    memset(arr, 0, sizeof arr);
    for (int j=i; j<n; ++j){
      for (int k=0; k<n; ++k) arr[k] += mat[j][k];
      int sum = 0;
      for (int k=0; k<n; ++k){
        sum += arr[k];
        ans = max(ans, sum);
        if (sum < 0) sum = 0;
      }
    }
  }
  return ans;
}


// Cube has the actual input. If all numbers in cube are negative
// the maximum sum is the biggest of the numbers
int kadane3D(){
  int ans = 0;
  for (int i=0; i<n; ++i){
    memset(mat, 0, sizeof mat);
    for (int j=i; j<n; ++j){
      for (int ii=0; ii<n; ++ii){
        for (int jj=0; jj<n; ++jj){
          mat[ii][jj] += cube[j][ii][jj];
        }
      }
      ans = max(ans, ());
    }
  }
  return ans;
}

