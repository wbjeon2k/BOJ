//BOJ2473
/*
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define llpii pair<ll, pii>

vector<ll> val, neg, addpos, addneg;
int N;
ll maxdiff = LLONG_MAX;
ll ans[3] = { 0,0,0 };

void find() {
	sort(val.begin(), val.end());

	for (int i = 0; i < val.size(); ++i) {
		for (int j = 0; j < val.size(); ++j) {
			if (i != j) {
				ll chk = -(val[i] + val[j]);
				auto iter = lower_bound(val.begin(), val.end(), chk);
				if (iter == val.end()) {
					--iter;
				}
				int idx = iter - val.begin();
				if (idx == i || idx == j) continue;

				if (abs(val[idx] - chk) < maxdiff) {
					maxdiff = abs(val[idx] - chk);
					ans[0] = *iter;
					ans[1] = val[i];
					ans[2] = val[j];
				}

				if (idx -1 != i && idx-1 != j) {
					if (idx > 0 && abs(val[idx - 1] - chk) < maxdiff) {
						maxdiff = abs(val[idx - 1] - chk);
						ans[0] = val[idx - 1];
						ans[1] = val[i];
						ans[2] = val[j];
					}
				}

				if (idx + 1 != i && idx + 1 != j) {
					if (idx < (val.size() - 1) && abs(val[idx + 1] - chk) < maxdiff) {
						maxdiff = abs(val[idx + 1] - chk);
						ans[0] = val[idx + 1];
						ans[1] = val[i];
						ans[2] = val[j];
					}
				}
			}
		}
	}


	return;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		ll a;
		cin >> a;
		val.push_back(a);
	}

	find();

	ll a, b, c;
	a = min({ ans[0], ans[1], ans[2] });
	c = max({ ans[0], ans[1], ans[2] });
	b = ans[0] + ans[1] + ans[2] - a - c;

	printf("%lld %lld %lld\n", a, b, c);

	return 0;

}
*/

//using two pointer method

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define llpii pair<ll, pii>

vector<ll> val;
int N;
ll maxdiff = LLONG_MAX;
ll ans[3] = { 0,0,0 };

void find() {
	for (int i = 0; i < N - 2; ++i) {
		int lo, hi;
		lo = i + 1;
		hi = N - 1;
		while (lo < hi) {
			ll a, b, diff;
			a = val[lo];
			b = val[hi];
			diff = abs(val[i] + a + b);
			if (diff < maxdiff) {
				maxdiff = diff;
				ans[0] = val[i];
				ans[1] = a;
				ans[2] = b;

				if (diff == 0) {
					return;
				}
			}

			if (val[i] + a + b > 0) {
				--hi;
			}
			else ++lo;
		}
	}
}





int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		ll a;
		cin >> a;
		val.push_back(a);
	}

	sort(val.begin(),val.end());

	find();

	printf("%lld %lld %lld\n", ans[0], ans[1], ans[2]);

	return 0;

}




/*
//topology's solution. two pointer method
#ifdef TOPOLOGY
#include "fastio.h"
#include "topology"
#else
#include <cstdio>
#include <cstring>
#endif
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <complex>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#define SZ(v) ((int) (v).size())

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;

int n;
ll a[5003];

int main(){
	scanf("%d", &n);
	for (int i=0; i<n; i++){
		scanf("%lld", &a[i]);
	}
	sort(a, a+n);
	ll m = 5e9, oa = 0, ob = 0, oc = 0;
	for (int i=0; i<n-2; i++){
		int l = i+1, r = n-1;
		while (l < r){
			if (m > abs(a[i]+a[l]+a[r])){
				m = abs(a[i]+a[l]+a[r]);
				oa = a[i], ob = a[l], oc = a[r];
				if (m == 0) goto E;
			}
			if (a[i]+a[l]+a[r] > 0) r--;
			else l++;
		}
	}
E:	printf("%lld %lld %lld\n", oa, ob, oc);
	return 0;
}
*/

/*
//1st attempt. MLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define llpii pair<ll, pii>

vector<ll> liquid;
vector<pair<ll, pii>> addsol;
vector<ll> addval;
int N;


bool comp(const llpii& a, const llpii& b) {
	if (a.first < b.first) {
		return true;
	}
	else {
		if (a.second.first > b.second.first) {
			return true;
		}
		else {
			return false;
		}
	}
}


int main() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		ll a;
		cin >> a;
		liquid.push_back(a);
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i != j) {
				ll sol = -(liquid[i] + liquid[j]);
				addsol.push_back({ sol,{i,j} });
				addval.push_back(sol);
			}
		}
	}

	sort(addsol.begin(), addsol.end());
	sort(addval.begin(), addval.end());

	ll maxdiff = LLONG_MAX;
	ll difflist[3] = { -1,-1,-1 };
	for (int i = 0; i < N; ++i) {
		ll chkval = liquid[i];
		vector<ll>::iterator lo, hi;

		lo = lower_bound(addval.begin(), addval.end(), chkval);
		hi = upper_bound(addval.begin(), addval.end(), chkval);

		if (lo == hi) {
			ll diff = (*lo - chkval);
			if (diff < maxdiff) {
				maxdiff = diff;
				int idx = lo - addval.begin();
				difflist[0] = chkval;
				difflist[1] = liquid[addsol[idx].second.first];
				difflist[2] = liquid[addsol[idx].second.second];
			}
		}

		for (auto iter = lo; iter < hi; ++iter) {
			ll diff = abs(*iter - chkval);
			int idx = iter - lo;
			if (diff < maxdiff) {
				maxdiff = diff;
				difflist[0] = chkval;
				difflist[1] = liquid[addsol[idx].second.first];
				difflist[2] = liquid[addsol[idx].second.second];
			}
		}
	}

	//printf("%lld\n", maxdiff);
	printf("%lld %lld %lld\n", difflist[0], difflist[1], difflist[2]);

	return 0;

}
*/