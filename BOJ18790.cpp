
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool cache[1010][505][505];
int N, input[1010];

int chk = 0;

void dp() {
	cache[0][0][0] = true;

	for (int i = 0; i < 2*N - 1; ++i) {
		for (int j = 0; j <= i; ++j) {
			for (int k = 0; k < N; ++k) {
				if (cache[i][j][k]) {
					cache[i + 1][j][k] = true;
					cache[i + 1][j + 1][(k + input[i + 1]) % N] = true;
				}
			}
		}
	}
}

void backtrack(int a, int b, int c) {

	int t = c - input[a];
	if (t < 0) t += N;

	if (a == 0 || b == 0) return;

	if (cache[a - 1][b - 1][t]) {
		printf("%d ", input[a]);
		backtrack(a - 1, b - 1, t);
	}
	else {
		backtrack(a - 1, b, c);
	}

	return;
}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	memset(cache, 0, sizeof(cache));

	cin >> N;
	for (int i = 1; i <= 2*N -1; ++i) {
		cin >> input[i];
	}

	dp();
	if (N == 1) {
		printf("%d", input[1]);
	}
	else {
		backtrack((2 * N) - 1, N, 0);
	}

	return 0;
}


//BOJ18790

/*
//1st attempt. back tracking failure.
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool cache[1010][505][505];
int N, input[505];


void dp() {
	cache[0][0][0] = true;

	for (int i = 0; i < 2 * N - 1; ++i) {
		for (int j = 0; j <= i; ++j) {
			for (int k = 0; k < N; ++k) {
				if (cache[i][j][k]) {
					cache[i + 1][j][k] = true;
					cache[i + 1][j + 1][(k + input[i + 1]) % N] = true;
				}
			}
		}
	}
}

int chk;

void backtrack() {

	int a, b, c;
	a = 2 * N - 1;
	b = N;
	c = 0;

	if (!cache[a][b][c]) {
		printf("-1");
		return;
	}

	if (N == 1) {
		printf("%d", input[1]);
		return;
	}

	while (a > 0 && b > 0) {
		int t = c;
		t -= input[a];
		if (t < 0) t += N;

		if (cache[a - 1][b - 1][t]) {
			printf("%d ", input[a]);
			chk += input[a];
			c = t;
			--b;
			--a;
		}
		else {
			--a;
		}

	}
	printf("\n");
	return;

}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	ifstream cin;
	cin.open("input.txt");

	memset(cache, 0, sizeof(cache));


	cin >> N;
	for (int i = 1; i <= 2 * N - 1; ++i) {
		cin >> input[i];
	}

	chk = 0;
	dp();
	backtrack();

	printf("chk : %d", chk);
	assert(chk % N == 0);

	return 0;
}
*/

