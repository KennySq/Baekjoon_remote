#include <iostream>
#include<queue>
using namespace std;

bool bVisit[101][101];
int gMap[101][101] = { 0, };
queue<int> nodes;
int n, edge;
int hcount = 0;

int bfs()
{
	nodes.push(1);

	while (nodes.empty() == false)
	{
		int node = nodes.front();
		int index = node - 1;
		nodes.pop();

		for (int i = 0; i < edge; i++)
		{
			if (bVisit[index][i] == true)
				continue;

			if (gMap[index][i] == 1)
			{
				nodes.push(i + 1);
				bVisit[index][i] = true;
				bVisit[i][index] = true;

			}

		}


	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (bVisit[i][j] == true && i != 0)
				hcount++;
		}
	}

	return hcount;
}

int main()
{
	cin >> n >> edge;

	for (int i = 0; i < edge; i++)
	{
		int a, b;

		cin >> a >> b;

		gMap[a - 1][b - 1] = 1;
		gMap[b - 1][a - 1] = 1;
	}
	hcount = bfs() / 2;
	cout << hcount;
}