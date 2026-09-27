#define _GLIBCXX_FILESYSTEM
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define F first
#define S second
#define int long long
using namespace std;



struct p
{
    int x,y;
    void read()
    {
        cin>>x>>y;
    }
    p operator -=(p p2)
    {
        x=x-p2.x;
        y=y-p2.y;
    }
    p operator -(p p2)
    {
        return p{p2.x-x,p2.y-y};
    }
    int  operator * (p p1)
    {
        return this->x*p1.y - this->y*p1.x;
    }
    int traingle(p p1,p p2)
    {
        return (p1-*this)* (p2-*this);
    }

    bool  operator < (p y)
    {
        return this->x<y.x;
    }
};

bool intersect(p a,p b,p c,p d)  // intersection of 2 colinear segments
{
    if( max(a.x,b.x)< min(c.x,d.x) || max(a.y,b.y )< min(c.y,d.y)) return false;
    swap(a,c);
    swap(b,d);
    if( max(a.x,b.x)< min(c.x,d.x) || max(a.y,b.y )< min(c.y,d.y)) return false;

    return true;
}


bool segments_intersect(p a,p b, p c, p d)   // intersect of any 2 segment
{
    int d1=a.traingle(b,c);
    int d2=a.traingle(b,d);
    if(d1>0 && d2>0 || d1<0 && d2<0)
    {
        return false;
    }
    else if(d1==0 && d2==0)
    {
        if(intersect(a,b,c,d))return true;
        else return false;
    }
    else
    {
        int d3=c.traingle(d,a);
        int d4=c.traingle(d,b);
        if(d3>=0 && d4<=0    || d3<=0 && d4>=0)
        {
            return true;
        }
        else return false;
    }
}


bool point_inside(p a,p b,p c)    // check if point inside segment
{
    if(a.traingle(b,c)!=0)return 0;

    return c.x>=min(a.x,b.x) && c.x<=max(a.x,b.x) && c.y>=min(a.y,b.y) && c.y<=max(a.y,b.y);
}


signed main()
{
    IOS
    return 0;
}
