//
// Created by Антон Донской on 13.05.2018.
//

#include "selection.h"
#include <fstream>
#include <iostream>

void Selection::input(const char *file_name) {
    std::ifstream input(file_name);

    if (input.is_open()) {

        std::string tmp;
        input >> tmp;
        _taskId = tmp[0];
        _typeVariable = tmp[2];

        input >> _size;

        if (_typeVariable == 'a') {

            initArrayInt();
            for (int i(0); i < _size; ++i) {
                input >> _arrayInt[i];
            }
        } else {
            initArrayFloat();
            for (int i(0); i < _size; ++i) {
                input >> _arrayFloat[i];
            }
        }

    } else {
        std::cout << "Cant open " << file_name << std::endl;
    }
    input.close();
}

void Selection::output(const char *file_name) {
    std::ofstream output(file_name);
    if (output.is_open()) {
        output << _size << std::endl;
        if (_typeVariable == 'a') {
            for (int i(0); i < _size; ++i) {
                output << _arrayInt[i] << " ";
            }
        } else {
            for (int i(0); i < _size; ++i) {
                output << _arrayFloat[i] << " ";
            }
        }
    } else {
        std::cout << "Cant open " << file_name << std::endl;
    }
    output.close();
}

Selection::~Selection() {
    if (_typeVariable == 'a') {
        delete[] _arrayInt;
    } else {
        delete[] _arrayFloat;
    }
}

void Selection::select() {
    if (_typeVariable == 'a') {
        intptr fp = getIntFunc();
        _arrayInt = fp(_arrayInt, _size, &_size);
    } else {
        floatptr fp = getFloatFunc();
        _arrayFloat = fp(_arrayFloat, _size, &_size);
    }
}


Selection::intptr Selection::getIntFunc() {

    switch (_taskId) {
        case 'A':
            return (intptr) Functions::positive_numbers;
        case 'B':
            return (intptr) Functions::negative_numbers;
        case 'C':
            return (intptr) Functions::arifm;
        default:
            return nullptr;
    }
}

Selection::floatptr Selection::getFloatFunc() {

    switch (_taskId) {
        case 'A':
            return (floatptr) Functions::positive_numbers;

        case 'B':
            return (floatptr) Functions::negative_numbers;
        case 'C':
            return (floatptr) Functions::arifm;
        default:
            return nullptr;
    }
}

void Selection::initArrayInt() {
    _arrayInt = new int[_size];
}

void Selection::initArrayFloat() {
    _arrayFloat = new float[_size];
}