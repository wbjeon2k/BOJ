//BOJ13323
//https://www.acmicpc.net/problem/13323
//https://jwvg0425-ps.tistory.com/98


#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pid pair<int,double>
#define pll pair<ll,ll>

#define MAXI 1001000

int N, offset;
ll input[MAXI];
ll ans;

priority_queue<ll> pq;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; ++i) cin >> input[i];

	offset = 0;
	ans = 0;

	pq.push(input[0]);

	for (int i = 1; i < N; ++i) {
		++offset;

		ll lastpoint = pq.top() + offset;

		if (input[i] <= lastpoint) {
			pq.pop();
			ans += lastpoint - input[i];
			pq.push(input[i] - offset);
		}

		pq.push(input[i] - offset);
	}

	printf("%lld\n", ans);
	return 0;

}

/*
//rkm0959's solution/
#include <bits/stdc++.h>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long double ldb;
typedef long long int ll;
typedef complex<double> base;

priority_queue<ll> PQ;
ll a[1111111], ans[1111111], tot, n;

int main(void)
{
	fio; ll n, i; cin>>n;
	for(i=1 ; i<=n ; i++) cin>>a[i];
	for(i=1 ; i<=n ; i++) a[i]-=i;
	for(i=1 ; i<=n ; i++)
	{
		if(!PQ.empty() && PQ.top()<a[i]) ans[i]=a[i], PQ.push(a[i]);
		else { PQ.push(a[i]); PQ.push(a[i]); PQ.pop(); ans[i]=PQ.top(); }
	}
	for(i=n-1 ; i>=1 ; i--) ans[i]=min(ans[i], ans[i+1]);
	for(i=1 ; i<=n ; i++) tot+=abs(ans[i]-a[i]);
	cout<<tot; return 0;
}

*/