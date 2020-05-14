#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
int N, K, Q;

vector<ll> parent2(ll here, vector<ll>& plist) {
    plist.push_back(here);
    if (here == 1) {
        return plist;
    }
    else {
        return parent2(here / 2, plist);
    }
}

vector<ll> parentK(ll here, vector<ll>& plist) {
    plist.push_back(here);
    if (here == 1) {
        return plist;
    }
    if ((here - 1) % K == 0) {
        return parentK((here - 1) / K, plist);
    }
    else if ((here) % K == 0) {
        return parentK((here) / K, plist);
    }
    else{
        return parentK((here / K) + 1,  plist);
    }
}



int main()
{
    scanf("%d %d %d", &N, &K, &Q);

    for (int i = 0; i < Q; ++i) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        vector<ll> ap;
        vector<ll> bp;
        if (K == 1) {
            if (a > b) {
                printf("%lld\n", a - b);
            }
            else {
                printf("%lld\n", b - a);
            }
            
        }
        else if (K == 2) {
            vector<ll>aparent = parent2(a,  ap);
            vector<ll>bparent = parent2(b,  bp);
            for (int j = 0; j < bparent.size(); ++j) {
                vector<ll>::iterator iter1 = find(aparent.begin(), aparent.end(), bparent[j]);
                if (iter1 != aparent.end()) {
                    ll lca = aparent[iter1 - aparent.begin()];
                    vector<ll>::iterator iter2 = find(bparent.begin(), bparent.end(), lca);
                    printf("%d\n", (iter1 - aparent.begin()) + (iter2 - bparent.begin()));
                    break;
                }
            }
        }
        else if (K>2){
            vector<ll>aparent = parentK(a,  ap);
            vector<ll>bparent = parentK(b, bp);
            for (int j = 0; j < bparent.size(); ++j) {
                vector<ll>::iterator iter1 = find(aparent.begin(), aparent.end(), bparent[j]);
                if (iter1 != aparent.end()) {
                    ll lca = *iter1;
                    vector<ll>::iterator iter2 = find(bparent.begin(), bparent.end(), lca);
                    printf("%d\n", (iter1 - aparent.begin()) + (iter2 - bparent.begin()));
                    break;
                }
            }
        }
    }

    return 0;
}
