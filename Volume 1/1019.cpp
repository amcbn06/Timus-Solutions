/* 1019. Line Painting

Strategy:
We keep some events about the operations using a hashmap; for every repainting we'll add an event
at the position where the segment begins and at the first positon after the segment ends, keeping
information about the time of the update, the color and whether the range beings or ends;
At every moment we'll keep a set with the current updates sorted decreasingly by the time of the update;
The latest update dictates the color of the current range 

Performance:
We'll add 2N elements to a hashmap => O(Nlogn)
We'll be traversing only through at most 2N intervals from 0 to 10^9 => O(N)

Observations:
!!! We're working with open intervals (a, b)

0   1   2   3
| 0 | 1 | 2 | 3 |

* Time complexity: O(NlogN)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

const int nmax = 5000;
int n;
struct event {
	int when;
	char color;
	bool begins;
};
map<int, vector<event>> events;

void add_segment(int i, int l, int r, char c) {
	events[l].push_back(event{ i, c, true });
	events[r].push_back(event{ i, c, false });
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	add_segment(0, 0, 1000'000'000, 'w');
	for (int i = 1; i <= n; ++i) {
		int l, r;
		char c;
		cin >> l >> r >> c;
		add_segment(i, l, r, c);
	}
	set<pair<int, char>, greater<pair<int, char>>> updates;
	pair<int, int> segment{ 0, -1 }, best{ 0, -1 };
	char color = 0;
	for (auto it = events.begin(); next(it) != events.end(); ++it) {
		int l = it->first, r = next(it)->first;
		for (auto& e : it->second) {
			if (e.begins) {
				updates.insert({ e.when, e.color });
			}
			else {
				updates.erase({ e.when, e.color });
			}
		}
		//cerr << "From " << l << " to " << r << " the color is " << updates.begin()->second << "\n";
		if (color == updates.begin()->second) {
			segment.second = r;
		}
		else {
			segment = { l, r };
			color = updates.begin()->second;
		}
		if (color == 'w' && segment.second - segment.first > best.second - best.first){
			best = segment;
		}
	}
	cout << best.first << " " << best.second;
}
