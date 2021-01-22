

#include <iostream>
#include<queue>

using namespace std;

constexpr int MAX_VERTICES = 1001;


int connections[MAX_VERTICES][MAX_VERTICES] = { -1, };
bool bVisit[MAX_VERTICES];
queue<int> q;
int n, m, v;

void dfs(int vertex)
{
	cout << vertex << " ";
	bVisit[vertex] = true;

	for (int i = 1; i <= n; i++)
	{
		if (connections[vertex][i] && bVisit[i] == false)
		{
			dfs(i);
		}
	}
}

void bfs(int vertex)
{
	bVisit[vertex] = true;
	q.push(vertex);

	while (q.empty() == false)
	{
		vertex = q.front();
		q.pop();

		cout << vertex << " ";

		for (int i = 1; i <= n; i++)
		{
			if (connections[vertex][i] && bVisit[i] == false)
			{
				q.push(i);
				bVisit[i] = true;
			}
		}
	}
}

int main()
{
	cin >> n >> m >> v;

	for (int i = 0; i < m; i++)
	{
		int a,b;
		cin >> a >> b;
		connections[a][b] = true;
		connections[b][a] = true;
	}

	dfs(v);
	cout << endl;
	memset(bVisit, false, sizeof(bool) * 1001);
	bfs(v);
	

//	int N, M, V;
//	int arg[10001][2];
//
//	cin >> N >> M >> V;
//
//	for (int i = 0; i < M; i++)
//	{
//		cin >> arg[i][0] >> arg[i][1];
//	}
//
//
//
////	NewDFS(N, M, V, arg, cout);
//	cout << std::endl;
//
////	BFS(N, M, V, arg, cout);

	return 0;
}