//BOJ1572

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 65536
#define ll long long

int N, K;
int input[250250];
vector<int> seed;
multiset<int> lo, hi;
ll ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;
	for (int i = 0; i < K; ++i) {
		cin >> input[i];
		lo.emplace(input[i]);
	}

	while (lo.size() >= hi.size()) {
		hi.emplace(*lo.rbegin());
		lo.erase(lo.find(*lo.rbegin()));
	}

	ans = *hi.begin();

	for (int i = K; i < N; ++i) {
		cin >> input[i];

		auto r = lo.find(input[i - K]);
		if (r != lo.end()) {
			lo.erase(r);
		}
		else hi.erase(hi.find(input[i - K]));

		lo.emplace(input[i]);

		while (lo.size() < hi.size()) {
			lo.emplace(*hi.begin());
			hi.erase(hi.begin());
		}

		while (lo.size() >= hi.size()) {
			hi.emplace(*lo.rbegin());
			lo.erase(lo.find(*lo.rbegin()));
		}

		ans += *hi.begin();
	}

	printf("%lld\n", ans);

	return 0;
}

/*
//shiftps's solution.
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <functional>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cstring>
#include <climits>
#include <map>

using namespace std;

using ll          = long long;
using db          = double;
using ld          = long double;
using uint        = unsigned int;
using ull         = unsigned long long;

using pii         = pair<int, int>;
using pll         = pair<ll, ll>;
using tiii        = tuple<int, int, int>;
using tlll        = tuple<ll, ll, ll>;

#define mod7        1000000007
#define mod9        1000000009

#define forall(v)   v.begin(), v.end()
#define prec(x)     setprecision(x) << fixed


int a[250000];

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	multiset<int> l, r;

	for (int i = 0; i < k; i++) {
		l.emplace(a[i]);
	}

	ll sum = 0;

	while (l.size() >= r.size()) {
		r.emplace(*l.rbegin());
		l.erase(l.find(*l.rbegin()));
	}
	sum += *r.begin();

	for (int i = k; i < n; i++) {
		auto lit = l.find(a[i - k]);
		if (lit != l.end()) {
			l.erase(lit);
		}
		else {
			r.erase(r.find(a[i - k]));
		}
		l.emplace(a[i]);

		while (l.size() < r.size()) {
			l.emplace(*r.begin());
			r.erase(r.begin());
		}
		while (l.size() >= r.size()) {
			r.emplace(*l.rbegin());
			l.erase(l.find(*l.rbegin()));
		}

		sum += *r.begin();
	}

	cout << sum;

	return 0;
}
*/

/*
//2nd trial. using modified segtree
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 65536
#define ll long long

struct segtree {
	int tree[Msize * 4];

	segtree() {
		memset(tree, 0, sizeof(tree));
	}

	int query(int val, int node, int nodeLeft, int nodeRight) {
		if (nodeLeft == nodeRight) return nodeLeft;

		int mid = (nodeLeft + nodeRight) / 2;
		if (val <= tree[node * 2]) return query(val, node * 2, nodeLeft, mid);
		else return query(val - tree[node * 2], node * 2 + 1, mid + 1, nodeRight);
	}

	int update(int idx, int val, int node, int nodeLeft, int nodeRight) {
		if (idx < nodeLeft || idx > nodeRight) return tree[node];

		if (nodeLeft == nodeRight) {
			tree[node] += val;
			return tree[node];
		}

		int mid = (nodeLeft + nodeRight) / 2;

		tree[node] = update(idx, val, node * 2, nodeLeft, mid) + update(idx, val, node * 2 + 1, mid + 1, nodeRight);

		return tree[node];
	}
};

segtree SEG;
int N, K;
int input[250250];
ll ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;

	for (int i = 0; i < N; ++i) {
		cin >> input[i];
	}

	for (int i = 0; i < K; ++i) {
		SEG.update(input[i], 1, 1, 0, Msize);
	}

	ans = SEG.query((K + 1) / 2, 1, 0, Msize);

	for (int i = K; i < N; ++i) {

		SEG.update(input[i], 1, 1, 0, Msize);
		SEG.update(input[i - K], -1, 1, 0, Msize);

		int medium = SEG.query((K + 1) / 2, 1, 0, Msize);
		ans += medium;
	}

	printf("%lld\n", ans);

	return 0;
}

*/

/*
//1st trial. FAIL
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define Msize 250250
#define pii pair<int,int>

int N, K;
ll ans;
int input[Msize];

struct maxtree {
	pii tree[Msize * 4];

	pii piimaxcomp(pii a, pii b) {
		pii ret;
		if (a.first >= b.first) {
			ret = a;
			return ret;
		}
		else {
			ret = b;
			return ret;
		}
	}

	pii init(int left, int right, int node) {
		if (left == right) {
			tree[node] = { -1,left };
			return tree[node];
		}

		int mid = (left + right) / 2;

		pii ans = piimaxcomp(init(left, mid, node * 2), init(mid + 1, right, node * 2 + 1));

		return ans;
	}

	pii query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (left > nodeRight || right < nodeLeft) return { -1,-1 };

		if (left <= nodeLeft && right >= nodeRight) return tree[node];

		int mid = (nodeLeft + nodeRight) / 2;

		pii ret = piimaxcomp(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));

		return ret;
	}

	pii update(int index, int val, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || index > nodeRight) return tree[node];

		if (nodeLeft == nodeRight) {
			tree[node].first = val;
			return tree[node];
		}

		int mid = (nodeLeft + nodeRight) / 2;
		tree[node] = piimaxcomp(update(index, val, node * 2, nodeLeft, mid), update(index, val, node * 2 + 1, mid + 1, nodeRight));
		return tree[node];
	}

};

struct mintree {
	pii tree[Msize * 4];

	pii piimincomp(pii a, pii b) {
		pii ret;
		if (a.first <= b.first) {
			ret = a;
			return ret;
		}
		else {
			ret = b;
			return ret;
		}
	}

	pii init(int left, int right, int node) {
		if (left == right) {
			tree[node] = { INT_MAX,left };
			return tree[node];
		}

		int mid = (left + right) / 2;

		pii ans = piimincomp(init(left, mid, node * 2), init(mid + 1, right, node * 2 + 1));

		return ans;
	}

	pii query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (left > nodeRight || right < nodeLeft) return { -1,-1 };

		if (left <= nodeLeft && right >= nodeRight) return tree[node];

		int mid = (nodeLeft + nodeRight) / 2;

		pii ret = piimincomp(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));

		return ret;
	}

	pii update(int index, int val, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || index > nodeRight) return tree[node];

		if (nodeLeft == nodeRight) {
			tree[node].first = val;
			return tree[node];
		}

		int mid = (nodeLeft + nodeRight) / 2;
		tree[node] = piimincomp(update(index, val, node * 2, nodeLeft, mid), update(index, val, node * 2 + 1, mid + 1, nodeRight));
		return tree[node];
	}
};

struct tup {
	int r, idx, minmax;
};

vector<int> seed;
vector<vector<tup>> q(2);
maxtree maxseg;
mintree minseg;

int minTsize, maxTsize;

int main() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		cin >> input[i];
		if (i < K) seed.push_back(input[i]);
	}

	ans = 0;

	if (K == 1) {
		for (int i = 0; i < N; ++i) ans += input[i];

		printf("%lld\n", ans);
		return 0;
	}

	if (K == 2) {
		for (int i = 0; i < N - 1; ++i) {
			ans += min(input[i], input[i + 1]);
		}

		printf("%lld\n", ans);
		return 0;
	}

	sort(seed.begin(), seed.end());

	maxTsize = (K + 1) / 2;
	minTsize = K - maxTsize;

	maxseg.init(1, maxTsize, 1);
	minseg.init(1, minTsize, 1);

	for (int i = 0; i < maxTsize; ++i) {
		maxseg.update(i + 1, seed[i], 1, 1, maxTsize);
		q[1].push_back({ seed[i], i + 1, 0 });
	}

	for (int i = maxTsize; i < K; ++i) {
		minseg.update(i - maxTsize + 1, seed[i], 1, 1, minTsize);
		q[0].push_back({ seed[i], i - maxTsize + 1, 1 });
	}


	for (int i = K; i < N; ++i) {
		int ridx, midx, m, x, r, chk;
		pii mediumval = maxseg.query(1, maxTsize, 1, 1, maxTsize);

		x = input[i];
		m = mediumval.first;
		midx = mediumval.second;
		r = input[i - K];

		if (r <= m) chk = 1;
		else chk = 0;

		ridx = q[chk][0].idx;



		q[chk].erase(q[chk].begin());

		printf("med %d\n", m);

		if (r >= m && x >= m) {
			minseg.update(ridx, x, 1, 1, minTsize);
			q[0].push_back({ x,ridx,0 });
		}
		if (r < m && x < m) {
			maxseg.update(ridx, x, 1, 1, maxTsize);
			q[1].push_back({ x,ridx,1 });
		}
		if (r >= m && x < m) {
			minseg.update(ridx, m, 1, 1, minTsize);
			maxseg.update(midx, x, 1, 1, maxTsize);
			q[1].push_back({ x,midx,1 });
		}

		if (r < m && x >= m) {
			pii minT = minseg.query(1, minTsize, 1, 1, minTsize);
			int minTval = minT.first, minTidx = minT.second;
			minseg.update(minTidx, x, 1, 1, minTsize);
			maxseg.update(ridx, minTval, 1, 1, maxTsize);
			q[0].push_back({ x,minTidx,0 });
		}

		printf("minsize maxsize\n");

	}

	return 0;



}
*/