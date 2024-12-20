/* 1111. Squares

Strategy:
Using some (a lot of geometry), we can find the coordinates of the corners for each square,
we can find whether the point is inside or outside the square and we can find the distance
from the point to each of the square's sides, thus calculating the distance from the point to the square

Pay attention to:
- how you check if a point is inside a square (handle the case in which the square is a point)
- how you compute the distance from a point to a segment: it's either the distance to the projection or the distance to one of the end points
- the fact that if a point is inside a square the distance is 0
- the fact that if two squares have the same distance to P, we sort them by the lower id
- precision errors
- the fact that squares can actually be points
- the sort might break

In case of errors, feel free to try the tests from the "Discussion" section of the problem
Also something that shocked me is that when i submitted my solution using the G++ compiler,
i got lots of runtime errors, yet when i used the Clang++ compiler, i got accepted
(I wasted 3 hours of my life figuring this out and I still don't know why this happens)

* Time complexity: O(N) aproximatively, with a constant from all the geometry

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
        return _lse(min(s.u.x, s.v.x), p.x) && _lse(p.x, max(s.u.x, s.v.x)) && _lse(min(s.u.y, s.v.y), p.y) && _lse(p.y, max(s.u.y, s.v.y));
    }

    // the distance from point `p` to the segment `s`
    long double distance(Point p, Segment s) {
        assert(s.a * s.a + s.b * s.b != 0);
        Point q; // the projection of `u` onto the line of the segment
        q.x = (s.b * (s.b * p.x - s.a * p.y) - s.a * s.c) / (s.a * s.a + s.b * s.b);
        q.y = (s.a * (s.a * p.y - s.b * p.x) - s.b * s.c) / (s.a * s.a + s.b * s.b);
        if (includes(s, p)) {
            return distance(p, q);
        }
        else {
            return min(distance(p, s.u), distance(p, s.v));
        }
    }

    struct Square {
        Point corner[4]; // the four corners
        Segment side[4]; // and the four sides
        Square() {}
        Square(Point c1, Point c2) {
            corner[0] = c1;
            corner[2] = c2;
            long double foo = (c1.x + c2.x + c1.y + c2.y) / 2;
            corner[1] = Point(foo - c2.y, foo - c1.x);
            corner[3] = Point(foo - c1.y, foo - c2.x);
            for (int k = 0; k < 4; ++k) {
                side[k] = Segment(corner[k], corner[(k + 1) % 4]);
            }
        }
    };

    // area of square `sq`
    long double area(Square sq) {
        return area(sq.corner[0], sq.corner[1], sq.corner[2]) + area(sq.corner[0], sq.corner[2], sq.corner[3]);
    }

    // does the square `sq` include point `p`
    bool includes(Square sq, Point p) {
        // handle the case in which the square has area equal to zero
        if (_eq(area(sq), 0)) {
            return _eq(distance(p, sq.corner[0]), 0);
        }
        else {
            long double total = 0;
            for (int k = 0; k < 4; ++k) {
                total += area(p, sq.corner[k], sq.corner[(k + 1) % 4]);
            }
            return _eq(area(sq), total);
        }
    }

    // the minimum distance from point `p` to the sides of square `sq`
    long double distance(Point p, Square sq) {
        // handle the case in which the square has area equal to zero
        if (_eq(area(sq), 0)) {
            return distance(p, sq.corner[0]);
        }
        else {
            long double aux = 1e18;
            for (int k = 0; k < 4; ++k) {
                aux = min(aux, distance(p, sq.side[k]));
            }
            return aux;
        }
    }
}

using namespace Geometry;

const int nmax = 100;
int n;
Square sq[nmax + 1];
Point P;

long double dist[nmax + 1];
int order[nmax + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        Point c1, c2;
        cin >> c1 >> c2;
        sq[i] = Square(c1, c2);
    }
    cin >> P;
    for (int i = 1; i <= n; ++i) {
        if (includes(sq[i], P)) {
            dist[i] = 0;
        }
        else {
            dist[i] = distance(P, sq[i]);
        }
    }
    iota(order + 1, order + n + 1, 1);
    stable_sort(order + 1, order + n + 1, [&](int i, int j) {
        return _ls(dist[i], dist[j]);
    });
    for (int i = 1; i <= n; ++i) {
        cout << order[i] << " ";
    }
}
