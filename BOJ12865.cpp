//BOJ12865

//https://medium.com/@fabianterh/optimizing-the-knapsack-problem-dynamic-programming-solution-for-space-complexity-c6bcdff3870b
//https://www.geeksforgeeks.org/space-optimized-dp-solution-0-1-knapsack-problem/

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, W;
int cache[100100], weight[101], value[101];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> W;

	//memset(cache, 0, sizeof(cache));

	int i = 0;
	while( ++i<=N ){
		cin >> weight[i] >> value[i];
		for (int j = W; j >= 1; --j) {
			int maxWithoutCur, maxWithcur;
			maxWithoutCur = cache[j];
			maxWithcur = 0;

			if (j >= weight[i]) {
				maxWithcur += value[i];
				maxWithcur += cache[j - weight[i]];
			}

			cache[j] = max(maxWithcur, maxWithoutCur);
		}
	}

	printf("%d\n", cache[W]);

	return 0;
}

/*
//portableangel's solution.
#include <stdio.h>

int main() {
	int d[100001]={0}, n, k, w, v;
	scanf("%d %d",&n,&k);
	while(n--) {
		scanf("%d %d",&w,&v);
		for(int i=k;i>=w;i--) {
			if(d[i-w]+v>d[i]) d[i]=d[i-w]+v;
		}
	}
	printf("%d\n",d[k]);
	return 0;
}
*/


/*
//third attempt. memory complexity O(W)
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, W;
int cache[100100], weight[101], value[101];

void dp() {
	for (int i = 1; i <= N; ++i) {
		for (int j = W; j >= 1; --j) {
			int maxWithoutCur, maxWithcur;
			maxWithoutCur = cache[j];
			maxWithcur = 0;

			if (j >= weight[i]) {
				maxWithcur += value[i];
				maxWithcur += cache[j - weight[i]];
			}

			cache[j] = max(maxWithcur, maxWithoutCur);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> W;

	for (int i = 1; i <= N; ++i) {
		cin >> weight[i] >> value[i];
	}

	memset(cache, 0, sizeof(cache));

	dp();

	printf("%d\n", cache[W]);

	return 0;
}

*/

/*
//second attempt. memory complexity O(2*W)
//https://medium.com/@fabianterh/optimizing-the-knapsack-problem-dynamic-programming-solution-for-space-complexity-c6bcdff3870b
//https://www.geeksforgeeks.org/space-optimized-dp-solution-0-1-knapsack-problem/

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, W;
int cache[2][100100], weight[101], value[101];

void dp() {
	for (int i = 1; i <= N; ++i) {

		if (i % 2 == 1) {
			for (int j=0; j <= W; ++j) {
				if (j >= weight[i]) {
					cache[1][j] = max(cache[0][j], cache[0][j - weight[i]] + value[i]);
				}
				else {
					cache[1][j] = cache[0][j];
				}
			}
		}
		if (i % 2 == 0) {
			for (int j = 0; j <= W; ++j) {
				if (j >= weight[i]) {
					cache[0][j] = max(cache[1][j], cache[1][j - weight[i]] + value[i]);
				}
				else {
					cache[0][j] = cache[1][j];
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> W;

	for (int i = 1; i <= N; ++i) {
		cin >> weight[i] >> value[i];
	}

	dp();

	printf("%d\n", cache[N%2][W]);

	return 0;
}



*/

/*
//first attempt.
//memory complexity O(N*W)

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, W;
int cache[101][100100];
int weight[101], value[101];

int dp(int n, int w) {
	//n == index of item
	//w == remaining capacity\
	//남은 용량 w 일때 n번 물건 이후로 담아 얻을 수 있는 가장 큰 value
	if (n == N+1) return 0;
	int& ret = cache[n][w];

	if (ret != -1) return ret;

	ret = dp(n + 1, w);

	if (w >= weight[n]) {
		ret = max(ret, dp(n + 1, w - weight[n]) + value[n]);
	}

	//printf("n%d w%d ret%d\n", n, w, ret);

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> W;

	for (int i = 1; i <= N; ++i) {
		cin >> weight[i] >> value[i];
	}

	memset(cache, -1, sizeof(cache));
	weight[0] = 0;
	value[0] = 0;

	printf("%d\n", dp(0, W));

	return 0;
}
*/