//
// Created by Антон Донской on 03.04.2018.
//


#include <iostream>
#include <fstream>
using namespace std;


class IntersectionOfSets {
private:
    int count{}, *Sizes{}, **Sets{}, *result{}, SizeResult = 0;

    bool findIn(int element, const int *set, int size);

public:
    ~IntersectionOfSets();

    void read(const char *file_name);

    void intersection();

    void write(const char *file_name);
};

void IntersectionOfSets::read(const char *file_name) {
    ifstream instr(file_name, ios::in | ios::binary);
    if(instr.is_open()) {
        instr.read((char *) &count, sizeof(int));
        Sizes = new int[count];
        Sets = new int *[count];
        for (int i(0); i < count; ++i) {
            instr.read((char *) &Sizes[i], sizeof(int));
            Sets[i] = new int[Sizes[i]];
        }

        for (int i(0); i < count; ++i) {
            for (int j(0); j < Sizes[i]; ++j) {
                instr.read((char *) &Sets[i][j], sizeof(int));
            }
        }
    } else {
        cout << "Cant open " << file_name << endl;
    }
    instr.close();
}
bool IntersectionOfSets::findIn(int element, const int *set, int size) {
    for (int i(0); i < size; ++i) {
        if (element == set[i]) {
            return true;
        }
    }
    return false;
}

void IntersectionOfSets::intersection() {
    result = new int[Sizes[0]];
    for (int i(0); i < Sizes[0]; ++i) {
        bool exist = true;
        for (int j(1); j < count; ++j) {
            if (!findIn(Sets[0][i], Sets[j], Sizes[j])) {
                exist = false;
                break;
            }
        }
        if (exist) {
            result[SizeResult] = Sets[0][i];
            SizeResult++;
        }
    }
}

void IntersectionOfSets::write(const char* file_name) {
    ofstream outstr(file_name, ios::out);
    if(outstr.is_open()) {
        outstr << SizeResult << endl;
        for (int i = 0; i < SizeResult; i++) {
            outstr << result[i] << " ";
        }
    } else {
        cout << "Cant open " << file_name << endl;
    }
    outstr.close();
}

IntersectionOfSets::~IntersectionOfSets() {
    delete[] Sets;
    delete[] result;
    delete[] Sizes;
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
    IntersectionOfSets Problem;
    Problem.read("input.bin");
    Problem.intersection();
    Problem.write("output.txt");
    return 0;
}

