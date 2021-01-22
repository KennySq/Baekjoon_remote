#include <iostream>
#include<algorithm>
#include<queue>

bool gMap[50][50] = { 0, };
int gNumber[50][50] = { 0, };
int gHouseCounts[1024];

int s = 0;
int gHouseNumber = 1;

using namespace std;

struct coordinate
{
	int x;
	int y;

	coordinate(int ex, int ey) : x(ex), y(ey) {}
};

bool IsValid(int x, int y)
{
	return gMap[y][x] == true && gNumber[y][x] == 0 && x >= 0 && x < s&& y >= 0 && y < s;
}

coordinate findEntry()
{
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			if (gNumber[i][j] == 0 && gMap[i][j] == true)
				return coordinate(j, i);
		}
	}

	return coordinate(-1, -1);
}

bool bfs(coordinate entry)
{
	queue<coordinate> q;
	q.push(entry);
	int houseCount = 0;
	gNumber[entry.y][entry.x] = gHouseNumber;
	++houseCount;
	while (q.empty() == false)
	{
		coordinate c = q.front();
		q.pop();

		coordinate crd[4] = { {c.x - 1 , c.y}, {c.x + 1, c.y}, {c.x, c.y - 1}, {c.x,c.y + 1} };

		for (int i = 0; i < 4; i++)
		{
			int ex = crd[i].x;
			int ey = crd[i].y;

			if (IsValid(ex, ey))
			{
				gNumber[ey][ex] = gHouseNumber;
				++houseCount;

				q.push(crd[i]);
			}
		}
	}

	gHouseCounts[gHouseNumber - 1] = houseCount;

	return true;
}

void numbering()
{
	while (true)
	{
		coordinate entry = findEntry();

		if (IsValid(entry.x, entry.y) == false)
			break;

		bool done = bfs(entry);
		if (done == true)
			gHouseNumber++;
	}
}

int main()
{
	char buffer[101][101];

	cin >> s;

	for (int i = 0; i < s; i++)
	{
		cin >> buffer[i];
	}

	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			auto b = buffer[i][j] - '0';
			gMap[i][j] = b;
		}
	}

	numbering();

	cout << gHouseNumber - 1 << endl;
	
	if(gHouseNumber >= 0)
		sort(gHouseCounts, &gHouseCounts[gHouseNumber - 1]);
	
	for (int i =0; i < gHouseNumber - 1; i++)
	{
		cout << gHouseCounts[i] << endl;
	}

	return 0;
}