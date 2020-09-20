//BOJ9576

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int T, N, M;
#define pii pair<int,int>

vector<pii> qlist;
bool visited[1010];

bool comp(pii& a, pii& b) {
	if (a.second < b.second) return true;
	if (a.second == b.second && a.first < b.first) return true;

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;

	while (T--) {
		cin >> N >> M;

		qlist.clear();

		for (int i = 0; i < M; ++i) {
			pii tmp;

			cin >> tmp.first >> tmp.second;
			qlist.push_back(tmp);
		}

		sort(qlist.begin(), qlist.end(), comp);

		memset(visited, 0, sizeof(visited));
		int cnt = 0;

		for (int i = 0; i < M; ++i) {
			int s, e;
			s = qlist[i].first, e = qlist[i].second;

			for (int j = s; j <= e; ++j) {
				if (visited[j]) continue;
				++cnt;
				visited[j] = true;
				break;
			}
		}

		printf("%d\n", cnt);
	}

	return 0;
}

/*
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 1010
#define pii pair<int,int>

int T, N, M;
int query[Msize];
bool visited[Msize];
vector<pii> qlist;

bool comp(pii& a, pii& b) {
	if (a.second - a.first < b.second - b.first) return true;

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	
	while (T--) {
		cin >> N >> M;

		memset(visited, 0, sizeof(visited));
		memset(query, 0, sizeof(query));
		qlist.clear();

		for (int i = 0; i < M; ++i) {
			int s, e;
			cin >> s >> e;

			for (int j = s; j <= e; ++j) {
				++query[j];
			}

			qlist.push_back({ s,e });
		}

		sort(qlist.begin(), qlist.end(), comp);

		int cnt = 0;

		for (int i = 0; i < qlist.size(); ++i) {
			int minq = Msize, midx = -1;
			int s, e;
			s = qlist[i].first, e = qlist[i].second;

			for (int j = s; j <= e; ++j) {
				if (visited[j]) continue;

				if (minq > query[j]) {
					minq = query[j];
					midx = j;
				}
			}

			if (midx != -1) {
				++cnt;
				visited[midx] = true;
			}
			
		}

		printf("%d\n", cnt);
		
	}

	return 0;
}

*/