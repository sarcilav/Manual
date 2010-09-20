// Returns true if pXq is inside aXb
bool cabe(long p, long q, long a, long b){
    long x,y,z,q; if(p<q) swap(p,q); if(a<b) swap(a,b);
    if(p<=a && q<=b) return true;
    if(p==q) return b>=q;
    x = 2*p*q*a; y=p*p-q*q; z=p*p+q*q; w=z-a*a;
    return p>a && 1.0*b*z >= x+y*sqrt(w) - 1e-10;
}

// Centroide (centro de masa) de un polígono
// pt[i][0] = pt[i].x  |  pt[i][1] = pt[i].y
// Area will return positive or negative depending on the points order
double area(vector<vector<double> > &pt){
    double r = 0.0; int t = pt.size();
    for(int i = 0, j = 1; i<t; i++, j = j+1 == t? 0 : j+1){
        r+= (pt[i][0] * pt[j][1] - pt[i][1] * pt[j][0]);
    }
    return r/2.0;
}

pair<double, double> centroide(vector<vector<double> > &pt){
    double d = area(pt) * 6.0;
    double p[2];
    p[0] = p[1] = 0.0;
    for(int i = 0, j = 1, t = pt.size(); i<t; i++, 
        j = j+1 ==t ? 0 : j+1)
	for(int k = 0; k<2;k++)
	    p[k] += (pt[i][k] + pt[j][k]) * \
	        (pt[i][0] * pt[j][1] - pt[j][0] * pt[i][1]);
    return pair<double, double>(pt[0]/d, pt[1]/d);
}
