#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int isChild[33000];
priority_queue<int> pq;

vector<vector<int>> adj;
int N,M;

int main()
{
    scanf("%d %d", &N, &M);
    adj.resize(N + 1);

    memset(isChild, 0, sizeof(isChild));

    for (int i = 0; i < M; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);

        adj[a].push_back(b);
        ++isChild[b];
    }

    for (int i = 1; i <= N; ++i) {
        if (isChild[i]==0) {
            pq.push(-i);
        }
    }

    while (!pq.empty()) {
        int t = -pq.top();
        printf("%d ", t);
        
        pq.pop();

        int n = adj[t].size();
        for (int i = 0; i < n; ++i) {
            int next = adj[t][i];
            --isChild[next];
            if (isChild[next] == 0) {
                pq.push(-next);
            }
        }
    }

    return 0;

}

/*
//csehydrogen's solution. Fast io
#include <unistd.h>
class FastIO {
    int fd, bufsz;
    char *buf, *cur, *end;
public:
    FastIO(int _fd = 0, int _bufsz = 1 << 20) : fd(_fd), bufsz(_bufsz) {
        buf = cur = end = new char[bufsz];
    }
    ~FastIO() {
        delete[] buf;
    }
    void readbuf() {
        cur = buf;
        end = buf + bufsz;
        while (true) {
            int res = read(fd, cur, end - cur);
            if (res == 0) break;
            if (res > 0)
                cur += res;
        }
        end = cur;
        cur = buf;
    }
    int readint() {
        while (true) {
            if (cur == end) readbuf();
            if (*cur >= '0') break;
            ++cur;
        }
        int ret = 0;
        while (true) {
            if (cur == end) readbuf();
            if (*cur < '0') break;
            ret = ret * 10 + *cur - '0';
            ++cur;
        }
        return ret;
    }
};

#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>
using namespace std;
int d[32001];
char z[600001], *o = z;
int main() {
    FastIO fio;
    int n = fio.readint(), m = fio.readint();
    vector<vector<int> > g(n + 1);
    for (int i = 0; i < m; ++i) {
        int a = fio.readint(), b = fio.readint();
        g[a].push_back(b);
        ++d[b];
    }
    priority_queue<int, vector<int>, greater<int> > q;
    for (int i = 1; i <= n; ++i)
        if (d[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int x = q.top(); q.pop();
        o += sprintf(o, "%d ", x);
        for (int y : g[x]) {
            --d[y];
            if (d[y] == 0)
                q.push(y);
        }
    }
    *o = 0;
    printf("%s", z);
    return 0;
}

*/

/* TC generator
#include <bits/stdc++.h>
using namespace std;

int main() {
    printf("50 50\n");

    srand(time(NULL));

    bool chk[51] = {0};
    memset(chk,false,sizeof(chk));

    for(int i=0;i<50;++i){
        int t = rand()%50 + 1;
        while(chk[t]){
            t = rand()%50 + 1;
        }
        chk[t] = true;
        printf("%d %d\n", t, rand()%t+1);
    }
    return 0;
}
*/