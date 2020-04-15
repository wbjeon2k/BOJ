#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>


using namespace std;

int pmap[505][505];
int cache[505][505];
vector< pair<int, pair<int, int>>> psort;
int N, maxi;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool comp(const pair<int, pair<int, int>> a, const pair<int, pair<int, int>> b) {
    return (a.first < b.first);
}

int main()
{
    scanf("%d", &N);

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            pair<int, int> t = {i,j};
            scanf("%d", &pmap[i][j]);
            psort.push_back(make_pair(pmap[i][j], t));
        }
    }

    sort(psort.begin(), psort.begin()+N*N, comp);

    for (int i = 0; i < 505; ++i) {
        for (int j = 0; j < 505; ++j) {
            cache[i][j] = 1;
        }
    }

    for (auto it = psort.begin(); it != psort.end(); ++it) {
        pair<int, int> t = it->second;
        int x = t.first, y = t.second;
        for (int i = 0; i < 4; ++i) {
            if (x + dx[i] >= 1 && x + dx[i] <= N && y + dy[i] >= 1 && y + dy[i] <= N) {
                if (pmap[x + dx[i]][y + dy[i]] > pmap[x][y]) {
                    cache[x + dx[i]][y + dy[i]] = max(cache[x][y]+1, cache[x + dx[i]][y + dy[i]]);
                    
                }
                maxi = max(maxi, cache[x + dx[i]][y + dy[i]]);
            }
        }
    }

    printf("%d", (N!=1) ? maxi : 1);

    return 0;
}


/*
sort by <bamboo, index>
bamboo(x+-1, y+-1) > bamboo(x,y): cache(x+-1, y+-1) += cache(x,y);
*/