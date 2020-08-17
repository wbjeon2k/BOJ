//BOJ14427

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 100100
#define ll long long

ll input[100100];
int N, Q;


struct segtree {
#define ll long long
#define pll pair<ll,ll>

	pll tree[4 * Msize];

	segtree() {
		for (int i = 0; i < 4 * Msize; ++i) {
			tree[i].first = 0;
			tree[i].second = 0;
		}
	}

	pll minpll(pll a, pll b) {
		if (a.first < b.first) return a;
		else if (a.first > b.first) return b;

		else if (a.second < b.second) return a;
		else if (a.second > b.second) return b;

		else return a;
	}

	pll init(int left, int right, int node) {
		//printf("l%d r%d n%d\n", left, right, node);
		//init(1,N,1)
		if (left == right) {
			tree[node].first = input[left];
			tree[node].second = left;
			return tree[node];
		}

		int mid = (left + right) / 2;

		pll tmp = minpll(init(left, mid, node * 2), init(mid + 1, right, node * 2 + 1));
		tree[node] = tmp;
		return tree[node];
	}

	pll query(int left, int right, int node, int nodeLeft, int nodeRight) {
		//query(left,right,1,1,N);
		if (left > nodeRight || right < nodeLeft) return { LLONG_MAX,LLONG_MAX };
		// 만약 node 가 표시하는 구간이 left 와 right 사이에 없다면 return MAX.

		if (left <= nodeLeft && right >= nodeRight) return tree[node];
		// 만약 node 가 표시하는 구간이 left 와 right 사이에 포함 된다면 node 의 값을 return.

		int mid = (nodeLeft + nodeRight) / 2;
		return minpll(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
		// 만약 node 가 표시하는 구간이 left 와 right 구간과 일부만 겹친다면 구간을 쪼갠다.
	}

	pll update(int index, int newVal, int node, int nodeLeft, int nodeRight) {
		if (index < nodeLeft || index > nodeRight) return tree[node];

		if (nodeLeft == nodeRight) {
			tree[node].first = newVal;
			return tree[node];
		}

		int mid = (nodeLeft + nodeRight) / 2;
		pll tmp = minpll(update(index, newVal, node * 2, nodeLeft, mid), update(index, newVal, node * 2 + 1, mid + 1, nodeRight));
		tree[node] = tmp;

		return tree[node];
	}
};

segtree SEG;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		cin >> input[i + 1];
	}

	cin >> Q;

	SEG.init(1,N,1);

	while (Q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int idx, val;
			cin >> idx >> val;
			SEG.update(idx, val, 1, 1, N);
		}
		else {
			pll ans = SEG.query(1, N, 1, 1, N);
			printf("%lld\n", ans.second);
		}
	}

	return 0;
}

/*
//gunwookim's solution. using std::set
#include <bits/stdc++.h>
using namespace std;
pair <int,int> t[400005];
int n,q,bit;
int a[100005];
set <pair <int,int> > s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for(bit = 1;bit <= n;bit *= 2);
	int x,l,r;
	int idx = 1,idx2 = 1;
	for(int i = 1;i <= n;i++) {
		cin >> a[i];
		s.insert({a[i],i});
	}
	cin >> q;
	while(q--) {
		cin >> x;
		if(x == 1) {
			cin >> l >> r;
			s.erase({a[l],l});
			a[l] = r;
			s.insert({a[l],l});
		}
		if(x == 2) {
			auto it = *s.begin();
			cout << it.second << '\n';
		}
	}
	return 0;
}
*/