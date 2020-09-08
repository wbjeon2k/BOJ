//BOJ1856

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int W, L;
string S;
vector<string> wordlist(666);

int cache[333];

int makeword(int pos, string word) {
	int chk = 0, ret = -1;
	for (int i = pos; i <= S.size(); ++i) {
		if (S[i-1] == word[chk]) ++chk;
		if (chk == word.size()) {
			ret = i;
			break;
		}
	}

	return ret;
}

int dp(int here) {
	//printf("here %d\n", here);

	if (here > L) return 0;
	if (here == L) return 1;

	int& ret = cache[here];
	if (cache[here] != 1234) return ret;

	for (int i = 1; i <= W; ++i) {
		string w = wordlist[i];
		if (w[0] != S[here - 1]) continue;

		int p = makeword(here, w);
		if (p == -1) continue;

		int tmp = dp(p + 1) + (p - here - w.size() + 1);
		ret = min(ret, tmp);
	}

	ret = min(ret, dp(here + 1) + 1);

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> W >> L;

	cin >> S;

	for (int i = 1; i <= W; ++i) {
		cin >> wordlist[i];
	}

	for (int i = 0; i < 333; ++i) {
		cache[i] = 1234;
	}

	printf("%d\n", dp(1));

	//printf("%d\n", makeword(6, "brown"));


	return 0;
}