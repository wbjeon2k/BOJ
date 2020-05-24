#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
bool visited[100][100];

int dx[7] = { 0,0,1,1,0,-1,-1 };
int dy[7] = { 0,1,1,-1,-1,-1,1 };

//육각형 한 변을 따라 이동하면
//그 다음 방향을 바꿀 수 있는 경우의 수는 2가지

int ret;

void dfs(int x, int y, int cnt, int mode) {
	//if (x == 51 && y == 49 && cnt==N) printf("%d %d\n", x, y);
	//if (x == 49 && y == 49 && cnt==N) printf("%d %d\n", x, y);

	if (cnt > N) {
		if (visited[x][y]) ++ret;
		return;
	}

	if (cnt <= N && visited[x][y]) return;

	int ret = 0;
	visited[x][y] = true;
	if (mode == 1) {
		dfs(x + dx[2], y + dy[2], cnt + 1, 2);
		dfs(x + dx[6], y + dy[6], cnt + 1, 6);
	}
	if (mode == 2) {
		dfs(x + dx[1], y + dy[1], cnt + 1, 1);
		dfs(x + dx[3], y + dy[3], cnt + 1, 3);
	}
	if (mode == 3) {
		dfs(x + dx[2], y + dy[2], cnt + 1, 2);
		dfs(x + dx[4], y + dy[4], cnt + 1, 4);
	}
	if (mode == 4) {
		dfs(x + dx[5], y + dy[5], cnt + 1, 5);
		dfs(x + dx[3], y + dy[3], cnt + 1, 3);
	}
	if (mode == 5) {
		dfs(x + dx[4], y + dy[4], cnt + 1, 4);
		dfs(x + dx[6], y + dy[6], cnt + 1, 6);
	}
	if (mode == 6) {
		dfs(x + dx[1], y + dy[1], cnt + 1, 1);
		dfs(x + dx[5], y + dy[5], cnt + 1, 5);
	}

	visited[x][y] = false;
	return;
}

int main() {
	cin >> N;
	int ans = 0;

	memset(visited, 0, sizeof(visited));
	dfs(50, 50, 0, 6);
	//2가지 방향으로 탐색하므로 ret/2

	printf("%d", ret/2);

	return 0;
}

/*
//koosaga's solution. O(1) lol
#include <bits/stdc++.h>
using namespace std;

vector<int> ans = {0,0,0,0,0,2,2,4,8,26,36,80,148,332,556,1172,2112,4350,7732,15568,28204,56100,101640};

int main(){
	int n;cin >> n; cout << ans[n] << endl;
}
*/