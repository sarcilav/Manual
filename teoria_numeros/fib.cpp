typedef unsigned long long uulong;
uulong fib(int n){
  uulong i=1,j=0,k=0,h=1,t=0;
  while(n>0){
    if (n%2==1){ t=j*h;  j=i*h + j*k + t;  i = i*k + t; }
    t = h*h; h = 2*k*h + t; k = k*k + t;
    n = floor(n/2);
  }
  return j;
}
