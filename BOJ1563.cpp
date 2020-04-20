#define _CRT_SECURE_NO_WARNINGS


#include <bits/stdc++.h>

using namespace std;

int c[1010][6];
// L0A0, L1A0, L0A1, L1A1, L0A2, L1A2
// L0A0 = L0A0 + L0A1 + L0A2
// L1A0 = L0A0 + L1A0 + L1A1 + L1A2 + L0A1+L0A2
// L0A1 = L0A0
// L1A1 = L1A0
// L0A2 = L0A1
// L1A2 = L1A1

int M = 1000000;
int N;
void calc() {
    for (int i = 2; i <= 1000; ++i) {
        c[i][0] = (c[i - 1][0] + c[i - 1][2] + c[i - 1][4]) % M;
        c[i][1] = (c[i - 1][0] + c[i - 1][1] + c[i - 1][2] + c[i - 1][3] + c[i - 1][4]+ c[i - 1][5]) % M;
        c[i][2] = c[i - 1][0]%M;
        c[i][3] = c[i - 1][1]%M;
        c[i][4] = c[i - 1][2]%M;
        c[i][5] = c[i - 1][3]%M;
    }
}

void ans(int n) {
    int t = 0;
    for (int i = 0; i < 6; ++i) {
        t += c[n][i] % M;
    }

    t = t % M;
    printf("%d", t);

}

int main()
{
    scanf("%d", &N);
    memset(c, 0, sizeof(c));

    c[1][0] = 1;
    c[1][1] = 1;
    c[1][2] = 1;
    c[1][3] = 0;
    c[1][4] = 0;
    c[1][5] = 0;



    if (N == 0) {
        printf("0");
    }
    else {
        calc();
        ans(N);
    }

    return 0;

}

/* Nada's solution. Using sliding window.
#include <stdio.h>

int main(){
    long long n, a[3][2]={0}, tal[3][2], s=0;
    scanf("%lld", &n);
    a[0][0]=1;
    a[1][0]=1;
    a[0][1]=1;
    for(int i=1; i<n ; i++){
        tal[0][0]=(a[2][0]+a[1][0]+a[0][0])%1000000;
        tal[0][1]=(a[0][0]+a[0][1]+a[1][0]+a[1][1]+a[2][0]+a[2][1])%1000000;
        tal[1][0]=a[0][0];
        tal[1][1]=a[0][1];
        tal[2][0]=a[1][0];
        tal[2][1]=a[1][1];
        for(int i=0; i<3; i++)
            for(int j=0; j<2; j++)
                a[i][j]=tal[i][j];
    }
    for(int i=0; i<3; i++)
        for(int j=0; j<2; j++)
            s+=a[i][j];
    printf("%lld", s%1000000);
    return 0;
}

*/