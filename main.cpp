#include "matrix.h"
#include <iostream>

using namespace mat;
using namespace std;

int main() {

    ifstream arq("001.pgm");
    //arg >> t >> w >> h >> m;
    //ifstream arq("teste.pgm");
    string sLine;
    string header, dimentions, max_input;
    getline(arq, sLine);
    header = sLine;
    getline(arq, sLine);
    dimentions = sLine;
    getline(arq, sLine);
    max_input = sLine;
    string dimentionsx = dimentions.substr(0, dimentions.find(" "));
    string dimentionsy = dimentions.substr(dimentions.find(" ") + 1, dimentions.size());
    int y = atoi(dimentionsx.c_str());
    int x = atoi(dimentionsy.c_str());
//    cout << header << endl;
//    cout << x << " " << y << endl;
//    cout << max_input << endl;
    int vetPos = 0;
    int vet[1000000];

    int cont = 0;
    /*while (!arq.eof()) {
        getline(arq, sLine);
        int count2 = 0;
        for (int i = 0; i < sLine.size(); i++) {
            if (sLine[i] == ' ') {}
            else {
                const char *c = &sLine[i];
                int n = atoi(c);
                cout << n << endl;
                vet[vetPos] = n;
                vetPos++;
                i++;
                count2++;
            }
        }
        cont++;
        arq.close();
    }*/

    string s;
    int k = 0;
    while (getline(arq, s))
    {
        istringstream line(s);
        string s2;

        int l = 0;
        while (getline(line, s2, ' '))
        {
            int n = stoi(s2);
            vet[k] = n;
            ++k;
            ++l;
            //cout << l << endl;
        }
    }

    auto matriz = Matrix<int>(x, y);

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            //cout << vet[i * y + j] << " ";
            //cout << vet[90000] << " ";
            matriz.at(i, j) = vet[i * y + j];
        }
    }

//    for (int i = 0; i < 1000; ++i)
//    {
//        cout << vet[i] << "\t";
//    }
    //cout << matriz.serialize() << endl;
    //cout << matriz.salt_and_pepper_removal().serialize();
    //cout << matriz.noise_removal().serialize();

    ofstream outfile ("image.txt");
    outfile << "P2" << endl << y << " " << x << endl << max_input << endl;
    //auto x1 = matriz.noise_removal();
    auto x1 = matriz.noise_removal_median();
    outfile << x1.serialize();

    outfile.close();

    return 0;
}
