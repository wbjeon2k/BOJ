#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int input[30];
int cache[30][30][30];
int N, K, ldoor, rdoor;

int steps(int idx, int left, int right) {
	if (idx > K) {
		return 0;
	}

	int& ret = cache[idx][left][right];

	if (cache[idx][left][right] != -1) {
		return ret;
	}

	int lsearch = abs(left - input[idx]) + steps(idx + 1, input[idx], right);
	int rsearch = abs(right - input[idx]) + steps(idx + 1, left, input[idx]);

	ret = min(lsearch, rsearch);

	return ret;
}


int main() {
	scanf("%d %d %d %d", &N, &ldoor, &rdoor, &K);

	memset(cache, -1, sizeof(cache));

	for (int i = 1; i <= K; ++i) {
		scanf("%d", &input[i]);
	}

	int ans = steps(1, ldoor, rdoor);
	printf("%d", ans);

	return 0;
}

/*
//koosaga's solution.
#include <cstdio>
#include <algorithm>
#include <cstdlib>
int n,q,a[20],dp[21][21];

int f(int xp, int yp, int pos){
	if(pos==q) return 0;
	if(dp[xp][pos]) return dp[xp][pos];
	return dp[xp][pos] = std::min(f(xp,a[pos],pos+1)+abs(yp-a[pos]),f(yp,a[pos],pos+1)+abs(xp-a[pos]));
}

int main(){
	int d1,d2;
	scanf("%d %d %d %d",&n,&d1,&d2,&q);
	for (int i=0; i<q; i++) scanf("%d",&a[i]);
	printf("%d",f(d1,d2,0));
}

*/