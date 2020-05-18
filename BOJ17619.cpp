#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

struct disjointSet {
    vector<int> parent;
    vector<int> rank;
    disjointSet() {
        parent.resize(100001);
        //rank.resize(100001, 1);
        for (int i = 0; i < 100001; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] == u) return u;

        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) return;

        if (u < v) swap(u, v);
        parent[v] = u;
    }
};

bool cmp(const pii& a, const pii& b)
{
    return a.first < b.first;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    int N, Q;
    cin >> N >> Q;

    disjointSet DJS;
    vector<pii> input;

    map<pii, int> logmap;
    int cnt = 1;

    input.push_back({ -1,-1 });
    for (int i = 0; i < N; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        input.push_back({ a,b });
        logmap[{a, b}] = cnt;
        ++cnt;
    }

    sort(input.begin(), input.end(), cmp);

    for (int i = 1; i <= N; ++i) {
        pii pivot = input[i];
        for (int j = i + 1; j <= N; ++j) {
            if (pivot.second >= input[j].first) {
                DJS.merge(logmap[pivot], logmap[input[j]]);
            }
            else {
                break;
            }
        }
    }

    while (Q--) {
        int s, e;
        cin >> s >> e;
        s = DJS.find(s);
        e = DJS.find(e);
        if (s != e) {
            printf("0\n");
        }
        else {
            printf("1\n");
        }
    }

    return 0;
}

/*
//TAMREF's solution
#include <bits/stdc++.h>
#define va first
#define vb second
#define lb lower_bound
#define ub upper_bound
#define bs binary_search
#define pp push_back
#define ep emplace_back
#define all(v) (v).begin(),(v).end()
#define szz(v) ((int)(v).size())
#define bi_pc __builtin_popcount
#define bi_pcll __builtin_popcountll
#define bi_tz __builtin_ctz
#define bi_tzll __builtin_ctzll
#define fio ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
using ll = long long; using lf = long double;
using pii = pair<int,int>; using ppi = pair<int,pii>;
using pll = pair<ll,ll>; using pff = pair<lf,lf>;
using ti = tuple<int,int,int>;
const lf PI = 3.14159265358979323846264338L;
template <typename T>
inline T umax(T& u, T v){return u = max(u, v);}
template <typename T>
inline T umin(T& u, T v){return u = min(u, v);}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, q;
int r[100005], gnt;
struct l{
    int s, e, i;
    bool operator< (l z){
        return s < z.s;
    }
} a[100005];
int main(){
    fio;
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> a[i].s >> a[i].e >> a[i].i;
        a[i].i = i;
    }
    sort(a + 1, a + n + 1);
    int rgt = 0;
    for(int i = 1; i <= n; i++){
        if(a[i].s > rgt){
            r[a[i].i] = ++gnt;
            rgt = a[i].e;
        }else{
            r[a[i].i] = gnt;
            rgt = max(a[i].e, rgt);
        }
    }
    for(int i, j; q--;){
        cin >> i >> j;
        cout << (r[i] == r[j]) << '\n';
    }
}
*/