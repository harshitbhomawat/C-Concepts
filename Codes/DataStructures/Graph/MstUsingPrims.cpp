#include<bits/stdc++.h>
using namespace std;

struct Edge
{
int v,u,w;
Edge(int _u, int _v, int _w):u(_u), v(_v), w(_w)
{
}
};

class MST
{
	int n,e;
	vector<int> parent;
	vector<int> rank;
	vector<vector<pair<int,int> > > tempGraph, Graph;
	public:
	void Init()
	{
		cout<<"Enter no. of vecrtices, edges: "<<endl;
		cin>>n;
		cin>>e;
		for(int i=0;i<n;i++)
		{
			parent.push_back(i);
			rank.push_back(0);
			vector<pair<int,int> > v;
			tempGraph.push_back(v);
			Graph.push_back(v);
		}
		cout<<"Enter edges : u v w"<<endl;
		for(int i=0;i<e;i++)
		{
			int u,v,w;
			cin>>u>>v>>w;
			pair<int,int> p;
			p.first = v;
			p.second = w;
			tempGraph[u].push_back(p);
			p.first = u;
			tempGraph[v].push_back(p);
		}
		
	}
	static bool cmp(Edge e1,Edge e2)
	{
		return e1.w < e2.w;
	}
	int find(int u)
	{
		if(parent[u] == u)
		{
			return u;
		}
		return find(parent[u]);
	}
	
	void Union(int u, int v)
	{
		u = find(u);
		v = find(v);
		if(rank[u]<rank[v])
		{
			parent[u] = v;
		}
		else if(rank[u]>rank[v])
		{
			parent[v] = u;
		}
		else
		{
			parent[v] = u;
			rank[u]+=rank[v];
		}
	}
	
	void Kruskal()
	{
		sort(Edges.begin(),Edges.end(),cmp);
		
		for(int i=0;i<Edges.size();i++)
		{
			Edge edge = Edges[i];
			if(find(edge.u) == find(edge.v))
			{
				continue;
			}
			pair<int,int> pr;
			pr.first = edge.v;
			pr.second = edge.w;
			tempGraph[edge.u].push_back(pr);
			pr.first = edge.u;
			pr.second = edge.w;
			tempGraph[edge.v].push_back(pr);
			Union(edge.u,edge.v);
		}
	}
	
	void Print()
	{
		for(int i=0;i<n;i++)
		{
			cout<<i<<": ";
			for(int j=0;j<Graph[i].size();j++)
			{
				cout<<Graph[i][j].first<<"|"<<Graph[i][j].second<<" ,";
			}
			cout<<endl;
		}
	}
};

int main()
{
	MST mst;
	mst.Init();
	mst.Print();
	mst.Kruskal();
	mst.Print();
}
