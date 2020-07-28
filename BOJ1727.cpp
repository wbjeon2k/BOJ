//BOJ1727

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

//dp(m,w): 경험치 제일 적은 남자 m, 여자 w 명으로 만들 수 있는 가장 작은 차이

#define Msize 1010

int cache[Msize][Msize], man[Msize], woman[Msize];
int M, W;

int dp(int m, int w) {
	int& ret = cache[m][w];
	if (ret != -1) return ret;

	//printf("m%d w%d\n", m, w);

	if (m == 0 || w == 0) {
		ret = 0;
		return ret;
	}

	ret = INT_MAX;
	ret = min(ret, dp(m - 1, w - 1) + abs(man[m] - woman[w]));
	if (m > w) {
		ret = min(ret, dp(m - 1, w));
	}
	else if (w > m) {
		ret = min(ret, dp(m, w - 1));
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	memset(cache, -1, sizeof(cache));


	cin >> M >> W;
	for (int i = 1; i <= M; ++i) {
		cin >> man[i];
	}
	for (int i = 1; i <= W; ++i) {
		cin >> woman[i];
	}

	sort(man + 1, man + M + 1);
	sort(woman + 1, woman + W + 1);

	int ans = dp(M, W);

	printf("%d\n", ans);

	return 0;
}

/*
//kyo20111's solution. sliding window.
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m, a[1010], b[1010], dp[1010];
stack<int> st;
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=m;i++) cin >> b[i];
	sort(a+1, a+1+n), sort(b+1, b+1+m);
	if(n > m) swap(n, m), swap(a, b);

	for(int i=1;i<=n;i++) dp[i] = 1e9;
	for(int i=1;i<=m;i++){
		for(int j=n;j>=1;j--) dp[j] = min(dp[j], dp[j-1] + abs(a[j] - b[i]));
	}
	printf("%d",dp[n]);
}
*/