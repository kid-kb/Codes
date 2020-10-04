#include <iostream>

using namespace std;

#define INF 1000

class Graph
{
	int V;
	int **adj;
	
	public:
	Graph(int v)
	{
		V = v;
		adj = new int*[V];
		for (int i=0; i<V; i++)
		{
			adj[i] = new int[V];
			for (int j=0; j<V; j++)
				adj[i][j] = INF;
		}
	}
	
	void makeGraph()
	{
		cout << "Enter the matrix" << endl;
		for (int i=0; i<V; i++)
		{
			for (int j=0; j<V; j++)
			{
				cin >> adj[i][j];
				if (adj[i][j]==0 && i!=j)
					adj[i][j] = INF;
			}
		}
	}	
	

	void addEdge(int u, int v, int w)
	{
		adj[u][v] = w;
	}
	
	void floydWarshall()
	{
		int dist[V][V], predecessor[V][V];
		
		// initializing
		for (int i=0; i<V; i++)
		{
			for(int j=0; j<V; j++)
			{
				dist[i][j]=adj[i][j];
				if (i==j || adj[i][j]==INF)
					predecessor[i][j] = -1;
				else
					predecessor[i][j] = i;
			}
		}
		
		for (int k=0; k<V; k++)
		{
			for (int i=0; i<V; i++)
			{
				for (int j=0; j<V; j++)
				{
					if (dist[i][k]+dist[k][j] < dist[i][j])
					{
						dist[i][j] = dist[i][k]+dist[k][j];
						predecessor[i][j] = predecessor[k][j];
					}
				}
			}
		}
		cout << "The distances are " << endl<<"  ";
		for (int i=0; i<V; i++)
			cout << i << "\t";
		cout << endl << "------------------------------------------" << endl;
		for(int i=0; i<V; i++)
		{
			cout <<i <<"|";
			for (int j=0; j<V; j++)
			{
				if (dist[i][j]==INF)
					cout << "$\t";
				else
					cout << dist[i][j]<< "\t";
			}
			cout << endl;
		}
		
		cout << "The predecessors are " << endl<<"  ";
		for (int i=0; i<V; i++)
			cout << i << "\t";
		cout << endl << "------------------------------------------" << endl;
		for(int i=0; i<V; i++)
		{
			cout <<i <<"|";
			for (int j=0; j<V; j++)
			{
				if (predecessor[i][j]==INF)
					cout << "$\t";
				else
					cout << predecessor[i][j]<< "\t";
			}
			cout << endl;
		}
		
	}
	
	void display()
	{
		for (int i=0; i<V; i++)
		{
			for (int j=0; j<V; j++)
			{
				if (adj[i][j]==INF)
					cout << "$ ";
				else
					cout << adj[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main()
{
	int v;
	cout<< "Enter no of vertices : ";
	cin >> v;
	Graph g1(v);
	g1.makeGraph();
	g1.floydWarshall();
	return 0;
}
