#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;


vector<int> inorder, preorder;

void postorder(int prs, int pre, int ins, int ine) {
    //printf("%d %d %d %d\n", prs, pre, ins, ine);

    if (prs == pre || ins == ine) {
        printf("%d ", preorder[prs]);
        return;
    }

    if (prs > pre || ins > ine) {
        return;
    }

    int root = preorder[prs];

    int L = find(inorder.begin() + ins, inorder.begin() + ine, root) - inorder.begin() - ins;

    

    postorder(prs+1, prs + L, ins, ins + L - 1);
    postorder(prs + L +1 , pre, ins + L +1, ine);
    
    printf("%d ", root);
    return;
}

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        int t = 0;
        scanf("%d", &t);

        vector<int> inpre, inin;

        for (int i = 0; i < t; ++i) {
            int a;
            scanf("%d", &a);
            inpre.push_back(a);
        }
        for (int i = 0; i < t; ++i) {
            int b;
            scanf("%d", &b);
            inin.push_back(b);
        }

        inorder = inin;
        preorder = inpre;

        postorder(0, t - 1, 0, t - 1);

        printf("\n");
    }

    

    return 0;
}