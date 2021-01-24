#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define cplx complex<double>

const double PI = acos(-1);

/*
	Non recursive implementation of Cooley Tulkey FFT algorithm.
	Time Complexity: O(NlogN)
	Space Complexity: O(N)
	It has significant time difference between recursive implementation and non-recursive implementation.
	So, it is preferred to use non-recursive one in Competitive Progiramming.
*/

#define cplx complex<double>

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