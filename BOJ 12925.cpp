#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int a[50];
int b[50];
int T, N;
int Mod = 1000;

double sqrt5 = sqrt(5);
//3-sqrt(5) < 1 이용
//수열의 특성 이용... 어렵다

struct matrix {
    int M[2][2] = { {0,0},{0,0} };
};

#define pii pair<int,int>

matrix arrCache[50];

matrix matmult(matrix A, matrix B) {
    matrix ret;
    ret.M[0][0] = (A.M[0][0] * B.M[0][0] + A.M[0][1] * B.M[1][0]) % Mod;
    ret.M[0][1] = (A.M[0][0] * B.M[0][1] + A.M[0][1] * B.M[1][1]) % Mod;
    ret.M[1][0] = (A.M[1][0] * B.M[0][0] + A.M[1][1] * B.M[1][0]) % Mod;
    ret.M[1][1] = (A.M[1][0] * B.M[0][1] + A.M[1][1] * B.M[1][1]) % Mod;
    return ret;
}

void powdp() {
    matrix t;
    t.M[0][0] = 6; t.M[0][1] = -4;
    t.M[1][0] = 1; t.M[1][1] = 0;
    arrCache[1] = t;
    for (int i = 1; i < 49; ++i) {
        arrCache[i + 1] = matmult(arrCache[i], arrCache[i]);
    }
}

int main()
{
    powdp();
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        scanf("%d", &N);

        int j = 1;
        matrix ansmat;
        ansmat.M[0][0] = 1;
        ansmat.M[1][1] = 1;

        while (N) {
            if (N & 1) {
                ansmat = matmult(ansmat, arrCache[j]);
            }
            ++j;
            N >>= 1;
        }

        // c1 = 6, c0 =2;
        int ansmod = ansmat.M[1][0] * 6 + ansmat.M[1][1] * 2;
        if (ansmod < 0) ansmod += 9999;
        else ansmod -= 1;

        ansmod %= Mod;


        if (ansmod >= 100) {
            printf("Case #%d: %d\n", i + 1, ansmod);
        }
        else if (ansmod >= 10) {
            printf("Case #%d: 0%d\n", i + 1, ansmod);
        }
        else {
            printf("Case #%d: 00%d\n", i + 1, ansmod);
        }
    }

    

    return 0;
}
