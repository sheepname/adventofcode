#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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

            stringstream ss(line);
            ss >> a >> tiret >> b;
            ranges.push_back({a, b});
        }
    }

    int compteur = 0;

    while (getline(file, line))
    {
        long long ID = stoll(line);
        for (range range : ranges)
        {
            if (ID >= range.a && ID <= range.b)
            {
                cout << ID << " est frais" << endl;
                compteur++;
                break;
            }
        }
        cout << ID << " n'est pas frais" << endl;
    }

    cout << "compteur final: " << compteur << endl;
    file.close();
    return 0;
}
