import java.awt.geom.*;

public class geojava {
  private static final double EPS = 1e-10;

  private static int cmp(double x, double y) {
    return (x<= y + EPS) ? (x + EPS < y) ? -1 : 0 : 1;
  }

  //Point Class
  private static class Point implements Comparable {
    public double x, y;

    public Point(double x, double y){
      this.x = x;
      this.y = y;
    }

    public Point(){
      this.x = this.y = 0.0;
    }

    public double dotProduct(Point o){
      return this.x * o.x + this.y * o.y;
    }

    public double crossProduct(Point o){
      return this.x*o.y - this.y*o.x;
    }

    public Point add(Point o){
      return new Point(this.x + o.x, this.y + o.y);
    }

    public Point substract(Point o){
      return new Point(this.x - o.x, this.y - o.y);
    }

    public Point multiply (double m){
      return new Point(this.x * m, this.y * m);
    }

    public Point divide (double m){
      return new Point (this.x/m, this.y/m);
    }

    //@Override
    public int compareTo(Object k){
      if(k instanceof Point){
        Point o = (Point)k;
        if (this.x < o.x) return -1;
        if (this.x > o.x) return 1;
        if (this.y < o.y) return -1;
        if (this.y > o.y) return 1;
        return 0;
      }
      return -5; //No es un punto!
    }

    //Euclidean distance Between Two Points

    double distance(Point o){
      double d1 = x-o.x, d2 = y-o.y;
      return Math.sqrt(d1*d1+d2*d2);
    }
  }//End of point class

  private static double angle(Point p, Point q,
    Point r){
    Point u = p.substract(r), v = q.substract(r);
    return Math.atan2(u.crossProduct(v), u.dotProduct(v));
  }

  private static int turn (Point p, Point q, Point r){
    return cmp((p.substract(r)).crossProduct(q.substract(r)),0.0);
  }

  private static boolean between(Point p, Point q,
    Point r){
    return turn(p,r,q)==0 &&
      cmp((p.substract(r)).dotProduct(q.substract(r)),0.0)<=0;
  }

  private static int inPolygon(Point p, Point[] polygon,
    int polygonSize){
    double a = 0; int N = polygonSize;
    for(int i=0;i < N; ++i){
      if(between(polygon[i], polygon[(i+1)%N], p))
        return -1;
      a+=angle(polygon[i], polygon[(i+1)%N], p);
    }
    return (cmp(a,0.0)==0)? 0 : 1;
  }

  private static Point GetIntersection(Line2D.Double l1,
    Line2D.Double l2){
    double A1 = l1.y2 - l1.y1;
    double B1 = l1.x1 - l1.x2;
    double C1 = A1 * l1.x1 + B1*l1.y1;

    double A2 = l2.y2 - l2.y1;
    double B2 = l2.x1 - l2.x2;
    double C2 = A2 * l2.x1 + B2*l2.y1;

    double det = A1*B2 - A2*B1;

    if(det==0){
      //Lines are parallel. Check if they are on the same line
      double m1 = A1/B1;
      double m2 = A2/B2;
      //Check whether their slopes are the same or not,
      //or if they are vertical
      if(cmp(m1,m2)==0 || (B1==0 && B2==0)) {
        //Cuidado con la implementación aqui!
        if((l1.x2==l2.x1 && l1.y2 == l2.y1) ||
          (l1.x2==l2.x2 && l1.y2 == l2.y2))
          return new Point(l1.x2, l1.y2);

        if((l1.x2==l2.x1 && l1.y2==l2.y1) ||
          (l1.x2==l2.x2 && l1.y2==l2.y2))
          return new Point(l1.x2, l1.y2);
      }
      return null;
    }
    double x = (B2*C1 - B1*C2)/det;
    double y = (A1*C2 - A2*C1)/det;
    return new Point(x,y);
  }
}
