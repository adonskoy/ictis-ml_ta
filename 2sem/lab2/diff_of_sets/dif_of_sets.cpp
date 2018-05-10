//
// Created by Антон Донской on 01.04.2018.
//

#include <iostream>
#include <fstream>
using namespace std;


class IntersectionOfSets {
private:
    int SizeA{}, SizeB{}, SizeC = 0, *SetA{}, *SetB{}, *SetC{};

    bool findB(int element);

public:
    ~IntersectionOfSets();

    void read(const char *file_name);

    void difference();


    void write(const char *file_name);
};

void IntersectionOfSets::read(const char* file_name) {
    ifstream instr(file_name, ios::in);
    instr >> SizeA;
    instr >> SizeB;

    SetA = new int[SizeA];
    SetB = new int[SizeB];
    for (int i(0); i < SizeA; ++i) {
        instr >> SetA[i];
    }
    for (int i(0); i < SizeB; ++i) {
        instr >> SetB[i];
    }

    instr.close();
}

void IntersectionOfSets::difference() {
    SetC = new int[SizeA];
    for (int i(0); i < SizeA; ++i) {
        if (!findB(SetA[i])) {
            SetC[SizeC] = SetA[i];
            SizeC++;
        }
    }
}

bool IntersectionOfSets::findB(int element) {
    for (int i(0); i < SizeB; ++i) {
        if (element == SetB[i]) {
            return true;
        }
    }
    return false;
}

void IntersectionOfSets::write(const char* file_name) {
    ofstream outstr(file_name, ios::out | ios::binary);
    outstr.write((char *) &SizeC, sizeof(int));
    cout<<SizeC<<endl;
    for (int i(0); i < SizeC; ++i) {
        outstr.write((char *) &SetC[i], sizeof(int));
        cout<<SetC[i]<<" ";
    }
}

IntersectionOfSets::~IntersectionOfSets() {
    delete[] SetA;
    delete[] SetB;
    delete[] SetC;
}
void createTxt(const char* input, const char* output) {
    ifstream inp(input, ios::in | ios::binary);
    ofstream out(output, ios::out);

    while (inp) {
        int tmp;
        inp.read((char *) &tmp, sizeof(int));
        out << tmp<<" ";

    }
    inp.close();
    out.close();
}
int main() {
    IntersectionOfSets Problem;
    Problem.read("input.txt");
    Problem.difference();
    Problem.write("output.bin");
    createTxt("output.bin", "output.txt");
    return 0;
}