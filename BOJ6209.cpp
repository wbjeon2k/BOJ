//BOJ6209

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int reject(vector<int>& vec, int gap) {

	int lastpick = 0, cnt = 0;
	for (int i = 1; i < vec.size() - 1; ++i) {
		
		if (vec[i] - vec[lastpick] >= gap) {
			lastpick = i;
			continue;
		}
		
		++cnt;
	}

	return cnt;
}

int N, D, M, cnt;
vector<int> input;
bool chk[50500];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> D >> N >> M;

	for (int i = 0; i < N; ++i) {
		int t;
		cin >> t;
		input.push_back(t);
	}

	input.push_back(0);
	input.push_back(D);

	sort(input.begin(), input.end());

	int lo = 0, hi = D, ans=0;

	if (input.size() == 2) {
		printf("%d\n", D);
		return 0;
	}

	while (1) {
		int mid, midreject;

		mid = (lo + hi) / 2;
		midreject = reject(input, mid);
		if (midreject <= M) {
			lo = mid + 1;
		}
		else if (midreject > M) {
			hi = mid;
		}

		if (lo == hi) break;
	}

	printf("%d\n", hi - 1);

	return 0;
}