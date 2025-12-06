#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
    struct range
    {
        long long a;
        long long b;
    };

    ifstream file("input.txt");

    if (!file.is_open())
    {
        return 1;
    }

    vector<range> ranges;
    long long compteur = 0;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            break;
        }
        else
        {
            long long a, b;
            char tiret;
            bool isAlreadyIN = false;

            stringstream ss(line);
            ss >> a >> tiret >> b;
            ranges.push_back({a, b});
        }
    }

    sort(ranges.begin(), ranges.end(),
         [](const range &r1, const range &r2)
         { return r1.a < r2.a; });

    long long maxA = -1, maxB = -1;
    bool isFirstRange = true;
    for (int i = 0; i < ranges.size(); i++)
    {
        if (maxB < ranges[i].a)
        {
            if (!isFirstRange)
            {
                compteur += maxB - maxA + 1;
                cout << "ajout de de la range finale: " << maxA << "-" << maxB << endl;
            }
            else
            {
                isFirstRange = false;
            }
            maxA = ranges[i].a;
            maxB = ranges[i].b;
        }
        else
        {
            maxB = max(maxB, ranges[i].b);
        }
    }
    compteur += maxB - maxA + 1;
    cout << "ajout de de la range finale: " << maxA << "-" << maxB << endl;

    cout << "compteur final: " << compteur << endl;
    file.close();
    return 0;
}
