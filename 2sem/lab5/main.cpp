//
// Created by Антон Донской on 13.05.2018.
//

#include "selection.h"

int main() {
    Selection _selection;
    _selection.input("input.txt");
    _selection.select();
    _selection.output("output.txt");
    return 0;
}