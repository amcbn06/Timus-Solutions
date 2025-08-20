/* 1993. This cheeseburger you don't need

Strategy:

If the sentence is complex, split into sentence_1, comma and conjunction and sentence_2.

Reorder each sentence, concatenate them back and capitalize first letter.

Performance:

Linear.

* Time complexity: O(L)
* Space complexity: O(L)

*/
#include <bits/stdc++.h>
using namespace std;

string sentence;

bool isBracket(char ch) {
	return strchr("()[]{}", ch) != nullptr;
}

string reorderSentence(string sentence) {
	// Make every letter lowercase
	for (auto& ch : sentence) {
		ch = tolower(ch);
	}
	// Split into parts
	map<char, string> parts;
	for (int i = 0; i < sentence.size(); ++i) {
		if (isBracket(sentence[i])) {
			int j = i + 1;
			while (not isBracket(sentence[j])) {
				++j;
			}
			parts[sentence[i]] = string(sentence.begin() + i + 1, sentence.begin() + j);
			i = j;
		}
	}
	return parts['{'] + " " + parts['('] + " " + parts['['];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	getline(cin, sentence);
	if (sentence.find(',') == string::npos) { // Simple sentence
		sentence = reorderSentence(sentence);
	}
	else { // Complex sentence
		string first(sentence.begin(), sentence.begin() + sentence.find(','));
		int i = sentence.find(',');
		while (not isBracket(sentence[i])) {
			++i;
		}
		string middle(sentence.begin() + sentence.find(','), sentence.begin() + i);
		string second(sentence.begin() + i, sentence.end());
		sentence = reorderSentence(first) + middle + reorderSentence(second);
	}
	sentence[0] = toupper(sentence[0]);
	cout << sentence;
}