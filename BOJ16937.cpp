#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, T, G;

int steps[100100];

#define pis pair<int,string>

int buttonB(int n) {
	n *= 2;
	if (n >= 100000) return -1;
	if (n >= 10000) return n - 10000;
	if (n >= 1000) return n - 1000;
	if (n >= 100) return n - 100;
	if (n >= 10) return n - 10;
	if (n >= 1) return n - 1;
	if (n == 0) return 0;
}

void bfs(int n) {
	queue<int> q;
	q.push(n);
	steps[n] = 0;

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		int N = here;

		if (N < 99999) {
			if (steps[N + 1] > steps[N] + 1) {
				steps[N + 1] = steps[N] + 1;
				q.push(N+1);
			}
		}
		if (N < 50000) {
			int b = buttonB(N);
			if (steps[b] > steps[N] + 1) {
				steps[b] = steps[N] + 1;
				q.push(b);
			}
		}
	}
}

int main() {
	cin >> N >> T >> G;
	fill(steps, steps + 100100, 11111111);
	bfs(N);
	if (steps[G] > T) {
		printf("ANG");
	}
	else {
		printf("%d", steps[G]);
	}
	return 0;
}