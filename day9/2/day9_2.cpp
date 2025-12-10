#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <random>
#include <array>
#include <cstdlib>

using namespace std;

struct redlight
{
    long long x, y;
};

struct edge
{
    redlight a;
    redlight b;
    long long maxX()
    {
        return max(a.x, b.x);
    }
    long long minX()
    {
        return min(a.x, b.x);
    }
    long long maxY()
    {
        return max(a.y, b.y);
    }
    long long minY()
    {
        return min(a.y, b.y);
    }
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

    while (fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%lld,%lld", &x, &y);
        redlights.push_back({x, y});
    }
    fclose(file);

    vector<edge> verticaledges;
    vector<edge> horizontaledges;
    for (size_t i = 0, j = redlights.size() - 1; i < redlights.size(); j = i++)
    {
        if (redlights[i].x == redlights[j].x)
        {
            verticaledges.push_back({redlights[j], redlights[i]});
        }
        else
        {
            horizontaledges.push_back({redlights[j], redlights[i]});
        }
    }

    long long maxarea = 0;
    for (long long i = 0; i < redlights.size(); i++)
    {
        for (long long j = i + 1; j < redlights.size(); j++)
        {
            long long maxX = max(redlights[i].x, redlights[j].x);
            long long minX = min(redlights[i].x, redlights[j].x);
            long long maxY = max(redlights[i].y, redlights[j].y);
            long long minY = min(redlights[i].y, redlights[j].y);
            long long dx = maxX- minX + 1;
            long long dy = maxY - minY + 1;
            long long d = dx * dy;
            if (d > maxarea)
            {
                bool valid = true;
                for (edge ve : verticaledges)
                {
                    if ((ve.a.x > minX && ve.a.x < maxX))// regarde si l'edge est entre les deux redlights qui lui sont parralleles
                    {
                        if (redlights[i].y >= ve.minY() && redlights[i].y < ve.maxY())//regarde si l'edge croise la ligne horizontale passant par le redlight i
                        {
                            valid = false;
                            break;
                        }
                        if (redlights[j].y >= ve.minY() && redlights[j].y < ve.maxY()) //Regarde si l'edge croise la ligne horizontale passant par le redlight j
                        {
                            valid = false;
                            break;
                        }
                    }
                }
                if (valid)
                {
                    for (edge he : horizontaledges)
                    {
                        if ((he.a.y > minY && he.a.y < maxY))// regarde si l'edge est entre les deux redlights qui lui sont parralleles
                        {
                            if (redlights[i].x >= he.minX() && redlights[i].x <= he.maxX())//regarde si l'edge croise la ligne verticale passant par le redlight i
                            {
                                valid = false;
                                break;
                            }
                            if (redlights[j].x >= he.minX() && redlights[j].x <= he.maxX())//Regarde si l'edge croise la ligne verticale passant par le redlight j
                            {
                                valid = false;
                                break;
                            }
                        }
                    }
                }
                if (valid)
                {
                    maxarea = d;
                }
            }
        }
    }

    cout << "max area corner: " << maxarea << endl;
    return 0;
}
