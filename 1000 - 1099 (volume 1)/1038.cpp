/* 1038. Spell Checker

Strategy:
We use regex to split the lines into sentences,
and to further split the sentences into words;

Observations:
* This problem has a very vague description:
* what happens at the end of a line?
-> new word starts, '\n' works just as another character
* what happens if the last sentence doesn't have an ending symbol?
-> it still counts as a sentence

* Time complexity: O(n)
* Space complexity: O(n)

*/
#include <bits/stdc++.h>
using namespace std;

vector<string> splitIntoWords(string sentence) {
	regex word("[a-zA-Z]+");
	auto bgn = sregex_iterator(sentence.begin(), sentence.end(), word);
	vector<string> words;
	for (auto it = bgn; it != sregex_iterator(); ++it) {
		smatch match = *it;
		words.push_back(match.str());
	}
	return words;
}

int countMistakes(string text) {
	regex sentence("[^.\?!]+[.\?!]+");
	auto bgn = sregex_iterator(text.begin(), text.end(), sentence);
	int mistakes = 0;
	for (auto it = bgn; it != sregex_iterator(); ++it) {
		smatch match = *it;
		vector<string> words = splitIntoWords(match.str());
		if (words.empty()) {
			continue;
		}
		if (islower(words.front()[0])) {
			++mistakes;
		}
		for (auto& word : words) {
			for (int i = 1; i < word.size(); ++i) {
				if (isupper(word[i])) {
					++mistakes;
				}
			}
		}
	}
	return mistakes;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	string text, line;
	while (getline(cin, line)) {
		text += line + '\n';
	}
	text += '.'; // end the last sentence in case it doesn't have an ending character
	cout << countMistakes(text) << "\n";
}
