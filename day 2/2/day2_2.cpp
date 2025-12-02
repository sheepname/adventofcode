#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <unordered_set>

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
    while (getline(file, line, ','))
    {
        stringstream sline(line); // créer le stream à partir de la ligne
        long long debut, fin;
        char segment;
        cout << "Ligne lue : " << line << endl;
        sline >> debut >> segment >> fin; // sortir les données du stream, segment sert a recuperer le '-'

        long long lenDebbut = to_string(debut).length();
        long long lenFin = to_string(fin).length();

        if (lenDebbut == lenFin)
        {
            unordered_set<long long> alreadyIn;
            for (int l = 2; l <= lenDebbut; l++)
            {
                if (lenDebbut % l == 0)
                {
                    long long borneInf = stoll(to_string(debut).substr(0, lenDebbut / l));
                    long long borneSup = stoll(to_string(fin).substr(0, lenFin / l));
                    cout << "Borne inf : " << borneInf << " Borne sup : " << borneSup << endl;

                    for (int i = borneInf; i <= borneSup; i++)
                    {
                        long long nbr = 0;
                        for (int m = 0; m < l; m++)
                        {
                            nbr += i * pow(10, m * (lenDebbut / l));
                        }
                        if (nbr >= debut && nbr <= fin)
                        {
                            
                            if (alreadyIn.empty() ||  alreadyIn.find(nbr) == alreadyIn.end())
                            {
                                alreadyIn.insert(nbr);
                                cout << "Nombre trouvé : " << nbr << endl;
                                compteur += nbr;
                            }else
                            {
                                cout << "Nombre déjà comptabilisé : " << nbr << endl;
                            }
                        }
                    }
                }
            }
        }
        else if (lenDebbut != lenFin)
        {
            unordered_set<long long> alreadyIn;
            for (int i = lenDebbut; i <= lenFin; i++)
            {
                for (int l = 2; l <= i; l++)
                {
                    if (i % l == 0)
                    {
                        long long borneInf = (i == lenDebbut) ? stoll(to_string(debut).substr(0, lenDebbut / l)) : floor(pow(10, (i / l) - 1));
                        long long borneSup = (i == lenFin) ? stoll(to_string(fin).substr(0, lenFin / l)) : floor(pow(10, i / l) - 1);

                        for (int j = borneInf; j <= borneSup; j++)
                        {
                            long long nbr = 0;
                            for (int m = 0; m < l; m++)
                            {
                                nbr += j * pow(10, m * (i / l));
                            }

                            if (nbr >= debut && nbr <= fin)
                            {
                                if (alreadyIn.empty() ||  alreadyIn.find(nbr) == alreadyIn.end())
                            {
                                alreadyIn.insert(nbr);
                                cout << "Nombre trouvé : " << nbr << endl;
                                compteur += nbr;
                            }else
                            {
                                cout << "Nombre déjà comptabilisé : " << nbr << endl;
                            }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "Résultat final : " << compteur << endl;

    file.close();
    return 0;
}