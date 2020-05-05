#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>


int N;

int main()
{
    scanf("%d", &N);
 

    stack<pii> s;
    ll ans = 0;

    
    for (int i = 0; i < N; ++i) {
        int input = 0;
        scanf("%d", &input);

        while (!s.empty() && input > s.top().first) {
            ans += s.top().second;
            s.pop();
        }

        if (s.empty()) {
            s.push({ input,1 });
        }
        else {
            if (input == s.top().first) {
                pii tmp = s.top();
                s.pop();

                if (!s.empty()) {
                    ++ans;
                }

                ans += tmp.second;
                tmp.second++;

                s.push(tmp);
            }

            if (input < s.top().first) {
                s.push({ input,1 });
                ++ans;
            }
        }
        
    }

    printf("%lld", ans);

    return 0;
}
