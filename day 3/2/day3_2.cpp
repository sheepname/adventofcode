#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    ifstream file("input.txt");

    if (!file.is_open())
    {
        return 1;
    }

    long long compteur = 0;

    string line;
    while (getline(file, line))
    {
        int maxs[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int lastID = -1;
        int lastlastID = -2;
        cout << "len : " << line.length() << endl;
        for (int j = 0; j < 12; j++) // pour boucler dans les maxs
        {
            int beforMAx = maxs[j];
            cout << "maxs[" << j << "]" << endl;
            for (int i = lastID + 1; i < line.length() - 11 + j; i++) // on boucle dans le string a partir de la dernier possition utilisé jusqu'a la taille max moins le nombre de max deja utilisé
            {   
                lastlastID = lastID;
                
                int val = line[i] - '0';
                cout << "Comparaison de " << val << " line[" << i << "]" << endl;
                if (val > maxs[j])
                {
                    maxs[j] = val;
                    lastID = i;
                    for (int k = j + 1; k < 12; k++)
                    { // on boucle sur tout les maxs après
                        maxs[k] = line[i + k - j] - '0';
                    }
                }
                if (lastID == lastlastID && (line[lastID]- '0') != maxs[j])
                {
                    lastID++;
                }
            }
            if(maxs[j] == beforMAx)
            {
                cout << "Aucun changement pour maxs[" << j << "], on incrémente lastID" << endl;
                lastID++;
            }
            cout << "maxs[" << j << "] = " << maxs[j] << endl;
        }

        long long bank = 0;
        for (int j = 0; j < 12; j++)
        {
            bank = bank * 10 + maxs[j];
        }
        cout << "Bank for this line: " << bank << endl;
        compteur += bank;
        cout << endl << endl;
    }

    cout << "Compteur final : " << compteur << endl;
    file.close();
    return 0;
}