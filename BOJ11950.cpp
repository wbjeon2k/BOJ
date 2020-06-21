//BOJ11950 
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int psumW[55], psumB[55], psumR[55];
char input[55][55];
int N, M;

int main() {
	memset(psumW, 0, sizeof(psumW));
	memset(psumB, 0, sizeof(psumB));
	memset(psumR, 0, sizeof(psumR));

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i) {
		int wcnt, bcnt, rcnt;
		wcnt = 0; bcnt = 0; rcnt = 0;
		scanf("%s", &input[i]);
		for (int j = 0; j < M; ++j) {
			char t;
			t = input[i][j];
			if (t == 'W') {
				++wcnt;
			}
			if (t == 'R') {
				++rcnt;
			}
			if (t == 'B') {
				++bcnt;
			}
		}
		psumW[i + 1] = psumW[i] + wcnt;
		psumR[i + 1] = psumR[i] + rcnt;
		psumB[i + 1] = psumB[i] + bcnt;
	}

	int ans = INT_MAX;
	for (int i = 1; i <= N - 2; ++i) {
		for (int j = i + 1; j <= N - 1; ++j) {
			int tmp=0;
			tmp += (M * i) - (psumW[i] - psumW[0]);
			tmp += (M * (j-i)) - (psumB[j] - psumB[i]);
			tmp += (M * (N-j)) - (psumR[N] - psumR[j]);
			ans = min(ans, tmp);
		}
	}

	printf("%d", ans);

	return 0;
}