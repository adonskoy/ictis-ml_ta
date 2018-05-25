//
// Created by Антон Донской on 14.05.2018.
//

#include "DataSet.h"

int main() {
    DataSet a;
    make_bin_file("input.txt", "input.bin");
    a.input("input.bin");
    a.select();
    a.output("output.txt");

    return 0;
}