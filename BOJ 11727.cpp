#define _CRT_SECURE_NO_WARNINGS


#include <bits/stdc++.h>

int n;

using namespace std;

/*
class BigInt {
private:
    vector<int> numlist;

public:
    BigInt() {
        this->numlist = { -1 };
    }

    BigInt(int a) {
        this->numlist = { a };
    }

    BigInt(string s) {
        for (int i = 0; i < s.size(); ++i) {
            this->numlist.push_back(s[i] - '0');
        }
    }

    BigInt operator = (const BigInt& A) {
        this->numlist = A.numlist;
        return *this;
    }

    int size() {
        return (this->numlist).size();
    }

    friend BigInt operator + (BigInt A, BigInt B) {
        BigInt S, L;
        if (A.size() < B.size()) {
            L = B;
            S = A;
        }
        else {
            L = A;
            S = B;
        }

        int diff = L.size() - S.size();

        for (int i = S.size() - 1; i >= 0; --i) {
            L.numlist[i + diff] += S.numlist[i];
            if (L.numlist[i + diff] >= 10) {
                L.numlist[i + diff] -= 10;
                if (i + diff >= 1) {
                    L.numlist[i + diff - 1] += 1;
                }
                else {
                    L.numlist.insert(L.numlist.begin(), 1);
                }
            }
        }

        return L;
    }

    bool isMinusOne() {
        if (this->numlist[0] == -1) {
            return true;
        }
        else {
            return false;
        }
    }

    void printNum() {
        for (int i = 0; i < this->numlist.size(); ++i) {
            printf("%d", this->numlist[i]);
        }

        printf("\n");
    }
};

BigInt cache[10000];
*/

int cache[10000];

int dp(int N) {
    int& ret = cache[N];
    if (ret != -1) {
        return ret;
    }

    ret = (dp(N - 1) + (dp(N - 2) + dp(N - 2)))%(10007);

    return ret;
}

int main()
{
    scanf("%d", &n);
    
    fill(cache, cache + 10000, -1);

    cache[1] = 1;
    cache[2] = 3;
    

    int ans = dp(n);

    printf("%d", ans);

    return 0;
}

