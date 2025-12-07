#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

string getlinesmultipicity(string line,const unordered_map<size_t, long long>& multiplicity)
{
    for(auto kv : multiplicity)
    {
        if(kv.second > 0 && kv.first != 0)
        {
            line[kv.first] = '0' + kv.second;
        }
    }

    return line;
}

int main()
{
    struct pathstruct
    {
        int multiplicity;
        vector<string> path;
    };

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

    // creation de log
    ofstream log("log.txt");

    // recherche du S su la premiere ligne pour démarer;
    size_t start = lines[0].find('S', 0);

    // gestion des path;
    unordered_map<size_t, long long> actualpaths;
    actualpaths[start] = 1;
    //log << lines[0] << endl << getlinesmultipicity(lines[1], actualpaths)<< endl;

    for (size_t i = 2; i < lines.size() - 1; i += 2)
    {
        unordered_map<size_t, long long> futurpaths; // la key c'est la place du beam et la value c'est ca multiplicity
        for (auto kv : actualpaths)
        {
            if (lines[i][kv.first] == '^')
            {
                futurpaths[kv.first - 1] += kv.second;
                futurpaths[kv.first + 1] += kv.second;
            }
            else
            {
                futurpaths[kv.first] += kv.second;
            }
        }

        actualpaths = futurpaths;       
        //log << getlinesmultipicity(lines[i], actualpaths) << endl << getlinesmultipicity(lines[i+1], actualpaths)<< endl;
    }

    long long totalmultiplicity = 0;

    for (auto kv : actualpaths)
    {
        log << "le beam " << kv.first << " a " << kv.second << " mltiplicity" << endl;
        totalmultiplicity += kv.second;
    }

    cout << "compteur finale: " << totalmultiplicity << endl;

    file.close();
    return 0;
}

