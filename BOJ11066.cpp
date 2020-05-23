#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

int input[505] = { 0, };
int sum[505] = { 0, };
int cache[505][505];

int N, T;
int M = INT_MAX;

int dp(int x, int y) {
	int& ret = cache[x][y];
	if (ret != -1) {
		return ret;
	}
	if (x + 1 == y) {
		ret = sum[y] - sum[x - 1];
		return ret;
	}
	if (x == y) {
		ret = 0;
		return ret;
	}

	ret = M;
	for (int i = x; i < y; ++i) {
		ret = min(ret, dp(x, i) + dp(i + 1, y) + sum[y] - sum[x - 1]);
	}

	return ret ;
}

int main() {
	scanf("%d", &T);

	for (int i = 0; i < T; ++i) {
		scanf("%d", &N);

		memset(cache, -1, sizeof(cache));
		
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &input[j]);
			sum[j] = input[j] + sum[j - 1];
		}
		
		int ans = dp(1, N);
		printf("%d\n", ans);
	}

	return 0;
}

/*

general usage of triple for loop dp

for(i = 1; i <= n; i++){
	dp[i][i] = 0;
}

for(j = 2; j <= n; j++){
	for(i = 1; i <= n-j+1; i++){
		s = i, e = i+j-1;
		dp[s][e] = vMax;

		for(k = s; k < e; k++){
			dp[s][e] = min(dp[s][e], dp[s][k] + dp[k+1][e]);
		}

		dp[s][e] += cost[s][e];
	}
}
[출처] Knuth Optimization (Dynamic Programming)|작성자 쭈노치킨
*/

/*

//cubelover's solution. Knuth optimization?

#include<cstdio>

int a[505];
int d[505][505];
short v[505][505];

int main()
{
	int tc;
	scanf("%d",&tc);
	while(tc--)
	{
		int i,j,k,n;
		scanf("%d",&n);
		for(i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			a[i]+=a[i-1];
			v[1][i]=i;
		}
		for(i=2;i<=n;i++)for(j=i;j<=n;j++)
		{
			int td=1e9,tv;
			for(k=v[i-1][j-1];k<=v[i-1][j];k++)if(d[k-j+i][k]+d[j-k][j]<td)
			{
				td=d[k-j+i][k]+d[j-k][j];
				tv=k;
			}
			d[i][j]=td+a[j]-a[j-i];
			v[i][j]=tv;
		}
		printf("%d\n",d[n][n]);
	}
}

*/