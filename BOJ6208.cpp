//BOJ6208

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define Msize 10010
#define pii pair<int,int>

struct tup {
	int x, w, f, c;

	tup() {
		x = w = f = c = 0;
	}
};

vector<tup> input;
int L, N, B;

ll cache[1010][1010];

bool comp(tup& a, tup& b) {
	if (a.x < b.x) return true;
	else return false;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> L >> N >> B;

	for (int i = 0; i < N; ++i) {
		tup tmp;
		cin >> tmp.x >> tmp.w >> tmp.f >> tmp.c;
		input.push_back(tmp);
	}

	sort(input.begin(), input.end(), comp);

	memset(cache, -1, sizeof(cache));

	for (int i = 0; i < N; ++i) {
		tup t = input[i];
		if (t.x == 0) {
			cache[t.w][t.c] = t.f;
			continue;
		}
		else {

			for (int j = 0; j <= B - t.c; ++j) {
				if (cache[t.x][j] == -1) continue;
				if (j + t.c > B) continue;
				if (t.x + t.w > L) continue;

				cache[t.x + t.w][j + t.c] = max(cache[t.x + t.w][j + t.c], cache[t.x][j] + t.f);
			}
		}

	}

	ll ans = -1;
	for (int i = 0; i <= B; ++i) {
		ans = max(ans, cache[L][i]);
	}

	printf("%lld\n", ans);

	return 0;
}