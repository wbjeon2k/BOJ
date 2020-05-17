#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct fenwickTree {
    vector<int> ftree;

    fenwickTree() {
        ftree.resize(1000001,0);
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
int input[1001000];

int main()
{
    memset(input, 0, sizeof(input));
    scanf("%d", &N);

    fenwickTree F;

    for (int i = 1; i <= N; ++i) {
        int t;
        scanf("%d", &t);
        input[t] = i;
        //F.add(i, 1);
    }

    ll ret = 0;
    for (int i = 0; i < N; ++i) {
        int t;
        scanf("%d", &t);
        
        //printf("%d %d\n", F.sum(1000000), F.sum(input[t]));

        ret += (ll)(F.sum(1000000) - F.sum(input[t]));
        F.add(input[t], 1);
    }

    printf("%lld", ret);

    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

bool chk[101];
int main() {
    srand(time(NULL));
    memset(chk, 0, sizeof(chk));
    printf("100\n");
    for(int i=1;i<=100;++i){
        printf("%d ", i);
    }
    printf("\n");
    for(int i=1;i<=100;++i){
        int t = rand()%100 +1;
        if(chk[t]){
            t = rand()%100 + 1;
        }
        chk[t] = true;
        printf("%d ", t);
    }
    return 0;
}

/*
//TC1
100
1 2 3 4 5 6 7 8 9 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
31 32 33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48 49 50
51 52 53 54 55 56 57 58 59 60
61 62 63 64 65 66 67 68 69 70
71 72 73 74 75 76 77 78 79 80
81 82 83 84 85 86 87 88 89 90
91 92 93 94 95 96 97 98 99 100

84 87 78 16 94 36 93 50 22 63
28 91 60 64 27 41 73 37 12 69
68 30 83 31 24 36 3 23 59 70
94 57 43 74 20 85 38 99 25 71
14 92 81 74 71 97 82 6 26 28
6 47 14 58 96 46 15 35 65 44
51 88 9 77 79 89 4 52 55 100
33 61 69 40 13 87 95 96 35 68
2 98 18 53 2 87 42 66 90 45
41 32 98 72 76 10 68 98 54 66
*/

/*
// TC2
100
1 2 3 4 5 6 7 8 9 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
31 32 33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48 49 50
51 52 53 54 55 56 57 58 59 60
61 62 63 64 65 66 67 68 69 70
71 72 73 74 75 76 77 78 79 80
81 82 83 84 85 86 87 88 89 90
91 92 93 94 95 96 97 98 99 100

79 16 85 27 75 25 78 12 19 38
26 20 91 65 77 63 43 22 76 92
60 42 29 23 73 74 100 52 67 31
41 60 4 55 97 81 80 52 24 85
2 13 10 14 54 90 88 49 61 30
65 96 84 95 37 54 75 73 6 62
28 56 55 77 64 82 10 2 70 89
34 14 25 33 16 59 39 40 100 44
36 8 32 6 18 15 13 70 22 3
30 38 45 46 37 27 54 26 57 58
*/
