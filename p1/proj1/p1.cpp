//
// Created by junsi on 2021/10/2.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point{
    int x;
    int y;
};

Point P0;

int ccw(Point p1, Point p2, Point p3)
// EFFECTS: return the cross product of P1P2 and P1P3
// If greater than zero, the polar angle of p3 is greater than p2.
// If smaller than zero, the polar angle of p3 is smaller than p2.
// Otherwise, the polar angle of p3 and p2 are equal.
{
    return(p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
}

int dis_sq(Point a, Point b)
// EFFECTS: return the square of the Euclidean distance of Point a and b
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

bool cmp(Point a, Point b)
// EFFECTS: the comparison function for sort to help to sort by polar angle
// If the polar angle of a is greater, return 0 to change order.
// If the polar angle of a is smaller, return 1 to do nothing.
// Otherwise, sort by distance.
{
    int val=ccw(P0,a,b);
    if(val==0){
        return dis_sq(P0, a) <= dis_sq(P0, b);
    }else return val > 0;
}

void Graham_scan(int n, vector<Point> &X, vector<Point> &S){
    // find out P0
    P0=X[0];
    int p0_ind=0;
    for (int j = 1; j <n ; ++j) {
        if(X[j].y<P0.y || (X[j].y==P0.y && X[j].x<P0.x)){
            P0=X[j];
            p0_ind=j;
        }
    }

    // sort the points in X by polar angle with P0.
    swap(X[p0_ind],X[0]);
    sort(X.begin()+1,X.end(),cmp);

    // delete the points which have the same polar angle with P0 except the farthest
    int n_after=1;
    for (int m = 0; m <n ; ++m) {
        while (m<n && X[m].x==P0.x && X[m].y==P0.y) ++m;
        if (m==n) break;
        while (m<n-1 && ccw(P0,X[m],X[m+1])==0) ++m;
        X[n_after]=X[m];
        ++n_after;
    }

    // Graham's scan loop
    for (int k = 0; k <n_after ; ++k) {
        while (S.size()>1 && ccw(S[S.size()-2],S[S.size()-1],X[k])<=0){
            S.pop_back();
        }
        S.push_back(X[k]);
    }
}

int main(){
    // input the number of points and the coordinates of points
    int n; cin>>n;
    if(n==0) return 0;
    vector<Point> X;
    int xin,yin;
    Point pin{};
    for (int i = 0; i <n ; ++i) {
        cin>>xin; cin>>yin;
        pin.x=xin; pin.y=yin;
        X.push_back(pin);
    }

    // execute Graham's scan
    vector<Point> S;
    Graham_scan(n,X,S);

    // output the points stored in S, i.e. a convex hull of the input points
    for (auto pout : S) {
        cout<<pout.x<<' '<<pout.y<<'\n';
    }
}
