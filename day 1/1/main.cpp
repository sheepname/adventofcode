#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main() {
    ifstream file("input1.txt");
    
    if (!file.is_open()) {
        return 1;
    }
    
    int dial = 50;
    int compteur = 0;

    string line;
    while (getline(file, line)) {
        if(line[0] == 'R'){
            dial += stoi(line.substr(1,3));
        }else if (line[0] == 'L')
        {
            dial -= stoi(line.substr(1,3));
        }

        if (dial < 0)
        {
            dial = (100 - (abs(dial) % 100)) % 100;
        }    
        else if(dial >= 100)
        {   
            dial = dial % 100;
        }
        
        if(dial == 0)
        {
            compteur++;
        }

        cout << dial << endl;
    }
    
    file.close();
    cout << compteur << endl;
    return 0;
}