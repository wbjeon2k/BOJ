// BOJ 1797

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll,ll>

vector<pll> input;
int N;

struct tup {
	ll val, pos, idx;
};

vector<tup> psumdiff;

bool inputcomp(pll& a, pll& b) {
	if (a.second < b.second) return true;
	else return false;
}

bool psumcomp(tup& a, tup& b) {
	if (a.val < b.val) return true;

	if (a.val == b.val && a.pos < b.pos) return true;

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		pll tmp;
		cin >> tmp.first >> tmp.second;
		input.push_back(tmp);
	}

	if (N == 2) {
		if (input[0].first != input[1].first) {
			printf("%lld\n", abs(input[0].second - input[1].second));
		}
		return 0;
	}

	sort(input.begin(), input.end(), inputcomp);

	int mcnt, wcnt;

	mcnt = 0, wcnt = 0;
	psumdiff.push_back({ 0,0 });
	for (int i = 0; i < N; ++i) {
		if (input[i].first == 1) ++wcnt;
		else ++mcnt;

		psumdiff.push_back({ mcnt - wcnt, input[i].second, i});
	}

	psumdiff.push_back({ INT_MAX, 0 });

	sort(psumdiff.begin(), psumdiff.end(), psumcomp);

	ll start = psumdiff[0].val, spoint = 0, gap = 0;
	for (int i = 0; i < psumdiff.size(); ++i) {
		if (start == psumdiff[i].val) continue;

		if (i - 1 == spoint) {
			start = psumdiff[i].val;
			spoint = i;
			continue;
		}

		int inputidx = psumdiff[spoint].idx + 1;

		ll tgap = psumdiff[i - 1].pos - input[inputidx].second;
		if (tgap > gap) gap = tgap;

		start = psumdiff[i].val;
		spoint = i;
	}

	printf("%lld\n", gap);

	return 0;

}