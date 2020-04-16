
#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int bino[205][205];
int maxi = 1000000001;

void calcbino() {
    memset(bino, 0, sizeof(bino));

    for (int i = 0; i < 201; ++i) {
        bino[i][0] = 1;
        bino[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            bino[i][j] = min(maxi, bino[i - 1][j - 1] + bino[i - 1][j]);
        }
    }
}

string dp(int n, int m, int skip){
    if (n == 0) {
        return string(m, 'z');
    }
    else if (bino[n + m - 1][n - 1] > skip) {
        return "a" + dp(n - 1, m, skip);
    }
    else {
        return "z" + dp(n, m - 1, skip - bino[n + m - 1][n - 1]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    calcbino();

    if (bino[N + M][M] < K || K > 1000000000) {
        printf("-1");
    }
    else {
        string ans = dp(N, M, K-1);//kth = skip (k-1) elements
        cout << ans;
    }

    return 0;
}


/* yukariko's solution
int N,M,K;
char res[201];
int stok;
int len;
int dp[201][101];

int solve(int pos, int n)
{
	if(!n)
	{
		stok++;
		if(stok == K)
		{
			puts(res);
			exit(1);
		}
		return 1;
	}

	if(pos + n == len)
	{
		for(int i=0;i<n;i++)
			res[pos+i] = 'a';
		int ret = solve(pos,0);
		for(int i=0;i<n;i++)
			res[pos+i] = 'z';
		return ret;
	}

	int *ret=&dp[pos][n];

	if(*ret && stok + *ret < K)
	{
		stok += *ret;
		return *ret;
	}
	res[pos] = 'a';
	*ret = solve(pos+1,n-1);
	res[pos] = 'z';
	*ret += solve(pos+1,n);

	return *ret;
}

main()
{
	scanf("%d%d%d",&N,&M,&K);
	memset(res,'z',N+M);
	len = N + M;
	solve(0,N);
	puts("-1");
}

*/