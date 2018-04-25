//
// Created by Антон Донской on 01.04.2018.
//

#include <iostream>
#include <fstream>
using namespace std;

int ** read(const char* file_name, int *n, int *m) {
    ifstream instr(file_name, ios::in);
    instr >> *n;
    instr >> *m;
    auto **z = new int *[2];
    z[0] = new int[*n];
    z[1] = new int[*m];
    for (int i(0); i < 2; ++i) {
        for (int j(0); j < (i == 0 ? *n : *m); ++j) {
            instr >> z[i][j];
        }
    }
    instr.close();
    return z;
}

void write(const char* file_name, int** mass, int size, int count) {
    ofstream outstr(file_name, ios::out | ios::binary);
    outstr.write((char *) &count, sizeof(int));
    for (int i(0); i < size; ++i) {
        if (mass[0][i] != NULL) {
            outstr.write((char *) mass[0][i], sizeof(int));
        }
    }

}

bool found_in_B(int a, int **arr, int size_b) {
    for (int i(0); i < size_b; ++i) {
        if (a == arr[1][i]) {
            return true;
        }
    }
    return false;
}

void diff(int ** arr, int size_a, int size_b, int  *count_a) {
    for (int i(0); i < size_a; ++i) {
        found_in_B(arr[0][i], arr, size_b) ? (arr[0][i] = NULL, *count_a = (*count_a) - 1) : 0;
    }
}

int main() {
    int n, m;
    int **array = read("input.txt", &n, &m);
    int count_a = n;
    diff(array, n, m, &count_a);
    write("output.bin", array, n, count_a);
}