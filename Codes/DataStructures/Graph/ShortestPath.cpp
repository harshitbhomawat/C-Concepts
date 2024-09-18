#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,e;
	cout<<"Enter no. of  vertices and Edges"<<endl;
	cin>>n>>e;
	vector<vector<pair<int,int> > > graph(n,vector<pair<int,int> >());
	for(int i=0;i<e;i++)
	{
		int x,y,w;
		cout<<"Enter a edge: "<<endl;
		cin>>x>>y>>w;
		pair<int,int> p;
		p.first = y;
		p.second = w;
		graph[x].push_back(p);
		p.first = x;
		graph[y].push_back(p);
	}
	vector<int> vis(n,0), dist(n,INT_MAX);
	dist[0] = 0;
	
	bool found = true;
	while(found)
	{
		found = false;
		int ver = -1,mindist = INT_MAX;
		for(int i=0;i<dist.size();i++)
		{
			if(!vis[i] and dist[i]<mindist)
			{
				found = true;
				mindist = dist[i];
				ver = i;
			}
		}
		if(found)
			vis[ver] = true;
		else
			break;
		for(int i=0;i<graph[ver].size();i++)
		{
			int nbr = graph[ver][i].first;
			if(dist[nbr] > dist[ver] + graph[ver][i].second)
			{
				dist[nbr] = dist[ver] + graph[ver][i].second;
			}
		}
	}
	
	for(int i=0;i<n;i++)
	{
		cout<<"i: "<<i<<" dist:"<<dist[i]<<endl;
	}
}
