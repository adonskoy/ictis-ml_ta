////
//// Created by Антон Донской on 14.05.2018.
////
//
//#include <iostream>
//#include "DataSet.h"
//
//void DataSet::input(const char *file_name) {
//    ifstream input(file_name, ios::in | ios::binary);
//    if (input.is_open()) {
//        input.read((char *) &n, sizeof(int));
//        initArray();
//        input.read((char *) &T1, sizeof(DateTime));
//        input.read((char *) &T2, sizeof(DateTime));
//
//        for (int i(0); i < n; ++i) {
//            input.read((char *) &_array[i], sizeof(Call));
//        }
//    } else {
//        std::cout << "Cant open " << file_name << std::endl;
//    }
//    input.close();
//}
//
//void DataSet::select() {
//    for (int i(0); i < n; ++i) {
//        if ((T1 <= _array[i]._startTime) && (_array[i]._startTime <= T2)) {
//            _data[string(_array[i]._phoneNumber)]._count++;
//            _data[string(_array[i]._phoneNumber)]._sumPeriod += _array[i]._periodInSeconds;
//            _data[string(_array[i]._phoneNumber)]._sumPrice += ceil(
//                    _array[i]._pricePerMinute * 100 / 60 * _array[i]._periodInSeconds
//            ) / 100;
//        }
//    }
//    for (auto p : _data) {
//        if (!CountOfCalls(p.first)) {
//            _data.erase(p.first);
//        }
//    }
//
//}
//
//bool DataSet::CountOfCalls(const string &number) {
//    if (_config._variant == 3) {
//        return true;
//    } else {
//        return _data[number]._count <= _config._count;
//    }
//}
//
//// vector<std::pair<string, CallInDataSet>> DataSet::prepairData() {
////    vector<std::pair<string, CallInDataSet>> data;
////    for (auto &it : _data) {
////        if (it.second._count <= 3) {
////            data.emplace_back(it.first, it.second);
////        }
////    }
////    return data;
////}
//
//void DataSet::output(const char *file_name) {
//    ofstream output(file_name, ios::out);
//    output << n << endl;
//    if (_config._variant == 2) {
//        for (auto p : _data) {
//            output << p.first << " " << p.second._sumPrice << " " << p.second._sumPeriod << endl;
//        }
//    } else {
//        for (auto p : _data) {
//            output << p.first << " " << p.second._count << endl;
//        }
//    }
//}
//
//
//
//void DataSet::initArray() {
//    _array = new Call[n];
//}
//
//void make_bin_file(const char *input_file_name, const char *output_file_name ) {
//    ifstream input(input_file_name, ios::in);
//    ofstream output(output_file_name, ios::out | ios::binary);
//    int n;
//    DateTime T1{}, T2{};
//    input >> n;
//    output.write((char *) &n, sizeof(int));
//    input >> T1;
//    output.write((char *) &T1, sizeof(DateTime));
//    input >> T2;
//    output.write((char *) &T2, sizeof(DateTime));
//    for (int i(0); i < n; ++i) {
//        Call tmp{};
//        input >> tmp._FIO >> tmp._phoneNumber >> tmp._startTime >> tmp._periodInSeconds >> tmp._pricePerMinute;
//        output.write((char *) &tmp, sizeof(Call));
//    }
//    input.close();
//    output.close();
//}
//
//void Config::read(const char * file_name) {
//    ifstream input(file_name, ios::in);
//    if (!input.is_open()) {
//        _variant = 3;
//    } else {
//        input >> _variant;
//        if (_variant == 2) {
//            input >> _count;
//        }
//    }
//}
//
//Config::Config() {
//    read();
//}
