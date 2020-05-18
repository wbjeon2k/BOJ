#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct fenwickTree {
    vector<int> ftree;

    fenwickTree() {
        ftree.resize(100001);
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

int input[100001];

int convert(int a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    if (a == 0) return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    char a;
    int b, c;
    int n, k;

    while (cin >> n >> k) {

        fenwickTree F1, F0;
        memset(input, 0, sizeof(input));

        for (int i = 1; i <= n; ++i) {
            int t;
            cin >> t;
            input[i] = convert(t);
            if (input[i] == 0) {
                F0.add(i, 1);
            }
            if (input[i] == -1) {
                F1.add(i, 1);
            }
        }


        for (int i = 0; i < k; ++i) {

            cin >> a >> b >> c;
            if (a == 'C') {
                c = convert(c);
                //printf("c %d\n", c);
                if (input[b] == 0) {
                    if (c != 0) F0.add(b, -1);
                    if (c == -1) F1.add(b, 1);
                }
                else if (input[b] == -1) {
                    if (c != -1) F1.add(b, -1);
                    if (c == 0) F0.add(b, 1);
                }
                else {
                    if (c == 0) F0.add(b, 1);
                    if (c == -1) F1.add(b, 1);
                }

                input[b] = c;
                // printf("C z%d m%d\n", F0.sum(n), F1.sum(n));
            }
            if (a == 'P') {
                int znum = F0.sum(c) - F0.sum(b - 1);
                int mnum = F1.sum(c) - F1.sum(b - 1);
                //printf("P z%d m%d\n", znum, mnum);
                if (znum > 0) {
                    printf("0");
                }
                if (znum == 0) {
                    if (mnum % 2 == 1) {
                        printf("-");
                    }
                    else {
                        printf("+");
                    }
                }
            }
        }
        printf("\n");
        
    }

    return 0;
}
