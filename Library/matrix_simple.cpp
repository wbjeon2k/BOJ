#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<int, int>
#define pll pair<ll, ll>
#define MAXI 1000000000
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = INT_MAX / 4;

#define MOD 100000007

int T;
ll N, K;

// matrix multiplication & power for square matices

struct Matrix {
    ll mat_mod = MOD;
    int size = 11;
    ll mat[11][11];
};

Matrix mat_mult(Matrix A, Matrix B){
    Matrix ans;
    int s = A.size;

    memset(ans.mat,0,sizeof(ans.mat));

    for (int i = 0; i < s; ++i){
        for (int j = 0; j < s; ++j){
            for (int k = 0; k < s;++k){
                ans.mat[i][j] += A.mat[i][k] * B.mat[k][j];
                ans.mat[i][j] %= MOD;
            }
        }
    }

    return ans;
}

Matrix mat_pow(Matrix A, ll p){
    Matrix ans;
    memset(ans.mat, 0, sizeof(ans.mat));

    for (int i = 0; i < ans.size; ++i){
        ans.mat[i][i] = 1;
    }

    while(p){
        if (p % 2) ans = mat_mult(ans, A);
        A = mat_mult(A, A);
        p /= 2;
    }

    return ans;
}
