//BOJ18920

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 50100
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = LLONG_MAX/2;

int trie[1010][26], last[1010], fail[1010];
ll adjmat[111][111];
vector<string> slist;
int root, num;//num: buildtrie 이후 trie 의 노드 갯수

void buildtrie() {
	num = 1;
	root = 1;
	for (int k = 0; k < slist.size(); ++k) {
		int l = slist[k].length();
		string s = slist[k];

		int now = root;
		for (int i = 0; i < l; ++i) {
			int c = s[i] - 'a';
			if (trie[now][c] == 0) {
				trie[now][c] = ++num;
			}
			now = trie[now][c];
			if (i == l - 1) last[now] = 1;
		}
	}
}

void buildfail() {
	queue<int> q;
	q.push(root);
	fail[root] = root;

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		for (int i = 0; i < 26; ++i) {
			int next = trie[here][i];
			if (next == 0) continue;

			if (here == root) fail[next] = root;
			else {
				int t = fail[here];
				while (t != root && trie[t][i] == 0) {
					t = fail[t];
				}
				if (trie[t][i]) t = trie[t][i];
				fail[next] = t;
			}

			if (last[fail[next]]) last[next] = 1;
			q.push(next);
		}
	}
}

void buildadj() {
	//node: 1~101
	for (int i = 1; i <= num; ++i) {
		
		if (last[i]) continue;
		
		for (int j = 0; j < 26; ++j) {

			if (trie[i][j] && last[trie[i][j]] == 0) {
				//다음 노드로 갈 수 있고 last 가 아니라면
				//i 노드에서 다음 노드로 가는 경로 있다
				++adjmat[i][trie[i][j]];
			}

			
			if (trie[i][j] == 0) {
				int next = fail[i];
				while (next != root && trie[next][j] == 0) {
					next = fail[next];
				}
				if (trie[next][j]) {
					if (last[trie[next][j]] == 0) ++adjmat[i][trie[next][j]];
				}
				else ++adjmat[i][root];
				
			}

		}
		
		
	}
}

const ll MOD = 998244353;

struct Mat {
	ll mat[111][111];

	Mat() {
		memset(mat, 0, sizeof(mat));
	}
};

Mat matmult(Mat a, Mat b) {
	Mat ret;
	for (int k = 1; k <= num; ++k) {
		for (int i = 1; i <= num; ++i) {
			a.mat[i][k] %= MOD;
			ll r = a.mat[i][k];
			for (int j = 1; j <= num; ++j) {
				ll tmp = (r * b.mat[k][j]) % MOD;
				ret.mat[i][j] += tmp;
				ret.mat[i][j] %= MOD;
			}
		}
	}
	return ret;
}

Mat matpow(Mat a, int p) {
	Mat ret;
	for (int i = 1; i <= num; ++i) ret.mat[i][i] = 1;

	while (p) {
		if (p & 1) ret = matmult(ret, a);
		a = matmult(a, a);
		p /= 2;
	}

	return ret;
}

int n, l;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin; cin.open("input.txt");

	memset(trie, 0, sizeof(trie));
	memset(last, 0, sizeof(last));
	memset(fail, 0, sizeof(fail));

	cin >> n >> l;
	slist.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> slist[i];
	}

	buildtrie();
	buildfail();
	buildadj();

	Mat ansmat, tmpmat;
	for (int i = 1; i <= num; ++i) {
		for (int j = 1; j <= num; ++j) {
			tmpmat.mat[i][j] = adjmat[i][j];
		}
	}
	//(adjmat)^L
	ansmat = matpow(tmpmat, l);

	ll ans = 0;
	//root 에서 갈 수 있는 길이 L 인 경로의 수
	for (int j = 1; j <= num; ++j) {
		//if (last[j]) continue;
		ans += ansmat.mat[root][j];
		ans %= MOD;
	}

	printf("%lld\n", ans);
	

	return 0;

}