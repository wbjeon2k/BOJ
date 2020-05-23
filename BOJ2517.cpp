#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct fenwickTree {
    vector<int> ftree;

    fenwickTree() {
        ftree.resize(500001, 0);
    }

    void add(int pos, int val) {
        while (pos < ftree.size()) {
            ftree[pos] += val;
            pos += pos & (-pos);
        }
    }

    int sum(int pos) {
        int ret = 0;
        while (pos > 0) {
            ret += ftree[pos];
            pos &= (pos - 1);
        }
        return ret;
    }
};

int N;

typedef pair<int, int> pii;
int input[500500];
vector<int> newidx;


int main()
{
    scanf("%d", &N);
    memset(input, 0, sizeof(input));

    for (int i = 1; i <= N; ++i) {
        int t;
        scanf("%d", &t);
        input[i] = t;
        newidx.push_back(t);
    }

    sort(newidx.begin(), newidx.end());

    fenwickTree F;

    for (int i = 1; i <= N; ++i) {
        int nidx = (lower_bound(newidx.begin(), newidx.end(), input[i]) - newidx.begin()) + 1;
        //printf("%d\n", nidx);
        int rank = 1 + (F.sum(500000) - F.sum(nidx));
        //printf("%d %d\n", F.sum(500000), F.sum(nidx));
        printf("%d\n", rank);
        F.add(nidx, 1);
    }

    //printf("%d\n", F.sum())

    return 0;
}
