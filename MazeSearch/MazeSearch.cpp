// MazeSearch.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include<queue>

using namespace std;
bool gGrid[100][100] = { 0, };
bool bVisit[100][100] = { 0, };

int gCosts[100][100]{0,};
int n, m;

struct coordinate
{
	int x;
	int y;

	coordinate(int lx, int ly) : x(lx), y(ly) {}
};

bool IsValid(int x, int y)
{
	return gGrid[y][x] == true && bVisit[y][x] == false && x >= 0 && x < m&& y >= 0 && y < n;
}

int bfsRoute()
{
	std::queue<coordinate> q;
	coordinate root = coordinate(0, 0);
	coordinate dest = coordinate(m - 1, n - 1);
	coordinate c = root;

	q.push(root);
	while (q.empty() == false)
	{
		c = q.front();
		q.pop();

		if (c.x == m - 1 && c.y == n - 1)
			return gCosts[n-1][m-1];

		coordinate crd[4] = { {c.x, c.y - 1},{c.x, c.y + 1},{ c.x - 1, c.y},{ c.x + 1, c.y} };
		float dists[4];
		gCosts[0][0] = 1;

		for (int i = 0; i < 4; i++)
		{
			int ex, ey;

			ex = crd[i].x;
			ey = crd[i].y;
			
			if (IsValid(ex, ey) && gCosts[ey][ex] == 0)
			{
				q.push(crd[i]);
				gCosts[crd[i].y][crd[i].x] += gCosts[c.y][c.x] + 1;
			}
			else
				continue;

		}
	}

	return gCosts[n-1][m-1];
}


int main()
{

	char buffer[101][101];
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		cin >> buffer[i];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			auto b = buffer[i][j] - '0';
			gGrid[i][j] = b;
		}
	}

	cout << bfsRoute() << endl;

}