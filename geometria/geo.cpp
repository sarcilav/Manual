const int INF = 0x3F3F3F3F;
const int NULO = -1;
const double EPS = 1e-10;

//If x==y, returns 0
//If x>y, returns 1
//If x<y, returns -1
int cmp(double x,double y=0, double tol=EPS){
    return( x<=y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

struct point {
    double x,y;
    point(double x=0, double y=0):x(x),y(y){}

    point operator + (const point &q) { return point (x + q.x, y+q.y) ;}
    point operator  -  (const point &q) { return point (x - q.x,  y-q.y)   ;}
    point operator * (const double &t)  {return point(x*t , y*t); }
    point operator  /  (const double &t) {return point(x/t , y/t);  }
    double operator *(const point &q)  { return x*q.x + y*q.y; } //Dot Product
    double operator %(const point &q) { return x*q.y - y*q.x; } //Cross Product

    int cmp(point q) const {
	if(int t= ::cmp(x,q.x)) return t;
	return ::cmp(y,q.y);
    }

    bool operator ==(const point &q) const { return cmp(q) == 0; }
    bool operator != (const point &q) const { return cmp(q) != 0; }
    bool operator < (const point &q) const { return cmp(q) < 0; }

    friend ostream& operator <<(ostream& o, point p){
	return o<<"("<<p.x<<", "<<p.y<<")";
    }

    //Distancia entre dos puntos
    double Distance(const point &o) const{
	double d1 = x-o.x, d2=y-o.y;
	return sqrt(d1*d1+d2*d2);
    }
    
    static point pivot;
};

typedef vector<point> polygon;
typedef pair<point, double> circle;

point point::pivot(0,0);

double abs(point p) { return hypot(p.x,p.y); }
double arg(point p) { return atan2(p.y,p.x); }

/**
 * Calcula el signo de giro entre dos vectores definidos
 * por (p-r) y (q-r)
 **/
inline int turn(point &p, point &q, point &r){
    return ::cmp((p-r)%(q-r));
}

int ccw (point p, point q, point r) {
    return cmp((p-r)%(q-r));
}

double angle(point p, point q, point r) {
    point u = p-q, v=r-q;
    return atan2(u%v, u*v);
}

//Decide si q esta sobre el segmento PR
bool between(point p, point q, point r){
    return ccw(p,q,r)==0 && cmp((p-q)*(r-q))<=0;
}

//Decide si dos segmentos PQ y RS tienen puntos en comun
bool seg_intersect(point p, point q, point r, point s){
    point A = q-p, B=s-r, C=r-p, D=s-q;
    int a = cmp(A%C) + 2 * cmp(A%D);
    int b = cmp(B%C) + 2 * cmp(B%D);
    if(a==3 || a== -3 || b == 3 || b == -3) return false;
    if(a ||b || p == r || p == s || q == r || q == s) return true;
    int t = (p<r) + (p<s) + (q<r) + (q<s);
    return t!=0 && t!=4;
}

//Calcula la distancia de un punto R al segmento PQ
double seg_distance(point p, point q, point r){
    point A = r - q, B = r - p, C = q - p;
    double a = A * A, b = B * B, c = C * C;
    if (cmp(b,a+c)>=0) return  sqrt(a);
    else if (cmp(a, b+c) >=0) return sqrt(b);
    return fabs(A % B) / sqrt (c);
}

//Califica un punto P con ralacion al poligono T
//Retorna 0,                -1,                        1
//En el exterior, en la frontera, en el interior respectivamente
int in_poly(point p, polygon &T){
    double a = 0; int N = T.size();
    for(int i=0; i < N; ++i) {
	if (between(T[i], p, T[(i+1) % N])) return -1;
	a+=angle(T[i],p,T[(i+1) % N]);
    }
    return cmp(a) != 0;
}

//Comparacion radial
bool radial_lt(point p, point q){
    point P = p-point::pivot, Q = q - point::pivot;
    double R = P % Q;
    if(::cmp(R)) return R > 0;
    return ::cmp(P*P, Q*Q) < 0;
}

//Destruye la lista de puntos T
polygon convex_hull(vector<point> &T){
    int j=0, k, n=T.size(); polygon U(n);
    
    point::pivot = *min_element(all(T));
    sort(all(T), radial_lt);
    for(k = n-2; k>=0 && ccw(T[0], T[n-1], T[k])==0; k--) ;
    reverse((k+1) + all(T));

    for(int i=0; i< n; ++i){
	//cambia >= por > para mantener los puntos colineales
	while (j > 1 && ccw(U[j-1], U[j-2], T[i]) >= 0) j--;
	U[j++] = T[i];
    }
    U.erase(j + all(U)); // U.erase(j+U.begin(), U.end() )
    return U;
}

//Returns the cuadrant where the point is
//Retorna 5 si el punto es (0, 0)
int quadrant(const point &p) {
    if(::cmp(p.x)==0 && ::cmp(p.y)==0) return 5;
    if(::cmp(p.y) == 1) {
	if(::cmp(p.x)==1) return 1;
	return 2;
    }
    if(::cmp(p.y)==0){
	if(::cmp(p.x)==1 || ::cmp(p.x)==0) return 1;
	return 3;
    }
    if(::cmp(p.x)==-1) return 3;
    return 4;
}

//Comparator to sort the points by their angle
bool PolarCom(point &p, point &q) {
    point P = P - point::pivot, Q = q - point::pivot;
    int q1 = quadrant(P), q2 = quadrant(Q);
    if(q1!=q2) return q1<q2;
    double R = P%Q;
    if(::cmp(R)) return R>0;
    return ::cmp(P*P, Q*Q) < 0;
}

//Calcula el area de un poligono T
double poly_area(polygon &T){
    double s = 0; int n = T.size();
    for(int i=0; i < n; ++i)
	s+= T[i] % T[(i+1)%n];
    return  fabs(s)/2.0;
}

//Encuentra el punto de interseccion de dos rectas PQ y RS
point line_intersect(point p, point q, point r, point s){
    point a = q - p, b = s - r, c = point(p % q, r % s);
    return point (point(a.x , b.x) % c, point(a.y , b.y) % c) / (a % b);
}

//Encuentra el menor circulo que contiene todos los puntos dados
bool in_circle(circle C, point p){
    return cmp(abs(p - C.first), C.second) <= 0;
}

point circumcenter(point p, point q, point r) {
    point a = p - r, b = q - r, c = point(a * (p+r) / 2, b * (q+r) / 2);
    return point(c % point(a.y, b.y), point(a.x, b.x) % c) / (a % b);
}

circle spanning_circle(vector<point> &T) {
    int n = T.size();
    random_shuffle(all(T));
    circle C(point(), -INFINITY);
    for(int i=0; i < n; i++) if (!in_circle(C, T[i])) {
	    C = circle(T[i], 0);
	    for(int j = 0; j < i; j++) if (!in_circle(C, T[j])) {
		    C = circle((T[i]+T[j]) / 2, abs(T[i] - T[j])/2);
		    for(int k = 0; k < j; k++) if (!in_circle(C, T[k])) {
			    point o = circumcenter(T[i], T[j], T[k]);
			    C = circle(o, abs(o - T[k]));
			}
		}
	}
    return C;
}
//Fin del spanning_circle

//Saca la interseccion de dos poligonos convexos P y Q.
//Tanto P como Q deben estar orientados positivamente

polygon poly_intersect(polygon &P, polygon &Q) {
    int m = Q.size(), n = P.size();
    int a = 0, b = 0, aa = 0, ba = 0, inflag = 0;
    polygon R;
    while( (aa < n || ba < m) && aa < 2*n && ba < 2*m) {
	point p1 = P[a], p2 = P[(a+1) % n], q1 = Q[b], q2 = Q[(b+1) % m];
	point A = p2 - p1, B = q2 - q1;
	int cross = cmp(A%B), ha = ccw(p2, q2, p1), hb=ccw(q2, p2, q1);
	if (cross == 0 && ccw(p1, q1, p2) == 0 && cmp(A*B) < 0) {
	    if(between(p1, q1, p2)) R.pb(q1);
	    if(between(p1, q2, p2)) R.pb(q2);
	    if(between(q1, p1, q2)) R.pb(p1);
	    if(between(q1, p2, q2)) R.pb(p2);
	    if (R.size() < 2) return polygon ();
	    inflag = 1; break;
	} else if(cross != 0 && seg_intersect(p1, p2, q1, q2)) {
	    if (inflag==0) aa = ba = 0;
	    R.pb(line_intersect(p1, p2, q1, q2));
	    inflag = (hb > 0) ? 1 : -1;
	}
	if (cross == 0 && hb < 0 && ha < 0) return R;
	bool t = cross == 0 && hb ==0 && ha == 0;
	if (t  ? (inflag == 1) : (cross >=0) ? (ha <= 0) : (hb > 0) ) {
	    if(inflag == -1) R.pb(q2);
	    ba++; b++; b%=m;
	} else {
	    if(inflag == 1) R.pb(p2);
	    aa++;a++;a%=n;
	}
    }
    if (inflag == 0) {
	if (in_poly(P[0], Q)) return P;
	if (in_poly(Q[0], P)) return Q;
    }
    R.erase(unique(all(R)) , R.end());
    if (R.size() > 1 && R.front() == R.back()) R.pop_back();
    return R;
}
