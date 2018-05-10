//
// Created by Антон Донской on 31.03.2018.
//
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class CM {
private:
    int n, k, R, **Dots, **Result, SizeResult = 0;

    int getRadius(int *cm, int *Dots);

    int *getCM();

public:
    void read(const char *file_name);


    void findDots();
    void write(const char *file_name);
};

void CM::read(const char * file_name) {
    ifstream instr(file_name, ios::in | ios::binary);
    instr.read((char *) &n, sizeof(int));
    instr.read((char *) &k, sizeof(int));
    instr.read((char *) &R, sizeof(int));
    Dots = new int *[n];
    for (int i(0); i < n; ++i) {
        Dots[i] = new int[k];
    }
    for (int i(0); i < n; ++i) {
        for (int j(0); j < k; ++j) {
            instr.read((char *) &Dots[i][j], sizeof(int));
        }
    }
    instr.close();
}

int * CM::getCM() {
    auto *cm = new int[k];
//    cm = {0};
    for (int i(0); i < k; ++i) {
        cm[i] = 0;
    }
    for (int i(0); i < k; ++i) {
        for (int j(0); j < n; ++j) {
            cm[i] += Dots[j][i];
        }
        cm[i] /= n;
    }
    return cm;
}

int CM::getRadius(int * cm, int * Dot) {
    int r = 0;
    for (int i(0); i < k; ++i) {
        r += pow(cm[i] - Dot[i], 2);
    }
    r = sqrt(r);
    return r;
}

void CM::findDots() {
    int *cm = getCM();
    Dots = new int *[n];
    for (int i(0); i < n; ++i) {
        if (getRadius(cm, Dots[i]) <= R) {
            Result[SizeResult] = Dots[i];
            SizeResult++;
        }
    }
}

void CM::write(const char* file_name) {
    ofstream outstr(file_name, ios::out | ios::binary);
    outstr.write((char *) &SizeResult, sizeof(int));
    for (int i(0); i < SizeResult; ++i) {
        outstr.write((char *) &Result[i], sizeof(int) * k);
    }
    outstr.close();
}

void createBin(const char* input, const char* output) {
    ifstream inp(input, ios::in);
    ofstream out(output, ios::out | ios::binary);

    while (inp) {
        int tmp;
        inp >> tmp;
        out.write((char *) &tmp, sizeof(int));
    }
    inp.close();
    out.close();
}

void createTxt(const char* input, const char* output) {
    ifstream inp(input, ios::in | ios::binary);
    ofstream out(output, ios::out);
    while (inp) {
        int tmp;
        inp.read((char *) &tmp, sizeof(int));
        out << tmp;

    }
    inp.close();
    out.close();
}

int main() {
    createBin("input.txt", "input.bin");
    CM Problem;
    Problem.read("input.bin");
    Problem.findDots();
    Problem.write("output.bin");
    createTxt("output.bin", "output.txt");
}