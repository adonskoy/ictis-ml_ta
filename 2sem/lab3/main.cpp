//
// Created by Антон Донской on 03.04.2018.
//

#include <iostream>
#include "phone.h"

using namespace std;
using namespace Phones;

int main() {
    Phone find_phones;
    find_phones.input("input.txt");
    find_phones.find();
    find_phones.output("output.txt");
    return 0;
}