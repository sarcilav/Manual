//Generate primes with Erathostenes
int fi(int n) { 
  if(primes[n]) return n-1;
  int result = n; 
  for(int i=2;i*i <= n;i++) { 
    if (n % i == 0) result -= result / i; 
    while (n % i == 0) n /= i; 
  }
  if (n > 1) result -= result / n; 
  return result; 
} 
