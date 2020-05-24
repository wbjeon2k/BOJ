#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int sieve[10010];
vector<int>primelist;
int N;

void calcsieve() {
    memset(sieve, -1, sizeof(sieve));
    sieve[1] = 0;
    for (int i = 2; i <= 10000; ++i) {
        if (sieve[i] == -1) {
            primelist.push_back(i);
            for (int j = i * 2; j <= 10000; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

bool chkprime(int a) {
    if (a <= 10000) {
        if (sieve[a] == -1) return true;
        else return false;
    }

    for (int i = 0; i < primelist.size(); ++i) {
        if (a % primelist[i] == 0) return false;
        if (primelist[i] * primelist[i] > a) return true;
    }
    return true;
}

void dfs(int here, int cnt) {
    //printf("a%d\n", here);
    if (cnt == N) {
        if (chkprime(here)) printf("%d\n", here);
        return;
    }

    if (chkprime(here)) {
        dfs(here * 10 + 1, cnt + 1);
        dfs(here * 10 + 3, cnt + 1);
        dfs(here * 10 + 5, cnt + 1);
        dfs(here * 10 + 7, cnt + 1);
        dfs(here * 10 + 9, cnt + 1);
    }

    return;
}

int main()
{
    calcsieve();
    cin >> N;
    //printf("%d", primelist.size());
    for (int i = 1; i < 10; ++i) {
        dfs(i, 1);
    }

}

