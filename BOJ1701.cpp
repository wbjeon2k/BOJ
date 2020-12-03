//BOJ1701

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define MAXI 12345

string N, Q;

int fail[MAXI] = { 0, };

void getfail(string Q) {
	memset(fail, 0, sizeof(fail));

	for (int i = 1, j = 0; i < Q.length(); ++i) {
		while (j > 0 && Q[i] != Q[j]) j = fail[j - 1];
		if (Q[i] == Q[j]) {
			++j;
			fail[i] = j;
		}
	}
}

vector<int> KMP(string S, string W) {
	getfail(W);
	vector<int> ret;

	for (int i = 0, j = 0; i < S.length(); ++i) {
		while (j > 0 && S[i] != W[j]) j = fail[j - 1];

		if (S[i] == W[j]) {
			if (j == W.length() - 1) {
				ret.push_back(i - W.length() + 1);
				j = fail[j];
			}
			else ++j;
		}
	}

	return ret;
}



int binsearch(int lo, int hi) {
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		vector<int> ret;
		bool chk = false;
		string tmp = "";

		for (int i = 0; i < mid; ++i) {
			tmp += N[i];
		}
		for (int i = mid; i < N.length(); ++i) {
			ret = KMP(N, tmp);
			if (ret.size() >= 2) chk = true;

			tmp.erase(tmp.begin());
			tmp += N[i];
		}
			


		if (chk) lo = mid + 1;
		else hi = mid;
	}

	return lo;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	string tmp = N;

	int ans = -1;
	for (int i = 0; i < N.length(); ++i) {
		getfail(tmp);
		for (int j = 0; j < tmp.length(); ++j) {
			ans = max(ans, fail[j]);
		}
		tmp.erase(tmp.begin());
	}

	printf("%d\n", ans);
	return 0;
}

//ntopia's solution. using suffix array

/*
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

template<typename Ty>
struct SuffixArray {
	vector<Ty> in;
	vector<int> out;
	template<typename Pt>
	SuffixArray(Pt begin, Pt end) : in(begin, end) {}

	vector<int> build() {
		int n = (int)in.size(), c = 0;
		vector<int> temp(n), pos2bckt(n), bckt(n), bpos(n);
		out.resize(n);
		for (int i = 0; i < n; i++) out[i] = i;
		sort(out.begin(), out.end(), [&](int a, int b) { return in[a] < in[b]; });
		for (int i = 0; i < n; i++) { bckt[i] = c; if (i + 1 == n || in[out[i]] != in[out[i + 1]]) c++; }
		for (int h = 1; h < n && c < n; h <<= 1) {
			for (int i = 0; i < n; i++) pos2bckt[out[i]] = bckt[i];
			for (int i = n - 1; i >= 0; i--) bpos[bckt[i]] = i;
			for (int i = 0; i < n; i++) if (out[i] >= n - h) temp[bpos[bckt[i]]++] = out[i];
			for (int i = 0; i < n; i++) if (out[i] >= h) temp[bpos[pos2bckt[out[i] - h]]++] = out[i] - h;
			c = 0;
			for (int i = 0; i + 1 < n; i++) {
				int a = (bckt[i] != bckt[i + 1]) || (temp[i] >= n - h) || pos2bckt[temp[i + 1] + h] != pos2bckt[temp[i] + h];
				bckt[i] = c;
				c += a;
			}
			bckt[n - 1] = c++;
			temp.swap(out);
		}
		return out;
	}

	vector<int> lcparray() {
		if (in.size() != out.size()) build();
		int n = (int)in.size();
		vector<int> rank(n); // temporary
		vector<int> height(n - 1); // output lcp array

		for (int i = 0; i < n; i++) rank[out[i]] = i;
		int h = 0;
		for (int i = 0; i < n; i++) {
			if (rank[i] == 0) continue;
			int j = out[rank[i] - 1];
			while (i + h < n && j + h < n && in[i + h] == in[j + h]) h++;
			height[rank[i] - 1] = h;
			if (h > 0) h--;
		}
		return height;
	}
};

char str[5003];

void proc() {
	scanf("%s", str);
	int len = strlen(str);

	SuffixArray<char> sa(str, str + len);
	vector<int> lcp(sa.lcparray());
	printf("%d", *max_element(lcp.begin(), lcp.end()));
}

int main() {
	//freopen("input.txt", "r", stdin);
	proc();
	return 0;
}
*/