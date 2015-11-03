//+-----------------------------------------------------------------------------
//
//  File:       1915.cpp
//
//  Synopsis:   POJ 1915, simple BFS
//
//  Author:     Qirong Ma, 11/02/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

struct pos{
	int x;
	int y;
	int steps;
	pos():x(0),y(0),steps(0){}
	pos(int _x,int _y,int _s):x(_x),y(_y),steps(_s){}
};

bool visited[310][310];

int n;
int xstart,ystart,xend,yend;
int xi[8]={-2,-1,1,2,2,1,-1,-2};
int yi[8]={1,2,2,1,-1,-2,-2,-1};

int bfs(){
	memset(visited,0,sizeof(visited));
	queue<pos> q;
	q.push(pos(xstart,ystart,0));
	visited[xstart][ystart]=true;
	while(!q.empty()){
		pos p = q.front();
		q.pop();
		if (p.x==xend&&p.y==yend)
			return p.steps;
		for (int i=0;i<8;i++){
			if(p.x+xi[i]>=0&&p.x+xi[i]<n&&p.y+yi[i]>=0&&p.y+yi[i]<n
				&& !visited[p.x+xi[i]][p.y+yi[i]]){
				q.push(pos(p.x+xi[i],p.y+yi[i],p.steps+1));
				visited[p.x+xi[i]][p.y+yi[i]]=true;
			}
		}
	}
	return -1;
}

int main(){
	// freopen("in.txt","r",stdin);
	int ncase;
	scanf("%d",&ncase);
	while(ncase--){
		scanf("%d%d%d%d%d",&n,&xstart,&ystart,&xend,&yend);
		printf("%d\n",bfs());
	}
}
