//+---------------------------------------------------------------------
//
//  File:       1151.cpp
//
//  Synopsis:   Atlantis, interval tree
//              
//  Author:     Qirong Ma, 08/22/2016
//
//----------------------------------------------------------------------
#include <cstdio>
#include <algorithm>
using namespace std;

struct CNode {
    int L, R;
    CNode *pLeft, *pRight;
    double Len;
    int Covers;
};
CNode Tree[1000];
double y[210];

struct CLine {
    double x, y1, y2;
    bool bLeft;
} lines[210];

int nNodeCount = 0;

bool operator<(const CLine &l1, const CLine &l2) {
    return l1.x < l2.x;
}

template <class F, class T>
F bin_search(F s, F e, T val) {
    F L = s;
    F R = e-1;
    while (L <= R) {
        F mid = L + (R-L) / 2;
        if (!(*mid < val || val < *mid))
            return mid;
        else if (val < *mid)
            R = mid-1;
        else
            L = mid+1;
    }
    return e;
}

int Mid(CNode* pRoot) {
    return (pRoot->L + pRoot->R) >> 1;
}

void Insert(CNode *pRoot, int L, int R) {
    if (pRoot->L == L && pRoot->R == R) {
        pRoot->Len = y[R+1] - y[L];
        pRoot->Covers++;
        return;
    }
    if (R <= Mid(pRoot))
        Insert(pRoot->pLeft, L, R);
    else if (L >= Mid(pRoot)+1)
        Insert(pRoot->pRight, L, R);
    else {
        Insert(pRoot->pLeft, L, Mid(pRoot));
        Insert(pRoot->pRight, Mid(pRoot)+1, R);
    }
    if (pRoot->Covers == 0) {
        pRoot->Len = pRoot->pLeft->Len + pRoot->pRight->Len;
    }
}

void Delete(CNode *pRoot, int L, int R) {
    if (pRoot->L == L && pRoot->R == R) {
        pRoot->Covers--;
        if (pRoot->Covers == 0) {
            if (pRoot->L == pRoot->R)
                pRoot->Len = 0;
            else
                pRoot->Len = pRoot->pLeft->Len + pRoot->pRight->Len;
        }
        return;
    }
    if (R <= Mid(pRoot))
        Delete(pRoot->pLeft, L, R);
    else if (L >= Mid(pRoot)+1)
        Delete(pRoot->pRight, L, R);
    else {
        Delete(pRoot->pLeft, L, Mid(pRoot));
        Delete(pRoot->pRight, Mid(pRoot)+1, R);
    }
    if (pRoot->Covers == 0) {
        pRoot->Len = pRoot->pLeft->Len + pRoot->pRight->Len;
    }
}

void BuildTree(CNode *pRoot, int L, int R) {
    pRoot->L = L;
    pRoot->R = R;
    pRoot->Covers = 0;
    pRoot->Len = 0;
    if (L == R)
        return;
    nNodeCount++;
    pRoot->pLeft = Tree + nNodeCount;
    nNodeCount++;
    pRoot->pRight = Tree + nNodeCount;
    BuildTree(pRoot->pLeft, L, (L+R)/2);
    BuildTree(pRoot->pRight, (L+R)/2+1, R);
}

int main() {
    int n;  int i, j, k;  double x1, y1, x2, y2;  int yc, lc;
    int nCount = 0;
    int t = 0;
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;
        t++;  yc = lc = 0;
        for (i = 0; i < n; i++) {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            y[yc++] = y1;  y[yc++] = y2;
            lines[lc].x = x1; lines[lc].y1 = y1;
            lines[lc].y2 = y2;
            lines[lc].bLeft = true;
            lc++;
            lines[lc].x = x2; lines[lc].y1 = y1;
            lines[lc].y2 = y2;
            lines[lc].bLeft = false;
            lc++;
        }

        sort(y, y+yc);
        yc = unique(y, y+yc) - y;
        nNodeCount = 0;
        BuildTree(Tree, 0, yc-1-1);

        sort(lines, lines+lc);
        double Area = 0;
        for (i = 0; i < lc-1; i++) {
            int L = bin_search(y, y+yc, lines[i].y1) - y;
            int R = bin_search(y, y+yc, lines[i].y2) - y;
            if (lines[i].bLeft)
                Insert(Tree, L, R-1);
            else
                Delete(Tree, L, R-1);
            Area += Tree[0].Len * (lines[i+1].x - lines[i].x);
        }
        printf("Test case #%d\n", t);
        printf("Total explored area: %.2f\n", Area);
        printf("\n");
    }
    return 0;
}
