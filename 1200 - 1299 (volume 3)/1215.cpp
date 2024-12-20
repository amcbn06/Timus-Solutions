/* 1215. Exactness of Projectile Hit

Strategy:
Check if the point is inside polygon, else find the minimum distance to a side of the polygon
Be careful about how you implement your geometry

* Time complexity: O(N)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

namespace Geometry {
    const double eps = 1e-10;

    inline bool _eq(long double a, long double b) { return abs(a - b) <= eps; }
    inline bool _ls(long double a, long double b) { return b - a > eps; }
    inline bool _gt(long double a, long double b) { return a - b > eps; }
    inline bool _lse(long double a, long double b) { return _eq(a, b) || _ls(a, b); }
    inline bool _gte(long double a, long double b) { return _eq(a, b) || _gt(a, b); }
    inline long double min(long double a, long double b) { return _ls(a, b) ? a : b; }
    inline long double max(long double a, long double b) { return _ls(a, b) ? b : a; }


    struct Point {
        long double x = 0, y = 0;
        Point() {}
        Point(long double x, long double y) : x(x), y(y) {

        }
        friend istream& operator>>(istream& is, Point& pt) {
            return is >> pt.x >> pt.y;
        }
        friend ostream& operator<<(ostream& os, Point& pt) {
            return os << pt.x << " " << pt.y;
        }
    };

    // the distance from point `u` to point `v`
    long double distance(Point u, Point v) {
        return sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2));
    }

    // area of triangle determined by three points
    long double area(Point u, Point v, Point w) {
        return abs(u.x * (v.y - w.y) + v.x * (w.y - u.y) + w.x * (u.y - v.y)) / 2;
    }

    struct Segment {
        // a * x + b * y + c
        long double a = 0, b = 0, c = 0;
        Point u, v;
        Segment() {}
        Segment(Point u, Point v) : u(u), v(v) {
            a = v.y - u.y; // a = 0 => horizontal line
            b = u.x - v.x; // b = 0 => vertical line
            c = u.y * v.x - u.x * v.y;
        }
    };

    // does the segment `s` include point `p`
    bool includes(Segment s, Point p) {
        // satisfies the line equation and is in bounds
        return _eq(s.a * p.x + s.b * p.y + s.c, 0) && _lse(min(s.u.x, s.v.x), p.x) && _lse(p.x, max(s.u.x, s.v.x)) && _lse(min(s.u.y, s.v.y), p.y) && _lse(p.y, max(s.u.y, s.v.y));
    }

    // the distance from point `p` to the segment `s`
    long double distance(Point p, Segment s) {
        assert(s.a * s.a + s.b * s.b != 0);
        Point q; // the projection of `u` onto the line of the segment
        q.x = (s.b * (s.b * p.x - s.a * p.y) - s.a * s.c) / (s.a * s.a + s.b * s.b);
        q.y = (s.a * (s.a * p.y - s.b * p.x) - s.b * s.c) / (s.a * s.a + s.b * s.b);
        if (includes(s, q)) {
            return distance(p, q);
        }
        else {
            return min(distance(p, s.u), distance(p, s.v));
        }
    }
}

using namespace Geometry;

const int nmax = 200;
Point S;
int n;
Point p[nmax + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    cin >> S >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    bool inside = false;
    for (int i = 2; i < n; ++i) {
        long double foo = area(S, p[1], p[i]) + area(S, p[1], p[i + 1]) + area(S, p[i], p[i + 1]);
        if (_eq(foo, area(p[1], p[i], p[i + 1]))) {
            inside = true;
        }
    }
    long double answer = 1e18;
    if (inside) {
        answer = 0;
    }
    else {
        for (int i = 1; i <= n; ++i) {
            Segment seg(p[i], p[i % n + 1]);
            long double foo = distance(S, seg);
            answer = min(answer, foo);
        }
    }
    assert(answer != 1e18);
    cout << fixed << setprecision(3) << 2 * answer;
}
