#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int main()
{
    ifstream file("test.txt");

    if (!file.is_open())
    {
        return 1;
    }

    static const int OFFSETS[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    //création du tableaux de base
    vector<string> tab;
    string line;
    while (getline(file,line))
    {
        string element = "." + line + ".";
        tab.push_back(element);
    }

    //entourer le tableau de points pour ne pas a avoir a check si on est au bors.
    string border(tab[0].length(), '.');
    tab.insert(tab.begin(), border);
    tab.push_back(border);


    int compteur = 0;

    //traitement du tableau
    for (int i = 0; i < tab.size(); i++)
    {
        for(int j = 0; j < tab[i].length(); j++)
        {
            if(tab[i][j] == '@')
            {
                int neihbors = 0;
                for (int k = 0; k < 8; k++)
                {
                    int ni = i + OFFSETS[k][0];
                    int nj = j + OFFSETS[k][1];
                    if(tab[ni][nj] == '@')
                    {
                        neihbors++;
                    }
                }
                if(neihbors < 4){
                    compteur++;
                    cout << "X";
                }else{
                    cout <<"@";
                }
            }
            else
            {
                cout << ".";
            }
            
        }
        cout << endl;
        
    }
    
    cout << "Compteur final : " << compteur << endl;

    file.close();
    return 0;
}