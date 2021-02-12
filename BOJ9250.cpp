//BOJ9250

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 100100
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = INT_MAX / 2;

int trie[100100][26],last[100100], fail[100100], num, root;
vector<string> slist;

void buildtrie() {
	num = 1;
	root = 1;

	for (int k = 0; k < slist.size(); ++k) {
		string s = slist[k];
		int l = s.length(), now = root;
		for (int i = 0; i < l; ++i) {
			int c = s[i] - 'a';
			if (trie[now][c] == 0) {
				trie[now][c] = ++num;
			}
			now = trie[now][c];
			if (i == l - 1) {
				last[now] = true;
			}
		}
	}
}

void buildfail() {
	fail[root] = root;
	queue<int> q;

	q.push(root);

	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (int i = 0; i < 26; ++i) {
			int there = trie[here][i];
			if (there == 0) continue;

			if (here == root) {
				fail[there] = root;
			}
			else {
				int t = fail[here];
				while (t != root && trie[t][i] == 0) {
					t = fail[t];
				}

				if (trie[t][i]) t = trie[t][i];

				fail[there] = t;
			}
			
			if (last[fail[there]]) last[there] = true;

			q.push(there);

		}
	}
}

bool traverse(string& s) {
	int l = s.length();
	bool ans = false;
	int now = root;
	for (int i = 0; i < l; ++i) {
		int c = s[i] - 'a';
		
		while (now != root && trie[now][c] == 0) {
			now = fail[now];
		}
		if (trie[now][c]) now = trie[now][c];
		
		if (last[now]) {
			ans = true;
			break;
		}
	}

	return ans;
}

int n, m;
vector<string> qlist;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin; cin.open("input.txt");

	cin >> n;
	for (int i = 0; i < n; ++i) {
		string tmp;
		cin >> tmp;
		slist.push_back(tmp);
	}

	memset(trie, 0, sizeof(trie));
	memset(last, 0, sizeof(last));
	memset(fail, 0, sizeof(fail));

	buildtrie();
	buildfail();

	cin >> m;

	for (int i = 0; i < m; ++i) {
		string tmp;
		cin >> tmp;
		if (traverse(tmp)) printf("YES\n");
		else printf("NO\n");
	}

	return 0;

}