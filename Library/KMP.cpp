//KMP
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
	
	S = "avadakedabra";
	W = "aked";

	getfail(W);

	vector<int> ans = KMP(S, W);

	return 0;
}