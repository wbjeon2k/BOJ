#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

string input;
string revstr;

int N;

bool ispalin(string s) {
	for (int i = 0; i < s.size()/2; ++i) {
		if (s[i] != s[s.size() - i - 1]) {
			return false;
		}
	}

	return true;
}

int main() {
	ios::sync_with_stdio(false);

	cin >> input;
	
	string t = "";
	int ans = 1000000;

	if (ispalin(input)) {
		ans= input.size();
	}
	else {
		for (int i = 0; i < input.size(); ++i) {
			t = input[i] + t;
			if (ispalin(input + t)) {
				ans = input.size() + t.size();
				break;
			}
		}
	}

	printf("%d", ans);

	return 0;
}