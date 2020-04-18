#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

struct cmp {
    bool operator()(long long t, long long u) {
        return t > u;
    }
};


vector<long long> input;
int N, T;

long long calc(priority_queue<long long, vector<long long>, cmp> pq) {
    long long ans = 0;
    bool chk = true;
    
    while (pq.size()>=2) {
        long long t1 = pq.top();
        pq.pop();
        long long t2 = pq.top();
        pq.pop();
        pq.emplace(t1 + t2);
        ans += (t1 + t2);
    }

    return ans;
}

int main()
{
    scanf("%d", &T);
    for (int i = 0; i < T; ++i) {
        scanf("%d", &N);

        input.clear();

        for (int j = 0; j < N; ++j) {
            int t = 0;
            scanf("%lld", &t);
            input.push_back(t);
            
        }

        priority_queue<long long, vector<long long>, cmp> pq(input.begin(), input.begin()+N);

        long long ans = calc(pq);

        printf("%lld\n", ans);
    }

    return 0;
}

/*
Huffman coding

TAMREF's solution

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

priority_queue<ll,vector<ll>,greater<ll>> pq;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t, n;
    ll x,y,ans;
    for(cin>>t;t--;){
        ans = 0;
        for(cin>>n;n--;){
            cin>>x;
            pq.push(x);
        }
        while(pq.size() > 1){
            x = pq.top(); pq.pop();
            y = pq.top(); pq.pop();
            ans += (x+y);
            pq.push(x+y);
        }
        pq.pop();
        cout<<ans<<'\n';
    }
}
*/