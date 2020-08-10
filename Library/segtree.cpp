#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 100100
#define ll long long

ll input[100100];
int N, Q;


struct segtree {
	ll tree[4 * Msize];

	segtree() {
		memset(tree, 0, sizeof(tree));
	}

	ll init(int left, int right, int node) {
		//init(1,N,1)
		if (left == right) {
			tree[node] = input[left];
			return tree[node];
		}

		int mid = (left + right) / 2;

		tree[node] = min(init(left, mid, node * 2), init(mid + 1, right, node * 2 + 1));
		return tree[node];
	}

	ll query(int left, int right, int node, int nodeLeft, int nodeRight) {
		//query(left,right,1,1,N);
		if (left > nodeRight || right < nodeLeft) return LLONG_MAX;
		// 만약 node 가 표시하는 구간이 left 와 right 사이에 없다면 return MAX.

		if (left <= nodeLeft && right >= nodeRight) return tree[node];
		// 만약 node 가 표시하는 구간이 left 와 right 사이에 포함 된다면 node 의 값을 return.

		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
		// 만약 node 가 표시하는 구간이 left 와 right 구간과 일부만 겹친다면 구간을 쪼갠다.
	}
};

segtree SEG;