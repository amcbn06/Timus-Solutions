/* 1116. Piecewise Constant Function

Strategy:
If A is the set of points defined for F1 and B is the set of points defined for F2,
we'll compute A - B; how do we do that => we can create events to know at which
position the values from either function change or become undefined
If previously the value for A was defined and the value for B was undefined
and now these values change, it means we reached the end of a interval from the "subsettraction"

* Time complexity: O((N + M)log(N + M))
* Space complexity: O(N + M)

*/
#include <bits/stdc++.h>
using namespace std;

const int undefined = 0x3f3f3f3f;

struct Event {
	int x;
	int value;
	bool add;
	int which;
	friend bool operator<(const Event& lhs, const Event& rhs) {
		return lhs.x == rhs.x ? lhs.add < rhs.add : lhs.x < rhs.x;
	}
};

struct Interval {
	int l, r;
	int value;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	vector<Event> events;
	for (int i = 0; i < 2; ++i) {
		int n;
		cin >> n;
		for (int j = 0; j < n; ++j) {
			int l, r, value;
			cin >> l >> r >> value;
			events.push_back(Event{ l, value, true, i });
			events.push_back(Event{ r, value, false, i });
		}
	}
	sort(events.begin(), events.end());
	int value[2]{ undefined, undefined };
	vector<Interval> answer;
	for (int i = 0; i < events.size(); ++i) {
		// found an interval
		if (value[0] != undefined && value[1] == undefined) {
			answer.push_back(Interval{ events[i - 1].x, events[i].x, value[0] });
		}
		int j = i - 1;
		while (j + 1 < events.size() && events[j + 1].x == events[i].x) {
			++j;
			if (events[j].add) {
				value[events[j].which] = events[j].value;
			}
			else {
				value[events[j].which] = undefined;
			}
		}
		i = j;
	}
	cout << answer.size() << " ";
	for (auto& it : answer) {
		cout << it.l << " " << it.r << " " << it.value << " ";
	}
}
