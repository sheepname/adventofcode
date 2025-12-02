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
        int previous_dial = dial;
        int step = 0;
        
        if(line[0] == 'R'){
            dial += stoi(line.substr(1,3));
        }else if (line[0] == 'L')
        {
            dial -= stoi(line.substr(1,3));
        }

        
        
        if (dial < 0)
        { 
            if(previous_dial != 0) 
            {        
                step = (abs(dial)/100) + 1;
            }else{
                step = (abs(dial)/100);
            }
            dial = (100 - (abs(dial) % 100)) % 100;
        }    
        else if(dial >= 100)
        { 
            step = dial / 100;
            dial = dial % 100;
        }
        else if(dial == 0)
        {
            compteur++;
        }
        
        compteur += step;

        cout << "[" << step << "]" << " " << compteur<< endl;

        cout << dial << endl;
    }
    
    file.close();
    cout << compteur << endl;
    return 0;
}