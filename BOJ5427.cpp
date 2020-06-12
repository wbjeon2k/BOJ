#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int T, N, M;
struct tup {
	int x, y, dist;
};

char input[1010][1010];
bool visited[1010][1010];
int fdist[1010][1010], edist[1010][1010];

queue<tup> fireq, escq;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>M) return false;
	return true;
}

void fire() {
	

	while (!fireq.empty()) {
		tup here = fireq.front();
		fireq.pop();

		int x = here.x, y = here.y, dist = here.dist;

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (isInside(nx, ny) && input[nx][ny] != '#' && fdist[nx][ny] == -1) {
				fdist[nx][ny] = dist + 1;
				visited[nx][ny] = true;
				fireq.push({ nx,ny, dist + 1 });
			}
		}
	}

}

int escape() {
	
	int ret = -1;

	while (!escq.empty()) {
		tup here = escq.front();
		escq.pop();

		int x = here.x, y = here.y, dist = here.dist;

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (isInside(nx, ny) && input[nx][ny] != '#' && edist[nx][ny] == -1) {
				if (fdist[nx][ny] > dist + 1) {
					edist[nx][ny] = dist + 1;
					escq.push({ nx,ny,dist + 1 });
				}
				if (isInside(nx, ny) && input[nx][ny] != '#' && fdist[nx][ny] == -1) {
					edist[nx][ny] = dist + 1;
					escq.push({ nx,ny,dist + 1 });
				}
			}
			if (!isInside(nx, ny)) {
				ret = dist+1;
				return ret;
			}
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> T;
	while (T--) {
		cin >> M >> N;

		memset(visited, 0, sizeof(visited));
		memset(fdist, -1, sizeof(fdist));
		memset(edist, -1, sizeof(edist));

		fireq = queue<tup>();
		escq = queue<tup>();

		for (int i = 1; i <= N; ++i) {
			string s;
			cin >> s;
			for (int j = 1; j <= M; ++j) {
				input[i][j] = s[j - 1];
				if (input[i][j] == '*') {
					fireq.push({ i,j,0 });
					fdist[i][j] = 0;
					visited[i][j] = 1;
				}
				if (input[i][j] == '@') {
					escq.push({ i,j,0 });
					edist[i][j] = 0;
				}
			}
		}

		fire();

		int ans = escape();
		if (ans == -1) printf("IMPOSSIBLE\n");
		else printf("%d\n", ans);
			
	}

	return 0;
}