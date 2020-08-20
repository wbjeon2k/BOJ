//BOJ1572

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