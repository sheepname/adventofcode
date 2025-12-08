#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int X = 5, Y = 5, Z = 5;
int sizeX, sizeY, sizeZ;

struct junction
{
    int x, y, z;
    int reseau = -1;
    size_t chunkindex = 0;
    size_t chunkX = 0, chunkY = 0, chunkZ = 0;
};

struct reseau
{
    size_t index;
    vector<junction *> junctions;
};

struct chunk
{
    vector<junction *> junctions;
};

size_t index3D(int x, int y, int z)
{
    return x + y * X + z * X * Y;
}

double dist(junction a, junction b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

vector<junction *> getNeighborsInRadius(int chunkX, int chunkY, int chunkZ, int radius, vector<chunk> &chunks)
{
    vector<junction *> neighbors;
    for (int dx = -radius; dx <= radius; ++dx)
    {
        for (int dy = -radius; dy <= radius; ++dy)
        {
            for (int dz = -radius; dz <= radius; ++dz)
            {
                int nx = chunkX + dx;
                int ny = chunkY + dy;
                int nz = chunkZ + dz;
                if (nx < 0 || ny < 0 || nz < 0 || nx >= X || ny >= Y || nz >= Z)
                    continue;
                size_t idx = index3D(nx, ny, nz);
                for (junction *j : chunks[idx].junctions)
                    neighbors.push_back(j);
            }
        }
    }
    return neighbors;
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
        if (x > maxX)
            maxX = x;
        if (y > maxY)
            maxY = y;
        if (z > maxZ)
            maxZ = z;
        if (x < minX)
            minX = x;
        if (y < minY)
            minY = y;
        if (z < minz)
            minz = z;
    }

    // calcul de la taille de la grille 3D pour savoir le nombrede chunk a faire et leur taille;
    sizeX = (maxX - minX + 1 + 4) / X; //+4 pour avoir une marge
    sizeY = (maxY - minY + 1 + 4) / Y;
    sizeZ = (maxZ - minz + 1 + 4) / Z;

    vector<chunk> chunks(X * Y * Z);

    for (junction &j : junctions)
    {
        int chunkX = (j.x - minX) / sizeX;
        int chunkY = (j.y - minY) / sizeY;
        int chunkZ = (j.z - minz) / sizeZ;
        size_t idx = index3D(chunkX, chunkY, chunkZ);
        j.chunkindex = idx;
        j.chunkX = chunkX;
        j.chunkY = chunkY;
        j.chunkZ = chunkZ;
        chunks[idx].junctions.push_back(&j);
    }

    vector<reseau*> reseaux;

    // maintenant vlala boucle
    for (int i = 0; i < 1000; i++)
    {
        double distMin = 1e30;
        junction *a, *b;
        for (junction &j1 : junctions)
        {
            bool found = false;
            int radius = 0;
            vector<junction *> neighbors;
            while (!found && radius <= 10)
            {
                neighbors = getNeighborsInRadius(j1.chunkX, j1.chunkY, j1.chunkZ, radius, chunks);
                for (junction *j2p : neighbors)
                {
                    junction &j2 = *j2p;
                    if (&j1 == &j2 || (j1.reseau>= 0 && j2.reseau >= 0 && j1.reseau == j2.reseau))
                        continue;
                    double d = dist(j1, j2);
                    if (d < distMin)
                    {
                        distMin = d;
                        a = &j1;
                        b = &j2;
                        found = true;
                    }
                }
                radius++;
            }
        }
        if (a && b)
        {
            if(a->reseau == -1 && b->reseau == -1)
            {
                reseaux.push_back(new reseau{reseaux.size() + 1});
                a->reseau = reseaux.size();
                b->reseau = reseaux.size();
            }
            else if(a->reseau != -1 && b->reseau == -1)
            {
                b->reseau = a->reseau;
                reseaux[a->reseau - 1]->junctions.push_back(b);
            }
            else if(a->reseau == -1 && b->reseau != -1)
            {
                a->reseau = b->reseau;
                reseaux[b->reseau - 1]->junctions.push_back(a);
            }
            else
            {
                size_t reseauToKeep = a->reseau;
                size_t reseauToChange = b->reseau;
                for (junction *j : reseaux[reseauToChange - 1]->junctions)
                {
                    j->reseau = reseauToKeep;
                    reseaux[reseauToKeep - 1]->junctions.push_back(j);
                }
                reseaux[reseauToChange - 1]->junctions.clear();
            }
        }
        cout << "Iteration " << i << " : connected junctions at distance " << distMin << endl;
    }

    fclose(file);
    return 0;
}
