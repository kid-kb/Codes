#include <iostream>
#include <vector>
#include <queue>
#define MAX 100
using namespace std;

typedef pair<int,int> pii;
typedef vector<pii>::iterator itr;

class Graph;
class minPriorityQueue;
bool bellmanFord(int s, Graph g, int *d, int *parent);
void dijkstra(int s, Graph g, int *d, int *parent);

class minPriorityQueue
{
	pair<int,int> a[MAX];
	int size;
	
	public:
	minPriorityQueue()
	{
		size=0;
	}
	bool empty()
	{
		if (size==0)
			return true;
		return false;
	}
	int isPresent(int x)
	{
		for (int i=1; i<=size; i++)
			if (a[i].first==x)
				return i;
		return 0;
	}
	int getKey(int x)
	{
		for (int i=1; i<=size; i++)
			if (a[i].first==x)
				return a[i].second;
		return -1;
	}
	void add(int x, int k)
	{
		size++;
		a[size].first = x;
		a[size].second = INT_MAX;
		decreaseKey(size, k);
		
	}
	int max()
	{
		return a[1].first;
	}
	
	int extractMin(int *x)
	{
		int max = a[1].first;
		(*x) = a[1].second;
		a[1].first = a[size].first;
		a[1].second = a[size].second;
		size--;
		minHeapify(1);
		
		return max;
	}
	
	void minHeapify(int i)
	{
		if (i<=size/2)
		{
			int index = 2*i;
			if (2*i+1<=size && a[2*i+1].second<a[2*i].second)
				index = 2*i+1;
				
			if (a[index].second<a[i].second)
			{
				int t=a[i].first;
				a[i].first=a[index].first;
				a[index].first=t;
				
				t=a[i].second;
				a[i].second=a[index].second;
				a[index].second=t;
				
				minHeapify(index);
			}
		}
	}
	
	void decreaseKey(int x, int newKey)
	{
		int i=isPresent(x);
		a[i].second = newKey;
		while (i>1 && a[i/2].second > newKey)
		{
			int t=a[i].first;
			a[i].first=a[i/2].first;
			a[i/2].first=t;
			
			t=a[i].second;
			a[i].second=a[i/2].second;
			a[i/2].second=t;
			
			i = i/2;
		}
	}
	
	void display()
	{
		for (int i=1; i<=size; i++)
			cout << a[i].first << " ";
		cout << endl;
	}
};


class Graph
{
	
	
	
	public:
	int V;
	vector<pii> *adj;
	Graph(int V)
	{
		this->V = V;
		adj= new vector<pii> [V+1];
		
	}
	void addEdge(int u, int v, int w)
	{
		adj[u].push_back(make_pair(v,w));
	}
	
	void johnson()
	{
		for (int i=0; i<V; i++)
			adj[V].push_back(make_pair(i,0));
		V++;
			
		int h[V-1],parent[V+1];
		if (bellmanFord(V-1, *this, h, parent) == false)
			cout << " The graph has negative weight cycle" << endl;
			
		else
		{
			V--;
			// h already changed
			for (int u=0; u<V; u++)
				for (itr v=adj[u].begin(); v!=adj[u].end(); v++ )
					(*v).second = (*v).second + h[u] - h[(*v).first];
					
			int ans[V][V];
			
			for (int u=0; u<V; u++)
			{
				int d[V], parent[V];
				dijkstra(u, *this, d, parent);
				
				for (int v=0; v<V; v++)
					ans[u][v] = d[v] - h[u] + h[v];
			}
			
			cout << "Ans is " << endl;
			for (int i=0; i<V; i++)
			{
				for (int j=0; j<V; j++)
					cout << ans[i][j] << " ";
				cout << endl;	
			}
		}
	}
	
	void display()
	{
		cout << "The edges are" << endl;
		for (int i=0; i<V; i++)
		{
			cout << i << " : ";
			for (itr j=adj[i].begin(); j!=adj[i].end(); j++)
				cout<< (*j).first << "(" << (*j).second << ")\t";
			cout << endl;
		}
			
	}
};

void initializeSingleSource(int s,int V, int *d, int *parent)
{
	for (int i=0; i<V; i++)
	{
		d[i]=INT_MAX;
		parent[i]=-1;
	}
	d[s] = 0;
}

void relax (int u, int v, int w, int *d, int* parent)
{
	int sum;
	if (d[u]==INT_MAX)
		sum = INT_MAX;
	else
		sum = d[u]+w;
		
	if (d[v]>sum)
	{
		d[v] = sum;
		parent[v] = u;
	}
}

void relax(int u, int v, int w, int *d, int *parent, minPriorityQueue *q)
{
	int sum = INT_MAX;
	if (d[u]!=INT_MAX)
		sum = d[u]+w;
		
	if (d[v]>sum)
	{
		d[v]=sum;
		parent[v] = u;
		q->decreaseKey(v, sum);
	}
	
}

bool bellmanFord(int s, Graph g, int *d, int *parent)
{
	int V = g.V;
	initializeSingleSource(s,V,d,parent);
	for (int i=1; i<=V-1; i++)
		for (int u=0; u<V;u++)
			for (itr v=g.adj[u].begin(); v!=g.adj[u].end(); v++)
				relax(u,(*v).first, (*v).second, d, parent);
				
	// now a check
	for (int u=0; u<V;u++)
		for (itr v=g.adj[u].begin(); v!=g.adj[u].end(); v++)
			if (d[(*v).first]>d[u] + (*v).second)
				return false;
	return true;
}

void dijkstra(int s, Graph g, int *d, int *parent)
{
	int V = g.V;

	minPriorityQueue q;
	initializeSingleSource(s, V, d, parent);
	
	vector<bool> visited(V, false);
	
	for (int i=0; i<V; i++)
		q.add(i, INT_MAX);
	
	q.decreaseKey(s,0);
		
	while (!q.empty())
	{
		int k;
		int u = q.extractMin(&k);
	
		visited[u] = true;
		
		
		d[u]=k;
		
		for (itr v=g.adj[u].begin(); v!=g.adj[u].end(); v++)
		{
			int x = (*v).first;
			if (!visited[x])
				relax(u, x,  (*v).second, d, parent,&q);
		}
		
	}
}



int main()
{
	int v;
	
	Graph g1(5);
	g1.addEdge(0,1,3);
	g1.addEdge(0,2,8);
	g1.addEdge(0,4,-4);
	g1.addEdge(1,3,1);
	g1.addEdge(1,4,7);
	g1.addEdge(2,1,4);
	g1.addEdge(3,0,2);
	g1.addEdge(3,2,-5);
	g1.addEdge(4,3,6);
	//g1.display();
	g1.johnson();
	return 0;
}


