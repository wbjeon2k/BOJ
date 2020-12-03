#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>

/*debug
	ifstream cin;
	cin.open("input.txt");
*/

int N, K;

ll input[500300], cache[500500];

#define MOD 1000000007

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N - 1; ++i) {
		cin >> input[i];
	}

	memset(cache, 0, sizeof(cache));
	ll ans = 0;
	cache[0] = input[0];
	ans = cache[0];
	for (int i = 1; i < N - 1; ++i) {
		cache[i] = cache[i - 1] * input[i] + input[i];
		cache[i] %= MOD;
		ans += cache[i];
		ans %= MOD;
	}
	
	printf("%lld\n", ans);

	return 0;
}