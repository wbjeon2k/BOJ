//BOJ1234
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll cache[11][101][101][101];
ll binomial[101][101];

void dpbinomial() {
	
	binomial[0][0] = 1;
	binomial[1][0] = 1;
	binomial[1][1] = 1;

	for (int i = 2; i <= 11; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j == 0 || j == i) {
				binomial[i][j] = 1;
			}
			else {
				binomial[i][j] = binomial[i - 1][j - 1] + binomial[i - 1][j];
			}
		}
	}

}

ll dp(int n, int r, int g, int b) {
	if (r < 0 || g < 0 || b < 0) return 0;

	ll& ret = cache[n][r][g][b];

	if (ret != -1) return ret;

	if (n == 1) {
		int tmp = (r > 0) + (g > 0) + (b > 0);
		return ret = (ll)tmp;
	}

	ret = 0;

	if (n % 2 == 0) {
		int t = n / 2;
		ret += dp(n - 1, r - t, g - t, b) * (binomial[n][t]);
		ret += dp(n - 1, r - t, g, b-t) * (binomial[n][t]);
		ret += dp(n - 1, r, g - t, b-t) * (binomial[n][t]);
	}

	if (n % 3 == 0) {
		int t = n / 3;
		ret += dp(n - 1, r-t, g - t, b - t) * (binomial[n][t]) * (binomial[n-t][t]);
	}

	ret += dp(n - 1, r - n, g, b);
	ret += dp(n - 1, r, g-n, b);
	ret += dp(n - 1, r, g, b-n);

	return ret;
}

int N, R, G, B;

int main() {
	cin >> N >> R >> G >> B;

	memset(cache, -1, sizeof(cache));
	dpbinomial();

	printf("%lld", dp(N, R, G, B));
	return 0;
}

/*
//pichulia's solution.
// r,g 둘을 알면 한 줄에 놓을 수 있는 n은 정해져 있기 때문에 무조건 b 알 수 있다.
// (r+g+b)!/r!g!b!
#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
int n;
int a[3];
long long int d[10][56][56];
long long int f[11];
long long int dp(int dep, int p, int q, int r) {
	if (p > a[0] || q > a[1] || r > a[2])return 0;
	if (dep > n) {
		return 1;
	}
	if (d[dep - 1][q][r] >= 0) return d[dep - 1][q][r];
	long long int& ret = d[dep - 1][q][r];
	ret = 0;
	long long int scale;
	//use only p, q, r
	scale = 1;
	ret += dp(dep + 1, p + dep, q, r);
	ret += dp(dep + 1, p, q + dep, r);
	ret += dp(dep + 1, p, q, r + dep);

	//use two
	if (dep % 2 == 0) {
		scale = f[dep] / f[dep / 2] / f[dep / 2];
		ret += dp(dep + 1, p + dep / 2, q + dep / 2, r) * scale;
		ret += dp(dep + 1, p, q + dep / 2, r + dep / 2) * scale;
		ret += dp(dep + 1, p + dep / 2, q, r + dep / 2) * scale;
	}

	//use all
	if (dep % 3 == 0) {
		scale = f[dep] / f[dep / 3] / f[dep / 3] / f[dep / 3];
		ret += dp(dep + 1, p + dep / 3, q + dep / 3, r + dep / 3) * scale;
	}

	return ret;
}
void inil() {
	int i, j;
	f[0] = 1;
	for (i = 1; i <= 10; i++) {
		f[i] = f[i - 1] * i;
	}
}
int main() {
	inil();
	int i, j, k;
	scanf("%d", &n);
	for (i = 0; i < 3; i++) {
		scanf("%d", &a[i]);
		if (a[i] > 55)a[i] = 55;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j <= a[1]; j++) {
			for (k = 0; k <= a[2]; k++) {
				d[i][j][k] = -1;
			}
		}
	}
	long long int res = dp(1, 0, 0, 0);
	printf("%lld\n", res);
}
*/