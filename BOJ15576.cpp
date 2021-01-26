//BOJ15576

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 301000
#define cplx complex<double>
const double PI = acos(-1);

vector<ll> A, B;

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

vector<ll> ans(2 * MAXI);

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	string s, e;
	cin >> s >> e;
	A.resize(s.length());
	B.resize(e.length());

	for (int i = 0; i < s.size(); ++i) {
		int t = (int)s.size() - i - 1;
		A[i] = s[t] - '0';
	}
	for (int i = 0; i < e.size(); ++i) {
		int t = (int)e.size() - i - 1;
		B[i] = e[t] - '0';
	}

	ans = multiply(A, B);
	ans.push_back(0);
	ans.push_back(0);
	ans.push_back(0);
	ans.push_back(0);
	ans.push_back(0);

	for (int i = 0; i < ans.size(); ++i) {
		ll now = ans[i];
		ans[i] = now % 10;
		for (int j = 1; j < 10; ++j) {
			if (i + j > ans.size() - 1) continue;
			if (now > 0) now /= 10;
			ans[i + j] += (now % 10);
		}
	}

	for (int i = 0; i < ans.size() - 1; ++i) {
		if (ans[i] < 10) continue;
		ans[i + 1]++;
		ans[i] %= 10;
	}


	bool chk = false;

	string t;

	if (s[0] == '0' || e[0] == '0') printf("0");
	else {
		bool chk = false;
		for (int i = s.size() + e.size(); i >= 0; --i) {
			if (chk) t += ans[i] + '0';
			if (ans[i] == 0 && !chk) continue;
			if (ans[i] != 0 && !chk) {
				chk = true;
				t += ans[i] + '0';
			}
		}
	}

	cout << t << "\n";


	return 0;

}


/*
//recursive FFT version.
//BOJ15576

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 301000
#define cplx complex<double>
const double PI = acos(-1);

vector<ll> A, B;

void FFT(vector<cplx>& a, cplx w) {

	int n = a.size();
	if (n == 1) return;
	vector<cplx> aodd(n / 2), aeven(n / 2);

	for (int i = 0; i < n; ++i) {
		if (i % 2) aodd[i / 2] = a[i];
		else aeven[i / 2] = a[i];
	}

	FFT(aodd, w * w);
	FFT(aeven, w * w);

	cplx p(1, 0);
	for (int i = 0; i < (n / 2); ++i) {
		a[i] = aeven[i] + p * aodd[i];
		a[i + (n / 2)] = aeven[i] - p * aodd[i];
		p *= w;
	}

	return;
}

vector<ll> convolution(vector<ll>& a, vector<ll>& b) {
	vector<cplx> ca(a.begin(), a.end()), cb(b.begin(), b.end()), cc;

	int n = 1;
	while (n < a.size() || n < b.size()) n *= 2;
	n *= 2;

	ca.resize(n);
	cb.resize(n);
	cc.resize(n);

	cplx w(cos((2 * PI) / n), sin((2 * PI) / n));

	FFT(ca, w);
	FFT(cb, w);

	for (int i = 0; i < n; ++i) cc[i] = ca[i] * cb[i];

	FFT(cc, cplx(1, 0) / w);

	vector<ll> ret;
	cplx tmp(n, 0);
	for (int i = 0; i < n; ++i) {
		cc[i] /= tmp;
		ret.push_back((ll)(round(cc[i].real())));
	}

	return ret;
}

vector<ll> ans;

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	string s, e;
	cin >> s >> e;
	A.resize(s.length());
	B.resize(e.length());

	for (int i = 0; i < s.size(); ++i) {
		int t = (int)s.size() - i - 1;
		A[i] = s[t] - '0';
	}
	for (int i = 0; i < e.size(); ++i) {
		int t = (int)e.size() - i - 1;
		B[i] = e[t] - '0';
	}

	ans = convolution(A, B);
	ans.push_back(0);
	ans.push_back(0);
	ans.push_back(0);
	ans.push_back(0);
	ans.push_back(0);

	for (int i = 0; i < ans.size(); ++i) {
		ll now = ans[i];
		ans[i] = now % 10;
		for (int j = 1; j < 10; ++j) {
			if (i + j > ans.size() - 1) continue;
			if (now > 0) now /= 10;
			ans[i + j] += (now % 10);
		}
	}

	for (int i = 0; i < ans.size() - 1; ++i) {
		if (ans[i] < 10) continue;
		ans[i + 1]++;
		ans[i] %= 10;
	}


	bool chk = false;

	string t;

	if (s[0] == '0' || e[0] == '0') printf("0");
	else {
		bool chk = false;
		for (int i = s.size() + e.size(); i >= 0; --i) {
			if (chk) t += ans[i] + '0';
			if (ans[i] == 0 && !chk) continue;
			if (ans[i] != 0 && !chk) {
				chk = true;
				t += ans[i] + '0';
			}
		}
	}

	cout << t << "\n";


	return 0;

}
*/