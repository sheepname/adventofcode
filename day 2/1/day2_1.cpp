#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;
int main() {
    ifstream file("input.txt");
    
    if (!file.is_open()) {
        return 1;
    }
    
    long long compteur = 0;

    string line;
    while (getline(file, line, ','))
    {
        stringstream sline(line); //créer le stream à partir de la ligne
        long long debut,fin;
        char segment;
        cout << "Ligne lue : " << line << endl;
        sline >> debut >> segment >> fin; //sortir les données du stream, segment sert a recuperer le '-'

        long long lenDebbut = to_string(debut).length();
        long long lenFin = to_string(fin).length();


        if(lenDebbut == lenFin && lenDebbut % 2 == 0){
            long long borneInf = stoll(to_string(debut).substr(0, lenDebbut / 2));
            long long borneSup = stoll(to_string(fin).substr(0, lenFin / 2));
            cout << "Borne inf : " << borneInf << " Borne sup : " << borneSup << endl;
            for(int i = borneInf; i <= borneSup; i++){
                long long nbr = stoll(to_string(i) + to_string(i));
                if(nbr >= debut && nbr <= fin){
                    cout << "Nombre trouvé : " << nbr << endl;
                    compteur += nbr;
                }
            }
        } else if(lenDebbut != lenFin){
            for(int i = lenDebbut; i <= lenFin; i ++){
                if(i%2 == 0){
                    long long borneInf = (i == lenDebbut) ? stoll(to_string(debut).substr(0, lenDebbut / 2)) : floor(pow(10, (i / 2 )- 1));
                    long long borneSup = (i == lenFin) ? stoll(to_string(fin).substr(0, lenFin / 2)) :  floor(pow(10, i / 2 ) - 1);
                    cout << "Borne inf : " << borneInf << " Borne sup : " << borneSup << endl;
                    for(int j = borneInf; j <= borneSup; j++){
                        long long nbr = stoll(to_string(j) + to_string(j));
                        if(nbr >= debut && nbr <= fin){
                            cout << "Nombre trouvé : " << nbr << endl;
                            compteur += nbr;
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