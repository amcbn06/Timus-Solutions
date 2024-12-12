/* 1015. Test the Difference!

Strategy:
For each dice we can find its lexicographically smallest orientation by bruteforce;
To make this approach faster, we can take a normal dice, bruteforce by repeteadly rotating
it on the X, Y and Z axis, find all the different orientions and use them for the actual dices.

=> we find 24 possible reorderings, we reorder our dice's values according to those reorderings 
and we pick the lexicographically smallest one as it's category

Performance:
- We can ignore the inital bruteforce because it's not that expensive to compute
- For each die we go through 24 permutations and we find the smallest one => O(24 * 6 * N)
- Then remains just the map, which runs in O(NlogN)

* Time complexity: O(144 * N + NlogN)
* Space complexity: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

/*
  0
1 2 3
  4
  5

0 - front, 1 - left, 2 - bottom, 3 - right, 4 - back, 5 - top

Let 0 be the front facing side and 2 be the bottom side
When we rotate around the X axis, we shift 0,5,4,2
When we rotate around the Y axis, we shift 0,3,4,1
When we rotate around the Z axis, we shift 5,3,2,1

*/

struct Dice {
	array<int, 6> faces;
	void rotate(int axis) {
		vector<int> from;
		if (axis == 0) {
			from = { 0, 5, 4, 2 };
		}
		else if (axis == 1) {
			from = { 0, 3, 4, 1 };
		}
		else {
			from = { 5, 3, 2, 1 };
		}
		vector<int> aux(4);
		for (int i = 0; i < 4; ++i) {
			aux[i] = faces[from[i]];
		}
		aux.insert(aux.begin(), aux.back());
		aux.pop_back();
		for (int i = 0; i < 4; ++i) {
			faces[from[i]] = aux[i];
		}
	}
};

set<array<int, 6>> orientations;

void backtrack(Dice cur) {
	orientations.insert(cur.faces);
	for (int k = 0; k < 3; ++k) {
		Dice nxt = cur;
		nxt.rotate(k);
		if (!orientations.count(nxt.faces)) {
			backtrack(nxt);
		}
	}
}

void bruteforceOrientations() {
	Dice foo;
	foo.faces = { 0, 1, 2, 3, 4, 5 };
	backtrack(foo);
}

const int nmax = 1e5;
int n;
array<int, 6> dices[nmax + 5];

array<int, 6> lexicographicallySmallest(array<int, 6> dice) {
	array<int, 6> best = dice;
	for (auto& orientation : orientations) {
		array<int, 6> cur;
		for (int i = 0; i < 6; ++i) {
			cur[i] = dice[orientation[i]];
		}
		if (lexicographical_compare(cur.begin(), cur.end(), best.begin(), best.end())) {
			best = cur;
		}
	}
	return best;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	bruteforceOrientations();
	cin >> n;
	map<array<int, 6>, vector<int>> categories;
	for (int i = 1; i <= n; ++i) {
		// the number of points on the left side of the die,
		cin >> dices[i][1];
		// then on the right side,
		cin >> dices[i][3];
		// on the top,
		cin >> dices[i][5];
		// on the forward side,
		cin >> dices[i][0];
		// on the bottom
		cin >> dices[i][2];
		// and on the backward side
		cin >> dices[i][4];
		categories[lexicographicallySmallest(dices[i])].push_back(i);
	}
	vector<vector<int>> groups;
	for (auto& it : categories) {
		groups.push_back(it.second);
	}
	sort(groups.begin(), groups.end());
	cout << groups.size() << "\n";
	for (auto& it : groups) {
		for (auto& i : it) {
			cout << i << " ";
		}
		cout << "\n";
	}
}
