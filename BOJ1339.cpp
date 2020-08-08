// BOJ 1339

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define ll long long

int N;
vector<string> slist;
ll cnt[8][30], numberlist[30];
//i 번쨰 자리 j 번째 알파벳 개수

string agenerator(int n) {
	string ret = "";
	for (int i = 0; i < n; ++i) {
		ret += "a";
	}
	return ret;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		string s, t;
		cin >> s;
		t = agenerator(8 - s.size());
		slist.push_back(t + s);
	}

	sort(slist.begin(), slist.end());

	memset(cnt, 0, sizeof(cnt));
	memset(numberlist, 0, sizeof(numberlist));

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < N; ++j) {
			if (slist[j][i] == 'a') continue;
			++cnt[i][slist[j][i] - 'A'];
		}
	}

	vector<pii> anslist;
	for (int i = 0; i < 26; ++i) {
		ll tmp = 0;
		ll pow10 = 1;
		for (int j = 7; j >= 0; --j) {
			tmp += (cnt[j][i])*pow10;
			pow10 *= 10;
		}
		if (tmp == 0) continue;
		anslist.push_back({ tmp,i });
	}

	sort(anslist.begin(), anslist.end());

	int idx = 9;
	for (int i = anslist.size() - 1; i >= 0; --i) {
		numberlist[anslist[i].second] = idx;
		--idx;
	}

	long long ans = 0;
	long long pow10 = 1;
	for (int i = 7; i >= 0; --i) {
		for (int j = 0; j < N; ++j) {
			if (slist[j][i] == 'a') continue;
			ans += numberlist[slist[j][i] - 'A']*pow10;
		}
		pow10 *= 10;
	}

	printf("%lld\n", ans);

	return 0;
}