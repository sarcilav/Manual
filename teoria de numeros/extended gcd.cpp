/**
 * GCD extendido
 * Alejandro Peláez
 */
#include <cstdio>

int egcd(int a, int b, int &x, int &y){
    x = 0, y = 1;
    int lastx = 1, lasty = 0;
    int quot, temp;
    while(b != 0){
        quot = a/b;
        temp = b;
        b = a%b;
        a = temp;
        temp = x;
        x = lastx - quot*temp;
        lastx = temp;
        temp = y;
        y = lasty - quot*temp;
        lasty = temp;
    }
    x = lastx, y = lasty;
    return a;
}

int main(){
    int a, b, x, y, g;
    while(scanf("%d%d",&a,&b) && (a+b)){
        g = egcd(a,b,x,y);
        printf("%d = %d*(%d) + %d*(%d)\n", g,a,x,b,y);
    }
    return 0;
}
