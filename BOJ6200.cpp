//BOJ 6200

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll S, E;
ll combination[40][40];

void getcombination() {
	combination[0][0] = 1;
	combination[1][0] = 1;
	combination[1][1] = 1;

	for (int i = 2; i < 35; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j == 0 || j == i) {
				combination[i][j] = 1;
				continue;
			}

			combination[i][j] = combination[i - 1][j - 1] + combination[i - 1][j];
		}
	}
}

struct bitlist {
	bool barr[35];
	ll num;

	bitlist() {
		memset(barr, 0, sizeof(barr));
		num = 0;
	}
};

bitlist numproc(ll n) {
	bitlist ret;

	ret.num = n;
	for (int i = 0; i < 35; ++i) {
		ret.barr[i] = n % 2;
		n /= 2;
	}

	return ret;
}

ll roundnum(bitlist n) {

	ll ret = 0;
	ll spoint = 0;
	for (ll i = 0; i <= 31; ++i) {
		ll tmp = ((ll)1 << (i));
		spoint = i;
		if (n.num >= tmp) {
			for (ll j = 0; (j + 1) <= i / 2; ++j) {
				ret += combination[i-1][j];
			}
		}
		else break;
	}

	--spoint;

	for (ll i = spoint - 1; i >= 0; --i) {
		if (!n.barr[i]) continue;

		ll cntone =0, cntzero=0;

		for (int j = spoint; j >= i; --j) {
			if (n.barr[j]) ++cntone;
			else ++cntzero;
		}

		--cntone; ++cntzero;

		for (ll j = 0; 2*(j + cntone) <= (spoint+1) ; ++j) {
			ret += combination[i][j];
		}
	}

	ll cntone = 0, cntzero = 0;
	for (ll i = spoint; i >= 0; --i) {
		if (n.barr[i]) ++cntone;
		else ++cntzero;
	}

	if (cntone <= cntzero) ++ret;

	return ret;
}

/*
//ver 1
ll roundnum(bitlist n) {
	ll ret = 0;
	int spoint = 0;

	for (int i = 31; i >= 0; --i) {
		if (n.barr[i]) {
			spoint = i;
			break;
		}
	}

	for (int i = spoint; i > 0; --i) {
		if (!n.barr[i]) continue;

		ll tcnt = 0;

		int zcnt = 0, ocnt = 0;

		for (int j = spoint; j >= i; --j) {
			if (n.barr[j]) ++ocnt;
			else ++zcnt;
		}

		for (int j = 0; j <= (i+1)/2; ++j) {
			if ((ocnt + j) * 2 > i + 1) continue;
			tcnt += combination[i][j];
		}

		ret += tcnt;
	}

	int zcnt = 0, ocnt = 0;
	for (int i = spoint; i >= 0; --i) {
		if (n.barr[i]) ++ocnt;
		else ++zcnt;
	}
	if (zcnt >= ocnt) ++ret;

	return ret;
}*/

int main() {
	cin >> S >> E;

	if (S > 1) --S;

	getcombination();

	bitlist s, e;
	s = numproc(S);
	e = numproc(E);

	printf("%lld\n", roundnum(e) - roundnum(s));


	return 0;
}