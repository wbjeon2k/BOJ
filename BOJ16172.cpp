//BOJ16172
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define MAXI 1234567
int N, M;
string S, W;

int fail[MAXI] = { 0, };

void getfail(string Q) {
	for (int i = 1, j = 0; i < Q.length(); ++i) {
		while (j > 0 && Q[i] != Q[j]) j = fail[j - 1];
		if (Q[i] == Q[j]) {
			++j;
			fail[i] = j;
		}
	}
}

vector<int> KMP(string S, string W) {
	vector<int> ret;

	for (int i = 0, j = 0; i < S.length(); ++i) {
		while (j > 0 && S[i] != W[j]) {
			j = fail[j - 1];
		}

		if (S[i] == W[j]) {
			if (j == W.length() - 1) {
				ret.push_back(i - W.length() + 1);
				j = fail[j];
			}
			else  ++j;
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> S >> W;

	string proc;

	for (int i = 0; i < S.length(); ++i) {
		if (S[i] < 'A') continue;
		proc += S[i];
	}

	getfail(W);

	vector<int> ans = KMP(proc, W);

	if (ans.size()) printf("1\n");
	else printf("0\n");

	return 0;
}