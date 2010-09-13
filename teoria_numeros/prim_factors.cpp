typedef map<int,int> prime_map;
void sqeeze(prime_map &M, int &n, int p) { for ( ; n%p ==0 ;n/=p) M[p]++;}
prime_map factor(int n){
    prime_map M;
    if(n<0) return factor(-n);
    if(n<2) return M;
    sqeeze(M, n, 2); sqeeze(M, n, 3);
    int maxP = sqrt(n) + 2;
    for(int p=5; p< maxP; p+=6){
	sqeeze(M , n, p); sqeeze(M, n, p+2);
    }
    if(n>1) M[n]++;
    return M;
}
    
