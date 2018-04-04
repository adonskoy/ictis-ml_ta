//
// Created by Антон Донской on 03.04.2018.
//

#include <iostream>
#include <string>
#include <fstream>
#include "phone_code.h"
#include <regex>
using namespace std;

namespace Phones {
    Phone::Phone() {
        initNumbers();
        initText();
    }

    Phone::~Phone() {
        delete[] Text;
        delete[] Numbers;
    }

    void Phone::initNumbers() {
        NumbersCapacity = 2;
        NumbersSize = 0;
        Numbers = new string[NumbersCapacity];
    }

    void Phone::initText() {
        TextSize = 0;
        TextCapacity = 2;
        Text = new char[TextCapacity];
    }

    void Phone::input(const char *file_name) {
        std::ifstream fp(file_name);
        while (fp) {
            fp.get(Text[TextSize]);
            TextSize++;
            if (TextCapacity == TextSize) {
                resizeText(TextCapacity * 2);
            }
        }
        TextSize--;
        fp.close();
    }


    bool Phone::inNumbers(string number) {

        for (int i(0); i < NumbersSize; ++i) {
            if (Numbers[i] == number) {
                return true;
            }
        }
        return false;
    }

    void Phone::resizeText(int new_capacity) {
        auto *new_Array = new char[new_capacity];
        for (int i(0); i < TextCapacity; i++) {
            new_Array[i] = Text[i];
        }
        delete[] Text;
        Text = new_Array;
        TextCapacity = new_capacity;
    }

    void Phone::resizeNumbers(int new_capacity) {
        auto *new_Array = new string[new_capacity];
        for (int i(0); i < NumbersCapacity; i++) {
            new_Array[i] = Numbers[i];
        }
        delete[] Numbers;
        Numbers = new_Array;
        NumbersCapacity = new_capacity;
    }

    void Phone::output(const char *file_name) {
        ofstream fp(file_name);
        fp << NumbersSize << endl;
        for (int i(0); i < NumbersSize; i++) {
            fp << Numbers[i] << endl;
        }
        fp.close();
    }

    void Phone::find() {
        string regexp = "((^|\\s)8\\s9\\d\\d\\s\\d\\d\\d-\\d\\d-\\d\\d(\\s|\\,|\\.|\\;|$))";
        regex e(regexp);
        char a[18] = " 8 988 533-04-75.";
        for (int i(0); i < TextSize - 16; ++i) {
            char s[17];
            for (int j(0); j < 17; ++j) {
                s[j] = Text[i + j];

            }

            if (regex_match(s, e)) {
                string found = s;
                if (found.length() == 17) {
                    i += 2;
                    found = found.substr(1, 15);
                } else if (found.length() == 16) {
                    i += 1;
                    if (found[0] != '8') {
                        found = found.substr(1, 15);
                    } else {
                        found = found.substr(0, 15);
                    }
                }
                i += 14;
                if (!inNumbers(found)) {
                    Numbers[NumbersSize] = found;
                    NumbersSize++;
                    if (NumbersSize == NumbersCapacity) {
                        resizeNumbers(NumbersCapacity * 2);
                    }
                }
            }

        }
    }

}