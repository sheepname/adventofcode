#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    ifstream file("input.txt");

    if (!file.is_open())
    {
        return 1;
    }

    vector<stringstream> sstreams;
    string line;
    while (getline(file, line))
    {
        sstreams.emplace_back(line);
    }

    vector<vector<int>> numberArrays;
    for (int i = 0; i < sstreams.size() - 1; i++)
    {
        vector<int> array;
        int n;
        while (sstreams[i] >> n)
        {
            array.push_back(n);
        }
        numberArrays.push_back(array);
    }

    vector<char> ops;
    for (char c : sstreams[sstreams.size() - 1].str())
    {
        if (c == '+' || c == '*')
        {
            ops.push_back(c);
        }
    }

    long long compteur =0;
    for (int i = 0; i < ops.size(); i++)
    {
        long long temp = (ops[i] == '+')? 0 : 1;
        for(vector<int> array : numberArrays)
        {
            temp = (ops[i] == '+')? temp + array[i]: temp * array[i]; 
        }
        compteur += temp;
    }

    cout << "fianl compteur = " << compteur << endl;

    file.close();
    return 0;
}
