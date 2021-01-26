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

	vector<int> ret;

	for (int i = 0; i < n; ++i) {
		C[i] /= cplx(n, 0);
		ret[i] = int(round(C[i].real));
	}

	return ret;
}