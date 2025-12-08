#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <memory>
#include <algorithm>

using namespace std;

const int X = 5, Y = 5, Z = 5;
int sizeX, sizeY, sizeZ;

struct junction
{
    const int x, y, z;
    int reseau = -1;
};

struct reseau
{
    vector<junction *> junctions;
};

struct edge
{
    junction *a;
    junction *b;
    double distance;
};

double dist(junction a, junction b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

int main()
{
    FILE *file = fopen("input.txt", "r");

    if (!file)
    {
        return 1;
    }

    string line;
    vector<junction> junctions;
    int maxX, maxY, maxZ, minX = INT_MAX, minY = INT_MAX, minz = INT_MAX;
    int x, y, z;

    char buffer[30];
    while (fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%d,%d,%d", &x, &y, &z);
        junctions.push_back({x, y, z});
    }

    // creation d'une que qui se trie par ordre croissant de distance
    auto cmp = [](const edge &e1, const edge &e2)
    {
        return e1.distance > e2.distance; // plus petit d'abord
    };
    priority_queue<edge, vector<edge>, decltype(cmp)> edgeQueue(cmp);

    for (int i = 0; i < junctions.size(); i++)
    {
        for (int j = i + 1; j < junctions.size(); j++)
        {
            double d = dist(junctions[i], junctions[j]);
            edgeQueue.push({&junctions[i], &junctions[j], d});
        }
    }

    vector<unique_ptr<reseau>> reseaux;
    while(!edgeQueue.empty())
    {
        edge e = edgeQueue.top();

        if (e.a->reseau == -1 && e.b->reseau == -1)
        {
            reseaux.push_back(make_unique<reseau>());
            e.a->reseau = reseaux.size() - 1;
            e.b->reseau = reseaux.size() - 1;
            reseaux[e.b->reseau]->junctions.push_back(e.a);
            reseaux[e.b->reseau]->junctions.push_back(e.b);
        }
        else if (e.a->reseau == -1 && e.b->reseau != -1)
        {
            e.a->reseau = e.b->reseau;
            reseaux[e.b->reseau]->junctions.push_back(e.a);
        }
        else if (e.a->reseau != -1 && e.b->reseau == -1)
        {
            e.b->reseau = e.a->reseau;
            reseaux[e.a->reseau]->junctions.push_back(e.b);
        }
        else if (e.a->reseau != e.b->reseau) // les deux sont dans des reseaux differents, on fusionne
        {
            int reseauA = e.a->reseau;
            int reseauB = e.b->reseau;
            for (junction *j : reseaux[reseauB]->junctions)
            {
                j->reseau = reseauA;
                reseaux[reseauA]->junctions.push_back(j);
            }
            reseaux[reseauB]->junctions.clear();
        }
        cout << "Connecte (" << e.a->x << "," << e.a->y << "," << e.a->z << ") et ("
             << e.b->x << "," << e.b->y << "," << e.b->z << ") distance : " << e.distance << endl;
        if(reseaux[e.a->reseau]->junctions.size() == junctions.size() && reseaux[e.b->reseau]->junctions.size() == junctions.size())
        {
            cout << "Tous les junctions sont connectes." << endl << "la longueur maximale est : " << e.a->x*e.b->x << endl;
            break;
        }
        edgeQueue.pop();
    }

    fclose(file);
    return 0;
}
