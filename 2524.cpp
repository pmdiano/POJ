//+-----------------------------------------------------------------------------
//
//  File:       2524.cpp
//
//  Synopsis:   POJ 2524, Ubiquitous Religions. Basic union find.
//
//  Author:     Qirong Ma, 10/26/2015
//
//------------------------------------------------------------------------------
#include <cstdio>

int n;
int parent[50005];

inline int find(int i) {
	if (parent[i] == i)
		return i;
	parent[i] = find(parent[i]);
	return parent[i];
}

void init() {
	for (int i = 1; i <= n; i++)
		parent[i] = i;
}

int main() {
	int m, i, j, pi, pj, ans, ncase = 1;

	while (true) {
		scanf("%d %d", &n, &m);
		if (!n && !m)
			break;

		init();
		ans = n;
		while (m--) {
			scanf("%d %d", &i, &j);
			pi = find(i);
			pj = find(j);
			if (pi != pj) {
				ans--;
				parent[pj] = pi;
			}
		}

		printf("Case %d: %d\n", ncase++, ans);
	}

	return 0;
}
