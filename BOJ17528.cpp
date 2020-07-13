//BOJ17528

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;


int A[1010], B[1010], cache[2][65000];
int T, N, W;

/*
//boj17528, 10982 같은 문제.
A[i] 를 weight, B[i]를 value로 간주.

A[i] 선택시 weight 증가, price 그대로
B[i] 선택시 weight 그대로, price 증가
cache[i][weight] : i번째 쿠키까지 A 에서 weight 시간 만큼 구웠을 떄 B에서 걸리는 최소 시간.

B에서 굽는 경우: weight 증가 X, price 증가
A에서 굽는 경우: weight 증가, price 증가 X
*/

int dp() {
	int ret = 0;
	for (int i = 1; i <= N; ++i) {
		int now, prev;
		if (i % 2 == 1) {
			now = 1, prev = 0;
		}
		else {
			now = 0, prev = 1;
		}

		ret = now;

		for (int j = 0; j <= W; ++j) {
			if (j >= A[i]) {
				cache[now][j] = min(cache[prev][j] + B[i], cache[prev][j - A[i]]);
			}
			else {
				cache[now][j] = cache[prev][j] + B[i];
			}
		}
	}

	
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N;
	W = 0;

	fill(&cache[0][0], &cache[0][0] + 2 * 65000, 65000);

	for (int i = 1; i <= N; ++i) {
		cin >> A[i] >> B[i];
		W += A[i];
	}

	cache[0][0] = 0;
	int idx = dp();
	//idx: 마지막 cache 갱신한 위치

	int ans = 1000000;
	for (int i = 0; i <= W; ++i) {
		//printf("i%d cache%d\n", i, cache[idx][i]);
		ans = min(ans, max(i, cache[idx][i]));
	}
	printf("%d\n", ans);

	return 0;
}

/*
//Green55's solution.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define xx first
#define yy second

int n, a[250], b[250], bsum, dp[250*250+1];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i){
		cin >> a[i] >> b[i];
		bsum += b[i];
	}
	for(int i=0; i<n; ++i){
		for(int j=250*250; j>=a[i]; --j)
			dp[j] = max(dp[j], dp[j-a[i]] + b[i]);
	}
	int ans = 250*250;
	for(int i=0; i<=250*250; ++i)
		ans = min(ans, max(i, bsum-dp[i]));
	cout << ans;
}

*/

/*
/*
//kazel's solution.(10928)
#include<bits/stdc++.h>
using namespace std;

int dp[100001];

int main() {
  int T;
  scanf("%d",&T);
  while(T--) {
	memset(dp, 1, sizeof(dp));
	dp[0] = 0;
	int n, r = 0;
	scanf("%d",&n);
	while(n--) {
	  int a,b;
	  scanf("%d%d",&a,&b);
	  for(int i=r;i>=0;i--) {
		if(dp[i] < dp[i+a]) {
		  dp[i+a] = dp[i];
		  if(i+a > r) r = i+a;
		}
		dp[i] += b;
	  }
	}
	int ans = 1e9;
	for(int i=r;i>=0;i--) {
	  int tmp = max(i,dp[i]);
	  if(tmp < ans) ans = tmp;
	}
	printf("%d\n",ans);
  }
}

*/
*/