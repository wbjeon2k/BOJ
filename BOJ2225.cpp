#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

long long cache[202][202];
int N, K;

long long M = 1000000000;

void calc() {
	for (int i = 0; i < 201; ++i) {
		cache[i][1] = 1;
	}

	for (int i = 0; i <= N; ++i) {
		for (int j = 2; j <= K; ++j) {
			for (int k = 0; k <= i; ++k) {
				cache[i][j] += cache[i - k][j - 1];
				cache[i][j] %= M;
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &K);
	memset(cache, 0, sizeof(cache));

	calc();
	printf("%lld", cache[N][K]);
}

/*
//gbs_kimdonggeun's solution. sliding window again.

#include<stdio.h>
int d[201];
int main()
{
	int n,k;
	scanf("%d %d",&n,&k);
	for(int i=1;i<=k;i++)
		d[i]=i;
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<=k;j++)
		{
			d[j]=(d[j]+d[j-1])%1000000000;
		}
	}
	printf("%d",d[k]%1000000000);
}


*/