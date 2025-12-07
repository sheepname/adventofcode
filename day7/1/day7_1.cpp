#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    ifstream file("input.txt");

    if (!file.is_open())
    {
        return 1;
    }

    // recuperation de la premiere ligne.
    vector<string> lines;
    string templine;
    while (getline(file, templine))
    {
        lines.push_back(templine);
    }

    // création d'un log.
    stringstream log;

    // recherche du S su la premiere ligne pour démarer;
    size_t start = lines[0].find('S', 0);
    lines[1][start] = '|';
    log << lines[0] << endl;

    int compteur = 0;

    for (size_t i = 1; i < lines.size() - 1; i += 2)
    {
        for (size_t j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == '|')
            {
                if (lines[i + 1][j] == '^')
                {
                    lines[i + 1][j - 1] = '|';
                    lines[i + 1][j + 1] = '|';
                    lines[i + 2][j - 1] = '|';
                    lines[i + 2][j + 1] = '|';

                    compteur++;
                }
                else
                {
                    lines[i+1][j] = '|';
                    lines[i+2][j] = '|';
                }
            }
        }
        log << lines[i] << endl
            << lines[i + 1] << endl;
    }

    cout << "compteur finale: " << compteur << endl;

    // enregistrement des log;
    ofstream logfile("log.txt");
    logfile << log.str();

    file.close();
    return 0;
}