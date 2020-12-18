#include <bits/stdc++.h>
using namespace std;
const int mx = 1 << 18 | 5;

namespace SA{ //special thanks to cubelover
    using namespace std;
    const int mx = 1 << 18 | 5;
    const int n_char = 128;

    int T[mx]; //tmp counting array for radix sort
    void radix_sort(const int *A, const int *V, int *F, int n, int m){
        fill(T, T+m+1, 0);
        for(int i = 0; i < n; i++) ++T[ V[A[i]] ];
        for(int x = 1; x <= m; x++) T[x] += T[x-1];
        for(int i = n; i--;) F[--T[V[A[i]]]] = A[i];
    }

    int G[mx]; //group number
    int tG[mx]; //tmp group number
    // arr[i] : 0 - based starting index of lexicographically i-th suffix
    void suffix_array(const char *S, int *arr, int n){
        for(int i = 0; i < n; i++){
            G[i] = S[i]; //first priority : char value
            tG[i] = i; //second priority : starting index
        }
        radix_sort(tG, G, arr, n, n_char); //preprocess : sort by character value
        for(int i = 1, k = 1; i < n && k < n; i <<= 1){
            for(k = 0; k < i; k++) tG[k] = k - i + n; //second priority : short strings are needn't to be compared
            for(int j = 0; j < n; j++){
                if(arr[j] >= i){
                    tG[k++] = arr[j] - i; //second priority : x + i - th character's priority
                }
            }
            radix_sort(tG, G, arr, n, n);
            tG[arr[0]] = k = 1;
            for(int j = 1; j < n; j++){
                if(G[ arr[j] ] != G[ arr[j-1] ] || G[arr[j] + i] != G[arr[j-1] + i]) ++k;
                tG[arr[j]] = k;
            }
            for(int j = 0; j < n; j++) G[j] = tG[j];
        }
    }

    int *R = tG; //to save memory
    void lcp_array(const int *sfx, const char *S, int *L, int n){
        for(int i = 0; i < n; i++) R[ sfx[i] ] = i;
        for(int i = 0, j = 0; i < n; i++){
            if( R[i] ){ // to avoid making lcp for the least string lexicographically
                while( S[i + j] == S[sfx[R[i] - 1] + j]) ++j;
                L[R[i]] = j;
            }
            if(j) --j; //Fact : if lcp(i,i-1) >= 1, lcp(i+1,i) >= lcp(i,i-1) - 1. Which guarantees O(n) complexity.
        }
    }
}

char S[mx];
int len, lcp[mx], sfx[mx];
int main(){
    scanf("%d\n",&len);
    scanf("%s",S);
    SA::suffix_array(S, sfx, len);
    SA::lcp_array(sfx, S, lcp, len);
    printf("%d\n",*max_element(lcp+1,lcp+len));
}
