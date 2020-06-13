#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, threshold;

int input[100100];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N >> threshold;

	for (int i = 0; i < N; ++i) {
		cin >> input[i];
	}

	int s = 0, e = 0, psum = 0;

	int length = 123456789;

	while (1) {
		if (psum >= threshold) {
			psum -= input[s];
			++s;
			length = min(length, e - s + 1);
		}
		else if (e == N) break;
		else if (psum < threshold) {
			psum += input[e];
			++e;
		}
	}

	if (length == 123456789) {
		printf("0");
	}
	else {
		printf("%d", length);
	}

	return 0;
}