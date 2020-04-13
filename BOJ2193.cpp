#define _CRT_SECURE_NO_WARNINGS


#include <bits/stdc++.h>

using namespace std;

class BigInt {
private:
    int numsize;
    vector<int> numlist;

public:
    BigInt() {
        this->numsize = 1;
        this->numlist = { -1 };
    }

    BigInt(string s) {
        int t = s.size();
        for (int i = 0; i < t; ++i) {
            this->numlist.push_back(s[i] - '0');
        }
        this->numsize = t;
    }

    BigInt(int i) {
        this->numsize = 1;
        this->numlist = { i };
    }

    BigInt operator=(const BigInt A) {
        this->numlist = A.numlist;
        this->numsize = A.numsize;
        return *this;
    }

    friend BigInt operator+(const BigInt A, const BigInt B) {
        BigInt S, L;
        if (A.numsize < B.numsize) {
            S = A;
            L = B;
        }
        else {
            S = B;
            L = A;
        }

        int ssize = S.numsize;
        int lsize = L.numsize;
        int diff = lsize - ssize;

        for (int i = ssize - 1; i >= 0; --i) {
            L.numlist[i + diff] += S.numlist[i];
            if (L.numlist[i + diff] >= 10) {
                L.numlist[i + diff] -= 10;
                if (i + diff >= 1) {
                    L.numlist[i + diff -1] += 1;
                }
                else {
                    L.numlist.insert(L.numlist.begin(), 1);
                    L.numsize = L.numlist.size();
                }
            }
        }
        

        return L;

    }

    void printNum() {
        for (int i = 0; i < this->numsize; ++i) {
            printf("%d", this->numlist[i]);
        }
        printf("\n");
        return;
    }

    bool isMinusOne() {
        if (this->numlist[0] == -1) {
            return true;
        }
        else {
            return false;
        }
    }
};

BigInt cache[100][2];

BigInt dp(int N, int end) {
    BigInt& ret = cache[N][end];

    if (!ret.isMinusOne()) return ret;

    if (end) {
        ret = dp(N-1,0);
    }
    else {
        ret = dp(N-1,1) + dp(N-1,0);
    }

    return ret;
}

int main()
{
    int N=0;
    BigInt ans;

    cache[1][1] = BigInt(1);
    cache[1][0] = BigInt(0);
    cache[2][1] = BigInt(0);
    cache[2][0] = BigInt(1);

    scanf("%d", &N);

    ans = dp(N, 1) + dp(N, 0);

    ans.printNum();

    return 0;
}
