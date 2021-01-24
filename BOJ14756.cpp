//BOJ14756

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 50100

/*https://koosaga.com/189 */

ll n, m, l, W;
ll sky[101][10010], telescope[101][3030], invert[101][3030];
vector<vector<ll>> vinvert(101);

#define cplx complex<double>

const double PI = acos(-1);

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

vector<vector<ll>> convolution;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> l >> m >> W;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> sky[i][j];
		}
	}

	for (int i = 0; i < m; ++i) {
		vinvert[i].resize(l);
		for (int j = 0; j < l; ++j) {
			cin >> telescope[i][j];
			vinvert[i][l - j - 1] = telescope[i][j];
		}
	}

	convolution.resize(m);
	for (int i = 0; i < m; ++i) {
		vector<ll> trow;
		for (int j = 0; j < n; ++j) trow.push_back(sky[i][j]);
		convolution[i] = multiply(trow, vinvert[i]);
	}
	
	int cnt = 0;

	/*
	1<=p<=n-l+1 일때
	한 row 의 intensity: sum(A[i]*B[i-p + 1]);
	B 배열 좌우 반전: sum(A[i]*B[l+p-i]);
	C[i] = sum(A[j], B[i-j])-> intensity: C[l+p] = sum(A[j], B[l+p-j]);

	0<=p<=n-l 인 본 코드에서는
	convolution[j][l+i-1] == intensity.

	*/

	for (int i = 0; i <= n - l; ++i) {
		ll sum = 0;
		for (int j = 0; j < m; ++j) {
			sum += convolution[j][l + i - 1];
		}
		if (sum > W) ++cnt;
	}

	printf("%d\n", cnt);
	return 0;

}
