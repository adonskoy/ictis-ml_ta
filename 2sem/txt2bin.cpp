//
// Created by Антон Донской on 31.03.2018.
//

#include <iostream>
#include <fstream>
using namespace std;

int *read_mass(const char* file_name, int *size) {
    ifstream instr(file_name, ios::in);
    int capacity = 2;
    auto *mass = new int[capacity];
    while (instr) {
        instr >> mass[*size];
        *size = (*size) + 1;
        if (*size == capacity) {
            auto *new_mass = new int[capacity * 2];
            for (int i(0); i < capacity; ++i) {
                new_mass[i] = mass[i];
            }
            capacity *= 2;
            delete[] mass;
            mass = new_mass;
        }
    }
    return mass;
}

void write_mass_binary(const char* file_name,int* mass,int count) {
    ofstream outstr(file_name, ios::out | ios::binary);
    outstr.write((char *) mass, sizeof(int) * count);
}

int main() {
    int size = 0;
    int *mass = read_mass("input.txt", &size);
    write_mass_binary("output.bin", mass, size);
    return 0;
}
