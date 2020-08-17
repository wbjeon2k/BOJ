//BOJ14860

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007

bitset<15001500> plist;
vector<ll> primelist;

ll N, M;

void sieve() {
	plist.set();

	for (int i = 2; i < 15000000; ++i) {
		if (!plist[i]) continue;

		primelist.push_back(i);

		for (int j = 2 * i; j < 15000000; j += i) {
			plist[j] = false;
		}
	}
}

void sieve2() {
	plist.set();

	for (int i = 2; i <= min(N,M); ++i) {
		if (!plist[i]) continue;

		primelist.push_back(i);

		for (int j = 2 * i; j <= min(N, M); j += i) {
			plist[j] = false;
		}
	}
}

ll powMod(ll p, ll k) {
	if (k == 0) return 1;
	if (k == 1) return p;

	ll tmp = powMod(p, k / 2);

	if (k % 2) {
		return p * ((tmp * tmp) % MOD) % MOD;
	}
	else {
		return (tmp * tmp) % MOD;
	}
}

ll calck(ll p) {
	ll ret = 0, div = p;
	while (1) {
		ll tmp = (N / div) * (M / div);
		if (tmp == 0) break;
		ret += tmp;
		div *= p;
	}

	return ret;
}

int main() {
	//clock_t s, e;

	//s = clock();

	cin >> N >> M;

	sieve();

	

	if (N > M) swap(N, M);

	ll ans = 1;
	for (int i = 0; i < primelist.size(); ++i) {
		ll p = primelist[i], k;
		if (p > N) break;
		k = calck(p);
		ans *= powMod(p, k);
		ans %= MOD;
	}

	printf("%lld\n", ans);

	//e = clock();

	//printf("%lf", (double)(e - s));

	return 0;
}

/*
//ekwoo's solution.
#include <stdio.h>
typedef long long ll;
const ll M=1e9+7;
bool v[20000000];

ll lpow(ll m, ll t){
	if(t==1) return m;
	if(t==0) return 1;
	ll x=lpow(m,t/2)%M; x=(x*x)%M;
	return (x*((t%2)?m:1))%M;
}

int main(){
	ll n, m, i, j, p, t;
	scanf("%lld%lld",&n,&m);
	for(t=0, j=2; j<=n; j*=2) t+=((n/j)*(m/j));
	p=lpow(2,t)%M;
	for(j=4; j<=n; j+=2) v[j]=true;

	for(i=3; i<=n; i+=2){
		if(!v[i]){
			for(t=0, j=i; j<=n; j*=i) t+=((n/j)*(m/j));
			p=(p*lpow(i,t))%M;
			for(j=i*i; j<=n; j+=i*2) v[j]=true;
		}
	}
	printf("%lld",p%M);
}

*/