//BOJ17134

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

#define MAXI 1001000
vector<ll> plist, a(MAXI, 0), b(MAXI, 0), ans;
bitset<MAXI> chk;

void sieve() {
	chk.flip();

	for (int i = 2; i < MAXI; ++i) {
		if (!chk[i]) continue;
		if (i != 2) a[i/2] = 1;
		if (i < 500000) b[i] = 1;
		for (int j = 2 * i; j < MAXI; j += i) {
			chk[j] = false;
		}
	}

}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	sieve();

	ans = multiply(a, b);

	//ifstream cin;
	//cin.open("input.txt");

	int T, a;
	cin >> T;
	while (T--) {
		cin >> a;
		printf("%lld\n", ans[a/2]);
	}


	return 0;

}
/*
//topology's solution.
#include <bits/stdc++.h>
#ifdef TOPOLOGY
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) 42
#endif
using namespace std;

const int P = 998244353;
int g[25], ig[25];
bool sieve[1000003];
vector<int> prime;

void add(int &a, int b) {
	a += b;
	if (a >= P) a -= P;
}

void sub(int &a, int b) {
	a -= b;
	if (a < 0) a += P;
}

int mul(int a, int b) {
	return 1LL * a * b % P;
}

int pw(int a, int b) {
	if (b == 0) return 1;
	int res = pw(a, b / 2);
	if (b & 1) return mul(res, mul(res, a));
	return mul(res, res);
}

void fft(vector<int> &a, bool inv) {
	int n = (int)a.size();
	for (int i = 1, j = 0; i < n - 1; i++) {
		int b = n >> 1;
		while (!((j ^= b) & b)) b >>= 1;
		if (i < j) swap(a[i], a[j]);
	}
	for (int i = 0; (2 << i) <= n; i++) {
		int omega = inv ? g[22 - i] : ig[22 - i];
		int b = 1 << i;
		for (int j = 0; j < n; j += (b << 1)) {
			int th = 1;
			for (int k = 0; k < b; k++) {
				int tmp = mul(th, a[b + j + k]);
				a[b + j + k] = a[j + k];
				sub(a[b + j + k], tmp);
				add(a[j + k], tmp);
				th = mul(th, omega);
			}
		}
	}
	if (inv) {
		int in = pw(n, P - 2);
		for (int i = 0; i < n; i++) {
			a[i] = mul(a[i], in);
		}
	}
}

void multiply(vector<int> &a, vector<int> &b) {
	fft(a, false);
	fft(b, false);
	int n = (int)a.size();
	for (int i = 0; i < n; i++) {
		a[i] = mul(a[i], b[i]);
	}
	fft(a, true);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	g[0] = pw(3, 119);
	ig[0] = pw(g[0], P - 2);
	for (int i = 1; i <= 23; i++) {
		g[i] = mul(g[i - 1], g[i - 1]);
		ig[i] = mul(ig[i - 1], ig[i - 1]);
	}
	vector<int> a(1 << 21, 0), b(1 << 21, 0);
	for (int i = 2; i <= 1000000; i++) {
		if (sieve[i]) continue;
		if (2 * i <= 1000000) a[2 * i] = 1;
		b[i] = 1;
		for (int j = 2; i * j <= 1000000; j++) {
			sieve[i * j] = true;
		}
	}
	multiply(a, b);
	int n;
	cin >> n;
	while (n--) {
		int m;
		cin >> m;
		cout << a[m] << '\n';
	}
	return 0;
}
*/

/*
//1st trial. TLE

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define cplx complex<double>

const double PI = acos(-1);

void FFT(vector<cplx> A, cplx w) {
	if (A.size() == 1) return;

	int n = A.size();
	vector<cplx> A_odd(n/2), A_even(n/2);

	for (int i = 0; i < n; ++i) {
		if (i % 2) A_odd[i / 2] = A[i];
		else A_even[i / 2] = A[i];
	}

	FFT(A_even, w * w);
	FFT(A_odd, w * w);

	cplx p(1, 0);

	for (int i = 0; i < n / 2; ++i) {
		A[i] = A_even[i / 2] + p * A_odd[i / 2];
		A[i + (n / 2)] = A_even[i / 2] - p * A_odd[i / 2];
		p *= w;
	}

	return;

}

vector<int> convolution(vector<int>& a, vector<int>& b) {
	int n = 1;
	while (n < a.size() || n < b.size()) n *= 2;
	n *= 2;

	vector<cplx> A(a.begin(), a.end()), B(b.begin(), b.end());
	A.resize(n);
	B.resize(n);

	cplx w(cos((2 * PI) / n), sin((2 * PI) / n));

	FFT(A, w);
	FFT(B, w);

	vector<cplx> C(n);

	for (int i = 0; i < n; ++i) C[i] = A[i] * B[i];

	FFT(C, cplx(1, 0) / w);

	vector<int> ret(n);

	for (int i = 0; i < n; ++i) {
		C[i] /= cplx(n, 0);
		ret[i] = int(round(C[i].real()));
	}

	return ret;
}

#define MAXI 1001000
vector<int> plist, a(MAXI, 0), b(MAXI, 0);
bool chk[MAXI];

void sieve() {
	memset(chk, 1, sizeof(chk));

	for (int i = 2; i * i < MAXI; ++i) {
		if (!chk[i]) continue;
		for (int j = 2 * i; j < MAXI; j += i) {
			chk[j] = false;
		}
	}

	for (int i = 2; i < MAXI; ++i) {
		if (chk[i]) plist.push_back(i);
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	sieve();

	for (int i = 0; i < plist.size(); ++i) {
		a[plist[i]] = 1;
		if(plist[i]*2 < MAXI) b[plist[i] * 2] = 1;
	}

	vector<int> ans = convolution(a, b);

	int T, a;
	cin >> T;
	while (T--) {
		cin >> a;
		printf("%d\n", ans[a]);
	}


	return 0;

}
*/