#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <random>
#include <array>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct redlight
{
    long long x, y;
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
    long long x, y;

    char buffer[30];
    vector<redlight> redlights;
    vector<long long> xcs;
    vector<long long> ycs;

    while (fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%lld,%lld", &x, &y);
        redlights.push_back({x, y});
        xcs.push_back(x);
        xcs.push_back(x - 1);
        xcs.push_back(x + 1);
        ycs.push_back(y);
        ycs.push_back(y - 1);
        ycs.push_back(y + 1);
    }

    sort(xcs.begin(), xcs.end());
    xcs.erase(unique(xcs.begin(), xcs.end()), xcs.end());

    sort(ycs.begin(), ycs.end());
    ycs.erase(unique(ycs.begin(), ycs.end()), ycs.end());

    unordered_map<long long, long long> xmap, ymap;
    for (size_t i = 0; i < xcs.size(); i++)
    {
        xmap[xcs[i]] = i;
    }
    for (size_t i = 0; i < ycs.size(); i++)
    {
        ymap[ycs[i]] = i;
    }

    vector<vector<char>> grid(ycs.size(), vector<char>(xcs.size(), '.'));

    // colorier les contours
    for (long long i = 0, j = redlights.size() - 1; i < redlights.size(); j = i++)
    {
        if (redlights[i].x == redlights[j].x) // meme x
        {
            long long miny = ymap[min(redlights[i].y, redlights[j].y)];
            long long maxy = ymap[max(redlights[i].y, redlights[j].y)];
            long long x = xmap[redlights[i].x];
            for (long long y = miny; y <= maxy; y++)
            {
                grid[y][x] = '#';
            }
        }
        else if (redlights[i].y == redlights[j].y) // meme y
        {
            long long minx = xmap[min(redlights[i].x, redlights[j].x)];
            long long maxx = xmap[max(redlights[i].x, redlights[j].x)];
            long long y = ymap[redlights[i].y];
            for (long long x = minx; x <= maxx; x++)
            {
                grid[y][x] = '#';
            }
        }
        else
        {
            cout << "Error: non axis-aligned edge detected." << endl;
            return 1;
        }
    }

    cout << "contours faits" << endl;

    // colorer l'exterieur
    array<long long, 2> start = {0, 0};
    queue<array<long long, 2>> tovisit;
    tovisit.push(start);
    // on remplit l'exterieur'
    while (!tovisit.empty())
    {
        array<long long, 2> current = tovisit.front();
        tovisit.pop();
        if (grid[current[1]][current[0]] == '.')
        {
            grid[current[1]][current[0]] = 'E';

            
            if(current[0] > 0) tovisit.push({current[0] - 1, current[1]});
            if(current[0] < grid[0].size()-1) tovisit.push({current[0] + 1, current[1]});
            if(current[1] > 0) tovisit.push({current[0], current[1] - 1});
            if(current[1] < grid.size()-1) tovisit.push({current[0], current[1] + 1});
        }
    }

    ofstream outfile("output.txt");
    for (const auto &row : grid)
    {
        outfile.write(row.data(), row.size());
        outfile.put('\n');
    }
    outfile.close();

    cout << "longerieur rempli" << endl;

    long long maxarea = 0;
    for (long long i = 0; i < redlights.size(); i++)
    {
        for (long long j = i + 1; j < redlights.size(); j++)
        {
            long long dx = abs(redlights[i].x - redlights[j].x) + 1;
            long long dy = abs(redlights[i].y - redlights[j].y) + 1;
            long long d = dx * dy;
            if (d > maxarea)
            {
                bool valid = true;
                for(long long x = xmap[min(redlights[i].x, redlights[j].x)]; x <= xmap[max(redlights[i].x, redlights[j].x)]; x++)
                {
                    for(long long y = ymap[min(redlights[i].y, redlights[j].y)]; y <= ymap[max(redlights[i].y, redlights[j].y)]; y++)
                    {
                        if (grid[y][x] == 'E')
                        {
                            valid = false;
                            break;
                        }
                    }
                    if(!valid) break;
                }
                if(valid)
                {
                    maxarea = d;
                }
            }
        }
        
    }

    cout << "max area corner: " << maxarea << endl;

    fclose(file);
    return 0;
}
