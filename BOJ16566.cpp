//BOJ 16566

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

vector<int> mlist;
bool chk[4004000];
int N, M, K;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> K;

	int t;
	for (int i = 0; i < M; ++i) {
		cin >> t;
		mlist.push_back(t);
	}

	sort(mlist.begin(), mlist.end());
	memset(chk, 0, sizeof(chk));

	for (int i = 0; i < K; ++i) {
		cin >> t;
		auto iter = upper_bound(mlist.begin(), mlist.end(), t);
		while (chk[*iter]) ++iter;
		printf("%d\n", *iter);
		chk[*iter] = true;
	}
	

	return 0;
}

/*
//kyo20111's  solution.
//query 와 update 를 합친 우아한 코드.
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define mid ((l+r)>>1)
int n, m, k, tree[16001600], a[4004004], in[4004004];
void build(int node, int l, int r){
	if(l == r){
		tree[node] = a[l] ? l : 0;
		return;
	}
	build(node*2, l, mid), build(node*2+1, mid+1, r);
	tree[node] = max(tree[node*2], tree[node*2+1]);
}
int find(int node, int l, int r, int v){
	if(l == r){
		tree[node] = 0;
		while(node/2){
			node/=2;
			tree[node] = max(tree[node*2], tree[node*2+1]);
		}
		return l;
	}

	int re;
	if(v < tree[node*2]) re = find(node*2, l, mid, v);
	else re = find(node*2+1, mid+1, r, v);
	return re;
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m >> k;
	for(int i=1;i<=m;i++){
		int b; cin >> b;
		a[b] = 1;
	}

	build(1, 1, n);

	for(int i=1;i<=k;i++){
		int b; cin >> b;
		cout << find(1, 1, n, b) << '\n';
	}
}
*/

/*
//1st trial. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

multiset<int> mset;
int N, M, K;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> K;

	for (int i = 0; i < M; ++i) {
		int t;
		cin >> t;
		mset.emplace(t);
	}

	for (int i = 0; i < K; ++i) {
		int t;
		cin >> t;
		auto iter = upper_bound(mset.begin(), mset.end(), t);
		printf("%d\n", *iter);
		mset.erase(iter);
	}

	return 0;
}
*/