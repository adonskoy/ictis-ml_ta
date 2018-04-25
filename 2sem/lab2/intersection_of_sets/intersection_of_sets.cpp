//
// Created by Антон Донской on 03.04.2018.
//

#include <iostream>
#include <fstream>
using namespace std;

int **read(const char *file_name, int *n) {
    ifstream instr(file_name, ios::in | ios::binary);
    instr.read((char *) n, sizeof(int));
    auto **mass = new int *[(*n) + 1];
    mass[0] = new int[*n];
    for (int i(0); i < *n; ++i) {
        instr.read((char *) &mass[0][i], sizeof(int));
    }
    for (int i(0); i < *n; ++i) {
        mass[i + 1] = new int[mass[0][i]];
        for (int j(0); j < mass[0][i]; ++j) {
            instr.read((char *) &mass[i + 1][j], sizeof(int));
            cout << mass[i + 1][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return mass;
}

void intersection(const int *n, int **mass, int *count) {
    for (int i(0); i < mass[0][0]; ++i) {
        for (int j(1); j < *n; ++j) {
            bool found = false;
            for (int k(0); k < mass[0][j]; ++k) {
                if (mass[1][i] == mass[j + 1][k]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                mass[1][i] = NULL;
                *count = (*count) - 1;
                break;
            }
        }
    }
}

void write(const char* file_name, int** mass, const int *count) {
    ofstream outstr(file_name, ios::out);
    outstr << *count << endl;
    for (int i = 0; i < mass[0][0]; i++) {
        if (mass[1][i] != NULL) {
            outstr << mass[1][i] << " ";
        }
    }
    outstr.close();
}

int main() {
    int n;
    int **mass = read("input.bin", &n);
    int count = mass[0][0];
    intersection(&n, mass, &count);
    write("output.txt", mass, &count);
    return 0;
}