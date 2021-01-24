//BOJ20176

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 101000


#define cplx complex<double>

const double PI = acos(-1);

vector<ll> A, B, C;
int asize, bsize, csize;

void fft(vector<cplx>& a, bool inv) {
	int n = a.size();
	// bit reversal
	for (int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		while (!((j ^= bit) & bit)) bit >>= 1;
		if (i < j) swap(a[i], a[j]);
	}
	for (int i = 1; i < n; i <<= 1) {
		double x = inv ? PI / i : -PI / i;
		cplx w = cplx(cos(x), sin(x));
		for (int j = 0; j < n; j += i << 1) {
			cplx p = cplx(1, 0);
			for (int k = 0; k < i; ++k) {
				cplx tmp = a[i + j + k] * p;
				a[i + j + k] = a[j + k] - tmp;
				a[j + k] += tmp;
				p *= w;
			}
		}
	}
	if (inv) {
		for (int i = 0; i < n; ++i) a[i] /= n;
	}
}

// h = fg
void multiply(vector<cplx>& f, vector<cplx>& g, vector<cplx>& h) {
	fft(f, false); fft(g, false);
	for (int i = 0; i < f.size(); ++i) h[i] = f[i] * g[i];
	fft(h, true);
}

vector<ll> multiply(vector<ll>& f, vector<ll>& g) {
	vector<cplx> pf(f.begin(), f.end()), pg(g.begin(), g.end());
	int n = 1; while (n < f.size() + g.size()) n <<= 1;
	pf.resize(n); pg.resize(n);
	fft(pf, false); fft(pg, false);
	for (int i = 0; i < n; ++i) pf[i] *= pg[i];
	fft(pf, true);
	vector<ll> ret(n);
	for (int i = 0; i < n; ++i) {
		ret[i] = (ll)round(pf[i].real());
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> asize;
	A.resize(MAXI,0);
	for (int i = 0; i < asize; ++i) {
		int t;
		cin >> t;
		++A[t + 30000];
	}

	cin >> bsize;
	B.resize(MAXI,0);
	for (int i = 0; i < bsize; ++i) {
		int t;
		cin >> t;
		++B[t + 30000];
	}

	cin >> csize;
	C.resize(MAXI,0);
	for (int i = 0; i < csize; ++i) {
		int t;
		cin >> t;
		++C[t + 30000];
	}

	vector<ll> convolution = multiply(A, C);

	int cnt = 0;
	for (int i = 0; i < B.size(); ++i) {
		if (B[i] == 0)continue;
		cnt += convolution[2 * i];
	}
	printf("%d\n", cnt);

	return 0;

}


/*
//wjdclgns12's solution. using bitset
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll gcd(ll a, ll b) { for (; b; a %= b, swap(a, b)); return a; }

int n[3];
bitset <60001> bs[3];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	for (int i = 0; i < 3; i++)
	{
		cin >> n[i];
		for (int j = 0; j < n[i]; j++)
		{
			int x; cin >> x;
			bs[i][x + 30000] = 1;
		}
	}

	ll ans = 0;
	for (int i = 0; i < 30000; i++)
	{
		auto res = bs[0] & (bs[1] << i) & (bs[2] << (i + i));
		ans += res.count();
	}

	for (int i = 1; i < 30000; i++)
	{
		auto res = bs[0] & (bs[1] >> i) & (bs[2] >> (i + i));
		ans += res.count();
	}

	cout << ans;
}
*/