//
// Created by Антон Донской on 31.03.2018.
//
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

int **read_mass_binary(const char* file_name, int *n, int *k, int *r) {
    ifstream instr(file_name, ios::in | ios::binary);
    instr.read((char *) n, sizeof(int));
    instr.read((char *) k, sizeof(int));
    auto **mass = new int *[*n];
    for (int i(0); i < *n; ++i) {
        mass[i] = new int[*k];
    }
    for (int i(0); i < *n; ++i) {
        for (int j(0); j < *k; ++j) {
            instr.read((char *) &mass[i][j], sizeof(int));
        }
    }
    instr.read((char *) r, sizeof(int));
    return mass;
}

void write_mass_binary(const char* file_name, int* mass, int count) {
    ofstream outstr(file_name, ios::out | ios::binary);
    outstr.write((char *) &count, sizeof(int));
    outstr.write((char *) mass, sizeof(int) * count);
}

int * getCM(int *n, int *k, int **mass) {
    auto *cm = new int[*k];
    for (int i(0); i < *k; ++i) {
        cm[i] = 0;
    }
    for (int i(0); i < *k; ++i) {
        for (int j(0); j < *n; ++j) {
            cm[i] += mass[j][i];
        }
        cm[i] /= *n;
    }
    return cm;
}

int getRadius(int * cm, int * point, int k){
    int r = 0;
    for(int i(0); i<k; ++i){
        r+= pow(cm[i]-point[i], 2);
    }
    r=sqrt(r);
    return r;
}

int main() {
    int n, k, r, cc = 2, countPM = 0;
    int **mass = read_mass_binary("input.bin", &n, &k, &r);
    int *cm = getCM(&n, &k, mass);
    int pm[n];
    for (int i(0); i < n; ++i) {
        if (getRadius(cm, mass[i], k) <= r) {
            pm[countPM] = i;
            countPM++;
        }
    }
    auto *output = new int[2 + countPM * k];
    output[0] = n, output[1] = k;
    for (int i(0); i < countPM; ++i) {
        for (int j(0); j < k; ++j) {
            output[cc] = mass[pm[i]][j];
            cc++;
        }
    }
    write_mass_binary("output.bin", output, cc);
}
