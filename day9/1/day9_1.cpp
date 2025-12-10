#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct redlight
{
    int x, y;
};

struct corner
{
    redlight *a;
    redlight *b;
    long long area;
};

int main()
{
    FILE *file = fopen("input.txt", "r");

    if (!file)
    {
        return 1;
    }

    string line;
    int x, y;

    char buffer[30];
    vector<redlight> redlights;

    while (fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%d,%d", &x, &y);
        redlights.push_back({x, y});
    }

    

    auto compare = [](const corner &a, const corner &b)
    {
        return a.area < b.area;
    };

    long long maxarea = 0;
    for (int i = 0; i < redlights.size(); i++)
    {
        for (int j = i + 1; j < redlights.size(); j++)
        {
            long long dx = abs(redlights[i].x - redlights[j].x) +1;
            long long dy = abs(redlights[i].y - redlights[j].y) +1;
            long long d = dx * dy;
                if(d > maxarea)
                {
                    maxarea = d;
                }
        }
    }

    cout << "max area corner: " << maxarea << endl;

    fclose(file);
    return 0;
}
