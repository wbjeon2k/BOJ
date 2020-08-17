//BOJ11402

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define Msize 2020

ll binomial[Msize][Msize];

ll N, K, M;

void binomialCount() {
	memset(binomial, 0, sizeof(binomial));
	binomial[0][0] = 1;
	binomial[1][0] = 1;
	binomial[1][1] = 1;

	for (int i = 2; i <= 2000; ++i) {
		binomial[i][0] = 1;
		binomial[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			binomial[i][j] = (binomial[i - 1][j] + binomial[i - 1][j - 1]) % M;
		}
	}

	return;
}

int main() {
	cin >> N >> K >> M;

	binomialCount();

	ll ans = 1;
	while (N > 0) {
		ll nmod, kmod;
		nmod = N % M;
		kmod = K % M;
		ans *= binomial[nmod][kmod];
		ans %= M;
		
		N -= nmod;
		K -= kmod;
		N /= M;
		K /= M;
	}
	
	printf("%lld\n", ans);

	return 0;
}

/*
//Nada's solution.
#include <cstdio>

typedef long long LL;

LL Pow( LL a, LL b, LL c ){
	if( b == 0 ) return 1%c;
	else if( b == 1 ) return a%c;
	else{
		long long A = Pow( a, b/2, c );
		A = (A*A)%c;
		if( b & 1 ) A = (A*a)%c;
		return A;
	}
}

const int N = 2005;
long long f[N];

LL comb( LL n, LL r, LL c ){
	if( n < r ) return 0;
	return (((f[n]*Pow( f[n-r], c-2, c ))%c)*Pow( f[r], c-2, c))%c;
}

LL lucas( LL n, LL r, LL m ){
	if( n >= m ) return (lucas( n/m, r/m, m ) * comb( n%m, r%m, m )) % m;
	else return comb( n%m, r%m, m );
}

int main(){

	long long n, r, m;
	scanf("%lld %lld %lld", &n, &r, &m);

	f[0] = 1;
	for(int i=1; i<=m; i++)
		f[i] = (f[i-1] * i) % m;

	printf("%lld\n", lucas( n, r, m));

}
*/