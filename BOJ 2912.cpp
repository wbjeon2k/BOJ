/*

<color,index> sort -> use upper&lower bound
-> get the number of colored hat in O(logN)

*/
#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int n, c;
int segtree[1210000];
int color[310000];
pair<int,int> sorted[300300];

void segtreeinit(int left, int right, int node) {
    if (left == right) {
        segtree[node] = color[left];
        return;
    }

    int mid = (left + right) / 2;
    segtreeinit(left, mid, node * 2);
    segtreeinit(mid + 1, right, node * 2 + 1);

    int candidiate = segtree[(node * 2)];
    int t = upper_bound(sorted, sorted + n, make_pair(candidiate, right)) - lower_bound(sorted, sorted +n, make_pair(candidiate,left));
    if (t > (right - left + 1)/2) {
        segtree[node] = candidiate;
        return;
    }

    candidiate = segtree[(2*node) +1];
    t = upper_bound(sorted, sorted + n, make_pair(candidiate, right)) - lower_bound(sorted, sorted + n, make_pair(candidiate, left));
    if (t > (right - left + 1)/2) {
        segtree[node] = candidiate;
        return;
    }

    segtree[node] = -1;

}

int query(int left, int right, int node, int nodeLeft, int nodeRight) {

    //printf("%d %d %d %d %d", left, right, node, nodeLeft, nodeRight);
    if (left > nodeRight || right < nodeLeft) {
        return -1;
    }
    if (left <= nodeLeft && right >= nodeRight) {
        int t = upper_bound(sorted, sorted + n, make_pair(segtree[node], right)) - lower_bound(sorted, sorted + n, make_pair(segtree[node], left));
        if (t > (right - left + 1)/2) {
            return segtree[node];
        }
        else {
            return -1;
        }
    }

    int mid = (nodeLeft + nodeRight) / 2;
    int leftTree = query(left, right, (node * 2), nodeLeft, mid);
    if (leftTree != -1) {
        return leftTree;
    }

    int rightTree = query(left, right, (node * 2) + 1, mid +1, nodeRight);
    if (rightTree != -1) {
        return rightTree;
    }

    return -1;
}

int main() {

    scanf("%d %d", &n, &c);
    for (int i = 1; i <= n; ++i) {
        int t = 0;
        scanf("%d", &t);

        color[i] = t;
        sorted[i-1] = { t,i };
    }

    sort(sorted, sorted + n);
    segtreeinit(1, n, 1);
    
    int a;
    scanf("%d", &a);
    for (int i = 0; i < a; ++i) {
        int l, r, ans;
        scanf("%d %d", &l, &r);

        ans = query(l, r, 1, 1, n);
        if (ans == -1) {
            printf("no\n");
        }
        else {
            printf("yes %d\n", ans);
        }
    }

    return 0;
}

/*
//TAMREF's solution

#include <bits/stdc++.h>
using namespace std;

const int mxq = 20, mxc = 10005, mxn = 300005, mxrnd = 32768;

vector<int> L[mxc];
int n, c, q;

random_device rd;
mt19937 gen(rd());
int rndarr[mxrnd];
int col[mxn];

void input(){
    cin >> n >> c;
    uniform_int_distribution<int> dist(1,n);
    for(int i = 0; i < mxrnd; i++){
        rndarr[i] = dist(gen);
    }
    for(int i = 1; i <= n; i++){
        cin >> col[i];
        L[col[i]].push_back(i);
    }
}

bool gnum(int a, int b, int v){
    return upper_bound(L[v].begin(),L[v].end(),b) - lower_bound(L[v].begin(),L[v].end(),a) > (b-a+1)/2;
}
void query(){
    cin >> q;
    int qtr = 0;
    for(int a, b; q--; ){
        cin >> a >> b;
        for(int j = 0; j < mxq; j++){
            int rv = a + (rndarr[qtr++])%(b-a+1);
            if(gnum(a,b,col[rv])){
                cout << "yes " << col[rv] << '\n';
                goto SUCC;
            }
            qtr &= mxrnd - 1;
        }
        cout << "no" << '\n';
        SUCC:
        continue;
    }
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    input();
    query();
}

*/