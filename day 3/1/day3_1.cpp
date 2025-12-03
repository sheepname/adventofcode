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

    int compteur = 0;

    string line;
    while (getline(file, line))
    {
        int max1 = 0, max2 = 0;

        for (int i = 0; i < line.length() - 1; i++)
        {
            int val = line[i] - '0';

            if (val > max1)
            {
                max1 = val;
                max2 = line[i + 1] - '0';
            } 
            else if (val > max2)
            {
                max2 = val;
            }       
            
        }

        int lastVal = line.back() - '0';
        if(lastVal > max2){
            max2 = lastVal;
        }
        cout << max1 << max2 << endl;

        compteur += (max1 *10) + max2;
    }

    cout << "Compteur final : " << compteur << endl;
    file.close();
    return 0;
}