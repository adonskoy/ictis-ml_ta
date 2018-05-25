//
// Created by Антон Донской on 14.05.2018.
//

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include "DateTime.h"
#include <iostream>
#include <set>

using namespace std;

struct Config {
public:
    int _variant{};
    int _count{};

    void read(const char *file_name = "config.txt");

    Config();
};

struct Call {
public:
    char _FIO[51];
    char _phoneNumber[16];
    DateTime _startTime;
    int _periodInSeconds;
    float _pricePerMinute;
};

struct CallInDataSet {
public:
    float _sumPrice = 0;
    int _sumPeriod = 0;
    int _count = 0;
    std::set<string> _abonents;
};


struct DataSet {
private:
    int n;
    DateTime T1, T2;
    std::map<string, CallInDataSet> _data;
    Call *_array;
    Config _config;
public:

    void input(const char *file_name);

    void select();

    void output(const char *file_name);

    bool CountOfCalls(const string &number);

    void initArray();
    ~DataSet();
};


void DataSet::input(const char *file_name) {
    ifstream input(file_name, ios::in | ios::binary);
    if (input.is_open()) {

        input.read((char *) &n, sizeof(int));

        initArray();

        input.read((char *) &T1, sizeof(DateTime));

        input.read((char *) &T2, sizeof(DateTime));
        for (int i(0); i < n; ++i) {
            input.read((char *) &_array[i], sizeof(Call));
        }
    } else {
        std::cout << "[ERROR]\tCant open " << file_name << std::endl;
        exit(EXIT_FAILURE);
    }
    input.close();
    cout << "[INFO]\t" << "Successfully read data from " << file_name << endl;
}

void DataSet::select() {
    for (int i(0); i < n; ++i) {
        if ((T1 <= _array[i]._startTime) && (_array[i]._startTime <= T2)) {

            _data[string(_array[i]._phoneNumber)]._count++;
            _data[string(_array[i]._phoneNumber)]._sumPeriod += _array[i]._periodInSeconds;
            _data[string(_array[i]._phoneNumber)]._sumPrice += ceil(
                    _array[i]._pricePerMinute * 100 / 60 * _array[i]._periodInSeconds
            ) / 100;
            _data[string(_array[i]._phoneNumber)]._abonents.insert(_array[i]._FIO);

        }
    }

    for (auto p : _data) {
        if (!CountOfCalls(p.first)) {
            _data.erase(p.first);
//            _data.end();
        }
    }
    cout << "[INFO]\t" << _data.size() << " outgoing calls selected" << endl;
}

bool DataSet::CountOfCalls(const string &number) {
    if (_config._variant == 3) {
        return true;
    } else {
        return _data[number]._count <= _config._count;
    }
}

void DataSet::output(const char *file_name) {
    ofstream output(file_name, ios::out);
    if (output.is_open()) {
        output << _data.size() << endl;
        if (_config._variant == 2) {
            for (auto p : _data) {
                output << p.first << " " << p.second._sumPrice << " " << p.second._sumPeriod << endl;
            }
        } else {
            for (auto p : _data) {
                output << p.first << " " << p.second._abonents.size() << endl;
            }
        }
    } else {
        std::cout << "[ERROR]\tCant open " << file_name << std::endl;
        exit(EXIT_FAILURE);
    }
    output.close();
    cout << "[INFO]\tResult successfully saved in " << file_name << endl;
}

void DataSet::initArray() {
    _array = new Call[n];
}


void make_bin_file(const char *input_file_name, const char *output_file_name ) {
    ifstream input(input_file_name, ios::in);
    if (!input.is_open()) {
        std::cout << "[ERROR]\tCant open " << input_file_name << std::endl;
        exit(EXIT_FAILURE);
    }
    ofstream output(output_file_name, ios::out | ios::binary);
    if (!output.is_open()) {
        std::cout << "[ERROR]\tCant open " << output_file_name << std::endl;
        exit(EXIT_FAILURE);
    }
    int n;
    DateTime T1{}, T2{};
    input >> n;

    output.write((char *) &n, sizeof(int));

    input >> T1;
    output.write((char *) &T1, sizeof(DateTime));
    input >> T2;
    output.write((char *) &T2, sizeof(DateTime));
    for (int i(0); i < n; ++i) {
        Call tmp{};
        input.ignore(1, '\n');
        input.getline(tmp._FIO, 51, ' ');
        input.getline(tmp._phoneNumber, 16);
        input.clear();
        input >> tmp._startTime;
        input >> tmp._periodInSeconds;
        input >> tmp._pricePerMinute;
        output.write((char *) &tmp, sizeof(Call));
    }

    input.close();
    output.close();
    cout << "[INFO]\tFile " << input_file_name << " successfuly converted to " << output_file_name << endl;
}

void Config::read(const char * file_name) {
    ifstream input(file_name, ios::in);
    if (!input.is_open()) {
        _variant = 3;
        cout << "[WARN]\tFile-config " << file_name << " doesn't exist. Solving task for variant 3" << endl;
    } else {
        input >> _variant;
        if (!(_variant == 2 || _variant == 3)) {
            cout << "[ERROR]\tThere are only 2 available variants: 2 or 3" << endl;
            exit(EXIT_FAILURE);
        }
        cout << "[INFO]\t" << "Solving task for variant " << _variant << endl;
        if (_variant == 2) {
            input >> _count;
            if (_count < 1) {
                cout << "[ERROR]\tCount of max repeats shuld be more than zero" << endl;
                exit(EXIT_FAILURE);
            }
            cout << "[INFO]\t" << "Count of max repeats set to " << _count << endl;
        }
    }
}

Config::Config() {
    read();
}

DataSet::~DataSet() {
    delete[] _array;
}