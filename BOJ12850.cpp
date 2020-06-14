//BOJ12850
//알고리즘 트레이닝 p550

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll adjMat[9][9] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 1, 1, 0, 0, 0, 0 },
	{ 0, 1, 1, 0, 1, 1, 0, 0, 0 },
	{ 0, 0, 1, 1, 0, 1, 1, 0, 0 },
	{ 0, 0, 0, 1, 1, 0, 1, 0, 1 },
	{ 0, 0, 0, 0, 1, 1, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 1 },
	{ 0, 0, 0, 0, 0, 1, 0, 1, 0 }
};

#define M 1000000007

struct Mat {
	ll mat[9][9];

	Mat() {
		memset(mat, 0, sizeof(mat));
	}

	Mat(ll a[][9]) {
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				mat[i][j] = a[i][j];
			}
		}
	}
};

Mat matMult(Mat a, Mat b) {
	Mat ans;
	int i, j, k;
	for (i = 0; i < 9; ++i) {
		for (j = 0; j < 9; ++j) {
			for (ans.mat[i][j] = k = 0; k < 9; ++k) {
				ans.mat[i][j] += (a.mat[i][k] * b.mat[k][j]) % M;
			}
			ans.mat[i][j] %= M;
		}
	}

	return ans;
}

Mat matPow(Mat base, int p) {
	Mat ans;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			ans.mat[i][j] = (i == j);
		}
	}

	while (p) {
		if (p & 1) ans = matMult(ans, base);
		base = matMult(base, base);
		p >>= 1;
	}

	return ans;
}


int N;
int main() {
	cin >> N;

	Mat adj(adjMat);
	Mat ans = matPow(adj, N);

	printf("%lld", ans.mat[1][1]);
	return 0;
}