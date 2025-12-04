#include <iostream>
#include <fstream>
#include <string>
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

    static const int OFFSETS[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0,  -1},          {0,  1},
        {1,  -1}, {1,  0}, {1, 1 }
    };

    // création du tableaux de base
    vector<string> tab;
    string line;
    while (getline(file, line))
    {
        string element = "." + line + ".";
        tab.push_back(element);
    }

    // entourer le tableau de points pour ne pas a avoir a check si on est au bors.
    string border(tab[0].length(), '.');
    tab.insert(tab.begin(), border);
    tab.push_back(border);

    //juste pour faire un log.txt
    ostringstream log;

    int compteur = 0;

    vector<string> temporaryTab = tab; // tab qui subit les changements.
    int oldCompteur = -1;              // pour verifier qu'il y a eu des changements
    
    int iteration = 0;
    while (oldCompteur != compteur)
    {   
        //demarage de l'itération
        tab = temporaryTab;
        oldCompteur = compteur;

        // traitement du tableau 
        for (int i = 0; i < tab.size(); i++)
        {
            for (int j = 0; j < tab[i].length(); j++)
            {
                if (tab[i][j] == '@')
                {
                    int neihbors = 0;
                    for (int k = 0; k < 8; k++)
                    {
                        int ni = i + OFFSETS[k][0];
                        int nj = j + OFFSETS[k][1];
                        if (tab[ni][nj] == '@')
                        {
                            neihbors++;
                        }
                    }
                    if (neihbors < 4)
                    {
                        compteur++;
                        temporaryTab[i][j] = '.'; // enlever dans le tableaux temporaire
                        log << "X";
                    }
                    else
                    {
                        log << "@";
                    }
                }
                else
                {
                    log << ".";
                }
            }
            log << endl;
        }

        cout << endl << "---- Fin de l'itération " << iteration << " ----" << endl <<  "====> " << compteur - oldCompteur << " éléments enlevés cette itération." << endl << endl;
        log << endl << "---- Fin de l'itération " << iteration << " ----" << endl <<  "====> " << compteur - oldCompteur << " éléments enlevés cette itération." << endl << endl;
        if(iteration > 1000)
        {
            break;
        }
        iteration++;
    }
    cout << "Compteur final : " << compteur << endl;
    log << "Compteur final : " << compteur << endl;

    ofstream logfile("log.txt");
    logfile << log.str();

    logfile.close();
    file.close();
    return 0;
}