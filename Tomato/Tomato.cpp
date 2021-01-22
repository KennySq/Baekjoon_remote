// Tomato.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include<queue>

using namespace std;

int n, m;
int gBox[1000][1000] = { 0, };
int gDays = 0;

struct coordinate
{
    int x;
    int y;

    int day = 0;

    coordinate(int ex, int ey) : x(ex), y(ey) {}
    coordinate(int ex, int ey, int dy) : x(ex), y(ey), day(dy) {}
};

bool IsValid(int x, int y)
{
    return gBox[y][x] == 0 && x >= 0 && x < m&& y >= 0 && y < n;
}

void waiting()
{

    queue<coordinate> q;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (gBox[i][j] == 1)
                q.push(coordinate(j, i, gDays));
        }
    }

    while (q.empty() == false)
    {
        coordinate c = q.front();
        q.pop();

        coordinate crd[4] = { {c.x - 1 ,c.y}, {c.x + 1, c.y}, {c.x, c.y - 1}, {c.x, c.y + 1} };
        

        for (int i = 0; i < 4; i++)
        {
            int ex, ey;

            ex = crd[i].x;
            ey = crd[i].y;

            if (IsValid(crd[i].x, crd[i].y))
            {
                crd[i].day += c.day + 1;
                q.push(crd[i]);
                gBox[ey][ex] = crd[i].day;
            }
        }
        gDays = c.day;

        
    }


}

void check()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (gBox[i][j] == 0)
                gDays = -1;
        }
    }
}


int main()
{
    cin >> m >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> gBox[i][j];
        }
    }

    waiting();
    check();
    cout << gDays << endl;



}
