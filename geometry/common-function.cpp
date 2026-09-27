struct point
{
 
    double x,y;
    void read()
    {
        cin>>x>>y;
    }
    bool operator == (point b)
    {
        return (x==b.x&& y==b.y);
    }
    point operator -(point b)
    {
        return {b.x-x,b.y-y};
    }
    double operator *(point b)
    {
        return (x*b.y)-(y*b.x);
    }
    double traingle(point a,point b)
    {
        point b1=a-*this;
        point b2=b-*this;
        return b1*b2;
    }
    double dot(point b)
    {
        return x*b.x+y*b.y;
    }
    double len()
    {
        return sqrtl(x*x+y*y);
    }
    void norm()
    {
        double z=len();
        x=x/z;
        y=y/z;
    }
};

point rotate(point b,double theta)
{
    return {-sin(theta)*b.y+cos(theta)*b.x ,cos(theta)*b.y+ sin(theta)*b.x};
}
 
void get_tangent(double r,point a,point& t1,point& t2)
{
    double d=a.len();
    double theta=acos(r/d);
    a.norm();
    a={a.x*r,a.y*r};
    t1=rotate(a,theta);
    t2=rotate(a,-theta);
}


double circle_intersect(point c1,double r1,point c2,double r2)
{
    if(r2>r1)
    {
        swap(r1,r2);
        swap(c1,c2);
    }
    double b=(c1-c2).len();
    if(b>=(r1+r2))
    {
        return 0;
    }
    if(r1>=b+r2)
    {
        return numbers::pi*r2*r2;
    }
    double ans=0;
    for(int i=0; i<2; i++)
    {
        double theta1 = ((r1*r1)+(b*b)-(r2*r2))/(2*r1*b);
        theta1=2*acosl(theta1);
        double s1=((r1*r1)*theta1)/2.0;
        s1=s1-((r1*r1 *sinl(theta1))/2.0);
        swap(c1,c2);
        swap(r1,r2);
        ans+=abs(s1);
    }
    return abs(ans);
}

// Find circle passes with 3 points, some times, there is no circle! (in case colinear)
bool findCircle(point a, point b, point c, pair<double, point>& circle) {
    if(isCollinear(a,b,c))
        return 0;
    point m1 = (b + a) * 0.5, v1 = b - a, pv1 = point(v1.Y, -v1.X);
    point m2 = (b + c) * 0.5, v2 = b - c, pv2 = point(v2.Y, -v2.X);
    point end1 = m1 + pv1, end2 = m2 + pv2, center;
    intersectSegments(m1, end1, m2, end2, center);
    circle = make_pair(length(vec(center, a)), center);
    return 1;
}



bool check_bounding_box(point a,point b,point c,point d)
{
    if((max(a.x,b.x) <min(c.x,d.x))  || (max(a.y,b.y) < min(c.y,d.y)) )return false;
    swap(a,c);
    swap(b,d);
    if( (max(a.x,b.x) <min(c.x,d.x))   || (max(a.y,b.y) < min(c.y,d.y)) )return false;

    return true;
}


void get_2segments_intersect(point a,point b,point c,point d)
{

long double A0,B0,C0,A1,B1,C1;
                A0 = a.y - b.y;
                B0 = b.x - a.x;
                C0 = A0 * a.x + B0 * a.y;
                A1=c.y-d.y;
                B1=d.x-c.x;
                C1=A1*c.x+B1*c.y;
                long double x=(C0*B1-C1*B0)/((A0*B1)-(A1*B0));
                if(B0!=0)
                {
                    long double y=(C0-A0*x)/B0;
                    cout<<fixed<<setprecision(2)<<x<<" "<<y<<"\n";
                }
                else if(B1!=0)
                {
                    long double y=(C1-A1*x)/B1;
                    cout<<fixed<<setprecision(2)<<x<<" "<<y<<"\n";
                }
}

----------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;
#define ll long long int
typedef long double ld;
typedef complex<double> point;  // it can be long long not double

template<class T>
istream& operator>>(istream& is, complex<T>& p) {
    T x, y;
    is >> x >> y;
    p.real(x);
    p.imag(y);
    return is;
}

#define PI acos(-1.0)
#define EPS 1e-8
#define X real()
#define Y imag()
#define angle(a)  (atan2((a).imag(), (a).real())) // angle with origin
#define length(a)   (hypot((a).imag(), (a).real()))
#define dist(v)   sqrtl((v).real() * (v).real() + (v).imag() * (v).imag())
#define vec(a,b)  ((b)-(a))
#define dp(a,b)   ( (conj(a)*(b)).real() )
#define cp(a,b)   ( (conj(a)*(b)).imag() ) // product = area of parallelogram
#define normalize(a)    (a)/length(a)

//----------------------------------------------------------------------------------------------------------------------------------------------------------
point rotate(point p, double angle, point around = point(0, 0)) {
    p -= around;
    return (p * exp(point(0, angle))) + around;
}

int dcmp(double a,double b){ // check two values are same or not
    if(fabs(a-b) <= 1e-10)
        return 0;
    return a < b ? -1 : 1;
}

bool same(point p1, point p2) { // check two points are same or not
    return dp(vec(p1, p2), vec(p1, p2)) < EPS;
}

double fixAngle(double A) {
    return A > 1 ? 1 : (A < -1 ? -1 : A);
}
//------------------------------------------------------------------------------
double angleO(point a, point O, point b) {
    point v1(a - O), v2(b - O);
    return acos(fixAngle(dp(v1, v2) / dist(v1) / dist(v2)));
}

double getSide_a_bAB(double b, double A, double B) {
    return (sin(A) * b) / sin(B);
}

double getAngle_A_abB(double a, double b, double B) {
    return asin(fixAngle((a * sin(B)) / b));
}

double getAngle_A_abc(double a, double b, double c) {
    return acos(fixAngle((b * b + c * c - a * a) / (2 * b * c)));
}
//------------------------------------------------------------------------------
bool isCollinear(point a, point b, point c) { // are three points on the same line?
    return fabs(cp(vec(a, b), vec(a, c))) < EPS;
}

bool isPointOnRay(point a, point b, point c) { // is point c on a-b ray?
    if (!isCollinear(a, b, c))
        return false;
    return dcmp(dp(vec(a, b), vec(a, c)), 0) == 1;
}

bool isPointOnSegment(point a, point b, point c) { // is point c on a-b segment?
    return isPointOnRay(a, b, c) && isPointOnRay(b, a, c);
}

double distToLine(point p0, point p1, point p2) { // point c distance to line a-b
    return fabs(cp(vec(p0, p1), vec(p0, p2)) / length(vec(p1, p0)));
}

double distToSegment(point p0, point p1, point p2) { // point c distance to segment a-b
    double d1, d2;
    point v1 = p1 - p0, v2 = p2 - p0;
    if ((d1 = dp(v1, v2)) <= 0)	return length(vec(p0, p2));
    if ((d2 = dp(v1, v1)) <= d1) return length(vec(p1, p2));
    double t = d1 / d2;
    return length(vec((p0 + v1 * t), p2));
}

point pointToSegment(point p0, point p1, point p2) { // nearest point in segment p0-p1 to point p2
    double d1, d2;
    point v1 = p1 - p0, v2 = p2 - p0;
    if ((d1 = dp(v1, v2)) <= 0)	return p0;
    if ((d2 = dp(v1, v1)) <= d1) return p1;
    double t = d1 / d2;
    return (p0 + v1 * t);
}

// find point intersect in line a-b with c-d
bool intersectSegments(point a, point b, point c, point d, point& intersect) {
    double d1 = cp(vec(b, a), vec(c, d)), d2 = cp(vec(c, a), vec(c, d)), d3 = cp(vec(b, a), vec(c, a));
    if (fabs(d1) < EPS)
        return false;
    double t1 = d2 / d1, t2 = d3 / d1;
    intersect = a + (b - a) * t1;
    if (t1 < -EPS || t2 < -EPS || t2 > 1 + EPS)
        return false;
    return true;
}
//------------------------------------------------------------------------------
double triangleAreaPoints(point p0, point p1, point p2) { // find area of triangle using points
    double a = length(vec(p1, p0)), b = length(vec(p2, p0)), c = length(vec(p2, p1));
    double s = (a + b + c) / 2.0;
    return sqrt((s - a) * (s - b) * (s - c) * s);
}

double triangleAreaLength(double a, double b, double c) { // find area of triangle using length
    double s = (a + b + c) / 2.0;
    return sqrt((s - a) * (s - b) * (s - c) * s);
}

bool pointInTriangle(point a, point b, point c, point pt) { // check if point in triangle
    ll s1 = fabs(cp(vec(a,b), vec(a,c)));
    ll s2 = fabs(cp(vec(pt,a), vec(pt,b))) + fabs(cp(vec(pt, b), vec(pt, c))) + fabs(cp(vec(pt, a), vec(pt, c)));
    return s1 == s2;
}

// Find largest Circle Inside the triangle
bool circleInTriangle(point a, point b, point c, pair<double, point>& circle) {
    double ab = length(a - b), bc = length(b - c),ca = length(c - a);
    double s = 0.5 * (ab + bc + ca);
    circle.first = triangleAreaLength(ab, bc, ca) / s;
    // if (fabs(circle.first) < EPS) return 0;
    double ratio = length(a - b) / length(a - c);
    point p1 = b + (vec(b, c) * (ratio / (1 + ratio)));
    ratio = length(b - a) / length(b - c);
    point p2 = a + (vec(a, c) * (ratio / (1 + ratio)));
    return intersectSegments(a, p1, b, p2, circle.second);
}
//------------------------------------------------------------------------------
// Find circle passes with 3 points, some times, there is no circle! (in case colinear)
bool findCircle(point a, point b, point c, pair<double, point>& circle) {
    if(isCollinear(a,b,c))
        return 0;
    point m1 = (b + a) * 0.5, v1 = b - a, pv1 = point(v1.Y, -v1.X);
    point m2 = (b + c) * 0.5, v2 = b - c, pv2 = point(v2.Y, -v2.X);
    point end1 = m1 + pv1, end2 = m2 + pv2, center;
    intersectSegments(m1, end1, m2, end2, center);
    circle = make_pair(length(vec(center, a)), center);
    return 1;
}

// Find points intersect with line and circle!
vector<point> intersectLineCircle(point p0, point p1, point C, double r) {
    double a = dp(vec(p0, p1), vec(p0, p1)), b = 2 * dp(vec(p0, p1), vec(C, p0)), c = dp(vec(C, p0), vec(C, p0)) - r * r;
    double f = b * b - 4 * a * c;
    vector<point> v;
    if (dcmp(f, 0) >= 0) {
        if (dcmp(f, 0) == 0)
            f = 0;
        double t1 = (-b + sqrt(f)) / (2 * a);
        double t2 = (-b - sqrt(f)) / (2 * a);
        v.push_back(p0 + t1 * (p1 - p0));
        if (dcmp(f, 0) != 0)
            v.push_back(p0 + t2 * (p1 - p0));
    }
    return v;
}

// Find points intersect with two circles!
vector<point> intersectCircleCircle(point c1, double r1, point c2, double r2) {
    if (same(c1, c2) && dcmp(r1, r2) == 0 && dcmp(r1, 0) > 0)
        return vector<point>(3, c1);
    double ang1 = angle(vec(c1, c2)), ang2 = getAngle_A_abc(r2, r1, length(vec(c1, c2)));
    if (::isnan(ang2))
        ang2=0;
    vector<point> v(1, polar(r1, ang1 + ang2) + c1);
    if (dcmp(dp(vec(c1, v[0]), vec(c1, v[0])), r1 * r1) != 0 ||
        dcmp(dp(vec(c2, v[0]), vec(c2, v[0])), r2 * r2) != 0)
        return vector<point>();
    v.push_back(polar(r1, ang1 - ang2) + c1);
    if (same(v[0], v[1]))
        v.pop_back();
    return v;
}

// Find area of intersect region between two circles!
ld circleCircleIntersectionArea(point cen1, ld r1, point cen2, ld r2) {
    ld dis = hypot(cen1.X - cen2.X, cen1.Y - cen2.Y);
    if (dis > r1 + r2)return 0;
    if (dis <= fabs(r2 - r1) && r1 >= r2)
        return PI * r2 * r2;
    if (dis <= fabs(r2 - r1) && r1 < r2)
        return PI * r1 * r1;
    ld a = r1 * r1, b = r2 * r2;
    ld ang1 = acos((a + dis * dis - b) / (2 * r1 * dis)) * 2;
    ld ang2 = acos((b + dis * dis - a) / (2 * r2 * dis)) * 2;
    ld ret1 = .5 * b * (ang2 - sin(ang2));
    ld ret2 = .5 * a * (ang1 - sin(ang1));
    return ret1 + ret2;
}
//------------------------------------------------------------------------------

double toDegree(double x){
    return x*180/PI;
}

bool right_or_left(point p1,point p2) {
    ll x = p2.X * p1.Y - p1.X * p2.Y;
    return (x > 0 ? 1 : 0);
}











