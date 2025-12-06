#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    struct opStruct
    {
        char op;
        int taille;
        int index;
    };

    ifstream file("input.txt");

    if (!file.is_open())
    {
        return 1;
    }

    vector<string> lines;
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    vector<opStruct> ops;
    opStruct tempOP;
    bool isFirst = true;
    string opLine = lines[lines.size() - 1];
    lines.pop_back(); // important pour ne plus avoir que les chifre.
    for (int i = 0; i < opLine.size(); i++)
    {
        char c = opLine[i];
        if (c == '+' || c == '*')
        {
            if (isFirst)
            {
                isFirst = false;
            }
            else
            {
                ops.push_back(tempOP);
            }
            tempOP = {c, 0, i};
        }
        else
        {
            tempOP.taille++;
        }
    }
    tempOP.taille++;// o augmente la taille car par de dernier espace pour séparer cette colone de la fin.
    ops.push_back(tempOP); //rajoute le dernier op

    long long compteur = 0;
    for (int i = 0; i < ops.size(); i++)
    {
        vector<int> tempsInt;

        for (int indexInTheString = 0; indexInTheString < ops[i].taille; indexInTheString++)
        {
            int temp = 0;
            for (int indexInTheArrays = 0; indexInTheArrays < lines.size(); indexInTheArrays++)
            {
                char c = lines[indexInTheArrays].substr(ops[i].index, ops[i].taille)[indexInTheString];
                if(isdigit(c))
                {
                    temp = (temp * 10) + (c - '0');
                }
            }
            tempsInt.push_back(temp);
            cout << temp << " ";
        }
        cout << ops[i].op;

        long long temp = (ops[i].op == '+') ? 0 : 1;
        for (int nbr : tempsInt)
        {
            temp = (ops[i].op == '+') ? temp + nbr : temp * nbr;
        }
        cout << " " << temp << endl;
        compteur += temp;
    }

    cout << "fianl compteur = " << compteur << endl;

    file.close();
    return 0;
}
